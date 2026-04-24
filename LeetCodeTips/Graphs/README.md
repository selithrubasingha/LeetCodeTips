
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

## Surrounded regions

- Just like the previous question . we perform dfs or the border slots . but we change them to 'V' s . (anything other that '0' and 'x' will do ) . then afterwards we change the O s to X s and V s to O s again !

```c++
class Solution {
public:

    void dfs(int i,int j,vector<vector<char>>& board){
        int n = board.size();
        int m = board[0].size();
        if (i<0 || j<0 || i>=n || j >= m || board[i][j]!='O'){
            return;
        }

        board[i][j] = 'V';
        dfs(i+1,j,board);
        dfs(i,j+1,board);
        dfs(i-1,j,board);
        dfs(i,j-1,board);
    }
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        for (int i = 0; i<n ; i++){
            dfs(i,0,board);
            dfs(i,m-1,board);
        }

        for (int j = 0; j<m ; j++){
            dfs(0,j,board);
            dfs(n-1,j,board);
        }

        for (int i = 0; i<n; i++){
            for (int j = 0; j<m  ; j++){
                if (board[i][j]=='V'){
                    board[i][j]='O';
                }

                else if (board[i][j]=='O')
                    board[i][j]='X';
            }
        }

        
        
    }
};
```
## COurse Shedule

- we do DFS ... but need to know if the curr node we are checking is visited WITHIN that set current set of recursive steps . 
- to do this when we finish the for loop , we need to set the curr visited node to false . 
- Also once the node is visited and there is no problem completing that current course in the node . we need to set the `adj = {}` .To avoid repeated work   .

```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        int n = prerequisites.size();
        for (const auto& pair : prerequisites){
            int u = pair[0];
            int v = pair[1];

            adj[u].push_back(v);
        }
        vector<bool> visited(numCourses,false);
        for (int i = 0 ; i <numCourses; i++ ){
            if (!dfs(i,adj,visited)) return false;
        }

        return true;

        
        
    }

    bool dfs(int node , vector<vector<int>>& adj, vector<bool> & visited){
        if (visited[node]==true) return false;

        visited[node] = true;
        for (int n : adj[node]){
            if (dfs(n,adj,visited)==false) return false;
        }

        visited[node]  = false;
        adj[node]={};
        return true;





    }
};
```

## COurse shedule 2

- they want us to output the path itself , for that we use a global like output vector to store the answer , and a visited and cycle vector to keep track of visited nodes and the visited with the cycle nodes .  

```c++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
    vector<vector<int>> adj(numCourses);
        int n = prerequisites.size();
        for (const auto& pair : prerequisites){
            int u = pair[0];
            int v = pair[1];

            adj[u].push_back(v);
        }
        vector<bool> cycle(numCourses,false);
        vector<bool> visited(numCourses,false);
        vector<int> output;
        for (int i = 0 ; i <numCourses; i++ ){
            if (!dfs(i,adj,cycle,visited,output)) return {};
        }

        return output;

        
        
    }

    bool dfs(int node , vector<vector<int>>& adj, vector<bool> & cycle , vector<bool> & visited , vector<int>& output){
        if (cycle[node]==true) return false;
        if (visited[node]==true) return true;

        cycle[node] = true;
        for (int n : adj[node]){
            if (dfs(n,adj,cycle,visited , output)==false) return false;
        }

        cycle[node]  = false;
        visited[node] = true;
        adj[node]={};
        output.push_back(node);
        return true;





    }
};

```