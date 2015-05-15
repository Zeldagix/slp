#include <iostream>
using namespace std;

// esp holds the stack pointer
// ebp points to the bottom of the current stack frame
//
// TODO: handle scope entry and exit
// My idea is to push ebp onto the stack before entering a new scope
// and then pop it from the stack after leaving a scope.
// This would make the first variable in the symbol table
// be located at an offset of 8 from ebp (currently it's 4).
void emitBoilerplatePre() {
	cout << "section .data" << endl;
	cout << "    newline:    db 0Ah" << endl;
	cout << "    newlineL:   equ $-newline" << endl;
	cout << endl;
	cout << "section .text" << endl;
	cout << "    global _start" << endl;
	cout << endl;
	cout << "_start:" << endl;
	cout << "    mov ebp, esp" << endl;
	cout << endl;
}

// edi is a counter which will hold the length
// of the integer to be printed
void emitBoilerplatePost() {
	cout << endl;
	cout << "    mov eax, 1" << endl;
	cout << "    int 0x80" << endl;
	cout << endl;
	cout << "print_eax:" << endl;
	cout << "    mov edi, 0" << endl;
	cout << endl;
	cout << "first_loop:" << endl;
	cout << "    mov edx, 0" << endl;
	cout << "    mov ecx, 10" << endl;
	cout << "    div ecx" << endl;
	cout << "    add edx, '0'" << endl;
	cout << "    push edx" << endl;
	cout << "    add edi, 1" << endl;
	cout << "    cmp eax, 0" << endl;
	cout << "    jnz first_loop" << endl;
	cout << endl;
	cout << "second_loop:" << endl;
	cout << "    mov edx, 1" << endl;
	cout << "    mov ecx, esp" << endl;
	cout << "    mov ebx, 1" << endl;
	cout << "    mov eax, 4" << endl;
	cout << "    int 0x80" << endl;
	cout << endl;
	cout << "    add esp, 4" << endl;
	cout << "    sub edi, 1" << endl;
	cout << "    cmp edi, 0" << endl;
	cout << "    jnz second_loop" << endl;
	cout << endl;
	cout << "    mov edx, newlineL" << endl;
	cout << "    mov ecx, newline" << endl;
	cout << "    mov ebx, 1" << endl;
	cout << "    mov eax, 4" << endl;
	cout << "    int 0x80" << endl;
	cout << endl;
	cout << "    ret" << endl;
	cout << endl;
}
