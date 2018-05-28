/*
The goal of this problem is to implement a variant of the 2-SUM algorithm covered in this week's lectures.

The file contains 1 million integers, both positive and negative (there might be some repetitions!).This is your array of integers, with the i^{th}i 
th
  row of the file specifying the i^{th}i 
  th
   entry of the array.

   Your task is to compute the number of target values tt in the interval [-10000,10000] (inclusive) such that there are distinct numbers x,yx,y in the input file that satisfy x+y=tx+y=t. (NOTE: ensuring distinctness requires a one-line addition to the algorithm from lecture.)

    Write your numeric answer (an integer between 0 and 20001) in the space provided.

    OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing your own hash table for it. For example, you could compare performance under the chaining and open addressing approaches to resolving collisions.


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unordered_map>

using namespace std;

#define MAX_SIZE 100000

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    char buffer[1024];

    unordered_map <long long, int> myarray;

    long long tmp;
    while(fgets(buffer, 1024, fp) != NULL)
    {
        tmp  = atoll(buffer);
        myarray[tmp] = 1;
    }

    int totalcount = 0;
    long long x;
    long long y;
    for(long long t = -10000; t <= 10000; t++)
    {
        unordered_map <long long, int>::iterator itr;
        for(itr = myarray.begin(); itr != myarray.end(); itr++)
        {
            x = itr->first;
            y = t - x;

            if( x == y)
                continue;

            if(myarray.find(y) != myarray.end())
            {
                totalcount++;
                break;
            }
        }
        printf("DONE PROCESSING FOR %lld count = %d\n", t, totalcount);
    }
    printf("Total count = %d\n", totalcount);
    fclose(fp);
}
