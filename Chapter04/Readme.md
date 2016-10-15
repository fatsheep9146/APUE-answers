## Chapter 04

### Exercise 4.1

> Modify the program in Figure 4.3 to use stat instead of lstat. What changes if one of thecommand-line arguments is a symbolic link?

The result of argument "/dev/cdrom" will be changed.

When we used **lstat**, the output is 
	
	/dev/cdrom: symbolic link

When we used **stat**, the output is 

	/dev/cdrom: block special

Since the /dev/cdrom is a symbolic link file which links to /dev/sr0，when we use symbolic link file as argument to **stat**，the command will actually check the stat of the file which the file links, so **stat** check the stat of file "/dev/sr0".

### Exercise 4.2

> What happens if the file mode creation mask is set to 777 (octal)? Verify the results using your shell’s umask command.

Using following shell command to change the mode creation mask into 777

	$ umask 777

You can check the umask by shell command umask
  
    $ umask
    777

After this operation, we can still creat file and directory on current directory, for example we use following commands to create one file called **1.txt**, and one directory **dir1**

	$ cat > 1.txt
    hello world! (press Ctrl+D to stop inputting)
    $ mkdir dir1

Then we enter `ls -l` to see the result as following

    total 8
	---------- 1 zzq zzq   13 Oct 15 20:39 1.txt
	d--------- 2 zzq zzq 4096 Oct 15 20:35 dir1	

So the three roles, owner, group, other users all do not have right of read, write and execution.

So when we use vim to see the content of **1.txt**, the system will tell us "Permission denied", and we won't see anything.

When we want **cd** to directory **dir1**, the system will also tell us "Permission denied".    
  