#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>     

using namespace std;

bool dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<int>& parent, int i, int v){
    visited[i] = true;
    parent[i] = v;

    for(auto& x : adj[i]){
        if(x == v){
            continue;
        }

        if(visited[x] == true){
            vector<int>cycle;
            cycle.push_back(x);
            int curr = i;

            while(curr != x){
                if (curr == -1) return false;
                cycle.push_back(curr);
                curr = parent[curr];
            }

            cycle.push_back(x);
            reverse(cycle.begin(), cycle.end());
            cout<<cycle.size()<<endl;
            for(auto& x : cycle){
                cout<<x<<" ";
            }
            cout<<endl;
            return true;
        }

        if(dfs(adj, visited, parent, x, i)){
            return true;
        }
    }

    return false;
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 

    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n + 1); 
    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;

        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
    vector<bool>visited(n + 1, false);
    vector<int>parent(n + 1, -1);
    bool found = false;

    for(int i = 1; i <= n; i++){
        if(visited[i] == false && dfs(adj, visited, parent, i, 0)){
            found = true;
            return 0;
        }
    }

    if(!found){
        cout<<"IMPOSSIBLE"<<endl;
    }

    return 0;
}