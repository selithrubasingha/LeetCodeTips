## space seperated int --> Tree

```c++
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* buildTreeFromSpaces() {
    int val;
    // Read the first value for the root
    if (!(cin >> val) || val == -1) return nullptr;

    TreeNode* root = new TreeNode(val);
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        // 1. Try to read the Left Child
        if (cin >> val) {
            if (val != -1) {
                curr->left = new TreeNode(val);
                q.push(curr->left);
            }
        } else break;

        // 2. Try to read the Right Child
        if (cin >> val) {
            if (val != -1) {
                curr->right = new TreeNode(val);
                q.push(curr->right);
            }
        } else break;
    }
    return root;
}

// Helper to verify the tree was built correctly (In-order)
void printTree(TreeNode* root) {
    if (!root) return;
    printTree(root->left);
    cout << root->val << " ";
    printTree(root->right);
}

int main() {
    // Example Input: 11 1 2 15 -1 -1 -1
    // (11 is root, 1 is left, 2 is right, 15 is 1's left child)
    cout << "Enter the values separated by spaces (use -1 for null): " << endl;
    
    TreeNode* root = buildTreeFromSpaces();

    cout << "In-order traversal of built tree: ";
    printTree(root);
    cout << endl;

    return 0;
}
```
