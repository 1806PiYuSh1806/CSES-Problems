#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int MOD = 1e9 + 7;

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

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>>pq;
    vector<long long>dist(n, LLONG_MAX);
    vector<int>routes(n, 0);
    vector<int>min_flights(n, INT_MAX);
    vector<int>max_flights(n, 0);

    dist[0] = 0;
    routes[0] = 1;
    min_flights[0] = 0;
    max_flights[0] = 0;
    pq.push({0, 0});

    while(!pq.empty()){
        long long currCost = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if(currCost > dist[curr]){
            continue;
        }

        for(auto& p : adj[curr]){
            long long weight = p.second;
            int next = p.first;

            long long newCost = currCost + weight;

            if(dist[next] > newCost){
                dist[next] = newCost;
                routes[next] = routes[curr];
                min_flights[next] = min_flights[curr] + 1;
                max_flights[next] = max_flights[curr] + 1;
                pq.push({newCost, next});
            }
            else if(dist[next] == newCost){
                routes[next] = (routes[next] + routes[curr]) % MOD;
                min_flights[next] = min(min_flights[next], min_flights[curr] + 1);
                max_flights[next] = max(max_flights[next], max_flights[curr] + 1);
            }
        }
    }

    cout<<dist[n - 1]<<" "<<routes[n - 1]<<" "<<min_flights[n - 1]<<" "<<max_flights[n - 1]<<endl;
    return 0;
}