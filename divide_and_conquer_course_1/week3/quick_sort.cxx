#include <stdio.h>
#include <stdlib.h>
/*
 * The file contains all of the integers between 1 and 10,000 (inclusive, with no repeats) in unsorted order. The integer in the ith row of the file gives you the ith entry of an input array.
 *
 * Your task is to compute the total number of comparisons used to sort the given input file by QuickSort. As you know, the number of comparisons depends on which elements are chosen as pivots, so we'll ask you to explore three different pivoting rules.
 *
 * You should not count comparisons one-by-one. Rather, when there is a recursive call on a subarray of length m, you should simply add m-1 to your running total of comparisons. (This is because the pivot element is compared to each of the other m-1 elements in the subarray in this recursive call.)
 *
 * WARNING: The Partition subroutine can be implemented in several different ways, and different implementations can give you differing numbers of comparisons. For this problem, you should implement the Partition subroutine exactly as it is described in the video lectures (otherwise you might get the wrong answer).
 *
 * DIRECTIONS FOR THIS PROBLEM:
 *
 * For the first part of the programming assignment, you should always use the first element of the array as the pivot element.
 *
 */


long long quick_sort_comparisons(int * array, int start, int end)
{
    if(start >= end)
        return 0;

    int pivot = array[start];
    int i = start + 1;
    int tmp;

    for(int j = start + 1; j <= end; j++)
    {
        if(array[j] < pivot){
            tmp = array[i];
            array[i]  = array[j];
            array[j] = tmp;
            i++;
        }
    }
    tmp = array[start];
    array[start] = array[i - 1];
    array[i - 1] = tmp;

    long long total_comparisons = (i - 2 - start + 1) + ( end - i + 1);

    total_comparisons += quick_sort_comparisons( array, start, i - 2);
    total_comparisons += quick_sort_comparisons(array, i, end);
    return total_comparisons;
}

#define MAX_SIZE 10000

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");

    char buffer[1024];

    int *interArray = new int[MAX_SIZE];

    int i = 0;
    while(fgets(buffer, 1024, fp) != NULL)
    {
        interArray[i++] = atoi(buffer);
    }

    long long total = quick_sort_comparisons(interArray, 0, i - 1);
    printf("Total value of i = %d, %lld\n", i, total);

    FILE *fp1 = fopen("output.txt", "w");

    for(int j = 0; j < i; j++)
        fprintf(fp1, "%d\n", interArray[j]);

    fclose(fp);
    fclose(fp1);

    return 0;
}
