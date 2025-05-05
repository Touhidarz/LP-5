#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<omp.h>

using namespace std;

void seqDFS(vector<vector<int>> &adj, int n, int start){
    vector<bool> visited(n, false);
    stack<int> st;
    
    st.push(start);
    
    while(! st.empty()){
        int node = st.top();
        st.pop();
        
        for(auto i : adj[node]){
            if(! visited[i]){
                visited[i] = true;
                st.push(i);
            }
        }
    }
}

void parDFS(vector<vector<int>> &adj, int n, int start){
    vector<bool> visited(n, false);
    stack<int> st;
    
    st.push(start);
    
    while(! st.empty()){
        int node;
        
        #pragma omp critical
        {
            if(! st.empty()){
                node = st.top();
                st.pop();
            }
        }     
        
        for(auto i : adj[node]){
            #pragma omp critical 
            {
                if(! visited[i]){
                    visited[i] = true;
                    st.push(i);
                }
            }
        }
    }
}

void seqBFS(vector<vector<int>> &adj, int n, int start){
    vector<bool> visited(n, false);
    queue<int> qu;
    
    qu.push(start);
    
    while(! qu.empty()){
        int node = qu.front();
        qu.pop();
        
        for(auto i : adj[node]){
            if(! visited[i]){
                visited[i] = true;
                qu.push(i);
            }
        }
    }
}

void parBFS(vector<vector<int>> &adj, int n, int start){
    vector<bool> visited(n, false);
    queue<int> qu;
    
    qu.push(start);
    
    while(! qu.empty()){
        int node;
        
        #pragma omp critical
        {
            if(! qu.empty()){
                node = qu.front();
                qu.pop();
            }
        }
       
        for(auto i : adj[node]){
            #pragma omp critical 
            {
                if(! visited[i]){
                    visited[i] = true;
                    qu.push(i);
                }
            }  
        }
    }
}

void generateRandom(vector<vector<int>> &adj, int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}


int main(){
    int size;
    cout<<"Enter Size : ";
    cin>>size;
    vector<vector<int>> adj(size);
    
    for(int i=0; i<size; i++){
        generateRandom(adj, rand()%size, rand()%size);
    }
    
    double seqBfsStart, seqBfsEnd, parBfsStart, parBfsEnd, seqBfsTime, parBfsTime;
    double seqDfsStart, seqDfsEnd, parDfsStart, parDfsEnd, seqDfsTime, parDfsTime;
    
    seqDfsStart = omp_get_wtime();
    seqDFS(adj, size, 0);
    seqDfsEnd = omp_get_wtime();
    seqDfsTime = (seqDfsEnd - seqDfsStart);
    cout<<"Sequential DFS Time : "<<seqDfsTime<<endl<<endl;
    
    parDfsStart = omp_get_wtime();
    parDFS(adj, size, 0);
    parDfsEnd = omp_get_wtime();
    parDfsTime = (parDfsEnd - parDfsStart);
    cout<<"Parallel DFS Time : "<<parDfsTime<<endl<<endl;

    cout<<"DFS Speedup : "<<(seqDfsTime/parDfsTime)<<endl<<endl;
    
    seqBfsStart = omp_get_wtime();
    seqBFS(adj, size, 0);
    seqBfsEnd = omp_get_wtime();
    seqBfsTime = (seqBfsEnd - seqBfsStart);
    cout<<"Sequential BFS Time : "<<seqBfsTime<<endl<<endl;
    
    parBfsStart = omp_get_wtime();
    parBFS(adj, size, 0);
    parBfsEnd = omp_get_wtime();
    parBfsTime = (parBfsEnd - parBfsStart);
    cout<<"Prallel BFS Time : "<<parBfsTime<<endl<<endl;

    cout<<"BFS Speedup : "<<(seqBfsTime/parBfsTime)<<endl<<endl;
    
}