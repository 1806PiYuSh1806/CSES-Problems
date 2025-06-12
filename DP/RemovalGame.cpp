#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <unordered_set>
using namespace std;

long long dp[5001][5001];

long long solve(vector<int>& nums, int i, int j){
    if(i > j){
        return 0;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    long long take_i = 1LL * nums[i] + min(solve(nums, i + 2, j), solve(nums, i + 1, j - 1));
    long long take_j = 1LL * nums[j] + min(solve(nums, i, j - 2), solve(nums, i + 1, j - 1));

    return dp[i][j] = max(take_i, take_j);
}

int main(){
    int n;
    cin>>n;

    vector<int>nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    // memset(dp, -1, sizeof(dp));
    // cout<<solve(nums, 0, nums.size() - 1)<<endl;

    vector<vector<long long>>dp(n, vector<long long>(n, 0));
    for(int i = 0; i < n; i++){
        dp[i][i] = nums[i];
    }

    for(int len = 2; len <= n; len++){
        for(int i = 0; i < n - len + 1; i++){
            int j = i + len - 1;

            long long take_i = nums[i];
            if(i + 2 <= j){
                take_i += min(dp[i + 1][j - 1], dp[i + 2][j]);
            }
            else if(i + 1 <= j){
                take_i += dp[i + 1][j - 1];
            }

            long long take_j = nums[j];
            if(i <= j - 2){
                take_j += min(dp[i + 1][j - 1], dp[i][j - 2]);
            }
            else if(i <= j - 1){
                take_j += dp[i + 1][j - 1];
            }

            dp[i][j] = max(take_i, take_j);
        }
    }
    cout<<dp[0][n - 1]<<endl;
    return 0;
}