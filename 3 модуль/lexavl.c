#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SHOW_RECURSION_DEPTH(i) {int k; for(k = 0; k < i; ++k) printf("  |");}

#define LENGTH 256
#define LOOP -1

typedef char boolean;
typedef int (*cmp_void)(const char *, const char *);
typedef char val_type[LENGTH];

typedef struct Node
{
    int key;
    int balance;
 
	char *value;
       
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} *node;

typedef struct Tree
{
	int last_index;
	
    node Head;
    
    cmp_void compare;
} *tree;

tree init_tree(cmp_void cmp);

node init_node();
node insert(tree T, node New_elem);
node insert_avl(tree T, node elem);

int SPEC_S = 777;

int spec_symbol(int c);

void const_finder(int ch, int nel);

void delete_nodes_after(node Head);
void delete_tree(tree T);

void tau_l(tree T, node leaf);
void tau_r(tree T, node leaf);

void replace_node_destructive(tree T, node x, node y);

void get_ident(char *buffer, int bufsize, int *global_counter);

void inspector(tree Idents);

int main(int argc, char **argv)
{
    tree Identifiers = init_tree(strcmp);
    
    inspector(Identifiers);
    
    delete_tree(Identifiers);
    
    return 0;
}

tree init_tree(cmp_void cmp)
{
    tree New_tree = (tree)malloc(sizeof(struct Tree));
    
    New_tree->Head = NULL;
    New_tree->last_index = 0;
    New_tree->compare = cmp;
    
    return New_tree;
}

node init_node()
{
    node New_node = (node)malloc(sizeof(struct Node)+LENGTH);
    
    New_node->left = New_node->right = New_node->parent = NULL;
    New_node->value = (char *)(New_node + 1);
    New_node->balance = 0;
    
    return New_node;
}

node insert(tree T, node New_elem)
{
    if(!(T->Head))
	{
        T->Head = New_elem;
        New_elem->key = 0;
        T->last_index = 1;
        
        return New_elem;
    }
    
    node Temp = T->Head;
    
    int assistor;
    while(LOOP)
	{
        assistor = T->compare(Temp->value, New_elem->value);
        if(!assistor)
		{
            free(New_elem);
            
            return Temp;
        }
        
        if(assistor == -1)
		{
            if(!Temp->left)
			{
                Temp->left = New_elem;
                
                New_elem->parent = Temp;
                New_elem->key = T->last_index;
                
                ++(T->last_index);
                
                return New_elem;
            }
			else
                Temp = Temp->left;
        }
		else 
		{
            if(!Temp->right)
			{
                Temp->right = New_elem;
                
                New_elem->parent = Temp;
                New_elem->key = T->last_index;
                
                ++(T->last_index);
                
                return New_elem;
            } 
			else
                Temp = Temp->right;
        }
    }
    
    return NULL;
}

node insert_avl(tree T, node elem)
{
    node a = insert(T, elem);
    node x = a->parent;
    
    a->balance = 0;
    while(LOOP)
	{
        x = a->parent;
        
        if(!x)
            return a;
            
        if(a == (x->left))
		{ 
            --(x->balance);
            
            if(!(x->balance))
                break;

            if(x->balance == -2)
			{
                if(a->balance == 1)
                    tau_l(T, a);
                    
                tau_r(T, x);
                
                break;
            } 
        } 
        else
		{
            ++(x->balance);
            
            if(!(x->balance))
                break;
                
            if(x->balance == 2)
			{
                if(a->balance == -1)
                    tau_r(T, a);
                    
                tau_l(T, x);
                
                break;
            }
        }
    }
    
    return a;
}

int spec_symbol(int c)
{
    switch(c)
	{
	    case '+' : return 0;
	    case '-' : return 1;
	    case '*' : return 2;
	    case '/' : return 3;
	    case '(' : return 4;
	    case ')' : return 5;
	    
	    default : return -1;
    }
}

void const_finder(int ch, int nel)
{
	char const_digit[nel];
	
    int j = 0, CH = ch;
    while(isdigit(ch) && (CH != EOF))
    {
        const_digit[j] = ch;
        
        j++;
        
        ch = getchar();
    }
    
    int i;
    for(i = 0; i < j; i++)
    	printf("%c", const_digit[i]);
    	
    printf("\n");
    
    if(spec_symbol(ch) != -1)
    	printf("SPEC %i\n", spec_symbol(ch));
		
}

