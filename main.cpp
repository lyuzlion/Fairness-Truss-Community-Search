// #pragma GCC optimize(3,"Ofast")
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#include <bits/stdc++.h>
#include "utils.hpp"
#include "truss.hpp"
using namespace std;

bool vis[maxn];
Graph C0;
int attr_sum[maxa];
void FTCS() {
    int lk = 1, rk = tau[q] + 1, k;
    while(lk < rk) {
        k = (lk + rk) >> 1;
        queue<int> que;
        que.push(q);

        for(const int u : C0.V) {
            C0.E[u].clear();
        }
        C0.V.clear();
        
        vis[q] = true;
        C0.V.push_back(q);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(const int & v : G[u]) {
                if(!vis[v]) {
                    vis[v] = true;
                    C0.V.push_back(v);
                    que.push(v);
                }
            }
        }
        for(const int v : C0.V) {
            attr_sum[phi[v]]++;
        }
        int fairness = 0;
        for(const int attr : attr_set) {
            fairness += min(F, attr_sum[attr]);
        }
        if(fairness == F * (int) attr_set.size()) lk = k + 1;
        else rk = k;
    }
    k = lk - 1;
    
}

mt19937 rnd(time(0));
int get_rand(int l, int r) {
    return l + rnd() % (r - l + 1);
}

int main(int argc, char * argv[])
{
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    F = stoi(argv[1]);
    q = stoi(argv[2]);

    cin >> n >> m;

    for (int i = 1; i <= m; i++)
    {
        cin >> e[i].u >> e[i].v;
        hash_table_1[1ll * e[i].u * n + e[i].v] = i;
        hash_table_1[1ll * e[i].v * n + e[i].u] = i;
        D[e[i].u]++;
        D[e[i].v]++;
        G[e[i].u].push_back(i);
        G[e[i].v].push_back(i);
        e_link.insert(e[i].u, e[i].v, i);
        e_link.insert(e[i].v, e[i].u, i);
    }

    for(int i = 1;i <= n;i++) {
        phi[i] = get_rand(0, 1);
        attr_set.insert(phi[i]);
    }
    truss_decomposition();
    FTCS();
    return 0;
}