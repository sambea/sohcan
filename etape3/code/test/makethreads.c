#include "syscall.h"

void print(int n)
{
	if (n % 2 == 0)
		PutString("pair\n");
	else
		PutString("impair\n");
	UserThreadExit();
}

void fct(int n)
{
	PutString("une chaine\n");
	UserThreadExit();
}

int main()
{
	int n;
	UserThreadCreate(fct, (void*)0);
	for (n = 0; n < 2; n++)
	{
		UserThreadCreate(print, (void*)n);
	}
	UserThreadCreate(fct, (void*)0);	
	return 0;
}
