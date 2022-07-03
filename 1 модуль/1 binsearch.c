#include <stdio.h>

unsigned long binsearch(unsigned long nel,
	int (*compare)(unsigned long i))
{
    unsigned long a = 0, b = nel - 1, i;

    while(a <= b) 
	{
        i = (a + b)/2;
        
        if(!compare(i))
            return i;
        else if(compare(i) == -1)
            a = i + 1;
        else if(compare(i) == 1)
            b = i - 1;
    }
    return nel;
}

/*
int compare(unsigned long i);

const int k = 51;
int a[8] = {1, 2, 30, 45, 50, 51, 55, 60};

int main(int argc, char **argv)
{
	printf("%lu\n", binsearch(8, compare));
		
	return 0;
}

int compare(unsigned long i)
{
	if(a[i] == k) 
		return 0; 
    else if(a[i] < k) 
		return -1;
	else 
    	return 1;
}
*/
