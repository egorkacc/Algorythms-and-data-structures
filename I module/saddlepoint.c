#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int c, d; 
	int *a, *b;
	int sadge = 0, min, i, j;
	
    scanf("%i", &c);
    scanf("%i", &d);

	a = (int *)malloc(sizeof(int)*c);
	b = (int *)malloc(sizeof(int)*d);

	int M[c][d];
    for(i = 0; i < c; i++)
        for(j = 0; j < d; j++)
            scanf("%i", &M[i][j]);
            
    for(i = 0; i < c; i++)
        for(j = 0; j < d; j++)
		{
            min = M[i][j];
            if(j == 0)
                a[i] = min;
            if(i == 0)
                b[j] = min;
            if(min > a[i])
                a[i] = min;
			if(min < b[j])
                b[j] = min;             
        }

    for(i = 0; i < c; i++)
        for(j = 0; j < d; j++)
            if(a[i] == b[j])
            {
                printf("%i %i\n", i, j); 
				sadge++;
			}
    
    if(!sadge) 
		printf("none");

    free(a);
    free(b);
    
	return 0;
}
