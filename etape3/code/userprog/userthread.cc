#ifdef CHANGED
#include "userthread.h"
#include "thread.h"
#include "system.h"

ThreadUser* CreateUserThread(int f, int arg)
{
	ThreadUser * userThread = new ThreadUser;
	userThread->fonction = f;
	userThread->argument = arg;

return userThread;

}
#endif // CHANGED


