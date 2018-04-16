#include <stdio.h>
#include <stdlib.h>

/*
 * GENERAL DIRECTIONS AND HOW TO GIVE US YOUR ANSWER:
 *
 * See the first question.
 *
 * DIRECTIONS FOR THIS PROBLEM:
 *
 * Compute the number of comparisons (as in Problem 1), using the "median-of-three" pivot rule. [The primary motivation behind this rule is to do a little bit of extra work to get much better performance on input arrays that are nearly sorted or reverse sorted.] In more detail, you should choose the pivot as follows. Consider the first, middle, and final elements of the given array. (If the array has odd length it should be clear what the "middle" element is; for an array with even length 2k, use the kth element as the "middle" element. So for the array 4 5 6 7, the "middle" element is the second one ---- 5 and not 6!) Identify which of these three elements is the median (i.e., the one whose value is in between the other two), and use this as your pivot. As discussed in the first and second parts of this programming assignment, be sure to implement Partition exactly as described in the video lectures (including exchanging the pivot element with the first element just before the main Partition subroutine).
 *
 * EXAMPLE: For the input array 8 2 4 5 7 1 you would consider the first (8), middle (4), and last (1) elements; since 4 is the median of the set {1,4,8}, you would use 4 as your pivot element.
 *
 * SUBTLE POINT: A careful analysis would keep track of the comparisons made in identifying the median of the three candidate elements. You should NOT do this. That is, as in the previous two problems, you should simply add m-1 to your running total of comparisons every time you recurse on a subarray with length m.
 *
 */



long long quick_sort_comparisons(int * array, int start, int end)
{
    if(start >= end)
        return 0;

    int tmp;
    int pivot = array[end];
    int pivot_index = end;

    if( (end - start) > 1)
    {
        int middle = (end + start)/2;

        int max, min;

        if(array[start] > array[middle])
        {
            max = start;
            min = middle;
        }
        else
        {
            max = middle;
            min = start;
        }

        if(array[max] < array[end])
            max = end;

        if(array[min] > array[end])
            min = end;

        if((start != max) && (start != min))
            pivot_index = start;
        else if((middle != max) && (middle != min))
            pivot_index = middle;
        else
            pivot_index = end;

        pivot = array[pivot_index];

        //printf("MIN = %d, MEDIAN = %d, MAX = %d\n", array[min], array[pivot_index], array[max]); 

    }

    tmp = array[start];
    array[start] = pivot;
    array[pivot_index] = tmp;

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
