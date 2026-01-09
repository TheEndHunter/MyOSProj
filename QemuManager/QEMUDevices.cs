// This file contains a curated list of common QEMU device names.
// The list is intentionally conservative and can be extended by
// parsing the local QEMU documentation HTML file and adding new
// values here. Each entry corresponds to a QEMU "-device" driver
// name (for example: "e1000", "virtio-net-pci", "usb-tablet").
namespace QemuRunner
{
    public static class QEMUDevices
    {
        // A non-exhaustive list of commonly used QEMU device ids and drivers.
        // Keep the list alphabetized for easier maintenance.
        public static readonly HashSet<string> KnownDeviceNames = new(StringComparer.OrdinalIgnoreCase)
        {
            // Network devices
            "e1000",
            "e1000-82545em",
            "i82559a",
            "rtl8139",
            "virtio-net-pci",

            // Block devices / controllers
            "ide-hd",
            "virtio-blk-pci",
            "scsi-hd",

            // USB devices
            "usb-tablet",
            "usb-mouse",
            "usb-kbd",

            // VGA / display
            "cirrus",
            "std",
            "qxl",
            "vmware",
            "virtio-vga",

            // Sound
            "sb16",
            "ac97",
            "hda",

            // Other common devices
            "virtio-serial",
            "virtconsole",
            "virtio-rng",
            "virtio-balloon",
            "usb-ehci",
            "usb-uhci",

            // TPM and IPMI
            "tpm-tis",
            "ipmi-bmc-sim",

            // PCI helpers
            "vfio-pci",

            // Paravirtual
            "virtio-9p-pci",
        };

        public static bool IsKnown(string deviceSpec)
        {
            if (string.IsNullOrWhiteSpace(deviceSpec)) return false;
            // Device spec can include commas and properties: "driver,prop=val".
            var driver = deviceSpec.Split(',')[0].Trim();
            return KnownDeviceNames.Contains(driver);
        }
    }
}
