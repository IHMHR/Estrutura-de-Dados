#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palidromo(char *palavra, int tam)
{
	if(1 == tam || 0 == tam)
	{
		return 1;
	}
	else if(palavra[0] == palavra[tam - 1])
	{
		return palidromo(&palavra[1], tam - 2);
	}
	else
	{
		return 0;
	}
}

int main5(void)
{
	//char nome[6] = "arara";
	//char nome[6] = "aroma";
	char nome[6] = "osso";
	printf("%s - %s", nome, palidromo(nome, strlen(nome)) == 1 ? "true" : "false");

	return 0;
}
