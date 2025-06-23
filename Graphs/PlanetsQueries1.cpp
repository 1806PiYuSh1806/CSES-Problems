#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>    
#include <climits>  

const int MAX_LOG = 30; 

int jump[200005][MAX_LOG + 1]; 

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    for(int i = 0; i < n; ++i){
        int u;
        std::cin >> u;
        jump[i][0] = u - 1;
    }

    for(int j = 1; j <= MAX_LOG; ++j){
        for(int i = 0; i < n; ++i){
            jump[i][j] = jump[jump[i][j - 1]][j - 1];
        }
    }

    for(int qi = 0; qi < q; ++qi){
        int curr;
        int k;   
        
        std::cin >> curr >> k;
        curr--;

        for(int j = MAX_LOG; j >= 0; --j){
            if((k >> j) & 1){
                curr = jump[curr][j];
            }
        }
        std::cout << curr + 1 << "\n";
    }

    return 0;
}