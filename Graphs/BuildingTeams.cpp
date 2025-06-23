#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>     

using namespace std;

bool dfs_color(vector<vector<int>>& adj, vector<int>& colors, int u, int color) {
    colors[u] = color; 

    for (int v : adj[u]) {
        if (colors[v] == -1) { 
            if (!dfs_color(adj, colors, v, 1 - color)) {
                return false; 
            }
        } else if (colors[v] == color) { 
            return false; 
        }
    }
    return true; 
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

    vector<int>colors(n + 1, -1);
    bool possible = true;

    for (int i = 1; i <= n; ++i) {
        if (colors[i] == -1) {
            
            if (!dfs_color(adj, colors, i, 0)) {
                possible = false; 
                break;            
            }
        }
    }

    if(!possible){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    
    for(int i = 1; i <= n; i++){
        
        cout<<(colors[i] == 0 ? "1" : "2")<<" ";
    }
    cout<<endl;

    return 0;
}