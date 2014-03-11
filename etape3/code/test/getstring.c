#include "syscall.h"

int main() {
  PutString("Veuillez saisir une phrase (max = 100) : ");
  char buffer[100];
  GetString(buffer,100);
  PutString("\nVoici la phrase : ");
  PutString(buffer);
  PutChar('\n');
  Halt();
  return 0;
}
