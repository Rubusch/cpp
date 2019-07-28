C++ class in assembler

What does a class repesentation work?

example: compile the code snippet:
$ g++ -m32 -S -fno-dwarf2-cfi-asm ./simpleclass.cpp
    simpleclass.s

and see the result in asm
$ vi ./simpleclass.s

