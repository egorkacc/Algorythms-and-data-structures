#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned int i, j;
	long N, k;
	long sum = 0, _sum = 0;
	
    scanf("%li\n", &N);
    int a[N];
    
    for(i = 0; i < N; i++)
        scanf("%i\n", &a[i]);
        
    scanf("%li", &k);
    
    for(i = 0; i < k; i++) 
        sum += a[i];
        
    _sum = sum; 
    if(k == N)
        printf("%li", _sum);
    else 
	{ 
        for(i = 0, j = k; j < N; i++, j++) 
		{
            _sum -= a[i] - a[j];
        	if(_sum > sum)
                sum = _sum;
		}
		printf("%li",sum);
	}
	return 0;
}
