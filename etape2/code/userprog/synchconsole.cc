#ifdef CHANGED
#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include "console.h"


static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *handleWrite;
static Semaphore *handleRead;
static Semaphore *handleWriteInt;
static Semaphore *handleReadInt;


static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console(readFile, writeFile, ReadAvail, WriteDone, 0); 

	handleWrite = new Semaphore("handleWrite", 1);
	handleWrite = new Semaphore("handleWrite", 1);
	handleRead = new Semaphore("handleRead", 1);
	handleWriteInt = new Semaphore("handleWriteInt", 1);
	handleReadInt = new Semaphore("handleReadInt", 1);
}

SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch)
{
  
	console->PutChar(ch);
        writeDone->P();
}

char SynchConsole::SynchGetChar()
{
	readAvail->P ();
	return console->GetChar ();


}

void SynchConsole::SynchPutString(const char s[])
{
	handleWrite->P();
	int i = 0;
	while (s[i] != '\0')
	{
		SynchPutChar(s[i++]);
	}
    handleWrite->V();    
}

void SynchConsole::SynchGetString(char *s, int n)
{
	int i;
	char c;	
	handleRead->P();
	for(i=0; i < n-1; i++){
		c = synchconsole->SynchGetChar();
		if(c == EOF || c == '\n'){
			break;
		}else{
			s[i] = c;
		}
	}
	s[i] = '\0';
	handleRead->V();
}


void SynchConsole::SynchGetString2(char *s, int n,char end)
{
	int i;
	char c;	
	handleRead->P();
	for(i=0; i < n-1; i++){
		c = synchconsole->SynchGetChar();
		if(c == end || c == '\n'){
			break;
		}else{
			s[i] = c;
		}
	}
	s[i] = '\0';
	handleRead->V();
}


void SynchConsole::SynchPutInt(int value) {
  char * buffer = new char[MAX_STRING_SIZE];
handleWriteInt->P();
  //écriture dans le buffer la valeur avec sprintf
 snprintf(buffer,MAX_STRING_SIZE, "%d", value);
  this->SynchPutString(buffer);
  delete [] buffer;
handleWriteInt->V();
}

int SynchConsole::SynchGetInt() {
  int value;
  char * buffer = new char[MAX_STRING_SIZE];
handleReadInt->P();
  this->SynchGetString2(buffer, MAX_STRING_SIZE, '\n');
  sscanf(buffer, "%d", &value);
  delete [] buffer;
  return value;
handleReadInt->V();
}


#endif // CHANGED
