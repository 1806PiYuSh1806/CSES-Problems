#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int cycle_start = -1;
int cycle_end = -1;

bool dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& inRecStack, vector<int>& parent, int i){
    visited[i] = true;
    inRecStack[i] = true;

    for(auto& x : adj[i]){
        if(visited[x] == false && dfs(adj, visited, inRecStack, parent, x)){
            parent[x] = i;
            return true;
        }

        if(inRecStack[x] == true){
            cycle_start = x;
            cycle_end = i;
            return true;
        }
    }

    inRecStack[i] = false;
    return false;
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;

        adj[u - 1].push_back(v - 1);
    }

    vector<bool>visited(n, false);
    vector<bool>inRecStack(n, false);
    vector<int>parent(n, -1);

    bool found = false;
    for(int i = 0; i < n; i++){
        if(visited[i] == false && dfs(adj, visited, inRecStack, parent, i)){
            found = true;
            break;
        }
    }

    if(!found){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    vector<int>cycle;
    int curr = cycle_end;
    while(curr != cycle_start){
        cycle.push_back(curr);
        curr = parent[curr];
    }
    cycle.push_back(cycle_start);
    reverse(cycle.begin(), cycle.end());

    cout<<cycle.size() + 1<<endl;
    for(auto& x : cycle){
        cout<<x + 1<<" ";
    }
    cout<<cycle[0] + 1<<endl;

    return 0;
}