#ifdef CHANGED
#include "system.h"
#include "userthread.h"
#include "thread.h"


ThreadUserParam* CreateUserThreadParams(int f, int arg)
{
	ThreadUserParam* userThreadP = new ThreadUserParam;
	userThreadP->f = f;
	userThreadP->arg = arg;

return userThreadP;

}


void InitRegistersWithParam(int f, int arg) {
  
    // placement de PC au début de la fonction à executer
    machine->WriteRegister (PCReg, f);
    // placement de l'argument dans le registre 4
    machine->WriteRegister(4,arg);
    
    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister (NextPCReg, f+4);  //branchement à l'instruction suivante
    machine->WriteRegister (RetAddrReg, currentThread->loadRetour()); //
    
    // On place StackReg 3 pages en dessous du pointeur du
    // programme principal
    machine->WriteRegister (StackReg, machine->ReadRegister(StackReg) - currentThread->getStackAddr()*PAGES_PER_THREAD*PageSize);
    DEBUG ('a', "Initializing stack register to %d\n",
           machine->ReadRegister(StackReg) - currentThread->getStackAddr()*PAGES_PER_THREAD*PageSize);

}




int do_UserThreadCreate(int f, int arg)
{
	Thread * newThread = new Thread("user thread");

	// declaration du nouveau thread
	ThreadUserParam * argThread;
	//creation du nouveau thread
	argThread=CreateUserThreadParams(f,arg);

	// positionnement de la variable space a la meme adresse que le thread courant
	newThread->space = currentThread->space;
	
	// verification qu'il y a assez de place pour le thread
	int tid = newThread->space->Allocate();
	if (tid != -1)
	{
		argThread->IdThread = tid;
		// placement du thread dans la file d'attente des threads noyaux
		newThread->Fork(StartUserThread, (int)argThread);
		// incrementation du nombre de threads du processus
		currentThread->space->IncrNumThreads();
	}
	
	return tid;
	
}

int do_UserThreadExit()
{
	currentThread->space->DecrNumThreads();
	currentThread->Finish();
	currentThread->space->Desallocate(currentThread->tid);
	return 0;
}

void StartUserThread(int f)
{	
  //Recuperation des parametres
  ThreadUserParam *param = (ThreadUserParam *) f;
  
  //Initialisation des registres
  currentThread->space->InitRegisters();
  InitRegistersWithParam(param->f, param->arg);
  
  //Lancement de l'interprete
  machine->Run();
}


#endif // CHANGED


