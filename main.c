#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

void clean();
void cleanAxiom(char(*)[]);
int strlength(char* );

int main(){
	char* axiom = malloc(16);
	char p, q;
	bool P[] = {true, true, false, false}, Q[] = {true, false, true, false};
	scanf(" %[^\n]", axiom);
	return 0;
}

void cleanAxiom(char(*axiom)[]){
	int i;
	for (i = 0; (*axiom)[i] != '\n'; ++i){

	}

}
void clean(){
	int i;
	printf("\033[0;0H");
	for (i = 0; i < 35; i++)
		printf("                                     \n");
	printf("\033[0;0H");
}
int strlength(char* axiom){
	int counter = 0, i;
	for (i = 0; axiom[i] != '\0'; ++i){
		counter++;
	}
	return counter;
}
