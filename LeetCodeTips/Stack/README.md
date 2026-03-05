## Valid Parenthesis

- Ah ! the age old most popular question asked from a stack . It  is quite obvious that we should use a stack for this .

**Stack problem code writing technique :** `if stack and stack.top== ...` code first and then `stack.append`.This style of code writing is common in stack questions

```C++
class Solution {
public:
    bool isValid(string s) {

        stack<char> stack;
        
        unordered_map<char , char> closeToOpen = {
            {')','('},
            {']','['},
            {'}','{'}
        };

        for (char c : s ){
            if (closeToOpen.count(c)){
                if (!stack.empty() && stack.top()==closeToOpen[c]){
                    stack.pop();
                }else{
                    return false;
                }
            }else{
                stack.push(c);
            }
        }

        return stack.empty();
    }
};
```

## Min Stack

- A simple minstack implementation 

```C++
class MinStack {

private:
    vector<int> buffer;
public:
    MinStack() {
    }
    
    void push(int val) {
        buffer.push_back(val);
        
    }
    
    void pop() {
        buffer.pop_back();
    }
    
    int top() {
        return buffer.back();
    }
    
    int getMin() {
        return *std::min_element(buffer.begin(), buffer.end());
    }
};
```