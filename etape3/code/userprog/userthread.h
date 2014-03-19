#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

typedef struct 
{
	int fonction;
	int argument;
	int IdThread;
} ThreadUser;

ThreadUser* CreateUserThread(int f, int arg);
extern int do_UserThreadCreate(int f, int arg);
extern int do_UserThreadExit();
extern int do_UserThreadJoin(int tid);
void StartUserThread(int f);

#endif
#endif // CHANGED
