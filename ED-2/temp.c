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
	//Pre Ordem
	if(NULL != arv)
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
}

void imprimirArvorePos(tree *arv)
{
	//Pos Ordem
	if(NULL != arv)
	{
		printf("(");
		if(arv->esq != NULL)
		{
			// go deep on left size
			imprimirArvorePos(arv->esq);
		}
		else
		{
			printf("(_)");
		}

		if(arv->dir != NULL)
		{
			// go deep on right size
			imprimirArvorePos(arv->dir);
		}
		else
		{
			printf("(_)");
		}
		printf("%c)", arv->dado);
	}
}

void imprimirArvoreOrdem(tree *arv)
{
	//Ordem
	if(NULL != arv)
	{
		printf("(");
		if(arv->esq != NULL)
		{
			// go deep on left size
			imprimirArvoreOrdem(arv->esq);
		}
		else
		{
			printf("(_)");
		}
		printf("%c)", arv->dado);
		if(arv->dir != NULL)
		{
			// go deep on right size
			imprimirArvoreOrdem(arv->dir);
		}
		else
		{
			printf("(_)");
		}
	}
}

tree* insereArv(tree *arv, char letra)
{
	if(arv == NULL)
	{
		arv = criaNo(letra, arv, arv);
	}
	else
	{
		if(letra > arv->dado)
		{
			//direita
			arv->dir = insereArv(arv->dir, letra);
		}
		else
		{
			//esquerda
			arv->esq = insereArv(arv->esq, letra);
		}
	}
	return arv;
}

int pertence(tree *arv, char letra)
{
	/* ERRO */
	if(arv->dado == letra)
	{
		return 1;
	}
	else
	{
		if(arv->esq != NULL)
		{
			pertence(arv->esq, letra);
		}

		if(arv->dir != NULL)
		{
			pertence(arv->dir, letra);
		}
	}
	return 0;
}

tree* busca(tree *arv, char letra)
{
	if(arv != NULL)
	{
		if(arv->dado == letra)
		{
			return arv;
		}
		busca(arv->esq, letra);
		busca(arv->dir, letra);
	}

	return NULL;
}

tree* removeArv(tree *arv, char letra)
{
}

int main()
{
	tree *arvore = criaVazia();

	//arvore = criaNo('M', criaNo('H', criaNo('E', criaNo('C', criaNo('A', criaVazia(), criaVazia()),criaNo('D', criaVazia(), criaVazia())), criaNo('G', criaVazia(), criaVazia())), criaNo('K', criaVazia(), criaNo('L', criaVazia(), criaVazia()))), criaNo('R', criaNo('O', criaNo('N', criaVazia(), criaVazia()), criaVazia()), criaNo('T', criaVazia(), criaVazia())));

	/* AROVRE */
	arvore = insereArv(arvore, 'M');

	arvore = insereArv(arvore, 'R');
	arvore = insereArv(arvore, 'H');

	arvore = insereArv(arvore, 'O');
	arvore = insereArv(arvore, 'K');
	arvore = insereArv(arvore, 'T');
	arvore = insereArv(arvore, 'E');

	arvore = insereArv(arvore, 'L');
	arvore = insereArv(arvore, 'G');
	arvore = insereArv(arvore, 'N');
	arvore = insereArv(arvore, 'C');

	arvore = insereArv(arvore, 'D');
	arvore = insereArv(arvore, 'A');
	/* AROVRE */

	imprimirArvore(arvore);

	printf("\n(M(H(E(C(A(_)(_))(D(_)(_)))(G(_)(_)))(K(_)(L(_)(_))))(R(O(N(_)(_))(_))(T(_)(_))))");

	printf("\nPertence H na arvore = %d", pertence(arvore, 'H'));
	printf("\nPertence X na arvore = %d", pertence(arvore, 'X'));

	return 0;
}

/*
						  ARVORE BINÁRIA
								M
					H						R
				E		K				O		T
			C		G		L		N
		A		D
*/
