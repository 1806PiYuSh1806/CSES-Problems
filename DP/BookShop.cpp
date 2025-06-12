#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

// int dp[1005][100005];

// int solve(vector<int>& price, vector<int>& pages, int x, int i){
//     if(i == price.size()){
//         return 0;
//     }

//     if(dp[i][x] != -1){
//         return dp[i][x];
//     }

//     int take = 0;
//     if(price[i] <= x){
//         take = pages[i] + solve(price, pages, x - price[i], i + 1);
//     }
//     int not_take = solve(price, pages, x, i + 1);

//     return dp[i][x] = max(take, not_take);
// }

int main(){
    int n,x;
    cin>>n>>x;

    vector<int>price(n);
    vector<int>pages(n);

    for(int i = 0; i < n; ++i){
        cin>>price[i];
    }

    for(int i = 0; i < n; ++i){
        cin>>pages[i];
    }

    vector<int>dp(x + 1, 0);

    for(int i = 0; i < n; i++){
        for(int j = x; j >= price[i]; j--){
            dp[j] = max(dp[j], pages[i] + dp[j - price[i]]);
        }
    }

    cout<<dp[x]<<endl;

    return 0;
}