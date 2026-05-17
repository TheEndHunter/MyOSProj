namespace QemuRunner
{
    using System.Text;

    public class QEMUConfig
    {
        // When true, the manager will print the fully resolved QEMU command and not start the process.
        public bool DryRun { get; set; } = false;

        public string Architecture { get; set; } = string.Empty;
        public string Configuration { get; set; } = string.Empty;
        public string Name { get; set; } = string.Empty;
        // Note: free-form AdditionalArgs removed; use the strongly-typed properties
        // or Devices/NetworkOptions lists for repeatable complex options.

        // Strongly-typed subset of commonly used QEMU options. These are nullable
        // so they can be omitted in `Settings.json` when not required.

        // -machine <machine>[,prop=value...]
        public string? Machine { get; set; }

        // -cpu <model>[,prop=value...]
        public string? Cpu { get; set; }

        // -accel <accel> (common values: tcg, kvm, hvf, whpx)
        public AccelType? Accel { get; set; }

        public enum AccelType
        {
            Unknown = 0,
            Tcg,
            Kvm,
            Hvf,
            Whpx,
            Mshv,
            Nvmm
        }

        public class AudiodevConfig
        {
            public string? Id { get; set; }
            public string? Driver { get; set; }
            public string? Options { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Driver) || string.IsNullOrWhiteSpace(Id)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-audiodev "); sb.Append(Driver);
                sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Options)) sb.Append($",{Options}");
                return sb.ToString();
            }
        }

        public class ObjectConfig
        {
            public string? Type { get; set; }
            public string? Id { get; set; }
            public string? Options { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Type)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-object "); sb.Append(Type);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Options)) sb.Append($",{Options}");
                return sb.ToString();
            }
        }

        public class MemoryBackendConfig
        {
            public string? Id { get; set; }
            public string? Type { get; set; }
            public string? Options { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Type)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-object memory-backend-"); sb.Append(Type);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Options)) sb.Append($",{Options}");
                return sb.ToString();
            }
        }

        public class TpmObjectConfig : ObjectConfig
        {
            // tpm-tis or passthrough specifics can be added as properties
            public string? Mode { get; set; }
            public string? DevicePath { get; set; }

            public new string ToArg()
            {
                // Type should be set (e.g. "tpm-tis") via base.Type
                if (string.IsNullOrWhiteSpace(Type)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-object "); sb.Append(Type);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Mode)) sb.Append($",mode={Mode}");
                if (!string.IsNullOrWhiteSpace(DevicePath)) sb.Append($",path={DevicePath}");
                return sb.ToString();
            }
        }

        // Common typed devices
        public abstract class DeviceConfigBase
        {
            public string? Id { get; set; }
            public abstract string ToArg();
            public virtual void Validate() { }
        }

        public class E1000Device : DeviceConfigBase
        {
            [JsonConverters.TypeDiscriminator("E1000Device")]
            public string? Mac { get; set; }
            public string? Netdev { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device e1000");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Netdev)) sb.Append($",netdev={Netdev}");
                if (!string.IsNullOrWhiteSpace(Mac)) sb.Append($",mac={Mac}");
                return sb.ToString();
            }

            public override void Validate()
            {
                if (string.IsNullOrWhiteSpace(Netdev) && string.IsNullOrWhiteSpace(Mac)) throw new InvalidOperationException("E1000Device requires Netdev or Mac to be set.");
            }
        }

        public class Rtl8139Device : DeviceConfigBase
        {
            public string? Netdev { get; set; }
            public string? Mac { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device rtl8139");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Netdev)) sb.Append($",netdev={Netdev}");
                if (!string.IsNullOrWhiteSpace(Mac)) sb.Append($",mac={Mac}");
                return sb.ToString();
            }
        }

        public class VirtioScsiDevice : DeviceConfigBase
        {
            [QemuRunner.JsonConverters.TypeDiscriminator("VirtioScsiDevice")]
            public string? Bus { get; set; }
            public string? Addr { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-scsi-pci");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Bus)) sb.Append($",bus={Bus}");
                if (!string.IsNullOrWhiteSpace(Addr)) sb.Append($",addr={Addr}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("VirtioGpuDevice")]
        public class VirtioGpuDevice : DeviceConfigBase
        {
            public string? Display { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-vga");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Display)) sb.Append($",display={Display}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("VirtioRngDevice")]
        public class VirtioRngDevice : DeviceConfigBase
        {
            public string? RngBackend { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-rng-pci");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(RngBackend)) sb.Append($",rng={RngBackend}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("VirtioBalloonDevice")]
        public class VirtioBalloonDevice : DeviceConfigBase
        {
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-balloon");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("HdAudioDevice")]
        public class HdAudioDevice : DeviceConfigBase
        {
            public string? DriverName { get; set; }
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device hda");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(DriverName)) sb.Append($",driver={DriverName}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("UsbXhciDevice")]
        public class UsbXhciDevice : DeviceConfigBase
        {
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device qemu-xhci");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("VfioPciDevice")]
        public class VfioPciDevice : DeviceConfigBase
        {
            public string? Bdf { get; set; }
            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Bdf)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append($"-device vfio-pci,host={Bdf}");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
            public override void Validate()
            {
                if (string.IsNullOrWhiteSpace(Bdf)) throw new InvalidOperationException("VfioPciDevice requires Bdf (bus:dev.func) to be set.");
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("VirtioSerialDevice")]
        public class VirtioSerialDevice : DeviceConfigBase
        {
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtserialport");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("QxlDevice")]
        public class QxlDevice : DeviceConfigBase
        {
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device qxl");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("PcspkDevice")]
        public class PcspkDevice : DeviceConfigBase
        {
            public override string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device pcspk");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }
        }

        /// <summary>
        /// Common known device drivers. This is a non-exhaustive list of commonly used device strings mapped to enum values.
        /// The mapping helper accepts common QEMU device names (case-insensitive, hyphen variants) and returns the enum.
        /// </summary>
        public enum DeviceDriver
        {
            Unknown = 0,
            VirtioNetPci,
            VirtioBlkPci,
            E1000,
            Rtl8139,
            Ne2k_Pci,
            I82551,
            UsbMouse,
            UsbTablet,
            UsbKeyboard,
            IdeHd,
            SataDevice,
            VirtioConsole,
            VirtioRng,
            VirtioBalloon,
            VirtioSerial,
            VirtioScsi,
            VgaCirrus,
            Qxl,
            VmwareSVGA,
            Pcspk,
            Gusc,
            SoundBlaster16,
            Ensoniq,
            HdAudio,
            IsaSerial,
            PciIpmiKcs,
            IpmiBmcSim,
            TpmTis,
            Nvdimm,
            Loader,
            GuestLoader
            ,
            VirtioGPU,
            VirtioSnd,
            Sb16,
            Es1370,
            Ac97,
            Hda,
            UsbXhci,
            UsbOhci,
            UsbEhci,
            Uhci,
            QemuXhci,
            VfioPci,
            VirtioIommuPci,
            Virtio9pPci,
            VirtioSerialPci,
            VirtioBalloonDevice,
            I440fx,
            PIIX3,
            Q35
        }

        public static DeviceDriver DeviceDriverFromString(string? s)
        {
            if (string.IsNullOrWhiteSpace(s)) return DeviceDriver.Unknown;
            var norm = s.Trim().Replace('-', '_').Replace('.', '_');
            // Try direct parse ignoring case
            if (Enum.TryParse<DeviceDriver>(norm, true, out var d)) return d;
            // common mappings
            switch (s.Trim().ToLowerInvariant())
            {
                case "virtio-net-pci": return DeviceDriver.VirtioNetPci;
                case "virtio-net": return DeviceDriver.VirtioNetPci;
                case "virtio-blk-pci": return DeviceDriver.VirtioBlkPci;
                case "e1000": return DeviceDriver.E1000;
                case "rtl8139": return DeviceDriver.Rtl8139;
                case "ne2k_pci":
                case "ne2k-pci": return DeviceDriver.Ne2k_Pci;
                case "pcspk": return DeviceDriver.Pcspk;
                case "qxl": return DeviceDriver.Qxl;
                case "cirrus":
                case "cirrus-5446": return DeviceDriver.VgaCirrus;
                case "virtio-blk": return DeviceDriver.VirtioBlkPci;
                case "virtio-scsi": return DeviceDriver.VirtioScsi;
                default:
                    return DeviceDriver.Unknown;
            }
        }

        public static string DeviceDriverToString(DeviceDriver d)
        {
            return d switch
            {
                DeviceDriver.VirtioNetPci => "virtio-net-pci",
                DeviceDriver.VirtioBlkPci => "virtio-blk-pci",
                DeviceDriver.E1000 => "e1000",
                DeviceDriver.Rtl8139 => "rtl8139",
                DeviceDriver.Ne2k_Pci => "ne2k-pci",
                DeviceDriver.VgaCirrus => "cirrus",
                DeviceDriver.Qxl => "qxl",
                DeviceDriver.Pcspk => "pcspk",
                DeviceDriver.VirtioScsi => "virtio-scsi",
                _ => string.Empty,
            };
        }

        public class VirtioNetDevice
        {
            public string? Id { get; set; }
            public string? Netdev { get; set; }
            public string? Mac { get; set; }
            public bool? Vhost { get; set; }

            public string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-net-pci");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Netdev)) sb.Append($",netdev={Netdev}");
                if (!string.IsNullOrWhiteSpace(Mac)) sb.Append($",mac={Mac}");
                if (Vhost == true) sb.Append(",vhost=on");
                return sb.ToString();
            }

            public void Validate()
            {
                if (string.IsNullOrWhiteSpace(Netdev)) throw new InvalidOperationException("VirtioNetDevice.Netdev is required.");
            }
        }

        public class VirtioBlkDevice
        {
            public string? Id { get; set; }
            public string? DriveId { get; set; }
            public bool? WriteCache { get; set; }

            public string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-device virtio-blk-pci");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(DriveId)) sb.Append($",drive={DriveId}");
                if (WriteCache == true) sb.Append(",write-cache=on");
                return sb.ToString();
            }

            public void Validate()
            {
                if (string.IsNullOrWhiteSpace(DriveId)) throw new InvalidOperationException("VirtioBlkDevice.DriveId is required.");
            }
        }

        // Ensure device-to-driver mapping helper exists for backward compatibility
        public static DeviceDriver MapDriverStringToEnum(string? s) => DeviceDriverFromString(s);

        // -m <size> (e.g. 4096M, 4G)
        public string? Memory { get; set; }

        // -smp <n> or -smp cores=...,sockets=...,threads=...
        public int? SmpCores { get; set; }

        // -display <display> (e.g. gtk, sdl, none)
        public DisplayType? Display { get; set; }

        // Strongly-typed display backend options
        public enum DisplayType
        {
            Unknown = 0,
            Gtk,
            Sdl,
            None,
            Cocoa,
            Curses,
            Vnc,
            Spice,
            Dbus,
            EglHeadless
        }

        // -gdb <address> (e.g. tcp::4242)
        public string? Gdb { get; set; }

        // -vnc <display> or -vnc none and options
        public VncConfig? Vnc { get; set; }

        public class VncConfig
        {
            // if null -> not present; "none" -> present but disabled
            public string? Display { get; set; }
            public bool? Password { get; set; }
            public string? Websocket { get; set; }
            public string? X509Dir { get; set; }

            public string ToArgs()
            {
                if (Display == null) return string.Empty;
                StringBuilder sb = new();
                sb.Append("-vnc ");
                sb.Append(Display);
                if (Password == true) sb.Append(",password=on");
                if (!string.IsNullOrWhiteSpace(Websocket)) sb.Append($",websocket={Websocket}");
                if (!string.IsNullOrWhiteSpace(X509Dir)) sb.Append($",x509-dir={X509Dir}");
                return sb.ToString();
            }
        }

        // -S (do not start CPU at startup)
        public bool HaltOnStart { get; set; } = false;

        // -nographic
        public bool NoGraphic { get; set; } = false;

        // -daemonize
        public bool Daemonize { get; set; } = false;

        // -device and other repeatable options: keep lists for repeatable entries
        public List<string>? Devices { get; set; }

        /// <summary>
        /// Strongly-typed drive entries. Prefer using this instead of free-form -device/-drive strings
        /// in Settings.json. Each DriveConfig can render itself to a QEMU argument via ToArg().
        /// </summary>
        public List<DriveConfig>? Drives { get; set; }

        /// <summary>
        /// Strongly-typed blockdev entries for -blockdev usage.
        /// </summary>
        public List<BlockdevConfig>? Blockdevs { get; set; }

        /// <summary>
        /// Network backends (-netdev) entries.
        /// </summary>
        public List<NetdevConfig>? Netdevs { get; set; }

        /// <summary>
        /// Filesystem device definitions (-fsdev)
        /// </summary>
        public List<FsdevConfig>? Fsdevs { get; set; }

        /// <summary>
        /// Chardev device definitions (-chardev)
        /// </summary>
        public List<ChardevConfig>? Chardevs { get; set; }

        /// <summary>
        /// NUMA node definitions (-numa).
        /// </summary>
        public List<NumaNodeConfig>? NumaNodes { get; set; }

        /// <summary>
        /// Network backend typed entries (-netdev)
        /// </summary>
        public List<NetdevConfigBase>? TypedNetdevs { get; set; }

        /// <summary>
        /// Character device typed entries (-chardev)
        /// </summary>
        public List<ChardevConfigBase>? TypedChardevs { get; set; }

        /// <summary>
        /// Audio backends (-audiodev)
        /// </summary>
        public List<AudiodevConfig>? AudioDevs { get; set; }

        /// <summary>
        /// Generic -object entries
        /// </summary>
        public List<ObjectConfig>? Objects { get; set; }

        /// <summary>
        /// Memory backend objects (-object memory-backend-*)
        /// </summary>
        public List<MemoryBackendConfig>? MemoryBackends { get; set; }

        /// <summary>
        /// Typed device configs for -device handling
        /// </summary>
        public List<DeviceConfig>? DeviceConfigs { get; set; }
        /// <summary>
        /// Common virtio-net devices represented as strongly-typed entries.
        /// </summary>
        public List<VirtioNetDevice>? VirtioNetDevices { get; set; }

        /// <summary>
        /// Common virtio-blk devices represented as strongly-typed entries.
        /// </summary>
        public List<VirtioBlkDevice>? VirtioBlkDevices { get; set; }

        // Validate devices against a curated known device list.
        // Returns the list of devices that are unknown (so callers can log or decide to allow them).
        public IEnumerable<string> ValidateDevices()
        {
            if (Devices == null) yield break;
            foreach (var d in Devices)
            {
                if (string.IsNullOrWhiteSpace(d)) continue;
                if (!QEMUDevices.IsKnown(d)) yield return d;
            }
        }

        // -netdev / -nic / -net options (free-form entries to allow complex definitions)
        public List<string>? NetworkOptions { get; set; }
        public LLDBConfig? LLDBConfig { get; set; }
        // When true the runner will attempt to launch an external LLDB instance
        // to connect to QEMU's gdb stub. This must be used together with
        // AdditionalArgs that enable the gdb server (e.g. "-gdb tcp::4242 -S").
        // Default is false (do not auto-start LLDB).
        public bool EnableLLDB { get; set; } = false;

        // When true, the runner will read/write raw bytes to/from QEMU stdio and use a UTF8 decoder to handle multi-byte sequences.
        // When false, the runner will operate in line mode (reads text lines) which is simpler but may not handle binary data.
        public bool RawStdioMode { get; set; } = true;

        // Controls whether output is logged to a UTF-8 file.
        public bool EnableLogging { get; set; } = true;

        // Maximum number of log files to keep. If <= 0, rotation is disabled.
        public int LogMaxFiles { get; set; } = 5;

        // When true, ANSI/VT control sequences will be removed from output before writing to the log file.
        public bool StripAnsiSequences { get; set; } = false;

        // When true, write raw-byte hex dumps for each ReadAsync into the log file (debugging only). Off by default.
        public bool EnableRawLogging { get; set; } = false;

        // Serial target configuration
        // Options: File, Stdio, Pipes, Disabled (no -serial arg), Off (-serial disabled)
        public SerialTargetType SerialTarget { get; set; } = SerialTargetType.Stdio;

        public enum SerialTargetType
        {
            Unknown = 0,
            File,
            Stdio,
            Pipes,
            Disabled,
            Off
        }

        // When SerialTarget is "file", this template is used to generate file names.
        // Supported tokens: {timestamp}, {arch}, {config}
        // Example: "qemu_serial_{arch}_{config}_{timestamp}.log"
        public string SerialFileTemplate { get; set; } = "qemu_serial_{arch}_{config}_{timestamp}.log";

        // When SerialTarget is "pipes", this name is used to create a named pipe pair on Windows.
        // QEMU on Windows will use \\./pipe/<name> for bidirectional communication.
        public string SerialPipeName { get; set; } = "QemuManager";

        // When SerialTarget is "Stdio" and bridged via UDP, this is the local port used
        public int SerialUdpPort { get; set; } = 17000;

        // Build a command-line fragment from the strongly-typed properties and
        // the legacy AdditionalArgs string. Returns a single string suitable for
        // passing to QEMU.
        public string BuildArgumentsString()
        {
            var sb = new System.Text.StringBuilder();

            void AppendFlag(string flag, bool enabled)
            {
                if (enabled)
                {
                    sb.Append(flag);
                    sb.Append(' ');
                }
            }

            void AppendOption(string option, string? value)
            {
                if (string.IsNullOrWhiteSpace(value)) return;
                sb.Append(option);
                sb.Append(' ');
                // quote if necessary
                if (value.IndexOfAny(new char[] { ' ', '\t', '"' }) >= 0)
                {
                    var v = value.Replace("\"", "\\\"");
                    sb.Append('"'); sb.Append(v); sb.Append('"');
                }
                else
                {
                    sb.Append(value);
                }
                sb.Append(' ');
            }

            AppendOption("-machine", Machine);
            AppendOption("-cpu", Cpu);
            if (Accel.HasValue)
            {
                AppendOption("-accel", AccelToArg(Accel.Value));
            }
            AppendOption("-m", Memory);

            if (SmpCores.HasValue)
            {
                AppendOption("-smp", SmpCores.Value.ToString());
            }

            if (Display.HasValue)
            {
                AppendOption("-display", DisplayToArg(Display.Value));
            }
            AppendOption("-gdb", Gdb);
            AppendFlag("-S", HaltOnStart);
            AppendFlag("-nographic", NoGraphic);
            AppendFlag("-daemonize", Daemonize);

            // Serial handling
            switch (SerialTarget)
            {
                case SerialTargetType.Disabled:
                    // Disabled: do not add -serial at all
                    break;
                case SerialTargetType.Off:
                    // Explicitly disable serial device via QEMU argument
                    AppendOption("-serial", "disabled");
                    break;
                case SerialTargetType.File:
                    // generate filename from template
                    var fname = SerialFileTemplate;
                    fname = fname.Replace("{arch}", string.IsNullOrWhiteSpace(Architecture) ? "unknown" : Architecture);
                    fname = fname.Replace("{config}", string.IsNullOrWhiteSpace(Configuration) ? "unknown" : Configuration);
                    fname = fname.Replace("{timestamp}", System.DateTime.UtcNow.ToString("yyyyMMddHHmmss"));
                    AppendOption("-serial", "file:" + fname);
                    break;
                case SerialTargetType.Pipes:
                    if (!string.IsNullOrWhiteSpace(SerialPipeName))
                    {
                        AppendOption("-serial", "pipe:" + SerialPipeName);
                    }
                    break;
                case SerialTargetType.Stdio:
                    // Route stdio via UDP to local console bridge
                    AppendOption("-serial", $"udp:127.0.0.1:{SerialUdpPort}");
                    break;
                default:
                    break;
            }

            if (Devices != null)
            {
                foreach (var d in Devices.Where(x => !string.IsNullOrWhiteSpace(x)))
                {
                    sb.Append("-device ");
                    sb.Append(d.Trim());
                    sb.Append(' ');
                }
            }

            if (NetworkOptions != null)
            {
                foreach (var n in NetworkOptions.Where(x => !string.IsNullOrWhiteSpace(x)))
                {
                    sb.Append(n.Trim());
                    sb.Append(' ');
                }
            }

            // render typed blockdevs / drives / netdevs / fsdevs / chardevs
            if (Blockdevs != null)
            {
                foreach (var b in Blockdevs)
                {
                    var arg = b.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (Drives != null)
            {
                foreach (var d in Drives)
                {
                    var arg = d.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (Netdevs != null)
            {
                foreach (var n in Netdevs)
                {
                    var arg = n.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (TypedNetdevs != null)
            {
                foreach (var n in TypedNetdevs)
                {
                    if (n == null) continue;
                    n.Validate();
                    var arg = n.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (Fsdevs != null)
            {
                foreach (var f in Fsdevs)
                {
                    var arg = f.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (Chardevs != null)
            {
                foreach (var c in Chardevs)
                {
                    var arg = c.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (TypedChardevs != null)
            {
                foreach (var c in TypedChardevs)
                {
                    if (c == null) continue;
                    c.Validate();
                    var arg = c.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (DeviceConfigs != null)
            {
                foreach (var d in DeviceConfigs)
                {
                    var arg = d.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (VirtioNetDevices != null)
            {
                foreach (var v in VirtioNetDevices)
                {
                    var arg = v.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (VirtioBlkDevices != null)
            {
                foreach (var v in VirtioBlkDevices)
                {
                    var arg = v.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (AudioDevs != null)
            {
                foreach (var a in AudioDevs)
                {
                    if (a == null) continue;
                    var arg = a.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (Objects != null)
            {
                foreach (var o in Objects)
                {
                    if (o == null) continue;
                    var arg = o.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            if (MemoryBackends != null)
            {
                foreach (var m in MemoryBackends)
                {
                    if (m == null) continue;
                    var arg = m.ToArg();
                    if (!string.IsNullOrWhiteSpace(arg)) { sb.Append(arg); sb.Append(' '); }
                }
            }

            string AccelToArg(AccelType a)
            {
                return a switch
                {
                    AccelType.Tcg => "tcg",
                    AccelType.Kvm => "kvm",
                    AccelType.Hvf => "hvf",
                    AccelType.Whpx => "whpx",
                    AccelType.Mshv => "mshv",
                    AccelType.Nvmm => "nvmm",
                    _ => ""
                };
            }

            string DisplayToArg(DisplayType dt)
            {
                return dt switch
                {
                    DisplayType.Gtk => "gtk",
                    DisplayType.Sdl => "sdl",
                    DisplayType.None => "none",
                    DisplayType.Cocoa => "cocoa",
                    DisplayType.Curses => "curses",
                    DisplayType.Vnc => "vnc",
                    DisplayType.Spice => "spice",
                    DisplayType.Dbus => "dbus",
                    DisplayType.EglHeadless => "egl-headless",
                    _ => ""
                };
            }

            // AdditionalArgs removed; any non-modeled options should be placed in
            // Devices or NetworkOptions lists.

            return sb.ToString().Trim();
        }

        /// <summary>
        /// Validate config for required parameters and cross-field requirements.
        /// Throws InvalidOperationException when validation fails.
        /// </summary>
        public void Validate()
        {
            // Name, Architecture, Configuration are required at higher level but double-check
            if (string.IsNullOrWhiteSpace(Name)) throw new InvalidOperationException("QEMUConfig.Name is required.");
            if (string.IsNullOrWhiteSpace(Architecture)) throw new InvalidOperationException("QEMUConfig.Architecture is required.");
            if (string.IsNullOrWhiteSpace(Configuration)) throw new InvalidOperationException("QEMUConfig.Configuration is required.");

            // If VNC is configured, Display must be set (or Vnc.Display set)
            if (Vnc != null)
            {
                if (Display == null && string.IsNullOrWhiteSpace(Vnc.Display))
                {
                    throw new InvalidOperationException("Vnc is configured but neither Display nor Vnc.Display is set.");
                }
            }

            // Validate drives and blockdevs
            if (Drives != null)
            {
                foreach (var d in Drives)
                {
                    if (d == null) throw new InvalidOperationException("Drives contains null entry.");
                    d.Validate();
                }
            }

            if (Blockdevs != null)
            {
                foreach (var b in Blockdevs)
                {
                    if (b == null) throw new InvalidOperationException("Blockdevs contains null entry.");
                    b.Validate();
                }
            }

            if (DeviceConfigs != null)
            {
                foreach (var dc in DeviceConfigs)
                {
                    if (dc == null) throw new InvalidOperationException("DeviceConfigs contains null entry.");
                    dc.Validate();
                }
            }

            if (VirtioNetDevices != null)
            {
                foreach (var vn in VirtioNetDevices)
                {
                    if (vn == null) throw new InvalidOperationException("VirtioNetDevices contains null entry.");
                    vn.Validate();
                }
            }

            if (VirtioBlkDevices != null)
            {
                foreach (var vb in VirtioBlkDevices)
                {
                    if (vb == null) throw new InvalidOperationException("VirtioBlkDevices contains null entry.");
                    vb.Validate();
                }
            }
        }

        #region Small typed option classes

        public class DriveConfig
        {
            public string? File { get; set; }
            public string? If { get; set; }
            public string? Format { get; set; }
            public string? Id { get; set; }
            public string? Media { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(File) && string.IsNullOrWhiteSpace(Id)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-drive ");
                if (!string.IsNullOrWhiteSpace(File))
                {
                    var fileVal = File;
                    if (fileVal.IndexOfAny(new char[] { ' ', '\t', '"' }) >= 0)
                    {
                        fileVal = fileVal.Replace("\"", "\\\"");
                        sb.Append($"file=\"{fileVal}\"");
                    }
                    else
                    {
                        sb.Append($"file={fileVal}");
                    }
                }
                else if (!string.IsNullOrWhiteSpace(Id))
                {
                    sb.Append($"id={Id}");
                }
                if (!string.IsNullOrWhiteSpace(If)) sb.Append($",if={If}");
                if (!string.IsNullOrWhiteSpace(Format)) sb.Append($",format={Format}");
                if (!string.IsNullOrWhiteSpace(Media)) sb.Append($",media={Media}");
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                return sb.ToString();
            }

            public void Validate()
            {
                if (string.IsNullOrWhiteSpace(File) && string.IsNullOrWhiteSpace(Id)) throw new InvalidOperationException("DriveConfig requires either File or Id to be set.");
            }
        }

        public class BlockdevConfig
        {
            // Common blockdev options (expanded subset)
            public string? Driver { get; set; }
            public string? NodeName { get; set; }
            public string? File_Filename { get; set; }
            public string? File_Aio { get; set; }
            public string? File_Locking { get; set; }
            /// <summary>
            /// Inline file node (nested): allows specifying file.driver=...,file.filename=... inline instead of file.filename only.
            /// </summary>
            public BlockdevFileInline? FileInline { get; set; }
            // Typed qcow2/format related options
            public bool? LazyRefcounts { get; set; }
            /// <summary>
            /// Cache size for the format layer (e.g. for qcow2 cache-size) in bytes. Use string suffixes in JSON if desired (handled as raw string here).
            /// </summary>
            public string? Format_CacheSize { get; set; }
            public bool? ReadOnly { get; set; }
            // qcow2 specific options
            public string? BackingFile { get; set; }
            public long? RefcountCacheSize { get; set; }
            public long? L2CacheSize { get; set; }
            public bool? PassDiscardRequest { get; set; }
            public bool? PassDiscardSnapshot { get; set; }
            public bool? DiscardNoUnref { get; set; }
            public string? BackingFormat { get; set; }
            /// <summary>
            /// Optional cluster size in bytes for qcow2 (if supported).
            /// </summary>
            public int? ClusterSize { get; set; }
            /// <summary>
            /// Interval in seconds for cache cleaning
            /// </summary>
            public int? CacheCleanInterval { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Driver)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-blockdev driver="); sb.Append(Driver);
                if (!string.IsNullOrWhiteSpace(NodeName)) sb.Append($",node-name={NodeName}");
                if (FileInline != null)
                {
                    // file.driver=...,file.filename=...
                    if (!string.IsNullOrWhiteSpace(FileInline.Driver)) sb.Append($",file.driver={FileInline.Driver}");
                    if (!string.IsNullOrWhiteSpace(FileInline.Filename)) sb.Append($",file.filename={FileInline.Filename}");
                    if (!string.IsNullOrWhiteSpace(FileInline.Aio)) sb.Append($",file.aio={FileInline.Aio}");
                    if (!string.IsNullOrWhiteSpace(FileInline.Locking)) sb.Append($",file.locking={FileInline.Locking}");
                }
                else
                {
                    if (!string.IsNullOrWhiteSpace(File_Filename)) sb.Append($",file.filename={File_Filename}");
                    if (!string.IsNullOrWhiteSpace(File_Aio)) sb.Append($",file.aio={File_Aio}");
                    if (!string.IsNullOrWhiteSpace(File_Locking)) sb.Append($",file.locking={File_Locking}");
                }
                if (LazyRefcounts.HasValue) sb.Append($",lazy-refcounts={(LazyRefcounts.Value ? "on" : "off")} ");
                else sb.Append(' ');
                if (RefcountCacheSize.HasValue) sb.Append($",refcount-cache-size={RefcountCacheSize.Value}");
                if (L2CacheSize.HasValue) sb.Append($",l2-cache-size={L2CacheSize.Value}");
                if (!string.IsNullOrWhiteSpace(Format_CacheSize)) sb.Append($",cache-size={Format_CacheSize}");
                if (CacheCleanInterval.HasValue) sb.Append($",cache-clean-interval={CacheCleanInterval.Value}");
                if (ClusterSize.HasValue) sb.Append($",cluster-size={ClusterSize.Value}");
                if (PassDiscardRequest.HasValue) sb.Append($",pass-discard-request={(PassDiscardRequest.Value ? "on" : "off")}");
                if (PassDiscardSnapshot.HasValue) sb.Append($",pass-discard-snapshot={(PassDiscardSnapshot.Value ? "on" : "off")}");
                if (DiscardNoUnref.HasValue) sb.Append($",discard-no-unref={(DiscardNoUnref.Value ? "on" : "off")}");
                if (ReadOnly.HasValue) sb.Append($",read-only={(ReadOnly.Value ? "on" : "off")}");
                return sb.ToString();
            }

            public void Validate()
            {
                if (string.IsNullOrWhiteSpace(Driver)) throw new InvalidOperationException("BlockdevConfig.Driver is required.");
                // file.filename is recommended for file-backed drivers
                if (string.Equals(Driver, "file", StringComparison.OrdinalIgnoreCase))
                {
                    if (FileInline == null && string.IsNullOrWhiteSpace(File_Filename)) throw new InvalidOperationException("BlockdevConfig.File_Filename is required when driver=file.");
                    if (FileInline != null && string.IsNullOrWhiteSpace(FileInline.Filename)) throw new InvalidOperationException("BlockdevConfig.FileInline.Filename is required when driver=file and FileInline is used.");
                }
                // qcow2 specific validations
                if (string.Equals(Driver, "qcow2", StringComparison.OrdinalIgnoreCase))
                {
                    // if refcount cache size provided, must be positive
                    if (RefcountCacheSize.HasValue && RefcountCacheSize.Value < 0) throw new InvalidOperationException("BlockdevConfig.RefcountCacheSize must be non-negative.");
                    if (L2CacheSize.HasValue && L2CacheSize.Value < 0) throw new InvalidOperationException("BlockdevConfig.L2CacheSize must be non-negative.");
                }
            }
        }

        public class BlockdevFileInline
        {
            public string? Driver { get; set; }
            public string? Filename { get; set; }
            public string? Aio { get; set; }
            public string? Locking { get; set; }
            public string? Protocol { get; set; }
            public string? Url { get; set; }
        }

        /// <summary>
        /// Device mapping for -device arguments. This supports common properties like driver name, id and simple props.
        /// Example: -device virtio-net-pci,netdev=n1,mac=52:54:00:12:34:56
        /// </summary>
        public class DeviceConfig
        {
            public string? Driver { get; set; }
            /// <summary>
            /// Typed driver enum if known (helps with case-insensitive handling and validation)
            /// </summary>
            public DeviceDriver DriverType { get; set; } = DeviceDriver.Unknown;
            public string? Id { get; set; }

            public string? Mac { get; set; }
            public string? Netdev { get; set; }
            public string? Bus { get; set; }
            public string? Addr { get; set; }

            public string ToArg()
            {
                var driver = !string.IsNullOrWhiteSpace(Driver) ? Driver : DeviceDriverToString(DriverType);
                if (string.IsNullOrWhiteSpace(driver)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-device "); sb.Append(driver);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Netdev)) sb.Append($",netdev={Netdev}");
                if (!string.IsNullOrWhiteSpace(Mac)) sb.Append($",mac={Mac}");
                if (!string.IsNullOrWhiteSpace(Bus)) sb.Append($",bus={Bus}");
                if (!string.IsNullOrWhiteSpace(Addr)) sb.Append($",addr={Addr}");
                return sb.ToString();
            }

            public void Validate()
            {
                if (string.IsNullOrWhiteSpace(Driver)) throw new InvalidOperationException("DeviceConfig.Driver is required.");
            }
        }

        public class NetdevConfig : NetdevConfigBase
        {
            public string? Type { get; set; }
            public string? Options { get; set; }

            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Type)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-netdev ");
                sb.Append(Type);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Options)) sb.Append($",{Options}");
                return sb.ToString();
            }
        }

        // Typed netdev base and common implementations
        public abstract class NetdevConfigBase
        {
            public string? Id { get; set; }
            public abstract string ToArg();
            public virtual void Validate()
            {
                if (string.IsNullOrWhiteSpace(Id)) throw new InvalidOperationException("Netdev Id is required.");
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("NetdevTapConfig")]
        public class NetdevTapConfig : NetdevConfigBase
        {
            public string? Ifname { get; set; }
            public bool? Script { get; set; }
            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Id)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-netdev tap");
                sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Ifname)) sb.Append($",ifname={Ifname}");
                if (Script.HasValue && Script.Value == false) sb.Append(",script=no");
                return sb.ToString();
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("NetdevUserConfig")]
        public class NetdevUserConfig : NetdevConfigBase
        {
            public string? Hostfwd { get; set; }
            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Id)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-netdev user");
                sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Hostfwd)) sb.Append($",hostfwd={Hostfwd}");
                return sb.ToString();
            }
        }

        public abstract class ChardevConfigBase
        {
            public string? Id { get; set; }
            public abstract string ToArg();
            public virtual void Validate()
            {
                if (string.IsNullOrWhiteSpace(Id)) throw new InvalidOperationException("Chardev Id is required.");
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("ChardevPtyConfig")]
        public class ChardevPtyConfig : ChardevConfigBase
        {
            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Id)) return string.Empty;
                return $"-chardev pty,id={Id}";
            }
        }

        [QemuRunner.JsonConverters.TypeDiscriminatorAttribute("ChardevSocketConfig")]
        public class ChardevSocketConfig : ChardevConfigBase
        {
            public string? Path { get; set; }
            public bool? Server { get; set; }
            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Id)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append($"-chardev socket,id={Id}");
                if (!string.IsNullOrWhiteSpace(Path)) sb.Append($",path={Path}");
                if (Server.HasValue && Server.Value) sb.Append(",server=on");
                return sb.ToString();
            }
        }

        public class FsdevConfig
        {
            public string? Driver { get; set; }
            public string? Id { get; set; }
            public string? Path { get; set; }
            public string? SecurityModel { get; set; }

            public string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Driver)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-fsdev "); sb.Append(Driver);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Path)) sb.Append($",path={Path}");
                if (!string.IsNullOrWhiteSpace(SecurityModel)) sb.Append($",security_model={SecurityModel}");
                return sb.ToString();
            }
        }

        public class ChardevConfig : ChardevConfigBase
        {
            public string? Backend { get; set; }
            public string? Options { get; set; }

            public override string ToArg()
            {
                if (string.IsNullOrWhiteSpace(Backend)) return string.Empty;
                var sb = new StringBuilder();
                sb.Append("-chardev "); sb.Append(Backend);
                if (!string.IsNullOrWhiteSpace(Id)) sb.Append($",id={Id}");
                if (!string.IsNullOrWhiteSpace(Options)) sb.Append($",{Options}");
                return sb.ToString();
            }
        }

        public class NumaNodeConfig
        {
            public int? NodeId { get; set; }
            public string? Mem { get; set; }
            public string? Cpus { get; set; }

            public string ToArg()
            {
                var sb = new StringBuilder();
                sb.Append("-numa node");
                if (NodeId.HasValue) sb.Append($",nodeid={NodeId.Value}");
                if (!string.IsNullOrWhiteSpace(Mem)) sb.Append($",mem={Mem}");
                if (!string.IsNullOrWhiteSpace(Cpus)) sb.Append($",cpus={Cpus}");
                return sb.ToString();
            }
        }

        #endregion
    }
}

