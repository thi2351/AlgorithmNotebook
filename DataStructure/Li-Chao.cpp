#include <bits/stdc++.h>
using namespace std;

/*
Li-Chao Tree (Dynamic Convex Hull Trick)
- Insert line: O(log n)
- Query minimum: O(log n)
- Supports dynamic line insertions and minimum queries
*/
struct Line {
    long long m, b;
    Line(long long m = 0, long long b = 0) : m(m), b(b) {}
    
    long long eval(long long x) const {
        return m * x + b;
    }
};

class LiChaoTree {
private:
    struct Node {
        Line line;
        Node *left, *right;
        Node(Line l) : line(l), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    long long min_x, max_x;
    
    void insert_line(Node*& node, Line line, long long l, long long r) {
        if (!node) {
            node = new Node(line);
            return;
        }
        
        long long mid = (l + r) / 2;
        bool left_better = line.eval(l) < node->line.eval(l);
        bool mid_better = line.eval(mid) < node->line.eval(mid);
        
        if (mid_better) {
            swap(node->line, line);
        }
        
        if (l == r) return;
        
        if (left_better != mid_better) {
            insert_line(node->left, line, l, mid);
        } else {
            insert_line(node->right, line, mid + 1, r);
        }
    }
    
    long long query(Node* node, long long x, long long l, long long r) {
        if (!node) return LLONG_MAX;
        
        long long curr = node->line.eval(x);
        if (l == r) return curr;
        
        long long mid = (l + r) / 2;
        if (x <= mid) {
            return min(curr, query(node->left, x, l, mid));
        } else {
            return min(curr, query(node->right, x, mid + 1, r));
        }
    }
    
    void destroy(Node* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

public:
    LiChaoTree(long long min_x, long long max_x) : min_x(min_x), max_x(max_x), root(nullptr) {}
    
    ~LiChaoTree() {
        destroy(root);
    }
    
    // Insert line y = mx + b
    void insert_line(long long m, long long b) {
        insert_line(root, Line(m, b), min_x, max_x);
    }
    
    // Query minimum value at x
    long long query(long long x) {
        return query(root, x, min_x, max_x);
    }
    
    // Insert line segment from x1 to x2
    void insert_line_segment(long long m, long long b, long long x1, long long x2) {
        // For simplicity, we'll insert the line for the entire range
        // In practice, you might want to use a more sophisticated approach
        insert_line(m, b);
    }
};
