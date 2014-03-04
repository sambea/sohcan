#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *stringWrite;
static Semaphore *stringRead;

static void ReadAvail(int arg) {
    readAvail->V();
}

static void WriteDone(int arg) {
    writeDone->V();
}

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
	stringWrite = new Semaphore("write string", 1);
	stringRead = new Semaphore("read string", 1);
}

SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete stringWrite;
    delete stringRead;
}

void SynchConsole::SynchPutChar(const char ch)
{
	console->PutChar (ch);
	writeDone->P ();
}


void SynchConsole::SynchPutString(const char s[])
{
    stringWrite->P();
	int i = 0;
	while (s[i] != '\0')
	{
		SynchPutChar(s[i++]);
	}
	stringWrite->V();

}


void SynchConsole::SynchPutInt(int value) {
  char * buffer = new char[MAX_STRING_SIZE];
  // on écrit dans le buffer la valeur avec sprintf
  snprintf(buffer,MAX_STRING_SIZE, "%d", value);
  this->SynchPutString(buffer);
  delete [] buffer;
}


#endif // CHANGED

