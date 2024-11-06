## Software Interrupts - Controlling the Car

### Instructions

In this exercise, you will do the **same** activity as [Exercise 7.1](ch07-01-peripheral-controlling-the-car.md): you must control a car to move it from a parking lot to the entrance of the Test Track. However, you can no longer access the MMIO addresses directly on user code, i.e., the high-level code with the control logic. You must implement a set of syscalls to control the car and use them in your control logic, that has to be executed in user mode.

<u>Separating the control code</u>

The following code is suggested as a starting point for your solution. You can change it however you want.

```riscvasm
.text
.align 4

int_handler:
  ###### Syscall and Interrupts handler ######

  # <= Implement your syscall handler here

  csrr t0, mepc  # load return address (address of
                 # the instruction that invoked the syscall)
  addi t0, t0, 4 # adds 4 to the return address (to return after ecall)
  csrw mepc, t0  # stores the return address back on mepc
  mret           # Recover remaining context (pc <- mepc)


.globl _start
_start:

  la t0, int_handler  # Load the address of the routine that will handle interrupts
  csrw mtvec, t0      # (and syscalls) on the register MTVEC to set
                      # the interrupt array.

# Write here the code to change to user mode and call the function
# user_main (defined in another file). Remember to initialize
# the user stack so that your program can use it.

.globl control_logic
control_logic:
  # implement your control logic here, using only the defined syscalls
```

You must create a second file, **called main.s**, that contains only the code below. This code can't be changed and will be used by the assistant to check your solution.

```riscvasm
.text
.globl user_main
user_main:
  jal control_logic
infinite_loop:
  j infinite_loop
```

<u>_Syscalls_</u>

You **can** implement the system calls listed below. In case your code doesn't use some of them, it is not necessary to implement it. For this exercise, you mustn't implement any additional system calls.

| _syscall_                                    | Parameters                                                                                                                                                                                                                         | Return Value                                          | Description                                                                                                                                                                                                                                  |
| :------------------------------------------- | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | :---------------------------------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| syscall_set_engine_and_steering</br>Code: 10 | **a0**: Movement direction</br>**a1**: Steering wheel angle                                                                                                                                                                        | 0 if successful and -1 if failed (invalid parameters) | Start the engine to move the car.</br>a0's value can be -1 (go backward), 0 (off) or 1 (go forward).</br>a1's value can range from -127 to +127, where negative values turn the steering wheel to the left and positive values to the right. |
| syscall_set_hand_brake</br>Code: 11          | **a0**: value stating if the hand brakes must be used                                                                                                                                                                              | -                                                     | a0 must be 1 to use hand brakes.                                                                                                                                                                                                             |
| syscall_read_line_camera</br>Code: 12        | **a0**: address of an array with 256 elements that will store the values read by the Line Camera.                                                                                                                                  | -                                                     | Read values from the Line Camera.                                                                                                                                                                                                            |
| syscall_get_position</br>Code: 15            | **a0**: address of the variable that will store the value of x position.</br>**a1**: address of the variable that will store the value of y position.</br>**a2**: address of the variable that will store the value of z position. | -                                                     | Read the car's approximate position using the GPS device.                                                                                                                                                                                    |

### Notes and Tips

