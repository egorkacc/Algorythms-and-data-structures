#include <stdio.h>

int maxarray(void *base, size_t nel, size_t width,
	int (*compare)(void *a, void *b))
{
	int ref;
	int i, local_max = 0;
	char *n, *_n;
	
    for(i = 1; i < (nel - 1); i++) 
	{
		n = (char *)base + local_max*width;
		_n = (char *)base + i*width;
        ref = compare(n, _n); 
        if (ref <= -1) 
            local_max = i;
    }
    return local_max;
}

int compare(void *a, void *b);
/*
int main(int argc, char **argv)
{
	int n = 10;
	int *a = (int *)malloc(sizeof(int)*n);
	
	int i;
	for(i = 0; i < n; i++)
		a[i] = i + 1;
	for(i = 8; i < n; i++)
		a[i] = 0;
		
	printf("%i (%i)\n", maxarray(a, n, sizeof(int), compare), a[maxarray(a, 10, sizeof(int), compare)]);
	
	return 0;
}
*/
int compare(void *a, void *b)
{
	return (*(int *)a - *(int *)b);
}
