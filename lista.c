/*VLAD Andrei-Alexandru - 311CB*/

#include "tema3.h"

TLista AlocaCelula(void *info)
/*Functie care aloca celula cu informatia data ca argument*/
{
	/*Aloc spatiu pentru celula*/
	TLista temp = (TLista) calloc(1, sizeof(struct celula));
	
	/*Verific alocarea*/
	if(!temp)	{return NULL;}

	temp->info = info;
	temp->urm = NULL;

	return temp;
}

void DistrugeLG(TLista *L)
/*Functia distruge lista generica primita ca parametru
	si elibereaza zona de memorie alocata*/
{
	if(*L == NULL)	{return;}

	TLista lista = *L;
	while(lista)
	{
		//Salvez celula curenta
		TLista temp = lista;

		//Avans la urmatoarea celula pentru a nu pierde continuarea listei
		lista = lista->urm;

		//Eliberari de memorie
		free(((TAsign)(temp->info))->numeVar);
		free(temp->info);
		free(temp);
	}

	*L = NULL;
}

TAsign InitAsign(char *var, int valoare)
{
	TAsign temp = (TAsign) calloc(1, sizeof(struct asignare));
	if(!temp)	{return NULL;}

	temp->numeVar = var;
	temp->valoare = valoare;

	return temp;
}

void IntrodLG(TLista *L, void *celula)
{
	if(*L == NULL)
	{
		/*Introduce celula in lista vida*/
		*L = celula;
		return;
	}else
	{
		/*Deplasare la finalul listei*/
		while(*L)
			L = &((*L)->urm);

		*L = celula;
		return;
	}
}