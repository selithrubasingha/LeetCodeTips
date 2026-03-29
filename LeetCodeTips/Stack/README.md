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

## Evaluate Reverse Polish Notation

- just use a stack ... when iterating through the list , if an int is found , add it to the stack and if the operator is found , pop two items ... perform the operation and add the answer to the stack again .
- The answer is the final value in the stack . 

```C++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        int ans ;

        for (string& token : tokens){
            

            if (token=="+"){
                int x = st.top();
                st.pop();
                int y = st.top();
                st.pop();
                st.push(x+y);
            }else if (token=="-"){
                int x = st.top();
                st.pop();
                int y = st.top();
                st.pop();
                st.push(y-x);
            }else if (token=="*"){
                int x = st.top();
                st.pop();
                int y = st.top();
                st.pop();
                st.push(x*y);
            }else if (token=="/"){
                int x = st.top();
                st.pop();
                int y = st.top();
                st.pop();
                st.push(y/x);
            }else{
                st.push(stoi(token));
            }


            
        }

        return st.top();
        
        
    }
};
```

## Daily temperatures 

- This is a interesting question . The trick is to use a monotincally decreasing stack (the items on the top of the stack are always smaller)
- when we iterate through the list ... if we meet a larger number ... then we pop stuff from stack while simultaneiously updating the answer on the answer vector . and once that large number can be added on the top of the stack  , then it is added
- You must remember that filling the answer vector with answers in each indices is not always linear ... that is what makes this question special .

```C++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        
        stack<pair<int,int>> st; // monotonically decreasing stack !
        int n = temperatures.size();
        vector<int> ans(n,0);

        for (int i = 0 ; i < n ; i++){
            int item = temperatures[i];

            
                //while item is larger than the top of the stack
                //update the answer and pop from the stack !

                while ( !st.empty() && item> st.top().first){
                    ans[st.top().second] = i-st.top().second;
                    st.pop();
                }

                st.push({item,i});
            
        }

        return ans;
        
    }
};
```

## Car Fleet

_There are n cars at given miles away from the starting mile 0, traveling to reach the mile target._

_You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour._

_A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car._

_A car fleet is a single car or a group of cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet._

_If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet._

_Return the number of car fleets that will arrive at the destination._

- what type of stack should we use for this ? we should use a stack to store the time every fleet of cars comes .... so that stack will become a monotonically increasing stack of times ! 
- Once you read the logic ... you'll remember what to do .

```C++
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {

        vector<pair<int,int>> input ;

        int n = position.size();

        for (int i=0; i<n ; i++){
            input.push_back({position[i],speed[i]});
        }

        sort(input.rbegin(),input.rend());

    //my way
        stack<double> st ;
        st.push((double)(target - input[0].first) / input[0].second);

        for (int i = 1; i<n ; i++){
            double time = (double)(target - input[i].first) / input[i].second;

            if (st.top()<time){
                st.push(time);
            }
        }
    // my way

        return st.size();

        
        
    }
};

```

- Instead of `my way`. you can also do this ...

```C++
        for (auto& p : pair) {
                    stack.push_back((double)(target - p.first) / p.second);
                    if (stack.size() >= 2 &&
                        stack.back() <= stack[stack.size() - 2])
                    {
                        stack.pop_back();
                    }
                }
```

## Largest Rectangle in a Histogram

- This is similar to Daily temperature in a sense that theMaxArea calculation is not done incrementally (linearly?) . 
- stack stores the index and the heght ... when items are poped that is when the maxArea is calculated ... this does not index store the current index but the index extends backwards . 

```C++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {

        heights.push_back(0);
        int maxArea = 0;
        stack<pair<int,int>> st;

        int n= heights.size();

        for (int i = 0 ; i <n ; i ++){
            int start = i;

            int h = heights[i];

            while (!st.empty() && st.top().second>h){
                int index = st.top().first;
                int height = st.top().second;
                st.pop();
                maxArea = max(maxArea , (i-index)*height);
                start = index;
            }

            st.push({start,h});

        }

        return maxArea;
        
    }
};
```


# Common patterns I noticed

- most questions : structure is ,
    1. you have list , you looop through it
    2. add or stuff to your sttack while looping
    3. most often we check if the current num were looking is either greater or larger than the top of the stack value and we perform the logic .
    4. modification of this pattern is there for certain problems

