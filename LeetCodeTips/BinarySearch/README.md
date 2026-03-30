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

## Koko Eating Bananas

_You are given an integer array piles where piles[i] is the number of bananas in the ith pile. You are also given an integer h, which represents the number of hours you have to eat all the bananas._

_You may decide your bananas-per-hour eating rate of k. Each hour, you may choose a pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, you may finish eating the pile but you can not eat from another pile in the same hour._

_Return the minimum integer k such that you can eat all the bananas within h hours._

- You can't actually see it's binary search ... but look , the maximum hours it can take is the len of the pile where the eating speed the value of the maximum item of the pile (X). 
- So the eating speed is bounded ! between (1 and X) .
- You will have to do the "How many hours ?" logic

```C++
            long long totalTime = 0;
            for (int p : piles) {
                totalTime += ceil(static_cast<double>(p) / k);
            }
```

here is the full code 

```C++
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1;
        int r = *max_element(piles.begin(), piles.end());
        int res = r;

        while (l <= r) {
            int k = (l + r) / 2;

            long long totalTime = 0;
            for (int p : piles) {
                totalTime += ceil(static_cast<double>(p) / k);
            }
            if (totalTime <= h) {
                res = k;
                r = k - 1;
            } else {
                l = k + 1;
            }
        }
        return res;
    }
};
```

## Find Minimum in Rotated Sorted Array

- Array is rotated ! it is super to find how many times it is rotated using linear search .
- But we need to do binary search . 

- This is not your typical left , right , mid binary search  . There is a few things we need to add. 

- Array is rotated ! it is super to find how many times it is rotated using linear search .
- But we need to do binary search . 

- This is not your typical left , right , mid binary search  . There is a few things we need to add. 

1. Every time we visit a mid index ... we set res and the min . 
2. Then if `nums[mid] < nums[l]` : `search left`; else : `search right`

```C++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0 ;
        int r = nums.size()-1;
        int res = nums[0];

        while (l<=r){
            if (nums[l]<nums[r]){
                res = min (res , nums[l]);
                break;
            }
            int mid = l + (r-l)/2;
            res = min(res,nums[mid]);

            if (nums[l]<=nums[mid]){
                
                l = mid+1;
            }else {
                r = mid-1;
            }
        }

        return res;
        
    }
};
```
