#include <stdio.h>
#include <stdlib.h>

typedef struct lista Tlista;

struct lista
{
	char dado;
	Tlista *prox;
};

int main(void)
{
	/*//char str[100] = "FACE";
	char *prt;
	prt = (char*)malloc(100 * sizeof(char));

	*(prt + 0) = 'F';
	*(prt + 1) = 'A';
	*(prt + 2) = 'C';
	*(prt + 3) = 'E';
	*(prt + 4) = '\0';

	printf("%s", prt);*/

	Tlista *letra1 = (Tlista*) malloc(sizeof(Tlista));
	Tlista *letra2 = (Tlista*) malloc(sizeof(Tlista));
	Tlista *letra3 = (Tlista*) malloc(sizeof(Tlista));
	Tlista *letra4 = (Tlista*) malloc(sizeof(Tlista));

	letra1->dado = 'F';
	letra2->dado = 'A';
	letra3->dado = 'C';
	letra4->dado = 'E';

	letra1->prox = letra2;
	letra2->prox = letra3;
	letra3->prox = letra4;

	/*printf("%c", letra1->dado);
	printf("%c", letra2->dado);
	printf("%c", letra3->dado);
	printf("%c", letra4->dado);*/

	printf("%c", letra1->dado);
	printf("%c", letra1->prox->dado);
	printf("%c", letra1->prox->prox->dado);
	printf("%c", letra1->prox->prox->prox->dado);

	return 0;
}
