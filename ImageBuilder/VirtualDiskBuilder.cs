namespace ImageBuilder
{
    using System.Linq;

    using DiscUtils;
    using DiscUtils.Fat;
    using DiscUtils.Partitions;
    using DiscUtils.Streams;

    using ImageBuilder.Serialization;

    public record struct VirtualImageFormats(string Format, IEnumerable<string> Variant)
    {
        public string Format { get; init; } = Format;
        public IEnumerable<string> Variants { get; init; } = Variant;
    }

    public static class VirtualDiskBuilder
    {
        public static readonly Guid _EFIGUID = new("C12A7328-F81F-11D2-BA4B-00A0C93EC93B");

        private static long CalculateDirectorySize(string directoryPath)
        {
            return CalculateDirectorySize(new DirectoryInfo(directoryPath));
        }

        private static long CalculateDirectorySize(DirectoryInfo d)
        {
            long size = 0;
            // Add file sizes.
            foreach (FileInfo fi in d.EnumerateFiles())
            {
                size += fi.Length;
            }
            // Add subdirectory sizes.
            foreach (DirectoryInfo di in d.EnumerateDirectories())
            {
                size += CalculateDirectorySize(di);
            }

            return size;
        }

        /// <summary>
        /// Verify Filename conforms to FAT32 Standard fileNames without using System.IO
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        public static string VerifyFileName(string fileName)
        {
            var delimiter = fileName.LastIndexOf('.');

            var fatName = delimiter switch
            {
                -1 => fileName,
                _ => fileName[..delimiter]
            };

            var extension = delimiter switch
            {
                -1 => string.Empty,
                _ => fileName[delimiter..]
            };

            fatName = fatName.Replace('.', '*');
            fatName = fatName.Replace('\\', '*');
            fatName = fatName.Replace(':', '*');
            fatName = fatName.Replace('?', '*');
            fatName = fatName.Replace("*", string.Empty);
            fatName = fatName.ToUpper();

            if (delimiter > -1)
            {
                extension = extension.Replace('.', '*');
                extension = extension.Replace('\\', '*');
                extension = extension.Replace(':', '*');
                extension = extension.Replace('?', '*');
                extension = extension.Replace("*", string.Empty);
                extension = extension.ToUpper();

                if (fatName.Length > 8)
                {
                    fatName = fatName[..8];
                }
                else
                {
                    fatName = fatName.PadRight(8, ' ');
                }

                if (extension.Length > 3)
                {
                    extension = extension[..3];
                }
                else
                {
                    extension = extension.PadRight(3, ' ');
                }

                return fatName + extension;
            }
            else
            {
                if (fatName.Length > 11)
                {
                    fatName = fatName[..11];
                }
                else
                {
                    fatName = fatName.PadRight(11, ' ');
                }
                return fatName;
            }
        }


        private static long BuildVirtualDisc<Disc>(Disc disc, ImageConfig profile, DiscFormat format) where Disc : DiscUtils.VirtualDisk
        {
            var gptTable = GuidPartitionTable.Initialize(disc);
            var partTable = disc.Partitions;
            long partitionOffset = gptTable.FirstUsableSector;

            long TotalSize = 0;

            List<Partition> partitionsToWrite = new(profile.Partitions.Count);

            partitionsToWrite.AddRange(from p in profile.Partitions
                                       where p.PartitionTypeGUID == _EFIGUID
                                       orderby p.Label
                                       select p);

            partitionsToWrite.AddRange(from p in profile.Partitions
                                       where p.PartitionTypeGUID != _EFIGUID
                                       orderby p.Label
                                       select p);

            foreach (var partition in partitionsToWrite)
            {
                var dirInfo = new DirectoryInfo(partition.SourceDir);
                var dirSize = CalculateDirectorySize(dirInfo);
                long partSrcSize = Math.Max(partition.MinSizeBytes, dirSize);
                TotalSize += partSrcSize;
                int partInSectors;

                if (partSrcSize < disc.Geometry!.Value.BytesPerSector)
                {
                    partInSectors = 1;
                }
                else
                {
                    partInSectors = (int)Math.Ceiling(partSrcSize / (double)disc.Geometry!.Value.BytesPerSector) + 1;
                }


                int lastSector = (int)(partitionOffset + partInSectors);

                /*Ensure partitition is aligned properly to conform to the Advanced Format standard*/

                if (lastSector % disc.Geometry!.Value.SectorsPerTrack != 0)
                {
                    lastSector += disc.Geometry!.Value.SectorsPerTrack - (lastSector % disc.Geometry!.Value.SectorsPerTrack);
                }

                int part = gptTable.Create(partitionOffset, lastSector, partition.PartitionTypeGUID, partition.AttributeFlags, partition.Label);

                if (part == -1)
                {
                    var c = Console.ForegroundColor;
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    Console.WriteLine($"Partition {partition.Label} failed to be created... Skipping");
                    Console.ForegroundColor = c;
                    continue;
                }

                if (lastSector > gptTable.LastUsableSector)
                {
                    var c = Console.ForegroundColor;
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    Console.WriteLine($"Partition {partition.Label} exceeds the disk capacity by {lastSector - gptTable.LastUsableSector}sectors");
                    Console.ForegroundColor = c;
                    continue;
                }
                Console.WriteLine($"Creating Partition: {partition.Label} at {partitionOffset} with {partInSectors} sectors");
                using FatFileSystem fs = FatFileSystem.FormatPartition(gptTable[part].Open(), partition.Label, disc.Geometry!.Value, (int)partitionOffset, partInSectors, 0);

                partitionOffset += partInSectors;
                /*Enumerate all files and directories in the source directory and copy them to the file system*/

                foreach (var file in dirInfo.EnumerateFiles("*", SearchOption.AllDirectories))
                {
                    var dirs = file.FullName[(dirInfo.FullName.Length + 1)..].Split('\\', StringSplitOptions.RemoveEmptyEntries);

                    if(dirs is null)
                    {
                        continue;
                    }

                    if(dirs.Length == 0)
                    {
                        continue;
                    }

                    int last = Array.IndexOf(dirs, dirs.Last());
                    int i = 0;
                    string relativePath = "\\";
                    for (; i < dirs.Length - 1; i++)
                    {
                        if (i == last)
                        {
                            break;
                        }
                        relativePath = relativePath + dirs[i] + '\\';

                        if (!fs.DirectoryExists(relativePath))
                        {
                            fs.CreateDirectory(relativePath);
                        }
                    }

                    relativePath += VerifyFileName(dirs[i]).Trim('.');
                    try
                    {
                        file.OpenRead().CopyTo(fs.OpenFile(relativePath, FileMode.Create));
                    }
                    catch (Exception ex)
                    {
                        var c = Console.ForegroundColor;
                        Console.ForegroundColor = ConsoleColor.Yellow;
                        Console.WriteLine($"File {file.FullName} Failed to be copied Reason: {ex.Message}... Skipping");
                        Console.ForegroundColor = c;
                    }
                }
                disc.Content.Flush();
            }
            return TotalSize;
        }

        public static void BuildDiscImage(ImageConfig profile, IEnumerable<DiscFormat> formats, string outDir, string baseImageSrcDir)
        {
            Console.WriteLine($"Building: {profile.Name}");
            if (profile.GenerateStartupScript)
            {
                var p = profile.Partitions.Where(x => x.PartitionTypeGUID == _EFIGUID);
                if (p is null)
                {
                    var c = Console.ForegroundColor;
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    Console.WriteLine("EFI partition not found... ignoring GenerateStartupScript");
                    Console.ForegroundColor = c;
                }
                else
                {
                    foreach (var partition in p)
                    {
                        Console.WriteLine($"Generating startup script for: {partition.Label}");
                        GenerateEFIShellScript(partition.SourceDir, profile.Architecture, profile.Configuration);
                    }
                }
            }

            string imageSrc = Path.Combine(baseImageSrcDir, profile.Architecture, profile.Configuration);
            string outputDir = Path.Combine(outDir, profile.Architecture, profile.Configuration);

            if (!Directory.Exists(outputDir))
            {
                Directory.CreateDirectory(outputDir);
            }

            foreach (var format in formats)
            {
                if (string.Equals(format.Format, "VHD", StringComparison.CurrentCultureIgnoreCase))
                {
                    var outPath = Path.Combine(outputDir, $"{profile.Name}_{format.Format}_{format.Variant}.vhd");

                    if (File.Exists(outPath))
                    {
                        File.Delete(outPath);
                    }

                    long dirSrcSize = CalculateDirectorySize(imageSrc);
                    long diskSize = Math.Max(profile.ImageMinSizeBytes, dirSrcSize) + (Sizes.OneMiB * 8); // DiskSize + 16896 for (MBR + GPT Header + GPT Entries)

                    using FileStream vhdStream = File.Create(outPath);
                    vhdStream.Position = 0;

                    DiscUtils.Vhd.Disk vhd;
                    if (string.Equals(format.Variant, "Fixed", StringComparison.CurrentCultureIgnoreCase))
                    {
                        Console.WriteLine($"Generating Disc: {format.Format}:{format.Variant} to output: {outPath}");
                        vhd = DiscUtils.Vhd.Disk.InitializeFixed(vhdStream, Ownership.None, diskSize);
                    }
                    else if (string.Equals(format.Variant, "Dynamic", StringComparison.CurrentCultureIgnoreCase))
                    {
                        Console.WriteLine($"Generating Disc: {format.Format}:{format.Variant} to output: {outPath}");
                        vhd = DiscUtils.Vhd.Disk.InitializeDynamic(vhdStream, Ownership.None, diskSize);
                    }
                    else
                    {
                        vhdStream.Close();
                        File.Delete(outPath);
                        ConsoleColor c = Console.ForegroundColor;
                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                        Console.Error.WriteLine($"Format: {format.Format}:{format.Variant} is not supported");
                        Console.ForegroundColor = c;
                        return;
                    }
                    long size = BuildVirtualDisc(vhd, profile, format);
                    Console.WriteLine($"Capacity:{diskSize / Sizes.OneMiB}MB Used:{size / Sizes.OneMiB}MB Free:{diskSize - size / Sizes.OneMiB}MB");
                    vhdStream.Close();
                }
                else if (string.Equals(format.Format, "VHDX", StringComparison.CurrentCultureIgnoreCase))
                {
                    var outPath = Path.Combine(outputDir, $"{profile.Name}_{format.Format}_{format.Variant}.vhdx");

                    if (File.Exists(outPath))
                    {
                        File.Delete(outPath);
                    }

                    long dirSrcSize = CalculateDirectorySize(imageSrc);
                    long diskSize = Math.Max(profile.ImageMinSizeBytes, dirSrcSize) + (Sizes.OneMiB * 8); // DiskSize + 16896 for (MBR + GPT Header + GPT Entries)

                    using FileStream vhdStream = File.Create(outPath);
                    vhdStream.Position = 0;

                    DiscUtils.Vhdx.Disk vhdx;

                    if (string.Equals(format.Variant, "Fixed", StringComparison.CurrentCultureIgnoreCase))
                    {
                        vhdStream.Close();
                        File.Delete(outPath);
                        ConsoleColor c = Console.ForegroundColor;
                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                        Console.WriteLine("Fixed VHDX Support is Currently Disabled... Skipping");
                        Console.ForegroundColor = c;
                        //vhdx = DiscUtils.Vhdx.Disk.InitializeFixed(vhdStream, Ownership.None, diskSize);
                        return;
                    }
                    else if (string.Equals(format.Variant, "Dynamic", StringComparison.CurrentCultureIgnoreCase))
                    {
                        Console.WriteLine($"Generating Disc: {format.Format}:{format.Variant} to output: {outPath}");
                        vhdx = DiscUtils.Vhdx.Disk.InitializeDynamic(vhdStream, Ownership.None, diskSize);
                    }
                    else
                    {
                        vhdStream.Close();
                        File.Delete(outPath);
                        ConsoleColor c = Console.ForegroundColor;
                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                        Console.WriteLine($"Format: {format.Format}:{format.Variant} is not supported");
                        Console.ForegroundColor = c;
                        return;
                    }

                    long size = BuildVirtualDisc(vhdx, profile, format);

                    if (size > diskSize)
                    {
                        var c = Console.ForegroundColor;
                        Console.ForegroundColor = ConsoleColor.DarkYellow;
                        Console.WriteLine($"Size exceeds the disk capacity... {size} > {diskSize}");
                        Console.ForegroundColor = c;
                        vhdStream.Close();
                        File.Delete(outPath);
                        return;
                    }
                    vhdStream.Close();
                }
                else if (string.Equals(format.Format, "ISO", StringComparison.CurrentCultureIgnoreCase))
                {
                    string outPath;
                    if (format.Variant == null)
                    {
                        outPath = Path.Combine(outputDir, $"{profile.Name}_{format.Format}.iso");
                        Console.WriteLine($"Generating Disc: {format.Format} to output: {outPath}");
                    }
                    else
                    {
                        outPath = Path.Combine(outputDir, $"{profile.Name}_{format.Format}_{format.Variant}.iso");
                        Console.WriteLine($"Generating Disc: {format.Format}:{format.Variant} to output: {outPath}");
                    }


                    if (File.Exists(outPath))
                    {
                        File.Delete(outPath);
                    }

                    var discSrc = new DirectoryInfo(imageSrc);
                    long diskSize = discSrc.EnumerateFiles("*", SearchOption.AllDirectories).Sum(f => f.Length); //30MB
                    using FileStream isoStream = File.OpenWrite(outPath);
                    DiscUtils.Iso9660.CDBuilder iso = new();
                    iso.SetBootImage(isoStream, DiscUtils.Iso9660.BootDeviceEmulation.HardDisk, 0);
                    foreach (var partition in profile.Partitions)
                    {
                        iso.AddDirectory(partition.Label);
                    }
                    iso.Build(isoStream);
                }
                else
                {
                    ConsoleColor c = Console.ForegroundColor;
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    Console.WriteLine($"Format: {format.Format} is not supported");
                    Console.ForegroundColor = c;
                }
            }
        }

        public static void GenerateEFIShellScript(string srcPath, string architecture, string configuration)
        {
            var script = Path.Combine(srcPath, "startup.nsh");

            var bootfile = $"Boot_{architecture}_{configuration}.efi";

            if (File.Exists(script))
            {
                File.Delete(script);
            }

            using var sw = File.CreateText(script);
            sw.AutoFlush = true;
            sw.WriteLine("echo -off");
            sw.WriteLine("mode 80 25");
            sw.WriteLine("cls");

            for (int i = 0; i < 16; i++)
            {
                sw.WriteLine($"if exists fs{i}:\\efi\\boot\\{bootfile} then");
                sw.WriteLine($"fs{i}:");
                sw.WriteLine($"efi\\boot\\{bootfile}");
                sw.WriteLine("goto END");
                sw.WriteLine("endif");
            }

            sw.WriteLine("echo Unable to find Bootloader");
            sw.WriteLine(":END");
            sw.Close();
            sw.Dispose();
        }
    }
}

