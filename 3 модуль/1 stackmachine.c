#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 100 

#define alloc(n, type) (type *)malloc(n*sizeof(type))

#define COMMAND(str) if(!strcmp(command, #str))

typedef char boolean;
typedef int my_type;
typedef my_type (* bin_op)(my_type, my_type);

typedef struct Stack
{
    my_type *data;
    
    int cap;
    int top;
} stack;

boolean stack_empty(stack *s);

my_type add(my_type a, my_type b);
my_type sub(my_type a, my_type b);
my_type mul(my_type a, my_type b);
my_type divide(my_type a, my_type b);
my_type max(my_type a, my_type b);
my_type min(my_type a, my_type b);
my_type pop(stack *s);

void init_stack(stack *s, int n);
void delete_stack(stack *s);

void push(stack *s, my_type x);

void scan_data(stack *s);

void arithmetics(stack *s, bin_op operation);
void neg(stack *s);
void dup(stack *s);
void swap(stack *s);

void commands(stack *s, int n);

int main(int argc, char **argv)
{
    stack *S = alloc(1, stack);
    int n;
    scanf("%i", &n);
    init_stack(S, n);
    commands(S, n);
    printf("%i\n", S->data[S->top-1]);
    delete_stack(S);
    free(S);
    return 0;
}

boolean stack_empty(stack *s)
{
    return !(s->top);
}

my_type add(my_type a, my_type b)
{
    return (a + b);
}

my_type sub(my_type a, my_type b)
{
    return (a - b);
}

my_type mul(my_type a, my_type b)
{
    return a*b;
}

my_type divide(my_type a, my_type b)
{
    return a/b;
}

my_type max(my_type a, my_type b)
{
	if(a > b)
		return a;
	else
		return b;
}

my_type min(my_type a, my_type b)
{
	if(a < b)
		return a;
	else
		return b;
}

my_type pop(stack *s)
{
    if(stack_empty(s))
	{
        printf("!Error! stack is empty\n");
        
        delete_stack(s);
        
        exit(1);
    }
    
    --(s->top);
    
    return s->data[s->top];
}

void init_stack(stack *s, int n)
{
    s->data = alloc(n, my_type);
    s->cap = n;
    s->top = 0;
}

void delete_stack(stack *s)
{
    free(s->data);
    
    s->cap = 0;
    s->top = 0;
}

void push(stack *s, my_type x)
{
    if(s->top == s->cap)
	{
        s->data = (my_type *)realloc(s->data, sizeof(my_type)*2*s->cap);
        s->cap *= 2;
    }
    
    s->data[s->top] = x;
    
    ++(s->top);
}

void scan_data(stack *s)
{
    int i, nel = s->cap;
    for(i = 0; i < nel; i++)
        scanf("%i", &s->data[i]);
}

void arithmetics(stack *s, bin_op operation)
{
    my_type a = pop(s);
    my_type b = pop(s);
    
    push(s, operation(a, b));
}

void neg(stack *s)
{
    my_type new_val = pop(s);
    
    push(s, -new_val);
}

void dup(stack *s)
{
    push(s, s->data[s->top - 1]);
}

void swap(stack *s)
{
    my_type a = pop(s);
    my_type b = pop(s);
    
    push(s, a);
    push(s, b);
}

void commands(stack *s, int n)
{
    char command[LENGTH];
    my_type arg;
    
    int i;
    for(i = 0; i < n; i++)
	{
        scanf("%s", command);
        
        COMMAND(CONST)
		{
            scanf("%i", &arg);
        
		    push(s, arg);
        }
        if(s->top > 1)
		{
            COMMAND(SUB)
			{
                arithmetics(s, sub);
            }
            
            COMMAND(ADD)
			{
                arithmetics(s, add);
            }
            
            COMMAND(MUL)
			{
                arithmetics(s, mul);
            }
            
            COMMAND(DIV)
			{
                arithmetics(s, divide);
            }
            
            COMMAND(MAX)
			{
                arithmetics(s, max);
            }
            
            COMMAND(MIN)
			{
                arithmetics(s, min);
            }

            COMMAND(SWAP)
			{
                swap(s);
            }
        }
        
        COMMAND(NEG)
		{
            neg(s);
        }
        
        COMMAND(DUP)
		{
            dup(s);
        }
    }
}
