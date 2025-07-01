#include <bits/stdc++.h>
using namespace std;

static constexpr int INF = 1'000'000'000;
/*
Segment Tree 1-based index
- Build: O(n)
- Point update: O(logn)
- Range query: O(logn)
*/
class SegmentTree {
    function<int(int,int)> merge;
    vector<int> st;
    int n;
public:
    SegmentTree(const vector<int>& data, function<int(int,int)> merge_)
      : merge(merge_)
      , n(int(data.size()) - 1)
      , st(4*n + 5, 0)
    {
        build(1, 1, n, data);
    }

    void update(int pos, int val) {
        update(1, 1, n, pos, val);
    }

    int query(int l, int r) {
        if (l > r) swap(l,r);
        return query(1, 1, n, l, r);
    }

private:
    void build(int id, int l, int r, const vector<int>& data) {
        if (l == r) {
            st[id] = data[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(id<<1,     l,   mid, data);
        build(id<<1|1, mid+1,   r, data);
        st[id] = merge(st[id<<1], st[id<<1|1]);
    }

    void update(int id, int l, int r, int pos, int val) {
        if (l == r) {
            st[id] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)      update(id<<1,   l, mid, pos, val);
        else                 update(id<<1|1, mid+1, r, pos, val);
        st[id] = merge(st[id<<1], st[id<<1|1]);
    }

    int query(int id, int l, int r, int u, int v) {
        if (r < u || l > v)  return INF;        // outside
        if (l >= u && r <= v) return st[id];    // fully inside
        int mid = (l + r) >> 1;
        int left = query(id<<1,   l, mid, u, v);
        int right= query(id<<1|1, mid+1, r, u, v);
        return merge(left, right);
    }
};
