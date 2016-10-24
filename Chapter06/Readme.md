## Chapter 06

### Exercise 6.1

> If the system uses a shadow file and we need to obtain the encrypted password, how do we do so?

I think that if we do not have the root priviledge, we can not access the shadow file to get the encrypted password.

### Exercise 6.2

> If you have superuser access and your system uses shadow passwords, implement the previous exercise.

If we have the superuser access priveledge, we can access the encrypted password.
We can transfer to the root, and use the function like **getspnam** to get the encrypted password.

### Exercise 6.3

> Write a program that calls uname and prints all the fields in the utsname structure. Compare the output to the output from the uname(1) command.

The program is here([click here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter06/Exercise_06_03)):.

### Exercise 6.4

> Calculate the latest time that can be represented by the time_t data type. After it wraps around, what happens?

In the program I make([click here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter06/Exercise_06_04)):, I use **time** system call to get the current time, and increase this time with 86400 second(one day). Then we use this new value of time as input to **localtime** and **strftime** in order to output in a certain format. We can find that the new time will be output as the same time but in the next day.

For example, current time is 2016.10.24 21:16:00, then the output will be 2016.10.25 21:16:00. 

### Exercise 6.5

> Write a program to obtain the current time and print it using strftime, so that it looks like the default output from date(1). Set the TZ environment variable to different values and see what happens.

I wrote the program([click here](https://github.com/fatsheep9146/APUE-answers/tree/master/Chapter06/Exercise_06_05)): to show the current time in the same format as shell commend **date**. The timezone of this program is **CST**.

Then I set TZ environment variable as **"UTC"** with following commend

	export TZ="UTC"

Then the output of the program is changed to UTC.

