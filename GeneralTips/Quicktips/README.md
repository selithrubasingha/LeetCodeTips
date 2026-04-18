
## Binary Search

- remember ! it's `l<=r`.
- Based on my experience these the are the types of questions
    - 2D binary search
    - rotated array Binary Search (find an element or find the minimum)
    - normal search algo's with 3 or more for loops but the last loop should be binary search . 
    -  normal search algo's but  should be binary search .
    - two array related stuff like median or 2 sorted arrays . 
- normally we have 3 if cases ... `mid<target`,`mid>target`,`mid=target`.
- But in some cases we might get `mid<=target`,`mid1>target` . maybe to update the variable or answer while searching through the array . 

## Stack 

- Common pattern 
    1. you have an array and you loop through it with a for loop 
    2. you compare `stack.top()` with the item and based on that add to the stack or update the answer . 
    3. inside the for loop , you could either use a if statement (simple) or a while loop (complex) .
    4. notice that in the inner for or while loop . we first check `!stack.empty()`.
    5. most medium problems use monotonously increasing or decreasing stacks .pattern !

- Do the largest rectangle in a histogram problem again . 

## Trees

- Almost everything is DFS , some are BFS
    - inverting is just like normal swapping
    - To find max depth `return 1+max(left,right)`
    - If you need to go through a path (not necessarily along the root), The diameter finding code is good for that  . 

```c++
    if (!root) return 0;

            int leftHeight = maxHeight(root->left);
            int rightHeight = maxHeight(root->right);
            int diameter = leftHeight + rightHeight;
            int sub = max(diameterOfBinaryTree(root->left),
                        diameterOfBinaryTree(root->right));
            return max(diameter, sub);
```
 
- You could return 2 things (multiple variables) along a recursive stack .

```c++
    vector<int> dfs(TreeNode* root){
        if (!root) return {1,0};

        vector<int> left = dfs(root->left);
        vector<int> right = dfs(root->right);

        int balanced = (left[0]==1 && right[0]==1 && abs(left[1]-right[1])<=1);

        int height = 1+ max(left[1],right[1]);

        return {balanced , height};
```

- AT LEAST type recursion__: where in the recursive stack ... if at least one thing is true or false ... then the whole answer should be true or false  .

```c++
bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        else if ((!p && q) || (p && !q)) return false;

        if (p->val != q->val) return false;

        bool ans = isSameTree(p->left,q->left) && isSameTree(p->right,q->right) ;

        return ans;
        
    }
```

## Dynamic programming -1D

- Climbing stairs is basically asking for hte fibonacci sequence  ,
- House robber teachers us the `skip or go ` recursive technique . This method can be seen in other methods too . 
- Notice in House robber ... we are given the houses array . for the n th house argument case the actual house there is n-1 BECAUSE of the 0 indexed problem . This is different from the climbing stairs indexing . 
- If you see palindrome ... just use the l--,r++ mehtod . don't use recurion !
- Decode ways is just like a `skip or go`. BUT it's more like `check the first none and go :: OR check the first two and go `.
- word break is AT LEAST type recursion
- Longest increasing subseq is also `skip and go`. although i bit advances ... must refer later . 
- after you get the answer ... try to memoize it . either 1D memo or 2D memo . 


 