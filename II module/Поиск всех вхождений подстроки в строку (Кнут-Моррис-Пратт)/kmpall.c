#include <stdio.h>
#include <malloc.h>

#define MAX_LEN 1000

#define DEBUG
#ifdef DEBUG
#define out printf
#define show_arr(arr, len) {int i; for(i = 0; i < len; ++i) {printf("%d ", arr[i]);} putchar('\n');}
#else
#define out
#endif

void  pref_func();
void kmpall();

char *str;
char *substr;

int len_substr;
int *pref;

int main(int argc, char **argv)
{
    if (argc == 3)
	{
        str = argv[1];
        substr = argv[2];
    } 
	else 
	{
        str = (char *)malloc(sizeof(char)*MAX_LEN);
        substr = (char *)malloc(sizeof(char)*MAX_LEN);
        
        scanf("%s%s", str, substr);
    }
    
    len_substr = 0;
    while(substr[len_substr])
    	++len_substr;
    	
    pref = (int *)malloc(sizeof(int)*len_substr);
    
    pref_func();
    kmpall();
    
    if(argc != 3) 
	{
        free(str);
        free(substr);
    }
    free(pref);
    
    return 0;
}

void pref_func()
{
    int i, t;
    
    pref[0] = t = 0;
    
    for(i = 1; substr[i]; i++)
	{
        while(t && (substr[t] != substr[i]))
            t = pref[t - 1];
            
        if(substr[t] == substr[i])
            ++t;
            
        pref[i] = t;
    }
    
    show_arr(pref, len_substr);
}

void kmpall()
{
    int k;    
    int q = 0;
    
    for(k = 0; str[k]; k++)
	{
        while((q > 0) && (substr[q] != str[k]))
            q = pref[q - 1];
            
        if(substr[q] == str[k])
            ++q;
            
        if(q == len_substr)
            printf("%i\n", k - len_substr + 1);
    }
}
