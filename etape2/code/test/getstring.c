#include "syscall.h"

int main() {
  PutString("Veuillez saisir une phrase de 100 caractères maximum:\n");
  char buffer[100];
  GetString(buffer,100);
  PutString("\nVoici la phrase : ");
  PutString(buffer);
  PutChar('\n');
  Halt();
  return 0;
}
