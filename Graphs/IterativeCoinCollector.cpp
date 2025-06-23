#include <iostream>
#include <vector>
#include <algorithm> 
#include <queue> // Not strictly needed for this solution but often included
#include <climits> // Not strictly needed, use numeric_limits
#include <stack>

using namespace std;

// Iterative version of topo_fill
void topo_fill_iterative(const vector<vector<int>>& adj, stack<int>& st, vector<bool>& visited, int start_node) {
    stack<pair<int, int>> dfs_stack; // pair: {node, state (0: push children, 1: process after children)}
    dfs_stack.push({start_node, 0});

    while (!dfs_stack.empty()) {
        int u = dfs_stack.top().first;
        int state = dfs_stack.top().second;
        dfs_stack.pop();

        if (state == 0) { // Before visiting children
            if (visited[u]) {
                continue;
            }
            visited[u] = true;
            dfs_stack.push({u, 1}); // Push again to process after children

            for (int i = adj[u].size() - 1; i >= 0; --i) { // Push children in reverse order for correct processing order
                int v = adj[u][i];
                if (!visited[v]) {
                    dfs_stack.push({v, 0});
                }
            }
        } else { // After visiting all children
            st.push(u);
        }
    }
}


// Iterative version of dfs (for SCCs)
void dfs_iterative(const vector<vector<int>>& adj, vector<int>& SCCid, vector<long long>& totalCoins, int start_node, int& count, const vector<long long>& coins) {
    stack<int> scc_stack;
    scc_stack.push(start_node);
    
    while (!scc_stack.empty()) {
        int u = scc_stack.top();
        scc_stack.pop();

        if (SCCid[u] != -1) { // Already assigned to an SCC
            continue;
        }

        SCCid[u] = count;
        totalCoins[count] += 1LL * coins[u];

        for (int v : adj[u]) {
            if (SCCid[v] == -1) { // Not yet assigned to an SCC
                scc_stack.push(v);
            }
        }
    }
}

// The solve function (DP on DAG) can usually remain recursive as the depth of the SCC graph
// is at most `count` (number of SCCs), which is at most `N`.
// However, if `count` is very large and the SCC graph is a long chain, it could also overflow.
// For robust solutions, this can also be made iterative (e.g., by explicit topological sort and iteration).
// For typical competitive programming limits, this recursive DP might pass if `count` is not extremely deep.
// Given N=100000, if a single SCC chain has 100000 SCCs, it will overflow.
// The safe bet is to also make this iterative or explicitly use topological sort.

// Iterative version of solve (DP on DAG) using explicit topological sort
// This requires calculating in-degrees for SCCGraph
long long solve_iterative(int num_sccs, const vector<vector<int>>& scc_graph, const vector<long long>& totalCoins) {
    vector<long long> dp(num_sccs, 0); // dp[i] = max coins ending at SCC i

    vector<int> in_degree(num_sccs, 0);
    for (int i = 0; i < num_sccs; ++i) {
        for (int neighbor_scc : scc_graph[i]) {
            in_degree[neighbor_scc]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < num_sccs; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
            dp[i] = totalCoins[i]; // Base case: path starts here
        }
    }

    long long max_overall_coins = 0;

    while (!q.empty()) {
        int u_scc = q.front();
        q.pop();

        max_overall_coins = max(max_overall_coins, dp[u_scc]);

        for (int v_scc : scc_graph[u_scc]) {
            // Update dp[v_scc] if a path through u_scc leads to a better sum for v_scc
            dp[v_scc] = max(dp[v_scc], dp[u_scc] + totalCoins[v_scc]); // Note: totalCoins[v_scc] is added to incoming path
            in_degree[v_scc]--;
            if (in_degree[v_scc] == 0) {
                q.push(v_scc);
            }
        }
    }
    return max_overall_coins;
}

// Or, the recursive solve function can be adjusted to find `max_path_starting_from_scc`
// and then find `max(all max_path_starting_from_scc)`
// The original recursive `solve` computes `max_path_starting_from_scc` correctly.
// So for robustness against stack overflow if the number of SCCs is also very large,
// we'll provide the `solve_iterative` (Topological Sort based) version.

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin>>n>>m;

    vector<vector<int>>adj(n);
    vector<vector<int>>reverse_adj(n);

    vector<long long>coins(n);
    for(int i = 0; i < n; i++){
        cin>>coins[i];
    }

    for(int i = 0; i < m; i++){
        int u, v;
        cin>>u>>v;
        adj[u - 1].push_back(v - 1);
        reverse_adj[v - 1].push_back(u - 1);
    }

    stack<int>st;
    vector<bool>visited(n, false);

    for(int i = 0; i < n; i++){
        if(visited[i] == false){
            topo_fill_iterative(adj, st, visited, i); // Use iterative version
        }
    }

    vector<int>SCCid(n, -1);
    vector<long long>totalCoins; // This will store coins per SCC. Indexed by SCC_ID.
    int count = 0; // Number of SCCs found

    while(!st.empty()){
        int top = st.top();
        st.pop();

        if(SCCid[top] == -1){
            totalCoins.push_back(0); // Add a new slot for a new SCC's coins
            dfs_iterative(reverse_adj, SCCid, totalCoins, top, count, coins); // Use iterative version
            count++;
        }
    }

    vector<vector<int>>SCCGraph(count);
    // Using a 2D boolean array to track edges can be memory intensive for count * count.
    // For large 'count', consider using std::set<int> in SCCGraph[i] or sort+unique the vectors after populating.
    // However, given N=10^5, `count` can also be 10^5.
    // If M (number of edges) is small, `SCCGraph` might be sparse.
    // For `count` up to 10^5, `vector<vector<bool>>` of size `count * count` is 10^10 bits, which is too much.
    // Let's use `std::set` to avoid duplicate edges in SCCGraph.
    vector<vector<int>> temp_SCCGraph(count); // Temporarily store edges before uniqueing
    
    for(int i = 0; i < n; i++){
        for(auto& x : adj[i]){
            if(SCCid[i] != SCCid[x]){
                temp_SCCGraph[SCCid[i]].push_back(SCCid[x]);
            }
        }
    }

    // Now, populate SCCGraph using temp_SCCGraph and sort+unique to remove duplicates
    for(int i = 0; i < count; ++i) {
        sort(temp_SCCGraph[i].begin(), temp_SCCGraph[i].end());
        temp_SCCGraph[i].erase(unique(temp_SCCGraph[i].begin(), temp_SCCGraph[i].end()), temp_SCCGraph[i].end());
        SCCGraph[i] = temp_SCCGraph[i]; // Copy unique edges
    }

    // Use the iterative DP solve function
    long long final_res = solve_iterative(count, SCCGraph, totalCoins);

    cout << final_res << endl;
    return 0;
}