#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int MOD = 1e9 + 7;
// int dp[1000005][101];

// int solve(vector<int>& coins, int x, int i){
//     if(x == 0){
//         return 1;
//     }

//     if(i >= (int)coins.size() || x < 0){
//         return 0;
//     }

//     if(dp[x][i] != -1){
//         return dp[x][i];
//     }

//     int take = solve(coins, x - coins[i], i);
//     int not_take = solve(coins, x, i + 1);

//     return dp[x][i] = (take + not_take) % MOD;
// }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,x;
    cin>>n>>x;

    vector<int>nums(n);
    for(int i = 0; i < n; ++i){
        cin>>nums[i];
    }

    vector<vector<int>>dp(n + 1, vector<int>(x + 1, 0));
    for(int i = 0; i <= n; i++){
        dp[i][0] = 1;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= x; j++){
            dp[i][j] = dp[i - 1][j];

            if(j - nums[i - 1] >= 0){
                dp[i][j] = (dp[i][j] + dp[i][j - nums[i - 1]]) % MOD;
            }
        }
    }

    cout<<dp[n][x]<<endl;
    return 0;
}