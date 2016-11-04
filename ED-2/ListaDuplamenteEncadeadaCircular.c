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

int isListaVazia(Tlista *lst)
{
	if(lst == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Tlista* inserirElemento(Tlista *lst, char letra)
{
	Tlista *aux = (Tlista*) malloc(sizeof(Tlista));
	aux->dado = letra;

	if(isListaVazia(lst))
	{
		aux->prox = aux;
		aux->ant = aux;
	}
	else
	{
		aux->prox = lst;
		lst->ant->prox = aux;
		aux->ant = lst->ant;
		lst->ant = aux;
	}

	return aux;
}

void imprimirLista(Tlista *lst)
{
	if (isListaVazia(lst))
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

Tlista* buscarElemento(Tlista *lst, char letra)
{
	if(isListaVazia(lst))
	{
		return NULL;
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
	return lst;
}

Tlista* liberarLista(Tlista *lst)
{
	if(isListaVazia(lst))
	{
		printf("Lista vazia !");
	}
	else if(lst->prox == lst && lst->ant == lst)
	{
		lst->ant = NULL;
		lst->prox = NULL;
		free(lst);
		lst = NULL;
	}
	else
	{
		while(!isListaVazia(lst))
		{
			if(lst != lst->prox)
			{
				Tlista *aux = lst;
				lst = lst->prox;
				aux->prox = aux->prox->prox;
				aux->ant = aux->ant->ant;
				aux->ant->prox = aux->prox;
				aux->prox->ant = aux->ant;
				free(aux);
				aux = lst;
			}
			else
			{
				lst->ant = NULL;
				lst->prox = NULL;
				free(lst);
				lst = NULL;
			}
		}
	}

	return lst;
}

Tlista* removerElemento(Tlista *lst, char letra)
{
	if(isListaVazia(lst))
	{
		printf("Lista vazia !");
	}
	else if(lst->prox == lst && lst->ant == lst && lst->dado == letra)
	{
		lst->ant = NULL;
		lst->prox = NULL;
		free(lst);
		lst = NULL;
	}
	else if(((lst->prox != lst || lst->ant != lst) && lst->dado == letra))
	{
		Tlista *aux = lst;
		lst = lst->prox;
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		free(aux);
		aux = NULL;
	}
	else
	{
		Tlista *aux = buscarElemento(lst, letra);
		if(!isListaVazia(aux))
		{
			aux->ant->prox = aux->prox;
			aux->prox->ant = aux->ant;
			free(aux);
			aux = NULL;
		}
	}

	return lst;
}

int main(void)
{
	Tlista *listaCompleta = NULL;
	listaCompleta = inserirElemento(listaCompleta, 'F');
	/*listaCompleta = inserirElemento(listaCompleta, 'A');
	listaCompleta = inserirElemento(listaCompleta, 'C');
	listaCompleta = inserirElemento(listaCompleta, 'E');*/

	imprimirLista(listaCompleta);

	/*printf("\n %c \n\n", listaCompleta->prox->prox->prox->prox->ant->ant->ant->ant->dado);

	Tlista *listaPesq = buscarElemento(listaCompleta, 'A');

	imprimirLista(listaPesq);*/

	printf("\n");

	//listaCompleta = removerElemento(listaCompleta, 'E');

	listaCompleta = liberarLista(listaCompleta);

	imprimirLista(listaCompleta);

	return 0;
}
