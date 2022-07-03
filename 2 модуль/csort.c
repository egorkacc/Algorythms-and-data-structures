#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csort(char *src, char *dest);
int split(char *s, char ***w);
int get_string(char **p);

int main(int argc, char **argv)
{
	char c;
	char *string;
	int slen = get_string(&string);

	char sorted_string[slen];
	csort(string, sorted_string);

	printf("%s\n", sorted_string);
	
	free(string);
	return 0;
}

int split(char *s, char ***w)
{
	char c = -1;
	char **wrds = '\0', *wrd = '\0';
	
	unsigned long wcou = 0, chcou = 0;
	while(c != '\0')
	{
		c = *(s++);
		
		if((c != ' ') && (c != '\0'))
		{
			if(!chcou) 
				wrd = (char *)malloc(sizeof(char));
			else 
				wrd = (char *)realloc(wrd, sizeof(char)*(chcou + 1));
				
			*(wrd + chcou) = c;
			++chcou;
		}
		else if(chcou)
		{
			wrd = (char *)realloc(wrd, sizeof(char)*(chcou + 1));
			wrd[chcou] = '\0';
				
			wrds = (char **)realloc(wrds, sizeof(char *)*(wcou + 1));
			*(wrds + wcou) = wrd;
			
			chcou = 0;
			++wcou;
		}
	}
	*w = wrds;
	
	return wcou;
}


void csort(char *src, char *dest) 
{
	int i, j;
	char **wrds;
	int NULL_idx = 0;
	int wcou = split(src, &wrds);

	int cou[wcou];
	for(i = 0; (i - wcou) < 0; i++) 
		cou[i] = 0;

	for(i = 0; (i - wcou + 1) < 0; i++)
	{
		int l1 = strlen(wrds[i]);
		NULL_idx += l1 + 1;

		for(j = i + 1; (j - wcou) < 0; j++)
		{
			int l2 = strlen(wrds[j]);

			if((l1 - l2) > 0)
				cou[i] += l2 + 1;
			else 
				cou[j] += l1 + 1;
		}
	}

	NULL_idx += strlen(wrds[wcou - 1]);

	for(i = 0; (i - wcou) < 0; i++)
		strcpy(dest + cou[i], wrds[i]);

	for(i = 0; (i - wcou) < 0; i++)
		if(cou[i])
			dest[cou[i] - 1] = ' ';

	dest[NULL_idx] = '\0';

	for(i = 0; (i - wcou) < 0; i++)
		free(wrds[i]);
	free(wrds);
}

int get_string(char **p)
{
	char *wrds = (char *)malloc(sizeof(char));
	
	char c;
	scanf("%c", &c);

	int slen = 0;
	
	while(c != '\n')
	{
		wrds[slen] = c;
		wrds = (char *)realloc(wrds, sizeof(char)*(++slen + 1));
		scanf("%c", &c);
	}
	wrds[slen] = '\0';

	*p = wrds;
	
	return slen;
}
