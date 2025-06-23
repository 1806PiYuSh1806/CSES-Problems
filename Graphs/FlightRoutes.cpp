#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m, k;
    cin>>n>>m>>k;

    vector<vector<pair<int, int>>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        long long wt;
        cin>>u>>v;
        cin>>wt;
        adj[u - 1].push_back({v - 1, wt});
    }

    vector<priority_queue<long long>>dist(n);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;

    dist[0].push(0);
    pq.push({0, 0});

    while(!pq.empty()){
        long long currWeight = pq.top().first;
        int currNode = pq.top().second;
        pq.pop();

        if(currWeight > dist[currNode].top()){
            continue;
        }

        for(auto& p : adj[currNode]){
            int nextNode = p.first;
            long long weight = p.second;

            if(dist[nextNode].size() < k){
                dist[nextNode].push(currWeight + weight);
                pq.push({currWeight + weight, nextNode});
            }
            else if(dist[nextNode].top() > currWeight + weight){
                dist[nextNode].pop();
                dist[nextNode].push(currWeight + weight);
                pq.push({currWeight + weight, nextNode});
            }
        }
    }

    vector<long long>res;
    while(!dist[n - 1].empty()){
        res.push_back(dist[n - 1].top());
        dist[n - 1].pop();
    }

    reverse(res.begin(), res.end());
    for(int i = 0; i < k; i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return 0;
}