#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>
#include <stack>

using namespace std;

void dfs(vector<vector<pair<int, int>>>& adj, vector<bool>& visited, int i){
    visited[i] = true;

    for(auto& x : adj[i]){
        if(!visited[x.first]){
            dfs(adj, visited, x.first);
        }
    }
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<pair<int, int>>>adj(n);
    vector<int>degree(n, 0);

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        adj[u - 1].push_back({v - 1, i});
        adj[v - 1].push_back({u - 1, i});
        degree[u - 1]++;
        degree[v - 1]++;
    }

    for(int i = 0; i < n; i++){
        if(degree[i] % 2 != 0){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }

    vector<bool>visited(n, false);
    dfs(adj, visited, 0);

    for(int i = 0; i < n; i++){
        if(degree[i] > 0 && visited[i] == false){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }

    if(m == 0){
        cout<<"1"<<endl;
        return 0;
    }

    vector<int>path;
    stack<int>st;
    vector<int>nextEdgeIdx(m, 0);
    vector<bool>visited2(m, false);

    st.push(0);
    while (!st.empty())
    {
        int u = st.top();
        bool nextFound = false;

        while(nextEdgeIdx[u] < adj[u].size()){
            int v = adj[u][nextEdgeIdx[u]].first;
            int id = adj[u][nextEdgeIdx[u]].second;
            nextEdgeIdx[u]++;

            if(!visited2[id]){
                visited2[id] = true;
                st.push(v);
                nextFound = true;;
                break;
            }
        }

        if(!nextFound){
            path.push_back(u);
            st.pop();
        }
    }
    

    if(path.size() != m + 1){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    if(path[0] != 0 && path[m] != 0){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    reverse(path.begin(), path.end());
    for(auto& x : path){
        cout<<x + 1<<" ";
    }
    cout<<endl;
    return 0;
}