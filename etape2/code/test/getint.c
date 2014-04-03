#include "syscall.h"

int main() {
  PutString("Veuillez saisir un nombre : \n");
  int nombre = GetInt();
  PutString("Your number +100 = ");
  PutInt(nombre+100);
  PutChar('\n');
  Halt();
  return 0;
}
