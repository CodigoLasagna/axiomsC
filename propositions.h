#include "bools.h"
#include <stdio.h>
//negación
bool dnot(bool [], bool(*)[]);
//conjución
bool con(bool [], bool [], bool(*)[]);
//disyunción
bool disy(bool [], bool [], bool(*)[]);
//condicional
bool cond(bool [], bool [], bool(*)[]);
//bicondicional
bool bic(bool [], bool [], bool(*)[]);
bool norm(bool Q[], bool(*)[]);
char* getAxiom(char*);
void solveAxiom(char*, char p, char q, bool P[], bool Q[], bool(*)[]);
void solveCompAxiom(char*, char p, char q, bool P[], bool Q[], char*, char*);
void addAxiom(char *input, bool *bin[], char axiom, bool in[]);
void equal(char*, char*, bool[], bool[]);
