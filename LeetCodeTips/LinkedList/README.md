- Linked list question have a unique way to solve them ... 
- We have to traverse through a linked list ...
- Traversing is done by node.next , node.prev (if doubly linked list)
- We're supposed to return a node most of the time .  

## Reverse Linked List

- reverse all the links in the list one node by node . 

```C++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr){
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;

        }

        return prev;
        
    }
};
```

  