# slp
A compiler for a simple straight-line programming language implemented in C++

The purpose of this project is to better understand code generation and compiler optimizations. The scanner and parser will be generated using Flex and Bison respectively. All other parts will be written by hand.

Sample interaction:
````
make slp
./slp examples/02_slp.in > 02_slp.asm
nasm -f elf 02_slp.asm; ld -m elf_i386 -s -o 02_slp 02_slp.o
./02_slp
````
Produces:
````
8
7
80
````
# Language constructs
The 32-bit integer is the only data type.

The language consists of statements and expressions.

Statements are terminated using a semicolon.

The language provides a built-in print statement which takes in a comma-delimited list of expressions and sends the result of each one to standard output.

Example: The following cpiece of code prints the number "2" five times.
````
a := 5;
while (a > 0) {
   printTwo();
   a := a - 1;
}
def printTwo() {
   print(2);
}
````
