// exception.cc
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"

#ifdef CHANGED
void copyStringFromMachine(int from, char *to, unsigned size);
void copyStringToMachine(char* from, int to, unsigned size);
#endif

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions
//      are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);
#ifndef CHANGED
    if ((which == SyscallException) && (type == SC_Halt))
      {
	  DEBUG ('a', "Shutdown, initiated by user program.\n");
	  interrupt->Halt ();
      }
#else

	if (which == SyscallException) {
        switch (type) {

        case SC_Halt: {
          DEBUG('a', "Shutdown, initiated by user program.\n");
          interrupt->Halt();
          break;
        }

        case SC_PutChar: {
          DEBUG('a', "PutChar.\n");
          // On récupère le premier paramètre
          char c = (char)(machine->ReadRegister(4));
          // on l'affiche dans grâce à synchconsole
          synchconsole->SynchPutChar(c);
          break;
        }
        case SC_GetChar: {
				DEBUG('a', "GetChar.\n");
				machine->WriteRegister(2, (int)synchconsole->SynchGetChar());
				break;
			}
        case SC_PutString: {
				DEBUG('a', "PutString.\n");
				char* str = new char[MAX_STRING_SIZE];

				//bzero(str,MAX_STRING_SIZE);
				copyStringFromMachine(machine->ReadRegister(4), str, MAX_STRING_SIZE);
				//printf("appel de putstring\n");
				synchconsole->SynchPutString(str);
				//printf("retour de putstring\n");
				delete [] str;
				break;
		    }
        case SC_GetString: {
				DEBUG('a', "GetString.\n");
				char* str = new char[MAX_STRING_SIZE];
				synchconsole->SynchGetString(str, (int) machine->ReadRegister(5));
				copyStringToMachine(str, (int) machine->ReadRegister(4), (int) machine->ReadRegister(5));
				delete [] str;
				break;
			}
        case SC_PutInt: {
          DEBUG('a', "PutInt, initiated by user program.\n");
          int value = machine->ReadRegister(4);
          synchconsole->SynchPutInt(value);
          break;
        }
        case SC_GetInt: {
          DEBUG('a', "GetInt, initiated by user program.\n");       
	  int value = synchconsole->SynchGetInt();
          machine->WriteRegister(2, value);
          break;
        }


	case SC_UserThreadCreate: {	
				DEBUG('a', "UserThreadCreate.\n");	
				int id = do_UserThreadCreate((int) machine->ReadRegister(4), (int) machine->ReadRegister(5));
				machine->WriteRegister(2, id);
				break;
			}
	
	case SC_UserThreadExit: {
				DEBUG('a', "UserThreadExit.\n");	
				do_UserThreadExit();	
				break;
			}
	
			case SC_Exit: {
				currentThread->space->DecrNumThreads(); 
				while (currentThread->space->GetNumThreads() != 0)
					currentThread->Yield();
				DEBUG('a', "Exit, initiated by user program\n");
				interrupt->Halt();
				break;
			}

        default: {
          printf("Unexpected user mode exception %d %d\n", which, type);
          ASSERT(FALSE);
        }
      }
    }
    #endif 

    // LB: Do not forget to increment the pc before returning!
    UpdatePC ();
    // End of addition
}

#ifdef CHANGED
// copy a string from MIPS machine to Linux
// copy at most size characters
void copyStringFromMachine(int from, char *to, unsigned size)
{
	unsigned i = 0;
	int tmp;
	for(i = 0; i < size ; i++){
		if(machine->ReadMem(from + i, 1, &tmp))
		to[i]=tmp;
	}
	//si le message ne se finit pas par '\0'...
	if(i<size && tmp != '\0'){
	 	to[size-1] = '\0';
	}
}

// copy a string from Linux to MIPS machine
// copy at most size characters
void copyStringToMachine(char* from, int to, unsigned size)
{
  int tmp;
  unsigned int i;
  for(i = 0; i < size - 1; i++){
  	tmp = from[i];
   	machine->WriteMem(to + i, 1, tmp);
  }
  tmp = '\0';
  machine->WriteMem(to + i, 1, tmp);

}
#endif


