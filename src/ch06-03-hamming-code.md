## Hamming Code

### Instructions

In this activity, you must write a program in RISC-V assembly language that performs the encoding and decoding of a [Hamming(7, 4)](https://en.wikipedia.org/wiki/Hamming%287,4%29) code.

#### Encoding

For the first part of this exercise, you will receive a sequence of 4 bits, and you have to encode these data bits using the Hamming Code. Assuming that the 4 bit input is given as:
</br>&nbsp;&nbsp;&nbsp;&nbsp; **d<sub>1</sub>d<sub>2</sub>d<sub>3</sub>d<sub>4</sub>**

The output will be
</br>&nbsp;&nbsp;&nbsp;&nbsp; **p<sub>1</sub>p<sub>2</sub>d<sub>1</sub>p<sub>3</sub>d<sub>2</sub>d<sub>3</sub>d<sub>4</sub>**

The new inserted bits with radical **p** are **parity** bits. Each one of the 3 parity bits is responsible for reflecting the parity of a given subset of bits (subset of 3 elements from the 4 available input bits). A parity bit is **1** if the evaluated set of bits has an **odd** number of **1**s, or **0** otherwise. The following table can be used as reference:

|  Parity Bit   |          Subset of tested bits          |
| :-----------: | :-------------------------------------: |
| p<sub>1</sub> | d<sub>1</sub>d<sub>2</sub>d<sub>4</sub> |
| p<sub>2</sub> | d<sub>1</sub>d<sub>3</sub>d<sub>4</sub> |
| p<sub>3</sub> | d<sub>2</sub>d<sub>3</sub>d<sub>4</sub> |

#### Decoding

On the second part of this exercise, you will receive a sequence of 7 bits that has been encoded. You have to extract the data field from this sequence, and also check if the data contains an error caused by a bit flip (there is no need for correcting the data if an error is detected). For this error checking, you have to verify the parity of each one of the 3 subsets.

The XOR operator can be used for a given subset of bits. For instance, to check the parity for which pd<sub>1</sub> is responsible, p<sub>1</sub> XOR d<sub>1</sub> XOR d<sub>2</sub> XOR d<sub>4</sub> must be equal to 0. Otherwise, there is an error on the encoded data. Do this for the 3 subsets of bits in order to check if you can trust the data encoded with Hamming(7, 4).

### Input

- **Line 1** - a sequence of 4 bits that must be encoded in a Hamming code using 3 parity bits.
- **Line 2** - a sequence of 7 bits that is Hamming encoded, and must be decoded and checked.

### Output

- **Line 1** - sequence of 7 bits that has been encoded using Hamming code
- **Line 2** - sequence of 4 bits that has been decoded from the Hamming code.
- **Line 3** - 1 if an error was detected when decoding the Hamming code, 0 otherwise.

### Examples

| Test Case | Input            | Output                 |
| :-------- | :--------------- | :--------------------- |
| 1         | 1001</br>0011001 | 0011001</br>1001</br>0 |
| 2         | 0000</br>0000000 | 0000000</br>0000</br>0 |
| 3         | 0001</br>0010001 | 1101001</br>1001</br>1 |
| 4         | 1111</br>1001001 | 1111111</br>0001</br>1 |
| 5         | 1010</br>1011010 | 1011010</br>1010</br>0 |

### Notes and Tips

- Exclusive OR (XOR) is a logic operator that facilitates the computation of parity bits
- AND instruction is useful to leave only a given group of bits set (masking).
- The decoded data doesn't need to be corrected, in case an error is detected.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14QUhwV0FDQVVRQThJd0VBRzFRY0E5Z0RNT2hZbVFxa090Qmt3QTZNS0FORjE1d0RnRlVBa25BQVNxUVFsUjBjSEFJSkVTNVNuQURLOVJ2SUMrSGNYVkZnT3lrQUE2VmpCUkFCTUFWMkVDVm1sN09VQ0FLd0lBZ0c1VmRRUk5iUUFaVVJvSVFRQWxWQ3l0VDI5ZmZ5Q1E4S2pVR0pwUkdCaFVHbElvWnFTVWtIU1lWUnBCYVc0ZUFEWTRBR1lPVkI1U1ZCZ3dnaHM3V1VjWEpXMVZEZzRtbURJNkNQYk5BQW9BU2c1Z0xlMkZDUE02TTc3cmpsSUFDeEpBaUtnT0FGNE9Wb0IzUFNHRXhtQ3pIQUs4Q3cwRWdpVWFCQ1lZRGhHZmhnV0RJRGdBWVhDcUFDcDBlMTJFOGpvcFd5UHorcUVCZVFLeFJKV2dlVjIycjNldTFhN1U2ZTBDQ0FpQkJleDJKWlZJZU5VRE9lYndJSHlnZ1FnWVRDY0RtWkhCTUNlMndDV0lFVUNHSFdhQVJ3SXUyY0IrQUQ0TG5ycnZ6c29GaWJJNlVLbGNydHNUU0JFNkVxbWVLMEswR0RRNEUxMWNJNVExU0dkNlhhbnA0ckthZE9Kb0lJNEtnSUhSQkFCUFJHa0E0aWR3aTIxUEVWdWlWU21VQmhXbWdJQUZVREhBQWpCeGpnQkhDS0I5bW5IV212UEVBVCsxRDF3cFFVaEpvdEIwMHFrQ1ZnQU1vOHJ5bFU0OHJZNG5VLTZ1Q0gxUm5jOG5xalhDOUhDNWJvZVZPbDlTR0pjSEVFUmdiT2FpT09FQndBQ056dDlqWG1hTnpTTDRmYjRqNmhyMVo3eHhNM3Uyek5udTJiWEhtbndGcks4cURvQjFUbG1RSEFBRXcxdldqYk5NMlM2d1cybVNkdDJnaTl2MjBHS3ZhdzdqdU9XNWtXUk82WVNSSzZVZVIwNVVkTzFHNnJCMndIcCtDYW9DZVo0WGpBVjQzbitqNmlzeXI3dm9lWEUtaHdmNEFmYXdGUEtCakppdm0wcFFZR3hIS21XRlpUSFdEWmtFMnU3MnRoSGJjVjJFUTluMkE0YWZhQVJrZXVNQXpuWkxITGdFczRUak9DNmJodXpsc1JjT3ljY2VwN25scS1FMW9KRDVQc3BMNWtPSkFYZmplMG5uTEp5cnlkY2lraWVLRUdxVlpKWWdQQjhnQUN3b1hwSVVZYXhSbktlMlFpbVhoQkU1YjVybXp2WmE0ZWNLTkVrWTFUV3poUjg3ZVcxNVVrUnhBaGNUeHdYc2dKZDRSUmxnVFJXK1lBZnNOeEpTVEpwcXBVQitKS2U4V1dGa1J1WDVSd0FDc3hWb1RBWld0cFZPRTFlWitHV2J0RFVqdTVua1RtT1k0K2JScm5QWTlHNWZRNWIyRGY1aTNjVUZmRVRVSmtXaVRGODBTVXRDVXJiQmEwY09sNGlhRFdoSWNGOHZ5aktrNk1jQUFQTDhZN1kxQUFEVXhQbkpjc0ZvM1FGQmhPKzBGa25tSG9XQkFjeFdlbG0yWlpLMlYzYlJBQUcrMEFDVEFGQTdpOHdORlh2RlZ1SFhYVlBPMFJ3MU1MSFRnWUFOcWpnQXV1TEpHSzdUODNRU3JsYWE4dTdIUTBEdkVoYURVM1BtSlVOeGN0U1hHNGp5N3BRQnViS1JCNGl3SVVjQldsRThpLUFhd2tVN1I1cGFKYXRLa0NyQVRRVDdEUit6MDZzTSs3a294NzdnaWtBUUczS21qeURVMkVJaS1LT1dkUEZBa2pIT0JLZUJySEJEeDJyaWNBSVNGK1RqdG8tQTBGTEw4RmVCS25jZnArS3dnd01ncnlPOGpkQ282ZzhnWTFXUk40MzhBNloranBQTjc1VHk1OUtJakU1M3lmZDFYYWNaeXJVRHE4WHlySmJSYS01MlN4em55SUFCVVZhanVjbkRIRzNnWUVBQXRKVzdQWEtmeXFoNlE0Y0NpamlBVDJNQnZiWHdDSW5YNDE5OFRMalJyZVFRb2hieGtqLW9FSm0xTldaLXhEQ0hDZXpvbFM4d0FPSjUxUUlpSVcxOTNDQkE0QUFFVkVQOEdBQ0RwUWNDVEtJWjB6d0t4LXk4RDRQd3RnWkFPSGtETU5vRVFRcDR3Z0J3RjR4SnhEZkNGdjhXQXROLWlCRjBFVUhJTTFpUXMxUUFBZVZ2SWtOb3BBRkU1R09QQXhCcHhQQ3lMb2FJYVUzd0FnekhHQk1BQjJRQWlHbU9JTUtBTkFBRFdvaUxDb0ZPTGpXSWhwQWk4MU5NbFYyZHBacXhVQnZiWU9CSUo3VEI0T1lkb3FBd2hrZ2dJRUFnUWhlekhBQU9RTG5TYWNRSW50MDVnbU9MMlZBZmhoSkZMOEkzYW91SjBwVTE3djdhU3lUVWxCa3lhb2JKdVNOUnpIdUlVdVlKVGpSbEk0QlVnSVZTczZPbHdkRTJKY3d3aEpGRUxBREpXU0h5LUQzbE1tWnpTWURaUHhPNFBvVndkYXdDREtpR0FWaElBOEdYazhFWkxvT0FBRmtXWXZGeVFnazRselhpV2hwcjRNNEhBNzdIRU9Sd04rSEE5bm5HSnQ4MkFvRWduYkIyWEtVUWNCYnd6SUFHNkZGLUwyQWdwd0lrT2h3V2M0NDBMQkFjRU5KaWpnRDl1NmlDY0dtTkV4eEVJNUtRR0VmRkNZZ3dRb3psWWRKbzVXa0VId2pRYjhiOHFYd3ZXY0tPMDh3bWo1emdDOEZFaEt3Z3N3Z0Fpa1VhTUVDVmlzQWdSQ2txSmhaM0ZaZlk0Z3J5QjEwK1J3V2wyU09BQUQwYXhLb2dBYlJPWHoxWG5HMVlxb1ZLc0pnR3JWWFMwNDZVcFVLdDFTcXcxMXF0VTZyTlloUzFScVhXbXVWUmExVlJyYlZURitNY2IxZXJEWit1ZFNhaDE3cncwYXNqV2EzMVRyc25wVk9YZ29XNHIzQnBzUWhtNEFEcU5iWm9RQk1iTkRyRFpGcmRlclV0UHJ5MjgzWmYwTzBhQXFDNnNjZGlFVmU0VTBjRjVrTGJscUFWYnV1elYybFdCVnkyZHV4Q3JBNlE3Z0Q5dEdGV3E0UUtkZ3ZEYUM0M2wtTEI1TnZ6aTJwNGFNYUFTcDJOS25Zc3FSUmJzdnYyaldNYmpVMW43ZEd4Tlo3VjNkc0hhZXIxazZQWFdxempRWkNRYisxaHF2UStrZGw2cld4dlBTT3NkOTZUV1B0UFMrd05BSDg3bXFmZittOUE2WVBYdjdVQnI5SUdSMVRyQXlLVXU1N3F3QUI4Y003bzRIaHZkNjdmN0lxVk9reXM2U3M0LXpiZXFtdFZ3Q0FUd3hIeXVnMWdnejdCd0RJbVlPQWFCaU9PZGNVdWhTRmd6QXhRb05NZ1FCNUR4ZUItYzRiYjlqRExJMkp1Z3lTSWkzbjJJUzBjbkhoTkhJNEg4M2pZOC1uN0JVMnBnbEs2dU04R0pwLVBvczYwR3FMWmlhUGNhTkJEYnNFTHU4UStFRUJaMmMwbmQ0SUszemdwbVhtYlpsQmppYWFyS01VNFZnQ3JWTGZkTlB6WUtJVXdITHNwWUxRWXd1VmdpMUZwR0htZlBpbFM2RnF3eEt2T3hiekZ5N0VTNndCN09RTWNWejZVc1BISGM0d0g0Qk1TTWJxaVkxaEE1aFpSVXR5NDhoWU95Q3NjQUFPeGYzcTY1bFdIV3VzQmRJSkEzNEZIc21JdXppVnlxVEdXTnNacTI1anpVMnFVMHVmUUU2WWdoR01PZG9xNTNyakhTRE1ZVE90MXpWaEp2eE9telN5alg4ZjQtelJyQUxrZFNPM0FHYzVtVlFRdFhPLVpnTlcwVlVUbUdrQSsyU0w3cFh6emxiNVpWd2x6bWpFTGlGb3pDZWNCRzIxY0IwTERyZ1BnZXRzVXdmR0FIMnJCZzQrMGZHZHFnZ2tBaEdOWWtNSExjQWdGMko3WkFtQlFDaUNZT3lBZ3JQR2ZOR1ozQUVnRUJyQ1lEVEEyUEFUT29ESUg1d1FDQUdKaGZwakY3emlYVXVJQ1VMbDZMbm5NQStjQzRBR0pxOVFBcnpYU3VCZjZEMXdiclgwdnptbTQxK2JpQVRncmZpOGx3TDNRVnY1Z1FIZ2R4QWdZTGVNTHR2S0lIZ1Z2UGZVSElLNHhBMHpLQVdEZ0dpaHNMQlJ3OENHOXJoUENmWmQ0QkJkNExzUHNLQm9CWUloQTZJQjNCNEFJRW1XZ2hSRHVzLXp5QWZPa0xuRU5ETCs0ZHdRQQ==" target="_blank">link</a>.
