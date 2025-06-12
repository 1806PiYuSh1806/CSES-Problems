#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int MOD = 1e9 + 7;
int M;
int dp[100005][101];

int solve(vector<int>& nums, int i, int prevVal){
    if(i == (int)nums.size()){
        return 1;
    }

    if(dp[i][prevVal] != -1){
        return dp[i][prevVal];
    }

    int ways = 0;
    if(nums[i] != 0){
        if(abs(nums[i] - prevVal) <= 1){
            return dp[i][prevVal] = solve(nums, i + 1, nums[i]);
        }
        return 0;
    }

    for(int diff = -1; diff <= 1; diff++){
        int nextVal = prevVal + diff;
        if(nextVal >= 1 && nextVal <= M){
            ways = (ways + solve(nums, i + 1, nextVal)) % MOD;
        }
    }

    return dp[i][prevVal] = ways;
}

int main(){
    int n, m;
    cin>>n>>m;
    M = m;

    vector<int>nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    memset(dp, -1, sizeof(dp));
    if(nums[0] != 0){
        cout<<solve(nums, 1, nums[0])<<endl;
    }
    else{
        int count = 0;
        for(int i = 1; i <= M; i++){
            count = (count + solve(nums, 1, i)) % MOD;
        }
        cout<<count<<endl;
    }
    return 0;
}