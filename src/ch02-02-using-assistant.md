## Using the Assistant to check a Simple Symbol Calculator program

This exercise is a simple program that must be executed on the ALE Simulator and checked using the Assistant's tests.

### Development Tutorial

Programs written in C are usually linked to the C standard library and with object files that contain support routines to the application's execution. These routines, initialize the C library's data structures, organize the parameters to the main function (\_start) and, after returning from the main function, invoke the operating system to signal the end of the application (function exit).

#### \_start function and exit syscall

Besides linking the code from multiple object files (.o), the linker must register the address of the entry function of the program on the header of the executable file so that the operating system's _loader_ knows where to start the execution of the program once it starts. By default, in C and C++, the program's entry point is defined by the function called **\_start**. This is a short function that invokes the function main() and after main returns, it invokes the **exit** syscall. to inform the operating system that the program has finished.

When generating the executable files, C and C++ compilers link an object file that has the implementation of this function. However, the RISC-V compiler used here doesn't link to such file (nor LibC), thi way, it is necessary to include an implementation of the function.

The following code shows possible implementations to the function **exit** and the function **\_start**. In this example, the function exit consists of a sequence of instructions in assembly language that copies the value of function parameter (code) to the register a0, puts the value 93 on register a7 and generates a software interrupt (ecall instruction). The software interrupt redirects the execution flow to the operating system, which will use the value on register a7 to determine which syscall was requested and the value on register a0 as a parameter to the call.

```c
void exit(int code)
{
  __asm__ __volatile__(
    "mv a0, %0           # return code\n"
    "li a7, 93           # syscall exit (64) \n"
    "ecall"
    :             // Output list
    :"r"(code)    // Input list
    : "a0", "a7"
  );
}

void _start()
{
  int ret_code = main();
  exit(ret_code);
}
```

The **\_start** function code simply calls the **main** function, which is implemented by the user, and, after main's return, invokes the **exit** function passing the **main** return value as a parameter.

You can copy and paste these two functions on your C programs that will be executed on the ALE simulator. Alternatively, you can put them in a file called start.c and compile/assemble/link the file with your program.

#### read and write syscalls

In general, programs that execute in computer systems that have an operating system don't have direct access to the system's peripherals (e.g., monitor, keyboard, mouse, ...), in other words, that can't interact directly with these devices. In this case, all interactions with these devices are done via system calls (_syscalls_).

The organization of the Linux operating system is strongly based on the concept of files. In this context, each file is identified by a path and a name (e.g., /home/students/john/prog.c). In addition to that, when a file is opened by a program, the operating system associates this file with a file descriptor and returns this file descriptor to the program. The file descriptor is an integer that must be provided by the program every time it requests the operating system to perform an operation with the file (e.g., write or read of data). In short, to write to (or read from) a file, the program must:

1. Invoke the operating system with the **open** syscall to open the file. This syscall will open the file and return an integer that corresponds to the file descriptor of the opened file.
2. Invoke the **write** or **read** syscall passing as argument the file descriptor of the file and a buffer to write or read data; and, finally
3. Invoke the operating system with the close syscall to close the file.

There are three special file descriptors that are always available and don't have to be opened or closed: STDIN, STDOUT and STDERR. The Values of the file descriptors STDIN, STDOUT and STDERR are 0, 1 e 2, respectively.

These file descriptors correspond to the standard input, standard output and error output of the program. When the program writes to standard output or error output, the operating system shows what was written on the terminal; where the program is being executed. In case the program reads from standard input, the operating system (i) waits until the user types something in the standard input and press ENTER, and (ii) returns to the program what was typed in the terminal.

The following code shows the implementation of a function in C that contains code in RISC-V assembly language to invoke the syscall **read**. This function contains a set of RISC-V instructions that adjust the parameters and invoke the operating system to perform the read operation through the read syscall.

