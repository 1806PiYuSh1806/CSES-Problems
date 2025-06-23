#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void bfs(vector<vector<int>>& adj, vector<bool>& visited, int i){
    queue<int>q;
    q.push(i);
    visited[i] = true;

    while(!q.empty()){
        int top = q.front();
        q.pop();

        for(auto& x : adj[top]){
            if(!visited[x]){
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>edges(m, vector<int>(2));
    for(int i = 0; i < m; i++){
        cin>>edges[i][0];
        cin>>edges[i][1];
    }

    vector<vector<int>>adj(n + 1);
    for(auto& edge : edges){
        int u = edge[0];
        int v = edge[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int>components;
    vector<bool>visited(n + 1, false);
    int count = 0;
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            count++;
            components.push_back(i);
            bfs(adj, visited, i);
        }
    }

    cout<<count - 1<<endl;
    for(int i = 0; i < components.size() - 1; i++){
        cout<<components[i]<<" "<<components[i + 1]<<endl;
    }

    return 0;
}