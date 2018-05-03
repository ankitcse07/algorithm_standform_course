/*
The file contains the adjacency list representation of a simple undirected graph. There are 200 vertices labeled 1 to 200. The first column in the file represents the vertex label, and the particular row (other entries except the first column) tells all the vertices that the vertex is adjacent to. So for example, the 6th row looks like : "6th1555652120......". This just means that the vertex with label 6 is adjacent to (i.e., shares an edge with) the vertices with labels 155,56,52,120,......,etc

Your task is to code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph to compute the min cut. (HINT: Note that you'll have to figure out an implementation of edge contractions. Initially, you might want to do this naively, creating a new graph from the old every time there's an edge contraction. But you should also think about more efficient implementations.) (WARNING: As per the video lectures, please make sure to run the algorithm many times with different random seeds, and remember the smallest cut that you ever find.) Write your numeric answer in the space provided. So e.g., if your answer is 5, just type 5 in the space provided
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct edge
{
    int vertex1;
    int vertex2;
};

unsigned long long int min_cut = 0xefffffffffffffffULL;


void kager(int adjacenyList[201][201])
{
    for(int i = 1; i <= 198; i++)
    {
        int vertex1;
        int vertex2; 

        while(1)
        {
            vertex1 = random()%201;
            if(vertex1 == 0)
                vertex1++;
            vertex2 = random()%201;
            if(vertex2 == 0)
                vertex2++;

            if(vertex1 == vertex2)
                continue;

            if(adjacenyList[vertex1][vertex2])
                break;
        }
        //printf("Random Vertex = %d %d\n", vertex1, vertex2);

        adjacenyList[vertex2][vertex1] = 0;
        for(int j = 1; j <=200; j++)
        {
            if(adjacenyList[vertex1][j])
            {
                if(adjacenyList[j][vertex1])
                {
                    adjacenyList[j][vertex2] += adjacenyList[j][vertex1];
                    adjacenyList[j][vertex1] = 0;

                    if( j != vertex2 )
                    {
                        adjacenyList[vertex2][j] += adjacenyList[vertex1][j];
                    }
                }
                adjacenyList[vertex1][j] = 0;
            }
        }
    }


    for(int j = 1; j <= 200; j++)
    {
        for(int k = 1; k <= 200; k++)
        {
            if(adjacenyList[j][k])
            {
                if(min_cut > adjacenyList[j][k])
                    min_cut = adjacenyList[j][k];

            }
        }
    }
}

int main(int argc, char *argv[])
{
    int adjacenyList[201][201];
    vector < edge *> myedges;
    map < string, int > myedgeMap;
    

    bzero(adjacenyList, sizeof(adjacenyList));

    FILE *fp = fopen(argv[1], "r");


    char buffer[1024];

    int i = 0;
    int j = 0;
    char *tmp;
    char *prev;
    char tmpStr[32];
    string mystr;
    
    
    while(fgets(buffer, 1024, fp) != NULL)
    {
        tmp = strtok(buffer, " \t\n");

        i = atoi(tmp);
        while((tmp = strtok(NULL, " \t\n")) != NULL)
        {
            j = atoi(tmp); 
            adjacenyList[i][j] += 1;
        }
    }
    fclose(fp);

    for(int i = 1; i < 20000; i++)
    {
        srandom(i);
    
        int adjacenyList1[201][201];
        for(int j = 1; j <=200; j++)
            for(int k = 1; k <=200; k++)
                adjacenyList1[j][k] = adjacenyList[j][k];
        
        kager(adjacenyList1);
    }
    printf("min_cut = %lld\n", min_cut);
    return 0;
}

