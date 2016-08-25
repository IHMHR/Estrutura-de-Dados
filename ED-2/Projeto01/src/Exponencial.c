#include <stdio.h>
#include <stdlib.h>

int elevado(int n, int e)
{
	if(0 == e)
	{
		return 1;
	}
	else if(1 == e)
	{
		return n;
	}
	else
	{
		return n * elevado(n, e - 1);
	}
}

int main4(void)
{
	printf("%d", elevado(2, 10));

	return 0;
}
