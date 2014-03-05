#include "syscall.h"

int main() {
  PutString("Veuillez saisir un nombre : \n");
  int nombre = GetInt();
  PutString("Nombre +10 = ");
  PutInt(nombre+10);
  PutChar('\n');
  Halt();
  return 0;
}
