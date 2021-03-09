# kernelModuleCycleCounter
Bela kernel module to enable user space access to Cycle Count register, for profiling.

The ARM CPU has a 32 bit cycle counter register (called CCNT), which increments every clock cycle (and can also be set to increment every 64 clock cycles instead, for longer intervals).

By reading this register before and after a piece of code and taking the difference, you can tell how many clock cycles the code took to execute.
If doing this in primary mode (i.e. in render()) then you will get the true execution time of your code, without interruptions from other tasks.
You can use this to directly measure the execution time of any piece(s) of code you want.

By default, however, this register cannot be read by user programs (attempting to do so generates an illegal instruction error - ouch!).  
A kernel module can be used to change the register settings to allow user access.

This project is a simple kernel module which does just this.
Simply copy the files to somewhere on your Bela, then from the command line:

cd to the folder containing the files.

make

insmod cycleCounter.ko


Although this is not a Bela project, you can still just drag it into the IDE to easily get the files onto the Bela.
It will complain, but it will work.

Read the C file for more information.

Now go and look at https://github.com/sjbaines/belaCycleCountProfileTest for an example of how to use.

