/*
 ============================================================================
 Name        : Projeto01.c
 Author      : IHMHR
 Version     : v0.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void contar(int n)
{
	printf("%d \n", n);
	if(n != 0)
	{
		contar(--n);
	}
}


int main0(void)
{
	contar(10);

	return EXIT_SUCCESS;
}
