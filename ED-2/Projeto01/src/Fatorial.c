#include <stdio.h>

int fat(int n)
{
	if(0 == n || 1 == n)
	{
		return 1;
	}
	else
	{
		return n * fat(n - 1);
	}
}

int main1(void)
{
	int n = 0;
	printf("informe o valor para ser fatorado: ");
	fflush(stdout);
	scanf("%d", &n);

	printf("%d.", fat(n));
	return 0;
}
