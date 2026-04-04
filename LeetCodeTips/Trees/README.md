# Trees

- The first few question is some basic questions that don't need no explanation 

## Invert Binary Tree

```C++
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        invertTree(root->left);
        invertTree(root->right);

        return root;
        
    }
};
```
## Maximum Depth of Binary Tree

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return 1+max(left,right);
        
    }
};
```

## Diameter of Binary Tree

```C++
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        int leftHeight = maxHeight(root->left);
        int rightHeight = maxHeight(root->right);
        int diameter = leftHeight + rightHeight;
        int sub = max(diameterOfBinaryTree(root->left),
                      diameterOfBinaryTree(root->right));
        return max(diameter, sub);
        
    }

    int maxHeight(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxHeight(root->left), maxHeight(root->right));
    }
};
```

## Balanced Binary Tree

```C++
class Solution {
public:
    bool isBalanced(TreeNode* root) {

        return dfs(root)[0]==1;
    }

    vector<int> dfs(TreeNode* root){
        if (!root) return {1,0};

        vector<int> left = dfs(root->left);
        vector<int> right = dfs(root->right);

        int balanced = (left[0]==1 && right[0]==1 && abs(left[1]-right[1])<=1);

        int height = 1+ max(left[1],right[1]);

        return {balanced , height};
    }
};
```

## Same Tree

```C++
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if ((!p && q) || (p && !q)) return false;

        if (p->val != q->val) return false;

        bool ans = isSameTree(p->left,q->left) && isSameTree(p->right,q->right) ;

        return ans;
        
    }
};
```