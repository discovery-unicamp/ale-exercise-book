## Number Base Conversion in C

### Instructions

Write a C program that reads a number from the user input in either hexadecimal or decimal format and converts it to binary, decimal, and hexadecimal representations. The program should handle both positive and negative numbers.

Your program must read a series of characters encoded in ASCII format from the standard input (STDIN). These characters will represent a number in either decimal or hexadecimal format. Below, you will find the necessary functions for reading/writing information from/to the standard input/output, along with a concise illustration of how they can be utilized:

```c
int read(int __fd, const void *__buf, int __n){
    int ret_val;
  __asm__ __volatile__(
    "mv a0, %1           # file descriptor\n"
    "mv a1, %2           # buffer \n"
    "mv a2, %3           # size \n"
    "li a7, 63           # syscall read code (63) \n"
    "ecall               # invoke syscall \n"
    "mv %0, a0           # move return value to ret_val\n"
    : "=r"(ret_val)  // Output list
    : "r"(__fd), "r"(__buf), "r"(__n)    // Input list
    : "a0", "a1", "a2", "a7"
  );
  return ret_val;
}

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

void exit(int code)
{
  __asm__ __volatile__(
    "mv a0, %0           # return code\n"
    "li a7, 93           # syscall exit (93) \n"
    "ecall"
    :   // Output list
    :"r"(code)    // Input list
    : "a0", "a7"
  );
}

void _start()
{
  int ret_code = main();
  exit(ret_code);
}

#define STDIN_FD  0
#define STDOUT_FD 1

int main()
{
  char str[20];
  /* Read up to 20 bytes from the standard input into the str buffer */
  int n = read(STDIN_FD, str, 20);
  /* Write n bytes from the str buffer to the standard output */
  write(STDOUT_FD, str, n);
  return 0;
}
```

### Input

- A 32-bit number represented by a string of up to 10 characters, followed by a newline character ("\n").
  - If the string represents a number in the hexadecimal base, it will start with characters "0x".
  - Otherwise, it will start with a number from 1 to 9 or with the minus sign (-), indicating that the number to be read is negative.
  - Note: The minus sign (-) will not be used in inputs in hexadecimal representation (e.g., -0x12 is not a valid input).

### Output

After reading the 32-bit number, you should print the following information followed by newline characters:

- The value in binary base preceded by "0b". If the number is negative, you must display the value in two's complement representation (as illustrated in the third example below);
- The value in decimal base assuming that the 32-bit number is encoded in two's complement representation (In this case, if the most significant bit is 1, the number is negative);
- The value in hexadecimal base preceded by "0x". If the number is negative, you must show the value in two's complement representation (as illustrated in the third example below);
- The value in decimal base assuming that the 32-bit number is encoded in unsigned representation and its endianness has been swapped. - For example, assuming the 32-bit number 0x00545648 was entered as input, after the endian swap, the number becomes 0x48565400, and its decimal value is 1213617152.

### Examples

| Test Case |   Input    | Output                                                                       |
| :-------- | :--------: | :--------------------------------------------------------------------------- |
| 1         |   545648   | 0b10000101001101110000</br>545648</br>0x85370</br>1884489728                 |
| 2         |  0x545648  | 0b10101000101011001001000</br>5527112</br>0x545648</br>1213617152            |
| 3         |  -545648   | 0b11111111111101111010110010010000</br>-545648</br>0xfff7ac90</br>2427254783 |
| 4         | 0x80000000 | 0b10000000000000000000000000000000</br>-2147483648</br>0x80000000</br>128    |

### Notes and Tips

