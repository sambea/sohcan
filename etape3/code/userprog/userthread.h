#ifdef CHANGED
#ifndef USERTHREAD_H
#define USERTHREAD_H

typedef struct 
{
	int f;
	int arg;
	int IdThread;
} ThreadUserParam;

ThreadUserParam* CreateUserThreadParams(int f, int arg);
void InitRegistersWithParam(int f, int arg);
extern int do_UserThreadCreate(int f, int arg);
extern int do_UserThreadExit();
void StartUserThread(int f);


#endif
#endif // CHANGED
