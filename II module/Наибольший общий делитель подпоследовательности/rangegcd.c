#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int nod(int x, int y);
int* ComputeLogarithms(int m);

int SparseTable_Query(int **ST, int l, int r, int *logar);
int **SparseTable_build(int *v, int n, int *logar);

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);
    
    int *start =(int *)malloc(sizeof(int)*(n + 2));

	int i;
    for(i = 0; i < n; i++)
        scanf("%i", &start[i]);
    
    int *logar = ComputeLogarithms(log2(n) + 2);

    int **ST = SparseTable_build(start, n, logar);

    int m, l, r;
    scanf("%i", &m);
    
    while(i < m)
	{
        scanf("%i %i", &l, &r);
        printf("%i\n", SparseTable_Query(ST, l, r, logar));
        
        ++i;
    }
    
    for(int i = 0; i < n; i++)
        free(ST[i]);
    free(ST);
    free(start);
    free(logar);
    
    return 0;
}

int nod(int x, int y)
{
    int a = abs(x), b = abs(y);
    while(a && b) 
	{
        if(a >= b)
            a -= b;
        else
            b -= a;
    }
    
    return a | b;
}

int* ComputeLogarithms(int m)
{
    int k = (1 << (m + 1));
    int *logar = (int *)malloc(sizeof(int)*k);
    int i = 1;
    int j = 0;
    
    while(i <= m)
	{
        k = (1 << i);
        while(j < k)
		{
            logar[j]= i - 1;
            
            ++j;
        }
        
        ++i;
    }
    
    return logar;
}

int SparseTable_Query(int **ST, int l, int r, int *logar)
{
    int j = logar[r - l + 1];
    int k = (1 << j);
    
    return nod(ST[l][j], ST[r - k + 1][j]);
}

int **SparseTable_build(int *v, int n, int *logar)
{
    int m = logar[n] + 1;
    int **ST = (int **)malloc(sizeof(int *)*n);
    
    int i;
    for(i = 0; i < n; i++)
        ST[i] =(int *)malloc(sizeof(int)*(m + 1));
    
    for(i = 0; i < n; i++)
        ST[i][0] = v[i];
        
    int j;
    for(j = 1; j < m; j++)
	{
        int k = (1 << j);
        for(i = 0; i <= (n - k); i++)
		{
            int kl = (1 << (j - 1));
            ST[i][j] = nod(ST[i][j - 1], ST[i + kl][j - 1]);
        }
    }
    
    return ST;
}
