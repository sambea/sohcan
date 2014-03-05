#include "syscall.h"

int main() {
  PutString("Veuillez saisir une lettre : \n");
  char c = GetChar();
  PutString("Voici la lettre : ");
  PutChar(c);
  PutChar('\n');
  Halt();
  return 0;
}
