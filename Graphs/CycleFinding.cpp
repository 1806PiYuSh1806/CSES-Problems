#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

int main(){
    int n, m;
    cin>>n>>m;

    vector<tuple<int, int, long long>>edges(m);
    for(int i = 0; i < m; i++){
        int u, v;
        long long wt;
        cin>>u>>v;
        cin>>wt;

        edges[i] = {u - 1, v - 1, wt};
    }

    vector<long long>dist(n, 0);
    vector<int>parent(n, -1);

    int lastNode = -1;

    for(int i = 0; i < n; i++){

        for(auto& edge : edges){
            int u = get<0>(edge);
            int v = get<1>(edge);
            long long wt = get<2>(edge);
            if(dist[v] > dist[u] + wt){
                dist[v] = dist[u] + wt;
                parent[v] = u;

                if(i == n - 1){
                    lastNode = v;
                }
            }
        }
    }

    if(lastNode == -1){
        cout<<"NO"<<endl;
        return 0;
    }

    cout<<"YES"<<endl;
    int curr = lastNode;
    for(int i = 0; i < n; i++){
        curr = parent[curr];
    }

    vector<int>cycle;
    int start = curr;
    cycle.push_back(curr);
    curr = parent[curr];

    while(curr != start){
        cycle.push_back(curr);
        curr = parent[curr];
    }

    reverse(cycle.begin(), cycle.end());
    for(auto& x : cycle){
        cout<<x + 1<<" ";
    }
    cout<<cycle[0] + 1<<endl;
    return 0;
}