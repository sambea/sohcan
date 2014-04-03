#include "syscall.h"

int main()
{
    int nombre=11;
    PutString("My Number=");
    PutInt(nombre);
    PutChar('\n');
    Halt();
}

