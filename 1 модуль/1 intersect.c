#include <stdio.h>

int main(int argc, char **argv)
{
	char A, B, p, i;
	unsigned int x = 0, y = 0, z;
	
	scanf ("%i\n", &A);
	int f = 0, n;
	
	for(i = 0; i < A; i++) 
	{
	    scanf("%i", &n);
		f |= (1 << n);
	    y = f | y;
    }
    
    scanf ("%i\n", &B);
    int ff = 0, nn;
	
	for(i = 0; i < B; i++) 
	{
	    scanf("%i", &nn);
		ff |= (1 << nn);
		x = ff | x;
   	}
   	
   	p = 0;
   	z = x&y;
    
	for(i = z; i; i--) 
	{
	    if(z&1) 
			printf ("%i ", p);
        p += 1;
        z = z >> 1;
	}	
		
	return 0;
}
