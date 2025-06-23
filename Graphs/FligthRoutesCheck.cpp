#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>
#include <stack>

using namespace std;

void topo_dfs(vector<vector<int>>& adj, stack<int>& st, int i, vector<bool>& visited){
    visited[i] = true;

    for(auto& x : adj[i]){
        if(!visited[x]){
            topo_dfs(adj, st, x, visited);
        }
    }

    st.push(i);
}

void dfs(vector<vector<int>>& adj, int i, vector<bool>& visited){
    visited[i] = true;

    for(auto& x : adj[i]){
        if(!visited[x]){
            dfs(adj, x, visited);
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
            topo_dfs(adj, st, i, visited);
        }
    }

    visited.assign(n, false);
    int count = 0;
    int prev = -1;
    int second_prev = -1;

    while(!st.empty()){
        int top = st.top();
        st.pop();

        if(!visited[top]){
            if(prev == - 1){
                prev = top;
            }
            else if(second_prev == -1){
                second_prev = top;
            }
            dfs(reversed_adj, top, visited);
            count++;
        }
    }

    if(count == 1){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
        cout<<second_prev + 1<<" "<<prev + 1<<endl;
    }

    return 0;
}