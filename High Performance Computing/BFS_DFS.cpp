#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <omp.h>

using namespace std;

class Graph {
public:
    int vertices;
    vector<vector<int>> adjList;
    vector<bool> visited;

    // Constructor to initialize graph with vertices and edges
    Graph(int v, int e) : vertices(v), adjList(v), visited(v, false) {
        generate_random_graph(e);
    }

    // Generate random graph edges
    void generate_random_graph(int edges) {
        srand(time(0));
        for (int i = 0; i < edges; ++i) {
            int u = rand() % vertices;
            int v = rand() % vertices;
            if (u != v) {
                adjList[u].push_back(v);
                adjList[v].push_back(u);  // Undirected graph
            }
        }
    }

    // Reset visited array
    void reset_visited() {
        fill(visited.begin(), visited.end(), false);
    }

    // Sequential DFS
    void dfs(int start) {
        stack<int> s;
        s.push(start);
        visited[start] = true;

        while (!s.empty()) {
            int node = s.top();
            s.pop();
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    s.push(neighbor);
                }
            }
        }
    }

    // Parallel DFS using OpenMP
    void parallel_dfs(int start) {
        visited[start] = true;
        #pragma omp parallel
        {
            stack<int> local_stack;
            local_stack.push(start);

            while (!local_stack.empty()) {
                int node;
                #pragma omp critical
                {
                    if (!local_stack.empty()) {
                        node = local_stack.top();
                        local_stack.pop();
                    } else {
                        node = -1; // No more nodes to process
                    }
                }

                if (node == -1) continue;

                for (int neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        #pragma omp critical
                        {
                            local_stack.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    // Sequential BFS
    void bfs(int start) {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    // Parallel BFS using OpenMP
    void parallel_bfs(int start) {
        visited[start] = true;
        queue<int> q;
        q.push(start);

        #pragma omp parallel
        {
            queue<int> local_queue;
            while (!q.empty()) {
                int node;
                #pragma omp critical
                {
                    if (!q.empty()) {
                        node = q.front();
                        q.pop();
                    } else {
                        node = -1; // No more nodes to process
                    }
                }

                if (node == -1) continue;

                for (int neighbor : adjList[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        #pragma omp critical
                        {
                            local_queue.push(neighbor);
                        }
                    }
                }

                #pragma omp critical
                {
                    while (!local_queue.empty()) {
                        q.push(local_queue.front());
                        local_queue.pop();
                    }
                }
            }
        }
    }
};

int main() {
    int V = 100000, E = 2000000;  // Graph with 10,000 vertices and 1,000,000 edges
    Graph g(V, E);

    // Timing variables
    double time_seq_dfs, time_par_dfs, time_seq_bfs, time_par_bfs;

    // Sequential DFS timing
    g.reset_visited();
    double start_time = omp_get_wtime();
    g.dfs(0);
    double end_time = omp_get_wtime();
    time_seq_dfs = end_time - start_time;
    cout << "DFS Sequential Time: " << time_seq_dfs << " sec\n";

    // Parallel DFS timing
    g.reset_visited();
    start_time = omp_get_wtime();
    g.parallel_dfs(0);
    end_time = omp_get_wtime();
    time_par_dfs = end_time - start_time;
    cout << "DFS Parallel Time: " << time_par_dfs << " sec\n";

    // Sequential BFS timing
    g.reset_visited();
    start_time = omp_get_wtime();
    g.bfs(0);
    end_time = omp_get_wtime();
    time_seq_bfs = end_time - start_time;
    cout << "BFS Sequential Time: " << time_seq_bfs << " sec\n";

    // Parallel BFS timing
    g.reset_visited();
    start_time = omp_get_wtime();
    g.parallel_bfs(0);
    end_time = omp_get_wtime();
    time_par_bfs = end_time - start_time;
    cout << "BFS Parallel Time: " << time_par_bfs << " sec\n";

    // Speedup calculations
    cout << "\nDFS Speedup: " << (time_par_dfs > 0 ? time_seq_dfs / time_par_dfs : 0) << endl;
    cout << "BFS Speedup: " << (time_par_bfs > 0 ? time_seq_bfs / time_par_bfs : 0) << endl;

    return 0;
}
