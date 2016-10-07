/*
 ============================================================================
 Name        : ListaCircular.c
 Author      : IHMHR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct lista Tlista;

struct lista
{
	char dado;
	Tlista *prox;
};

int isListavazia(Tlista *lst)
{
	if(NULL == lst)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Tlista* inserir(Tlista *anterior, char letra)
{
	Tlista *aux = (Tlista*) malloc(sizeof(Tlista));
	if(NULL == anterior)
	{
		aux->dado = letra;
		aux->prox = aux;
		return aux;
	}
	else
	{

		Tlista *auxN = anterior;
		aux->dado = letra;
		aux->prox = aux;
		aux->prox = anterior;

		do {
			auxN = auxN->prox;
		} while (auxN->prox != anterior);

		auxN->prox = aux;

		return aux;


		/*//dado
		//ligação
		do
		{ // para no ultimo da lista
			aux2 = anterior;
			/*aux->dado = letra;
			aux->prox = aux2;
			aux2->prox = aux;*/
		/*} while(aux2->prox != anterior);
		//ultimo no primeiro
		aux2->prox = anterior;
		return anterior;*/
	}
}

void imprime(Tlista *lst)
{
	if(NULL == lst)
	{
		printf("Lista vazia !");
	}
	else
	{
		Tlista *aux = lst;
		do
		{
			printf("%c\n", lst->dado);
			lst = lst->prox;
		} while (aux != lst);
	}
}

Tlista* BuscaCircular(Tlista* lst, char letra)
{
	if(isListavazia(lst))
	{
		return NULL; //return lst;
	}
	else
	{
		Tlista *aux = lst;
		do
		{
			if(lst->dado == letra)
			{
				return lst;
			}
			lst = lst->prox;
		} while (aux != lst);
		return NULL;
	}
}

Tlista* liberaCircular(Tlista *lst)
{
	while(!isListavazia(lst))
	{
		Tlista *aux = lst;
		Tlista *aux2 = lst;
		lst = lst->prox;

		do
		{
			aux2 = aux2->prox;
		} while (aux != aux2->prox);

		free(aux);
		aux2->prox = lst;
	}

	return lst;
}

int main(void)
{
	Tlista *listaCompleta = NULL;
	listaCompleta = inserir(listaCompleta, 'F');
	listaCompleta = inserir(listaCompleta, 'A');
	listaCompleta = inserir(listaCompleta, 'C');
	listaCompleta = inserir(listaCompleta, 'E');

	imprime(listaCompleta);

	printf("\n");

	printf("%p", BuscaCircular(listaCompleta, 'A'));

	printf("\n\n");

	listaCompleta = liberaCircular(listaCompleta);
	printf("%s", isListavazia(listaCompleta) ? "Lista Vazia" : "Lista CHEIA");

	return 0;
}
