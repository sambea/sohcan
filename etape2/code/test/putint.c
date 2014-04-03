#include "syscall.h"

#define N 16 

int main()
{
  int i;
for (i=0;i<N;i++) {
    //PutString("My Number=");
    PutInt(i);
    PutChar('\n');
}
Halt();
return 0;
}
