## Image on Canvas

### Instructions

In this activity, you must write a program in RISC-V assembly language that reads an image in [PGM format](https://davis.lbl.gov/Manuals/NETPBM/doc/pgm.html) from a file and shows it on screen using the canvas peripheral.

### Input

Your program must read a file called "image.pgm" that will be in the same directory as the executable file. The _syscall_ open can be used to open the file (an example is shown at the [Notes and Tips](#notes-and-tips) section)

Some examples of PGM images can be found on this site: [PGMB Files - Binary Portable Gray Map Graphics Files](https://people.sc.fsu.edu/~jburkardt/data/pgmb/pgmb.html)

### Output

Your program must show the image on the screen using _syscalls_ to the Canvas peripheral. The Canvas must be adjusted to have the image size. The available _syscalls_ are:

| _syscall_     | Input                                                                                                                                                                                                                                                         | Description                                                                                                                 |
| :------------ | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | :-------------------------------------------------------------------------------------------------------------------------- |
| setPixel      | **a0**:pixel's x coordinate</br>**a1**: pixel's y coordinate</br>**a2**: concatenated pixel's colors: R\|G\|B\|A <ul><li>a2[31..24]: Red</li><li>a2[23..16]: Green</li><li>a2[15..8]: Blue</li><li>a2[23..16]: Green</li></ul>**a7**: 2200 (_syscall_ number) | Defines the color of a given canvas' pixel. For gray scale, use the same values for the colors (R = G = B) and alpha = 255. |
| setCanvasSize | **a0**:canvas width (value between 0 and 512)</br>**a1**: canvas height (value between 0 and 512)</br>**a7**: 2201 (_syscall_ number)                                                                                                                         | Resets and defines canvas' size.                                                                                            |
| setScaling    | **a0**:horizontal scaling</br>**a1**: vertical scaling</br>**a7**: 2202 (_syscall_ number)                                                                                                                                                                    | Updates canvas' scaling                                                                                                     |

### Notes and Tips

- To test on the simulator, you have to load your program (.s file) and the image file (name "image.pgm") simultaneously.
- When new files are loaded to the simulator, older ones are erased, so you have to load the program and image files together every time.
- To use the Canvas, you must enable it on the simulator. To do so, go to the tab “Hardware” -> “External Devices” table -> “+” Icon on the Canvas row. A new tab will appear where the canvas can be seen.
- This exercise uses multiple _syscall_ numbers. These values will always be stored on the register a7, and the _ecall_ function has a different behavior for each value. To check the syscall for a specific functionality, the simulator table can be checked (note that the _syscalls_ related to external devices, like Canvas, are not shown in this table if the device is not enabled).
- You will not receive images larger than 512x512 (that typically takes up 262159 bytes).
- In all images, Maxval will be 255.
- The canvas is indexed starting on 0.
- **You need to resize the canvas (setCanvasSize _syscall_) according to the file header.**
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZVlCNWlNQWNJVWk0NFRNb0RjVWM2SGgxOVF4TnpLMXNISnd0YStzYTZJdE15Z1BaS25naVlBRGRDQk43a2kxUUFEMUpVR0dJczV4dFVSYWdhWVlYbGdrbVFmMzhhY1ZjZUFGRk5nRFk0QUJZZUxaMllHd0o1SXAzQ3AxQXdtTUItRHg1Z2RTSFE3SGt1QUFLQUNVRUpnVUtoQkRzVWpvS09tR0o0cEFBRmlRekhZb0R3QUx3OEhJQWR4NFFsRUVoeGlOTUwya05CSXFCNHJ6TUh3d1BFRWtEUVBDeVBBQXdoUkxxWmtkTklSakhMdzJNZzREc3lGU2VJUUFKNHdHZzhPQlVnQjhmSGxCTVZQR1ZHdUpwTFFPVG9EVlFjRG9memdiQlFxRHhwb3hvd2U0MmFXVmhISGEwak00ZzRFQnNjRHBjRjBVRWNpT1ZBRzBBQXdBWFZsWHFoVUYwaUlBaElpSUxUb0x4clZjNGZBZlEwa2NpYTJpQ1FUUzJTb0tHT01oV1NBQUhJY1BSeDdrRUNTNUhZMkdYNCt0UXh0aHR1bUxzOXh3MUFkNVZERGtBWjlGam5oMFZDa096T3ZTUmZ1amdsYVRPYW90UVhpRjR1RWtsWE05VVhSTkRoMlVnSVorSTRCZ0FqSURDbWZqOXpwa0J3Q0NtTEl1aEVnS0FCTXNqNUdBcUJQcVFHQUFNekppaHlaYUt1WTR0T3FtNVl1SXZEVWhjaEJtRzZhQUFDSU5CQVpnMkJSaDRZdG1pS0VWY0pHb09SNUJVUlJvYTdNZ3hJOExtMUpKZ0FqS21BQlVIeW9pZTQ0M2syTFp0Z0FCb0l1cGNKdWVROEtvVUFBRjZvQUtBQWt3Q0NhbU9oOFR3dW1NY1J3b3NSeDFGc1k0TURjVVNXaXlSaDY0VHEyaUx5WXBkREtid2FtYVRwZWxnTWdpWkNZWjFJbVZLUkhNYXhsRldaUk5sMlE1VGxqcHUyNjdybys2b0xSVUxIbXVEWlNZQkNEVUd3WXpWcGwxNmtwT2NEd2ErcENlamxHSVBwMGlMbWhTMUxKaVVGbzhBQVBCYUFWQmFtN1ZRQUExSU55SW1uVkJMMFRoRGlrSW1VQ2lhbXZIOGIxRUdwck42WjF1dWtta3VTTWx1UXBtU2VZT1BBQUFwUUpzRWgrVkFDV2xibDVXdWU1QjFlU2RaMFhjWmVuWFJKR0xKVHU2SnBlSUI2ZmRsWTVBLVczMjdyQ2Rpb0Y2SU5RcENYcm1wdWNRYW5TUEJoQkUwU3hKVXRXM1ZjTFE1SGtCUjdHWXI0RUVTaUtJNVVpVmxWY0NDYmtjc1k1SkdFQjBNZ0FMVW9tcGdBTFNjM1M0aFFBQVJpQmZUYy0yc0tvTWdRdW1BUUNDVXNtbXdBT3dBR0xLOHI0cVN5QTNNa0JBNnNRRFFOaXhwK2RpbVAxWHFOanRFYVJtcU5VbnFZNHFHQWdjWU5JVElFbmdhbExHaHRTV1k5d1pnNGVRM0RZK3VZUG9vMnRyU0tjLXJzTDJxcE9EVnlLQjBlUEN5Q2UxUnBYR2NDb016NGhhZ0tFUGNqRFBCVTJiellXekhaRHRnQUtySFBBQ1VMeXBsNlFSZFNlYk5pVzdIbGZWeEJkY0JRM1RmYlNYcmNOeDM2cUlkM0twVzMzVnd0MjM1ZW1GWDZvZkdQdmUwY1haaWwxYncrOEFBckV2RTl5blZxOE01RVRwT05OR3B1NGFudGZkN25nVTl3SE1nRmJKKzRhUXhRTGRTcTlQMU5lRUVLVjVySVBhSTRHbzJvbm16RHdSRW45WTdQMm1nUUZNQzBqTEpsR2xmTTBXNGFRTnpadFRhU1g5VDQtMDRyWllrbjBHcmdPYWhxQVNBMHVwb0t0ci1DMHcwa0dmU2hBQWlNM0pCb2YyYnMyYkJMOVlGUUJOdU5ERUJjQ1NNS0FkU1JFZ2p1VENScm9nbmdGaHdId0NvWnpBU1ZNc29uanZyZkcrRDhqN2lEZ0tJNDJHcFJGLTFRZnpNTS1NTlFxTE1HSGUwT3dUNXhBVHRmRks2SlpJQUhGQUZhVGVxSXJRWmdlQ2tRNExTR0FZWUl3OEMxRStUb1ZzTnczMVdFWUJRYmhsQzhDMkxrWjhoTXVvUUI0RVNUY3VoS1M2VnBMQUd3M2l6RDhDaUNFTXc5Qk00N0FBUEw4eThJT1BKSVJFU0dJNFB6WkVPaHNrK0w4VFlTa3BndGp2QStMN0crcGhEUU1UNWpRQUExc2s2UXFCa1NkUmNJYU13c2xvYnlteXZLY3hEb25RdW1ZaWlLK0ZocEZFa3prY09nOE5VR2JDdEZKZTBmeFlBMVFFc21XUUVGRUY3TjRGcVE1cEpqazJGT1lpYzVsenJsMVhORnNwaGRCcUN3ZzFMSlk2TzktQzZVMkRvWFNXcGp6K0FnbHZJRk1BWmtmTlFWOG5aeU5VRDBpcnRzSjRpa2RudG1mTG9UbUFBT0dVWmhkaVpDT0lpSkYwaGZsMENwdWFHS0tMNlQ4Rk9maXVRbmtJQmFrUkpzWVNXb3FaRUthcWdscVBBMm9kVzZqRlBCZGtCcTBMR21PR0thMTdsbGdvRTh5Z2lJTG5RcTNsVEF1NXBhbkdPcENqQUFRa1l4RWlZS1V5QjRERlZNc2hnQ2tDMUZJQVVwZ0lBSUFRQU1wMldRTERoQjJLUVRtWkJOd1FEQUtZZEN0RnpTeGpuRHExRlBCRmE5a05WcTgxZlJtTEUyUUw2bGN0Rmc0OEVURUcxQXNoT1ZhbGtHYTBjOHkxeVBPZVdBV0FzaElDYkRvWFZaTkFCWkJvUkl6QzZEREVpYXR4SmZZS3NNQ2lIZzRqRVNscDRKekhnUmIwU0RScnFOUWQtYW5KNXJ6U2pGNG5TOFM0QkFDMFdNeUJNQ2dDQXZrQTRTNjUxWkFYYTZBZ0VBNUNZRHpuZ2VkVUFWUmEzRlB1dUU2YU4wd0MzVnJVaTU3SWFIczNjZTdkRUJGYjNzdlVlazlPN0JEdnNmZGU1OVd0SzItcXZUZW5kcWhnT2ZwZmZ3WUR1d0lDR01kQVFEZ3pRdGxEUDVod1RZd0hFTy1OMW9NeEFIQlRtVXVXT0lTR0xBNVpLeFZvck05ZUJUa3hrM0FBUnlkQlFOQUxCb1VnQzBIZ0FnV3BhQ1JIK2t1OWpJQWpnbkRPQVFkZHBrZkRyb0lHR1pnR0JvV3ZDMFBKclFRQQ==" target="_blank">link</a>.

_setPixel_ example:

```riscvasm
    li a0, 100 # x coordinate = 100
    li a1, 200 # y coordinate = 200
    li a2, 0xFFFFFFFF # white pixel
    li a7, 2200 # syscall setPixel (2200)
    ecall
```

[_open_](https://man7.org/linux/man-pages/man2/open.2.html) example:
The open _syscall_ returns the file descriptor (fd) for the file on a0. This file descriptor must be used on the read _syscall_ to indicate the file from which the operating system must read from to get the contents of the file.

```riscvasm
    la a0, input_file    # address for the file path
    li a1, 0             # flags (0: rdonly, 1: wronly, 2: rdwr)
    li a2, 0             # mode
    li a7, 1024          # syscall open
    ecall

input_file: .asciz "image.pgm"
```
