#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

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

    vector<int>parent(n, -1);
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

    for(auto& x : topo_order){
        if(x != 0 && dp[x] == 0){
            continue;
        }

        for(auto& v : adj[x]){
            if(dp[x] + 1 > dp[v]){
                dp[v] = dp[x] + 1;
                parent[v] = x;
            }
        }
    }

    if(dp[n - 1] == 0){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    cout<<dp[n - 1]<<endl;
    vector<int>res;

    int curr = n - 1;
    while(curr != -1){
        res.push_back(curr);
        curr = parent[curr];
    }

    reverse(res.begin(), res.end());
    
    for(auto& x : res){
        cout<<x + 1<<" ";
    }
    cout<<endl;
    return 0;
}