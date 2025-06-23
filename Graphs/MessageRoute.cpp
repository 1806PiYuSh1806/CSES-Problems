#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>edges(m, vector<int>(2));
    for(int i = 0; i < m; i++){
        cin>>edges[i][0];
        cin>>edges[i][1];
    }

    vector<vector<int>>adj(n + 1);
    for(auto& edge : edges){
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    queue<int>q;
    vector<int>parent(n + 1, -1);
    parent[1] = 1;
    bool found = false;
    q.push(1);

    while(!q.empty()){
        int top = q.front();
        q.pop();

        if(top == n){
            found = true;
            break;
        }

        for(auto& x : adj[top]){
            if(parent[x] == -1){
                q.push(x);
                parent[x] = top;
            }
        }
    }

    if(!found){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    vector<int>res;
    int x = n;
    while(x != 1){
        res.push_back(x);
        x = parent[x];
    }
    res.push_back(1);

    reverse(res.begin(), res.end());
    cout<<res.size()<<endl;

    for(auto& r : res){
        cout<<r<<" ";
    }
    cout<<endl;
    return 0;
}