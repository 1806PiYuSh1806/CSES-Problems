#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>
#include <stack>

using namespace std;

void topo_fill(vector<vector<int>>& adj, stack<int>& st, vector<bool>& visited, int i){
    visited[i] = true;

    for(auto& x : adj[i]){
        if(!visited[x]){
            topo_fill(adj, st, visited, x);
        }
    }

    st.push(i);
}

void dfs(vector<vector<int>>& adj, vector<int>& kingdoms, int i, int& count){
    kingdoms[i] = count;

    for(auto& x : adj[i]){
        if(kingdoms[x] == -1){
            dfs(adj, kingdoms, x, count);
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    vector<vector<int>>reversed_adj(n);

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;

        adj[u - 1].push_back(v - 1);
        reversed_adj[v - 1].push_back(u - 1);
    }

    stack<int>st;
    vector<bool>visited(n, false);
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            topo_fill(adj, st, visited, i);
        }
    }

    vector<int>kingdoms(n, -1);
    int count = 1;

    while(!st.empty()){
        int curr = st.top();
        st.pop();

        if(kingdoms[curr] == -1){
            dfs(reversed_adj, kingdoms, curr, count);
            count++;
        }
    }

    cout<<count - 1<<endl;
    for(auto& x : kingdoms){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}