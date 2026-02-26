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

## Merging two sorted linked lists

- In c++ to create a new node , there is some weird syntax I don't know why ?
```C++

ListNode dummy(0);
ListNode* node = &dummy;

```

- The rest of the code is pretty self explanatory . 

```C++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode dummy(0);
        ListNode* node = &dummy;

        while (list1 && list2){
            if (list1->val < list2->val){
                node->next = list1;
                list1  = list1->next;
            }else{
                node->next = list2;
                list2  = list2->next;
            }

            node = node->next;

        }

        if (list1) {
            node->next = list1;
        } else {
            node->next = list2;
        }

        return dummy.next;
        
    }
};
```



  