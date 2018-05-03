/*The file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second column is the head (recall the graph is directed, and the edges are directed from the first column vertex to the second column vertex). So for example, the 11th row looks liks : "2 47646". This just means that the vertex with label 2 has an outgoing edge to the vertex with label 47646
 *
 * Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), and to run this algorithm on the given graph.
 *
 * Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, separated by commas (avoid any spaces). So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100" (without the quotes). If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, then your answer should be "400,300,100,0,0" (without the quotes). (Note also that your answer should not have any spaces in it.)
 *
 * WARNING: This is the most challenging programming assignment of the course. Because of the size of the graph you may have to manage memory carefully. The best way to do this depends on your programming language and environment, and we strongly suggest that you exchange tips for doing this on the discussion forums.
 *
 * Answer:
 *
 * 211
 * 313
 * 459
 * 968
 * 434821
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

#define MAX_VERTICES 875714
//#define MAX_VERTICES 9

struct node
{
    int vertex;
    int vertex_ft;
    bool isExplored_rev; 
    bool isExplored;
    list < node* > * forward;
    list < node* > *backward;
};

node  *nodeArray[MAX_VERTICES + 1];
    
int MAX_COUNT[MAX_VERTICES + 1];

int ft[MAX_VERTICES + 1];
int gFT = 0;

void DFS_Reverse(int s)
{
    node *vtxPtr = nodeArray[s];

    vtxPtr->isExplored_rev = true;

    if(vtxPtr->backward)
    {
        list <node*>::iterator iter;
        for(iter = vtxPtr->backward->begin(); iter != vtxPtr->backward->end(); iter++)
        {
            node *adjPtr = *iter;
            if(!adjPtr->isExplored_rev)
                DFS_Reverse(adjPtr->vertex);
        }
    }
    gFT++;
    ft[gFT] = s;
    vtxPtr->vertex_ft = gFT;
}
int SCC_Count = 0;

void DFS(int s)
{
    node *vtxPtr = nodeArray[ft[s]];

    vtxPtr->isExplored = true;
    SCC_Count++;

    if(vtxPtr->forward)
    {
        list <node*>::iterator iter;
        for(iter = vtxPtr->forward->begin(); iter != vtxPtr->forward->end(); iter++)
        {
            node *adjPtr = *iter;
            if(!adjPtr->isExplored)
                DFS(adjPtr->vertex_ft);
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp = fopen(argv[1], "r");

    char buffer[1024];

    char *tmp;
    int vertex1;
    node *vtxPtr1;

    int vertex2;
    node *vtxPtr2;
    while(fgets(buffer, 1024, fp) != NULL)
    {
        tmp = strtok(buffer, " \t\n");
        vertex1 = atoi(tmp);

        tmp = strtok(NULL, " \t\n");
        vertex2 = atoi(tmp);

        if(nodeArray[vertex1] == NULL)
        {
            vtxPtr1 = new node;
            vtxPtr1->vertex = vertex1;
            vtxPtr1->forward = NULL;
            vtxPtr1->isExplored_rev = false;
            vtxPtr1->isExplored = false;
            vtxPtr1->backward = NULL;
            nodeArray[vertex1] = vtxPtr1;
        }
        else
        {
            vtxPtr1 = nodeArray[vertex1];
        }

        if(nodeArray[vertex2] == NULL)
        {
            vtxPtr2 = new node;
            vtxPtr2->vertex = vertex2;
            vtxPtr2->isExplored_rev = false;
            vtxPtr2->isExplored = false;
            vtxPtr2->forward = NULL;
            vtxPtr2->backward = NULL;
            nodeArray[vertex2] = vtxPtr2;
        }
        else
        {
            vtxPtr2 = nodeArray[vertex2];
        }

        if( vtxPtr1->forward == NULL )
        {
            vtxPtr1->forward = new list<node *>();
        }
        vtxPtr1->forward->push_back(vtxPtr2);
        if(vtxPtr2->backward == NULL)
        {
            vtxPtr2->backward = new list <node *> ();
        }
        vtxPtr2->backward->push_back(vtxPtr1);
    }

    for(int j = MAX_VERTICES ; j >= 1; j--)
    {
        node * vtxPtr = nodeArray[j];

        if(vtxPtr && !vtxPtr->isExplored_rev)
        {
            DFS_Reverse(j);
        }
    }

    //for (int j = 1; j <= MAX_VERTICES; j++)
      //  printf("FT[%d] = %d\n", j, nodeArray[j]->vertex_ft);


    for(int j = MAX_VERTICES ; j >= 1; j--)
    {
        node * vtxPtr = nodeArray[ft[j]];

        if(vtxPtr && !vtxPtr->isExplored)
        {
            DFS(j);
            MAX_COUNT[SCC_Count] = 1;
            SCC_Count = 0;
        }
    }

    fclose(fp);

    for(int j =1; j <= MAX_VERTICES; j++)
    {
        if(MAX_COUNT[j])
        {
        }
    }

}
