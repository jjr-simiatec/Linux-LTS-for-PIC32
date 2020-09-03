# Running Linux on the PIC32MZ DA Starter Kit 

## What you need

* PIC32MZ Embedded Graphics with External DRAM (DA) Starter Kit, Microchip part number DM320008 or DM320008-C
* microSDHC card (2GB minimum) and/or TFTP server
* PuTTY or equivalent Terminal Emulator
* MPLAB X IDE for initial installation of U-Boot

## Manifest

`u-boot.hex` - U-Boot with Ethernet, MMC and USB support  
`pic32-boot-recovery.itb` - FIT image containing the Linux kernel, RAM disk and device tree  
`pic32-boot.itb` - FIT image containing the Linux kernel and device tree  
`modules-pic32.txz` - Modules for the kernel in the FIT images  
`rootfs.tar.xz` - rootfs to be transferred to the SD card  
`id_ed25519` - SSH *private key* for example user. Refer to security notes!

## Installing U-Boot

* Two Type-A to Micro-B USB cables are required.
* Connect the first cable from the **UART-USB** port (J5) to your PC. A Com Port will appear but the rest of the board will remain unpowered.
* Start PuTTY and connect it to the Com Port at baud rate 115,200.
* Connect the second cable from the **Debug** port (J19) to your PC. The board should now power up.
* Start `MPLAB X IDE`.
* Select **New Project** and choose **Prebuilt (Hex, Loadable Image) Project** from the **Microchip Embedded** category.
* Browse for `u-boot.hex` for the **Prebuilt Filename**.
* Choose **PIC32MZ2064DAB288** for the **Device**.
* Choose **Starter Kits (PKOB)** for the **Hardware Tool**.
* After completing the project creation process, you will need to **Run Main Project**. This will flash the PIC32.
* When flashing is complete, the yellow LED (LED2) should light indicating that U-Boot has started.
* Output from U-Boot should be visible in the terminal.
* Verify that U-Boot starts when power is removed and then reapplied. Assuming this works, the debug cable is no longer needed.

## Loading the recovery enviroment via TFTP

Place `pic32-boot-recovery.itb` on your TFTP server ensuring the permissions are correct.

For this example, it will be assumed the TFTP server address is 192.168.1.1 and the PIC32 address will be 192.168.1.200.

```
setenv ipaddr 192.168.1.200
setenv serverip 192.168.1.1
tftp ${fitimage_addr_r} pic32-boot-recovery.itb
bootm
```

## Preparing the SD card

While the SD card can be prepared on any Linux system, it can be done just as easily from the recovery environment running on the PIC32. An example procedure is as follows:

* Boot the recovery environment and insert a SD card
* Use `gdisk` to create a new GUID Partition Table with two partitions: the first 256M in size, the second 1G.
* Format the two partions. For example:

```
mke2fs -t ext4 -e remount-ro -E lazy_itable_init=0,discard -O ^has_journal /dev/mmcblk0p1
tune2fs -o discard,journal_data_writeback /dev/mmcblk0p1
```

* Set up the boot partition:

```
mount /dev/mmcblk0p1 /mnt
scp scp://jjr@192.168.1.1//home/pic32/pic32-boot.itb /mnt
scp scp://jjr@192.168.1.1//home/pic32/pic32-boot-recovery.itb /mnt
umount /mnt
```
* Set up the root partition:

```
scp scp://jjr@192.168.1.1//home/pic32/rootfs.tar.xz /tmp
scp scp://jjr@192.168.1.1//home/pic32/modules-pic32.txz /tmp
mount /dev/mmcblk0p2 /mnt
tar xf /tmp/rootfs.tar.xz -C /mnt
tar xf /tmp/modules-pic32.txz -C /mnt
umount /mnt

```
* Reboot and ensure Linux starts automatically.
* Reboot and ensure the recovery image can be started (refer to the boot sequence descriptions below).

## Cold boot sequence reference

* Hold down switch SW1 if you want to boot the recovery image from the SD card. Otherwise, the operational image will be booted.
* Apply power. When the yellow LED (LED2) is lit, you can release switch SW1 if you have pressed it.
* If a SD card is not present, you will need to interact with U-Boot to do anything useful.
* If SW1 was held, U-Boot will try to load `pic32-boot-recovery.itb` from the first partition and boot it. Note: There will be a delay of up to 25 seconds while the RAM disk is decompressed.
* Otherwise, U-Boot will try to load `pic32-boot.itb` from the first partition and boot it.
* When the kernel starts to run, the green LED (LED3) will be lit. The red LED (LED1) provides a 'heartbeat' indication and the yellow LED shows SD card activity.

## Warm boot sequence reference

This proceeds as for the cold boot sequence except that the SRAM test is not done. If you want to change to recovery mode, hold down the appropriate switch before issuing the `reboot` command.

## Linux environments

For both *operational* and *recovery* enviroments, the same Linux kernel v4.4.232 is used.

The rootfs for the operational environment resides on partition 2 of the SD card. This partition is mounted read-only so the power can be removed at any time during normal use without corrupting the filesystem.

The rootfs for the recovery environment is RAM based. Once the image has been loaded, the SD card is no longer needed and can be swapped or removed.

Both rootfs types were built using Buildroot v2020.08. MUSL is the C runtime and BusyBox provides most of the usual utilities. Full versions of utilities/tools are provided where the BusyBox equivalents are limited or have compatibility issues.

An IP address will be obtained using DHCP and the time set via NTP if appropriate connectivity is available. SSH is also available.

## Security notes

The SSH host keys will need to be regenerated in the operational environment for any serious use. It will take a few minutes for the PIC32 to do that...

The SSH configuration is hardened and only allows public key authentication. The provided sample key `id_ed25519` can be used to test the SSH server with the user name `user`. Again, for serious use this key needs to be changed.

