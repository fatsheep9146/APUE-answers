## Chapter 10

### Exercise 10.1

> In Figure 10.2, remove the for (;;) statement. What happens and why?

When you first send the process a signal, the process will be terminated. Since the **pause** can only wait to catch one signal, and then return.

### Exercise 10.2


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

 