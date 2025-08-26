## Organization of an ELF file

In this activity, you will manually read and interpret an ELF executable file from its hexadecimal byte-by-byte representation (hexdump), as exemplified below.

<pre><code>
00000000  7f 45 4c 46 01 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 f3 00 01 00 00 00  b4 10 01 00 34 00 00 00  |............4...|
00000020  a4 01 00 00 04 00 00 00  34 00 20 00 04 00 28 00  |........4. ...(.|
00000030  06 00 04 00 06 00 00 00  34 00 00 00 34 00 01 00  |........4...4...|
00000040  34 00 01 00 80 00 00 00  80 00 00 00 04 00 00 00  |4...............|
00000050  04 00 00 00 01 00 00 00  00 00 00 00 00 00 01 00  |................|
00000060  00 00 01 00 b4 00 00 00  b4 00 00 00 04 00 00 00  |................|
00000070  00 10 00 00 01 00 00 00  b4 00 00 00 b4 10 01 00  |................|
00000080  b4 10 01 00 48 00 00 00  48 00 00 00 05 00 00 00  |....H...H.......|
00000090  00 10 00 00 51 e5 74 64  00 00 00 00 00 00 00 00  |....Q.td........|
000000a0  00 00 00 00 00 00 00 00  00 00 00 00 06 00 00 00  |................|
000000b0  00 00 00 00 37 15 02 00  13 05 95 f4 93 05 00 00  |....7...........|
000000c0  13 06 00 00 93 06 f0 ff  93 72 15 00 b3 85 55 00  |.........r....U.|
000000d0  33 46 56 00 93 86 16 00  13 55 15 00 e3 16 05 fe  |3FV......U......|
000000e0  17 05 00 00 13 05 85 01  23 20 b5 00 13 05 00 00  |........# ......|
000000f0  93 08 d0 05 73 00 00 00  00 00 00 00 4c 69 6e 6b  |....s.......Link|
00000100  65 72 3a 20 4c 4c 44 20  31 30 2e 30 2e 30 00 00  |er: LLD 10.0.0..|
00000110  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000120  01 00 00 00 e0 10 01 00  00 00 00 00 00 00 01 00  |................|
00000130  05 00 00 00 c8 10 01 00  00 00 00 00 00 00 01 00  |................|
00000140  0a 00 00 00 f8 10 01 00  00 00 00 00 00 00 01 00  |................|
00000150  11 00 00 00 b4 10 01 00  00 00 00 00 10 00 01 00  |................|
00000160  00 2e 74 65 78 74 00 2e  63 6f 6d 6d 65 6e 74 00  |..text..comment.|
00000170  2e 73 79 6d 74 61 62 00  2e 73 68 73 74 72 74 61  |.symtab..shstrta|
00000180  62 00 2e 73 74 72 74 61  62 00 00 65 6e 64 00 6c  |b..strtab..end.l|
00000190  6f 6f 70 00 72 65 73 75  6c 74 00 5f 73 74 61 72  |oop.result._star|
000001a0  74 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |t...............|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001c0  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
000001d0  01 00 00 00 06 00 00 00  b4 10 01 00 b4 00 00 00  |................|
000001e0  48 00 00 00 00 00 00 00  00 00 00 00 04 00 00 00  |H...............|
000001f0  00 00 00 00 07 00 00 00  01 00 00 00 30 00 00 00  |............0...|
00000200  00 00 00 00 fc 00 00 00  13 00 00 00 00 00 00 00  |................|
00000210  00 00 00 00 01 00 00 00  01 00 00 00 10 00 00 00  |................|
00000220  02 00 00 00 00 00 00 00  00 00 00 00 10 01 00 00  |................|
00000230  50 00 00 00 05 00 00 00  04 00 00 00 04 00 00 00  |P...............|
00000240  10 00 00 00 18 00 00 00  03 00 00 00 00 00 00 00  |................|
00000250  00 00 00 00 60 01 00 00  2a 00 00 00 00 00 00 00  |....`...*.......|
00000260  00 00 00 00 01 00 00 00  00 00 00 00 22 00 00 00  |............"...|
00000270  03 00 00 00 00 00 00 00  00 00 00 00 8a 01 00 00  |................|
00000280  18 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
00000290  00 00 00 00                                       |....|
00000294
</code></pre>

This is an example of the Hexdump for the executable of exercise Ex. 2.3. In the example, each line contains the following information, separated by spaces:

1. Offset of the first byte in the line (in hexadecimal). The offset is a number indicating the distance of the information (in this case, the first byte of the line) from a reference point (in this case, the beginning of the file).
2. 16 hexadecimal numbers, each representing a byte of the file.
3. 16 ASCII characters enclosed in "|". This is an attempt to decode the bytes into ASCII. The character "." may indicate a value that doesn't represent valid or printable ASCII characters.

As a first step, you should carefully read the description of the ELF format (particularly the tables for File Header, Program Header, and Section Header).

### Notes and Tips

- All numbers are represented in hexadecimal.
- Memory words store numbers in little-endian representation. Therefore, the bytes "34 00 01 00" represent the value 0x10034 in 4 bytes.
- The program instructions can be found in the .text section. Refer to the [RISC-V Instruction Set Manual](https://drive.google.com/file/d/1uviu1nH-tScFfgrovvFCrj7Omv8tFtkp/view) to decode the instructions. Especially, consult the RV32I Base Instruction Set on page 609.

### Example Solution

To make your job easier, we will discuss how to read the ELF file given above. The following listing contains the same file contents, but with color marks to simplify the discussion.

<pre><code>
00000000  7f 45 4c 46 01 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 f3 00 01 00 00 00  b4 10 01 00 34 00 00 00  |............4...|
00000020  <mark style="background:transparent;color: purple">a4 01 00 00</mark> 04 00 00 00  34 00 20 00 04 00 28 00  |........4. ...(.|
00000030  <mark style="background:transparent;color: blue">06 00</mark> <mark style="background:transparent;color: red">04 00</mark> 06 00 00 00  34 00 00 00 34 00 01 00  |........4...4...|
00000040  34 00 01 00 80 00 00 00  80 00 00 00 04 00 00 00  |4...............|
00000050  04 00 00 00 01 00 00 00  00 00 00 00 00 00 01 00  |................|
00000060  00 00 01 00 b4 00 00 00  b4 00 00 00 04 00 00 00  |................|
00000070  00 10 00 00 01 00 00 00  b4 00 00 00 b4 10 01 00  |................|
00000080  b4 10 01 00 48 00 00 00  48 00 00 00 05 00 00 00  |....H...H.......|
00000090  00 10 00 00 51 e5 74 64  00 00 00 00 00 00 00 00  |....Q.td........|
000000a0  00 00 00 00 00 00 00 00  00 00 00 00 06 00 00 00  |................|
000000b0  00 00 00 00 37 15 02 00  13 05 95 f4 93 05 00 00  |....7...........|
000000c0  13 06 00 00 93 06 f0 ff  93 72 15 00 b3 85 55 00  |.........r....U.|
000000d0  33 46 56 00 93 86 16 00  13 55 15 00 e3 16 05 fe  |3FV......U......|
000000e0  17 05 00 00 13 05 85 01  23 20 b5 00 13 05 00 00  |........# ......|
000000f0  93 08 d0 05 73 00 00 00  00 00 00 00 4c 69 6e 6b  |....s.......Link|
00000100  65 72 3a 20 4c 4c 44 20  31 30 2e 30 2e 30 00 00  |er: LLD 10.0.0..|
00000110  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000120  01 00 00 00 e0 10 01 00  00 00 00 00 00 00 01 00  |................|
00000130  05 00 00 00 c8 10 01 00  00 00 00 00 00 00 01 00  |................|
00000140  0a 00 00 00 f8 10 01 00  00 00 00 00 00 00 01 00  |................|
00000150  11 00 00 00 b4 10 01 00  00 00 00 00 10 00 01 00  |................|
00000160  00 2e 74 65 78 74 00 2e  63 6f 6d 6d 65 6e 74 00  |..text..comment.|
00000170  2e 73 79 6d 74 61 62 00  2e 73 68 73 74 72 74 61  |.symtab..shstrta|
00000180  62 00 2e 73 74 72 74 61  62 00 00 65 6e 64 00 6c  |b..strtab..end.l|
00000190  6f 6f 70 00 72 65 73 75  6c 74 00 5f 73 74 61 72  |oop.result._star|
000001a0  74 00 00 00<mark style="background: green"> </mark>00 00 00 00  00 00 00 00 00 00 00 00  |t...............|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001c0  00 00 00 00 00 00 00 00  00 00 00 00<mark style="background: green"> </mark><mark style="background:transparent;color: lightblue">01 00 00 00</mark>  |................|
000001d0  01 00 00 00 06 00 00 00  b4 10 01 00 b4 00 00 00  |................|
000001e0  48 00 00 00 00 00 00 00  00 00 00 00 04 00 00 00  |H...............|
000001f0  00 00 00 00<mark style="background: green"> </mark>07 00 00 00  01 00 00 00 30 00 00 00  |............0...|
00000200  00 00 00 00 fc 00 00 00  13 00 00 00 00 00 00 00  |................|
00000210  00 00 00 00 01 00 00 00  01 00 00 00<mark style="background: green"> </mark>10 00 00 00  |................|
00000220  02 00 00 00 00 00 00 00  00 00 00 00 10 01 00 00  |................|
00000230  50 00 00 00 05 00 00 00  04 00 00 00 04 00 00 00  |P...............|
00000240  10 00 00 00<mark style="background: green"> </mark><mark style="background:transparent;color: orange">18 00 00 00  03 00 00 00 00 00 00 00</mark>  |................|
00000250  <mark style="background:transparent;color: orange">00 00 00 00</mark> <mark style="background:gray;color: orange">60 01 00 00</mark>  <mark style="background:transparent;color: orange">2a 00 00 00 00 00 00 00</mark>  |....`...*.......|
00000260  <mark style="background:transparent;color: orange">00 00 00 00 01 00 00 00  00 00 00 00</mark><mark style="background: green"> </mark>22 00 00 00  |............"...|
00000270  03 00 00 00 00 00 00 00  00 00 00 00 8a 01 00 00  |................|
00000280  18 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
00000290  00 00 00 00                                       |....|
00000294
</code></pre>

1. First, we must identify the values of fields e_shoff, e_shnum, and e_shstrndx (see their description on the [Wikipedia page](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) related to the ELF format), which are colored in <mark style="background:transparent;color: purple">purple</mark>, <mark style="background:transparent;color:blue">blue</mark>, and <mark style="background:transparent;color:red">red</mark>, respectively.

   - The value of the e_shoff field is 0x000001a4 (recall the little-endian representation), indicating that the Section Headers start at this offset.

2. According to the ELF format, we know that each Section Header contains 0x28 bytes. Thus, we marked the beginning of each of them in <mark style="background: green">green</mark>.

3. e_shstrndx contains the value 4, indicating that Section Header number 4 (counting from 0) is the header of shstrtab, which stores the information about the names of the sections. We colored its content in <mark style="background:transparent;color:orange">orange</mark>.

4. The sh_offset field of Section Header 4 (<mark style="background:gray;color: orange">orange number with gray background</mark>) stores the address of shstrtab: 0x00000160.

5. The sh_name field of Section Header 4 is the offset (from the beginning of the shstrtab section) to the string representing the section's name. For example, Section Header number 1 has an offset of 0x1 (highlighted in <mark style="background:transparent;color: lightblue">cyan</mark>), so its name is the string at position 0x00000160 + 0x1. In other words, this is the Header of the ".text" section, which stores the executable's instructions.

6. Our objective is to find the ".symtab" and ".strtab" sections, which respectively store the addresses and names of the symbols.

7. By checking the name of each section, we identified that Section Headers number 3 and 5 represent the ".symtab" and ".strtab" sections.

8. Evaluating the sh_offset field of each of them, we know that the ".symtab" and ".strtab" sections are located at addresses 0x00000110 and 0x0000018a. Evaluating the sh_size field, we know that their sizes are 0x50 and 0x18 bytes, respectively.

9. In the .symtab section, for each symbol:

   - The first 4 bytes represent the offset of the symbol's name in the ".strtab" section.
   - The next 4 bytes represent the symbol's address in the program's memory.
   - The last 8 bytes represent other information about the symbol (not useful to us at this moment).

10. Copying the sections here:

    - .symtab: (offsets to .strtab are highlighted in blue, addresses in red)
    <pre><code>
    00000110  <mark style="background: blue">00 00 00 00</mark> <mark style="background: red">00 00 00 00</mark>  00 00 00 00 00 00 00 00  |................|
    00000120  <mark style="background: blue">01 00 00 00</mark> <mark style="background: red">e0 10 01 00</mark>  00 00 00 00 00 00 01 00  |................|
    00000130  <mark style="background: blue">05 00 00 00</mark> <mark style="background: red">c8 10 01 00</mark>  00 00 00 00 00 00 01 00  |................|
    00000140  <mark style="background: blue">0a 00 00 00</mark> <mark style="background: red">f8 10 01 00</mark>  00 00 00 00 00 00 01 00  |................|
    00000150  <mark style="background: blue">11 00 00 00</mark> <mark style="background: red">b4 10 01 00</mark>  00 00 00 00 10 00 01 00  |................|
    </code></pre>
    - .strtab:
    <pre><code>
    0000180  62 00 2e 73 74 72 74 61  62 00 <mark style="background: green">00 65 6e 64 00 6c</mark>  |b..strtab.<mark style="background: green">.end.l</mark>|
    00000190  <mark style="background: green">6f 6f 70 00 72 65 73 75  6c 74 00 5f 73 74 61 72</mark>  |<mark style="background: green">oop.result._star</mark>|
    000001a0  <mark style="background: green">74 00</mark> 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |<mark style="background: green">t.</mark>..............|
    </code></pre>

11. Now we can easily identify the names and addresses of the symbols:
    - The first line of the symtab is null, and we can ignore it.
    - The second line tells us that the symbol with the name at offset 0x1 is at address 0x000110e0. Consulting the strtab, we see that offset 0x1 is occupied by the name "end" (String defined by the bytes 65 6e 64 00. Notice that the string is terminated with the NULL character, with a value of 00).
    - The third line tells us that the symbol with the name at offset 0x5 is at address 0x000110c8. Consulting the strtab, we see that offset 0x5 is occupied by the name "loop".
    - Following this same logic, we can identify the name and address of all symbols.
