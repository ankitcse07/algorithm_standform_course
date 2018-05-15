/*The goal of this problem is to implement the "Median Maintenance" algorithm (covered in the Week 3 lecture on heap applications). The text file contains a list of the integers from 1 to 10000 in unsorted order; you should treat this as a stream of numbers, arriving one by one. Letting x_ix 
i
?	  denote the iith number of the file, the kkth median m_km 
k
?	  is defined as the median of the numbers x_1,\ldots,x_kx 
1
?	 ,,x 
k
?	 . (So, if kk is odd, then m_km 
k
?	  is ((k+1)/2)((k+1)/2)th smallest number among x_1,\ldots,x_kx 
1
?	 ,,x 
k
?	 ; if kk is even, then m_km 
k
?	  is the (k/2)(k/2)th smallest number among x_1,\ldots,x_kx 
1
?	 ,,x 
k
?	 .)

In the box below you should type the sum of these 10000 medians, modulo 10000 (i.e., only the last 4 digits). That is, you should compute (m_1+m_2+m_3 + \cdots + m_{10000}) \bmod 10000(m 
1
?	 +m 
2
?	 +m 
3
?	 +?+m 
10000
?	 )mod10000.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <assert.h>

using namespace std;

void  swap ( int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void HeapifyDown(int *heap, int nodeIndex, int totalCount, int isMaxHeap)
{
    int left = ((2*nodeIndex) <= totalCount) ? 2*nodeIndex : 0;
    int right = ((2*nodeIndex + 1) <= totalCount) ? 2*nodeIndex + 1: 0;

    if( !left && !right)
        return;

    if(isMaxHeap)
    {
        int maxIndex = nodeIndex;

        if(left)
        {
            if(heap[left] > heap[nodeIndex])
                maxIndex = left;
            else
                maxIndex = nodeIndex;
        }

        if(right)
        {
            if(heap[right] > heap[maxIndex])
                maxIndex = right;
        }

        if(maxIndex != nodeIndex)
        {
            swap(heap[maxIndex], heap[nodeIndex]);
            HeapifyDown(heap, maxIndex, totalCount, isMaxHeap);
        }
    }
    else
    {
        int minIndex = nodeIndex;

        if(left)
        {
            if(heap[left] < heap[nodeIndex])
                minIndex = left;
            else
                minIndex = nodeIndex;
        }

        if(right)
        {
            if(heap[right] < heap[minIndex])
                minIndex = right;
        }

        if(minIndex != nodeIndex)
        {
            swap(heap[minIndex], heap[nodeIndex]);
            HeapifyDown(heap, minIndex, totalCount, isMaxHeap);
        }

    }

}

void Heapify(int *heap, int nodeIndex, int isMaxHeap)
{
    int parent = nodeIndex/2;

    if(parent == 0)
        return;

    if(isMaxHeap)
    {
        if(heap[parent] < heap[nodeIndex])
        {
            swap(heap[parent], heap[nodeIndex]);
            Heapify(heap, parent, isMaxHeap);
        }
    }
    else 
    {
        if(heap[parent] > heap[nodeIndex])
        {
            swap(heap[parent], heap[nodeIndex]);
            Heapify(heap, parent, isMaxHeap);
        }
    }
}


int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    
    char buffer[1024];

    int heap_low_max[5002 + 1];
    int heap_high_min[5002  + 1];

    int heap_low_cnt = 0;
    int heap_high_cnt= 0;

    int number;

    long long SumOfMedians = 0;
    while(fgets(buffer, 1024, fp) != NULL)
    {
        number = atoi(buffer);

        if(heap_low_cnt == 0)
        {
           heap_low_cnt++;
           heap_low_max[heap_low_cnt] = number;
        }
        else
        {
            if(number < heap_low_max[1]) // Compare with root
            {
                heap_low_cnt++;
                heap_low_max[heap_low_cnt] = number;
                Heapify(heap_low_max, heap_low_cnt, 1);
            }
            else
            {
                heap_high_cnt++;
                heap_high_min[heap_high_cnt] = number;
                Heapify(heap_high_min, heap_high_cnt, 0);
            }

            // Adjust
            if((heap_low_cnt - 1) > heap_high_cnt)
            {
                int maxInLow = heap_low_max[1];
                heap_low_max[1] = heap_low_max[heap_low_cnt];
                heap_low_cnt--;
                HeapifyDown(heap_low_max, 1, heap_low_cnt, 1);

                heap_high_cnt++;
                heap_high_min[heap_high_cnt] = maxInLow;
                Heapify(heap_high_min, heap_high_cnt, 0);
            }
            else if( (heap_high_cnt - 1) > heap_low_cnt)
            {
                int minInHigh = heap_high_min[1];
                heap_high_min[1] = heap_high_min[heap_high_cnt];
                heap_high_cnt--;
                HeapifyDown(heap_high_min, 1,  heap_high_cnt, 0);

                heap_low_cnt++;
                heap_low_max[heap_low_cnt] = minInHigh;
                Heapify(heap_low_max, heap_low_cnt, 1);
            }
        }


        int heapCnt = heap_low_cnt + heap_high_cnt;
        int medianIndex;

        if(heapCnt%2)
        {
            medianIndex = (heapCnt + 1)/2;
        }
        else
            medianIndex = heapCnt/2;

        if(medianIndex == heap_low_cnt)
            SumOfMedians += heap_low_max[1];
        else
        {
            assert(medianIndex == heap_high_cnt);
            SumOfMedians += heap_high_min[1];
        }
        

    }

    printf("Total count in max = %d, min = %d %lld\n", heap_low_cnt, heap_high_cnt, SumOfMedians);
    printf("Answer = %lld\n", (SumOfMedians%10000));
#if 0
    printf("Heap High Min = ");
    for(int i = 1; i <= heap_high_cnt; i++)
        printf("%d ", heap_high_min[i]);
    printf("\n\n");

    printf("Heap Low Max = ");
    for(int i = 1; i <= heap_low_cnt; i++)
        printf("%d ", heap_low_max[i]);
    printf("\n\n");
#endif
    fclose(fp);
}



