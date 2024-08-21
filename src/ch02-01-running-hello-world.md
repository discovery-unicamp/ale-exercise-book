## Running the Hello World program

This exercise is a tutorial that guides the student to run executable files on the simulator.

### Prerequisites

- Complete [exercise 1.1](ch01-01-code-generation-tools.md) to generate the Hello World program (prog.x).

### ALE Simulator Tutorial

The RISC-V ALE is a simulator that runs on your browser and can be accessed at [ALE Simulator](https://riscv-programming.org/ale/).

#### Loading files

The simulator has its own file system that enables storing multiple files. To load files, you need to click on the file button at the top right corner (left of RUN button), and select the files that you wish to load from your computer.

You can load executable files, source files or even data files to be accessed by your programs.

There is no directory structure and existing files with the same name are automatically overwritten, in other words, if you load a file named prog.x more than once, just the last one will be kept.

#### Running

Once you have loaded your files, you can start your program execution. To do so, you must click on the RUN button (top right corner).

The simulator will identify the source files and, if necessary, perform the compiling, assembling and linking to get the executable.
Note that for this case, if the C files are loaded, a warning is issued during the compilation process (`function declared 'noreturn' should not return`) due to the exit function definition.
This warning can be ignored.
Finally, the simulator will invoke the executable and show the program's output (if there is any).

Note: The simulator stops the program's execution when (i) the program invokes the system call (syscall) exit, or (ii) when the execution finds invalid instructions. In the last case, the simulator may show error messages like "Error: Failed stop: 64 consecutive illegal instructions: 0". This is expected in programs that do not call the exit syscall, as the processor doesn't know where the program ends and will continue to execute instructions consecutively, until it finds invalid instructions.

### Instructions

Load and execute the prog.x file on the ALE simulator and inspect the output produced by the program on the simulator terminal. You should see the string "Hello world!".
