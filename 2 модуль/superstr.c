#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1000

#define SET_BIT(i) (1 << (i))
#define GET_BIT(arr, index) (1 & ((arr) >> (index)))

#define INIT_ARR(m) (SET_BIT(m)-1) 

#define ERASE_q_ARR(arr, q) (GET_BIT(arr, q) ? ((arr) ^ SET_BIT(q)) : arr)

#define MATRIX_MALLOC(arr, M, N, type) {\
    int i;\
    arr = (type **)malloc((M)*sizeof(type *) + (M)*(N)*sizeof(type));\
    arr[0] = (type *)(arr + M);\
    for(i = 1; i < (M); i++){\
       arr[i] = arr[i - 1] + N;\
    }\
  }
  
#define MATRIX_FREE(arr) free(arr);

#define STR1_t ((t < len1) ? str1[t] : str2[t - len1])

typedef unsigned char byte;

byte pref_func1(char *str1);
byte pref_func2(char *str2, char *str1);

void init_matrix(int n);
void permut(short arr, int nel);

short init_arr(int m);
short erase_q_arr(short arr, int q);

int *add_q_cort(int *cort, int q, int i);

char **container;

byte **matrix;
byte *pref;
byte *pi;

int shortest;

int main(int argc, char **argv)
{
    int n;
    scanf("%i ", &n);
    
    MATRIX_MALLOC(container, n, LENGTH, char);
    
    int i;
    for(i = 0; i < n; i++)
        scanf("%s", container[i]);

    MATRIX_MALLOC(matrix, n, n, byte);
    
    init_matrix(n);
    
    permut(INIT_ARR(n), n);
    
    MATRIX_FREE(container);
    MATRIX_FREE(matrix);
    
    return 0;
}

byte pref_func1(char *str1)
{  
    pi = pref + 1;
    
    byte t = 0;
    pi[0] = 0;
    
    byte i;
    for(i = 1; str1[i]; i++)
	{
        while((str1[t] != str1[i]) && t)
            t = pi[t - 1];

        if(str1[t] == str1[i])
            ++t;
    
        pi[i] = t;
    }
    
    return pref[0] = i;
}

byte pref_func2(char *str2, char *str1)
{
    byte len1 = pref[0]; 
    byte i, t = pi[len1 - 1];
    
    for(i = len1; str2[i - len1]; i++)
	{
        while(t && (STR1_t != str2[i - len1]))
            t = pi[t - 1];

        if(STR1_t == str2[i - len1])
            ++t;
    
        pi[i] = t;
    }
    
    byte len2 = i - len1;

    while(t > len2)
        t = pi[t - 1];
        
    return len2-t;
}

void init_matrix(int n)
{
    pref = (byte *)malloc(2*LENGTH + 1);
    
    int i, j;
    for(i = 0; i < n; i++)
	{
        pref_func1(container[i]);
        for(j = 0; j < n; j++)
		{
            if(j != i)
                matrix[j][i] = pref_func2(container[j], container[i]);
            else
                matrix[j][i] = 0;
        }
    }
    
    free(pref);
}

void count_least(int *cort, int nel)
{
    int i, current = 0;
    for(i = 0; i < (nel - 1); i++)
        current += matrix[cort[i]][cort[i + 1]];
        
    current += strlen(container[cort[i]]);

    if(current < shortest)
        shortest = current;
}

void permut_rec(short arr, int nel, int counter, int last, int sum)
{
    if(counter == nel)
	{
        sum += strlen(container[last]);
        
        if(sum < shortest)
            shortest = sum;
    } 
	else 
	{
        int i, new_sum;
        for(i = 0; i < nel; i++)
		{
            if(!counter)
			{
                last = i;
                new_sum = sum;
            }
            
            if(GET_BIT(arr, i))
			{
                new_sum = sum + matrix[last][i];
                permut_rec(ERASE_q_ARR(arr, i), nel, counter + 1, i, new_sum);
            }
        }
    }
}

void permut(short arr, int nel)
{
    shortest = 10*LENGTH;
    permut_rec(arr, nel, 0, 0, 0);
    
    printf("%i\n", shortest);
}

short init_arr(int m)
{
    return SET_BIT(m) - 1;
}

short erase_q_arr(short arr, int q)
{
	if(GET_BIT(arr, q))
		return arr ^ SET_BIT(q);
	else
		return arr;
}

int *add_q_cort(int *cort, int q, int i)
{
    cort[i] = q;
    
    return cort;
}
