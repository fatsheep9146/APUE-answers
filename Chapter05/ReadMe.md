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

