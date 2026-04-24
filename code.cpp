
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int sz[MAXN];
int parent[MAXN];
int n, k;
vector<int> results;

void iterative_dfs_size(int start_node) {
    stack<pair<int, int>> s;
    s.push({start_node, 0});
    vector<int> order;
    while (!s.empty()) {
        int u = s.top().first;
        int p = s.top().second;
        s.pop();
        order.push_back(u);
        parent[u] = p;
        for (int v : adj[u]) {
            if (v != p) {
                s.push({v, u});
            }
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v != parent[u]) {
                sz[u] += sz[v];
            }
        }
    }
}

void iterative_dfs_check(int start_node) {
    stack<pair<int, int>> s;
    s.push({start_node, 0});
    while (!s.empty()) {
        int u = s.top().first;
        int p = s.top().second;
        s.pop();
        bool ok = true;
        if (n - sz[u] > k) ok = false;
        for (int v : adj[u]) {
            if (v != p) {
                if (sz[v] > k) ok = false;
                s.push({v, u});
            }
        }
        if (ok) {
            results.push_back(u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> n >> k)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    iterative_dfs_size(1);
    iterative_dfs_check(1);

    if (results.empty()) {
        cout << "None" << endl;
    } else {
        sort(results.rbegin(), results.rend());
        for (int i = 0; i < results.size(); ++i) {
            cout << results[i] << (i == results.size() - 1 ? "" : " ");
        }
        cout << endl;
    }

    return 0;
}
