
## Binary Search

- remember ! it's `l<=r`.
- Based on my experience these the are the types of questions
    - 2D binary search
    - rotated array Binary Search (find an element or find the minimum)
    - normal search algo's with 3 or more for loops but the last loop should be binary search . 
    -  normal search algo's but  should be binary search .
    - two array related stuff like median or 2 sorted arrays . 
- normally we have 3 if cases ... `mid<target`,`mid>target`,`mid=target`.
- But in some cases we might get `mid<=target`,`mid1>target` . maybe to update the variable or answer while searching through the array . 

## Stack 

- Common pattern 
    1. you have an array and you loop through it with a for loop 
    2. you compare `stack.top()` with the item and based on that add to the stack or update the answer . 
    3. inside the for loop , you could either use a if statement (simple) or a while loop (complex) .
    4. notice that in the inner for or while loop . we first check `!stack.empty()`.
    5. most medium problems use monotonously increasing or decreasing stacks .pattern !

- Do the largest rectangle in a histogram problem again . 