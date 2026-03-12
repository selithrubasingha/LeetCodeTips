## Stacks

## Valid Parenthesis

* Basically the oldest trick in the game ... when a bracket is open . it should be closed when iterating throughout the bracket array . 

```C++
class Solution {
public:
    bool isValid(string s) {
        std::stack<char> stack;
        std::unordered_map<char, char> closeToOpen = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        for (char c : s) {
            if (closeToOpen.count(c)) {
                if (!stack.empty() && stack.top() == closeToOpen[c]) {
                    stack.pop();
                } else {
                    return false;
                }
            } else {
                stack.push(c);
            }
        }
        return stack.empty();
    }
};
```

## Min Stack

*  A normal generic stack . nothing particularly interesting here...

```c++
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

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```