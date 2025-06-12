#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

// int dp[5001][5001];

// int solve(vector<int>& nums1, vector<int>& nums2, int i, int j){
//     if(i >= nums1.size() || j >= nums2.size()){
//         return 0;
//     }

//     if(dp[i][j] != -1){
//         return dp[i][j];
//     }

//     if(nums1[i] == nums2[j]){
//         return dp[i][j] = 1 + solve(nums1, nums2, i + 1, j + 1);
//     }

//     int first = solve(nums1, nums2, i + 1, j);
//     int second = solve(nums1, nums2, i, j + 1);

//     return dp[i][j] = max(first, second);
// }

int main(){
    int n,m;
    cin>>n>>m;

    vector<int>nums1(n);
    vector<int>nums2(m);

    for(int i = 0; i < n; i++){
        cin>>nums1[i];
    }

    for(int i = 0; i < m; i++){
        cin>>nums2[i];
    }

    vector<vector<int>>dp(n + 1, vector<int>(m + 1, INT_MAX));
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            if(i == 0 || j == 0){
                dp[i][j] = 0;
                continue;
            }

            if(nums1[i - 1] == nums2[j - 1]){
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    vector<int>lcs;
    int i = n, j = m;

    while(i > 0 && j > 0){
        if(nums1[i - 1] == nums2[j - 1]){
            lcs.push_back(nums1[i - 1]);
            i--;
            j--;
        }
        else if(dp[i - 1][j] > dp[i][j - 1]){
            i--;
        }
        else{
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout<<dp[n][m]<<endl;
    for(auto& x : lcs){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}