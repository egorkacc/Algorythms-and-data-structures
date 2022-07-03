#include <stdio.h>

int main(int argc, char **argv)
{
	int n, i;
	long x0, k;
	long long res, _res = 0, res_deriv, _res_deriv = 0;
	
	scanf("%i %li", &n, &x0);
	
	while(n + 1)
	{
		scanf("%li", &k);
		res = k;
		for(i = 0; i < n; i++)
			res *= x0;
		_res += res;
		if(n)
		{
			res_deriv = k*n;
			for(i = 0; i < (n - 1); i++)
				res_deriv *= x0;
			_res_deriv += res_deriv;
		}
		n--;
	}
	
	printf("%lli\n%lli\n", _res, _res_deriv);
	
	return 0;
}
