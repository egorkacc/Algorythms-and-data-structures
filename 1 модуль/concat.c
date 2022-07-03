#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_LEN 100

char *concat(char **s, int n);

int main(int argc, char **argv)
{
    int n;
    scanf("%i", &n);
    
    char **string = (char **)calloc(n, sizeof(char *));
    
    int i;
    for (i = 0; i < n; i++)
	{
        *(string + i) = (char *)calloc(MAX_LEN, 1);
        
        scanf("%s", *(string + i));
    }
  
	char* str;  
    puts(str = concat(string, n));
    
    for (i = 0; i < n; i++) 
		free(*(string + i));
    free(string);
    free(str);
    
    return 0;
}

char *concat(char **s, int n)
{
    int i, sumlength = 0;
    for(i = 0; i < n; i++)
        sumlength += strlen(*(s + i));
        
    char* str = (char*)calloc(sumlength + 1, 1);
    
    for(i = 0; i < n; i++)
        strcat(str, *(s + i));
        
    return str;
}
