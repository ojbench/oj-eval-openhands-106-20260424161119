
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int sz[MAXN];
int n, k;
vector<int> results;

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }
}

void dfs_check(int u, int p) {
    bool ok = true;
    if (n - sz[u] > k) ok = false;
    for (int v : adj[u]) {
        if (v != p) {
            if (sz[v] > k) ok = false;
            dfs_check(v, u);
        }
    }
    if (ok) {
        results.push_back(u);
    }
}

int main() {
    if (!(cin >> n >> k)) return 0;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_size(1, 0);
    dfs_check(1, 0);

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
