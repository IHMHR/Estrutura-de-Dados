#include <stdio.h>
#include <stdlib.h>

typedef struct lista Tlista;

struct lista
{
	char dado;
	Tlista *prox;
};

int isListaVazia(Tlista *lst)
{
	/*if(NULL == lst)
	{
		return 1;
	}
	else
	{
		return 0;
	}*/

	//return NULL == lst;

	return !lst;
}

Tlista* preencher(Tlista *anterior, char letra)
{
	Tlista *aux = (Tlista*) malloc(sizeof(Tlista));
	aux->dado = letra;
	aux->prox = anterior;

	return aux;
}

void imprime(Tlista *lista)
{
	/*printf("%c", lista->dado);
	printf("%c", lista->prox->dado);
	printf("%c", lista->prox->prox->dado);
	printf("%c", lista->prox->prox->prox->dado);*/

	//while(NULL != lista)
	while(!isListaVazia(lista))
	{
		printf("%c\n", lista->dado);
		lista = lista->prox;
	}
}

void imprimeRec(Tlista *lista)
{
	//if(NULL == lista->prox)
	//if(NULL != lista)
	if(!isListaVazia(lista))
	{
		imprimeRec(lista->prox);
		printf("%c", lista->dado);
	}
}

Tlista *buscaLetra(Tlista *lst, char letra)
{
	while(!isListaVazia(lst))
	{
		if (lst->dado == letra)
		{
			return lst;
		}
		lst = lst->prox;
	}
	return NULL;
}

int PertenceLista(Tlista *lst, char letra)
{
	while(!isListaVazia(lst))
	{
		if (lst->dado == letra)
		{
			return 1;
		}
		lst = lst->prox;
	}
	return 0;

	//return (1 <= tam) || ((palavra[0] == palavra[tam - 1]) && palidromo(&palavra[1], tam - 2));
	//return
}

int PertenceXulambs(Tlista *lst, char letra)
{
	return (NULL != lst) && ((lst->dado == letra) || PertenceXulambs(lst->prox, letra));
}

Tlista *RemoverInicio(Tlista *lst)
{
	/*Tlista *aux = lst;

	lst = aux->prox;
	free(aux);

	return lst;*/

	/*Tlista *aux = lst;

	//lst = aux->prox;
	lst = lst->prox;
	free(aux);

	return lst;*/

	if (!isListaVazia(lst))
	{
		Tlista *aux = lst;
		lst = lst->prox;
		free(aux);
	}
	return lst;
}

Tlista *LiberaLista(Tlista *lst)
{
	while(!isListaVazia(lst))
	{
		lst = RemoverInicio(lst);
	}
	return lst;
}

Tlista *Circular(Tlista *lst)
{
	Tlista *aux = lst;
	while(!isListaVazia(aux->prox))
	{
		aux = aux->prox;
	}
	aux->prox = lst;

	return lst;
}

Tlista *LiberarCaracterQualquer(Tlista *lst, char letra)
{
	/*Tlista *prox = NULL;
	Tlista *ant = NULL;
	Tlista *aux = lst;
	while(!isListaVazia(aux))
	{
		ant = aux;
		if(letra == aux->dado)
		{
			prox = aux->prox;
		}
	}
printf("|%c|", ant->dado);
printf("|%c|", prox->dado);
	free(aux);
	ant->prox = prox;
	return ant;*/

	Tlista *aux = lst;

	if (aux->dado == letra)
	{
		lst = lst->prox;
		free(aux);
	}
	else
	{
		while(NULL != aux->prox)
		{
			if(aux->prox->dado == letra)
			{
				Tlista *aux2 = aux->prox;

				aux->prox = aux->prox->prox;
				free(aux2);
			}
			else
			{
				aux = aux->prox;
			}
		}
	}

	return lst;
}

int main(void)
{
	Tlista *listaCompleta = NULL;
	listaCompleta = preencher(listaCompleta, 'F');
	listaCompleta = preencher(listaCompleta, 'A');
	listaCompleta = preencher(listaCompleta, 'C');
	listaCompleta = preencher(listaCompleta, 'E');

	/*imprime(listaCompleta);
	printf("\n");
	imprimeRec(listaCompleta);
	printf("\n");
	printf("Valor Hexadecimal da letra: %p, letra: %c", buscaLetra(listaCompleta, 'F'), buscaLetra(listaCompleta, 'F')->dado);
	printf("\n");
	printf("%p", listaCompleta->prox->prox->prox);*/
	/*printf("A na lista = %d", PertenceLista(listaCompleta, 'A'));
	printf("\n");
	printf("H na lista = %d", PertenceLista(listaCompleta, 'H'));
	printf("\n");
	imprimeRec(listaCompleta);
	printf("\n");
	listaCompleta = RemoverInicio(listaCompleta);
	printf("Impressão lista SEM INICIO: \n");
	imprimeRec(listaCompleta);
	listaCompleta = LiberaLista(listaCompleta);
	printf("\n");
	printf("Impressão lista VAZIA: \n");
	imprimeRec(listaCompleta);*/

	/*printf("H na lista = %d", PertenceXulambs(listaCompleta, 'H'));
	printf("\n");
	printf("A na lista = %d", PertenceXulambs(listaCompleta, 'A'));*/

	//printf("%c \n", Circular(listaCompleta));
	/*Tlista *listaCircular = Circular(listaCompleta);
	imprime(listaCircular);*/

	listaCompleta = LiberarCaracterQualquer(listaCompleta, 'A');
	imprime(listaCompleta);

	return 0;
}
