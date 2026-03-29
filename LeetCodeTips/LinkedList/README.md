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

## Linked list Cycle

### The legendary Floyd's tortoise and hare algorithm

* Imagine two racers in a track , ONe is fast and the other is slow 
* if they start at the same place in the circular track and have the same speed 
* It is garanteed that the fast guy will meet the slow guy again ... because "he so fast that he made a gap of 1 circular track !"
* That is what this algorithm does ... It has two pointers fast and slow , slow is incremented once and fast is incremented twice . if the Linked list has a cycle it is guranteed that slow node will be equal to fast node at some point . 
* If the fast node reached null ... That means the linked list was not circular.

```C++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while ( fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) return true;
        } 

        return false;

        
    }
};
```

## Reorder list

*You are given the head of a singly linked-list. The list can be represented as:*


`_L0 → L1 → … → Ln - 1 → Ln_`

_Reorder the list to be on the following form:_

`_L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …_`

_You may not modify the values in the list's nodes. Only nodes themselves may be changed._

- Bruh ... you basically need to use the knowledge of the 3 questions before 
- first , use tortoisse and hare to find the middle of the linked list
- second , cut the linked list in half and reverse the second linked list
- third , merge the two linked lists .

```C++
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        //find the middle (using tortoise and hare)
        while ( fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        } 

        ListNode* second = slow->next;

        ListNode* first = head;
        ListNode* prev = slow->next =nullptr;

        //reversing  the second linked list
        while (second){
            ListNode* nxt = second->next;
            second->next = prev;
            prev = second;
            second = nxt;

        }

        
        //merging 
        second = prev;
        while (second != nullptr) {
            ListNode* tmp1 = first->next;
            ListNode* tmp2 = second->next;
            first->next = second;
            second->next = tmp1;
            first = tmp1;
            second = tmp2;
        }
   
    }
};
```

## Remove a Node from the end of a list

- The problem with linked lists is ... we don't know what the length of a linked list is , so how do we remove from the end of the node ?

- Well , it is quite a common pattern to use the tortoise and hare type pointers to do the traversal .

- We shift the fast pointer n times while the slow pointer is at the head ... and increment the pointers until the fast pointer becomes NULL 

- but we do not need to reach the node that is to delete! but we need to reach the one before it ! 

- For this we use the legendary technique known as the dummy node technique , which get rid of edge cases also .

```C++

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {

        ListNode dummy(0);
        dummy.next = head;

        int count = 0 ;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;


        while (count < n){
            fast = fast->next;
            count++;
            
        }

        while (fast && fast->next){
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* newnxt = slow->next ? slow->next->next : slow->next;;
        slow->next = newnxt;

        return dummy.next;
        
    }
};
```

## Copy List with Random Pointer

_A linked list of length n is given such that each node contains an additional random pointer, which could point to any node in the list, or null.Construct a deep copy of the list._

- Just make the nodes first . and map them into a hashmap ... them connect them around all the next and random pointers !

```C++

class Solution {
public:
    Node* copyRandomList(Node* head) {

        unordered_map<Node* , Node* > mapper;
        mapper[NULL] = NULL;

        Node* curr = head;

        while (curr!=NULL){
            Node* copy = new Node(curr->val);
            mapper[curr] = copy;
            curr = curr->next;
        }

        curr = head;

        while (curr!=NULL){
            Node* copy = mapper[curr];
            copy->next = mapper[curr->next];
            copy->random = mapper[curr->random];
            curr = curr->next;
        }

        return mapper[head];

        
    }
};
```

## Add Two Numbers

_You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list._

- Dude ! remember how we used to calculate additions in pre school ? yeah ! we do the exact same logic here ... they even made it easier for us by giving the linked lists reversed !

```C++
class Solution {
public:
    Node* copyRandomList(Node* head) {

        unordered_map<Node* , Node* > mapper;
        mapper[NULL] = NULL;

        Node* curr = head;

        while (curr!=NULL){
            Node* copy = new Node(curr->val);
            mapper[curr] = copy;
            curr = curr->next;
        }

        curr = head;

        while (curr!=NULL){
            Node* copy = mapper[curr];
            copy->next = mapper[curr->next];
            copy->random = mapper[curr->random];
            curr = curr->next;
        }

        return mapper[head];

        
    }
};
```

## Find the Duplicate Number

_Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive._

_There is only one repeated number in nums, return this repeated number._

- This might be the most uintuitive hardest question in a linked list 

- The thing is ... this vector nums acts like a liked list 
    - the index is like the val 
    - the value inside the nums is like the index of the next node
    - we can use the tortoise and hare algorithm to meet at some palce (let's say P)

- Here is the unintuitive part ! the if we travel from P and from the start at the same pace with two pointers . 
- The two pointers meet at some place ... THE PLACE WHERE THEY MEET IS THE PLACE WHERE THE DUPLICATE IS !!!
(don't ask me how it's just math you can prove it yourself)

```C++
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;

        while (true){
            fast = nums[nums[fast]];
            slow = nums[slow];

            if (fast==slow){
                break;
            }
        }

        int slow2 = 0;

        while (true){
            slow = nums[slow];
            slow2 = nums[slow2];
            if (slow == slow2){
                return slow;
            }
        }
        
    }
};
```
  