#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void alg_Kad(float *v, int n)
{
    int l = 0, r = 0;
    float maxsum = v[0];
    float sum = 0;
    
    int point = 0;
    
    int _n = n;
    while(_n)
	{
        sum += v[n - _n];
        if(sum > maxsum)
		{
            maxsum = sum;
            r = n - _n;
            l = point;
        }
        
        --_n;
        
        if(sum < 0)
		{
			point = n - _n;
            sum = 0;
        }
    }
    
    printf("%i %i\n", l, r);
}

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);
    
    float *v = (float *)malloc(sizeof(float)*n);
    float *b = (float *)malloc(sizeof(float)*n);
    float *a = (float *)malloc(sizeof(float)*n);

	int i;
    for(i = 0; i < n; i++)
        scanf("%f/%f", &a[i], &b[i]);

    for(i = 0; i < n; i++)
        v[i] = log(a[i]/b[i]);
        
    alg_Kad(v, n);

	free(v);
	free(b);
    free(a);

    return 0;
}
