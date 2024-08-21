## Debugging a program

This exercise requires students to use the ALE simulator interactive commands to inspect the contents of registers and memory locations of a running program.

### Prerequisites

- Get familiar with the concepts of instructions, registers and labels.

### Debugging Tutorial

The ALE simulator has an interactive interface that allows the user to control the execution of the program and inspect the registers and memory values. This interface is similar to the interface provided by the GDB debugger and allows the user to debug the code execution.

To enable the interactive execution interface, just click on the arrow beside the RUN button and select the "Debug" option. After clicking on this button, the simulator will open an interactive terminal where you can type commands to control the execution and/or inspect the state of the memory and register of the RISC-V processor.

We recommend using the commands listed on the table below, but a complete list of the commands can be obtained using the "help" command on the interactive terminal.

| Command                       | Description                                                                                                                                                                                                                                 |
| :---------------------------- | :------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| symbols                       | Shows the address of the symbols (e.g., \_start, loop, end, result) of the program. The address is shown in the hexadecimal representation (e.g., 0x11180).                                                                                 |
| until \<address\>             | Executes the instructions until a certain address. The address must be provided in the hexadecimal representation (e.g., 0x11180).                                                                                                          |
| step [n=1]                    | Executes the next **n** instructions.                                                                                                                                                                                                       |
| peek r \<register\>           | Shows the value stored on the register \<register\> (e.g., _peek r x1_ or _peek r mtval_). The value is shown in the hexadecimal representation. The command _peek r all_ shows the values of all the registers.                            |
| peek m \<address\>            | Shows the value stored on the memory word associated with the address \<address\>. The value is shown in the hexadecimal representation.                                                                                                    |
| poke r \<register\> \<value\> | Modifies the content of the register \<register\> with the value \<value\>. For instance, the command _poke r x1 0xff_ stores the value 0xff in the register x1.                                                                            |
| poke m \<address\> \<value\>  | Modifies the content of the memory position associated with the address \<address\> with the value \<value\>. For instance, the command _poke m 0x800 0xfe_ stores the value 0xfe in the memory position associated with the address 0x800. |
| run                           | Executes the program continuously until the execution ends due to an exit syscall or execution of invalid instructions.                                                                                                                     |

### Instructions

In this exercise, you must modify the code below with your academic record (RA) number, assemble and link the code, and run it step by step in the simulator's interactive mode, as explained in the previous sections.

```riscvasm
.globl _start

_start:
  li a0, 134985  #<<<=== Academic Record number (RA)
  li a1, 0
  li a2, 0
  li a3, -1
loop:
  andi t0, a0, 1
  add  a1, a1, t0
  xor  a2, a2, t0
  addi a3, a3, 1
  srli a0, a0, 1
  bnez a0, loop

end:
  la a0, result
  sw a1, 0(a0)
  li a0, 0
  li a7, 93
  ecall

result:
  .word 0
```

This program receives as input the value of your RA in register a0 and produces as output the values ​​in registers a1, a2, and a3. Assume the program has received your RA as input and answer the following questions:

1. What are the values ​​of the following registers in hexadecimal representation when the execution reaches the "end" label?

   - a0:
   - a1:
   - a2:
   - a3:

2. What are the values ​​of the following registers in hexadecimal representation when the execution reaches the “loop” label for the fifth time?

   - a0:
   - a1:
   - a2:
   - a3:

3. What are the values ​​of the following registers in hexadecimal representation after the simulator executes the first 25 instructions?

   - a0:
   - a1:
   - a2:
   - a3:

4. What are the values ​​of the following registers in hexadecimal representation when the execution reaches the “loop” label for the eighth time?

   - a0:
   - a1:
   - a2:
   - a3:

5. What are the values ​​of the following registers in hexadecimal representation after the simulator executes the first 30 machine instructions?

   - a0:
   - a1:
   - a2:
   - a3:

6. What are the values ​​of the following registers in hexadecimal representation when the contents of a1 and a2 are different from 0 and have the same value for the first time?

   - a0:
   - a3:

7. What value (in hexadecimal representation) is stored at the "result" memory location after the execution of instruction sw a1, 0(a0) (located after the "end" label)?

### Notes and Tips

- To see the complete list of commands available in the interactive mode you can execute the "help" command.
- Depending on how many bits are necesary to encode the immediate value, the `li` pseudo-instruction can be mapped to one (`addi`) or two machine instructions (`lui` and `addi`).
- When the question indicates to execute to code until it reaches a given label, it means you must execute instructions until reaching the memory address of the label, but without executing the instruction stored in that memory address.
- The interactive terminal outputs some informations regarding the instruction that was executed in the format `#{Inst Num} 0 {Mem Addr} {Inst Code} {Inst Type} {Val} {Mnemonic}`
   - **Inst Num**: number of the machine instruction that was executed.
   - **Mem Addr**: memory address of the instruction that was executed. 
   - **Inst Code**: code of the instruction that was executed.
   - **Inst Type**: can be either `r` if the instruction uses only register or `m` if there is a memory access (store or load). 
   - **Val**: value stored in the `rd` register for instructions of type `r` or stored in the memory position accessed for type `m` instructions.
   - **Mnemonic**: assembly mnemonic of the executed instruction
- The second occurrence of the instruction #1 can be ignored.