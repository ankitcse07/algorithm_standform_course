#include <stdio.h>
#include <stdlib.h>

/*
 * GENERAL DIRECTIONS AND HOW TO GIVE US YOUR ANSWER:
 *
 * See the first question.
 *
 * DIRECTIONS FOR THIS PROBLEM:
 *
 * Compute the number of comparisons (as in Problem 1), always using the final element of the given array as the pivot element. Again, be sure to implement the Partition subroutine exactly as it is described in the video lectures.
 *
 * Recall from the lectures that, just before the main Partition subroutine, you should exchange the pivot element (i.e., the last element) with the first element.
 *
 */


long long quick_sort_comparisons(int * array, int start, int end)
{
    if(start >= end)
        return 0;

    int tmp;
    int pivot = array[end];

    tmp = array[start];
    array[start] = array[end];
    array[end] = tmp;

    int i = start + 1;

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
