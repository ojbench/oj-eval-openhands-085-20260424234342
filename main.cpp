#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int v): val(v), left(nullptr), right(nullptr) {}
};

// Build tree from extended preorder input stream (values separated by spaces),
// with -1 meaning null pointer, and -2 meaning end of input.
// According to problem statement, the stream represents an extended preorder
// that constructs a tree: a value for the node (0/1), then recursively left and right,
// with -1 for empty child. Here we read tokens and build accordingly.

class Reader {
public:
    vector<long long> a;
    size_t idx{0};
    Reader() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        long long x;
        while (cin >> x) {
            if (x == -2) break;
            a.push_back(x);
        }
    }
    bool hasNext() const { return idx < a.size(); }
    long long next() { return a[idx++]; }
};

Node* build(Reader &r) {
    if (!r.hasNext()) return nullptr; // safety
    long long x = r.next();
    if (x == -1) return nullptr;
    Node* n = new Node((int)x);
    n->left = build(r);
    n->right = build(r);
    return n;
}

// Prune subtrees whose all nodes are 0 (i.e., remove subtrees that contain only 0 values).
// Based on examples, pruning condition: remove a node if its value is 0 AND both pruned children are null
// or pruned away to null (i.e., the subtree has no 1).
Node* prune(Node* root) {
    if (!root) return nullptr;
    root->left = prune(root->left);
    root->right = prune(root->right);
    if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }
    return root;
}

void preorder_with_null(Node* root, vector<int>& out) {
    if (!root) {
        out.push_back(-1);
        return;
    }
    out.push_back(root->val);
    preorder_with_null(root->left, out);
    preorder_with_null(root->right, out);
}

void destroy(Node* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    Reader r;
    if (r.a.empty()) return 0;
    Node* root = build(r);
    root = prune(root);
    vector<int> out;
    preorder_with_null(root, out);
    // Print space-separated line
    for (size_t i = 0; i < out.size(); ++i) {
        if (i) cout << ' ';
        cout << out[i];
    }
    cout << "\n";
    destroy(root);
    return 0;
}
