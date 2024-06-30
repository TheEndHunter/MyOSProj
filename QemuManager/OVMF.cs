namespace QemuRunner
{
    using Octokit;

    using System;
    using System.IO.Compression;
    using System.Threading.Tasks;

    internal static class OVMF
    {
        internal static async Task UpdateAsync(Settings config, string? sha1 = null)
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
            if (sha1 != null && currentsha != null)
            {
                if (sha1 == currentsha)
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
                    versionFile.WriteLine(currentsha);
                }
            });

            await DownloadTask;

            if (!DownloadTask.IsCompletedSuccessfully)
            {
                Console.WriteLine("Failed to download OVMF Repository");

                throw DownloadTask.Exception ?? new Exception("Failed to download OVMF Repository");
            }
        }
    }
}
