## Square Root

### Instructions

Write a program in RISC-V assembly language that computes the approximated square root of integers.

To perform read and write of data from/to the terminal, you must use the read and write syscalls (similarly to exercise 4.1, but now in assembly language)

_read_ syscall example:

```riscvasm
    li a0, 0  # file descriptor = 0 (stdin)
    la a1, input_address #  buffer to write the data
    li a2, 1  # size (reads only 1 byte)
    li a7, 63 # syscall read (63)
    ecall

input_address: .skip 0x10  # buffer
```

_write_ syscall example:

```riscvasm
    li a0, 1            # file descriptor = 1 (stdout)
    la a1, string       # buffer
    li a2, 19           # size
    li a7, 64           # syscall write (64)
    ecall
string:  .asciz "Hello! It works!!!\n"
```

### Input

- Four 4-digit decimal numbers separated by spaces (' '), followed by a newline character ('\n'). The whole input takes up 20 bytes.
  - String Format - "**DDDD DDDD DDDD DDDD\n**"
  - **D**: a decimal digit, (0-9)

### Output

For each 4-digit number read, you must compute its approximate square root and write its value to STDOUT using 4-digits and each square root must be separated by a space (' ') and the last one is followed by a newline character ('\n'), so the output will also take up 20 bytes.

- String Format - "**DDDD DDDD DDDD DDDD\n**"
- **D**: a decimal digit, (0-9)

### Examples

| Test Case |        Input        |       Output        |
| :-------- | :-----------------: | :-----------------: |
| 1         | 0400 5337 2240 9166 | 0020 0073 0047 0095 |

### Notes and Tips

- The usage of [Babylonian method](https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method) with 10 iterations is recommended. Considering that we want to compute the square root of a number y, the basic idea of this method is:

  - Compute an initial guess for the square root:
    $$
      k=\frac{y}{2}
    $$
  - Approximate your estimative, k, to the real value of the square root by applying the following equation:

    $$
      k'=\frac{k+\frac{y}{k}}{2}
    $$

  - Each time the above equation is applied is considered "one iteration". For this exercise, use 10 iterations.

- For this exercise, approximate solutions are accepted.
  - Solutions with an absolute error smaller than 10 will be considered correct.
