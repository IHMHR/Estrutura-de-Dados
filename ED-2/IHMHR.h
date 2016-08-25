#ifndef IHMHR
#define IHMHR
#endif //END IHMHR

int fatorial(int n)
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
