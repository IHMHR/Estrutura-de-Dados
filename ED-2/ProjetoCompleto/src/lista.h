/*
 * lista.h
 *
 *  Created on: 10 de nov de 2016
 *      Author: Igor Martinelli Ramos
 */

#ifndef LISTA_H_
#define LISTA_H_

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
	Tlista *aux = lst;
	Tlista *aux2 = lst->prox;

	if (aux->prox == aux)
	{
		free(aux);
		return NULL;
	}
	else
	{
		do
		{
			aux = aux2->prox;
			free(aux2);
			lst->prox = aux;

			aux2 = aux;
		} while (aux != lst);

		free(aux);
	}

	return NULL;
}

Tlista* removeLista(Tlista *lst, char letra)
{
	if(isListavazia(lst))
	{
		return lst;
	}
	else if(lst == lst->prox && letra == lst->dado)
	{
		free(lst);
		lst = NULL;
		return lst;
	}
	else if(lst->dado == letra)
	{
		Tlista *aux = lst;
		Tlista *aux2 = lst;

		do
		{
			aux2 = aux2->prox;
		} while(aux2->prox != lst);

		lst = lst->prox;
		aux2->prox = lst;

		free(aux);
		return lst;
	}
	else
	{
		Tlista *aux = lst;
		Tlista *aux2;

		do
		{
			if (aux->prox->dado == letra)
			{
				aux2 = aux->prox;
				aux->prox = aux->prox->prox;
				free(aux2);
			}
			else
			{
				aux = aux->prox;
			}
		} while (aux->prox != lst);

		return lst;
	}

	return lst;
}

#endif /* LISTA_H_ */
