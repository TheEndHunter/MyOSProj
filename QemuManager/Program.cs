using Microsoft.Extensions.Configuration;

using Octokit;

using System.Diagnostics;
using System.IO.Compression;
using System.Text;

namespace QemuManager
{

    internal class Program
    {
        static string BuildDrives(string directory)
        {
            if (Directory.Exists(directory))
            {
                Console.WriteLine($"Building Qemu Drive Layout from Directory: {Path.GetFullPath(directory)}");

                StringBuilder sb = new();
                foreach (string folder in Directory.GetDirectories(directory))
                {
                    DirectoryInfo i = new(folder);
                    sb.Append(
                        $"-drive file=fat:fat-type=fat32:rw:\"{i.FullName}\",label=\"{i.Name.ToUpperInvariant()}\",format=vvfat "
                    );
                }
                return sb.ToString();
            }
            return string.Empty;
        }

        private static Process qemu;

        private static async Task UpdateOVMF(Settings config, string? sha1 = null, long? offset = null)
        {
            Console.WriteLine("Checking for Updates...");

            var Dir = Directory.GetCurrentDirectory();
            var extractPath = Path.Combine(Dir, "OVMF_Latest");
            var ovmfPath = Path.Combine(Dir, "OVMF");
            var zipPath = Path.Combine(Dir, "ovmf_repo.zip");

            var client = new GitHubClient(new ProductHeaderValue("QemuRunner"));
            var ovmf = config.OVMFConfiguration!.Value;
            var repo = await client.Repository.Get(ovmf.Author, ovmf.Repo);

            if (repo == null)
            {
                Console.WriteLine("Could not find Repository");
                return;
            }
            var branch = await client.Repository.Branch.Get(repo.Id, ovmf.Branch);
            if (branch == null)
            {
                Console.WriteLine("Could not find Branch");
                return;
            }

            var currentsha = branch.Commit.Sha;

            if (offset != null && sha1 != null && currentsha != null)
            {
                if (offset >= repo.UpdatedAt.ToUnixTimeMilliseconds() && sha1 == currentsha)
                {
                    Console.WriteLine("OVMF is up to date");
                    return;
                }
            }

            Console.WriteLine($"Downloading Latest Version: {repo.UpdatedAt} From {repo.FullName}...");

            if (File.Exists(zipPath))
            {
                File.Delete(zipPath);
            }

            var DownloadTask = client.Repository.Content.GetArchive(repo.Id, ArchiveFormat.Zipball).ContinueWith(zipTask =>
            {
                if (zipTask.IsCompletedSuccessfully)
                {
                    Console.WriteLine("Download Complete.");
                    if (Directory.Exists(ovmfPath))
                    {
                        Directory.Delete(ovmfPath, true);
                    }

                    if (Directory.Exists(extractPath))
                    {
                        Directory.Delete(extractPath, true);
                    }
                    Directory.CreateDirectory(extractPath);
                    System.IO.File.WriteAllBytes(zipPath, zipTask.Result);


                    Console.WriteLine("Extracting...");
                    ZipFile.ExtractToDirectory(zipPath, extractPath);
                    Console.WriteLine("Extracted...");

                    var dirs = Directory.GetDirectories(extractPath);

                    foreach (var d in dirs)
                    {
                        var t = Path.Combine(d, ovmf.OVMFBinPath);
                        if (Directory.Exists(t))
                        {
                            Directory.Move(t, ovmfPath);
                        }
                    }

                    Console.WriteLine("Writing Version.txt");
                    using var versionFile = File.CreateText(Path.Combine(ovmfPath, "Version.txt"));
                    versionFile.WriteLine(repo.UpdatedAt.ToUnixTimeSeconds());
                    versionFile.WriteLine(currentsha);

                    versionFile.Flush();
                    versionFile.Close();
                }
            });

            await DownloadTask;

            if (!DownloadTask.IsCompletedSuccessfully)
            {
                Console.WriteLine("Failed to download OVMF Repository");
                throw DownloadTask.Exception;
            }
        }

