#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("Usage: frame <height> <width> <text>");
		return 0;
	}
	
	int i, j;
	int a = atoi(argv[1]), b = atoi(argv[2]);
	char *str = argv[3];
    
    int s_len = strlen(str);
    int tab = (b - s_len)/2;
    
    if(((a - 2) <= 0) || ((b - 2) < s_len))
    {
    	printf("Error");
        return 0;
	}
	
	int _b = b;
    while(_b)
    {
    	printf("*");
    	--_b;
	}
	_b = b;
	printf("\n");
	
	int n;
	if(a%2)
		n = 1;
	else
		n = 2;
    
    for(i = n; i < a/2; i++)
    	for(j = 0; j < b; j++)
    	{
    		if(j && (j != (b - 1)))
    			printf(" ");
    		else
    		{
    			printf("*");
    			if(j == (b - 1))
    				printf("\n");
			}
		}
    
    for(i = 0; i < tab; i++)
    {
    	if(i)
    		printf(" ");
    	else
    		printf("*");
	}
	printf("%s", str);
	
	for(i = (s_len + tab); i < b; i++)
	{
		if(i != (b - 1))
			printf(" ");
		else
			printf("*");
	}
    printf("\n");
    
    if(a%2)
    	--a;
    for(i = (a/2 + 1); i < a; i++)
    	for(j = 0; j < b; j++)
    	{
    		if(!j || (j == (b - 1)))
    		{
    			printf("*");
    			if(j == (b - 1))
    				printf("\n");
			}
			else
				printf(" ");
		}
    
    while(_b)
    {
    	printf("*");
    	--_b;
	}
	printf("\n");
    
	return 0;
}
