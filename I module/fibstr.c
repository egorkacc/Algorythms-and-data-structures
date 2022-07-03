#include <stdio.h>
#include <malloc.h>
#include <string.h>

char *fibstr(int n);
int fibonacci(int n);

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);

    char *s = fibstr(n);
    
    puts(s);
    
    free(s);
    
    return 0;
}

char *fibstr(int n)
{
    
    int length = fibonacci(n) + 1;
    
    char *s1 = (char *)calloc(length, sizeof(char));
    char *s2 = (char *)calloc(length, sizeof(char));
    char *temp;
    
    *s1 = 'a';
    *s2 = 'b';
    
    switch(n)
	{
	    case 1:
	        free(s2);
	        
	        return s1;
	    case 2:
	        free(s1);
	        
	        return s2;
    }
    
    while(n > 2) 
	{
        strcat(s1, s2); 
        temp = s2; 
        
        s2 = s1;
        s1 = temp;
        
        --n;
    }
    
    free(s1);
    
    return s2;
}

int fibonacci(int n)
{
    int f1 = 1, f2 = 1, temp;
    
    int i;
    for(i = 3; i <= n; i++)
	{
        temp = f2;
        f2 += f1;
        f1 = temp;
    }
    
    return f2;
}

