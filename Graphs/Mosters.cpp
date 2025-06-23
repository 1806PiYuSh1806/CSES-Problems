#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<char>>grid(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>grid[i][j];
        }
    }

    int row_start = -1;
    int col_start = -1;

    vector<int>dirR = {0, -1, 0, 1};
    vector<int>dirC = {-1, 0, 1, 0};
    vector<char>dir = {'L', 'U', 'R', 'D'};

    queue<pair<int, int>>mosters;
    vector<vector<int>>time(n, vector<int>(m, INT_MAX));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'M'){
                mosters.push({i, j});
                time[i][j] = 0;
            }
            else if(grid[i][j] == 'A'){
                row_start = i;
                col_start = j;
            }
        }
    }

    while(!mosters.empty()){
        int currR = mosters.front().first;
        int currC = mosters.front().second;
        mosters.pop();

        for(int i = 0; i < 4; i++){
            int newR = currR + dirR[i];
            int newC = currC + dirC[i];

            if(newR >= 0 && newC >= 0 && newR < n && newC < m && time[newR][newC] == INT_MAX && grid[newR][newC] != '#'){
                time[newR][newC] = time[currR][currC] + 1;
                mosters.push({newR, newC});
            }
        }
    }

    vector<vector<char>>parent(n, vector<char>(m, ' '));
    vector<vector<int>>playerTime(n, vector<int>(m, INT_MAX));
    playerTime[row_start][col_start] = 0;
    queue<pair<int, int>>player;
    player.push({row_start, col_start});
    int row_end = -1;
    int col_end = -1;

    while(!player.empty()){
        int currR = player.front().first;
        int currC = player.front().second;
        player.pop();

        if(currR == 0 || currC == 0 || currR == n - 1 || currC == m - 1){
            row_end = currR;
            col_end = currC;
            break;
        }

        for(int i = 0; i < 4; i++){
            int newR = currR + dirR[i];
            int newC = currC + dirC[i];

            if(newR >= 0 && newC >= 0 && newR < n && newC < m && playerTime[newR][newC] == INT_MAX && grid[newR][newC] != '#'){
                if(playerTime[currR][currC] + 1 < time[newR][newC]){
                    playerTime[newR][newC] = playerTime[currR][currC] + 1;
                    player.push({newR, newC});
                    parent[newR][newC] = dir[i];
                }
            }
        }
    }

    if(row_end == -1 || col_end == -1){
        cout<<"NO"<<endl;
        return 0;
    }

    cout<<"YES"<<endl;
    cout<<playerTime[row_end][col_end]<<endl;

    string path;
    int r = row_end;
    int c = col_end;

    while(r != row_start || c != col_start){
        path += parent[r][c];

        if(parent[r][c] == 'L'){
            c++;
        }
        else if(parent[r][c] == 'R'){
            c--;
        }
        else if(parent[r][c] == 'U'){
            r++;
        }
        else{
            r--;
        }
    }
    reverse(path.begin(), path.end());
    cout<<path<<endl;
    return 0;
}