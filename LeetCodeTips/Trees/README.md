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

- diameter is the max path along the tree nodes ? it might even go through the tree node . that is why th `int sub` is used .

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

- In every node each subtree must have equal or differ by 1 heights .

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

## Subtree of Another Tree

- for each node in main tree ... check the equality with the subtree,

```c++
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (!root) return false;

        if (isSameTree(root , subRoot)) return true;

        int left = isSubtree(root->left , subRoot);
        int right = isSubtree(root->right , subRoot);

        return (left||right);
        

        
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if ((!p && q) || (p && !q)) return false;

        if (p->val != q->val) return false;

        bool ans = isSameTree(p->left,q->left) && isSameTree(p->right,q->right) ;

        return ans;
        
    }
};
```

## Lowest Common Ancestor of a Binary Search Tree

- REMEBER ! it's just a binary search tree! where left < curr < right .
- You can just use this logic to check who the lowest C. ansestor is .

```C++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root|| !p || !q) return nullptr;

        if (max(p->val,q->val)<root->val){
            return lowestCommonAncestor(root->left, p, q);

        }else if (min(p->val,q->val)>root->val){
            return lowestCommonAncestor(root->right, p, q);

        }else{
            return root;
        }

        
        
    }
};
```

## Binary Tree Level Order Traversal

- A basic probelm uncluding BFS .
- The tweak is that _we keep track of which level we are on_.
- This can be done by getting the size of the  q . and doing the for loop until that exact iterations of size is over

```C++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) return {};

        vector<vector<int>> ans;

        queue<TreeNode*> q;

        q.push(root);

        while (!q.empty()){
            int n =q.size();
            vector<int> temp;

            for (int i = 0 ; i < n; i++){
                TreeNode* curr = q.front();
                q.pop();

                //do something
                temp.push_back(curr->val);

                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);

            }

            ans.push_back(temp);
            
        }

        return ans;
    }
};
```

## Binary Tree Right Side View

- In a way , if you think about it , we already made a list of all all the levels in the prev question ,
- If we just add the last element in all of 'em . we get the right side view . 

```c++

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};

        vector<int> ans;

        queue<TreeNode*> q;

        q.push(root);

        while (!q.empty()){
            int n =q.size();
            vector<int> temp;

            for (int i = 0 ; i < n; i++){
                TreeNode* curr = q.front();
                q.pop();

                //do something
                temp.push_back(curr->val);

                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);

            }

            ans.push_back(temp[n-1]);
            
        }

        return ans;
        
    }
};
```

## Count Good Nodes in Binary Tree

- we just keep track of the largest element and the parental nodes above .
 _Given a binary tree `root`, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X._

 ```c++

class Solution {
public:
    int goodNodes(TreeNode* root) {

        return dfs(root,root->val);
        
    }

    int dfs(TreeNode* root, int largest){
       if (!root) return 0;

       int ans = 0;

       if (root->val>=largest){
            ans = 1;
       }

       ans+=dfs(root->left , max(largest,root->val))+dfs(root->right,max(largest,root->val));

       return ans;
    }
};
 ```