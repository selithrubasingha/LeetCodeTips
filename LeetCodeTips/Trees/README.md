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

 ## Validate Binary Search Tree

 - Just checking left< cur < right for every node is not enough !
 - because ALL the elements in right of subtree should be greater than cur , and vice versa for left.`

 - so we keep variables `left` and `right` to keep track of curr max and min bounds in the subtree , notice how we update them in each call . The initial values are + and - infinities . 

 ```c++
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return solve(root,LONG_MIN , LONG_MAX);
        
        
    }

    long solve(TreeNode* root , long left , long right){
        if (!root) return true;

        if (!(root->val<right && left<root->val) )
            return false;

        

        bool ans = solve(root->left,left , root->val) && solve(root->right,root->val , right);

        return ans;
    }
};
 ```

 ## Kth Smallest Element in a BST

 - In order traversal BABY !

 ```c++

class Solution {
public:

    int ans = 0;

    int kthSmallest(TreeNode* root, int k) {

        int count = 0;

        dfs(root , k , count);
        return ans;

        
    }

    void dfs(TreeNode* root , int k , int& count){

       if (!root) return ;

       dfs(root->left , k , count);
       count++;
       if (count==k) ans = root->val;

       dfs(root->right , k , count);

    }
};

 ```

 ## Construct Binary Tree from Preorder and Inorder Traversal

 - We are given the preorder and inorder traversals .... how are we going to create the actual tree?
 - we know that `preorder[0]` is always the root , if we  find that values' index in inorder , every element left to the index is i the left subtree and
 every element right to it is in the right subtree . (`inLeft` and `inRight`)
 - also , with len of `inLeft` , we can get the same element list in the preorder by getting (1,len) sublist and we can get the `preRight` with (len,end) sublist
 - If we do this enough recursively we can make the tree node .

 ```c++

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty()) return nullptr;

        TreeNode* root = new TreeNode(preorder[0]);
        auto mid = find(inorder.begin(),inorder.end(),preorder[0]) - inorder.begin();

        vector<int>leftPre(preorder.begin() + 1, preorder.begin() + mid + 1);
        vector<int> rightPre(preorder.begin() + mid + 1, preorder.end());
        vector<int> leftIn(inorder.begin(), inorder.begin() + mid);
        vector<int> rightIn(inorder.begin() + mid + 1, inorder.end());
        root->left = buildTree(leftPre, leftIn);
        root->right = buildTree(rightPre, rightIn);
        return root;
    }
};
 ```

 ## Serialize and Deserialize BST

 - we need to store the whole tree as a string , and when the string is given , make the tree from that string  

 - EVERY leaf node , will have NULL nodes and we need to mention that explicitly when serializing and deserializing . 

 ```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }

private:
    // Recursive helper for serialization
    void serialize(TreeNode* root, ostringstream& out) {
        if (!root) {
            out << "N "; // Using space as a delimiter is easier than commas
            return;
        }
        out << root->val << " ";
        serialize(root->left, out);
        serialize(root->right, out);
    }

    // Recursive helper for deserialization
    TreeNode* deserialize(istringstream& in) {
        string val;
        in >> val; // Automatically reads the next space-separated word
        if (val == "N") return nullptr;

        TreeNode* node = new TreeNode(stoi(val));
        node->left = deserialize(in);
        node->right = deserialize(in);
        return node;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
 ```

 - SUPER IMPORTANT : instead of this ostringstream , we could make our own split and join function like the ones in python . 
 the ostringstream is unfamiliar . nevertheless , BE SURE TO LOOK into this stringstream syntax , might be helpful in competitive coding . 

 