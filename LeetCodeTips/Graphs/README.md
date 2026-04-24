
## Number of Islands

```c++
class Solution {
public:
    void dfs(int i , int j  , vector<vector<char>>& grid){
        if (0>i || i>=grid.size()||j<0 || j>=grid[0].size()||grid[i][j]=='0') return;

        grid[i][j]='0';

        dfs(i,j+1,grid);
        dfs(i+1,j,grid);
        dfs(i-1,j,grid);
        dfs(i,j-1,grid);
    }
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int count = 0 ;

        for (int i = 0 ; i < rows ; i++){
            for (int j = 0; j < cols ; j++){
                if (grid[i][j]=='1'){
                    count++;
                    dfs(i,j,grid);
                }
            }
        }

        return count;

        
        
    }
};
```

- In normal graph BFS , there is a visited set that keeps track , but here we just mark the visited by updating the graph `1` into `0` s.

- Don't be fooled by the double for loops . this method is O(1).

## Max Area of Island

- Same as the previous one . but in order to get the Area of the island we need a count variable everytime we DFS ! 

```c++
class Solution {
public:
void dfs(int i , int j ,vector<vector<int>>& grid , int& count ){
        if (0>i || i>=grid.size()||j<0 || j>=grid[0].size()||grid[i][j]==0) return;

        grid[i][j]=0;
        count++;
        dfs(i,j+1,grid , count);
        dfs(i+1,j,grid , count);
        dfs(i-1,j,grid , count);
        dfs(i,j-1,grid , count);
    }

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int ans = 0;
        

        for (int i = 0 ; i < rows ; i++){
            for (int j = 0; j < cols ; j++){
                int count = 0;
                if (grid[i][j]==1){

                    dfs(i,j,grid,count);

                    ans = max(ans , count);
                }
            }
        }

        return ans;
    }
};
```

## Clone Graph

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* dfs(Node* node , unordered_map<Node*,Node*>& hashmap){
        if (!node) return nullptr;

        if (hashmap.count(node)) return hashmap[node];

        Node* temp = new Node(node->val);
        hashmap[node] = temp;

        for (auto& nei : node->neighbors){
            temp->neighbors.push_back(dfs(nei, hashmap));
        }

        return temp;

    }
    Node* cloneGraph(Node* node) {

        unordered_map<Node*,Node*> hashmap;

        return dfs(node , hashmap);
        
    }
};
```

- The hashmap is BASICALLY a visited set thingy . It keeps track of the visited nodes ... kinda like a dp memo.
- We make new nodes if every recursive step . and inside the for loop of that method . we call dfs again (which also returns a temp node) . 

## Walls and Gates

- We be using multisource BFS .

```c++
class Solution {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        vector<vector<int>> dirs = {{-1, 0}, {1, 0},
                                    {0, -1}, {0, 1}};
        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            for (int i = 0; i < 4; i++) {
                int r = row + dirs[i][0];
                int c = col + dirs[i][1];

                if (r < 0 || r >= m || c < 0 ||
                    c >= n || grid[r][c] != INT_MAX) {
                    continue;
                }

                grid[r][c] = grid[row][col] + 1;
                q.push({r, c});
            }
        }
    }
};
```

- This part below is the most important . 
```c++
if (r < 0 || r >= m || c < 0 ||
        c >= n || grid[r][c] != INT_MAX) {
        continue;
    }

    grid[r][c] = grid[row][col] + 1;
    q.push({r, c});
```