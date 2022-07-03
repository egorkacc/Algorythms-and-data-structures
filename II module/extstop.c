#include <stdio.h>
#include <stdlib.h>

#define MATRIX_MALLOC(arr, M, N, type) { \
    int i; \
    int col_size = (M)*sizeof(type *); \
    int str_size = (N)*sizeof(type); \
    char *place = (char *)malloc(sizeof(char)*(col_size + (M)*str_size)); \
    arr = (type **)place; \
    char *strings = place + col_size; \
    for(i = 0; i < (M); i++){ \
        arr[i] = (type *)(strings + i*str_size); \
    }\
  }
  
#define MATRIX_FREE(arr) free((char *)arr); 

#define newline {putchar('\n');}

#define LENGTH 100
#define SIZE 26  

#define LEN(l) for((l) = 0; S[l]; ++(l));
#define KEY(c, str) (str[c]-'a')

char *T;
char *S;

int **delta1;

int lenS;
int lenT;

void delta1_func();
int bmall();

int main(int argc, char **argv)
{
    char *place1;
    
    if (argc == 3) 
	{
        S = argv[1];
        T = argv[2];
    }
	else 
	{
        place1 = (char *)malloc(sizeof(char)*LENGTH*2);
        
        S = place1;
        T = place1 + LENGTH;
        
        scanf("%s%s", S, T);
    }
    
    LEN(lenS);
    LEN(lenT);
    
    lenT = 0;
    while(T[lenT])
    	++lenT;
    	
    MATRIX_MALLOC(delta1, lenS, SIZE, int);
    
    printf("%i\n", bmall());
    
    if (argc != 3)
        free(place1);
    
    MATRIX_FREE(delta1);
    
    return 0;
}

void delta1_func()
{
    int a, i;
    for(i = 0; i < lenS; i++)
        for(a = 0; a < SIZE; a++)
            delta1[i][a] = lenS;
            
    for(i = 0; i < lenS; i++)
        for(a = 0; a <= i; a++)
          delta1[i][KEY(a, S)] = lenS - 1 - a;

}

int bmall()
{
    delta1_func();
    
    int k, i;
    for(k = lenS - 1 ; k < lenT; k += delta1[i][KEY(k, T)]) 
        for(i = lenS - 1; T[k] == S[i]; i--, k--)
            if(!i)
                return k;
    
    return lenT;
}
