#include <stdio.h>
#include <stdlib.h>
void quicksort(int low, int high, int m, int *pointer);
void selectsort(int low, int high, int *arr);
void swap(long p, long q, int *arr);
int partition(int low, int high, int *arr);
int compare(long p, long q, int *arr);

int main(int argc, char **argv)
{
	int n, m;
	scanf("%i %i", &n, &m);
	
	int i;
	int array[n];
	for(i = 0; i < n; i++)
		scanf("%i", &array[i]);
	
	quicksort(0, n - 1, m, array);
	
	for(i = 0; i < n; i++)
		printf("%i ", array[i]);
	printf("\n");
	
	return 0;
}

void quicksort(int low, int high, int m, int *pointer)
{
	while(high - low)
	{
		if((high - low) <= m)
		{
			selectsort(low, high, pointer);
			break;
		}
		
		int part = partition(low, high, pointer);
		
		if((low + high) > 2*part)
		{
			quicksort(low, part - 1, m, pointer);
			low = ++part;
		}
		else
		{
			quicksort(part + 1, high, m, pointer);
			high = --part;
		}
	}
}

void selectsort(int low, int high, int *arr)
{
	int i, j;
	
	int k = high;
	for(k; k > low; k--)
	{
		j = k;
		i = k - 1;
		
		while(i + 1)
		{
			if(compare(j, i, arr) == -1)
				j = i;
			--i;
		}
		
		swap(k, j, arr);
	}
}

void swap(long p, long q, int *arr)
{
	int temp = arr[p];
	arr[p] = arr[q];
	arr[q] = temp;
}

int partition(int low, int high, int *arr)
{
	int i, j;
	i = j = low;
	
	for(i; i < high; i++)
		if(compare(i, high, arr) == -1)
		{
			swap(i, j, arr);
			++j;
		}
		
	swap(j, high, arr);
	
	return j;
}

int compare(long p, long q, int *arr)
{
	if(arr[p] < arr[q])
		return -1;
	else if(arr[p] == arr[q])
		return 0;
	else
		return 1;
}
