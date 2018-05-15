#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
#include <assert.h>

using namespace std;

struct edgeHead
{
    int vertex;
    int length;
};


int main(int argc, char *argv[])
{
    int adjacenyList[201][201];

    bzero(adjacenyList, sizeof(adjacenyList));

    FILE *fp = fopen(argv[1], "r");


    char buffer[4096];

    int i = 0;
    int j = 0;
    char *tmp;
    
    int length;

    int vminusx[201];
    int shortest_path[201];
    
    while(fgets(buffer, 4096, fp) != NULL)
    {
        tmp = strtok(buffer, " \t\n");

        i = atoi(tmp);
        vminusx[i] = 1;
        shortest_path[i] = 1000000;
        while((tmp = strtok(NULL, " \t\n")) != NULL)
        {
            j = atoi(tmp); 
            while(*tmp != ',')
                tmp++;
            tmp++;
            adjacenyList[i][j] = atoi(tmp);
        }
    }
    fclose(fp);

    int index = 1;
    vminusx[1] = 0;
    shortest_path[1] = 0;

    list <int> v_list;
    v_list.push_back(1);

    while(index <  200)
    {
        list <int>::iterator itr;

        int find_dij_greedy_sum = 1000000;
        int vertex_w = -1;
        for(int i = 1; i <=200; i++)
        {
            if(vminusx[i])
            {
                for(itr = v_list.begin(); itr != v_list.end(); itr++)
                {
                    assert(i != *itr);
                    if(adjacenyList[*itr][i])
                    {
                        if((shortest_path[*itr] + adjacenyList[*itr][i]) < find_dij_greedy_sum)
                        {
                            find_dij_greedy_sum = shortest_path[*itr] + adjacenyList[*itr][i];
                            vertex_w = i;
                        }
                    }
                }
            }
        }
        /*
         * This will also work
        for(itr = v_list.begin(); itr != v_list.end(); itr++)
        {
            for(int i = 1; i <= 200; i++)
            {
                if(i != *itr)
                {
                    if(adjacenyList[*itr][i] && vminusx[i])
                    {
                        if((shortest_path[*itr] + adjacenyList[*itr][i]) < find_dij_greedy_sum)
                        {
                            find_dij_greedy_sum = shortest_path[*itr] + adjacenyList[*itr][i];
                            vertex_w = i;
                        }

                    }
                }
            }
        }
        */
        vminusx[vertex_w] = 0;
        v_list.push_back(vertex_w);
        shortest_path[vertex_w] = find_dij_greedy_sum;
        index++;
    }
    for(int i = 1; i <= 200; i++)
    {
        printf("SHORTEST PATH 1 --> %d = %d\n", i, shortest_path[i]);
    }
    return 0;
}

