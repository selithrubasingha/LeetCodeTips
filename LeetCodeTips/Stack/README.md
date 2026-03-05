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

## Daily Temperatures

- This question feels like you need to have memory of previous days , when compared to the day we are lookig at . 
- It takes a while to understand that this is a stack question  .
- The main thing ... while we are iterating through the array . the answer array is not filled in teh same pace (speed)

- we need to use a Monotonically Decreasing Stack ... the stack is always decreasing 

Logic :
- While we are iterating through the array , 
  - if the item we are checking is smaller then the top of the stack . we just add it to teh stack 
  - if it is larger ! we clean out all the items at the top of the stack , where the items are smaller then than the item at hand. BUT WAIT ! while we are doing this , we update the answer array as well ... so to do that we need to store the index of the items in teh stack as well ... better use a pair .

```C++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        stack<pair<int, int>> stack; // pair: {temp, index}

        for (int i = 0; i < temperatures.size(); i++) {
            int t = temperatures[i];
            while (!stack.empty() && t > stack.top().first) {//first -> ][0]
                auto pair = stack.top();
                stack.pop();
                res[pair.second] = i - pair.second;
            }
            stack.push({t, i});
        }
        return res;
    }
};
```