#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int N, M;
    scanf("%i %i", &N, &M);

    long *cluster = (long *)malloc(sizeof(long )*N);
    
    int i;
    for(i = 0; i < N; i++)
        *(cluster + i) = 0;

    long t1, t2;
    for(i = 0; i < M; i++)
	{
        scanf("%li %li", &t1, &t2);
        
        int start1 = 0;
        
        for(i = 0; i < N; i++)
            if(*(cluster + i) <= t1)
			{
                start1 = 1;
                *(cluster + i) = t1 + t2;
                
                break;
            }
        
        if (!start1)
		{
            int min = 0;
            for(i = 1; i < N; i++)
                if((*(cluster + min)) > (*(cluster + i)))
                	min = i;
            
            *(cluster + min) = *(cluster + min) + t2;
        }
    }
    
    long max = 0;
    for(i = 0; i < N; i++)
	{
        if(*(cluster + i) > max)
        max = *(cluster + i);
    }
    
    printf("%li", max);
    
    free(cluster);
    
    return 0;
}
