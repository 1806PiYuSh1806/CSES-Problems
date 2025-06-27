#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <stack>
#include <map>
#include <list>
#include <functional>

using namespace std;

int dy[] = {2, 1, -1, -2, -2, -1, 1, 2};
int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
vector<vector<int>>board(8, vector<int>(8, 0));

bool isValid(int x, int y){
    if(x >= 0 && x < 8 && y >= 0 && y < 8 && board[x][y] == 0){
        return true;
    }
    return false;
}

int degree(int x, int y){
    int total = 0;
    for(int i = 0; i < 8; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if(isValid(new_x, new_y)){
            total++;
        }
    }

    return total;
}

bool solve(int x, int y, int moveCount){
    if(moveCount == 64){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return true;
    }

    vector<pair<int, pair<int, int>>>nextMoves;
    for(int i = 0; i < 8; i++){
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        if(isValid(new_x, new_y)){
            nextMoves.push_back({degree(new_x, new_y), {new_x, new_y}});
        }
    }

    sort(nextMoves.begin(), nextMoves.end());

    for(auto& move : nextMoves){
        int new_x = move.second.first;
        int new_y = move.second.second;

        board[new_x][new_y] = moveCount + 1;

        if(solve(new_x, new_y, moveCount + 1)){
            return true;
        }

        board[new_x][new_y] = 0;
    }

    return false;
}

int main(){
    int x, y;
    cin>>x>>y;

    board[y - 1][x - 1] = 1;
    solve(y - 1, x - 1, 1);
    return 0;
}