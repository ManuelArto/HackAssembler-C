# Hack Assembler C

## INTRODUCTION

This is an implementation written in **C** of the Hack assembler outlined in project 6 of the online course [Nand To Tetris](https://www.nand2tetris.org/project06).

## ASSEMBLER OVERVIEW

This is a basic implementation that doesn't cover error reporting, so it works only with correct .asm file

### Setup

First of all unzip the "AsmFiles.zip" that contains 7 **asm** file and their relative correct **hack** code.
Then:

```bash
cd src
make
./assembler ../<asmfile>
```

If you want to test all the asm files at ones:

```bash
python script.py
```

### BRIEF OVERVIEW OF HACK ASSEMBLY

For a more complete introduction to the Hack Assembly language and the Hack computer it is designed for, please refer
to Nand To Tetris course materials.

Hack assembly is a simple language designed for the Hack computer platform that comes as part of the course. The
Hack instruction set architecture (ISA) consists of only two instructions and thus Hack assembly language also
contains only two instructions (which I refer to as commands, to distinguish them from their equivilents in the ISA):
'A' commands and 'C' commands. However C commands can take three different forms due to optional command components/fields.

The assembly commands take the following formats:

  A-Command   ->    "@<literal|symbol>"
  C-Command   ->    " &lt;dest>= &lt;comp>; &lt;jump>"
              ->    " &lt;dest>= &lt;comp>
              ->    " &lt;comp>; &lt;jump>"

note: "comp" is short for computation, "dest" for destination. Further  &lt;comp>,  &lt;dest> and  &lt;jump> are placeholders
for assembly mnemonics.

The function of the two commands is as follows. A-commands load a value into the address register of the Hack
computer. C-commands instruct the computer to perform one of a fixed, limited set, of computations and (a) assign the
result to a specified register, (b) use the result as a jump condition to jump to another instruction, or (c) both.

Hack assembly language also contains one psuedo command called an 'L' command that does not translate into a Hack
machine instruction. Its purpose is equivilent to a goto label in C, it simply marks a location in the code to jump
to. The effect of an L command is to create a new symbol in the assemblers symbol table which maps to an address in
ROM where the instruction to jump to is stored.

In terms of vocabulary, Hack assembly defines a small set of mnemonics for the "dest", "comp" and "jump" fields of
the C commands, and a small set of predefined symbols to be used in the A commands. These are outlined in the below
tables.

       +--------------------+  +--------------------+ +---------------------------------------------+
       |dest    d1   d2   d3|  |jump    j1   j2   j3| |comp     c1   c2   c3   c4   c5   c6    comp |
       |--------------------|  |--------------------| |(a=0)                                   (a=1)|
       |null    0    0    0 |  |null    0    0    0 | |---------------------------------------------|
       |M       0    0    1 |  |JGT     0    0    1 | |0        1    0    1    0    1    0          |
       |D       0    1    0 |  |JEQ     0    1    0 | |1        1    1    1    1    1    1          |
       |MD      0    1    1 |  |JGE     0    1    1 | |-1       1    1    1    0    1    0          |
       |A       1    0    0 |  |JLT     1    0    0 | |D        0    0    1    1    0    1          |
       |AM      1    0    1 |  |JNE     1    0    1 | |A        1    1    0    0    0    0      M   |
       |AD      1    1    0 |  |JLE     1    1    0 | |!D       0    0    1    1    0    1          |
       |AMD     1    1    1 |  |JMP     1    1    1 | |!A       1    1    0    0    0    1      -M  |
       +--------------------+  +--------------------+ |D+1      0    1    1    1    1    1          |
            +---------------------+                   |A+1      1    1    0    1    1    1      M+1 |
            |symbol    RAM address|                   |D-1      0    0    1    1    1    0          |
            |---------------------|                   |A-1      1    1    0    0    1    0      M-1 |
            |SP        0          |                   |D+A      0    0    0    0    1    0      D+M |
            |LCL       1          |                   |D-A      0    1    0    0    1    1      D-M |
            |ARG       2          |                   |A-D      0    0    0    1    1    1      M-D |
            |THIS      3          |                   |D&A      0    0    0    0    0    0      D&M |
            |THAT      4          |                   |D|A      0    1    0    1    0    1      D|M |
            |R0-R15    0-15       |                   +---------------------------------------------+
            |SCREEN    16384      |                     ^  
            |KBD       24576      |                     |
            +---------------------+                the mnemonics

note: tables sourced from Chapter 6: Elements of Computing Systems.

The binary values associated with the mnemonics correspond to the representation of the mnemonics in the ISA. The
assemblers job is of course to translate Hack assembly into Hack machine instructions defined in the ISA. The binary
format of the two ISA commands is outlined below.

A-instruction (ISA):

                op-code
                   |
                   V
     Binary Form:  0 v v v  v v v v  v v v v  v v v v           note: 16-bit instructions
                    |                                |
                    +--------------------------------+
                                |
          value of symbol|literal from A-command @<value|symbol>

C-instruction (ISA):

             unused/junk bits                dest bits
                     |                           |
                   +---+                     +--------+
                   |   |                     |        |
    Binary Form:  1 1 1  a c1 c2 c3 c4 c5 c6  d1 d2 d3  j1 j2 j3
                  ^     |                   |          |        |
                  |     +-------------------+          +--------+
              op-code            |                          |
                             comp bits                   jump bits

So for example the assembly command "D=D-1;JLE" which is C command of the form &lt;dest>=&lt;comp>;&lt;jump> translates to the binary machine instruction "1110001110010110".