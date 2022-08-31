#include <stdio.h>
#include <stdlib.h>
#include "propositions.h"

void clean();
int strlength(char* );

int main(){
	int lim = 10;
	bool P[] = {true, true, false, false}, Q[] = {true, false, true, false};
	char type[] = {'!', '^', 'v', '>', '<', '-', '=', '(', ')'};
	char p, q, T;
	char* axiom = malloc(32);
	char* partA = malloc(32), *partB = malloc(32);
	bool PA[4], PB[4];
	
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
		if (strlength(axiom) > 1){
			solveCompAxiom(axiom, p, q, P, Q, partA, partB);
			solveAxiom(partA, p, q, P, Q, &PA);
			solveAxiom(partB, p, q, P, Q, &PB);
			equal(partA, partB, PA, PB);
		}else{
			printf("  %c\n", axiom[0]);
			printf("-----\n");
			if (axiom[0] == p){
				for(int i = 0; i < 4; ++i){
					printf("  %i\n", P[i]);
				}
			}else if (axiom[0] == q){
				for(int i = 0; i < 4; ++i){
					printf("  %i\n", Q[i]);
				}
			}
		}
	}
	return 0;
}

void clean(){
	printf("\033[0;0H");
	for (int i = 0; i < 35; i++)
		printf("                                     \n");
	printf("\033[0;0H");
}
int strlength(char* axiom){
	int counter = 0;
	for (int i = 0; axiom[i] != '\0'; ++i){
		counter++;
	}
	return counter;
}
