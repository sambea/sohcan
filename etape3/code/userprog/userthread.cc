#ifdef CHANGED
#include "system.h"
#include "userthread.h"
#include "thread.h"


#include "userthread.h"
#include "thread.h"
#include "system.h"

int do_UserThreadCreate(int f, int arg)
{
	Thread * newThread = new Thread("user thread");
	// cree un nouveau thread
	ArgThread * argThread = new ArgThread;
	argThread->f = f;
	argThread->arg = arg;
	
	// positionne la variable space a la meme adresse que le thread courant
	newThread->space = currentThread->space;
	
	// verifie qu'il y a assez de place pour le thread
	int tid = newThread->space->AllocateStack();
	if (tid != -1)
	{
		argThread->Idthread = tid;
		// place le thread dans la file d'attente des threads noyaux
		newThread->Fork(StartUserThread, (int)argThread);
		// incremente le nombre de threads du processus
		currentThread->space->IncrNumThreads();
	}
	
	return tid;
	
}

int do_UserThreadExit()
{
	currentThread->space->DecrNumThreads();
	currentThread->Finish();
	currentThread->space->DesallocateStack(currentThread->tid);
	return 0;
}

void StartUserThread(int f)
{	
	currentThread->space->RestoreState();

	currentThread->space->InitRegisters();
	
	ArgThread * argT = new ArgThread;
	argT = (ArgThread*)f;
	
	currentThread->tid = argT->Idthread;
	
	//calcul du nouveau pointeur de pile en fonction de l'Idthread
	int new_stack_reg = currentThread->space->TSize() - (PAGES_PER_THREAD * PageSize) * (argT->Idthread + 1);
	// positionne new_stack_reg sur le pointeur de pile
	machine->WriteRegister(StackReg, new_stack_reg);
	// PC <- user function address
	machine->WriteRegister(PCReg, argT->f);
	machine->WriteRegister(NextPCReg, argT->f+4);
	// reg4 <- argument
	machine->WriteRegister(4,argT->arg);
	
	machine->Run();
}

#endif // CHANGED
