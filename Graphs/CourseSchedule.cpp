#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    vector<int>indegree(n, 0);

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        adj[u - 1].push_back(v - 1);
        indegree[v - 1]++;
    }

    queue<int>q;
    vector<int>res;
    for(int i = 0; i < n; i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int top = q.front();
        q.pop();
        res.push_back(top + 1);

        for(auto& x : adj[top]){
            indegree[x]--;
            if(indegree[x] == 0){
                q.push(x);
            }
        }
    }

    if(res.size() != n){
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }

    for(auto& x : res){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}