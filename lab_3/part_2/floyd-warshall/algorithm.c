// Алгоритм Флойда-Уоршелла
#include<stdio.h>
  
// количество вершин
#define V 4
  
// расстояние между не смежными вершинами
#define INF 99999
  
// печать матрицы с наименьшими длинами кратчайших путей
void printSolution(int dist[][V]);
  
// функция алгоритма Флойда-Уоршелла
void floydWarshall (int graph[][V])
{
    int dist[V][V], i, j, k;
  
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
  
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
  
    printSolution(dist);
}
  
void printSolution(int dist[][V])
{
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}
  
// главный метод 
int main()
{
    // граф с 4 вершинами
    int graph[V][V] = { {0,   5,  INF, 10},
                        {INF, 0,   3, INF},
                        {INF, INF, 0,   1},
                        {INF, INF, INF, 0}
                      };
    printSolution(graph);
  
    // напечатать обработанный граф
    floydWarshall(graph);
    return 0;
}
