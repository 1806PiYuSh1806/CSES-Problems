#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <unordered_set>
using namespace std;

int MOD = 1e9 + 7;

unordered_map<string, int>dp;

int solve(int n, int i, int sum1, int sum2){
    if(i > n){
        return (sum1 == sum2) ? 1 : 0;
    }

    string key = to_string(sum1) + "#" + to_string(sum2) + "#" + to_string(i);
    if(dp.count(key)){
        return dp[key];
    }

    int take1 = (solve(n, i + 1, sum1 + i, sum2)) % MOD;
    int take2 = (solve(n, i + 1, sum1, sum2 + i)) % MOD;

    return dp[key] = (take1 + take2) % MOD;
}

int main(){
    int n;
    cin>>n;

    cout<<solve(n, 1, 0, 0) / 2<<endl;
    return 0;
}