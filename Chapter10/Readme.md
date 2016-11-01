## Chapter 10

### Exercise 10.1

> In Figure 10.2, remove the for (;;) statement. What happens and why?

When you first send the process a signal, the process will be terminated. Since the **pause** can only wait to catch one signal, and then return.

### Exercise 10.2

> Implement the sig2str function described in Section 10.22.

	int sig2str(int signo, char *str) {
		str = strsignal(signo);
		if(str != NULL)
			return 0;
		else 
			return -1;
	}

### Exercise 10.3

> Draw pictures of the stack frames when we run the program from Figure 10.9

	+++++++++++++++
	|             |
	|  sleep2's   |
	|  stack      |
	|             |
	+++++++++++++++
	|             |
	|  sig_int's  |
	|  stack      |
	|			  |
	+++++++++++++++
	|			  |
	|  sig_alrm's |
	|  stack      |
	|             |
	+++++++++++++++


### Exercise 10.4

> In Figure 10.11, we showed a technique that’s often used to set a timeout on an I/O operation using setjmp and longjmp. The following code has also been seen:

	signal(SIGALRM, sig_alrm);
	alarm(60);
	if (setjmp(env_alrm) != 0) {
		/* handle timeout */
		...
	}
	...	

> What else is wrong with this sequence of code?

There exists a race condition. When the first **alarm** is called. If the program is blocked at this time, the **setjmp** will never be called. Then if the **SIGALRM** is generated, the signal handler **sig_alrm** is called, so the **longjmp** is called, too. But since the **setjmp** is not called, so the **env_alrm** is not set properly. So the behaviour of **longjmp** is undefined.

 
### Exercise 10.5

> Using only a single timer (either alarm or the higher-precision setitimer), provide a set of functions that allows a process to set any number of timers.

I have no ideas.

### Exercise 10.6

> Write the following program to test the parent–child synchronization functions in Figure 10.24. The process creates a file and writes the integer 0 to the file. The process then calls fork, and the parent and child alternate incrementing the counter in the file. Each time the counter is incremented, print which process (parent or child) is doing the increment.

### Exercise 10.7

> In the function shown in Figure 10.25, if the caller catches SIGABRT and returns from the signal handler, why do we go to the trouble of resetting the disposition to its default and call kill the second time, instead of simply calling _exit?

I think it is because the behaviour of **abort** and **_exit** may be not same. This depends on the implementation.

### Exercise 10.8

> Why do you think the siginfo structure (Section 10.14) includes the real user ID, instead of the effective user ID, in the si_uid field?

Because if a signal is delivered from process A to process B, then the process A must be root or process A has same user ID or effective ID with B's user ID or effective ID. 

So if A's effective ID is same as B, then B would not be able to know his real user ID. So we use si_uid field to deal with this problem.

### Exercise 10.9

> Rewrite the function in Figure 10.14 to handle all the signals from Figure 10.1. The function should consist of a single loop that iterates once for every signal in the current signal mask (not once for every possible signal).

I have no ideas.

### Exercise 10.10

> Write a program that calls sleep(60) in an infinite loop. Every five times through the loop (every 5 minutes), fetch the current time of day and print the tm_sec field. Run the program overnight and explain the results. How would a program such as the cron daemon, which runs every minute on the minute, handle this situation?

### Exercise 10.11

> Modify Figure 3.5 as follows: (a) change BUFFSIZE to 100; (b) catch the SIGXFSZ signal using the signal_intr function, printing a message when it’s caught, and returning from the signal handler; and (c) print the return value from write if the requested number of bytes wasn’t written. Modify the soft RLIMIT_FSIZE resource limit (Section 7.11) to 1,024 bytes and run your new program, copying a file that is larger than 1,024 bytes. (Try to set the soft resource limit from your shell. If you can’t do this from your shell, call setrlimit directly from the program.) Run this program on the different systems that you have access to. What happens and why?

### Exercise 10.12

> Write a program that calls fwrite with a large buffer (about one gigabyte). Before calling fwrite, call alarm to schedule a signal in 1 second. In your signal handler, print that the signal was caught and return. Does the call to fwrite complete? What’s happening?

Since the buffer is very large, so the **fwrite** may took more than 1 second to finish its job, so the fwrite must be interrupted by signal handler. Then the result may depend on several factors, for example, what does signal handler do? How to deal the interrupted fwrite? 