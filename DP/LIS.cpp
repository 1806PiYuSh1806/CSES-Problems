#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <unordered_set>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;

    vector<long long>nums(n);
    for(int i = 0; i < n; i++){
        cin>>nums[i];
    }

    vector<int>dp;
    for(int i = 0; i < n; i++){
        auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
        if(it == dp.end()){
            dp.push_back(nums[i]);
        }
        else{
            *it = nums[i];
        }
    }

    cout<<dp.size()<<endl;
    return 0;
}