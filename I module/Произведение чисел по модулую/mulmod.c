#include <stdio.h>

int main()
{
	unsigned long i;
	
    long long a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    
	long long d, e, f;
    long long d1, d2;
    
    char twos[64];
	for (i = 0; b; i++, twos[i] = 0)
	{
		twos[i] = b%2;
		b /= 2;
	}
	
	d = twos[i]*a;
	for (i; i + 1; i--, f = 0) 
	{
		f += ((d%c)*(2%c)%c);
		d2 = (a*(twos[i]%c))%c;
		e = f + d2;
        d = e;
	}
    e %= c;
    
	printf("%lld", e);
	
	return 0;
}
