#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int MOD = 1e9 + 7;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    vector<int>indegree(n, 0);

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;

        adj[u - 1].push_back(v - 1);
        indegree[v - 1]++;
    }

    queue<int>q;
    for(int i = 0; i < n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    vector<int>topo_order;
    while(!q.empty()){
        int top = q.front();
        q.pop();
        topo_order.push_back(top);

        for(auto& x : adj[top]){
            indegree[x]--;
            if(indegree[x] == 0){
                q.push(x);
            }
        }
    }

    vector<int>dp(n, 0);
    dp[0] = 1;

    for(auto& u : topo_order){
        if(u != 0 && dp[u] == 0){
            continue;
        }

        for(auto& v : adj[u]){
            dp[v] = (dp[u] + dp[v]) % MOD;
        }
    }

    cout<<dp[n - 1]<<endl;
    return 0;
}