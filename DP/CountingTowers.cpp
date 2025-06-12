// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <climits>
// #include <cstring>
// using namespace std;

// int MOD = 1e9 + 7;

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin>>t;

//     while(t--){
//         int n;
//         cin>>n;

//         vector<vector<int>> dp(n + 1, vector<int>(2, 0));
//         dp[n - 1][0] = 1;
//         dp[n - 1][1] = 1;

//         for(int i = n - 2; i >= 0; i--){
//             dp[i][0] = ((2LL * dp[i + 1][0]) % MOD + dp[i + 1][1]) % MOD;
//             dp[i][1] = ((4LL * dp[i + 1][1]) % MOD + dp[i + 1][0]) % MOD;
//         }

//         cout<<(dp[0][0] + dp[0][1]) % MOD<<endl;
//     }

//     return 0;
// }

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> dp0(MAXN), dp1(MAXN);
    dp0[MAXN - 1] = 1;
    dp1[MAXN - 1] = 1;

    for (int i = MAXN - 2; i >= 0; i--) {
        dp0[i] = ((2LL * dp0[i + 1]) % MOD + dp1[i + 1]) % MOD;
        dp1[i] = ((4LL * dp1[i + 1]) % MOD + dp0[i + 1]) % MOD;
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << (dp0[MAXN - n] + dp1[MAXN - n]) % MOD << '\n';
    }

    return 0;
}
