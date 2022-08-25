#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bools.h"

bool not(bool []);
bool con(bool [], bool []);
bool disy(bool [], bool []);
bool cond(bool [], bool []);
bool bic(bool [], bool []);
char* getAxiom(char*);
void solveAciom(char*, char p, char q, bool P[], bool Q[]);

int main(){
	bool ans = false;
	int lim = 10;
	bool P[] = {true, true, false, false}, Q[] = {true, false, true, false};
	char type[] = {'!', '^', 'v', '>', '<', '-'};
	char p, q, T;
	char* axiom = malloc(32);
	//scanf(" %[^\n]", axiom);
	//getAxiom(axiom);
	//printf("%s\n", axiom);
	printf(">:");
	scanf(" %c", &p);
	scanf(" %c", &q);
	printf("\n%c : %c\t\n", p, q);
	printf("-----\n");
	for(int i = 0; i < 4; ++i){
		printf("%i : %i\t\n", P[i], Q[i]);
	}
	printf("\n");
	while(true){
		printf("-----\n");
		printf("write an axiom\n-----\n");
		scanf(" %[^\n]", axiom);
		getAxiom(axiom);
		solveAciom(axiom, p, q, P, Q);
	}
	return 0;
}

void solveAciom(char* axiom, char p, char q, bool P[], bool Q[]){
	char type = ' ';
	char inputA = ' ', inputB = ' ', axiomType = ' ';
	bool binA[4], binB[4];
	for (int i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] == p){
			if (inputA == ' '){
				inputA = axiom[i];
				for (int i = 0; i < 4; i++)
					binA[i] = P[i];
			}else{
				inputB = axiom[i];
				for (int i = 0; i < 4; i++)
					binB[i] = P[i];
			}
		}else if(axiom[i] == q){
			if (inputA == ' '){
				inputA = axiom[i];
				for (int i = 0; i < 4; i++)
					binA[i] = Q[i];
			}else{
				inputB = axiom[i];
				for (int i = 0; i < 4; i++)
					binB[i] = Q[i];
			}
		}else{
			axiomType = axiom[i];
		}
	}
	//printf("%c\n", inputA);
	//printf("%c\n", axiomType);
	//printf("%c\n", inputB);
	//for (int i = 0; i < 4; i++){
	//	printf("%s\n", printb(binA[i]));
	//}
	//printf("\n-----\n");
	//for (int i = 0; i < 4; i++){
	//	printf("%s\n", printb(binB[i]));
	//}
	
	if (axiomType != '!')
		printf("\n%c %c %c\t\n", inputA, axiomType, inputB);
	else
		printf("  %c \n", inputA);
	printf("-----\n");
	switch (axiomType) {
		case '!':
			not(binA);
		break;
		case '^':
			con(binA, binB);
		break;
		case 'v':
			disy(binA, binB);
		break;
		case '>':
			cond(binA, binB);
		break;
		case '<':
			cond(binB, binA);
		break;
		case '-':
			bic(binA, binB);
		break;
	}
	printf("\n");
}

char* getAxiom(char* axiom){
	int count = 0;
	for (int i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] != ' '){
			axiom[count] = axiom[i];
			count++;
		}
	}
	axiom[count] = '\0';
	return axiom;
}

bool not(bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (Q[i] == true){
			printf("  %i  \n", false);
		}else {
			printf("  %i  \n", true);
		}
	}
	return 0;
}
bool con(bool P[], bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == true){
			printf("  %i  \n", true);
		}else {
			printf("  %i  \n", false);
		}
	}
	return 0;
}
bool disy(bool P[], bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (P[i] == false && Q[i] == false){
			printf("  %i  \n", false);
		}else {
			printf("  %i  \n", true);
		}
	}
	return 0;
}
bool cond(bool P[], bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == false){
			printf("  %i  \n", false);
		}else {
			printf("  %i  \n", true);
		}
	}
	return 0;
}
bool bic(bool P[], bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (P[i] == Q[i]){
			printf("  %i  \n", true);
		}else {
			printf("  %i  \n", false);
		}
	}
	return 0;
}
