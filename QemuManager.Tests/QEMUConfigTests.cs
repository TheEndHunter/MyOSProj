using System;
using Xunit;
using QemuRunner;

namespace QemuManager.Tests
{
    public class QEMUConfigTests
    {
        [Fact]
        public void Blockdev_ToArg_And_Validate_FileDriver()
        {
            var b = new QEMUConfig.BlockdevConfig
            {
                Driver = "file",
                NodeName = "disk0",
                File_Filename = "/tmp/disk.qcow2",
                File_Aio = "threads",
                LazyRefcounts = true,
                RefcountCacheSize = 4194304,
            };

            var arg = b.ToArg();
            Assert.Contains("-blockdev", arg);
            Assert.Contains("driver=file", arg);
            Assert.Contains("file.filename=/tmp/disk.qcow2", arg);

            // Validate should not throw
            b.Validate();
        }

        [Fact]
        public void TypedNetdev_And_Chardev_ToArg_Validate()
        {
            var n = new QEMUConfig.NetdevTapConfig { Id = "n1", Ifname = "tap0", Script = false };
            var s = n.ToArg();
            Assert.Contains("-netdev tap", s);
            Assert.Contains("id=n1", s);

            var c = new QEMUConfig.ChardevPtyConfig { Id = "c1" };
            var cs = c.ToArg();
            Assert.Contains("-chardev pty", cs);
            Assert.Contains("id=c1", cs);
        }

        [Fact]
        public void Device_VirtioNet_ToArg_And_Validate()
        {
            var v = new QEMUConfig.VirtioNetDevice
            {
                Id = "net0",
                Netdev = "n1",
                Mac = "52:54:00:12:34:56",
                Vhost = true
            };

            var arg = v.ToArg();
            Assert.Contains("-device virtio-net-pci", arg);
            Assert.Contains("netdev=n1", arg);
            Assert.Contains("mac=52:54:00:12:34:56", arg);

            v.Validate();
        }

        [Fact]
        public void DeviceConfig_EnumMapping_And_ToArg()
        {
            var d = new QEMUConfig.DeviceConfig
            {
                Driver = null,
                DriverType = QEMUConfig.DeviceDriver.E1000,
                Id = "e0",
                Netdev = "n1",
                Mac = "52:54:98:76:54:32"
            };

            var arg = d.ToArg();
            Assert.Contains("-device e1000", arg);
            Assert.Contains("netdev=n1", arg);
            Assert.Contains("mac=52:54:98:76:54:32", arg);
            d.Validate();
        }
    }
}
