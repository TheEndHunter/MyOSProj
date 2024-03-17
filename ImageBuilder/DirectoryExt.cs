namespace ImageBuilder
{
    using System;

    public static class DirectoryExt
    {
        public static void UpdateDirectoriesAndFiles(this DirectoryInfo source, string root, DirectoryInfo dest)
        {
            if (Directory.Exists(dest.FullName))
            {
                dest.Delete(true);
            }

            source.CopyDirectoriesAndFiles(root, dest);
        }

        public static void CopyDirectoriesAndFiles(this DirectoryInfo source, string root, DirectoryInfo dest)
        {
            string startPath = source.FullName;
            string relsrc = Path.GetRelativePath(startPath, root);
            string destDir = dest.FullName;

            var dirs = Directory.EnumerateDirectories(startPath).Select((x) =>
            {
                return Path.GetRelativePath(startPath, x);
            });

            foreach (var dir in dirs)
            {
                string destPath = Path.Combine(destDir, dir);
                Directory.CreateDirectory(destPath);
                Console.WriteLine($"Created Directory: {destPath}");
                new DirectoryInfo(Path.Combine(startPath, dir)).CopyDirectoriesAndFiles(startPath, new DirectoryInfo(destPath));
            }

            var files = Directory.EnumerateFiles(startPath).Select((x) =>
            {
                return Path.GetRelativePath(startPath, x);
            });

            foreach (var file in files)
            {
                string destPath = Path.Combine(destDir, file);
                var s = Path.Combine(startPath, file);
                File.Copy(s, destPath, true);
                Console.WriteLine($"Copied File: {s} to {destPath}");
            }
        }

        public static long CalculateSize(this DirectoryInfo d)
        {
            long size = 0;
            // Add file sizes.
            FileInfo[] fis = d.GetFiles();
            foreach (FileInfo fi in fis)
            {
                size += fi.Length;
            }
            // Add subdirectory sizes.
            DirectoryInfo[] dis = d.GetDirectories();
            foreach (DirectoryInfo di in dis)
            {
                size += di.CalculateSize();
            }
            /*
             * convert Size to MB round to nearest 1MB and return
             */
            return (long)Math.Ceiling(Math.Ceiling(size / 1024.0) / 1024.0);
        }
    }
}
