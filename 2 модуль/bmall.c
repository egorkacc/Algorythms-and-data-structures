#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100
#define SIZE 26  

#define LEN(l, str) for((l) = 0; str[l]; ++(l))
#define KEY(c, str) (str[c]-'a')
#define MAX(a, b) ((a) > (b) ? (a) : (b))

char *T;
char *S;
         
int *sigma;       
int delta1[SIZE]; 
int *delta2;

int lenT;
int lenS;

void sigma_func();
void delta1_func();
void delta2_func();
void bmall();

int main(int argc, char **argv)
{
    if(argc == 3)
	{
        S = argv[1];
        T = argv[2];
    } 
	else 
	{
        T = (char *)malloc(LENGTH);
        S = (char *)malloc(LENGTH);
        
        scanf("%s%s", S, T);
    }
    
    LEN(lenT, T);
    LEN(lenS, S);
    
    sigma = (int *)malloc(sizeof(int)*lenS);
    delta2 = (int *)malloc(sizeof(int)*lenS);
    bmall();
    
    free(sigma);
    free(delta2);
    if(argc != 3)
	{
        free(T);
        free(S);
    }
    
    return 0;
}

void sigma_func()
{
	int t;
    sigma[lenS - 1] = t = lenS - 1;
    
    int i;
    for(i = lenS - 2; i + 1; i--)
	{
        while((t < lenS - 1) && (S[t] != S[i]))
            t = sigma[t + 1];
            
        if(S[t] == S[i])
            --t;
            
        sigma[i] = t;
    }
}

void delta1_func()
{
    int a;
    for(a = 0; a < SIZE; a++)
        delta1[a] = lenS;
        
    for(a = 0; a < lenS; a++)
        delta1[KEY(a, S)] = lenS - 1 - a;
}

void delta2_func()
{
    sigma_func();
    
    int i, t = sigma[0];
    for (i = 0; i < lenS; i++) 
	{
        while(t < i)
            t = sigma[t + 1];
            
        delta2[i] = lenS - i + t;
    }
    
    for(i = 0; i < lenS; i++)
	{
        t = i;
        while(t < (lenS - 1)) 
		{
            t = sigma[t + 1];
            
            if(S[i] != S[t])
                delta2[t] = lenS - 1 - i;
        }
    }
}

void bmall()
{
    delta1_func();
    delta2_func();
    
    int k, i;
    for(k = lenS - 1 ; k < lenT; k += MAX(delta1[KEY(k, T)], delta2[i])) 
        for(i = lenS - 1; T[k] == S[i]; i--, k--)
            if(!i) 
			{
                printf("%i ", k);
                
                break;
            }
}
