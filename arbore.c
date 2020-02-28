/*VLAD Andrei-Alexandru - 311CB*/

#include "tema3.h"

TArb ConstrFr(void *info)
/*Functia construieste o frunza care contine pointer catre o informatie*/
/*Acest nod nu are fiu stang sau drept*/
{
	/*Aloca memorie pentru un nod*/
	TArb a = (TArb) calloc(1, sizeof(struct arbore));
	/*Verifica alocarea*/
	if(!a) {return NULL;}

	/*Seteaza campul info*/
	a->info = info;
	/*Seteaza cu NULL fiul stang si drept*/
	a->st = NULL;
	a->dr = NULL;

	return a;
}

void InitArb(TArb *a, void *info)
/*Functia insereaza in arborele a o frunza cu informatia data*/
/*Daca inserarea nu se realizeaza din cauza esuarii alocarii
de memorie, arborele ramane neschimbat si informatia nu se adauga*/
{
	if(*a == NULL)
	{
		*a = ConstrFr(info);
		return;
	}
}

TArb SubArbExpr()
{
	TArb arb = NULL;
	char *temp = NULL;
	temp = strtok(NULL, " \n");

	/*Conditie de iesire din recursivitate*/
	if(temp == NULL)	{return NULL;}

	char *nod_info = ConstrInfo(temp);
	if(!nod_info)	{return NULL;}

	int operand = WhatIs(nod_info);
	if(isOperand(operand) == 1)
	{
		InitArb(&arb, nod_info);
		arb->st = SubArbExpr();
		if(WhatIs(nod_info) != 6)
			arb->dr = SubArbExpr();

		return arb;
	}else
	{
		return ConstrFr(nod_info);
	}
}

TArb ConstrArbExpr(char *buffer)
/*Functia creeaza si intoarce un arbore de expresie delimitand bufferul trimis
ca parametru*/
{
	TArb arb = NULL;
	char *temp = NULL;

	temp = strtok(buffer, " \n");
	char *nod_info = ConstrInfo(temp);
	if(!nod_info)	{return NULL;}

	int operand = WhatIs(nod_info);
	if(isOperand(operand) != 1)
	{
		printf("Invalid expression\n");
		free(nod_info);
		return NULL;
	}

	InitArb(&arb, nod_info);
	arb->st = SubArbExpr();
	arb->dr = SubArbExpr();

	return arb;
}

void RSD(TArb a)
{
	if(!a) {printf("   "); return;}
	if(!a->st && !a->dr) {printf(" %s ", (char*)(a->info)); return;}
	printf(" %s ", (char*)(a->info));
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}

void DistrugeArb(TArb *a)
/*Functia de distrugere a arborelui de la curs*/
{
	if(*a == NULL)	{return;}

	DistrugeArb(&((*a)->st));
	DistrugeArb(&((*a)->dr));

	free((*a)->info);
	free(*a);
	*a = NULL;
}