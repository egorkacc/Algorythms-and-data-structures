#include <stdio.h>
#include <malloc.h>

#define SIZE 100

void pref_func();
void find_prefixes();

char *str;
int *pref;

int main(int argc, char **argv)
{
    if(argc > 1)
        str = argv[1];
    else 
	{
        str = (char *)malloc(sizeof(char)*SIZE);
        
        scanf("%s", str);
    }
    
    int len = 0;
    while(str[len])
    	++len;
    
    pref = (int *)malloc(sizeof(int)*len);
    
    pref_func();
    find_prefixes();
    
    free(pref);
    
    return 0;
}
void pref_func()
{
    int t;
    pref[0] = t = 0;
    
    int i;
    for(i = 1; str[i]; i++)
	{
        while(t && (str[t] != str[i]))
            t = pref[t - 1];
            
        if(str[t] == str[i])
            ++t;
            
        pref[i] = t;
    }
}

void find_prefixes()
{
    int len;
    for(len = 2; str[len - 1]; len++)
	{
        int substr_len = len - pref[len - 1];
		  
        if(substr_len && pref[len - 1] && !(len%substr_len))
            printf("%i %i\n", len, len/substr_len);
    }
}
