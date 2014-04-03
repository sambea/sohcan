#include "syscall.h"

void put(int i) {
	PutString(" Fonction execute par le thread utilisateur ");
	PutInt(i);
	PutString("\n");
	UserThreadExit();
}
int main() {
	PutString("Début du programme utilisateur\n");
	int i;
	for (i=0;i<3;i++){ // creation de 3 threads utilisateur
		if( UserThreadCreate(put,(void *)i) == -1){
			PutString("Erreur lors de la creation du thread (espace d'adressage)\n");
		}
	}
	PutString("Fin\n");
	return 0;
}
