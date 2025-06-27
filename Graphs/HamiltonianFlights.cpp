#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <stack>
#include <map>
#include <list>
#include <functional>

using namespace std;

int MOD = 1e9 + 7;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        adj[u - 1].push_back(v - 1);
    }

    vector<vector<int>>dp((1 << n), vector<int>(n, 0));
    dp[1][0] = 1;

    for(int mask = 0; mask < (1 << n); mask++){
        for(int u = 0; u < n; u++){
            if(dp[mask][u] > 0 && (mask & (1 << u))){
                for(auto& v : adj[u]){
                    if(!(mask & (1 << v))){
                        int new_mask = mask | (1 << v);
                        dp[new_mask][v] = (dp[new_mask][v] + dp[mask][u]) % MOD;
                    }
                }
            }
        }
    }

    cout<<dp[(1 << n) - 1][n - 1]<<endl;
    return 0;
}