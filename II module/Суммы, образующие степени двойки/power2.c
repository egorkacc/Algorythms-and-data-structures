#include <stdio.h>

int pw2(int a);
int pw2cou(int *a, int n);
int pw2cou_rec(int *a, int n, int sum, int q);

int main()
{
	int n, i;
    scanf("%i", &n);
    
    int x[n];
    for(i = 0; i < n; i++) 
		scanf("%i", &x[i]);
		
    printf("%i", pw2cou(x, n));
    
    return 0;
}

int pw2(int a)
{
	if(a)
		return !(a&(a - 1));
	else
		return 0;
}

int pw2cou(int *a, int n)
{
	int cou = 0, _n = n;
    
    while(_n)
    {
        cou += pw2cou_rec(a, n, 0, n-_n);
        --_n;
    }
    
    return cou;
}

int pw2cou_rec(int *a, int n, int sum, int q)
{
    sum += a[q];
    int cou = pw2(sum), j = q + 1;
    
    while(j < n)
    {
        cou += pw2cou_rec(a, n, sum, j);
        ++j;
    }
    
    return cou;
}
