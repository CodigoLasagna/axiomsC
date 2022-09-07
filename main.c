#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

/*show P and Q*/
/*erases spaces from string*/
void cleanAxiom(char*);
/*divide axiom*/
void disolveAxiom(char*);
/*erases screen*/
void clean();
/*returns string size*/
int strlength(char*);

int main(){
	char* axiom = malloc(16);
	char p, q;
	bool P[] = {true, true, false, false}, Q[] = {true, false, true, false};
	printf("introduzca P:\n");
	scanf(" %c", &p);
	printf("introduzca Q:\n");
	scanf(" %c", &q);
	scanf(" %[^\n]", axiom);
	cleanAxiom(axiom);
	printf("%s", axiom);
	return 0;
}

void cleanAxiom(char* axiom){
	short i;
	int count = 0;
	for (i = 0; axiom[i] != '\0'; ++i){
		if (axiom[i] != ' '){
			axiom[count] = axiom[i];
			count++;
		}
	}
	axiom[count] = '\0';
}

void disolveAxiom(char* axiom){
	short i;
	for (i = 0; axiom[i] != '\0'; ++i){
		
	}
}

void clean(){
	short i;
	printf("\033[0;0H");
	for (i = 0; i < 35; i++)
		printf("                                     \n");
	printf("\033[0;0H");
}

int strlength(char* str){
	short counter = 0, i;
	for (i = 0; str[i] != '\0'; ++i){
		counter++;
	}
	return counter;
}
