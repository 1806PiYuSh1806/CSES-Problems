#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<pair<int, long long>>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin>>u>>v>>w;
        adj[u - 1].push_back({v - 1, w});
    }

    vector<long long>dist(n, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;

    pq.push({0, 0});
    dist[0] = 0;

    while(!pq.empty()){
        long long currWeight = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if(currWeight > dist[curr]){
            continue;
        }

        for(auto& p : adj[curr]){
            int x = p.first;
            long long weight = p.second;

            if(dist[x] > dist[curr] + weight){
                dist[x] = 1LL * dist[curr] + weight;
                pq.push({dist[x], x});
            }
        }
    }

    for(auto& x : dist){
        cout<<x<<" ";
    }
    cout<<endl;
    return 0;
}