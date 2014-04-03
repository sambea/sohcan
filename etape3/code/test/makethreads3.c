#include "syscall.h"

void print(int i){
  PutInt(i);
  if(i%2 == 1){
    PutString("  je suis un nombre impair\n");
  }
  else {
     PutString("  Je suis un nombre pair\n");
  }
  
  UserThreadExit();
}


int main(){
  int i = 36;
  int j = 56;
  int k = 87;

  
  PutString("Début du main...\n");
  UserThreadCreate(print,(void*)i);
  UserThreadCreate(print,(void*)j);
  UserThreadCreate(print,(void*)k);
  

  Exit(0);



}
