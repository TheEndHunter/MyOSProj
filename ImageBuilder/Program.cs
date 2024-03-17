namespace ImageBuilder
{
    using System;
    using System.Collections.Frozen;
    using System.Diagnostics;

    internal class Program
    {
        private static readonly FrozenDictionary<string, string> bootfileMap = new Dictionary<string, string>()
                {
                    { "x86", "BOOTIA32.efi" },
                    { "x64", "BOOTX64.efi" },
                    { "arm", "BOOTARM.efi" },
                    { "arm64", "BOOTAA64.efi" }
                }.ToFrozenDictionary();

        static int Main(string[] args)
        {
            Console.Title = "Virtual Disk Builder Tool";

            string Dir = Path.GetFullPath(Directory.GetCurrentDirectory());

            string? architecture = null;
            string? configuration = null;
            string? SrcPath = null;
            string? DestPath = null;
            string? imgName = null;
            string? bootfile = null;

            int l = args.Length;
            if (l != 5)
            {
                Console.WriteLine("Invalid amount of arguments specified (min/max of 5 arguments). switching to manual entry");



                while (string.IsNullOrEmpty(architecture) && string.IsNullOrWhiteSpace(architecture))
                {
                    Console.Clear();
                    Console.WriteLine("Please enter the architecture being used (Select from: x86,x64,ARM,ARM64)");
                    architecture = Console.ReadLine()!.ToLower();

                    if (bootfileMap.TryGetValue(architecture, out string? bf))
                    {
                        bootfile = bf;
                    }
                    else
                    {
                        architecture = null;
                        bootfile = null;
                    }

                }

                while (string.IsNullOrEmpty(configuration) && string.IsNullOrWhiteSpace(configuration))
                {
                    Console.Clear();
                    Console.WriteLine("Please enter the configuration being used(e.g. Debug, Release)");
                    configuration = Console.ReadLine();
                }

                while (string.IsNullOrEmpty(SrcPath) && string.IsNullOrWhiteSpace(SrcPath))
                {
                    Console.Clear();
                    Console.WriteLine($"Current Dir: {Directory.GetCurrentDirectory()}");
                    Console.WriteLine("Please enter path of the to the src directory being used(e.g. C:\\Build\\Src)");
                    var test = Console.ReadLine();

                    test = Path.GetFullPath(test!);

                    if (Directory.Exists(test))
                    {
                        SrcPath = test;
                    }
                    else
                    {
                        Console.WriteLine("Invalid path specified");
                        Console.ReadKey();
                    }
                }

                while (string.IsNullOrEmpty(DestPath) && string.IsNullOrWhiteSpace(DestPath))
                {
                    Console.Clear();
                    Console.WriteLine($"Current Dir: {Directory.GetCurrentDirectory()}");
                    Console.WriteLine("Please enter path of the to the src directory being used(e.g. C:\\Build\\Dest)");
                    var test = Console.ReadLine();

                    test = Path.GetFullPath(test!);

                    if (Directory.Exists(test))
                    {
                        DestPath = test;
                    }
                    else
                    {
                        Console.WriteLine("Invalid path specified");
                        Console.ReadKey();
                    }
                }

                while (string.IsNullOrEmpty(imgName) && string.IsNullOrWhiteSpace(imgName))
                {
                    Console.Clear();
                    Console.WriteLine("Please enter the name to use for the file (e.g. 'virtualOS')(prefixes the Architecture and Configuration)");
                    imgName = Console.ReadLine()!.ToLower();

                    Console.Clear();
                }
            }
            else
            {
                architecture = args[0];
                configuration = args[1];
                SrcPath = Path.GetFullPath(Path.Combine(Dir, args[2]));
                DestPath = Path.GetFullPath(Path.Combine(Dir, args[3]));
                imgName = args[4];

                if (bootfileMap.TryGetValue(architecture, out string? bf))
                {
                    bootfile = bf;
                }
                else
                {
                    architecture = null;
                    bootfile = null;
                }
            }

            var dirs = Directory.EnumerateDirectories(SrcPath);

            List<Partition> _partitions = [];
            foreach (var dir in dirs)
            {
                DirectoryInfo info = new(dir);
                Partition p = new()
                {
                    SrcPath = info.FullName,
                    DestPath = null,
                    Size = Math.Max(500, info.CalculateSize())
                };

                if (string.Equals(info.Name, "EFI", StringComparison.CurrentCultureIgnoreCase))
                {
                    p.Label = "EFI";
                    p.Type = PartitionType.EFI;

                    var startupPath = Path.Combine(p.SrcPath, "startup.nsh");
                    if (File.Exists(startupPath))
                    {
                        File.Delete(startupPath);
                    }
                    using var f = File.CreateText(startupPath);
                    f.AutoFlush = true;
                    f.WriteLine("echo -off");
                    f.WriteLine("mode 80 25");
                    f.WriteLine("cls");

                    if (configuration == "Debug")
                    {
                        for (int i = 0; i < 16; i++)
                        {
                            f.WriteLine($"if exists fs{i}:\\efi\\boot\\{bootfile} then");
                            f.WriteLine($"fs{i}:");

                            f.WriteLine($"echo found Bootloader on fs{i}:");
                            f.WriteLine($"efi\\boot\\{bootfile}");
                            f.WriteLine("goto END");
                            f.WriteLine("endif");
                            f.Flush();
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 16; i++)
                        {
                            f.WriteLine($"if exists fs{i}:\\efi\\boot\\{bootfile} then");
                            f.WriteLine($"fs{i}:");
                            f.WriteLine($"efi\\boot\\{bootfile}");
                            f.WriteLine("goto END");
                            f.WriteLine("endif");

                            f.Flush();
                        }
                    }
                    f.WriteLine("echo Unable to find Bootloader");
                    f.WriteLine(":END");
                    f.Close();
                }
                else
                {
                    p.Label = info.Name.ToUpper();
                    p.Type = PartitionType.PRIMARY;
                }
                _partitions.Add(p);
            }

            /*
             *  We have all the folders linked to a Partition in the Partitions list
             *  We can start to build the ImageFile we Need:
             *  On Windows this is a .VHDX file
             *  On Linux this is a .IMG file
             *  
             *  to do this we need to create a new file with the size of the total size of all the partitions
             *  formatted as a GPT disk with the correct partition types and sizes for each partition,
             *  then we need to mount each partition and copy the files from the source directory to the mounted partition
             *  
             *  when finished we unmount, and close the file
             *  
             *  if there are any errors, we unmount(if needed) close the file, delete it and exit with an error code
             *  
             */

            DriveInfo[] drives = DriveInfo.GetDrives();

            var assigned = drives.Select(d => d.Name).ToArray();

            List<string> free =
            [
                "A:\\",
                "B:\\",
                "C:\\",
                "D:\\",
                "E:\\",
                "F:\\",
                "G:\\",
                "H:\\",
                "I:\\",
                "J:\\",
                "K:\\",
                "L:\\",
                "M:\\",
                "N:\\",
                "O:\\",
                "P:\\",
                "Q:\\",
                "R:\\",
                "S:\\",
                "T:\\",
                "U:\\",
                "V:\\",
                "W:\\",
                "X:\\",
                "Y:\\",
                "Z:\\"
            ];

            foreach (var drive in assigned)
            {
                free.Remove(drive);
            }

            var max = _partitions.Count;
            if (free.Count < max)
            {
                Console.WriteLine("Not Enough Free Drive letter to create partitions");
                Console.ReadLine();

            }

            for (int i = 0; i < max; i++)
            {
                var p = _partitions[i];
                var _key = free.First();
                p.DestPath = _key;
                _partitions[i] = p;
                free.Remove(_key);
            }


            string vhdxPath = Path.GetFullPath(Path.Combine(DestPath, $"{architecture}_{configuration}_{imgName}"));
            string vhdPath = vhdxPath.Replace(".vhdx", ".vhd");
            int res;

            if (File.Exists(vhdxPath))
            {
                try
                {
                    File.Delete(vhdxPath);
                }
                catch
                {
                    Console.WriteLine("Unable to delete existing vhdx file");
                    Console.ReadLine();
                    return -1;
                }
            }

            if (File.Exists(vhdPath))
            {
                try
                {
                    File.Delete(vhdPath);
                }
                catch
                {
                    Console.WriteLine("Unable to delete existing vhd file");
                    Console.ReadLine();
                    return -1;
                }
            }

            res = Create(DestPath, architecture!, configuration, vhdxPath, ref _partitions);
            if (res != 0)
            {
                return res;
            }

            res = Mount(DestPath, architecture!, configuration, vhdxPath, ref _partitions);

            foreach (Partition p in _partitions)
            {
                DirectoryInfo _src = new(p.SrcPath);
                DirectoryInfo _dest = new(p.DestPath!);
                _src.CopyDirectoriesAndFiles(_src!.Parent!.FullName, _dest);
            }

            res = Detach(DestPath, architecture, configuration, vhdxPath, ref _partitions);
            if (res != 0)
            {
                return res;
            }

            res = Convert(vhdxPath, vhdPath);
            if (res != 0)
            {
                return res;
            }

            return 0;
        }

        private static int Mount(string DestPath, string architecture, string configuration, string vhdxPath, ref List<Partition> _partitions)
        {
            try
            {
                string mScript = CreateMountScript(DestPath, architecture, configuration, vhdxPath, ref _partitions);

                ProcessStartInfo m = new()
                {
                    FileName = "Diskpart.exe",
                    WorkingDirectory = Environment.SystemDirectory,
                    Arguments = $"/s {mScript}",
                    WindowStyle = ProcessWindowStyle.Normal,
                    CreateNoWindow = true,
                    UseShellExecute = true,
                    ErrorDialog = true,
                };
                Process.Start(m)!.WaitForExit();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.ReadKey();
                return e.HResult;
            }
            return 0;
        }
        private static int Convert(string vhdxPath, string vhdPath)
        {
            try
            {
                //Convert - VHD - Path c:\test\child1vhdx.vhdx - DestinationPath c:\test\child1vhd.vhd - VHDType Differencing
                string cScript = CreateConvertScript(vhdxPath, vhdPath);

                ProcessStartInfo d = new()
                {
                    FileName = "powershell.exe",
                    Verb = "RunAs",
                    WorkingDirectory = Environment.SystemDirectory,
                    Arguments = $"{cScript}",
                    WindowStyle = ProcessWindowStyle.Normal,
                    CreateNoWindow = true,
                    UseShellExecute = true,
                    ErrorDialog = true,
                };
                Process.Start(d)!.WaitForExit();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.ReadKey();
                return e.HResult;
            }
            return 0;
        }
        private static int Detach(string DestPath, string architecture, string configuration, string vhdxPath, ref List<Partition> partitions)
        {
            try
            {
                string dtScript = CreateDetachScript(DestPath, architecture, configuration, vhdxPath, ref partitions);

                ProcessStartInfo d = new()
                {
                    FileName = "Diskpart.exe",
                    WorkingDirectory = Environment.SystemDirectory,
                    Arguments = $"/s {dtScript}",
                    WindowStyle = ProcessWindowStyle.Normal,
                    CreateNoWindow = true,
                    UseShellExecute = true,
                    ErrorDialog = true,
                };
                Process.Start(d)!.WaitForExit();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.ReadKey();
                return e.HResult;
            }
            return 0;
        }

        private static int Create(string DestPath, string architecture, string configuration, string vhdxPath, ref List<Partition> _partitions)
        {
            string atScript = CreateAttachScript(DestPath, architecture, configuration, vhdxPath, ref _partitions);
            try
            {
                ProcessStartInfo a = new()
                {
                    FileName = "Diskpart.exe",
                    WorkingDirectory = Environment.SystemDirectory,
                    Arguments = $"/s {atScript}",
                    WindowStyle = ProcessWindowStyle.Normal,
                    CreateNoWindow = true,
                    UseShellExecute = true,
                    ErrorDialog = true,
                };
                Process.Start(a!)!.WaitForExit();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                Console.ReadKey();
                return e.HResult;
            }
            return 0;
        }
        private static string CreateConvertScript(string vhdxPath, string vhdPath)
        {
            return $"Convert-VHD -Path {vhdxPath} -DestinationPath {vhdPath} -VHDType Fixed";
        }
        private static string CreateDetachScript(string destPath, string architecture, string configuration, string imgPath, ref List<Partition> partitions)
        {
            string diskPartDetach = Path.Combine(destPath, $"{architecture}_{configuration}_DetachScript.txt");

            if (File.Exists(diskPartDetach))
            {
                File.Delete(diskPartDetach);
            }

            {
                using var f = File.CreateText(diskPartDetach);
                f.WriteLine($"select vdisk file ={imgPath}");

                int index = 2;
                foreach (var part in partitions)
                {
                    f.WriteLine($"select partition {index}");
                    f.WriteLine($"remove letter = {part!.DestPath!.Replace(":\\", "")}");
                    index++;
                }

                f.WriteLine($"detach vdisk");
                f.Close();
            }

            return diskPartDetach;
        }

        private static string CreateMountScript(string destPath, string architecture, string configuration, string imgPath, ref List<Partition> partitions)
        {
            string diskPartMount = Path.Combine(destPath, $"{architecture}_{configuration}_MountScript.txt");

            if (File.Exists(diskPartMount))
            {
                File.Delete(diskPartMount);
            }

            {
                using var f = File.CreateText(diskPartMount);
                f.WriteLine($"select vdisk file ={imgPath}");
                f.WriteLine("attach vdisk");

                int index = 2;
                foreach (var part in partitions)
                {
                    f.WriteLine($"select partition {index}");
                    f.WriteLine($"assign letter = {part!.DestPath!.Replace(":\\", "")}");
                    index++;
                }
                f.Close();
            }
            return diskPartMount;
        }

        public static string CreateAttachScript(string dest, string arch, string conf, string imgPath, ref List<Partition> partitions)
        {
            string diskPartAttach = Path.Combine(dest, $"{arch}_{conf}_AttachScript.txt");

            if (File.Exists(diskPartAttach))
            {
                File.Delete(diskPartAttach);
            }

            {
                long size = partitions.Sum(x => x.Size) + 18; // Size of all partitions and 16MB for the GPT Header
                using var f = File.CreateText(diskPartAttach);

                f.WriteLine($"create vdisk file ={imgPath} maximum = {size}");
                f.WriteLine($"select vdisk file ={imgPath}");
                f.WriteLine("attach vdisk");
                f.WriteLine("convert gpt");
                foreach (var part in partitions)
                {
                    switch (part.Type)
                    {
                        case PartitionType.EFI:
                            f.WriteLine($"create partition efi size={part.Size}");
                            break;
                        default:
                            f.WriteLine($"create partition primary size={part.Size}");
                            break;
                    }
                    f.WriteLine($"format quick fs = fat32 label = \"{part.Label.ToUpper()}\"");
                }
                f.WriteLine("detach vdisk");
                f.Close();
            }
            return diskPartAttach;
        }
    }
}
