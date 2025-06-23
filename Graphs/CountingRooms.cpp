#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>
#include <unordered_set>
#include <queue>
using namespace std;

int delX[4] = {0, -1, 0, 1};
int delY[4] = {-1, 0, 1, 0};

void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j){
    queue<pair<int, int>>q;
    q.push({i, j});
    visited[i][j] = true;

    while(!q.empty()){
        auto top = q.front();
        q.pop();

        for(int k = 0; k < 4; k++){
            int newX = top.first + delX[k];
            int newY = top.second + delY[k];

            if(newX >= 0 && newY >= 0 && newX < grid.size() && newY < grid[0].size() && visited[newX][newY] == false && grid[newX][newY] == '.'){
                q.push({newX, newY});
                visited[newX][newY] = true;
            }
        }
    }
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<char>>grid(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>grid[i][j];
        }
    }

    int count = 0;
    vector<vector<bool>>visited(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == '.' && visited[i][j] == false){
                bfs(grid, visited, i, j);
                count++;
            }
        }
    }

    cout<<count<<endl;
    return 0;
}