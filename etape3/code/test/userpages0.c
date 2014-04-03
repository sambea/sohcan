#include "syscall.h"

#define N 4

/*void print(char c)
{
	int i;
	for (i = 0; i < N; i++){
		PutChar(c);
	}
	PutChar('\n');
	UserThreadExit();
}*/

void print(char c)
{
	int i;
	for (i = 0; i < N; i++){
		PutChar(c);
	}
	PutChar('\n');
	UserThreadExit();
}

void print_int(int c)
{
	int i;
	for (i = 0; i < N; i++){
		PutInt(c);
	}
	PutChar('\n');
	UserThreadExit();
}

int main()
{
	PutString("Debut main\n");
	UserThreadCreate(print, (void*)('1'));
	UserThreadCreate(print, (void*)('2'));
	UserThreadCreate(print, (void*)('3'));
	PutString("Fin main\n");
	return 0;
}
