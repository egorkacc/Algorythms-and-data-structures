#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REQUEST(str) if(!strcmp(command, #str))

#define NAME_LENGTH 256
#define LENGTH 10
#define LOOP -1

#define rank(x) (x->left ? x->left->count : 0)

typedef char boolean;
typedef char val_type[LENGTH];
typedef int (*cmp_void)(int, int);

typedef struct Node
{
	int key;
    int count;
    
    char *value;

    struct Node *parent;
    struct Node *right;
    struct Node *left;
} *node;

typedef struct Tree
{
    node Head;
    
    cmp_void compare;
} *tree;

tree init_tree(cmp_void cmp);
tree delete_node(tree Tr, int key);
tree replace_node(tree Tr, const node x, node y);

node search_by_rank(tree Tr, int index);
node insert(tree Tr, node New_elem);
node descend(tree Tr, int key);

node minimum(node Head);
node succ(node x);

node scan_elem();
node init_node();

int compare(int a, int b);

void decrease_count(node x);
void delete_nodes_after(node Head);
void delete_tree(tree Tr);

void commands(tree Tr, int n);

int main(int argc, char **argv)
{
    tree Tr = init_tree(compare);
    
    int n;
    scanf("%i", &n);
    
    commands(Tr, n);

    delete_tree(Tr);
    
    return 0;
}

tree init_tree(cmp_void cmp)
{
    tree New_tree = (tree)malloc(sizeof(struct Tree));
    
    New_tree->Head = NULL;
    New_tree->compare = cmp;
    
    return New_tree;
}

tree delete_node(tree Tr, int key)
{
    node x = descend(Tr, key);
    
    if(!x)
	{
        printf("DELETE: object %i doesn't exist\n", key);
        
        return Tr;
    }
    
    if(x->left && x->right)
	{ 
        node y = succ(x);
        
        decrease_count(y);
        
        replace_node(Tr, y, y->right);
        
        x->left->parent = y;
        y->left = x->left;
        
        if(x->right)
            x->right->parent = y;
            
        y->right = x->right;
        y->count = x->count;
        
        replace_node(Tr, x, y);
        
        free(x);
        
        return Tr;
    }
    
    decrease_count(x);
    
    if(!(x->left) && !(x->right))
	{
        replace_node(Tr, x, NULL);
        
        free(x);
        
        return Tr;
    }
    
    if(!(x->left))
	{
        replace_node(Tr, x, x->right);
        
        free(x);
        
        return Tr;
    }
    
    if(!(x->right))
	{
        replace_node(Tr, x, x->left);
        
        free(x);
        
        return Tr;
    }
    
    return NULL;
}

tree replace_node(tree Tr, const node x, node y)
{
    if(x == Tr->Head)
	{
        Tr->Head = y;
        y->parent = NULL;
        
        return Tr;
    }
    
    node p = x->parent;
    
    if(y)
        y->parent = p;
        
    if(p->left == x)
        p->left = y;
    else
        p->right = y;
        
    return Tr;
}

node search_by_rank(tree Tr, int index)
{
    node temp = Tr->Head;
    if(!temp)
	{
        printf("SEARCH BY RANK: the tree is empty.\n");
        
        return NULL;
    }
    
    while(rank(temp) != index)
	{
        while(rank(temp) > index)
            temp = temp->left;
            
        while(rank(temp) < index)
		{
            index = index - rank(temp) - 1;
            
            temp = temp->right;
        }
    }
    
    return temp;
}

node insert(tree Tr, node New_elem)
{
    if(!(Tr->Head)) 
	{
        Tr->Head = New_elem;
        
        return New_elem;
    }
    node temp = Tr->Head;
    
    int assistor;
    while(LOOP)
	{
        assistor = Tr->compare(New_elem->key, temp->key);
        
        if(!assistor)
		{
            printf("INSERT: element already exists %s %i\n", New_elem->value, temp->key);
            
            free(New_elem);
            
            return temp;
        }
        
        ++(temp->count);
        
        if(assistor == -1)
		{
            if(!(temp->left))
			{
                temp->left = New_elem;
                
                New_elem->parent = temp;
                New_elem->count += rank(New_elem);
                
                return New_elem;
            } 
			else
                temp = temp->left;
        } 
		else
		{
            if(!(temp->right))
			{
                temp->right = New_elem;
                
                New_elem->parent = temp;
                New_elem->count += rank(New_elem);
                
                return New_elem;
            } 
			else
                temp = temp->right;
        }
    }
    
    return NULL;
}

node descend(tree Tr, int key)
{
    node temp = Tr->Head;
    while(temp && (Tr->compare(temp->key, key)))
	{
        if(Tr->compare(temp->key, key) == 1)
            temp = temp->left;
        else
            temp = temp->right;
    }
    
    if(!temp)
        printf("DESCEND: object %i doesn't exist\n", key);

    return temp;
}

node minimum(node Head)
{
    if(!Head)
	{
        printf("MINIMUM: the tree is empty\n");
        
        return NULL;
    } 
	else 
	{
        node temp = Head;
        while(temp->left)
            temp = temp->left;
            
        return temp;
    }
}

node succ(node x)
{
    if(x->right)
        return minimum(x->right);
        
    node y = x->parent;
    
    while(y && (x == y->right))
	{
        x = y;
        
        y = y->parent;
    }
    
    return y;
}

node scan_elem()
{
    node New = init_node();
    
    scanf("%i %s", &New->key, New->value);
    
    return New;
}

node init_node()
{
    node New_node = (node)malloc(sizeof(struct Node) + LENGTH);
    
    New_node->left = NULL;
    New_node->right = NULL;
    New_node->parent = NULL;
    
    New_node->value = (char *)(New_node + 1);
    New_node->count = 1;
    
    return New_node;
}

int compare(int a, int b)
{
    if(a == b) 
		return 0;
	else if(a > b)
		return 1;
	else
		return -1;
}

void decrease_count(node x)
{
    node temp = x->parent;
    
    while(temp)
	{
        --(temp->count);
        
        temp = temp->parent;
    }
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

void delete_tree(tree Tr)
{
    delete_nodes_after(Tr->Head);
    
    free(Tr);
    
    Tr = NULL;
}

void commands(tree Tr, int n)
{
    char command[NAME_LENGTH];
    node temp = NULL;
    
    int N = n;
    for(N; N; temp = NULL, N--)
	{
        scanf("%s", command);
        
        REQUEST(SEARCH)
		{
			int input;
            scanf("%i", &input);
            
            temp = search_by_rank(Tr, input);
            
            printf("%s\n", temp->value);
        }
        
        REQUEST(LOOKUP)
		{
			int input;
            scanf("%i", &input);
            
            temp = descend(Tr, input);
            printf("%s\n", temp->value);
            
            continue;
        }
        
        REQUEST(DELETE)
		{
			int input;
            scanf("%i", &input);
            
            delete_node(Tr, input);
            
            continue;
        }
        
        REQUEST(INSERT)
		{
            temp = init_node();
            
            scanf("%i %s", &temp->key, temp->value);
            insert(Tr, temp);
            
            continue;
        }
    }
}
