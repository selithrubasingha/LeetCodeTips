
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

## 