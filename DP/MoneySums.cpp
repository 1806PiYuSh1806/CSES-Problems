#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <unordered_set>
using namespace std;

unordered_set<long long>st;

void solve(vector<int>& nums, int i, int currSum){
    if(i >= nums.size()){
        if(currSum != 0){
            st.insert(currSum);
        }
        return;
    }

    solve(nums, i + 1, currSum + nums[i]);
    solve(nums, i + 1, currSum);
}

int main(){
    int n;
    cin>>n;

    vector<int>nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }
    // sort(nums.begin(), nums.end());
    // solve(nums, 0, 0);

    // cout<<st.size()<<endl;
    // for(auto& x : st){
    //     cout<<x<<" ";
    // }
    // cout<<endl;

    vector<bool>dp(100000 + 1, false);
    dp[0] = true;

    for(auto& x : nums){
        for(int i = 100000; i >= x; i--){
            if(dp[i - x]){
                dp[i] = true;
            }
        }
    }

    vector<int>res;
    for(int i = 1; i <= 100000; i++){
        if(dp[i]){
            res.push_back(i);
        }
    }

    cout<<res.size()<<endl;
    for(auto& x : res){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}