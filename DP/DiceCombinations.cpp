#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int MOD = 1e9 + 7;
unordered_map<int, int>memo;

int solve(int n){
    if(n == 0){
        return 1;
    }

    if(n < 0){
        return 0;
    }
    
    if(memo.find(n) != memo.end()){
        return memo[n];
    }

    memo[n] = 0;
    int sum = 0;
    for(int i = 1; i <= 6; i++){
        sum = (sum + solve(n - i)) % MOD;
    }

    return memo[n] = sum;
}

int main() {
    int n;
    cin>>n;

    cout<<solve(n)<<endl;
    return 0;
}