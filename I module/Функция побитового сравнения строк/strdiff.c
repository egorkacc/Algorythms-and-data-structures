#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strdiff(char *a, char *b);
/*
int main(int argc, char **argv)
{
	char str1[64], str2[64];
	gets(str1);
	gets(str2);
	
	printf("%i\n", strdiff(str1, str2));;
    
	return 0;
}
*/
int strdiff(char *a, char *b)
{
    int res = 0;
    
    if(strcmp(a, b) == 0)
        return -1;
    else 
	{
		char _a = *a, _b = *b;
        
        int i = 0;
        while((_a&1) == (_b&1)) 
		{
            _a >>= 1;
            _b >>= 1;
            
            ++res;
            if(res%8 == 0)
			{
                _a = *(a + i);
                _b = *(b + i);
                ++i;
            }
        }
    }	

	return res;
}
