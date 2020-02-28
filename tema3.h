/*VLAD Andrei-Alexandru - 311CB*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct celula
{
	void *info;
	struct celula *urm;
}Celula, *TLista;

typedef struct asignare
{
	char *numeVar;
	int	valoare;
}Asign, *TAsign;

typedef struct arbore
{
	void *info;
	struct arbore *st, *dr;
}Arb, *TArb;

/*lista.c*/
void DistrugeLG(TLista *L);
TLista AlocaCelula(void *info);
TAsign InitAsign(char *var, int valoare);
void IntrodLG(TLista *L, void *celula);

/*evaluari.c*/
int giveValue(char *info, TLista ListaVar, FILE *output, int *ok);
int calculeaza(int A, int B, int operand, int *ok);
int solve(TArb t, FILE *output, TLista ListaVar, int *ok);
void rezolva(TArb t, FILE *output, TLista ListaVar);
int WhatIs(char *nod_info);
int isOperand(int operand);
char* ConstrInfo(char *temp);

/*arbore.c*/
TArb ConstrFr(void *x);
void InitArb(TArb *a, void *info);
TArb ConstrArbExpr(char *buffer);
void DistrugeArb(TArb *a);
TArb SubArbExpr();

void RSD(TArb a);
