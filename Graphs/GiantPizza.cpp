#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue>
#include <climits>
#include <stack>

using namespace std;

int getIndex(int val, char sign){
    if(sign == '+'){
        return 2 * (val - 1);
    }

    return 2 * (val - 1) + 1;
}

int negateNode(int val){
    if(val % 2 == 0){
        return val + 1;
    }

    return val - 1;
}

void topo_fill(vector<vector<int>>& adj, stack<int>& st, vector<bool>& visited, int i){
    visited[i] = true;

    for(auto& x : adj[i]){
        if(!visited[x]){
            topo_fill(adj, st, visited, x);
        }
    }

    st.push(i);
}

void dfs(vector<vector<int>>& adj, vector<int>& SCCid, int i, int& count){
    SCCid[i] = count;

    for(auto& x : adj[i]){
        if(SCCid[x] == -1){
            dfs(adj, SCCid, x, count);
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(2 * m);
    vector<vector<int>>reverse_adj(2 * m);

    for(int i = 0; i < n; i++){
        char sign1, sign2;
        int val1, val2;

        cin>>sign1>>val1>>sign2>>val2;

        int idx1 = getIndex(val1, sign1);
        int idx2 = getIndex(val2, sign2);

        adj[negateNode(idx1)].push_back(idx2);
        adj[negateNode(idx2)].push_back(idx1);

        reverse_adj[idx2].push_back(negateNode(idx1));
        reverse_adj[idx1].push_back(negateNode(idx2));
    }

    stack<int>st;
    vector<bool>visited(2 * m, false);

    for(int i = 0; i < 2 * m; i++){
        if(!visited[i]){
            topo_fill(adj, st, visited, i);
        }
    }

    vector<int>SCCid(2 * m, -1);
    int count = 1;

    while(!st.empty()){
        int top = st.top();
        st.pop();

        if(SCCid[top] == -1){
            dfs(reverse_adj, SCCid, top, count);
            count++;
        }
    }

    vector<char>res;

    for(int i = 0; i < m; i++){
        int currID = 2 * i;
        int negateID = 2 * i + 1;

        if(SCCid[currID] == SCCid[negateID]){
            cout<<"IMPOSSIBLE"<<endl;
            return 0;
        }

        if(SCCid[currID] > SCCid[negateID]){
            res.push_back('+');
        }
        else{
            res.push_back('-');
        }
    }

    for(auto& x : res){
        cout<<x<<" ";
    }

    cout<<endl;
    return 0;
}