- This exercise challenges you to apply your understanding of number representation and conversion in C language. It's essential to consider edge cases, such as handling negative numbers, when designing and implementing your program.
- Note that the code for the write and read functions contains assembly instructions for the RISC-V architecture; as such, it is not possible to compile this code (as it is) for other architectures.
- You may assume that all input values will be small enough to be encoded within 32 bits.
- For printing the signed number in decimal base, we recommend:
  - Check if the number is negative by examining the most significant bit (MSB).
  - If it is negative:
    - Print the "-" sign;
    - Print the negated value of the number (consider the two's complement representation as discussed in the theory class).
- The RISC-V simulator stores data written with the write syscall in internal buffers and only displays the content in the terminal after encountering a newline character ("\n").
- In debugging mode, the terminal only accepts interactive debug commands. To provide input data to your program, you must use the "Standard IO" feature in the "Operating System" tab or the "write-stdin" command in the terminal.
- We have identified two minor issues in the simulator. For now, we have updated the example in the prompt and suggest considering:
  - The input "-1" will not be provided to your program.
  - When using the read function, request a larger number of bytes than necessary (for this exercise, we suggest using the read function with n = 20, as shown in the example).
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14QUhwV0FDQVVRQThJd0VBRzFRY0E5Z0RNT2hZbVFxa090Qmt3QTZNS0FORjE1d0RnRlVBa25BQVNxUVFsUjBjSEFJSkVTNVNuQURLOVJ2SUMrSGNYVkZnT3lrQUE2VmpCUkFCTUFWMkVDVm1sN09VQ0FLd0lBZ0c1VmRRUk5iUTRBR1ZFYUNFRUFKVlFzclE1UGIxOS1JSkR3cU5RWW1sRVlHRlFhVWloV3BKU1FkSmhWR2tGcGJoNEFaamdBUmc1VUhsSlVHRENDR3p0WlJ4Y2xiVlVPRGhhWU1qb0l6czBBQ2dCS0RtQWQzWVVJOHpvTGdkdU9VZ0FMRWtDSXFBNEFYZzUyZ0IzUFNHRXhtQ3luQUs4Q3cwRWdpY2FCS1lZRGdBT1FpWUFBUmhZT0FBaFFnaUFEQ3JRQWJoWmlLME9MQU9BU0F1ZG5yZGhQSTZHVnNuOEFhaGdmbENpVVdWb25qZGR1OVB2dDJwMXVnZEFnZ0lnUTNxZG1lVlNIU0JSeDJOd1lCQU1jSUZBQlBXaEZRUXJDaGhCU29lVHZFUUlIeklPajhCVGtHZ0FhMlZRb0lrdVpZVlE0bGdxRENjQWdkR1FLMytBRzBBZ0JhTU5Bd1JRREVCS3poc01FVTNNNUJ4Mm9FQkMtQUFNUEFBN0FBeFF1Rm1tNFdvUmtnUU5NQkNBME1KZXNBRUNJQkFDNkExVXl2RUVSZ1lvcE1IUkZpZ05EZ0xRRS1wSXJWT1BDczJzdTF4Z0wxMmpJVVBEWlBFQ3BBWVlBdWdRejBkSXAxWXltVWRBQS1FZVlLeHpvRXZZSUZvOVRLZ3dJdDVMOEFIeXpZUlB5aEsrY0xwY0ViVTJXMWRkTjIzWGNvSDNROWp6UFZSTDJ2S0Jid2hCOHZ4ZmQ5a09mSDlsVjJLQkpGT0FnMTJFR0JrSGVEZ0FFSi1nQUZsbkxEYm1aVWdJam9lZHhDS0pONlJlZHgyMS1GNGwyUU5rczBDTE0yeTRobFRRNE9nMlZEWVNYbFlBQTlMTU1XRExNd3ltWnNBR29BQkpXQndHamRsa3NNVDBVc01BRTQxTTA3U3BOdVdTYzBNb3lJRERjUnJERGZOVEswblNWUmtteVhKbzF0T0lYTHhOQTRVNGx4K2Y1Qk1wRGdBQjRPQW8xSktWVTFUcUlzeGRSTEFGZC1udzRNb0diUUpJRklHaFpUb1RMbXgtUHpzTncxS09BQU1rcTVjaXIrWDUtbFN4VGlxdU55eXNDdEZNUWhES3NzdUJyLWs2ckZIZ0FvcnprUzBxRjE0MVRRc0NBQW1BQldOalNvNHBMS2hvbGFhTG9oajUxNC1xT0NtQVNsbzI0U1hTK0tCQWdnTUpmUVdNaElSQUlrQkFRaUF1bGFOTTREK2Q5Z0hsYkpBbVpXUStUcE1UVFcyMTRQbGROQjJnWUljUndRQkRVRGdHNzkzT0o1M0NzWUJtSVF1QlVIOVFSdFdSRGNJbFFkd1N0dVU3dmd1cTZFYWFmY2FJQ0FBVmFuOXNDZ0JIUW15SEZjNDR4bzA3aUFFWVFzZFpvb0lPMUtuYnJjZ0o1b28rYUFEWUtJQURuUExuVm9DZVNwaXpkV3N6VnRYTmExcVp0ZlZ4WFZFbG1YNWNObUFjemwrYnhsekxNemFtT1c1WW8rV2pOeldhRmZiZHRjRGNuUVlmOWVITzI3RjZZR1JQc255aDRkZkNRQmdDQXBGYS1NNTRTU2NGTUd6b3A2N3FjaEN6NmNaMmFXYlpvUE9hOWl5ZWN5Zm5VRUZ2Y1JjUnpPSnBWbmhqZGw5M0JpTDJ1UUZWeldPLVZyV2RhNzN1RFk5bUI1dm0yYmN6MTJhelp6QnZUWUhxWlpxbWNacGFtVWZoN05wV0pwOXlPLWJnQU9lMkRnRiszRDMzbzlqbWlFNWVKUFFjK2NuTHZUc1dzNUFCbXlBNGNZOCtwam0xNFhFdStmaDh1SWlGMGdxNFozRmlBTU1VOG00Zno4aXJERWVzWUd3SmdUclBXSGRFR2QzMXJiQWVvQ3BhTnduandjUXVEY3cxaU1tZ3dZcWhab1VSSGd0Q2l1WTViakZYaTNVcUc5UnpNbTNsMlhlSWNENkRnam93OGM4NDQ0TGpQcmNDK1pOem8zMUZqVGUrajk1QVVWZnV6Vm9oZHpKK1Mta0lIK0ZkaGFpSnJxVk91Y3NOYmFNVm5ReUJiZG9IYUtNY1lreHBpaUhuakRIUFNoOHNGN1QySWViSGdXampGMnpkclErUjlDOWlieVlUdklPYkN3NGNLUHR3dGFGbCtHN0VFU25hK2xOcTYwd2ZvemVhRURTWXAxNWtvZ1dmOUs1cU9BVG1YTXVDY200TjBlNC1ScXM0SEZKS2FVMkJac3JHNWhzYkxYTTJEc201THlRUE1oUmtLSkdXbHFQZHBianZhZU1ZZjdGaHZqOTcrT2hsNG9KdkR6N0tuQ1ZmWVJVU2dIaU1adExCSnlkUGpKTExpb2dCR1RsWnR4d1EweHB6Y0NrTGlnV1VvNXh5OVptMlV0Z25adXp6ek5OYWUwMmFSbDRrRDBXYmNCaFVjK21CM0ZINGdjd3l1RXh4NGFmQ1pTMGhGcHcyZm9pUkhCYWw2TVNjczB1eWkwbXFPaVpzbk1zMUt5ZTMyUzhRNVNEekdxRElkZ2xGWnNiWVVWbHVNTE1yc3VtclZlVnZIeG56Qm5mTTRWSFVaQUxFNUFvaWRNMitZaXdXTXdWbENwWnJvVmx3di1vQXUrcmRjVm9zeVlZN3VadFJYMk9SYWkreGhMaVdrdkhrOG5sTHllbHZPWVI4MW9YekQ0akwrY0UrT2dMblNzcEJZaXpsVDhqTFBNVWFzK0Y2eXpVYUpBZEs1NXV4RGtuTGRVZ3RXWnluV3FCekRzc0lDeUI0TDFKVnJDaTR4TFVxdlJXcW8rN3pXRzB0MWI4aytJU2pVblJOU0krMUdMWWxQMDlhcTYxQXIwbnBvT1ZzcDFxcVhVR05RWjZnZTBzQTB5cDRONm1BaURYWnRJV3RXLUozVG8yYXRqYUhPbGdUOVZqSUVjbTQxVXo0THFrRUhBUDZVUVh3Y0hlbStWcUZsdnBhRityeVVnb1lRQ0l6SFUwQ2RmUm14c21CV3U4ZHQ0Q0JMV1N2SWEwbDBSQ2hTUFpTWEN1N3FicnNiQWU1cVpGUXJqVktrdWVBaU1neVgxZE9UUGRHNkQyQkVJc1JONGJseEFCU0NxSkVLKzFZby1DaXUrNm1oNjRvSlZuUk5YWXA2UFFjR21sKzFPdjc3MmtBSUVWUzl1dyswdkRRK2V3S3BHT0FBQ3A5cFprdUp3VTRjR3lBRUdVaGZJam0wbDJMb1ZDdXIwSTY0Q2taYkd5VWpRay1KTGsxS0lERWJKNTJrRUNCREN3ejE0WlNmNUhPNEdqRU9BQUFNQURpTm9QVEluVXNBVWo3aEFnY0FBQ0tpRUJEQVFRb2hMb2NHMUtJQmlyeEdaU2E4RDRQd3RnWkFPSGtITURvRVFnNUF3VkpGQ0FIQTNqTW5FTDhQVGdKWUJoRE00RVhReFJjaUJIb05qQllBQjVERWlRT2lrRmk3a1U0WW1NVG5FOEZGOHpsbkxxLUFDSE1TWUIwcE1CRmZLY1lZZzRIUkJZc0tnYzRFVllpdmtDR3A1VXgwMk13R09rQ01ZRldsT2NWd0NBZllYcGtDWUZBS0lKZzRvQ0NUZEc2MGNiY0FLeldFd0FUVkFlQXh0UUdRTXRnZ0VBQ1JyYU9CdGhiTUFsc1ZtTTRkd21tM0Z2YmQyeEFmTWwzanRiWjJ4V2ZRajNydW5kdXhXQUFzdTlrN1oyOXRPRCs4OXU3dWctdUxBMVB6R093NDNnZEFkQmlVUVBBLXZROWtJNlJBb2hZQjNqZ01TSW9oTVdCWktMTVdFYm1QdDdNbVptT2lnYUFXQUxSQUtqRUFBRTlTQ0FOSk51bkhwaVNEaWFDejl3N2dnQQ==" target="_blank">link</a>.
  - Simply select your program, click on the assistant icon (small eye in the top-right corner of the screen), and click "Run Tests."
