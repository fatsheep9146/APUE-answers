## Chapter 09

### Exercise 9.1

> Refer back to our discussion of the utmp and wtmp files in Section 6.8. Why are the logout records written by the init process? Is this handled the same way for a network login?

When the user is terminal login, the workflow is **init**->**getty**->**login**->**shell**. When the **login** is done, it will be deleted, so the process **shell** becomes orphan process and be redirected to **init** as his child. 

So when the user logouts, the process **shell** must be deleted, and his parent **init** will notice this event. Then he writes the logout record to file **wtmp** and **utmp**.

But in the network login, the parent process of **shell** is process **inetd**, and he is always running to accept other network login request, so when user logouts, it is **inetd**'s duty to write to the file **utmp** and **wtmp**.

### Exercise 9.2

> Write a small program that calls fork and has the child create a new session. Verify that the child becomes a process group leader and that the child no longer has a controlling terminal.

The program is [here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter09/Exercise_09_02). In the program, we use **fork** to create a child process, and in the child process, we use **setsid** to create a new session for this child process. And then, we use **print_ids** to check about all related ids for a given process. The output is just like following:

	parent: pid = 14549, ppid = 14018, pgrp = 14549, tpgrp = 14549, sid = 14018
	child : pid = 14550, ppid = 14549, pgrp = 14550, tpgrp = -1, sid = 14550

We can see that, for this child process, the **sid**, which means the session leader process id, is different from parent. This means that the two process are in different sessions. 

Then the **tpgrp** is the process group ID of foreground process group. We can find that the child process's **tpgrp** is -1, which means he does not have foreground process group, which means he no longer has a controlling terminal.


