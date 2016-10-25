## Chapter 07

### Exercise 7.1

> On an Intel x86 system under Linux, if we execute the program that prints ‘‘hello, world’’ and do not call exit or return, the termination status of the program — which we can examine with the shell—is 13. Why? 7.2 When is the output from the printfs in Figure 7.3 actually output.

Since the **main** function does not have any **return** or **exit**, then the return code of main must be the return code of the last statement have none-void return type. In this program, the last statement has return type is **printf**, which is the number of characters being print. So the return code must be 13, which is the length of the string "hello, world".

### Exercise 7.2

> When is the output from the printfs in Figure 7.3 actually output?

Because the stdout is line buffering, and all the strings output by **printf** in Figure 7.3 end with new line character. So the content of **printf** in figure 7.3 will be output immediately after **printf**.

### Exercise 7.3

> Is there any way for a function that is called by main to examine the command-line arguments without (a) passing argc and argv as arguments from main to the function or (b) having main copy argc and argv into global variables?

I think we can use environment variable to store the argc and argv, since every program has access to an environment variable table.

### Exercise 7.4

> Some UNIX system implementations purposely arrange that, when a program is executed, location 0 in the data segment is not accessible. Why?

This provides a way to terminate the process when it tries to dereference a null pointer, a common C programming error.


### Exercise 7.5

> Use the typedef facility of C to define a new data type Exitfunc for an exit handler. Redo the prototype for atexit using this data type.

	typedef void ExitFunc(void);
	
	int atexit(ExitFunc *fun);

### Exercise 7.6

> If we allocate an array of longs using calloc, is the array initialized to 0? If we allocate an array of pointers using calloc, is the array initialized to null pointers?

The answers for two question are both 'yes'.

 
### Exercise 7.7

> In the output from the size command at the end of Section 7.6, why aren’t any sizes given for the heap and the stack?

The heap and the stack are both dynamically allocated to the program when the program is running. So the information about them can not be recorded into the executive file.

### Exercise 7.8

> In Section 7.7, the two file sizes (879443 and 8378) don’t equal the sums of their respective text and data sizes. Why?

Because the two executable files contains several other sections other than **text**, **data** and **bss** sections. So the result of `ls -l` is the size of all sections which must be larger than the sum of only three sections.

### Exercise 7.9 

> In Section 7.7, why does the size of the executable file differ so dramatically when we use shared libraries for such a trivial program?

Because if we do not use shared libraries, then we should copy one copy of library functions into each program the user make. And the library functions are always very large.

### Exercise 7.10

This code is not recommended, although we can execute with no error. But the variable **val** inside the braces of **if** is a local variable, and will be freed after the right brace of if. So in the **return** statement, the **ptr** deferenced a freed memory, which is not safe.


