#include "syscall.h"


void print(int i){
	int j = 0;
	for(j = 0; j < 150; j++){
		PutChar(i);
	}

	UserThreadExit();
}

int main(){
	int t1, t2;
	t1 = UserThreadCreate(print,(void *) 'a');
	t2 = UserThreadCreate(print,(void *) 'e');

	PutChar('\n');


	return 0;
}
