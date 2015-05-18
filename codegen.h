#ifndef CODEGEN_H
#define CODEGEN_H

#include "node.h"
#include <iostream>

// Define functions to write boilerplate ASM code to
// standard output. The boilerplate is Linux i386-specific
// and does the following:
//
// 1) Define the newline character
// 2) Define a procedure print_eax, which prints to stdout
//    the value contained in register eax
// 3) Set ebp equal to esp upon code entry
// 4) Call sys_exit upon code completion
//
// Running:
// 1) emitBoilerplatePre()
// 2) codeGen() method on the program's AST
// 3) emitBoilerplatePost()
// will generate a complete ready-to-assemble x86 ASM source file

void emitBoilerplatePre();
void emitBoilerplatePost();

#endif