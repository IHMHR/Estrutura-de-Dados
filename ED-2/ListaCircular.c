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

Tlista* inserir(Tlista *anterior, char letra)
{
	Tlista *aux = (Tlista*) malloc(sizeof(Tlista));
	Tlista *aux2;
	if(NULL == anterior)
	{
		aux->dado = letra;
		aux->prox = aux;
		return aux;
	}
	else
	{
		//dado
		//ligação
		do
		{ // para no ultimo da lista
			aux2 = anterior;
			/*aux->dado = letra;
			aux->prox = aux2;
			aux2->prox = aux;*/
		} while(aux2->prox != anterior);
		//ultimo no primeiro
		return aux;
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
		Tlista *aux = lst->prox;
		while(aux != lst)
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

	imprime(listaCompleta);

	return 0;
}
