/***** cycleCounter.c *****/

// This is NOT a Bela project!
// This is used to build a small kernel module which allows access to CCNT Cycle Counter register from actual Bela projects.
//
// To build this, enter the following at the command line:
// # cd ~/Bela/projects/kernelModuleCycleCounter    <--- Use whatever name you imported this project as.
// # make											<--- Wait until you see 'make[1]: Leaving directory message
//
// To install the module:
// # insmod cycleCounter.ko
// To check it worked:
// # dmesg | tail -1
// Should show 'Enabling user access to Cycle Counter register (CCNT)'


#include <linux/module.h>
#include <linux/kernel.h>    // For KERN_INFO
#include <linux/init.h>      // For __init and __exit macros

MODULE_LICENSE("Public Domain");
MODULE_DESCRIPTION("Module to enable Cycle Counter on ARM v7 Cortex 8 CPU");

static int __init cycle_counter_init(void)
{
    printk(KERN_INFO "Enabling user access to Cycle Counter register (CCNT)\n");
    asm ("MCR p15, 0, %0, C9, C14, 0\n\t" :: "r"(1)); // Allow user access
    asm ("MCR p15, 0, %0, C9, C14, 2\n\t" :: "r"(0x8000000f)); // Disable overflow interrupts
    return 0;    // Success
}


static void __exit cycle_counter_cleanup(void)
{
	printk(KERN_INFO "Exiting Cycle Counter module.\n");
}

module_init(cycle_counter_init);
module_exit(cycle_counter_cleanup);

