#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;


class Graph{
    public:
        // vector<vector<int>> graph;
        // vector<bool> visited;
        // int vertices = 0;
        // int edges = 0;

        int vertices = 6;
        int edges = 5;
        vector<vector<int>> graph = {{1},{0,2,3},{1,4,5},{1,4},{2,3},{2}};   // simple graph
        // vector<vector<int>> graph = {                                     //comlpex graph
        //     {1, 2, 3},      // Node 0 is connected to 1, 2, 3
        //     {0, 4, 5},      // Node 1 is connected to 0, 4, 5
        //     {0, 6, 7},      // Node 2 is connected to 0, 6, 7
        //     {0, 8, 9},      // Node 3 is connected to 0, 8, 9
        //     {1, 10, 11},    // Node 4 is connected to 1, 10, 11
        //     {1, 6, 12},     // Node 5 is connected to 1, 6, 12
        //     {2, 5, 13},     // Node 6 is connected to 2, 5, 13
        //     {2, 14},        // Node 7 is connected to 2, 14
        //     {3, 10, 12},    // Node 8 is connected to 3, 10, 12
        //     {3, 11, 13},    // Node 9 is connected to 3, 11, 13
        //     {4, 8, 14},     // Node 10 is connected to 4, 8, 14
        //     {4, 9, 12},     // Node 11 is connected to 4, 9, 12
        //     {5, 8, 11, 14}, // Node 12 is connected to 5, 8, 11, 14
        //     {6, 9},         // Node 13 is connected to 6, 9
        //     {7, 10, 12}     // Node 14 is connected to 7, 10, 12
        // };
        
        vector<bool> visited;

        // Graph(){
        //     cout << "Enter number of nodes: ";
        //     cin >> vertices;
        //     cout << "Enter number of edges: ";
        //     cin >> edges;
        //     graph.assign(vertices,vector<int>());
        //     for(int i = 0 ; i < edges;i++){
        //         int a,b;
        //         cout << "Enter adjacent nodes: ";
        //         cin >> a >> b;
        //         addEdge(a,b);
        //     }
        // }
        void addEdge(int a, int b){
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        void printGraph(){
            for(int i = 0; i < vertices; i++){
                cout << i << " -> ";
                for(auto j = graph[i].begin(); j != graph[i].end();j++){
                    cout << *j << " ";
                }
                cout << endl;
            }
        }

        void initialize_visited(){
            visited.assign(vertices,false);
        }

        void dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                s.pop();
                for(auto j = graph[current].begin(); j != graph[current].end();j++){
                    if(visited[*j] == false){
                        s.push(*j);
                        visited[*j] = true;
                    }
                }
                
            }
        }

        void parallel_dfs(int i){
            stack<int> s;
            s.push(i);
            visited[i] = true;

            while(s.empty() != true){
                int current = s.top();
                cout << current << " ";
                #pragma omp critical
                    s.pop();
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                            {
                                s.push(*j);
                                visited[*j] = true;
                            }
                        }
                    }
                
            }
        }

        void bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                int current = q.front();
                q.pop();
                cout << current << " ";
                for(auto j = graph[current].begin(); j != graph[current].end();j++){
                    if(visited[*j] == false){
                        q.push(*j);
                        visited[*j] = true;
                    }
                }
            }
        }

        void parallel_bfs(int i){
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(q.empty() != true){
                
                    int current = q.front();
                    cout << current << " ";
                    #pragma omp critical
                        q.pop();
                    
                #pragma omp parallel for
                    for(auto j = graph[current].begin(); j != graph[current].end();j++){
                        if(visited[*j] == false){
                            #pragma omp critical
                                q.push(*j);
                                visited[*j] = true;
                        }
                    }
                
            }
        }
};

int main(int argc, char const *argv[])
{
    Graph g;
    cout << "Adjacency List:\n";
    g.printGraph();
    g.initialize_visited();
    
    
    cout << "Depth First Search: \n";
    auto startD = chrono::high_resolution_clock::now();
    g.dfs(0);
    cout << endl;
    auto endD = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(endD - startD).count() << " microseconds" << endl;
    
    
    cout << "Parallel Depth First Search: \n";
    g.initialize_visited();
    auto startPD = chrono::high_resolution_clock::now();
    g.parallel_dfs(0);
    cout << endl;
    auto endPD = chrono::high_resolution_clock::now();
    cout << "Time taken: "<< chrono::duration_cast<chrono::microseconds>(endPD - startPD).count() << " microseconds" << endl;
    cout << "Speed Factor (DFS): "
     << (double)chrono::duration_cast<chrono::microseconds>(endD - startD).count() /
        chrono::duration_cast<chrono::microseconds>(endPD - startPD).count()
     << endl
     << endl;
    
    
    auto startB = chrono::high_resolution_clock::now();
    cout << "Breadth First Search: \n";
    g.initialize_visited();
    g.bfs(0);
    cout << endl;
    auto endB = chrono::high_resolution_clock::now();
    cout << "Time taken: "<< chrono::duration_cast<chrono::microseconds>(endB - startB).count() << " microseconds" << endl;
    
    
    auto startPB = chrono::high_resolution_clock::now();
    cout << "Parallel Breadth First Search: \n";
    g.initialize_visited();
    g.parallel_bfs(0);
    cout << endl;
    auto endPB = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(endPB - startPB).count() << " microseconds" << endl;
    
    cout << "Speed Factor (BFS): "
     << (double)chrono::duration_cast<chrono::microseconds>(endB - startB).count() /
        chrono::duration_cast<chrono::microseconds>(endPB - startPB).count()
     << endl;

    return 0;
}
