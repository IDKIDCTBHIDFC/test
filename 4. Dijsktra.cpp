#include <iostream>
#include<vector>
#include<cstdlib>
#include<omp.h>
using namespace std;
#define V 15

int minDistance(int dist[], bool visited[])
{
	int min = 1000000, min_index;

	for (int v = 0; v < V; v++)
		if (visited[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void printSolution(int dist[], int n)
{
	cout<<"Vertex Distance from Source\n";
	for (int i = 0; i < V; i++)
		cout<<i<<" : "<< dist[i]<<endl;
}

void printgraph(vector<vector<int> > graph, int n)
{
	cout<<"Graph is: \n";
	for (int i = 0; i < V; i++){
		for (int j = 0; j < V; j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}
}

void dijkstra(vector<vector<int> > graph, int src)
{
	int dist[V];

	bool visited[V];
	
	#pragma omp parallel for
	for (int i = 0; i < V; i++)
		dist[i] = 1000000, visited[i] = false;
	#pragma omp barrier
	
	dist[src] = 0;
	
	int v;
	#pragma omp parallel for private (v)
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance(dist, visited);

		visited[u] = true;

		for (v = 0; v < V; v++)
			if (!visited[v] && graph[u][v]
				&& dist[u] != 1000000
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}
	#pragma omp barrier
	printSolution(dist, V);
}

vector<vector<int> > generate(int n, int max) {
    vector<vector<int> > matrix(n, vector<int>(n, 0));
    srand(3);
    int j;
	#pragma omp parallel for private (j)
    for (int i = 0; i < n; ++i) {
        for (j = i; j < n; ++j) {
            if (i == j) continue;

            int edge = rand() % 2; // 0 or 1, edge exists or no
            if (edge) {
                int weight = 1 + rand() % max;
                matrix[i][j] = weight;
                matrix[j][i] = weight;
            }
        }
    }

    return matrix;
}
int main()
{
	vector<vector<int> > graph = generate(V,10);
	printgraph(graph,V);
	dijkstra(graph, 0);

	return 0;
}

