#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

bool norm(bool Q[]);
bool dnot(bool []);
bool con(bool [], bool []);
bool disy(bool [], bool []);
bool cond(bool [], bool []);
bool bic(bool [], bool []);
char* getAxiom(char*);
void solveAxiom(char*, char p, char q, bool P[], bool Q[]);
void solveCompAxiom(char*, char p, char q, bool P[], bool Q[], char*, char*);
void addAxiom(char *input, bool *bin[], char axiom, bool in[]);
void clean();

int main(){
	int lim = 10;
	bool P[] = {true, true, false, false}, Q[] = {true, false, true, false};
	char type[] = {'!', '^', 'v', '>', '<', '-'};
	char p, q, T;
	char* axiom = malloc(32);
	char* partA = malloc(32), *partB = malloc(32);
	
	printf(">:");
	scanf(" %c", &p);
	scanf(" %c", &q);
	clean();
	printf("%c : %c\t\n", p, q);
	printf("-----\n");
	for(int i = 0; i < 4; ++i){
		printf("%i : %i\t\n", P[i], Q[i]);
	}
	while(true){
		printf("-----\n");
		printf("input\n-----\n");
		scanf(" %[^\n]", axiom);
		clean();
		getAxiom(axiom);
		solveCompAxiom(axiom, p, q, P, Q, partA, partB);
		solveAxiom(partA, p, q, P, Q);
		solveAxiom(partB, p, q, P, Q);
		//printf("%s\n", partA);
		//printf("%s\n", partB);
		//solveAxiom(axiom, p, q, P, Q);
	}
	return 0;
}

void solveCompAxiom(char* axiom, char p, char q, bool P[], bool Q[], char* partA, char* partB){
	bool left[2][4], right[2][4];
	bool toggler = false;
	int counter = 0;
	for (int i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] != '='){
			if (toggler == false){
				partA[counter] = axiom[i];
			}else{
				partB[counter] = axiom[i];
			}
			counter++;
		}else if (axiom[i] == '='){
			toggler = true;
			counter = 0;
		}
	}
	//for (int i = 0; axiom[i] != '\0'; i++){
	//	if (axiom[i] != '='){
	//		if (axiom[i] == p || axiom[i] == q){
	//			if (axiom[i+1] != '\0' && axiom[i+2] != '\0'){
	//				if (axiom[i+2] !='(' && axiom[i+2] != ')'){
	//					if(axiom[i+1] != p && axiom[i+1] != q && axiom[i+1] != '='){
	//						printf("x");
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}

void solveAxiom(char* axiom, char p, char q, bool P[], bool Q[]){
	char type = ' ';
	char inputA = ' ', inputB = ' ', axiomType = ' ';
	bool *binA[4], *binB[4];
	for (int i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] == p){
			if (inputA == ' '){
				addAxiom(&inputA, binA, axiom[i], P);
			}else{
				addAxiom(&inputB, binB, axiom[i], P);
			}
		}else if(axiom[i] == q){
			if (inputA == ' '){
				addAxiom(&inputA, binA, axiom[i], Q);
			}else{
				addAxiom(&inputB, binB, axiom[i], Q);
			}
		}else{
			axiomType = axiom[i];
		}
	}
	
	if (axiomType != '!')
		printf("%c %c %c\t\n", inputA, axiomType, inputB);
	else
		printf(" %c%c \n", axiomType, inputA);
	printf("-----\n");
	switch (axiomType) {
		case '!':
			dnot(*binA);
		break;
		case '^':
			con(*binA, *binB);
		break;
		case 'v':
			disy(*binA, *binB);
		break;
		case '>':
			cond(*binA, *binB);
		break;
		case '<':
			cond(*binB, *binA);
		break;
		case '-':
			bic(*binA, *binB);
		break;
	}
}

void addAxiom(char *input, bool *bin[], char axiom, bool in[]){
	input[0] = axiom;
	for (int i = 0; i < 4; i++)
		bin[i] = &in[i];
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

bool norm(bool Q[]){
	for (int i = 0; i < 4; ++i) {
		if (Q[i] == true){
			printf("  %i  \n", true);
		}else {
			printf("  %i  \n", false);
		}
	}
	return 0;
}

bool dnot(bool Q[]){
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
void clean(){
	printf("\033[0;0H");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("                                     \n");
	printf("\033[0;0H");
}