- Check the [ALE Peripheral MMIO Manual](appendix_ale-peripherals-mmio-manual.md#self-driving-car) for information about the Self Driving Car peripheral.
- If you are not using the assistant, you must configure the simulator in a similar way as done for [Exercise 7.1](ch07-01-peripheral-controlling-the-car.md). However, with a small difference: the option “_Enable Operating System_” must stay disabled.
- You mustn't call the exit _syscall_ (as there isn't an operating system, it doesn't exist).
- The _syscall_ operation code must be passed via register a7, as done in previous exercises.
- You can test your code using the simulator's assistant from this <a href="https://riscv-programming.org/ale/#select_url_content=TjRJZ3RnaGdsZ2RnK2dCd2djd0tZZ0Z3aEFHaEJBWndLZ0lCY0laUzRDQmpBSnlnVk14Q2pBUUhzN1NBQ1lBVlFDU2NBQktvQU5nbFIwY1BBSUpFUzVTbkFESzlScVFDK1BBR1owT1lIZ0IwUUFPZ0QwWURnQk1BcnVOUUVMaFltUXFrekFLd0tuak1OazV1UGdBWkRob0ljUUFsVkNEdFBRTWpVMHRyZTBkbkdnNFlHRlFhVWlnczcxOFFBRzUtUUs1ZVlCNWlNQWNJVWk0NFRNb0RjVWM2SGgxOVF4TnpLMXNISnd0YStzYTZJdE15Z1BaS25nak9ucVQrMUFBUFVsUVlZaXpuRzFRQU55Z2FZWUlKWFRnYkJrT1laR2FJQ1o4LUdIOGFjVmNlQUZGVmdIWTRBQlllR3NOakFiQVI1SXAzQ3AxQXdtTUItRHg1anRTSFE3SGt1QUFLQUNVY0pnQ0lSQkRzVWpvV09tZUo0cEFBRmlRekhZb0R3QUx3OEhJQWR4NFFsRUVpSjZJQUJnQWVDbC1BQjhYMmtOQklxQjQzek1md3dQRlVIRjBwR1o5d2xna28waFJUREJBRm9lQUJoTExJamp0V0RJY2tVaVY2KzY4aXdDd1c4Z0JHZEVGOEx4anJzcEVhdU5JQUU4cFBUVEE2UFY3VER3b0RZQXlBRm5CWUZCRUJ4aXZNM2tSSXc3U0xpMHpCdFFnR0pBNkQ3VElMVktoZUF0eVJ3d3dGOHBFZUp4aVBrc2phZzU2c2k3Y1c3bTE3eVg3VUtuZzFsUStISTRTYkExVUhjNlBIRTY5WEtuMHp4TTluYy1jQ3lCQlFCeEV2emU3ek94ME9pYlhoMXFBTm1CTi1zd050a3gzTzEwSWtLRVVzNzQrbjJXOGdoSVhGRDB6Um1oN2c4cUhXaFkyaCtGQ0N0eW1MVEhlUEEyT0VkaGdJZVpob0tRSHlPQWhsQUFFSStvSU5qb3FZSTVqaE9VNm1KaVpoWks4UndBTllNandjQU1vS2ZBTERTVlkrZ0Fzb01qaG1NV0lLc1U0QkFvS2dlRlJ2Y3BpeUtZeUdxT1FwQjJNVWtGYU5Cc0YtdWhuaklhaHFES1ZoT0ZDZEdzYkVTQXBIa2VJVkUwWFI5SU1jQVRHbkZRN2diT2l3Q3JMS0FDTUFBY0FBTVpnQUt5eUQ2c29BRXhtQUFiTElBQmVzcmFvNXJuT1dZcmxhTEk5bXl1NWpuZk41WVVBTXdlUUZaak9TRkNYUlZvY24rSVY3YjRpV2FvYkhRK3lST2lXTDBYdzBFSWxBdWpva3hMNEZQQTRnY01nWmlPRGNsSThBeHJuWXZWZUtLZkJpR3FXaGg2YWJoUDczTTAtNkhucHBHd0RrZEFpQUFLcXhJUTBRQVVxb0FEeUFCeVpoa0F3TnlOVDZ6WDNHWXJWWkhBSFhJQUEyaTFDWW5tMTkyZGQxbXpJSDF1cU9RQXVwQnczeWNWWFN5QjVybURWQm9PT0x3R3hrSEFxUVNveWhBK2pBTkMwYlZPTERaUzFJUURZTmpOTFlnbmNzTlpnYk9zWlBJQjFEcmlEd01uU0lqMERQS0RDSU01T2tDd0JndzBJa1o1S09iSXJtckFBWXFMd3V1UkZyazh6d2ZNUU1sUEFBSnhLd3J3MXdHc3h4TU85OE9rTnpyTjRnUURya3E1Z3ZvcVFqbVl0TFhnMWkwUnJpQjl5QkhNTnNDNkxHR3dmUndDQzYyU1pKZUpXTHRWdU9IVWU5eVluZ016SjBrZERPTlVnUVpoN0xvRUFPRlFMczlSQUNFMFJBeW9udWExS1pPd1VDT0VUZXdrdEgxSzB0MW5XbXpISjJrTEJIb1lYWXVpNk5Ja0VtSHJ1T3grWEQxVjlTWkI3UHVEZE55M0pSdDk3T2V4dzljQWNCNkNBZWlYN2ZWNVBzQ3o4bkJkT1BQWStOZWlBQ0VIZHg2Z0NkSjNBS2ViR25xQ1lqd0I3U1hRdUlKK0lwelEyUGxrbHRRVW1DZkZQQXVlNVhrOEQ1UEQrVUZIZ29VZURoVWlubE9LRGtlQ0pYbG4tYlU2Vk1yWlNBYmxHS1FNOVl2WHJPOUI2TkZIci1WSk43UGVPWlVEeDFnRVF1QTl4a0Jna1pJOVV3MnB0U3dIS2hBUElVQjlpb0ZFbjBXaEpBSUJzTk1Jd213THN3QUVsTUxncDJUVnQ3b2t6dEFPRzFjVVR3RkdHOGNZV0pNUkRUMWdpUGVYZEs2bUVPaFdFK05RSkM1QTJEWVNPMHM5N2QwMGRvdGV1akhCNUNJVVlsUmw4U3g3bHZwRUIrd01pcGoxaGpVSDBZQUhUR2tvVHdDUjJjOTdJV29GNG54OThON2V3Q1ZJNmtNaVl6cWpvSXctSUxEbWhnRnd0eU93bEFDNVFOV0FBRW1BQVFVSnZqcUVnRFZxc0RXcDQ0RGF5RWVURGdra3pySUhSSTVBS21JdEFRVHdXU0R4Q0FhQndBZEFmTGd5TWVEb2lRSFFVNFpWeEZaMmliSFdKOURwQ0pPWWVPR2dxU2hKU0ZRTlJMcEpFbEh0THhGRThlWmhwbnhMbWNreFphU3lDeERhY05UcDNTSUNLbWtEUklaOXhSbVVIR1pJM1oreUdGTUtPVXMwd0t5MWswQTJhZ2tSUXlyazNNNkxxTHBQUytrSGdaSXlQNHlpeDZxT3J1b2hwcGdEU3RHTkRMVHFSeEVSN0RER0NHQUhCZUN3SHBxY1RvU016Q1IxSHZDa3hHaVFDb3R0aGloMkdOTWc0cElFeUFsbFppVzNMSlJTNHgxY3lBZTJvR3dNWUdKVUh3dnNkZkp4OTlVQmJJUkNETWVlOStVSUVGWFVlUklxWlc3TW50UFVnSzhJbGtpdm80OGtLSnBYUVJCdEJEeDJzSndHQXpnVTlHbU16SjFRWG5qQW1SY1NiUzNKa0NOMTFNT0MwMDVSelptMHQyWk15NXRMQkVWczZZMnphUGJSMmRqbmF1MERod0Qyc3BMWit6amU3QkF3MXBZaHo2SnpHQUVkOUp1UHdkWGVPaWR4Q3IxVHVuRkdFemRsNXdRR3ZGMXVxOFJxS2dCWEJwQ3JhNWFzSHMzT2dyZFM2ZDJiZDNOdC1jNkNkdUhwU3NrMUxiaGFwMWFLd3QxSWw0d0JYc2ZOZUJBRzBOVkVYdll0UjhUNHdEUGhmZlZOODlET09OU3pKKzEwckt2ekhIWlNCWDlQSXBYLW9GSEtJQ0lwUlJpaEEzS1NVNzF3SXlsbFI5N2tVSHF2UVc5TzZXQ3FIQ01kYkhRaHhDY2lFM0lYNDRwSEQrTGNQd0RRUGhiQkJFZ0RBNXZVUnp6QW5TSXljcTRWeElsRndxcFlpLXROS3RGNkFzYWNLeEJqYkZpb25VSlNqT2lhUDZKc2ZwZFZDSjkyU3BjWHJPVjNzV2hrSEpPUXJjaklQN2ZGU3RLRHlxVTcyT1RNS2xiNEFWbkl1VWZlRkJXWmh2Z0sxY2g1UDQtR3lTNkM0SU04MU5GWElqMTRMeVQrYmt6TUFHcHJNWHh4R0twaUdTVHhzUTRxZ0xpbXdiQzhTSUFKYlNJbGNCOUFrbEpHUzlINFU3SVZZNFdJalRJWlEybG9KNDA3blRFZ0FBRlNwYlMrbG82SHdlRHJVRUt4RDRxaDFvZkFBQXJwZEsybDJ4Y1drUzFnVERSUURGU0hyUFd1cmRkcW4wZW8tUXBDQXorbUg0V0NkNERZSlFORldJTkFwQ2RBQWp0d2FxNUE2RElUTUtzVHJkWlp1WWxTNzVIZzFuQmxUWm16NmViQ1l6QStpVzhsbGJhM1RZaWM4TUZiYnNkZ3I3ZDhoYk94OFhPTGQyNUdWMUwrcG55dlZQUDR1RzlJOG5hRmxPaVBKQzNWaXhSNFA5bmJQb2djZzR1LWxNd1BBQUFpU2dLREhBU0wwRGJXNEdpRE8reWQyYjRQZ0FvODhHRDJRR1Bwc2xqTU1GZktzbzhuOWJJSzBtZFdIMFNVLU00eVh5ZzBITmlvMVpYSmltUVRUYkJhOGdHbnBHNTNzNmEyOXpCblUrZnlyNVkwSlZjaUdocXBEZUtnMXlJN0RIckZYcHZFcXVFVzkwbHdSMVZSSDFVVHFualBPZVl2NWNIcnZyeHNrcXZvSm1xM0FlT0lORVdROERDQkVhSXNSS2dOcjNpMEhJVENkZzNSa2hTZEV0dktoODRJUWVLRHBEWVBZSm9YUWc1SHpXRUJhajV3cER2RCtIb2JBOUJKdFpoOGFFMjFuaFBXcGgrQWtwNEVqY2tUaFNDaVZWbGphV2dmdUI3TkwtY1VncTY4VGNaTHdqSkdqZWdmRFdBQW5BdWF0N2ppRC1vcjFBK1V0a1o2ejVVMHZRa3JTZEFqZWloNldLcWtCWXRRc0F3QUtUMk5ySTJZZjJrUTRBSGdKS1dreWxlOWJWODhNZjRwRnJkOUoyS1A5R2lHZno5T0V2K3FqeHlBRWs0c1pLWjRhQm5Pam9nOFhTTi1JODZRV2EzNmw0NzczNmxvVHpmU1VqLTYyYjJiU3pQNzR3U2pXYU1oQUVJd1g1Z0dQUlFELVRKWWVUcXJxNzJKeEMxNXhERkpiNTJ4d0Y3QkNJMFNrSEhvWEpiaTB6ZW8wVEg1SVNiQ3pKdXpINk43TjdjanJndjZvRGs3QUNVRmFEUTR3NGNETWd3QWRUNHktelR5ZERheDRGekJMRGdodURLQzhCckM1QWVodFE4QzhnUUE4QVVnSGk2QmZiQURNaXdDd1RNaG1EOEJSQWhCbUQwQ29Camo3UU9oZUQ2SW1FaERvaTBFT2d0SXdSQ0VpRWNENHlSaHJDLUItQUVHVkNGak5SR1EwRFVRV2dIaVlnMmdRQ0NobUNreWd6OGFtcnRoajdNcUNSSkd5QTdvSVFrYTh4YmlqamtEMjZvQ3NqclJBZ2ZEb3pFekVqNFNrQzZEYWpPUWtSbUNiQkpITlRFeDg0ZUpPRzVHc2dZUTB6b2lQVFpFUUQtUnhTK2hTQkpyNEFJQUlCQkVOQnRRV0RoQWJDa0RhaW5TV0ZnQ21ERDdXNjhBNktNZ083Q3hyd2RGT0U5Rk1pN3BiTFM3akJFeG9ydERTQVZ6NHh3QXNoTHFPRG9nbnd6cnhGY1lVRDlaUEpnQ3dDeUNRQ3JBd0dnek41RGFVaWI1QnpFaGZFallKSWdpR0ExVEphREt2R2RaUEV3QVh4cmFRazNIK0R4RU81ZkErSHp5NEJSaFpBdXpJQ1lDZ0FleW5nRUJZbG9rd0FZa3hqOFJ5Q1lDRDU0QXRCRW1jSjZoa2xHb1Vub2xRQzNDY0l3NjBsSzcwbUVtTW5Fa1FEQ3lzbW9Ec2xVbjhTQ0M4bjhtY21jS3NUQ2tFa0NrUUNxQVNtVW1pbjhUOEFTbW55MHpqZ0VBY0ROQVdqQkUrS3JDWUJtNThrZ0Jxa1hyQkh4Z3pLVGlWVGlCSzRzQkN6ZkJpeWl3MGw0RDBMSHdIaWpZNzRVQm9Bc0MrUWVRZ0N4UUdrK2kwQ1JEM3hZaytsN0NIREhCNGtZQ2dBMGJuQ1hETUttZ1RoRkQ0a0VBZFRNQVlDZWtCUmFBWmxhQkFB" target="_blank">link</a>.
