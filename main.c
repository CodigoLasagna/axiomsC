#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

/*check equality*/
void checkEquality(bool[], bool[]);

void conju(bool[], bool[], bool*);
void disy(bool[], bool[], bool*);
void cond(bool[], bool[], bool*);
void bic(bool[], bool[], bool*);

/*solver for a side*/
void solveSimpleAxiom(char*, char, char, char, bool[], bool*);
/*decompose complex axiom*/
void solveCompoundAxiom(char*, char*, char*, bool*);
/*check variable for var list*/
void printVar(char, bool []);
/*print values from var*/
void printValue(char*, bool []);
/*erases spaces from string*/
void cleanAxiom(char*);

int main(){
	char* compoundAxiom = malloc(16), *sideA = malloc(16), *sideB = malloc(16);
	bool parts = false, debug = true;
	char v, P, Q, R;
	bool tTable[] = {true, true, false, false,
					 true, false, true, false,
					 true, false, false, true};
	bool ansA[4], ansB[4];
	int i;
	printf("introduzca P:\n");
	scanf(" %c", &P);
	printf("introduzca Q:\n");
	scanf(" %c", &Q);
	printf("introduzca R:\n");
	scanf(" %c", &R);
	printf("Sus literales son\n");
	printVar(P, tTable);
	printVar(Q, tTable+4);
	printVar(R, tTable+8);
	if (debug == true){
		printf("introduzca una literal simple como '%c'\nuna proposicion simple como la de abajo\n", P);
		printf("%c>%c\no un axioma complejo como alguno de los siguientes\n", P, Q);
		printf("%c>%c=!%c>!%c\n", P, Q, Q, P);
		printf("%c-%c=(%c>%c)^(%c<%c)\n", P, Q, P, Q, P, Q);
		printf("%cv(%c^%c)=(%cv%c)^(%cv%c)\n", P, Q, R, P, Q, P, R);
		printf("las siguientes conectivas logicas pueden ser usadas\n");
		printf("[!]negacion\n[^]conjucion\n[v]disyuncion\n[>]condicional izq. a der.\n[<]condicional der. a izq.\n[-]bicondicional\n");
	}
	while (true) {
		printf("\n---------------");
		printf("\n>");
		scanf(" %[^\n]", compoundAxiom);
		printf("---------------\n");
		cleanAxiom(compoundAxiom);
		solveCompoundAxiom(compoundAxiom, sideA, sideB, &parts);
		if (parts == false){
			solveSimpleAxiom(sideA, P, Q, R, tTable, ansA);
			printValue(sideA, ansA);
		}else{
			solveSimpleAxiom(sideA, P, Q, R, tTable, ansA);
			solveSimpleAxiom(sideB, P, Q, R, tTable, ansB);
			printValue(sideA, ansA);
			printValue(sideB, ansB);
			checkEquality(ansA, ansB);
		}
		parts = false;
	}
	return 0;
}

void checkEquality(bool sideA[], bool sideB[]){
	int i, counter = 0;
	for (i = 0; i < 4; ++i){
		if (sideA[i] == sideB[i])
			counter++;
	}
	if (counter == 4){
		printf("demostracion verdadera\n");
	}else{
		printf("demostracion falsa\n");
	}
}

void solveSimpleAxiom(char* simpleAxiom, char P, char Q, char R, bool tTable[], bool ans[]){
	unsigned int i, j;
	int selector = 0, childSelector = 0, literal = 1;
	char* child = malloc(16), connector = '0', v = ' ';
	bool childAns[4], solution[2][4];
	bool recursive = false, negative = false;
	for (i = 0; simpleAxiom[i] != '\0'; ++i){
		if (simpleAxiom[i] == '!'){
			negative = true;
			i++;
		}
		if (simpleAxiom[i] == '('){
			recursive = true;
			i++;
		}
		if (simpleAxiom[i] == ')'){
			selector++;
			childSelector = 0;
			recursive = false;
			negative = false;
		}
		if (recursive == false){
			if (simpleAxiom[i] == P || simpleAxiom[i] == Q || simpleAxiom[i] == R){
				if (simpleAxiom[i] == P){
					literal = 0;
				}
				if (simpleAxiom[i] == Q){
					literal = 1;
				}
				if (simpleAxiom[i] == R){
					literal = 2;
				}
				for (j = 0; j < 4; j++){
					solution[selector][j] = negative ? !tTable[literal*4+j]:tTable[literal*4+j];
				}
				selector++;
			}else{
				if (selector == 1){
					connector = simpleAxiom[i];
				}
			}
			negative = false;
		}
		if (recursive == true){
			child[childSelector] = simpleAxiom[i];
			childSelector++;
			child[childSelector+1] = '\0';
			solveSimpleAxiom(child, P, Q, R, tTable, childAns);
			for (j = 0; j < 4; j++){
				solution[selector][j] = negative ? !childAns[j]:childAns[j];
			}
		}
		
	}
	if (selector > 1){
		switch (connector) {
			case '^':
				conju(solution[0], solution[1], ans);
			break;
			case 'v':
				disy(solution[0], solution[1], ans);
			break;
			case '>':
				cond(solution[0], solution[1], ans);
			break;
			case '<':
				cond(solution[1], solution[0], ans);
			break;
			case '-':
				bic(solution[0], solution[1], ans);
			break;
		}
	}else{
		for (i = 0; i < 4; ++i){
			ans[i] = solution[0][i];
		}
	}
	selector = 0;
}

void solveCompoundAxiom(char* axiom, char* sideA, char* sideB, bool* parts){
	unsigned int i = 0, counter = 0;
	bool toggler = false;
	for (i = 0; axiom[i] != '\0'; i++){
		if (axiom[i] != '='){
			if (toggler == false){
				sideA[counter] = axiom[i];
				sideA[counter+1] = '\0';
			}else{
				sideB[counter] = axiom[i];
				sideB[counter+1] = '\0';
			}
			counter++;
		}else if (axiom[i] == '='){
			toggler = true;
			counter = 0;
			*parts = true;
		}
	}
}

void conju(bool inpA[], bool inpB[], bool* ans){
	int i;
	for (i = 0; i < 4; ++i) {
		if (inpA[i] == true && inpB[i] == true){
			ans[i] = true;
		}else {
			ans[i] = false;
		}
	}
}

void disy(bool inpA[], bool inpB[], bool ans[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (inpA[i] == false && inpB[i] == false){
			ans[i] = false;
		}else {
			ans[i] = true;
		}
	}
}

void cond(bool inpA[], bool inpB[], bool ans[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (inpA[i] == true && inpB[i] == false){
			ans[i] = false;
		}else {
			ans[i] = true;
		}
	}
}

void bic(bool inpA[], bool inpB[], bool ans[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (inpA[i] == inpB[i]){
			ans[i] = true;
		}else {
			ans[i] = false;
		}
	}
}

void printVar(char v, bool QA[]){
	char* t = &v;
	printValue(t, QA);
}

void printValue(char* v, bool VA[]){
	short i;
	printf("[");
	for (i = 0; i < 4; ++i){
		printf("%i", VA[i]);
	}
	printf("] %s\n", v);
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
