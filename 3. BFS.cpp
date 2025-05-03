#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void bfs(int start, vector<vector<int> >& adjList){

    int vertices = adjList.size();
    vector<bool> visited(vertices, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS traversal ";

    while (!q.empty()){
        int current = q.front();
        q.pop();
        cout<<current <<" ";

        #pragma omp parallel for
        for(int i = 0; i<adjList[current].size(); i++){
            int next = adjList[current][i];
            
            if (!visited[next]){
                #pragma omp critical
                {
                    if(!visited[next]){
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
    }
    cout<<endl;
}

int main() {
    int vertices, edges;
    
    cout<<"enter the number of vertices ";
    cin>> vertices;
    cout<< "enter the number of edges ";
    cin >>edges;

    vector<vector<int>> adjList(vertices);

    cout<< "enter the edges (u v)"<<endl;
    for (int i = 0; i < edges; ++i){
        int u, v;
        cin >>u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int start;
    cout<< "which is the starting vertex: ";
    cin >>start;

    bfs(start, adjList);
}