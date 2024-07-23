namespace ImageBuilder
{
    using DiscUtils;

    using ImageBuilder.Serialization;

    using Microsoft.Extensions.Configuration;

    using System;
    using System.Collections.Frozen;
    using System.Diagnostics;
    using System.Linq;

    public static partial class Program
    {

        private static readonly FrozenDictionary<string, string> bootfileMap = new Dictionary<string, string>()
                {
                    { "x86", "BOOTIA32.efi" },
                    { "x64", "BOOTX64.efi" },
                    { "arm", "BOOTARM.efi" },
                    { "arm64", "BOOTAA64.efi" }
                }.ToFrozenDictionary();

        static int Main(string[] Args)
        {
            Console.Title = "Virtual Disc Builder Tool";
            DiscUtils.Complete.SetupHelper.SetupComplete();
            ImageBuilderConfigs? configs = GenerateConfig();

            if (configs is null)
            {
                Console.WriteLine("Invalid Settings.json");
                return -1;
            }

            var configurations = SelectConfigurations(configs.Value);

            if (configurations is null || !configurations.Any())
            {
                Console.WriteLine("No Configurations Found");
                return -1;
            }

            var architectures = SelectArchitectures(configs.Value);

            if (architectures is null || !architectures.Any())
            {
                Console.WriteLine("No Architectures Found");
                return -1;
            }

            var profiles = SelectProfiles(configs.Value, configurations, architectures);

            if (profiles is null || !profiles.Any())
            {
                Console.WriteLine("No Profiles Selected");
                return -1;
            }

            var formats = SelectDiscFormatAndVariants(configs.Value);
            if (formats is null || !formats.Any())
            {
                Console.WriteLine("No Disc Formats Selected");
                return -1;
            }

            foreach (var profile in profiles)
            {
                VirtualDiskBuilder.BuildDiscImage(profile, formats, configs.Value.BaseOutputDir, configs.Value.BaseImageSourceDir);
            }

            return 0;
        }

        private static ImageBuilderConfigs? GenerateConfig()
        {
            ImageBuilderConfigs config;
            string Dir = Path.GetFullPath(Directory.GetCurrentDirectory());
            string SettingsPath = Path.Combine(Dir, "Settings.json");

            IEnumerable<string> sdts = DiscUtils.VirtualDiskManager.SupportedDiskTypes;

            if (File.Exists(SettingsPath))
            {
                ConfigurationBuilder builder = new();
                builder.SetBasePath(Dir);
                builder.AddJsonFile(SettingsPath, false);

                IConfigurationRoot root = builder.Build();

                config = new ImageBuilderConfigs(root);
            }
            else
            {
                throw new FileNotFoundException("Settings.json not found");
            }


            if (config.Configurations is null || config.Configurations.Count < 1)
            {
                Console.WriteLine($"No Configurations found!");
                return null;
            }

            if (config.Architectures is null || config.Architectures.Count < 1)
            {
                Console.WriteLine($"No Architectures found!");
                return null;
            }

            if (config.DiscFormats is null || config.DiscFormats.Count < 1)
            {
                Console.WriteLine($"No Disc Formats found!");
                return null;
            }

            if (config.ImageConfigs is null || config.ImageConfigs.Count < 1)
            {
                Console.WriteLine($"No Image Configs found!");
                return null;
            }

            List<DiscFormat> DiscFormats = [];
            foreach (var DiscFormat in config.DiscFormats)
            {
                if (string.IsNullOrEmpty(DiscFormat.Format) || string.IsNullOrWhiteSpace(DiscFormat.Format))
                {
                    Console.WriteLine("Invalid Disk Format: Format is null, empty or whitespace");
                    continue;
                }

                if (!sdts.Contains(DiscFormat.Format.ToUpperInvariant()))
                {
                    Console.WriteLine($"Invalid Disk Format: {DiscFormat.Format}, Not Supported");
                    continue;
                }

                var variants = DiscUtils.VirtualDisk.GetSupportedDiskVariants(DiscFormat.Format);

                if (variants is not null)
                {
                    if (string.IsNullOrEmpty(DiscFormat.Variant) || string.IsNullOrWhiteSpace(DiscFormat.Variant))
                    {
                        Console.WriteLine($"Invalid Disk Format: {DiscFormat.Format}, variant is null, empty or whitespace when required");
                        continue;
                    }

                    if (!variants.Select(x =>
                    {
                        return string.Equals(x, DiscFormat.Variant, StringComparison.InvariantCultureIgnoreCase);
                    }).Any())
                    {
                        Console.WriteLine($"Invalid Disk Format: {DiscFormat.Format}, Variant {DiscFormat.Variant} Not Supported");
                        continue;
                    }
                }
                DiscFormats.Add(DiscFormat);
            }

            if (DiscFormats.Count < 1)
            {
                return null;
            }

            /*validate configurations and architectures in ImageConfig, Removing Invalid Configurations*/

            List<ImageConfig> _imageConfigs = [];
            foreach (var imageConfig in config.ImageConfigs)
            {
                if (string.IsNullOrEmpty(imageConfig.Configuration) || string.IsNullOrWhiteSpace(imageConfig.Configuration) || !config.Configurations.Contains(imageConfig.Configuration))
                {
                    Console.WriteLine($"Invalid Configuration: Configuration is null, empty or whitespace... removing profile");
                    continue;
                }

                if (string.IsNullOrEmpty(imageConfig.Architecture) || string.IsNullOrWhiteSpace(imageConfig.Architecture) || !config.Architectures.Contains(imageConfig.Architecture))
                {
                    Console.WriteLine($"Invalid Architecture: Architecture is null, empty or whitespace... removing profile");
                    continue;
                }

                if (string.IsNullOrEmpty(imageConfig.Name) || string.IsNullOrWhiteSpace(imageConfig.Name))
                {
                    Console.WriteLine($"Invalid Image Profile Name: Image Profile Name is null, empty or whitespace... removing profile");
                    continue;
                }

                if (imageConfig.Partitions.Count < 1)
                {
                    continue;
                }

                int pCount = imageConfig.Partitions.Count;

                bool valid = true;
                foreach (var partition in imageConfig.Partitions)
                {

                    if (string.IsNullOrEmpty(partition.Label) || string.IsNullOrWhiteSpace(partition.Label))
                    {
                        Console.WriteLine($"Invalid Partition Label: Partition Label is null, empty or whitespace... removing profile");
                        valid = false;
                        break;
                    }

                    if (string.IsNullOrEmpty(partition.SourceDir) || string.IsNullOrWhiteSpace(partition.SourceDir))
                    {
                        Console.WriteLine($"Invalid Partition Source Directory: Partition Source Directory is null, empty or whitespace... removing profile");
                        valid = false;
                        break;
                    }

                    if (!Directory.Exists(partition.SourceDir))
                    {
                        Console.WriteLine($"Invalid Partition Source Directory: {partition.SourceDir} does not exist... removing profile");
                        valid = false;
                        break;
                    }

                    if (partition.MinSizeBytes < 1)
                    {
                        Console.WriteLine($"Invalid Partition Min Size: Partition Min Size is less than 1... removing profile");
                        valid = false;
                        break;
                    }

                    if (string.IsNullOrEmpty(partition.FileFormat) || string.IsNullOrWhiteSpace(partition.FileFormat))
                    {
                        Console.WriteLine($"Invalid Partition File Format: Partition File Format is null, empty or whitespace... removing profile");
                        valid = false;
                        break;
                    }
                }

                if (valid == false)
                {
                    continue;
                }

                _imageConfigs.Add(imageConfig);
            }

            if (_imageConfigs.Count < 1)
            {
                return null;
            }

            config.ImageConfigs.Clear();
            config.ImageConfigs.AddRange(_imageConfigs);

            config.Architectures = config.ImageConfigs.Select(x => x.Architecture).Distinct().ToList();
            config.Configurations = config.ImageConfigs.Select(x => x.Configuration).Distinct().ToList();

            return config;
        }

        public static IEnumerable<string>? SelectConfigurations(ImageBuilderConfigs config)
        {
            if (config.Configurations is null)
            {
                return null;
            }

            if (config.Configurations.Count > 1)
            {
                Checkbox c = new("Select Configuration(s)", options: config.Configurations, multiSelect: true);

                c.Show();
                IEnumerable<CheckboxReturn> selected = c.Select();
                Console.Clear();
                /*
                 *  Select all configurations from ImageConfigs where the Configuration matches the selectedDiscFormats Configuration(s)
                 */

                return from conf in config.Configurations
                       from sel in selected
                       where sel.Option == conf
                       orderby conf
                       select conf;
            }
            else
            {

                return config.Configurations;
            }
        }

        public static IEnumerable<string>? SelectArchitectures(ImageBuilderConfigs config)
        {
            if (config.Architectures is null)
            {
                return null;
            }

            if (config.Architectures.Count > 1)
            {
                Checkbox c = new(displayText: "Select Architecture(s)", options: config.Architectures, multiSelect: true);

                c.Show();
                IEnumerable<CheckboxReturn> selected = c.Select();
                Console.Clear();
                /*
                 *  Select all Architectures from ImageConfigs where the Architecture matches the selectedDiscFormats Architecture(s)
                 */

                return from arch in config.Architectures
                       from sel in selected
                       where sel.Option == arch
                       orderby arch
                       select arch;
            }
            else
            {
                return config.Architectures;
            }
        }

        public static IEnumerable<ImageConfig>? SelectProfiles(ImageBuilderConfigs config, IEnumerable<string> configurations, IEnumerable<string> architecures)
        {
            if (configurations is null || architecures is null)
            {
                return null;
            }

            var profiles = from profile in config.ImageConfigs
                           from conf in configurations
                           from arch in architecures
                           where profile.Configuration == conf && profile.Architecture == arch
                           select profile.Name;

            if (profiles is null)
            {
                return null;
            }

            if (profiles.Count() > 1)
            {
                Checkbox c = new(displayText: "Select Architecture(s)", options: profiles, multiSelect: true);

                c.Show();
                IEnumerable<CheckboxReturn> selected = c.Select();

                /*
                 *  Select all Architectures from ImageConfigs where the Architecture matches the selectedDiscFormats Architecture(s)
                 */

                return from profile in config.ImageConfigs
                       from sel in selected
                       where profile.Name == sel.Option
                       orderby profile.Name
                       select profile;
            }
            else
            {
                return config.ImageConfigs.Where(predicate: x =>
                {
                    return x.Name == profiles.ElementAt(0);
                }).OrderBy(x => x.Name);
            }
        }

        public static IEnumerable<DiscFormat>? SelectDiscFormatAndVariants(ImageBuilderConfigs config)
        {
            List<DiscFormat> discFormats = [];

            foreach (var disc in VirtualDiskManager.SupportedDiskFormats)
            {
                try
                {
                    ICollection<string>? variants = VirtualDisk.GetSupportedDiskVariants(disc);

                    if (variants is null)
                    {
                        discFormats.Add(new DiscFormat(disc));
                        continue;
                    }

                    foreach (var variant in variants)
                    {
                        discFormats.Add(new DiscFormat(disc, variant));
                    }
                }
                catch
                {
                    discFormats.Add(new DiscFormat(disc));
                }
            }

            if (discFormats is null)
            {
                return null;
            }

            if (discFormats.Count > 1)
            {
                IEnumerable<DiscFormat> distinctFormats = discFormats.DistinctBy(x => x.Format);

                Checkbox discFormatsCheckBox = new(displayText: "Select Disc Format(s)", options: distinctFormats.Select(x => x.Format), selected: config.DiscFormats.Select(x => x.Format), multiSelect: true);

                discFormatsCheckBox.Show();
                IEnumerable<CheckboxReturn> selectedDiscFormats = discFormatsCheckBox.Select();
                Console.Clear();

                /*
                 *  Select all Disc Formats select all selectedDiscFormats options
                 */

                var formats = from disc in distinctFormats
                              from sel in selectedDiscFormats
                              where string.Equals(disc.Format, sel.Option, StringComparison.CurrentCultureIgnoreCase)
                              orderby disc.Format
                              select disc;

                if (formats is null)
                {
                    return null;
                }
                /*
                 *  For each Disc Format, ask user for selection of input, in cases where there are no variants,
                 *  just select the format and continue itterating
                 */

                List<DiscFormat> results = [];
                foreach (var format in formats)
                {
                    string strFormat = format.Format;

                    if (format.Variant is null)
                    {
                        results.Add(format);
                        continue;
                    }
                    var f = format.Format;
                    var selectedVartiants = discFormats.Where(x => string.Equals(x.Format, f, StringComparison.CurrentCultureIgnoreCase))
                        .Select(x => x.Variant!) ?? throw new NotSupportedException("No Variants Selected");
                    if (selectedVartiants.Count() > 1)
                    {
                        Checkbox discVariantsCheckBox = new(displayText: $"Select Variant for {format.Format}", options: selectedVartiants, selected: config.DiscFormats.Where(x =>
                        {
                            return string.Equals(x.Format,f, StringComparison.CurrentCultureIgnoreCase);
                        }).Select(x => x.Variant!), multiSelect: true);
                        discVariantsCheckBox.Show();
                        IEnumerable<CheckboxReturn> selectedDiscVariants = discVariantsCheckBox.Select();
                        Console.Clear();

                        results.AddRange(from disc in discFormats
                                         from sel in selectedDiscVariants
                                         where string.Equals(disc.Variant, sel.Option, StringComparison.CurrentCultureIgnoreCase) && string.Equals(disc.Format, f, StringComparison.CurrentCultureIgnoreCase)
                                         orderby disc.Format
                                         select disc);
                    }
                    else
                    {
                        results.AddRange(from disc in discFormats
                                         from sel in selectedVartiants
                                         where string.Equals(disc.Variant,sel, StringComparison.CurrentCultureIgnoreCase) && string.Equals(disc.Format, f, StringComparison.CurrentCultureIgnoreCase)
                                         orderby disc.Format
                                         select disc);

                    }
                }

                return results.OrderBy(x => x.Format);
            }
            else
            {
                return discFormats.OrderBy(x => x.Format);
            }
        }
    }
}
