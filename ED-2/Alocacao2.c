/*
 ============================================================================
 Name        : ProjetoCompleto.c
 Author      : IHMHR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "lista.h"

typedef struct pilha Tpilha;
typedef struct fila Tfila;

struct pilha
{
	Tlista *topo;
};

struct fila
{
	Tlista *inicio;
	Tlista *final;
};

Tpilha* inicializarPilha()
{
	Tpilha *aux = (Tpilha*) malloc(sizeof(Tpilha));
	aux->topo = NULL;
	return aux;
}

void pushPilha(Tpilha *pilha, char letra)
{
	pilha->topo = inserir(pilha->topo, letra);
}

void imprimirPilha(Tpilha *pilha)
{
	imprime(pilha->topo);
}

void popPilha(Tpilha *pilha)
{
	pilha->topo = removeLista(pilha->topo, pilha->topo->dado);
}

void liberaPilha(Tpilha *pilha)
{
	pilha->topo = liberaCircular(pilha->topo);
}

int isPilhaVazia(Tpilha *pilha)
{
	return isListavazia(pilha->topo);
}

Tpilha* buscaPilha(Tpilha *pilha, char letra)
{
	return (Tlista *) BuscaCircular(pilha->topo, letra);
}

Tfila* inicializarFila()
{
	Tfila *aux = (Tfila *) malloc(sizeof(Tfila));
	aux->inicio = aux->final = NULL;
	return aux;
}

int isFilaVazia(Tfila *fila)
{
	return isListavazia(fila->inicio);
}

void inserirFila(Tfila *fila, char letra)
{
	if(isFilaVazia(fila))
	{
		// inicio e final recebem a mesma Lista
		fila->inicio = fila->final = inserir(NULL, letra);
	}
	else
	{
		Tlista *aux = inserir(fila->inicio, letra);
		fila->final->prox = aux;
		fila->final = aux;
	}
}

void imprimirFila(Tfila *fila)
{
	imprime(fila->inicio);
}

void removeFila(Tfila *fila)
{
	// remover no inicio
	if(isFilaVazia(fila))
	{
		fila = inicializarFila();
	}
	else
	{
		/*Tlista *aux = fila->inicio;
		fila->inicio = fila->inicio->prox;
		free(aux);*/

		fila->inicio = removeLista(fila->inicio, fila->inicio->dado);

		if(fila->inicio == NULL)
		{
			fila->final = fila->inicio;
		}
	}
}

void liberarFila(Tfila *fila)
{
	fila->inicio = fila->final = libera(fila->inicio);
}

int main()
{
	/*Tpilha *pilhaUsuario = inicializarPilha();

	pushPilha(pilhaUsuario, 'F');
	pushPilha(pilhaUsuario, 'A');
	pushPilha(pilhaUsuario, 'C');
	pushPilha(pilhaUsuario, 'E');

	imprimirPilha(pilhaUsuario);

	popPilha(pilhaUsuario);
	printf("\n");

	imprimirPilha(pilhaUsuario);

	liberaPilha(pilhaUsuario);
	printf("\n");

	imprimirPilha(pilhaUsuario);*/

	Tfila *filaUsuario = inicializarFila();

	inserirFila(filaUsuario, 'F');
	inserirFila(filaUsuario, 'A');
	inserirFila(filaUsuario, 'C');
	inserirFila(filaUsuario, 'E');

	imprimirFila(filaUsuario);

	removeFila(filaUsuario);

	printf("\n----------------------------\n");

	imprimirFila(filaUsuario);

	liberarFila(filaUsuario);

	printf("\n----------------------------\n");

	imprimirFila(filaUsuario);

	return 0;
}
