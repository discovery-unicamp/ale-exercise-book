## Debugging a program

This exercise requires students to use the ALE simulator interactive commands to inspect the contents of registers and memory locations of a running program.

### Prerequisites

- Get familiar with the concepts of instructions, registers and labels.
- Get familiar with the concepts and commands discussed in Section 4.2 of the ALE Manual.

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

This program receives as input the value of its RA in register a0 and produces as output the values ​​in registers a1, a2, and a3. Assume the program has received your RA as input and answer the following questions:

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

5. What are the values ​​of the following registers in hexadecimal representation after the simulator executes the first 30 instructions?

   - a0:
   - a1:
   - a2:
   - a3:

6. What are the values ​​of the following registers in hexadecimal representation when the contents of a1 and a2 are different from 0 and have the same value?

   - a0:
   - a3:

7. What value (in hexadecimal representation) is stored at the "result" memory location after the execution of instruction sw a1, 0(a0) (located after the "end" label)?

### Notes and Tips

- To see the complete list of commands available in the interactive mode you can execute the "help" command. For this particular exercise, we suggest using the commands listed in Table 4.1 of the ALE Manual.