```c
/* read
 * Parameters:
 *  __fd:  file descriptor of the file to be read.
 *  __buf: buffer to store the data read.
 *  __n:   maximum amount of bytes to be read.
 * Return:
 *  Number of bytes read.
 */
int read(int __fd, const void *__buf, int __n)
{
    int ret_val;
  __asm__ __volatile__(
    "mv a0, %1           # file descriptor\n"
    "mv a1, %2           # buffer \n"
    "mv a2, %3           # size \n"
    "li a7, 63           # syscall read code (63) \n"
    "ecall               # invoke syscall \n"
    "mv %0, a0           # move return value to ret_val\n"
    : "=r"(ret_val)                   // Output list
    : "r"(__fd), "r"(__buf), "r"(__n) // Input list
    : "a0", "a1", "a2", "a7"
  );
  return ret_val;
}
```

As you don't have access to the C standard library, you can use the function above to perform read operations from the standard input. To do so, just call the function **read** to the file descriptor of value 0. To use it, you must allocate a buffer that can be a global variable, like the example below. Note that the global variable (input_buffer) is an array with 10 characters, a 10 byte array. After reading the data, the **read** function writes the read bytes to the provided buffer and returns the amount of bytes read. The last parameter of the **read** function indicates the maximum amount of bytes that must be read. In case the amount of bytes read is greater than this value, the **read** function just writes the maximum amount of bytes (10 in the example below) on the input buffer and returns. The remaining bytes are stored in an internal buffer of the operating system and are returned when the **read** function is called again.

```c
/* Buffer to store the data read */
char input_buffer[10];

int main()
{
  /* fd = 0 : reads from standard input (STDIN) */
  int n = read(0, (void*) input_buffer, 10);
  /* … */
  return 0;
}
```

The following code shows a possible C implementation of the function write. This C function contains a code in RISC-V assembly language to invoke the system call (syscall) **write**. It invokes the operating system to write **\_\_n** bytes from the buffer **\_\_buf** on the file (or device) indicated by the file descriptor, parameter **\_\_fd**. When **\_\_fd** = 1, this function writes to the standard output (stdout).

```c
/* write
 * Parameters:
 *  __fd:  files descriptor where that will be written.
 *  __buf: buffer with data to be written.
 *  __n:   amount of bytes to be written.
 * Return:
 *  Number of bytes effectively written.
 */
void write(int __fd, const void *__buf, int __n)
{
  __asm__ __volatile__(
    "mv a0, %0           # file descriptor\n"
    "mv a1, %1           # buffer \n"
    "mv a2, %2           # size \n"
    "li a7, 64           # syscall write (64) \n"
    "ecall"
    :   // Output list
    :"r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
}
```

Again, as you don't have access to the C standard library, you can use the function above to write to the standard output of the program, in other words, the terminal where your program was executed. To do so, just call the function write to the file descriptor 1. The code below shows an example where the write function is called to show a string on the output terminal.

```c
/* Allocates a global string with 5 bytes.
 *   Note: the break line character, \n is encoded
 *       with a single byte */
char my_string[] = "1969\n";

int main()
{
  /* Prints the first 5 characters from the string on
   * the standard output, in other words, 1, 9, 6, 9 and break line. */
  write(1, my_string, 5);

  return 0;
}
```

The ALE simulator expects a break line character ('\n') to print the content written to the standard output on the terminal. This way, you must add a break line at the end of your buffer or call the function **write** again with a string that has the break line character. The example above shows a program that prints a string with 5 characters ending with a break line.

### Instructions

You must write a C program that implements a simple calculator. The calculator must read a string from the Standard Input with the following format: **s1 op s2**, where **s1** and **s2** are symbols that have a value associated to them and **op** is the operation to be performed.
The result of the operation must be written to the Standard Output, i.e., file descriptor equals to 1.

The symbols to be considered are the characters '0', '1', '2', '3', '4', '5', '6', '7', '8', and '9', and the values associated to them are zero, one, two, ..., and nine.

The arithmetic operations are represented by the symbols '+' (addition), '-' (subtraction) and '\*' (multiplication).

### Examples

| Test Case | Input  | Output |
| :-------- | :----: | :----: |
| 1         | 2 + 3  |   5    |
| 2         | 7 - 7  |   0    |
| 3         | 4 \* 2 |   8    |

