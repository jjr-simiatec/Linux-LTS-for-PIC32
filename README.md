# Linux-LTS-For-PIC32

## Background

In 2015, Microchip released a modified 4.2 series Linux kernel to support their PIC32MZ DA series MCU. The repository for the PIC32MZ DA kernel can be found here https://github.com/MicrochipTech/linux-pic32.

PIC32 support was added to the mainline kernel tree in version 4.5 but did not provide the same level of peripheral support as the earlier 4.2 version. So you could use a fully featured but unsupported kernel or the latest kernel with many useful of the more useful peripherals unavailable.

After I discovered I could apply the 4.2.x series patches to the Microchip kernel and used 4.2.8 for a time, I wondered if I could patch to the next kernel revision and get that to work. With the announcement that the 4.4 series was to be LTS and supported until February 2022, it seemed reasonable to try and get to that version and then see if the LTS patches would work.

## How to use

The rules and methods for applying patches is documented in "Applying Patches To The Linux Kernel" located here https://www.kernel.org/doc/html/v4.11/process/applying-patches.html.

Start with the 4.2 kernel archive from https://www.kernel.org. Then apply the patches for each base stable release to get to 4.4. Finally apply the latest LTS patch. The LTS patches in this repository should apply cleanly. If you wish to use a different LTS patch some files don't patch cleanly and you must update those files manually.

## Known issues

To check for files that weren't patched correctly, search for *.rej files:

`find . -name \*.rej -print`

Up to version 4.4.138, there are three files known to not patch properly. These along with remedial action are listed below:

### ./arch/mips/include/asm/cacheflush.h

`static inline void flush_icache_page(struct vm_area_struct *vma, struct page *page)`

Delete implementation.

### ./arch/mips/kernel/signal.c

`static int restore_msa_extcontext(void __user *buf, unsigned int size)`

If patch applied, duplicate check code added. Remove.

`int protected_restore_fp_context(void __user *sc)`

Patch after fp_done already applied - ignore.

### ./drivers/usb/musb/musb_host.c

`static int musb_tx_dma_set_mode_mentor(...)`

Patch already applied - ignore.

`void musb_host_rx(struct musb *musb, u8 epnum)`

@comment /* we are expecting IN packets */

Instead of assigning result of `musb_rx_dma_in_inventra_cppi41(...)` to ret, put function call directly in the `if(...)` statement.