- Other methods to square root approximation can be used, as long as:
  - It used only integers. Floating point numbers or the RISC-V square root instruction cannot be used.
  - The approximation is as or more precise than the suggested method.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lIZ0tvQkpPQUFsVUFHd1NvNk9IZ0VFaUpjcFRnQmxlbzE0QmZIZ0RNNkhNRHdBNklBSFFCNk1Cd0FtQVZ3bW9DbHdzVElWUzVnRllFekFiaE1ZTms1dVBnQVpEaG9JQ1FBbFZGRFNYUU1qVXd0ck8wZG5TeG9PR0JoVUdsSW9QSjgtRUVDWUlKb0pOeDRBVVFBUEFEWTRBRVllVkViU1ZCaGJBZ1VsRDFVTkJpWStJSjRlWEpneU9uc2lyZ0FLQUVvSm1DbXBnbnRwT2xYS3paNVNBQXNTYzNzb0hnQmVIZ0tBZDBFUmNTa1pKYk1tbVJvU1ZCNW04emFNRHcxQUJIZXdRT2ctV0ljRGlrTXdyQTZiSnk4Q0dKYTYzVkFQU0xST0lKTGlrZmFUVFluTTR6QXBGRXF6Y3dJZXdFWTVMRkY0K0ZCUWxUWWtFYzVRY3dRV3kyT0E5TWh2RGFITklBWVNNQ0NndFdLZVRNT0JabXpnMXdBZk90aFpzR2R4ekJDUE53Q1VLMVJEU1BZNkJzMmVZMEFVR0RRNExsMkpMVUh6blBpVm5xMWJvNVBLcHZ3OU5BSkhCVU9DSkFCUFFHa2VZLWJUeXBuNjB3eHMwWExrOHgwQ3oxcEFBcVRwNEhTV29LZEZKV3N0VFp1STdDYy10Qk1TZ3BDRHlmeHFhbVpnQURBQVdSdU5uZ0FWZ0F6RjJBT3c4QUJNQTliUEFBbkcxbXMwVE16Y1BXMG0yQisyMjcydXp3MjgzKzIzUngzcDFWWnpIRHZ4YlVnSVhBOVBZWU9TOHFIVHV6aitDSFFSZ1dGSXdlZUFXWTlIRHZIT2R6ZWZ5NnpmTXdNeklRZFpWak5WaXhDTXRVQXJDUXF4ckFEQlRWQnNRRWJQc0IwSE5wdHg0WnNKd0FEa0hjY2R4bk9VMzFRdHRzTFhGdG1tbzVwbTJvN3RkMExjaStIdlU5ejB2YVVZQnZFbHhRZmFobnlTVk1QME9MOGlWdkRsRTMtSjFrT0ZZRE15N0ZqSU1ra3NFQmd1Q0VOck9TMVRNQWN1MGJURDhJN1VkVjJiWWRDSmJmQzJtWS1jVVBuRnROMGJVZE1MYlpvTzJvZ2NiTkl1ZGdIWWgxT0t2SGlqa2stekJPNFY4MVZFelp4TlpTU0V6LWJUVXdVMERtMlU0VW9OTEIxWUxCZURxeVMxaXpEYVh0RzBJMGRyTm80eXFPYmF5U0wzTWo3S2JGc09pM1VkcUpjdWpSMXNocVVMOC1pT0l2SUxlTHZmckh5RXlMaFdpcVpZcENzNEVxVEpEa3BBRURlQjNPeU10VTZEc3MwLUxGc0trQWV4TXRjQnc3VENoMUhCalczUTdxNXlhanNuTGFEejF5YzVvbE5JaURlckN3THVPRzh3d3FmQ0tSS2pCRXBqMExnZUNXSkVlRXVHNW1uOGFHZUFBSGh1TnBHM2hxQUFHb01iV1lCVXlodWdLRnNJeGF6Uk0wTFJrQ0FlbTBtYTRybTM4RnRrdWNBQU1WcDRBQVNZQW9HMEptZXBVczQxSTAzS3RMMit5cGdKdnBpWUFnQnRSc0FGMWVaUThXaWJBV3NwYmFlVzV5OUw3QnArMmFSdllBU0FlRTFqcHJuR2JYM2xIOXpEMFdBWWpnYlZIRjRHNUZTdUZWY2RZalV2RTlxV3pBQSszbkVkOHBaZEorTE9UOWgySkZJQWdRZUZLSGtBSjJ3Zmh1Tkc1eWdQUUlhdDhPQThqZ2daZURnQkNaT2NjMW5nb2ZnQUNCaHVUT25YOTdZYy1NSndZR1FFNFM3QnVnSWFobUdzM1JwSGJscmFQb2F4NHVUYzJlUHVSK0RHcTlEOHdzN3JxT3BhZ1dXWTdkRXV4OFR0RWxqWG40QUNvczBiTlpMQWg4dW5RSUFCYU5vYWMyQ2FEVnhUVnZiTUcyWUR0cmV6R0RtNHQ0Uk9jb1lBSXdrRGh2N1JKN2MwdlFLWlUwOXE2UldxQWpRbWg0RXpBQTRnblZBZ0lPWmIyME9ZSGdBQVJEZ2R3WUItMjVEd0lNSEJqUkhFeko3ZlFoaGpDS0hjQ29YZ1hSQ2oyRzRrakNBUEJqZ1FqMEZjRG1keFlCRXp1T1lBUXNSd2gtUWhKVFZBQUI1YiszaENpa0g0ZUVKWXY5LTRyRjBEdzNCSEJ1UlhETUYwVm9iUXRTMzFoQ0FKVVN3YWhRQm9BQWF4WVRJVkFLeEVhdUNWT1lKbXFZSm9XeUZFcldBK0l3Q3dEa0pBUm93OURpR21OQnNBQXNwVFk0MXMtN0xDQ1NjTFVoTWpDckI0THZKWVhpZUNueDRPNG1BYXdNWXBOZ09KSnhVeC1wQ1NXSTBPUVFZZkdiRWFHaVJvTThHQmdGV09ZQWc2a3F4TEVzTk9BZ0dOTEF6U0RHaUlNbFMyQTFMcVhsUnB6VFdrelRUZ1VodXZSbTdIQjRJWFhDYXctRXdKOUJJQWdxQVk1dHc3bEFoR3ljZTZJMXd1akllcXBoUXpGQWpJUXc3Y2JnUkpDUkFiK0JBQ2tMMkRza29NdHpMNGpKSUFBT1FnQzhwWXh5dUJyQUFENC1NNkhRRTVQQVZTbzFtVkEteCtnWWhMSmp0ZkhnY3pUVGhnUkRrbmc1TUNaVXlRaVVxWW5jWURVaWRta0FJOG9vWkVOSUxpdEVaaHlVeG5sS3N5RzZ5dTVvd1J0czVzdXlNa3JIZHZaS0dBQTNHSUljemd1TW9Fc1JzY2hVWnRrdmxNV0FwTEo1QWpETEFaQVN3dVVTQldGU2JrYWh5QzZtYkhJQUE1STJEVjZTZUFhcjFjdlRZeEtKVTNCVlF3SnVTeHpsYWlJWDBTMXdUYW41UGxTc1oxU3JiQXF2QlBpZFZlcnRXNnYxUnFtRjhwNFU4QVhqaWhodFQ0STBGUUFLdVE1OWZXN2cxWElZMVlhQ0FScWpZS3BKRjhlQVpJMWZHcGV6SWhTdmljZmNCb0xSMmg2bnpiZ0VBTXdiYklFd0tBRGdUQUtRRURyVld2SU5hNEFrQWdQSVRBWVo3Q29Ed05XcUF5QU8wRUFnQ0tIdDRZQjF0cUhTT2lBR0NKMTlxblRBZHRuYUFCaUM3KzJ0dVhUT3p0UWdOMUxwWGFPZ0orNnQySG9nR29FOWc3aDJkb0VDZTNvbHl5d0VBNERhWTRoUVRIZnc0STBFOVQ3cURrRk1ZZ0RncmlaQndIbFgybGdqWkdpOWxYZEI2RDQ2OEN1TFBCQ1lFOXNLQm9CWUNkRUEyZzhBRUNETFFHSWl5NjFZWkFJbkRseGpuQ0VlME5vSUFB" target="_blank">link</a>.
