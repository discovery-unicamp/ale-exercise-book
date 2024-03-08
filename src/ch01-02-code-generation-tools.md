## Automating the compilation process with Makefiles

This exercise requires students to reason about the compilation process and automate this process with Makefiles.

### Prerequisites

- Read and get familiar with the concepts and commands discussed in sections 3.1 to 3.5 of the ALE Manual. These sections cover the basics of generating and inspecting object and executable code.
- Read section 3.6 of the ALE Manual to learn more about Makefiles

### Instructions

In this exercise, you must produce a Makefile script that automates the compilation process carried out manually in the [previous exercise](ch01-01-code-generation-tools.md), i.e., for a program that contains two source files (file1.c and file2.c). The final file to be produced must be named prog.x. For this, you must create a rule for each intermediate file, until you reach the final file.

You might test your script executing the following commands:

```bash
make file1.s
make file2.s
make file1.o
make file2.o
make prog.x
```

These commands must generate, respectively: the assembly code for file1.c and file2.c; the object files file1.o and file2.o; and, finally, the executable file named prog.x.
