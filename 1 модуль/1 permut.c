#include <stdio.h>

int main(int argc, char **argv)
{
	int i, j;
	int s1 = 0, s2 = 0;
	unsigned int k = 0;
    int a[8], b[8];

    for(i = 0; i < 8; i++)
        scanf("%i", &a[i]);
        
    for(i = 0; i < 8; i++)
        scanf("%i", &b[i]);
    
    for(i = 0; i < 8; i++)
        s1 += a[i];
        
    for(i = 0; i < 8; i++)
        s2 += b[i];
        
    if (s1 == s2)
	{
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
			{
                if(a[i] == b[j])
                k++;
        	}
        if (k > 7) 
			printf("yes");
    }
    else 
		printf("no");
	
	return 0;
}
