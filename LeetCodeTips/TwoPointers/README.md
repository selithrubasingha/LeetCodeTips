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