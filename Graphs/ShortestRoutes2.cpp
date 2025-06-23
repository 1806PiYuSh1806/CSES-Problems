#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m, q;
    cin>>n>>m>>q;

    vector<vector<long long>>dist(n, vector<long long>(n, LLONG_MAX));
    vector<vector<pair<int, long long>>>adj(n);
    for(int i = 0; i < m; i++){
        int u, v;
        long long wt;
        cin>>u>>v>>wt;
        adj[u - 1].push_back({v - 1, wt});
        adj[v - 1].push_back({u - 1, wt});
        dist[u - 1][v - 1] = min(dist[u - 1][v - 1], wt);
        dist[v - 1][u - 1] = min(dist[u - 1][v - 1], wt);
    }

    vector<vector<int>>queries(q, vector<int>(2));
    for(int i = 0; i < q; i++){
        cin>>queries[i][0];
        cin>>queries[i][1];
    }

    for(int i = 0; i < n; i++){
        dist[i][i] = 0;
    }

    for(int via = 0; via < n; via++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(dist[i][via] != LLONG_MAX && dist[via][j] != LLONG_MAX){
                    dist[i][j] = min(dist[i][j], 1LL * dist[i][via] + dist[via][j]);
                }
            }
        }
    }

    vector<int>res(q);
    for(auto& q : queries){
        int u = q[0] - 1;
        int v = q[1] - 1;

        if(dist[u][v] == LLONG_MAX){
            cout<<"-1"<<endl;
        }
        else{
            cout<<dist[u][v]<<endl;
        }
    }

    return 0;
}