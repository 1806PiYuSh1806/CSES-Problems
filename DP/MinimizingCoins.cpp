#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

// int dp[1000005][101];

// int solve(vector<int>& coins, int x, int i){
//     if(x == 0){
//         return 0;
//     }

//     if(i >= (int)coins.size() || x < 0){
//         return INT_MAX - 1;
//     }

//     if(dp[x][i] != -1){
//         return dp[x][i];
//     }

//     int take = 1 + solve(coins, x - coins[i], i);
//     int notTake = solve(coins, x, i + 1);

//     return dp[x][i] = min(take, notTake);
// }

int main(){
    int n, x;
    cin>>n>>x;

    vector<int>coins(n);
    for(int i = 0; i < n; i++){
        cin>>coins[i];
    }

    vector<int>dp(x + 1, INT_MAX);
    dp[0] = 0;

    for(auto& coin : coins){
        for(int i = coin; i <= x; i++){
            if(dp[i - coin] != INT_MAX){
                dp[i] = min(dp[i - coin] + 1, dp[i]);
            }
        }
    }

    if(dp[x] == INT_MAX){
        cout << -1 << endl;
    } else {
        cout << dp[x] << endl;
    }
    return 0;
}