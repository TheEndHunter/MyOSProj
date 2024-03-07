# Operating System Project

## Description
	A Custom Multi-Platform OS Built From Scratch.
	This project is a to be used as a learning process for how modern computers work, and how the hardware and software interact with respect, showing how memory is managed,
	how the CPU interacts with the hardware, and how the OS interacts with the hardware and software.

	This is a learning project to learn more about OS Development and how to build a UEFI Compliant Bootloader for an OS.
	This project is written using C++ and Assembly. The tools are built using C#.

	another strech goal will be to have C# support for the OS, allowing programs to be written in C# and run on the OS natively.

### Project Structure

#### Features
	P=Planned, IP=In Progress, C=Completed,N=Not Planned, ?=Suggested
	NOTE: Not In Order Of Implementation

	[P] ACPI Support (Kernel)
	[P] Audio Support (Kernel)
	[I] File System Support(Bootloader)
	[P] Debugging support (Kernel & Bootloader)
	[P] PCI Support (Kernel)
	[P] Multihreading Support (Kernel)
	[P] Driver System (Kernel)
	[P] Virutal File System Support (Kernel)
	[P] Ext3 Support (Kernel)
	[P] Ext4 Support (Kernel)
	[P] FAT32 Support (Kernel)
	[?] NTFS Support (Kernel)
	[P] Shell Support (Kernel)
	[P] Shell Commands (Kernel)
	[P] Serial Console (Kernel)
	[P] PS/2 Support (Kernel)
	[P] SATA Support (Kernel)
	[P] SCSI Support (Kernel)
	[P] USB Support (Kernel)
	[P] Networking & Communications Support(Bluetooth, Wifi, Ethernet)
	[P] Software Rendering System (Kernel)
	[P] Windowing System (Kernel)
	[P] Hardware Accelerated Graphics (Kernel)

#### Bootloader
	this is the first stage of the OS, it is responsible for setting up the Enviroment for the kernel to run, it will be responsible for setting up the GDT, IDT, and other tables, and then
	loadin the kernel into memory and calling into it's entry point. this may change as the project progresses, but this is the initial plan.

#### Kernel
	the kernel for the os, it will be responsible for managing the hardware, and providing a stable interface for the user to interact with the hardware and software.

#### QemuRunner
	This tool is what starts qemu with the correct arguments to run the OS from the build directory.

#### ImageBuilder
	The ImageBuilder is a tool to build an OS image for use with virtual machines or as a image to burn to media(syuch as a USB Stick)


## Platforms Supported
	[x] x86
	[~] ARM (UNTESTED, NEEDS Scripts and Tools, as QuemuRunner and ImageBuilder don't support ARM)
	[x] x64
	[x] ARM64 (UNTESTED)

## Building
	Building is done via the Build menu in visual studios, it's setup to build QemuRunner, which has manually defined dependanices
	on the other projects, pressing run will build the dependant projects first, then build QemuRunner and start it with the correct arguments to start the OS.

## Build Image
	Building the image is now an optional step, as the image is no longer required for Qemu to run the OS.

	if building an image, the builder requires the following arguments:
		architecture - (x86, x64, arm, arm64)
		configuration - (debug, release)
		SrcPath - (The path to the build directory, each sub directory of this directory will be treated as a partion in the overall image, it will look for an "EFI" partition for boot code,
			that needs be be layed out correctly. e.g EFI:\efi\boot\Boot$ARCH$.efi)
		DestPath - The path to the output image file
		imgName - name of the output file

	If any of the arguments are missing, the builder will begin prompting for all arguments, and will not continue until all arguments are provided.
	The builder will create 2 images one with a .VHDX extension and one with a .VHD extension, this is for compatibility with different virtualization software.

##	Run Image
	running the image will need you to use a virtualization software, such as Qemu, VirtualBox, or VMWare,the setup and arguments for each of these is different,
	so you will need to look up how to run a VHDX or VHD image on your chosen software.

## Debugging
	Deugging support is Planned for both the bootloader and kernel, most likely the bootloader and the kernel will initially allow debug through the UEFI Debug Protocol,
	and then once fully booted, through a custom protocol(possibly) over serial or usb. the end goal will be to have a full debugging experience avaible directly
	from visual studio, either remotelyt to bare metal, or through a virtual machine.




