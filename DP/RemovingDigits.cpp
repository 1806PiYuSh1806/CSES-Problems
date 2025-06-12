#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

// int dp[1000005];

// int solve(int n){
//     if(n == 0){
//         return 0;
//     }

//     if(dp[n] != -1){
//         return dp[n];
//     }

//     int res = INT_MAX;
//     int temp = n;
//     while(temp > 0){
//         int rem = temp % 10;
//         temp /= 10;
//         if(rem == 0){
//             continue;
//         }
//         res = min(res, 1 + solve(n - rem));
//     }

//     return dp[n] = res;
// }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;

    vector<int>dp(n + 1, INT_MAX);
    dp[0] = 0;
    
    for(int i = 1; i <= n; i++){
        int temp = i;
        while(temp > 0){
            int rem = temp % 10;
            temp /= 10;
            if(rem == 0){
                continue;
            }

            dp[i] = min(dp[i], 1 + dp[i - rem]);
        }
    }

    cout<<dp[n]<<endl;
    return 0;
}