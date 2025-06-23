#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>

using namespace std;

vector<int>parent;
vector<int>dsu_rank;
vector<int>dsu_size;

int maxSize;
int components;

int find(int u){
    if(u == parent[u]){
        return u;
    }

    return parent[u] = find(parent[u]);
}

void Union(int u, int v){
    int parent_u = find(u);
    int parent_v = find(v);

    if(parent_u == parent_v){
        return;
    }

    if(dsu_rank[parent_u] > dsu_rank[parent_v]){
        parent[parent_v] = parent_u;
        dsu_size[parent_u] += dsu_size[parent_v];
        maxSize = max(maxSize, dsu_size[parent_u]);
    }
    else if(dsu_rank[parent_u] < dsu_rank[parent_v]){
        parent[parent_u] = parent_v;
        dsu_size[parent_v] += dsu_size[parent_u];
        maxSize = max(maxSize, dsu_size[parent_v]);
    }
    else{
        parent[parent_u] = parent_v;
        dsu_rank[parent_v]++;
        dsu_size[parent_v] += dsu_size[parent_u];
        maxSize = max(maxSize, dsu_size[parent_v]);
    }
    components--;
}

int totalComponents(){
    return components;
}

int getSize(){
    return maxSize;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    parent.resize(n);
    dsu_rank.resize(n, 0);
    dsu_size.resize(n, 1);
    components = n;
    maxSize = 1;

    for(int i = 0; i < n; i++){
        parent[i] = i;
    }

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        Union(u - 1, v - 1);
        cout<<totalComponents()<<" ";
        cout<<getSize()<<endl;
    }

    return 0;
}