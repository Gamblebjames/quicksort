/******************************************************************************
	File: quicksort.c
	Author: Ben Gamble
	Creation Date: 01/08/2018
	Last Modified: 01/10/2018
	Last Modified By: Ben Gamble
	Description: Divide and conquer algorithm to create a sorted list of
	integers in increasing order.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PROTOTYPES
int		*quicksort(int *arr, int low, int high);
int		partition(int *arr, int low, int high);
void	swap(int *a, int *b);
int		*get_data(char *path);
void	*write_data(int *arr);

// GLOBALS
static int count; // number of data elements

int main(
	int argc,
	char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <data path>\n", argv[0]);
		return(-1);
	}

	int		*arr;
	int		low, high;	// range of index values to be sorted
	char	*path;

	if((path = (char *)malloc(strlen(argv[1])+1)) == NULL) {
		perror("Failed to allocate memory");
		exit(-1);
	}
	strcpy(path, argv[1]);

	arr = get_data(path);
	
	low = 0;
	high = count-1;
	arr = quicksort(arr, low, high);

	write_data(arr);

	free(arr);
	free(path);

	return 0;
}

int *quicksort(
	int *arr, 
	int low, 
	int high)
{
	int p;

	if(low < high) {
		p = partition(arr, low, high);
		quicksort(arr, low, p-1);	// sort elements to the left of the pivot
		quicksort(arr, p+1, high);	// sort elements to the right of the pivot
	}

	return arr;
}

/*	Determine the pivot element and put data less than the pivot element on the
	left side of the array and elements greater than the pivot on the right.	
	Then, move the pivot to the index between those elements.				  */
int	partition(
	int *arr, 
	int low, 
	int high)
{
	int pivot = arr[high];
	int i = low-1;

	for(int j = low; j <= high-1; j++) {
		if(arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i+1], &arr[high]);

	return(i+1);
}

void swap(
	int *a, 
	int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*	Read data in a file pointed to by path.
	First number in the file should be the number of elements that follow.
	The rest of the elements are the numbers to be sorted in a single column. */
int *get_data(
	char *path)
{
	FILE	*data;	
	int		*arr;

	if((data = fopen(path, "r")) == NULL) {
		perror("Failed to open file");
		exit(-1);
	}

	// get the number of elements to be sorted
	if((fscanf(data, "%d", &count)) == 0) {
		perror("Failed to scan data");
		exit(-1);
	}

	if((arr = (int *)malloc(sizeof(int) * count)) == NULL) {
		perror("Failed to allocate memory");
		exit(-1);
	}
	for(int i = 0; i < count; i++) {
		if((fscanf(data, "%d", &arr[i])) == 0) {
			perror("Failed to scan data");
			exit(-1);
		}
	}

	return arr;
}

/*	The sorted array will be written to a file named 'sorted' in the working
	directory. The data will appear in a single sorted column.				 */	
void *write_data(
	int *arr)
{
	FILE *sorted;

	if((sorted = fopen("sorted", "w")) == NULL) {
		perror("Failed to open file");
		exit(-1);
	}	
	
	for(int i = 0; i < count; i++) {
		if((fprintf(sorted, "%d\n", arr[i])) == 0) {
			perror("Failed to scan data");
			exit(-1);
		}
	}
}
