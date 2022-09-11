#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

/*decompose complex axiom*/
void solveComplexAxiom(char*);
/*check variable for var list*/
void printVar(char, char, char, bool [], bool []);
/*print values from var*/
void printValue(char, bool []);
/*erases spaces from string*/
void cleanAxiom(char*);
/*erases screen*/
void clean();
/*returns string size*/
int strlength(char*);

int main(){
	char* axiom = malloc(16);
	char v, P, Q;
	bool PA[] = {true, true, false, false}, QA[] = {true, false, true, false};
	printf("introduzca P:\n");
	scanf(" %c", &P);
	printf("introduzca Q:\n");
	scanf(" %c", &Q);
	printf("Sus variables son\n");
	printVar(P, P, Q, PA, QA);
	printVar(Q, P, Q, PA, QA);
	while (true) {
		scanf(" %[^\n]", axiom);
		cleanAxiom(axiom);
		solveComplexAxiom(axiom);
	}
	return 0;
}

void solveComplexAxiom(char* axiom){
	char* sideA = malloc(32);
	char* sideB = malloc(32);
	unsigned int i = 0, counter = 0, turn = 0;
	for (i = 0; axiom[i] != '\0'; ++i){
		if (axiom[i] != '='){
			if (turn == 0){
				sideA[counter] = axiom[i];
			}else{
				sideA[counter] = axiom[i];
			}
		}else{
			counter = 0;
			turn = 1;
		}
		counter++;
	}
	printf("%s\n", sideA);
	printf("%s\n", sideB);
}

void printVar(char v, char P, char Q, bool PA[], bool QA[]){
	if (v == P){
		printValue(v, PA);
	}
	if (v == Q){
		printValue(v, QA);
	}
}

void printValue(char v, bool VA[]){
	short i;
	printf("%c [", v);
	for (i = 0; i < 4; ++i){
		printf("%i", VA[i]);
	}
	printf("]\n");
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
