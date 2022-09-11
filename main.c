#include <stdio.h>
#include <stdlib.h>
#include "bools.h"

/*check equality*/
void checkEquality(bool[], bool[]);

void conju(bool[], bool[], bool*);
void disy(bool[], bool[], bool*);
void cond(bool[], bool[], bool*);
void cond(bool[], bool[], bool*);
void bic(bool[], bool[], bool*);

/*solver for a side*/
void solveSimpleAxiom(char*, char, char, bool[], bool[], bool*);
/*decompose complex axiom*/
void solveCompoundAxiom(char*, char*, char*, bool*);
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
	char* compoundAxiom = malloc(16), *sideA = malloc(16), *sideB = malloc(16);
	bool parts = false;
	char v, P, Q;
	bool PA[] = {true, true, false, false}, QA[] = {true, false, true, false};
	bool ansA[4], ansB[4];
	int i;

	printf("introduzca P:\n");
	scanf(" %c", &P);
	printf("introduzca Q:\n");
	scanf(" %c", &Q);
	printf("Sus variables son\n");
	printVar(P, P, Q, PA, QA);
	printVar(Q, P, Q, PA, QA);
	while (true) {
		printf("\n>");
		scanf(" %[^\n]", compoundAxiom);
		cleanAxiom(compoundAxiom);
		solveCompoundAxiom(compoundAxiom, sideA, sideB, &parts);
		printf("\n---------------\n");
		printf("%s", compoundAxiom);
		printf("\n---------------");
		if (parts == false){
			solveSimpleAxiom(sideA, P, Q, PA, QA, ansA);
			printf("\n%s[", sideA);
			for (i = 0; i < 4; ++i)
				printf("%i", ansA[i]);
			printf("]\n");
		}else{
			solveSimpleAxiom(sideA, P, Q, PA, QA, ansA);
			solveSimpleAxiom(sideB, P, Q, PA, QA, ansB);
			printf("\n%s[", sideA);
			for (i = 0; i < 4; ++i)
				printf("%i", ansA[i]);
			printf("]");
			printf("\n%s[", sideB);
			for (i = 0; i < 4; ++i)
				printf("%i", ansB[i]);
			printf("]\n");
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

void solveSimpleAxiom(char* simpleAxiom, char P, char Q, bool PA[], bool QA[], bool ans[]){
	unsigned int i, j;
	char* child = malloc(16);
	bool childAns[4];
	int childN = 0;
	bool solution[2][4];
	char connector = '0';
	int selector = 0, childSelector = 0;
	bool recursive = false, negative = false;
	for (i = 0; simpleAxiom[i] != '\0'; ++i){
		if (simpleAxiom[i] != '!'){
			if (simpleAxiom[i] == '('){
				recursive = true;
				childN++;
			}
			if (recursive == false){
				if (simpleAxiom[i] == P){
					for (j = 0; j < 4; j++){
						if (negative == true){
							solution[selector][j] = !PA[j];
						}else{
							solution[selector][j] = PA[j];
						}
						/*
						ans[j] = PA[j];
						*/
					}
					selector++;
				}else if (simpleAxiom[i] == Q){
					for (j = 0; j < 4; j++){
						if (negative == true){
							solution[selector][j] = !QA[j];
						}else{
							solution[selector][j] = QA[j];
						}
						/*
						ans[j] = QA[j];
						*/
					}
					selector++;
				}else{
					if (simpleAxiom[i] != ')' && simpleAxiom[i] != P && simpleAxiom[i] != Q){
						connector = simpleAxiom[i];
					}
				}
				negative = false;
			}else{
				if (simpleAxiom[i] == ')'){
					solveSimpleAxiom(child, P, Q, PA, QA, childAns);
					for (j = 0; j < 4; j++){
						if (negative == true){
							solution[selector][j] = !childAns[j];
						}else{
							solution[selector][j] = childAns[j];
						}
					}
					/*
					if (childN == 1)
						printf("childA: %s\n", child);
					if (childN == 2)
						printf("childB: %s\n", child);
					*/
					selector++;
					child[childSelector+1] = '\0';
					childSelector = 0;
					recursive = false;
					negative = false;
				}
				if (simpleAxiom[i] != '(' && simpleAxiom[i] != ')'){ 
					child[childSelector] = simpleAxiom[i];
					childSelector++;
				}
			}
		}else{
			negative = true;
		}
	}
	/*
	if (connector != '0')
		printf("connector = %c\n", connector);
	if (childN > 0)
		printf("parent: %s\n", simpleAxiom);
	printf("----------\n");
	printf("parts of side: %i\n", selector);
	if (selector > 0){
		for (i = 0; i < 4; i++) {
			printf("%i", solution[0][i]);
		}
		printf("\n");
	}
	if (selector > 1){
		for (i = 0; i < 4; i++) {
			printf("%i", solution[1][i]);
		}
		printf("\n");
	}
	*/
	
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

void conju(bool P[], bool Q[], bool* PC){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == true){
			PC[i] = true;
		}else {
			PC[i] = false;
		}
	}
}
void disy(bool P[], bool Q[], bool PC[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == false && Q[i] == false){
			PC[i] = false;
		}else {
			PC[i] = true;
		}
	}
}
void cond(bool P[], bool Q[], bool PC[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == true && Q[i] == false){
			PC[i] = false;
		}else {
			PC[i] = true;
		}
	}
}
void bic(bool P[], bool Q[], bool PC[]){
	int i;
	for (i = 0; i < 4; ++i) {
		if (P[i] == Q[i]){
			PC[i] = true;
		}else {
			PC[i] = false;
		}
	}
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
