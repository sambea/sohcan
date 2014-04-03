#ifndef USERTHREAD_H
#define USERTHREAD_H

typedef struct 
{
	int f;
	int arg;
	int Idthread;
} ArgThread;

extern int do_UserThreadCreate(int f, int arg);
extern int do_UserThreadExit();
extern int do_UserThreadJoin(int tid);
void StartUserThread(int f);

#endif
