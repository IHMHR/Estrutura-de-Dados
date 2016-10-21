/*
 ============================================================================
 Name        : ListaDuplamenteEncadeada.c
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
	Tlista *ant;
};


Tlista* inserir(Tlista *anterior, char letra)
{
	Tlista *aux = (Tlista*) malloc(sizeof(Tlista));

	if(anterior == NULL)
	{
		aux->dado = letra;
		aux->ant = NULL;
		aux->prox = anterior;
	}
	else
	{
		aux->dado = letra;
		aux->prox = anterior;
		anterior->ant = aux;
		aux->ant = NULL;
	}

	return aux;
}

void imprime(Tlista *lst)
{
	if(NULL == lst)
	{
		printf("Lista vazia !");
	}
	else
	{
		while(lst != NULL)
		{
			printf("%c\n", lst->dado);
			lst = lst->prox;
		}
	}
}

int main(void)
{
	Tlista *listaCompleta = NULL;
	listaCompleta = inserir(listaCompleta, 'F');
	listaCompleta = inserir(listaCompleta, 'A');
	listaCompleta = inserir(listaCompleta, 'C');
	listaCompleta = inserir(listaCompleta, 'E');

	//printf("%c \n\n", listaCompleta->ant->ant->ant->prox->prox->prox->dado);
	printf("%c \n\n", listaCompleta->prox->prox->prox->ant->ant->ant->dado);

	imprime(listaCompleta);

	return 0;
}
