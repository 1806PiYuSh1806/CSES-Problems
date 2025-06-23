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

void dfs(vector<vector<int>>& adj, vector<int>& SCCid, vector<long long>& totalCoins, int i, int& count, vector<long long>& coins){
    SCCid[i] = count;
    totalCoins[count] += 1LL * coins[i];

    for(auto& x : adj[i]){
        if(SCCid[x] == -1){
            dfs(adj, SCCid, totalCoins, x, count, coins);
        }
    }
}

long long solve(vector<vector<int>>& adj, vector<long long>& totalCoins, vector<long long>& dp, int i){
    if(dp[i] != -1){
        return dp[i];
    }

    long long res = 0;
    for(auto& x : adj[i]){
        res = max(res, solve(adj, totalCoins, dp, x));
    }

    return dp[i] = totalCoins[i] + res;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    vector<vector<int>>reverse_adj(n);

    vector<long long>coins(n);
    for(int i = 0; i < n; i++){
        cin>>coins[i];
    }

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        adj[u - 1].push_back(v - 1);
        reverse_adj[v - 1].push_back(u - 1);
    }

    stack<int>st;
    vector<bool>visited(n, false);

    for(int i = 0; i < n; i++){
        if(visited[i] == false){
            topo_fill(adj, st, visited, i);
        }
    }

    vector<int>SCCid(n, -1);
    vector<long long>totalCoins;
    int count = 0;

    while(!st.empty()){
        int top = st.top();
        st.pop();

        if(SCCid[top] == -1){
            totalCoins.push_back(0);
            dfs(reverse_adj, SCCid, totalCoins, top, count, coins);
            count++;
        }
    }

    vector<vector<int>>SCCGraph(count);
    vector<vector<bool>>isPresentInSCC(count, vector<bool>(count, false));

    for(int i = 0; i < n; i++){
        for(auto& x : adj[i]){
            if(SCCid[i] != SCCid[x] && isPresentInSCC[SCCid[i]][SCCid[x]] == false){
                SCCGraph[SCCid[i]].push_back(SCCid[x]);
                isPresentInSCC[SCCid[i]][SCCid[x]] = true;
            }
        }
    }

    vector<long long>dp(count, -1);

    long long res = 0;
    for(int i = 0; i < count; i++){
        res = max(res, solve(SCCGraph, totalCoins, dp, i));
    }

    cout<<res<<endl;
    return 0;
}
