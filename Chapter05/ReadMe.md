## Chapter 05

### Exercise 5.1 

> Implement setbuf using setvbuf.

	void setbuf(FILE *restrict fp, char *restrict buf) {
		if(buf != NULL) {
			setvbuf(fp, buf, _IOFBF, BUFSIZ);
		}
		else {
			setvbuf(fp, NULL, _IONBF, 0);
		}
	} 

### Exercise 5.2 

> Type in the program that copies a file using line-at-a-time I/O (fgets and fputs) from Figure 5.5, but use a MAXLINE of 4. What happens if you copy lines that exceed this length? Explain what is happening.

As the text said

> With fgets, we have to specify the size of the buffer, n. This function reads up through and including the next newline, but no more than n − 1 characters, into the buffer. The buffer is terminated with a null byte. If the line, including the terminating newline, is longer than n − 1, only a partial line is returned, but the buffer is always null terminated. Another call to fgets will read what follows on the line.

So if MAXLINE is reduced to 4, then many lines may be readed piece by piece of which size is 3. And since the **fputs** function will output the stream until it met '\0', then append with a newline char, so if the input is 

	'aaabbbccc'

Then in the original version of this program, the output is 

	'aaabbbccc'

However in this case, the output should be
	
	'aaa'
	'bbb'
	'ccc'

### Exercise 5.3

> What does a return value of 0 from printf mean?

The return value of **printf** is the amount of characters which are successfully outputted to stdout.

So if the return value is zero, it means that the **printg** output the empty string. For example, **printf("");**


### Exercise 5.4 

> The following code works correctly on some machines, but not on others. What could be the problem?

I have no idea...

### Exercise 5.5

> How would you use the fsync function (Section 3.13) with a standard I/O stream?

You should first call the funtion **fflush** to clear the buffer in order to call system call **write**. And then call **fsync** to write the data into disk.

### Exercise 5.6

> In the programs in Figures 1.7 and 1.10, the prompt that is printed does not contain a newline, and we don’t call fflush. What causes the prompt to be output?

The program in Figure 1.7 and 1.10 both have stdin as their input, stdout as their output. Section 5.4 said that:

> Line buffering is typically used on a stream when it refers to a terminal—standard input and standard output, for example.

So we can infer that,  the stdin and stdout is line buffering. Then section 5.4 also said that:

> Second, whenever input is requested through the standard I/O library from either (a) an unbuffered stream or (b) a line-buffered stream (that requires data to be requested from the kernel), all line-buffered output streams are flushed.

Since in the programs of Figure 1.7 and 1.10, the statements

	printf("%% ");

which control stdout output stream, are all followed by the statement 

	fgets(buf, MAXLINE, stdin)

control stdin input stream, in which case is just like above discussion. output streams will be flushed by the input streams.

So the prompt will be shown on the screen.

