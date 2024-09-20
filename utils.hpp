#ifndef __UTILS_HPP__
#define __UTILS_HPP__
#include <bits/stdc++.h>

const int max_trussness = 1105;
const int maxn = 320005;
const int maxm = 1050005;
const int maxa = 10;
const int gamma = 1;

struct HashTable
{
    const int mod = maxm << 2;
    struct data
    {
        long long u;
        int v, next;
    };
    data e[maxm << 3];
    int h[maxm << 2], cnt;

    int hash(long long u) { return u < mod ? u : u % mod; }

    int &operator[](long long u)
    {
        int hu = hash(u);
        for (int i = h[hu]; i; i = e[i].next)
        {
            if (e[i].u == u)
                return e[i].v;
        }
        return e[++cnt] = (data){u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
    }

    bool count(long long u)
    {
        int hu = hash(u);
        for (int i = h[hu]; i; i = e[i].next)
        {
            if (e[i].u == u)
                return true;
        }
        return false;
    }

    void erase(long long u)
    {
        int hu = hash(u), pre;
        for (int i = h[hu]; i; i = e[i].next)
        {
            if (e[i].u == u)
            {
                if (i == h[hu])
                    h[hu] = e[i].next;
                else
                    e[pre].next = e[i].next;
            }
            pre = i;
        }
    }

    HashTable()
    {
        cnt = 0;
        memset(h, 0, sizeof(h));
    }
};


struct edge_link
{

    struct data
    {
        int v, pre, next, index_in_e;
    } e[maxm << 1];
    int p[maxn], eid;

    void insert(int u, int v, int index_in_e)
    {
        e[eid].v = v;
        e[eid].next = p[u];
        e[eid].pre = -1;
        e[eid].index_in_e = index_in_e;
        if (p[u] != -1)
            e[p[u]].pre = eid;
        p[u] = eid++;
    }

    void erase(int cur_id)
    {
        if (~e[cur_id].next)
            e[e[cur_id].next].pre = e[cur_id].pre;
        if (~e[cur_id].pre)
            e[e[cur_id].pre].next = e[cur_id].next;
    }

    edge_link()
    {
        memset(p, -1, sizeof(p));
        eid = 0;
    }
};

struct Graph {
    vector<int> V;
    unordered_set<int> E;
    unordered_set<int> G[maxn];
    unordered_map<int, int> trussness; // eid -> tau
    unordered_set<pair<int, int> > triangles[maxm];
    int query_dis = 0;
};

vector<int> G[maxn];
int D[maxn];
int n, m, F, q;
HashTable hash_table_1;
edge_link e_link;
int tau[maxn]; // 存每个节点的tau值
int phi[maxn];
unordered_set<int> attr_set;

#endif