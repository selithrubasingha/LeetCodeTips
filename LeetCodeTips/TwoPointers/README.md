## Valid Palindrome

* Finding a single palindrome ? use Two pointers from the edges of both sides of the two strings and traverse to the middle . 

```C++
class Solution {
public:
    bool isPalindrome(string s) {
        int l = 0;
        int r = s.length() - 1;

        while (l < r) {
            // Safety brake: l < r
            while (l < r && !isalnum(s[l])) {
                l++;
            }
            
            // Safety brake: l < r
            while (l < r && !isalnum(s[r])) {
                r--;
            }

            // Once we have valid alphanumeric characters, compare them
            if (tolower(s[l]) != tolower(s[r])) {
                return false;
            }

            l++;
            r--;
        }

        return true;
    }
};
```

## Two Sum II : array is sorted

* Even more easier use the same technique as the valid palindrome two pointer technique

```C++
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int current_sum = numbers[left] + numbers[right];
            
            if (current_sum == target) {
                // Return 1-indexed positions
                return {left + 1, right + 1};
            } 
            else if (current_sum < target) {
                // Sum is too small, need a larger number
                left++;
            } 
            else {
                // Sum is too large, need a smaller number
                right--;
            }
        }
        
        // The problem guarantees exactly one solution, 
        // so we theoretically never reach here.
        return {}; 
    }
};
```

## 3Sum

* the target is now 0 . but now there are 3 values ! So what should we do ? 
* We need to iterate through the array with a pointer and then for each iteration apply the 2sum code ! we set the target as `-value3` cause `value1 + value2 + value3 = 0`

```C++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // Step 1: Sort the array. This is CRUCIAL for avoiding duplicates easily.
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; i++) {
            // Optimization: If the number is the same as the one before, skip it!
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int target = nums[i];
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = target + nums[left] + nums[right];

                if (sum < 0) {
                    left++; // We need a bigger number
                } else if (sum > 0) {
                    right--; // We need a smaller number
                } else {
                    // Found a triplet!
                    result.push_back({target, nums[left], nums[right]});
                    
                    // Skip duplicates for the second number
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for the third number
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                }
            }
        }
        return result;
    }
};
```

## Container with the most Rain Water

- `l = 0 ; r = n-1; while l<r ` type question . 
- we alway decre.. or increment the short height one . it will always work in this case

```C++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0 ;
        int r = height.size()-1;
        int width;
        int area = 0;


        while (l<r){
            width = r-l;

            area = max(area , width * min(height[l],height[r]));

            if (height[l]<height[r])
                l++;
            else
                r--;


        }

        return area;
        
    }
};
```

## Trapping Rain water

- Might be the hardest question in the history of the universe ? 
- This isn't necessarily a two pointer problem ... it is prefix suffix problem IMO .

### Method 01

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if (n == 0) {
            return 0;
        }

        vector<int> leftMax(n);
        vector<int> rightMax(n);

        leftMax[0] = height[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], height[i]);
        }

        int res = 0;
        for (int i = 0; i < n; i++) {
            res += min(leftMax[i], rightMax[i]) - height[i];
        }
        return res;
    }
};
```
- we do this because to know how much water can be stored we need to know in advance whether there are walls at the right of left .

## Method 02
- This uses the same logic but also does neat tricks to make the space complexity o(!) using two pointers .

```C++
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) {
            return 0;
        }
        int l =0;
        int r = height.size()-1;
        int leftMax = height[l];
        int rightMax = height[r];
        int res=0;

        while (l<r){
            if (leftMax<rightMax){
                l++;
                leftMax=max(leftMax , height[l]);
                res+= leftMax - height[l];
            }else{
                r--;
                rightMax=max(rightMax , height[r]);
                res+= rightMax - height[r];

            }
        }


        return res;
        
    }
};
```
