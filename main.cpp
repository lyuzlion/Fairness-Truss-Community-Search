// #pragma GCC optimize(3,"Ofast")
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")

#include <bits/stdc++.h>
#include "utils.hpp"
#include "truss.hpp"
using namespace std;

bool vis[maxn];
Graph C;
int attr_sum[maxa];
int dis[maxn];
void FTCS() {
    int lk = 1, rk = tau[q] + 1, k;
    while(lk < rk) {
        k = (lk + rk) >> 1;

        C.V.clear();
        memset(vis, false, sizeof(vis));

        queue<int> que;
        que.push(q);
        vis[q] = true;
        C.V.push_back(q);

        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(const int & v : G[u]) {
                if(!vis[v]) {
                    vis[v] = true;
                    C.V.push_back(v);
                    que.push(v);
                }
            }
        }
        memset(attr_sum, 0, sizeof(attr_sum));
        for(const int v : C.V) {
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
    cerr << k << '\n';

    for(const int v : C.V) {
        for(const int u : G[v]) {
            if(vis[u] && vis[v]) {
                C.E.insert(hash_table_1[1ll * v * n + u]);
                C.G[u].insert(v);
                C.G[v].insert(u);
            }
        }
    }
    // ----------------------------------------------------------------------------------

    auto cmp = [](const int &v1, const int &v2) -> bool
    {
        return C.G[v1].size() != C.G[v2].size() ? C.G[v1].size() > C.G[v2].size() : v1 < v2;
    };
    sort(C.V.begin(), C.V.end(), cmp);

    unordered_set<int> A[maxn];

    for (int i = 0; i < C.V.size(); i++)
    {
        int vertex = C.V[i];
        for (const int v : C.G[vertex])
        {
            if (cmp(v, vertex))
                continue;
            for (const int &w : A[vertex])
            {
                if (A[v].count(w))
                {
                    int eid1 = hash_table_1[1ll * v * n + vertex], eid2 = hash_table_1[1ll * v * n + w], eid3 = hash_table_1[1ll * vertex * n + w];
                    C.trussness[eid1]++;
                    C.trussness[eid2]++;
                    C.trussness[eid3]++;
                    C.triangles[eid1].insert(min(eid2, eid3), max(eid2, eid3));
                    C.triangles[eid2].insert(min(eid1, eid3), max(eid1, eid3));
                    C.triangles[eid3].insert(min(eid1, eid2), max(eid1, eid2));
                }
            }
            A[v].insert(vertex);
        }
    }

    // -----------------------------------------------------------------------------
    while(1) {
        queue<int> que;
        que.push(q);
        memset(dis, 0x3f, sizeof(dis));
        dis[q] = 0;
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(const int v : C.G[u]) {
                if(dis[v] == 0x3f3f3f3f) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
        sort(C.V.begin(), C.V.end(), [] (const int &v1, const int &v2) -> bool {
            return dis[v1] > dis[v2];
        });

        assert(que.empty());

        C.query_dis = dis[C.V[0]];
        
        for(int i = 0;i < gamma && i < C.V.size();i++) {
            int v = C.V[i];
            for(const int u : C.G[v]) {
                int eid = hash_table_1[1ll * v * n + u];
                que.push(eid);
            }
        }

        while(!que.empty()) {
            int eid1 = que.front();
            que.pop();
            int u = E[eid1].u, v = E[eid1].v;
            C.G[u].erase(v), C.G[v].erase(u);
            C.E.erase(eid1);
            for(auto ele : C.triangles[eid1]) {
                int eid2 = ele.first, eid3 = ele.second;
                C.trussness[eid2]--;
                C.trussness[eid3]--;
                if(C.trussness[eid2] < k - 2) {
                    que.push(eid2);
                }
            }
        }

        sort(C.V.begin(), C.V.end(), [] (const int &v1, const int &v2) -> bool {
            return C.G[v1].size() > C.G[v2].size();
        });


        while((int) C.V.size() > 0 && C.G[C.V[C.V.size() - 1]].size() == 0) {
            C.V.pop_back();
        }

        for(const int u : C.V) {
            assert((int) C.G[u].size() < k - 2);
        }

        memset(attr_sum, 0, sizeof(attr_sum));
        for(const int v : C.V) {
            attr_sum[phi[v]]++;
        }
        int fairness = 0;
        for(const int attr : attr_set) {
            fairness += min(F, attr_sum[attr]);
        }

        if(fairness < F * (int) attr_set.size()) break;
    }
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
        cin >> E[i].u >> E[i].v;
        hash_table_1[1ll * E[i].u * n + E[i].v] = i;
        hash_table_1[1ll * E[i].v * n + E[i].u] = i;
        D[E[i].u]++;
        D[E[i].v]++;
        G[E[i].u].push_back(i);
        G[E[i].v].push_back(i);
        e_link.insert(E[i].u, E[i].v, i);
        e_link.insert(E[i].v, E[i].u, i);
    }

    for(int i = 1;i <= n;i++) {
        phi[i] = get_rand(0, 1);
        attr_set.insert(phi[i]);
    }
    truss_decomposition();
    FTCS();
    return 0;
}