#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

int dp[5001][5001];

int solve(string& str1, string& str2, int i, int j){
    if(i >= (int)str1.size()){
        return str2.size() - j;
    }

    if(j >= (int)str2.size()){
        return str1.size() - i;
    }

    if(dp[i][j] != -1){
        return dp[i][j];
    }

    if(str1[i] == str2[j]){
        return dp[i][j] = solve(str1, str2, i + 1, j + 1);
    }

    int insert = 1 + solve(str1, str2, i, j + 1);
    int del = 1 + solve(str1, str2, i + 1, j);
    int change = 1 + solve(str1, str2, i + 1, j + 1);

    return dp[i][j] = min({insert, del, change});
}

int main(){
    string str1, str2;
    cin>>str1;
    cin>>str2;

    memset(dp, -1, sizeof(dp));
    int count = solve(str1, str2, 0, 0);

    cout<<count<<endl;
    return 0;
}