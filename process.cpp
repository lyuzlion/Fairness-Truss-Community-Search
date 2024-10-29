#include <bits/stdc++.h>
using namespace std;

int n, m;
set<int> G[5000000];
int core[5000000];
bool vis[5000000];

set<int> core_class[5000000];

void core_decomposition() {
    vector<int> node;
    for(int i = 1;i <= n;i++) {
        node.push_back(i);
        core_class[G[i].size()].insert(i);
    }
    
    sort(node.begin(), node.end(), [&] (const int &u, const int &v) -> bool {
        return G[u].size() < G[v].size();
    });


    queue<int> que;
    for(const int v : node) {
        if(G[v].size() == G[node[0]].size()) {
            que.push(v);
            core[v] = G[v].size();
            vis[v] = true;
        }
    }
    int cur_core = G[node[0]].size();
    while(1) {
        // cerr << 1 << endl;
        while(!que.empty()) {
            int u = que.front();
            // cerr << u << endl;
            que.pop();
            for(const int v : G[u]) {
                // cerr << v << "..."<< endl;
                core_class[G[v].size()].erase(v);
                G[v].erase(u);
                core_class[G[v].size()].insert(v);
                if(!vis[v] && G[v].size() <= cur_core) {
                    vis[v] = true;
                    que.push(v);
                    core[v] = cur_core;
                }
            }
            G[u].clear();
        }
        // cerr << 1 << endl;
        for(cur_core++;cur_core <= n;cur_core++) {
            // if(cur_core <= 100) cerr << cur_core << " " << core_class[cur_core].size() << '\n';
            if(!core_class[cur_core].empty()) {
                for(const int v : node) {
                    if(!vis[v] && G[v].size() == cur_core) {
                        que.push(v);
                        vis[v] = true;
                        core[v] = cur_core;
                    }
                }
                break;
            }
        }
        if(cur_core == n + 1) {

            int max_core = 0;
            for(int i = 1;i <= n;i++) {
                max_core = max(max_core, core[i]);
            }
            int cnt4 = 0;
            int cnt5 = 0;
            int cnt6 = 0;
            int cnt7 = 0;
            int cnt8 = 0;
            int cnt9 = 0;
            int cnt10 = 0;
            int cnt11 = 0;
            int cnt50 = 0;
            cout << "max coreness : " << max_core << endl;
            for(int i = 1;i <= n;i++) {
                if(core[i] <= max_core * 0.85 + 2 && core[i] >= max_core * 0.85) {
                    cout << i << endl;
                }
            }   
            return;
        }
    }
    
}


int main() {
    freopen("../Dataset/wiki_A4/wiki_A4.txt", "r", stdin);
    freopen("../Dataset/wiki_A4/wiki_A4_processed.txt", "w", stdout);
    cin >> n >> m;
    // cout << n << " " <<  m << endl;
    for(int i = 1;i <= m;i++) {
        int u, v;
        cin >> u >> v;
        if(u == v || G[u].count(v)) continue;
        // cout << u << " " << v << endl;
        G[u].insert(v);
        G[v].insert(u);
    }
    // return 0;
    core_decomposition();

    
    
    return 0;
}
