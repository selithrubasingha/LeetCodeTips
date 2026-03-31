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

## Search in Rotated Sorted Array

_You are given an array of length n which was originally sorted in ascending order. It has now been rotated between 1 and n times. For example, the array nums = [1,2,3,4,5,6] might become:_

_[3,4,5,6,1,2] if it was rotated 4 times._
_[1,2,3,4,5,6] if it was rotated 6 times._
_Given the rotated sorted array nums and an integer target, return the index of target within nums, or -1 if it is not present._

_You may assume all elements in the sorted rotated array nums are unique,_

_A solution that runs in O(n) time is trivial, can you write an algorithm that runs in O(log n) time?_


- The easiest way to think about this is ... instead of two scenarios like in normal binary seach . this one has 4 scenarios ... And we have to each provide where to search for each of the 4 cases . 
- first we check whether mid is in the left sorted portion or the right sorted portion 
- Next , we determine where target is comparing to nums[mid] and nums[l] and then do the logic . 

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0 ;
        int r= nums.size()-1;

        while (l<=r){
            
            
            int mid = l + (r-l)/2;

            if (target == nums[mid]) return mid;

            if (nums[l]<=nums[mid]){
                if (target>=nums[l] && target<nums[mid]) r = mid-1;
                else l = mid+1;

            }else{
                if (nums[mid]<target && target<=nums[r]) l = mid+1;
                else r = mid-1;

            }

        }

        return -1;

        
    }
};
```

## Time Based Key-Value Store

- Were asked to build a map which has two items as values ... which is an timestammp and the string value 
- a key can contain multiple values , so for diffrent timestamps , different string vals (THe value is actually a list in that case)
- The binary search can be added when finding the exact timestamp outof the list of values in a certain key . 

(There is nothing special about this peoblem other than that)

```C++

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> keyStore;

public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        keyStore[key].push_back({timestamp, value});
    }

    string get(string key, int timestamp) {
        auto& values = keyStore[key];
        int left = 0, right = values.size() - 1;
        string result = "";

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (values[mid].first <= timestamp) {
                result = values[mid].second;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return result;
    }
};
```