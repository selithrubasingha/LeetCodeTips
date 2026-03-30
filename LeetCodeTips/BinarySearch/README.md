## Binary Search

- The most basic form of the legendary binary search

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0; 
        int r= nums.size()-1;

        while (l<=r){
            int mid = l+(r-l)/2;

            if (nums[mid]<target)
                l = mid +1;

            else if (nums[mid]>target)
                r = mid -1;
            else return mid;

            
        }

        

        return -1;

        
    }
};
```
## 2D Matrix

- Binary search ... but we do it two times ... cause it's a two dimensional array !

```C++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int l = 0;
        int r = matrix.size()-1;
        int cols = matrix.size();
        int mid;

        while (l<=r){
            mid = l + (r-l)/2;

            if (matrix[mid][matrix[0].size()-1]<target)
                l = mid +1;

            else if (matrix[mid][0]>target)
                r = mid -1;
            else break;
        }

        int inner_l = 0;
        int inner_r = matrix[0].size()-1;

        while (inner_l<=inner_r){
            int mid_mid = inner_l+(inner_r-inner_l)/2;

            if (matrix[mid][mid_mid]<target)
                inner_l = mid_mid +1;

            else if (matrix[mid][mid_mid]>target)
                inner_r = mid_mid-1;
            else return 1;

            
        }

        return 0;

        
    }
};
```