### Notes and Tips

- All inputs are 5-character strings, where the first character represents the first symbol, the second is a space, third determines the operation, fourth is a space, and the fifth character is the second symbol.
- The test cases have values between 0 and 9 (just one digit) as outputs, so it is not necessary to implement a complete conversion function from integer to string (itoa).
- Your program must be self-contained and cannot use library routines, not even C's standard library.

### Using the Assistant

We will be using the assistant from the RISC-V simulator for the first time in this exercise. It can be accessed via this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14QUhwV0FDQVNUQVFIczZwRG9XSmtLUWlnQk1PQUd6N0prc1pCekI5SkFWeG1vQ0FIUmhSZUFvY0FDcVhPQUFsVU1oS2pvNE9BUVNJbHlsT0FHVjZqVWdGOE9BR1owZkdBY09pQUFkS3lxR2xvRXJDS3U0aEVBVnJvZ2VnYjhnaHpBQURKOE5CQXlBRXFvMlg2QndhSGhVVEdhMnF3MGZEQXdxRFNrVUMycDZRRGNlbm8wTWlJY0FLSUFIZ0JNY0pNY3FPT2txRENTQkU0dVl1NWVERXk1QXpBY0hNMHdaSFRxSFFJQUZBQ1V3SG9IQndUcXRuVFgtZnYzcEFBV0pCSHFVQndBWGc0YlFBN2h3ekpack04THVFSm5ZYUNSVUJ4SmhGSmhnT0I0c2xvTVFCUE1BQUl6NE1nNEFHRmlqUk5CQlNBSndsYzN2ZFpLZ2hIUnlrWkFjRFVHQ0NrVlNxekJLODdoOXZnUUlrYzJoMHVzY0lnaDFBUlBoY1dSVTZYc0dld3hqQUlQanNRUWNiUmlqSlZsSU9BUW1Sd3ZraUVNRmtIUUlLRXhEUUFOYUNnNWZINlcxQ1NWQUJXQWV1QVFPaklWWkFnRGE0UUF0R0hRVElvUGp3ZzV3MkdUYVFXY2c0MkVRQVFFQUNBQXpqQURzQURFaTBXU1dtRXlRSUdYOERSSk42d0k5d2dCZE43T3MzQzM1UUNJUVNTU09DTE1nd2tBa2tJSUtERFRvdE5Od1FFQVBseWlxTUVSWlluNWRJNExOSTZqbysxZElyUWJRWU5EZ3pWNFk5UWZlMHBHdXIxOERtQUFXZ01qZ3FIOU1oeDZPVDZsUXZtVk1GYmFzY0h0QWlnY1lQVE5TOWRIZUE0dENFZnNxQ2dhUWdRQVJsYlhjT3k3SHNMd0hBQURBQVZTOE9BQUVtQU9DNEFRZ0JxY2otQXVBQkhMOHlFbEs0T0RESndlMndodzBPSVhndEdmT2ppaWdVZ2NTd3E5c05tY2lPQUFaaDBQUjJJNGJDQUZacEpnV1RnQlBKQVdUZ0FKMUJnQ1VXblJDNElCd2ZFbUlCT2NJQWlaTURHdVFFZ1h4Q3lHREFhNGZ5dVZEMnorRERlemdpNDhJSTRqU0lvcWlPRm8raUp4Z0ppV0k4ZFI4Vmt6aXNYUFZBK09qUVRoTzh2Tm1JNFBNbE5rN0RzeXl1ODFQOWM4dEowMEw5TU00eloyRWV5ckpNMnpxc2NxNW5OY241M083VHpMMjgtQ3lDSWtqTHpJeVJLT291akwwWTlLQUZsTkJpOXN1SVFIaUV2VWZqa3E4N0NBQllPQUFLbVJQSzVJQURtMjFTUjBLelR0TjBtQXlxTWt5elBxNnlBVHF5eUdxYXY4b01DQVFncGdqaC1pQmJOZWcramdBQjVKSitxQktLWTI1bnVnMDBJSFpOQ2JXV1dBcjJ6SEFBRTVmd1pDR2hIeGFIMjFoeVI0WXVSR2tiRENBMXpDY0cyeGF6czJwU256dXI4dnFBdjhGakFNa0thZmhtdWJFb0VvVGx1SWlCLUhFNGo4VjhiYnNONThpaGYyZ3FOT0swN3pvcTB5cXZ1bTY3b2NweXJoY3Ntb2FCR0dwRHhnblViUnpIdGV4M1hLSHhuQmlmcE5HME5hekRscTZvUTZiSWZyQnZTeUxvbzQ2YTR0NGhha3U1anJSZUFQbjBzRjRXWkljUU9JRERDWHc5eUtXaXBPMHFndkt5N0ZkVjJxT0RzcFhHdlYxc0RpMThtUlJ4dldjQWtnMkdTTnd1bDFOaEhTLUxvVUtZODZtSFo2LXlCc0NsaUpwa1ZtUlhaK0xPYVdnUGVmOFRiUTVGM24xcGo1VDhzTzZYRThsT1hVLU03T2JNejY2YzQxaGxoYWVoa2JjN2IwTlNmWmROQ0VJRnB3VnNHMGZYUGxTQ1hHLVF4QVVqajVrVWgwa2JMSEc2ZjdRVDRJSzJHWGU2MDNZa1JmVC12Y0tBQVFncDd3c24xWityOWd6Wm5mZ0FRaStxRFBPOXgzcndEZ2tHS3U3a3Y2UEJmaUtMUU1Ca0JmRFFRY0FJcjBManZVK2h3SkNRTi1yQW1Fci1ENklOZGhrd1pJQXowSEJ5TEcwLWpBNytCRGd4UUdiR1FqZzI4cjRIRTRjQW9LVWlOcTBPekV4VGdGeE1FUVRERWhldUJ4eEZvd1hJSU8rRlFINEgyS0hBS1JUWjJSU0piR1RkNldvK0NWeDBiZmZjZGdxVG5qc1FLTW1HNHR6N0d3Z0FjUnRKNmRFeEVwRytBaUJ3QUFJbndFRU1BNURkZzREaVBnVzV3TGRUc1ZVRUlheFJCdUNFUE1kbzZoUXJYd3FQOUtHbndXUUJBQk1SRUVzQkpEaElpQ1lFb2VSUlFzaWNRQWVYeENrZG9wQnFsNUF1Tlk0eS1nS2tSS2laSUFFNFI1alRCUkhZOElNNExoRENnSTZEZ253N0NvQ3VIOUJJTTRJallWYk52UVVHejNqRnpObUFXQURoSURqRlFjOWR4MjRPQmpTcEo4Q0lBUTVDWEF1VjhhdXl3UWpXVTJoY1E1NlU5bGhXNFNvV0FCc3RsYk5CR01LWU14WEc0QkFFY2IweUJNQ2dENEV3U1VCQm9YZ3BhSkNzaUJBSUNPRXdKK1ZBZUFJVlFHUUtpaUFKSk1Xbkd4VWltQUtLS3doT0pWK0hGeUs4VUVvTE5TMGx1TDhVVmk0RXkybDVMNlVWakdoeXNsRkswVWVENVN5Z2xKZytWTEUxRHhBZ2ZCanh6TWRJU2NZZkxwWFVISUk2UkFmQjRaMkRnQUFOMktGK0ZndVpDekZnTEVTdkE4Tk5Jc2hvbkFXR2FBV0NUSGtpQVc4R1pkUThnTk5DcDFucHRYVE8wTzYzd3ZnZ0E=" target="_blank">link</a>.
When accessing the assistant, a new simulator tab will open with the configured Assistant available in the button below the _Debug_ button.

To test your code, load the file (in this exercise the .c file) on the simulator and click on _Run Tests_ after selecting the Assistant tab.
The name of each one of the tests will be informed, and after some processing time, it will return either _Pass_ or _Fail_, which can be selected to inform the input, expected output and returned output for the selected test.
