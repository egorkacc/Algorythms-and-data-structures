#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 256

int wcount(char *s);

int main(int argc, char **argv)
{
	char *w = (char *)malloc(sizeof(char)*SIZE);

    fgets(w, sizeof(char)*SIZE, stdin);

	int ans = wcount(w);
    printf("%i\n", ans);
    
    free(w);
    
    return 0;
}

int wcount(char *s)
{
	int i;
	int f = 0, wcou = 0;

	for(i = 0; *(s + i); i++)
	{
        if((*(s + i) == '\n') || (*(s + i) == '\t') || (*(s + i) == ' '))
            f = 0;
        else if((*(s + i) != ' ') && !f)
		{
            f = 1;
            ++wcou;
        }
    }

    return wcou;
}
