#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};
char dir_char[4] = {'U', 'D', 'L', 'R'};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<char>>grid(n, vector<char>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>grid[i][j];
        }
    }

    int start_row, start_col, end_row, end_col;
    queue<pair<int, int>>q;
    vector<vector<char>>parent(n, vector<char>(m, ' '));
    vector<vector<int>>dist(n, vector<int>(m, -1));

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'A'){
                start_row = i;
                start_col = j;
                q.push({i, j});
                dist[i][j] = 0;
            }
            else if(grid[i][j] == 'B'){
                end_row = i;
                end_col = j;
            }
        }
    }

    bool found = false;
    while(!q.empty()){
        int currR = q.front().first;
        int currC = q.front().second;
        q.pop();

        if(currR == end_row && currC == end_col){
            found = true;
            break;
        }

        for(int i = 0; i < 4; i++){
            int newR = currR + dr[i];
            int newC = currC + dc[i];

        
            if(newR >= 0 && newR < n && newC >= 0 && newC < m &&
               grid[newR][newC] != '#' && dist[newR][newC] == -1){
                
                q.push({newR, newC});
                dist[newR][newC] = dist[currR][currC] + 1;
                parent[newR][newC] = dir_char[i];
            }
        }
    }

    if(!found){
        cout<<"NO"<<endl;
        return 0;
    }

    cout<<"YES"<<endl;
    cout<<dist[end_row][end_col]<<endl;

    string res = "";
    int r = end_row;
    int c = end_col;

    while(r != start_row || c != start_col){
        char d = parent[r][c];
        res += d;
        if(d == 'U'){
            r++;
        }
        else if(d == 'D'){
            r--;
        }
        else if(d == 'L'){
            c++;
        }
        else{
            c--;
        }
    }

    reverse(res.begin(), res.end());
    cout<<res<<endl;
    return 0;
}