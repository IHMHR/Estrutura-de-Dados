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

Tlista* buscaElemento(Tlista *lst, char letra)
{
    if(isListaVazia(lst))
    {
        return NULL;
    }
    else
    {
        while(!isListaVazia(lst))
        {
            if(lst->dado == letra)
            {
                return lst;
            }
            lst = lst->prox;
        }
        return NULL;
    }
    return lst;
}

Tlista* liberarLista(Tlista *lst)
{
    if(isListaVazia(lst))
    {
        return NULL;
    }
    else if(lst->prox == NULL && lst->ant == NULL) //somente este elemento na lista
    {
        free(lst);
        return NULL;
    }
    else
    {
        Tlista *aux = lst;

        while(!isListaVazia(aux))
        {
            if(lst->prox != NULL)
            {
                lst = lst->prox;
                lst->ant = NULL;
                free(aux);
                aux = lst;
            }
            else
            {
                free(lst);
                return NULL;
            }
        }
        return NULL;
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