void delete_nodes_after(node Head)
{
    if(Head)
	{
        delete_nodes_after(Head->left);
        delete_nodes_after(Head->right);
        
        free(Head);
        
        Head = NULL;
    }
}

void delete_tree(tree T)
{
    delete_nodes_after(T->Head);
    
    free(T);
    
    T = NULL;
}

void tau_l(tree T, node leaf)
{
    node x = leaf;
    node y = x->right;
    node parent = x->parent;

    if(!y) 
	{
        printf("ROTATE_LEFT: !ERROR! right child is trivial.\n");
        
        return;
    }

    if(x != T->Head)
    {
        if(parent->left == x)
            parent->left = y;
        else
            parent->right = y;
    }
    else
        T->Head = y;
        
    y->parent = parent;
    x->parent = y;
    x->right = y->left;

    if(x->right)
        x->right->parent = x;

    y->left = x;

    --(x->balance);
    
    if(y->balance > 0)
        x->balance -= y->balance;
        
    --(y->balance);
    
    if(x->balance < 0)
        y->balance += x->balance;
}

void tau_r(tree T, node leaf)
{
    node x = leaf;
    node y = x->left;
    node parent = x->parent;

    if(!y) 
	{
        printf("ROTATE_LEFT: !ERROR! left child is trivial.\n");
        
        return;
    }

    if (x != T->Head)
    {
        if (parent->right == x)
            parent->right = y;
        else
            parent->left = y;
    }
    else
        T->Head = y;
        
    y->parent = parent;
    x->parent = y;
    x->left = y->right;

    if (x->left)
        x->left->parent = x;

    y->right = x;
    
    ++(x->balance);
    
    if(y->balance < 0)
        x->balance -= y->balance;
        
    ++(y->balance);
    
    if(x->balance > 0)
        y->balance += x->balance;
}

void replace_node_destructive(tree T, node x, node y)
{
    if(x == T->Head)
	{
        delete_nodes_after(T->Head);
        
        T->Head = y;
        
        return;
    }
    
    node p = x->parent;
    
    if(y)
	{
        if(y->parent)
		{
            if(y == y->parent->left)
                y->parent->left = NULL;
            else if(y == y->parent->right)
                y->parent->right = NULL;
        }
        
        y->parent = x->parent;
    }
    
    if(p->left == x)
        p->left = y;
    else
        p->right = y;
        
    delete_nodes_after(x);
}

void get_ident(char *buffer, int bufsize, int *global_counter)
{
	char *buffer1 = buffer;
    int len, c;
	int C = c;
    	
    for(len = 0; (len < (bufsize - 1)) && (isdigit(c) || isalpha(C = getchar())); len++)
	{	
		c = getchar();
//		printf("%i %i\n", C, c);
		
		buffer1[len] = (char)C;
        buffer[len] = (char)c;
        
        if(buffer1[len] == ' ' && buffer[len] == ' ')
        	break;
        
//      	printf("|%c %c|\n", buffer1[len], buffer[len]);
	   
        ++(*global_counter);
    }
	
//	printf("%i\n", len);
//	printf("%c %c\n", C, c);
	
	if(len)
		SPEC_S = spec_symbol(C);
		
		
	buffer1[len] = '\0'; 
    buffer[len] = '\0';
		
	if(!len && SPEC_S != 777 && isdigit(C) && (SPEC_S != -1))
		printf("SPEC %i\n", SPEC_S);
    
//    printf("=============================\n");
}


/*
28
alpha + x1 (beta alpha) x1 y
IDENT 0
SPEC 0
IDENT 1
SPEC 4
IDENT 2
IDENT 0
!! SPEC 5 !!
IDENT 1
IDENT 3
*/
void inspector(tree Idents)
{
	node New_ident = NULL;
	
    int n;
    scanf("%i", &n);

    int c, i = -2;
    int current_ident_id = 0;
	while((c = getchar()) != EOF)
	{	
//		printf("<%c>\n", c);
		
        if(isspace(c))
            continue;  
        
        if(isdigit(c))
		{
			printf("CONST ");
			
        	const_finder(c, n);
          
		    continue;
        }
        
        if(!isalpha(c))
        	printf("SPEC %i\n", spec_symbol(c));
        else
		{
			New_ident = init_node();
            New_ident->value[0] = c;
		
            get_ident(New_ident->value + 1, LENGTH - 1, &i);
            
            New_ident = insert_avl(Idents, New_ident);
            
            printf("IDENT %i\n", New_ident->key);
            
            continue;
        }
    }
}
