/*
 ============================================================================
 Name        : Arvore.c
 Author      : IHMHR
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct arvore tree;

struct arvore
{
	tree *esq;
	char dado;
	tree *dir;
};

tree* criaVazia()
{
	return NULL;
}

tree* criaNo(char letra, tree *esquerda, tree *direita)
{
	tree *aux = (tree *) malloc(sizeof(tree));
	aux->dado = letra;
	aux->esq = esquerda;
	aux->dir = direita;
	return aux;
}

void imprimirArvore(tree *arv)
{
	printf("(%c", arv->dado);

	if(arv->esq != NULL)
	{
		// go deep on left size
		imprimirArvore(arv->esq);
	}
	else
	{
		printf("(_)");
	}

	if(arv->dir != NULL)
	{
		// go deep on right size
		imprimirArvore(arv->dir);
	}
	else
	{
		printf("(_)");
	}
	printf(")");
}

tree* insereArv(tree *arv, char letra)
{
}

int pertence(tree *arv, char letra)
{
}

tree* busca(tree *arv, char letra)
{
}

tree* removeArv(tree *arv, char letra)
{
}

int main()
{
	tree *arvore = criaVazia();

	arvore = criaNo('M', criaNo('H', criaNo('E', criaNo('C', criaNo('A', criaVazia(), criaVazia()),criaNo('D', criaVazia(), criaVazia())), criaNo('G', criaVazia(), criaVazia())), criaNo('K', criaVazia(), criaNo('L', criaVazia(), criaVazia()))), criaNo('R', criaNo('O', criaNo('N', criaVazia(), criaVazia()), criaVazia()), criaNo('T', criaVazia(), criaVazia())));

	/*printf("	%c", arvore->dado);
	printf("\n");
	printf("%c", arvore->esq->dado);
	printf("		%c", arvore->dir->dado);
	printf("\n\n\n");*/

	imprimirArvore(arvore);

	printf("\n(M(H(E(C(A(_)(_))(D(_)(_)))(G(_)(_)))(K(_)(L(_)(_))))(R(O(N(_)(_))(_))(T(_)(_))))");

	return 0;
}

/*
						  ARVORE BINÁRIA
								M
					H						R
				E		L				O		T
			C		G				N
		A		D
*/
