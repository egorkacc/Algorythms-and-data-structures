#include <stdio.h>

void revarray(void *base, size_t nel, size_t width) 
{ 
	char *n, *_n;
	char temp = *(char *)base;
	
	int i, j;
    for(i = 0; i < nel/2; i++)
        for(j = 0; j < width; j++)
		{
			n = (width*i + (char *)base + j);
			temp = *n;
			_n = (width*((nel - 1) - i) + (char *)base + j);
            *(width*i + (char *)base + j) = *_n;
            *(width*((nel - 1) - i) + (char *)base + j) = temp;
        }
}

/*
int main(int argc, char **argv)
{
	int *a;
	a = (int *)malloc(sizeof(int)*10);
	
	int i;
	for(i = 0; i < 10; i++)
		a[i] = i;
		
	revarray(a, 10, sizeof(int));
	
	for(i = 0; i < 10; i++)
		printf("%i ", a[i]);
		
	return 0;
}
*/
