#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<pair<int, long long>>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        long long wt;
        cin>>u>>v;
        cin>>wt;

        adj[u - 1].push_back({v - 1, wt});
        adj[v - 1].push_back({u - 1, wt});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;
    pq.push({0, 0});
    vector<bool>inMST(n, false);

    long long res = 0;

    while(!pq.empty()){
        long long currWeight = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if(inMST[curr]){
            continue;
        }

        res += currWeight;
        inMST[curr] = true;

        for(auto& p : adj[curr]){
            long long weight = p.second;
            int next = p.first;

            if(inMST[next] == false){
                pq.push({weight, next});
            }
        }
    }

    for(int i = 0; i < n; i++){
        if(inMST[i] == false){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }
    }

    cout<<res<<endl;
    return 0;
}