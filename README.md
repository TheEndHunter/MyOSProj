# Operating System Project

## Description
	A Custom Multi-Platform OS Built From Scratch.
	This is a learning project to learn more about OS Development and how to build a UEFI Compliant Bootloader for an OS.
	This project is written using C++ and Assembly. The tools are built using C#.

## Platforms Supported
	[x] x86
	[~] ARM (ImageBuilder and QemuRunner do not support ARM as C# does not have files for it.Not Tested At This Time, But Source Will Be Created)
	[x] x64
	[~] ARM64 (Not Tested At This Time, But Source Will Be Created)

## Building
	!! Build Supported on Windows Only At This Time!!
	Run build through Visual Studios 2022 or later.

## Build Image
	Run Build first!
	In The Tools folder of the solution.
	Run the Build_$(Platform)_$(Configuration).bat for the architecture/configuration you want to build for.
##	Run Image
	Prerequisites:
		- Qemu
	Run Build
	Build Image
	Run the Run_(Platform)_$(Configuration).bat for the architecture/configuration you want to build for.

## Debugging
	To Be Implemented. Plan is to use UEFI Debuging Protocol to allow for debugging.

## Features
	P=Planned, IP=In Progress, C=Completed,N=Not Planned, ?=Suggested
	NOTE: Not In Order Of Implementation
	[P] ACPI Support
	[P] AHCI Support
	[P] ATA Support
	[P] Audio Support
	[P] Debugging support
	[P] Ext3 Support
	[P] Ext4 Support
	[P] FAT32 Support
	[P] Graphics Support
	[P] Multihreading Support
	[P] Networking & Communications Support(Bluetooth, Wifi, Ethernet)
	[P] PCI Support
	[P] Serial Console
	[P] Shell Commands
	[P] Shell Support
	[P] UEFI File System Support
	[P] USB Support
	[P] Windowing System



