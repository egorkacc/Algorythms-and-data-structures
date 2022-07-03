#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char str[1000000];
	gets(str);
	
	int k;
	int letters[26 + 1] = {};
	int slen = strlen(str);
	
	int _slen = slen;
	for( ; _slen; _slen--)
	{
		k = str[slen - _slen] - 97;
		++letters[k];
	}
	k = 0;
	
	for(k; k < 26; k++)
		while(letters[k])
		{
			--letters[k];
			printf("%c", k + 97);
		}
	printf("\n");
	
	return 0;
}