        static int Main(string[] args)
        {
            Settings config;
            string Dir = Path.GetFullPath(Directory.GetCurrentDirectory());
            string SettingsPath = Path.Combine(Dir, "Settings.json");

            if (File.Exists(SettingsPath))
            {
                IConfigurationBuilder builder = new ConfigurationBuilder();
                builder.SetBasePath(Dir);
                builder.AddJsonFile(SettingsPath);

                IConfigurationRoot root = builder.Build();

                config = new(root);
            }

            else
            {
                config = new Settings()
                {
                    Architectures = ["x86", "x64", "arm", "arm64"],
                    Configurations = ["Debug", "Release"],
                    OVMFConfiguration = null,
                };
            }

            Console.Title = "Qemu Virtual Machine Starter Tool";

            string? architecture = null;
            string? configuration = null;
            string? imagePath = null;
            string? machine;

            if (!Directory.Exists(Path.Combine(Dir, "OVMF")))
            {
                if (!config.OVMFConfiguration.HasValue)
                {
                    Console.WriteLine("Could not find Settings for OVMF");
                    Console.ReadKey();
                    return -1;
                }

                UpdateOVMF(config).Wait();
            }

            var verPath = Path.Combine(Dir, "OVMF", "Version.txt");

            if (File.Exists(verPath))
            {
                var data = File.ReadLines(verPath);
                if (data.Any())
                {
                    if (data.Count() > 1)
                    {
                        if (long.TryParse(data.ElementAt(0), out long unixtimeSeconds))
                        {
                            UpdateOVMF(config, data.ElementAt(1)!, unixtimeSeconds).Wait();
                        }
                    }
                    else
                    {
                        UpdateOVMF(config).Wait();
                    }
                }
                else
                {
                    UpdateOVMF(config).Wait();
                }
            }

            int l = args.Length;
            if (l != 3)
            {
                Console.WriteLine(
                    "Invalid amount of arguments specified (min/max of 3 arguments). switching to manual entry"
                );

                while (
                    string.IsNullOrEmpty(architecture) && string.IsNullOrWhiteSpace(architecture)
                )
                {
                    Console.Clear();
                    Console.WriteLine(
                        "Please enter the architecture being used (Select from: x86,x64,ARM,ARM64)"
                    );
                    architecture = Console.ReadLine()?.ToLower() ?? string.Empty;

                    if (config.Architectures.Contains(architecture))
                    {
                        break;
                    }
                }

                while (
                    string.IsNullOrEmpty(configuration) && string.IsNullOrWhiteSpace(configuration)
                )
                {
                    Console.Clear();
                    Console.WriteLine(
                        "Please enter the configuration being used(e.g. Debug, Release)"
                    );
                    configuration = Console.ReadLine();

                    if (config.Configurations.Contains(configuration))
                    {
                        break;
                    }
                }

                while (string.IsNullOrEmpty(imagePath) && string.IsNullOrWhiteSpace(imagePath))
                {
                    Console.Clear();
                    Console.WriteLine($"Current Dir: {Directory.GetCurrentDirectory()}");
                    Console.WriteLine(
                        "Please enter path to the Directory where the drives are specified(e.g. C:\\MyBuildDir\\"
                    );

                    string test = Console.ReadLine()!;

                    test = Path.GetFullPath(test);

                    if (Directory.Exists(test))
                    {
                        imagePath = test;
                    }
                    else
                    {
                        Console.WriteLine("Invalid path specified");
                        Console.ReadKey();
                    }
                }

                Console.Clear();
            }
            else
            {
                architecture = args[0];
                configuration = args[1];
                imagePath = Path.Combine(args[2]);
            }


            string firmwareCodePath = Path.Combine(
                Dir,
                "OVMF",
                architecture,
                configuration,
                "OVMF_CODE.fd"
            );
            string firmwareVarPath = Path.Combine(
                Dir,
                "OVMF",
                architecture,
                configuration,
                "OVMF_VARS.fd"
            );

            string filename;

            switch (architecture)
            {
                case "x86":
                    filename = "qemu-system-i386";
                    machine = " -machine q35 -accel tcg -display gtk";
                    break;
                case "x64":
                    filename = "qemu-system-x86_64";
                    machine = " -machine q35 -accel tcg -display gtk";
                    break;
                case "arm":
                    filename = "qemu-system-arm";
                    machine = " -machine virt -cpu cortex-a15 -accel tcg -display gtk";
                    break;
                case "arm64":
                    filename = "qemu-system-aarch64";
                    machine = " -machine virt -cpu cortex-a710 -accel tcg -display gtk";
                    break;
                default:
                    Console.WriteLine("Unknown Architecture");
                    Console.ReadKey();
                    return -1;
            }



            string exePath = string.Empty;
            string qemuPath = string.Empty;

            if (Environment.OSVersion.Platform == PlatformID.Win32NT)
            {
                filename += ".exe";
                var path = Environment.GetEnvironmentVariable("Path");

                string[] paths = path.Split(";");

                foreach (string s in paths)
                {
                    if (File.Exists(Path.Combine(s, filename)))
                    {
                        qemuPath = s;
                        exePath = Path.Combine(s, filename);
                        break;
                    }
                }
                if (exePath == string.Empty)
                {
                    Console.WriteLine("Could not find Qemu in Path");
                    Console.ReadKey();
                    return -1;
                }
            }
            else
            {
                exePath = filename;
            }

            string debug = string.Empty; //* TODO: Enable this in debug builds to allow live debug of the boot configuration. (configuration != "Debug") ? string.Empty : "-gdb tcp::4242 -S";

            Process.GetCurrentProcess().EnableRaisingEvents = true;
            qemu = new();
            qemu.StartInfo.FileName = exePath;
            qemu.StartInfo.WorkingDirectory = qemuPath;
            qemu.StartInfo.Arguments =
                $"""{machine} {debug} -accel tcg -m 2048M -drive if=pflash,format=raw,unit=0,file={firmwareCodePath},readonly=on -drive if=pflash,format=raw,unit=1,file={firmwareVarPath} {BuildDrives(imagePath)} -net none""";
            qemu.StartInfo.UseShellExecute = false;
            qemu.StartInfo.CreateNoWindow = false;
            qemu.StartInfo.WindowStyle = ProcessWindowStyle.Normal;
            qemu.EnableRaisingEvents = true;

            AppDomain.CurrentDomain.DomainUnload += DomainUnload;
            AppDomain.CurrentDomain.UnhandledException += UnhandledException;
            AppDomain.CurrentDomain.ProcessExit += Exit;

            if (qemu.Start())
            {
                if (configuration == "Debug")
                {
                    Console.WriteLine("Listening as gdb tcp on LocalHost:4242...");
                }
                qemu.WaitForExit();
                if (qemu.ExitCode != 0)
                {
                    Console.WriteLine("Qemu exited with error code: " + qemu.ExitCode);
                    Console.ReadKey(true);
                }

                return qemu.ExitCode;
            }
            else
            {
                if (qemu.ExitCode != 0)
                {
                    Console.WriteLine("Failed to start Process with error code: " + qemu.ExitCode);
                    Console.ReadKey(true);
                }
                return qemu.ExitCode;
            }
        }

        private static void UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            if (qemu != null)
            {
                if (qemu.HasExited)
                {
                    return;
                }
                qemu.Kill();
                qemu.WaitForExit();
                qemu.Dispose();
            }
        }

        private static void DomainUnload(object? sender, EventArgs e)
        {
            if (qemu != null)
            {
                if (qemu.HasExited)
                {
                    return;
                }
                qemu.Kill();
                qemu.WaitForExit();
                qemu.Dispose();
            }
        }

        private static void Exit(object? sender, EventArgs e)
        {
            if (qemu != null)
            {
                if (qemu.HasExited)
                {
                    return;
                }
                qemu.Kill();
                qemu.WaitForExit();
                qemu.Dispose();
            }
        }
    }
}

