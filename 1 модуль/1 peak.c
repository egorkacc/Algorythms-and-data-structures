#include <stdio.h>

unsigned long peak(unsigned long nel, 
	int (*less)(unsigned long i, unsigned long j)) 
{
    unsigned long  a = 0, b = nel - 1;

	unsigned long i = 0;
    if((b - a - 1) && (b > 1))
	    while(a < b)
		{
            i = ((a + b)/2);
            if(less(i, i + 1))
                a = i + 1;
            else if(less(i, i - 1)) 
                b = i - 1;
            else 
				return i;
        } 
    else
        return i;
        
    return a;
}
