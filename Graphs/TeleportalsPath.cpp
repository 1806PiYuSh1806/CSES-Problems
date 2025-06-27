#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <stack>
#include <map>
#include <list>
#include <functional>

using namespace std;

void dfs(int u, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (const auto& edge : adj[u]) {
        if (!visited[edge.first]) {
            dfs(edge.first, adj, visited);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> indegree(n, 0);
    vector<int> outdegree(n, 0);
    vector<vector<pair<int, int>>> adj(n);
    vector<vector<pair<int, int>>> adj_copy(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        adj[u].push_back({v, i});
        adj_copy[u].push_back({v, i});
        indegree[v]++;
        outdegree[u]++;
    }

    int start_node = -1;
    int end_node = -1;
    int diff_count = 0;

    for (int i = 0; i < n; i++) {
        if (outdegree[i] - indegree[i] == 1) {
            start_node = i;
            diff_count++;
        } else if (indegree[i] - outdegree[i] == 1) {
            end_node = i;
            diff_count++;
        } else if (indegree[i] != outdegree[i]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    if (diff_count == 0) {
        start_node = 0;
        for (int i = 0; i < n; ++i) {
            if (outdegree[i] > 0) {
                start_node = i;
                break;
            }
        }
        end_node = start_node;
    } else if (diff_count != 2) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    if (start_node != 0 || end_node != n - 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<bool> visited(n, false);
    int dfs_start = -1;
    for (int i = 0; i < n; ++i) {
        if (outdegree[i] > 0) {
            dfs_start = i;
            break;
        }
    }

    if (dfs_start != -1) {
        dfs(dfs_start, adj, visited);
    }

    for (int i = 0; i < n; i++) {
        if (outdegree[i] > 0 || indegree[i] > 0) {
            if (!visited[i]) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    stack<int> st;
    vector<int> path;
    map<int, vector<pair<int, int>>::iterator> current_edge;

    for (int i = 0; i < n; ++i) {
        current_edge[i] = adj[i].begin();
    }

    st.push(start_node);

    while (!st.empty()) {
        int u = st.top();

        if (current_edge.count(u) && current_edge[u] != adj[u].end()) {
            int v = current_edge[u]->first;
            current_edge[u]++;
            st.push(v);
        } else {
            path.push_back(u);
            st.pop();
        }
    }

    if (path.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    reverse(path.begin(), path.end());

    if (path[0] != start_node || path.back() != end_node) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] + 1 << (i == path.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}