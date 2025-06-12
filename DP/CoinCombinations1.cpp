#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int MOD = 1e9 + 7;
// int dp[1000006];

// int solve(vector<int>& coins, int x){
//     if(x == 0){
//         return 1;
//     }

//     if(dp[x] != -1){
//         return dp[x];
//     }

//     int res = 0;
//     for(auto& coin : coins){
//         if(x - coin >= 0){
//             res = (res + solve(coins, x - coin)) % MOD;
//         }
//     }

//     return dp[x] = res;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; ++i) cin >> coins[i];

    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int i = 1; i <= x; ++i) {
        for (int c : coins) {
            if (i >= c) {
                dp[i] += dp[i - c];
                if (dp[i] >= MOD) dp[i] -= MOD;
            }
        }
    }

    cout << dp[x] << '\n';
    return 0;
}