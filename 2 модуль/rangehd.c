#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000
#define ACT_COU 2

void tree_build(int *v, int n, int **pT);
void tree_update(int *tree, int n, int a, char *substr);
int tree_satisfy(int *tree, int n, int a, int b);

int action_index(char *action);

char *actions[ACT_COU] = {"HD", "UPD"};

int main(int argc, char **argv)
{
    char str[SIZE];
    scanf("%s", str);

    int len = strlen(str),
        power = 1;

    while(power < len) 
		power *= 2;

    int *v = (int *)malloc(sizeof(int)*power);

	int i = 0;
    while(i < power)
    {
        v[i] = 0;
        if(i < len) 
			v[i] = 1 << str[i] - 'a';
        
        ++i;
    }
    i = 0;

    int m;
    scanf("%i", &m);
    
    int *T;
    tree_build(v, power, &T);

    while(i < m)
    {
    	char s[SIZE];
        char action[4];
        scanf("%s", action);
        
        int idx = action_index(action);

		int p, q;
        scanf("%i", &p);
        
        if(idx == 1)
		{
            scanf("%s", s);
            tree_update(T, power, p, s);
            
            break;	
		}
        else if(!idx)
        {
        	scanf("%i", &q);
            printf("%s\n", tree_satisfy(T, power, p, q) ? "YES" : "NO");
            
            break;
		}
		
		++i;	
    }
    
    free(v);
    free(T);
    
    return 0;
}

void tree_build(int *v, int n, int **pT)
{
    int *T = (int *)malloc(sizeof(int)*(2*n));
    
    int i;
    for(i = 0; i < n; i++)
        T[n + i] = v[i];
    
    for(i = n - 1; i; i--)
        T[i] = T[2*i]^T[2*i + 1];

    *pT = T;
}

void tree_update(int *tree, int n, int a, char *substr)
{
	int _a, value, i;
    int len = strlen(substr);
    
    for(i = 0; i < len; i++)
    {
        value = (1 << substr[i] - 'a');
        _a = a + (n + i);

        tree[_a] = value;
        while(_a/2)
        {
            _a /= 2;
            tree[_a] = tree[2*_a] ^ tree[2*_a + 1];
        }
    }
}

int tree_satisfy(int *tree, int n, int a, int b)
{
	int i = 0;
	int overbit_cou = 0;
    int sum = 0;
    
    if(a == b) 
		sum = tree[a + n];
    else
    {
        a += n;
        b += n;
		
		int _a, _b;
        while(a <= (b - 1))
        {
        	_a = a, _b = b;
        	
            if(((a + 1) < b) && a%2)
            {
				++_a;
                sum ^= tree[_a];
			}
			
            if((a < (b - 1)) && !(b%2))
            {
				--_b;
                sum ^= tree[_b];     
			}
			
            if((_b - _a - 1) < 1)
            {
                sum ^= tree[_b]^tree[_a];
                
                break;
            }

            a /= 2;
            b /= 2;
        }  
    }

    while(i < (-'a' + 'z'))
    {
        overbit_cou += (sum >> i)%2;
        
        ++i;
    }

    return (overbit_cou - 1) < 1;
}

int action_index(char *action)
{
	int i = 0;
    while(i < ACT_COU)
    {
        if(!strcmp(action, actions[i])) 
			return i;
		
		++i;	
	}
	
    return -1;
}
