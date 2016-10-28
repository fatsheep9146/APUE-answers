## Chapter 08

### Exercise 8.1

> In Figure 8.3, we said that replacing the call to _exit with a call to exit might cause the standard output to be closed and printf to return −1. Modify the program to check whether your implementation behaves this way. If it does not, how can you simulate this behavior?

The program is [here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter08/Exercise_08_01). In order to cause the standard output to be closed in exit, I use the function **atexit** to register a function **my\_exit** to **exit**. In the **my\_exit**, we call **fclose** funtion to close the standard output. Then if child process call **exit**, the **printf** in the parent process will be wrote into standard output.

If we want to prove that **printf** will return -1, we can use **write** system call instead of **printf** to write the return code of **printf** into file **STDOUT_FILENO**, because even thought standrad output is closed, the file is not closed.

You can run the program in your system, then change the **exit(0)** in child process to **_exit(0)** and run it again to see the differences.

### Exercise 8.2

> Recall the typical arrangement of memory in Figure 7.6. Because the stack frames corresponding to each function call are usually stored in the stack, and because after a vfork the child runs in the address space of the parent, what happens if the call to vfork is from a function other than main and the child does a return from this function after the vfork? Write a test program to verify this, and draw a picture of what’s happening.

The program is [here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter08/Exercise_08_02).

In the program, the child process is created inside the function **fun()**, when the vfork is called, the stack frame for parent process consists of two functions, which are **main** and **fun**. When the child process is created, he will use the same stack frame as parent process. So the child process first run and return from **fun**, so the stack frame for **fun** is destoryed. Then return to **main** and after **main** is done, the frame for **main** is also destoryed. 

At this time, the control is returned to parent process which is blocked in his **fun**, so he will execute the rest of the statements in **fun**, but when he executes **return**, he can not get any information from stack frame. So the fault is happening. 

### Exercise 8.4

> When we execute the program in Figure 8.13 one time, as in
	
	$ ./a.out
> the output is correct. But if we execute the program multiple times, one right after the other, as in

	$ ./a.out ; ./a.out ; ./a.out
	output from parent
	ooutput from parent
	ouotuptut from child
	put from parent
	output from child
	utput from child

> the output is not correct. What’s happening? How can we correct this? Can this problem happen if we let the child write its output first?

The output is mixed because, in the first **./a.out**, when the parent process finish his execution, he will be terminated, so the second **./a.out** can be scheduled with CPU. In the meantime, when the first parent process finish his execution, he will tell this message to his child process. So the child process can be scheduled with CPU, too. So the child process in the first **./a.out**, and the parent process in the second **./a.out** form race condition, so the output is mixed.

So if we want to correct it we must make sure the parent process can not be terminated until the child process finish his work. So we can correct the code like following.

	if((pid = fork()) < 0) {
		err_sys("fork error");
	}  
	else if(pid == 0) {
		WAIT_PARENT();
		charatatime("Output from child\n");
		TELL_PARENT(getppid());
	}
	else {
		charatatime("Output from parent\n");
		TELL_CHILD(pid);
		WAIT_CHILD();
	}

If we let the child write its output first, the output can not be mixed.


### Exercise 8.6

> Write a program that creates a zombie, and then call system to execute the ps(1) command to verify that the process is a zombie.

The program is  [here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter08/Exercise_08_06). When the parent process create a child process, but does not use **wait/waitpid** to capture is exit status, the children process turns into zombie process. So my program use this intuition.

So I keep track of the pid of children process, and use **system** to call **ps aux** to list the detailed format of all processes and filter them with **grep**, and keep all the infomation about the children process I just created. Then we can see from his information, **Z+** means the process is a zombie process.

 