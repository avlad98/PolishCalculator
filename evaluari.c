#include "tema3.h"

int WhatIs(char *nod_info)
/*VLAD Andrei-Alexandru - 311CB*/

/*Functia returneaza un index dupa care se verifica daca string-ul primit
	este operator sau nu. Daca este operator returneaza un indice.
	Daca nu este operator se intoarce -1*/
{
	if(strcmp(nod_info, "-") == 0)		{return 1;}
	if(strcmp(nod_info, "+") == 0)		{return 2;}
	if(strcmp(nod_info, "*") == 0)		{return 3;}
	if(strcmp(nod_info, "/") == 0)		{return 4;}
	if(strcmp(nod_info, "^") == 0)		{return 5;}
	if(strcmp(nod_info, "sqrt") == 0)	{return 6;}

	return -1;
}

int isOperand(int operand)
/*Daca semnul delimitat este o valoare intre 1 si 6 inclusiv
returnez 1 (operand este un semn de operatie sau radical)
		-1 caz contrar*/
{
	if(operand > 0 && operand < 7)
		return 1;

	return -1;
}

char* ConstrInfo(char *temp)
{
	char *nod_info = NULL;
	nod_info = (char *) calloc(1, strlen(temp) + 1);
	if(!nod_info)	{printf("Nu s-a alocat informatia\n"); return NULL;}
	memcpy(nod_info, temp, strlen(temp));

	return nod_info;
}

int calculeaza(int A, int B, int operand, int *ok)
/*Functia calculeaza expresia si intoarce rezultatul.
Daca expresia nu este valida se modifica "ok" in -1,
iar rezultatul intors nu mai conteaza*/
{
	if(*ok != 1)	{return -10000;}
	switch(operand)
	{
		case 1:
		// Operatia -
			return A - B;
			break;

		case 2:
		// Operatia +
			return A + B;
			break;

		case 3:
		// Operatia *
			return A * B;
			break;

		case 4:
		// Operatia /
			if(B == 0)
			{
				*ok = -1;
				return -1;
			}

			return A / B;
			break;

		case 5:
		// Operatia ^
			return pow(A, B);
			break;

		case 6:
		// Operatia sqrt
			if(A < 0)
			{
				*ok = -1;
				return -1;
			}

			return sqrt(A);
			break;

		default:
			/*Nu ar trebui sa ajunga aici*/
			break;

	}

	return -1;
}


int giveValue(char *info, TLista ListaVar, FILE *output, int *ok)
/*
	Functia intoarce valoarea variabilei (daca este variabila)
	sau intoarce valoarea numerica a string-ului cu numar

	Daca variabila nu este declarata "ok" va lua valoarea 0
	si valoarea de retur a functiei nu mai conteaza
*/
{
	if(*ok != 1)	{return -10000;}
	char aux = '\0';

	memcpy(&aux, info, 1 * sizeof(char));
	if(aux == '-')
	{
		return(atoi(info));
	}
		
	if(aux >= '0' && aux <= '9')
	{
		return atoi(info);
	}
	
	TAsign asignare = NULL;
	while(ListaVar != NULL)
	{
		asignare = (TAsign)(ListaVar->info);
		if(strcmp(info, asignare->numeVar) == 0)
		{
			return asignare->valoare;
		}
		
		//Avans in lista de variabile
		ListaVar = ListaVar->urm;
	}

	if(ListaVar == NULL)
	/*Nu exista variabila declarata*/
	{
		*ok = 0;
		fprintf(output, "Variable %s undeclared\n", info);
		return -1;
	}
	
	return -1;
}

int solve(TArb t, FILE *output, TLista ListaVar, int *ok)
{
	if(*ok != 1)	{return -100000;}
	int A = 0;
	int B = 0;

	int operand = WhatIs(((char*)(t->info)));
	if(isOperand(operand) == 1)
	/*Verifica daca informatia din nod e operator*/
	{
		if(operand == 6)
		/*Operatorul este sqrt, deci se va calcula doar subarborele stang*/
		{
			A = solve(t->st, output, ListaVar, ok);
		}
		else
		{
			A = solve(t->st, output, ListaVar, ok);
			B = solve(t->dr, output, ListaVar, ok);
		}
	}
	else
	{
		A = giveValue(t->info, ListaVar, output, ok);
		return A;
	}

	return calculeaza(A, B, operand, ok);
}

void rezolva(TArb t, FILE *output, TLista ListaVar)
{
	if(t == NULL)
	{
		fprintf(output, "Invalid expression - Arbore null\n");
		printf("Invalid expression - Arbore null\n");
		return;
	}

	int rez = 0;
	int ok = 1;
	rez = solve(t, output, ListaVar, &ok);
	switch(ok)
	{
		case 1:
			fprintf(output, "%d\n", rez);
			break;

		case 0:
			break;

		case -1:
			fprintf(output, "Invalid expression\n");
			break;
		default:
			printf("Eroare in alta parte (nu s-a alocat aux in giveValue)\n");
			break;
	}

}
