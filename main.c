#include <stdio.h>
#include <stdlib.h>

void clean();
int strlength(char* );

int main(){
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
