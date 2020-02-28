/*VLAD Andrei-Alexandru - 311CB*/

#include "tema3.h"
#define INPUT 1
#define OUTPUT 2
#define DELIMS " \n"

int main(int argc, char const *argv[])
{
	/*Daca nu sunt date fisierul de input + output se incheie executia*/
	if(argc != 3)
		return -1;

	/*Deschidere fisiere primite ca argumente*/
	FILE *input = fopen(argv[INPUT], "rt");
	FILE *output = fopen(argv[OUTPUT], "wt");

	//getline
	char *buffer = NULL;
	char *temp = NULL;
	size_t len = 64;

	/*Se citeste numarul de asignari*/
	getline(&buffer, &len, input);
	temp = strtok(buffer, DELIMS);

	int nAsign = atoi(temp);

	/*Asignarile sunt salvate intr-o lista simplu inlantuita generica*/
	TLista ListaVar = NULL;

	int i = 0;
	for(i = 0; i < nAsign; ++i)
	{
		char *nume_var = NULL;
		int valoare = 0;
		getline(&buffer, &len, input);
		temp = strtok(buffer, DELIMS);

		nume_var = (char*) calloc(strlen(temp) + 1, 1);
		memcpy(nume_var, temp, strlen(temp));

		temp = strtok(NULL, DELIMS);		
		valoare = atoi(strtok(NULL, DELIMS));

		TAsign asignare = InitAsign(nume_var, valoare);
		if(asignare == NULL)
		{
			free(nume_var);
			break;
		}

		TLista celula = AlocaCelula(asignare);
		if(!celula)
		{
			free(nume_var);
			free(asignare);
			break;
		}

		IntrodLG(&ListaVar, celula);
	}

	/*Salveaza numarul de expresii*/
	int nrExpresii = 0;
	getline(&buffer, &len, input);
	temp = strtok(buffer, DELIMS);
	nrExpresii = atoi(temp);

	/*Mai jos se prelucreaza urmatoarele M expresii*/
	for(i = 0; i < nrExpresii; ++i)
	{
		TArb arb = NULL;

		/*Se citeste o linie intreaga*/
		getline(&buffer, &len, input);
		arb = ConstrArbExpr(buffer);
		if(arb == NULL)
			printf("Arbore null\n");

		rezolva(arb, output, ListaVar);
		/*Distruge arborele pentru aceasta expresie care a fost deja evaluata*/
		DistrugeArb(&arb);
	}

	/*Eliberari de memorie*/
	DistrugeLG(&ListaVar);
	free(buffer);

	/*Inchidere fisiere*/
	fclose(input);
	fclose(output);

	return 0;
}