
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


## Rotting Oranges

- Same as the prev one , Only the main logic changes . 

```c++
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        vector<vector<int>> dirs = {{-1, 0}, {1, 0},

                                    {0, -1}, {0, 1}};

        int rows = grid.size();
        int cols = grid[0].size();

        queue<pair<int,int>> q;

        for (int i = 0 ; i < rows; i++){
            for (int j = 0 ; j< cols ; j++){
                if (grid[i][j]==2)
                    q.push({i,j});
            }
        }

        int time = 0;

        while (!q.empty()){
            int size = q.size();
            
            for (int i = 0; i<size;i++){
                int row = q.front().first;
                int col = q.front().second;
                q.pop();

                for (int j = 0; j<4 ; j++){
                    int nr = row+dirs[j][0];
                    int nc = col+dirs[j][1];

                    if (nr < 0 || nr >= rows || nc < 0 ||
                    nc >= cols || grid[nr][nc] != 1) {
                        continue;
                }
                    grid[nr][nc] = 2;
                    q.push({nr,nc});


                }

            }

            time++;
            

            
        }

        for (int i = 0 ; i < rows; i++){
            for (int j = 0 ; j< cols ; j++){
                if (grid[i][j]==1)
                    return -1;
            }
        }

        return max(time-1,0);
        
        
    }
};
```

## Pacific atlantic

- top row and left col  slots are definitley pacific . 
- bottom row and right col slots are definitely atlantic . 
- we do DFS from everyslot mentioned above and update the 2D `can flow` matrices . 

```c++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<bool>> pac(rows , vector<bool>(cols,false));
        vector<vector<bool>> atl(rows , vector<bool>(cols,false));

        // Top and Bottom borders
    for (int c = 0; c < cols; c++) {
        // Pacific (Top row: r=0)
        dfs(0, c, pac, heights[0][c], heights);
        // Atlantic (Bottom row: r=rows-1)
        dfs(rows - 1, c, atl, heights[rows - 1][c], heights);
    }

    // Left and Right borders
    for (int r = 0; r < rows; r++) {
        // Pacific (Left col: c=0)
        dfs(r, 0, pac, heights[r][0], heights);
        // Atlantic (Right col: c=cols-1)
        dfs(r, cols - 1, atl, heights[r][cols - 1], heights);
    }

        vector<vector<int>> res;

        for (int r = 0; r<rows; r++){
            for (int c = 0 ; c< cols ; c++){
                if (pac[r][c] && atl[r][c])
                    res.push_back({r,c});
            }
        }
        

        return res;
        
    }

    void dfs(int r, int c, vector<vector<bool>>& visit, int prevHeight, vector<vector<int>>& heights) {
    int ROWS = heights.size();
    int COLS = heights[0].size();

    // "Leap Before You Look" - Base cases handle all boundary and logic checks
    if (r < 0 || c < 0 || r == ROWS || c == COLS || 
        visit[r][c] || heights[r][c] < prevHeight) {
        return;
    }

    // Mark as visited
    visit[r][c] = true;

    // Recursive calls in all 4 directions
    dfs(r + 1, c, visit, heights[r][c], heights);
    dfs(r - 1, c, visit, heights[r][c], heights);
    dfs(r, c + 1, visit, heights[r][c], heights);
    dfs(r, c - 1, visit, heights[r][c], heights);
}
};
```