#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;
static Semaphore *handleWrite;
static Semaphore *handleRead;

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
	handleWrite = new Semaphore("write string", 1);
	handleRead = new Semaphore("read string", 1);
}

SynchConsole::~SynchConsole()
{
    delete console;
    delete writeDone;
    delete readAvail;
    delete handleWrite;
    delete handleRead;
}

void SynchConsole::SynchPutChar(const char ch)
{
	console->PutChar (ch);
	writeDone->P ();
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
	handleRead->P();
	int i = 0;
	while (i < n)
	{
		s[i] = SynchGetChar();
		if (s[i] == '\n' || s[i] == '\0' || s[i] == EOF)
			break;
		i++;
	}
	s[n-1] = '\0';
	handleRead->V();
}


void SynchConsole::SynchGetString(char *s, int n,char end)
{
	handleRead->P();
	int i = 0;
	while (i < n)
	{
		s[i] = SynchGetChar();
		if (s[i] == end || s[i] == '\0' || s[i] == EOF)
			break;
		i++;
	}
	s[n-1] = '\0';
	handleRead->V();
}

void SynchConsole::SynchPutInt(int value) {
  char * buffer = new char[MAX_STRING_SIZE];
  //écriture dans le buffer la valeur avec sprintf
  snprintf(buffer,MAX_STRING_SIZE, "%d", value);
  this->SynchPutString(buffer);
  delete [] buffer;
}

int SynchConsole::SynchGetInt() {
  int value;
  char * buffer = new char[MAX_STRING_SIZE];
  this->SynchGetString(buffer, MAX_STRING_SIZE, '\n');
  sscanf(buffer, "%d", &value);
  delete [] buffer;
  return value;
}

#endif // CHANGED

