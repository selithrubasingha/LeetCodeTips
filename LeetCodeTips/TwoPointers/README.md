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