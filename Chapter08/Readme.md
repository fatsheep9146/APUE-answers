## Chapter 08

### Exercise 8.1

> In Figure 8.3, we said that replacing the call to _exit with a call to exit might cause the standard output to be closed and printf to return −1. Modify the program to check whether your implementation behaves this way. If it does not, how can you simulate this behavior?

The program is here[click here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter08/Exercise_08_01). In order to cause the standard output to be closed in exit, I use the function **atexit** to register a function **my\_exit** to **exit**. In the **my\_exit**, we call **fclose** funtion to close the standard output. Then if child process call **exit**, the **printf** in the parent process will be wrote into standard output.

If we want to prove that **printf** will return -1, we can use **write** system call instead of **printf** to write the return code of **printf** into file **STDOUT_FILENO**, because even thought standrad output is closed, the file is not closed.

You can run the program in your system, then change the **exit(0)** in child process to **_exit(0)** and run it again to see the differences.

