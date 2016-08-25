#include <stdio.h>
#include <stdlib.h>

int mdc(int val, int val2)
{
	if(val % val2 == 0)
	{
		return val2;
	}
	else
	{
		return mdc(val2, (val % val2));
	}
}

int main3(void)
{
	setbuf(stdout, NULL);
	int val = 0, val2 = 0;
	printf("informe o valor para ser calculado o MDC: ");
	fflush(stdin);
	scanf("%d", &val);
	printf("informe o segundo valor para s er calculado o MDC: ");
	fflush(stdin);
	scanf("%d", &val2);

	printf("%d", mdc(val, val2));
	return 0;
}
