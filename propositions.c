#include "propositions.h"
void solveCompAxiom(char* axiom, char p, char q, bool P[], bool Q[], char* partA, char* partB){
	bool left[2][4], right[2][4];
	bool toggler = false;
	int counter = 0, i;
	for (i = 0; axiom[i] != '\0'; i++){
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
}

void solveAxiom(char* axiom, char p, char q, bool P[], bool Q[], bool(*PC)[]){
	char type = ' ';
	char inputA = ' ', inputB = ' ', axiomType = ' ';
	bool *binA[4], *binB[4];
	int i;
	for (i = 0; axiom[i] != '\0'; i++){
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
	
	printf("-----\n");
	if (axiomType != '!')
		printf("%c %c %c\t\n", inputA, axiomType, inputB);
	else
		printf(" %c%c \n", axiomType, inputA);
	printf("-----\n");
	switch (axiomType) {
		case '!':
			dnot(*binA, PC);
		break;
		case '^':
			con(*binA, *binB, PC);
		break;
		case 'v':
			disy(*binA, *binB, PC);
		break;
		case '>':
			cond(*binA, *binB, PC);
		break;
		case '<':
			cond(*binB, *binA, PC);
		break;
		case '-':
			bic(*binA, *binB, PC);
		break;
	}
}

void addAxiom(char *input, bool *bin[], char axiom, bool in[]){
	int i;
	input[0] = axiom;
	for (i = 0; i < 4; i++)
		bin[i] = &in[i];
}

char* getAxiom(char* axiom){
	int i;
	int count = 0;
	for (i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] != ' '){
			axiom[count] = axiom[i];
			count++;
		}
	}
	axiom[count] = '\0';
	return axiom;
}

bool dnot(bool Q[], bool (*PC)[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (Q[i] == true){
			printf("  %i  \n", false);
			(*PC)[i] = false;
		}else {
			printf("  %i  \n", true);
			(*PC)[i] = true;
		}
	}
	return 0;
}
bool con(bool P[], bool Q[], bool (*PC)[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == true){
			printf("  %i  \n", true);
			(*PC)[i] = true;
		}else {
			printf("  %i  \n", false);
			(*PC)[i] = false;
		}
	}
	return 0;
}
bool disy(bool P[], bool Q[], bool (*PC)[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == false && Q[i] == false){
			printf("  %i  \n", false);
			(*PC)[i] = false;
		}else {
			printf("  %i  \n", true);
			(*PC)[i] = true;
		}
	}
	return 0;
}
bool cond(bool P[], bool Q[], bool (*PC)[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == false){
			printf("  %i  \n", false);
			(*PC)[i] = false;
		}else {
			printf("  %i  \n", true);
			(*PC)[i] = true;
		}
	}
	return 0;
}
bool bic(bool P[], bool Q[], bool (*PC)[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == Q[i]){
			printf("  %i  \n", true);
			(*PC)[i] = true;
		}else {
			printf("  %i  \n", false);
			(*PC)[i] = false;
		}
	}
	return 0;
}

void equal(char* partA, char* partB, bool PA[], bool PB[]){
	int i;
	printf("\n-----------\n");
	printf("  %s=%s\n", partA, partB);
	printf("-----------\n");
	bool valid = false;
	int counter = 0;
	for (i = 0; i < 4; ++i){
		if (PA[i] == PB[i]) {
			valid = true;
			counter++;
		}else{
			valid = false;
		}
		printf(" %i = %i : %i\n", PA[i], PB[i], valid);
	}
	if (counter == 4){
		printf("-----------\n");
		printf("Equivalente\n");
	}else{
		printf("-------------\n");
		printf("Inequivalente\n");
	}
}
