
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

## Dynamic programming - 2D

- unique paths - grid technique 
- LOngest common subseq - grid technique again . 

```c++
if (text1[i]==text2[j]){
                    dp[i+1][j+1]  = 1+ dp[i][j];
                }else{
                    dp[i+1][j+1] = max(dp[i][j+1] , dp[i+1][j]);
                }
```
 - Buy and sell stock with cool down - This is kinda like a `skip or go` variation . `skip or buy or sell` . 
 - Coin change : remember EVERY SINGLE variation 

 ```c++
for (int i = startIndex ; i < n ; i++){
            total += solve(amount-coins[i], coins , i , memo);

        }
//changing i to i+1 ? removing the startIndex completely ? what could happen ? 
 ```

 - Target sum : just normal stuff . but caching is a hassle . 
 - Interleaving string : either we choose left one or right one and increment .  if the char ain't equal . then return false . 
 - use PrevValue as an argument and go through the 4 directions 
 - distinct subseq - `skip or go `
 - edit distance - grid technique

 ```c++
if (word1[i]==word2[j]){
                    dp[i+1][j+1] = dp[i][j];
}else{
    dp[i+1][j+1] = 1+min(min(dp[i][j+1],dp[i+1][j]),dp[i][j]);
}
 ```

 ## Linked List

 - We traverse by simply `node = node->next` ing.
 - If you are asked to merge a list .or create a new linked list . You should use the Dummy Node method . 

 ```c++

ListNode dummy(0);
ListNode* node = &dummy;

 ```

 - If you want to through a list halfway , or to any index in the list . You should be using the tortoise and Hare algo . 

 ```c++
while ( fast && fast->next){
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) return true;
} 
 ```

 - The ternary operator technique : If we need to get next node . You need to check if the current node is `NOT nullptr` sometimes

 ```c++
int v1 = (l1 != nullptr) ? l1->val : 0;
int v2 = (l2 != nullptr) ? l2->val : 0;

int val = v1 + v2 + carry;
carry = val / 10;
val = val % 10;
cur->next = new ListNode(val);

cur = cur->next;
l1 = (l1 != nullptr) ? l1->next : nullptr;
l2 = (l2 != nullptr) ? l2->next : nullptr;
 ```

```c++

ListNode* newnxt = slow->next ? slow->next->next : slow->next;
```
- If you wanna make a deep copy of  linked list ... use an unordered_map !

- Also look into the merge sort merge linked list thing too . 

## Two pointers

- 