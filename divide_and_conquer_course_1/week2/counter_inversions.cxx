/*
   This file contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some order, with no integer repeated.

   Your task is to compute the number of inversions in the file given, where the ith row of the file indicates the ith entry of an array.

   Because of the large size of this array, you should implement the fast divide-and-conquer algorithm covered in the video lectures.

   The numeric answer for the given input file should be typed in the space below.

   So if your answer is 1198233847, then just type 1198233847 in the space provided without any space / commas / any other punctuation marks. You can make up to 5 attempts, and we'll use the best one for grading.

Answer: 2407905288
   */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100000

long long countInversions(int *arr, int size)
{
    if(size == 1)
        return 0;
    else if ( size == 2)
    {
        if(arr[0] > arr[1])
        {
            int tmp = arr[1];
            arr[1] = arr[0];
            arr[0] = tmp;
            return 1;
        }
        else
            return 0;
    }
    else
    {
        long long tInv1 = countInversions(arr, size/2);
        long long tInv2 = countInversions(arr + size/2, (size - size/2));

        long long totalInversions = tInv1 + tInv2;

        int size1 = size/2;
        int size2 = size -size/2;

        int *ptr1 = arr;
        int *ptr2 = arr + size/2;

        int i = 0;
        int j = 0;

        int *mergeCopy = new int [size1 + size2];
        int k = 0;

        while( (i < size1) && ( j < size2))
        {
            if(ptr1[i] < ptr2[j] )
            {
                mergeCopy[k++] = ptr1[i];
                i++;
            }
            else 
            {
                totalInversions += (size1 - i);
                mergeCopy[k++] = ptr2[j++];
            }
        }
        while( i < size1 )
        {
            mergeCopy[k++] = ptr1[i++];
        }
        while( j < size2)
        {
            mergeCopy[k++] = ptr2[j++];
        }
        for(i = 0; i < k; i++)
            arr[i] = mergeCopy[i];
        delete [] mergeCopy;

        return totalInversions;
    }

}

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


    long long total = countInversions(interArray, i);
    printf("Total value of i = %d, %lld\n", i, total);

    /*
    FILE *fp1 = fopen("output.txt", "w");

    for(int j = i - 1; j >=0; j--)
        fprintf(fp1, "%d\n", interArray[j]);

    total = countInversions(interArray, i);
    printf("Total value of i = %d, %lld\n", i, total);

    //for(int j = 0; j < i; j++)
      //  printf("%d\n", interArray[j]);
*/
    fclose(fp);
  //  fclose(fp1);

}
