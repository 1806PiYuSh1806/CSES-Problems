#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int main(){
    int n;
    cin>>n;

    vector<vector<char>>grid(n, vector<char>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin>>grid[i][j];
        }
    }

    // vector<vector<string>>dp(n, vector<string>(n, ""));
    // dp[0][0] += grid[0][0];

    // for(int i = 1; i < n; i++){
    //     dp[0][i] = dp[0][i - 1] + grid[0][i];
    // }

    // for(int i = 1; i < n; i++){
    //     dp[i][0] = dp[i - 1][0] + grid[i][0];
    // }

    // for(int i = 1; i < n; i++){
    //     for(int j = 1; j < n; j++){
    //         if(dp[i - 1][j] < dp[i][j - 1]){
    //             dp[i][j] = dp[i - 1][j] + grid[i][j];
    //         }
    //         else{
    //             dp[i][j] = dp[i][j - 1] + grid[i][j];
    //         }
    //     }
    // }

    // cout<<dp[n - 1][n - 1]<<endl;

    vector<string>prev(n);
    vector<string>curr(n);

    prev[0] = string(1, grid[0][0]);
    for(int i = 1; i < n; i++){
        prev[i] = prev[i - 1] + grid[0][i];
    }

    for(int i = 1; i < n; i++){
        curr[0] = prev[0] + grid[i][0];
        for(int j = 1; j < n; j++){
            string top = prev[j] + grid[i][j];
            string left = curr[j - 1] + grid[i][j];
            curr[j] = min(top, left);
        }
        swap(curr, prev);
    }

    cout<<prev[n - 1]<<endl;
    return 0;
}