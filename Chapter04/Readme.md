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

### Exercise 4.3

> Verify that turning off user-read permission for a file that you own denies your access to the file.

We can use following commands to create a file, write some characters into it, and then turning off user-read permission.

	$ cat > 1.txt
    hello world!
	$ chmod u-r 1.txt

Then when I want to use vim to check the content of the **1.txt**, the system will say that permission denied.

### Exercise 4.4

>  Run the program in Figure 4.9 after creating the files foo and bar. What happens?

Just as Section 3.4 says that, **creat** is just same as 
	
	open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);

So if we already run the program in Figure 4.9 once, **foo**, **bar** will be created. But if we write some characters into **foo**(**bar** also works) before we run the program again, then after we run the program again, there are still one copy of **foo** and **bar**, but the characters we just wrote into foo will be truncated.

### Exercise 4.5

> In Section 4.12, we said that a file size of 0 is valid for a regular file. We also said that the st_size field is defined for directories and symbolic links. Should we ever see a file size of 0 for a directory or a symbolic link?

For directory, a directory file size of 0 is not possible, because of two reasons:

1. Each directory will automatically be provided two default directory entries "." and ".." when it is created.
2. Each directory will use up all the bytes which is allocated to it when it is created. We can use `ls -l` to check the directory size, we would found that, most of the directory's size is 4096, this size should be the "st\_size" entry of the stat struct for this directory file, when we check this file's **st\_blocks**, the result is 8, 512 * 8 is just equal to 4096. So the directory used up all the bytes allocated to it.

For symbolic link, the file size is the length of the pathname of which the symbolic link file links to, for example, symbolic file **/mnt** links to **"/var/usr"**, then the file size of link file is length of string **"/var/usr"**.

Since we can not create a symbolic link but links no file, so the file size of the link file can not be 0, either.

### Exercise 4.6

> Write a utility like cp(1) that copies a file containing holes, without writing the bytes of 0 to the output file.

We wrote three files([click here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter04/Exercise_04_06)):

* **file\_with\_hole.c**: this c file create a file with hole in it called '1.txt'
* **cp.c**: this file is the answer to the question, which can copy the valid content(the character which is not '\0') of file with hole into another file. Assume the new file called **3.txt**
* **file\_without\_hole.c**: this c file create a file without hole, which has same content with **1.txt**, but the hole in **1.txt** will be substituted with real '\0' in it. The file called **2.txt**

So after we execute three execution files which are generated from above three files by following commands, we can get three files

	$ ./file_with_hole 1.txt
    $ ./file_without_hole 2.txt
    $ ./cp 1.txt 3.txt

Then we use `ls -ls` to check

	8 -rwxrwSr-T 1 zzq zzq 16392 Oct 16 14:52 1.txt
	20 -rwxrwSr-T 1 zzq zzq 16392 Oct 16 14:54 2.txt
	4 -rw-rw-r-- 1 zzq zzq    16 Oct 16 15:10 3.txt

We can see that **1.txt** and **2.txt** have same st_size, but they are allocated different amount of blocks, **1.txt** is 8, **2.txt** is 20. So we can see that, **1.txt** has hole. And **3.txt** has least size, because it only contains character which is not '\0'.

### Exercise 4.7

> Note in the output from the ls command in Section 4.12 that the files core and
core.copy have different access permissions. If the umask value didn’t change between the creation of the two files, explain how the difference could have occurred.

Since in the program in section 4.12, the file "core" is created by the similar program in figure 3.2 of section 3.6. So the core's mode is FILE_MODE, we can find this macro in **apue.h**

	#define FILE_MODE       (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

And the umask is `002`. So the core's mode is certainly `rw-r--r--`.

But the **core.copy** is created by system. The system's default file mode is decided by umask, first the new file's mode is rw-rw-rw before combined with umask(System do not allow to add the execution right 'x' when creating file).
umask is now '002'. So after combined, the new file's mode is changed into 'rw-rw-r--'.


### Exercise 4.8

> When running the program in Figure 4.16, we check the available disk space with the df(1) command. Why didn’t we use the du(1) command?

According to the following explinations:

> **df**  will read the meta data of the disk partition containing the specified folder which in your case is app1 and return the disk partition information rather than that of the actual directory.

> **du**  will runs through the directory tree specified and counts the sum size of all the files under the directory and return the total space occupied by that directory.

We can see that, although these two commands both can know the data file size on the disk, but the **du** should use the directory file to find the data files, but **df** do not have to. So after the program in figure 4-16 unlinked the file
the directory entry for the **tempfile** are deleted, so if we use **du** to check the size of all the files in current directory, the **tempfile** will not be included, so the results of two `du -sh` commands executed **before** "done" is printed on the console and **after** "done" is printed on the console are same. 

### Exercise 4.9

> In Figure 4.20, we show the unlink function as modifying the changed-status time of the file itself. How can this happen?

Because **unlink** will change the **link count** of this file, which is a information that stored in the **inode** of this file, so the **st_ctim** will be changed, too.

### Exercise 4.10 

> In Section 4.22, how does the system’s limit on the number of open files affect the myftw function?

In the function **dopath**, the **opendir** will be called recursively, if we use opendir to open a directory file, then a file descriptor will be created, and unless we finished visitting of all the subfiles of this directory, the directory file can be closed. So the system's limit on the number of open files will limit the maximum depth of directory hierarchy we scan.

  
### Exercise 4.12 

> Each process also has a root directory that is used for resolution of absolute pathnames. This root directory can be changed with the chroot function. Look up the description for this function in your manuals. When might this function be useful?

Since chroot function can create a new root directory for command, system can create so-called "chroot jail" for users which enter the system. The chroot can limit the files that user can visit, user can only visit the files under the new chrooted root directory. By doing this, the system is well protected.

### Exercise 4.13

> How can you set only one of the two time values with the utimes function?

Note that, the second parameters for **futimens** and **utimes** are not same. In  **futimens** are 
	
	struct timespec{
		time_t tv_sec;
 		long tv_nsec;  // Note that, the unit is nanosecond
	};   

In **utimes** are

	struct timeval {
		time_t tv_sec;
		long tv_usec;  // Note that, the unit it microsecond
	};

So if we want to set only one of the two times, we should first use **stat** to obtain original time values, after the file is visitted or modified, we could use the original time values we just got to restore the time value which we want. 

The program in the **main.c**, is after we modify one file, we remain the file's access time unchanged, but modified time changed.


 