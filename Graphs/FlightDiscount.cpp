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
        int u, v;
        long long wt;
        cin>>u>>v;
        cin>>wt;
        adj[u - 1].push_back({v - 1, wt});
    }

    priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>>pq;
    vector<vector<long long>>dist(n, vector<long long>(2, LLONG_MAX));
    pq.push({0, {0, 0}});
    dist[0][0] = 0;

    while(!pq.empty()){
        long long currWeight = pq.top().first;
        int currNode = pq.top().second.first;
        int state = pq.top().second.second;
        pq.pop();

        if(dist[currNode][state] < currWeight){
            continue;
        }
        
        for(auto& p : adj[currNode]){
            int nextNode = p.first;
            long long weight = p.second;

            if(state == 0){
                if(dist[nextNode][0] > currWeight + weight){
                    dist[nextNode][0] = currWeight + weight;
                    pq.push({dist[nextNode][0], {nextNode, state}});
                }

                if(dist[nextNode][1] > currWeight + (weight / 2)){
                    dist[nextNode][1] = currWeight + (weight / 2);
                    pq.push({dist[nextNode][1], {nextNode, 1}});
                }
            }
            else{
                if(dist[nextNode][1] > currWeight + weight){
                    dist[nextNode][1] = currWeight + weight;
                    pq.push({dist[nextNode][1], {nextNode, state}});
                }
            }
        }
    }

    cout<<dist[n - 1][1]<<endl;
    return 0;
}