/*
 
 CCI CH02: Linked Lists
 
 */

#include <string>
#include <unordered_set>

using namespace std;

namespace RawPtr {

    struct ListNode{
        int val;
        ListNode* next;
        ListNode(int x) : val{x},next{nullptr} {}
    };
    
    bool isEqual(const ListNode* lhs, const ListNode* rhs) {
        while (lhs && rhs && lhs->val==rhs->val)
            lhs=lhs->next,rhs=rhs->next;
        return lhs==nullptr && rhs==nullptr;
    }
    
    ListNode* reverse(ListNode* head){
        if (!head) return nullptr;
        for (auto prev=head,curr=head->next; curr;){
            prev->next=curr->next;
            curr->next=head;
            head=curr;
            curr=prev->next;
        }
        return head;
    }
    
    //
    // Question 2.1 Remove Dups: Write code to remove duplicates from an unsorted linked list.
    //
    // Answer 2.1: use an unordered_set to track Visited values to be skipped by changing
    // prev->next to point towards on past the duplicate node.  Only move prev forward when
    // unique values of curr are found
    //
    class Solution_2_1 {
    public:
        ListNode* removeDups(ListNode* head) const {
            if (!head) return nullptr;
            unordered_set<int> V({head->val});
            for (auto prev=head,curr=prev->next; curr; curr=curr->next)
                if (V.insert(curr->val).second)
                    prev=curr;
                else
                    prev->next=curr->next;
            return head;
        }
    };
    
    //
    // Question 2.2 Return Kth to Last: Implement an algorithm to find the kth to last element
    // of a singly linked list
    //
    // Answer 2.2: Iterate through the list entirely to find the size of the list N.
    // Then iterate through the list again until the kth from last (N-K-1) index is found.
    // Return a pointer to the kth from last ListNode.  If K>N, then the kth from last
    // index doesn't exist, return nullptr.
    //
    class Solution_2_2 {
    public:
        ListNode* kthToLast(ListNode* head, int K) const {
            if (!head) return nullptr;
            int N=0;
            for (auto itr=head; itr; ++N,itr=itr->next); // no-op, just increment N
            if (K>N) return nullptr;
            int i=0;
            for (auto itr=head; itr; ++i,itr=itr->next)
                if (i==N-K-1)
                    return itr;
            return nullptr;
        }
    };
    
    //
    // Question 2.3 Delete Middle Node: Implement an algorithm to find the kth to last element
    // of a singly linked list.
    //
    // Answer 2.3: shift contents of list left by one, similiar to insertion sort, then
    // remove the final node by setting prev->next to nullptr when curr points at the last node.
    // To remove the very last node, the actual pointer to be modified needs to be passed in by reference.
    // This is a special corner-case use condition.
    //
    class Solution_2_3 {
    public:
        void deleteNode(ListNode*& node) const {
            if (!node) return;
            if (!node->next){ // special case to remove last node
                node=nullptr;
                return;
            }
            for (auto prev=node,curr=prev->next; curr; prev=curr,curr=curr->next){
                prev->val=curr->val;
                if (curr->next==nullptr)
                    prev->next=nullptr;
            }
        }
    };
    
    //
    // Question 2.4 Partition: Write code to partition a linked list around a value x,
    // such that all nodes less than x come before all nodes greater than or equal to x.
    // If x is contained within the list, the values of x only need to be after the elements
    // less than x (see below).  The partition element x can appear anywhere in the
    // "right partition"; it does not need to appear between the left and right partitions.
    //
    // EXAMPLE
    // Input:   3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition=5]
    // Oupput:  3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
    //
    // Answer 2.4: Create two lists, one to store values less than x, and the other
    // to store values greater than or equal to x.  Merge the lists and return the merged list.
    //
    class Solution_2_4 {
    public:
        ListNode* partition(ListNode* head, int pivot) const {
            ListNode *ans,
                *lt_head=new ListNode(-1),*gte_head=new ListNode(-1), // use sentinels
                *lt_tail=lt_head,*gte_tail=gte_head;
            for (auto itr=head; itr; itr=itr->next)
                if (itr->val < pivot)
                    lt_tail->next=new ListNode(itr->val),lt_tail=lt_tail->next;
                else
                    gte_tail->next=new ListNode(itr->val),gte_tail=gte_tail->next;
            ans=lt_head->next; // skip one past the sentinels while appending lists onto ans
            lt_tail->next=gte_head->next;
            return ans;
        }
    };
    
    //
    // Question 2.5 Sum Lists: You have two numbers represented by a linked list,
    // where each node contains a single digit.  The digits are stored in reverse order,
    // such that the 1's digit is at the head of the list.  Write a function
    // that adds the two numbers and returns the sum as a linked list.
    //
    // EXAMPLE
    // Input:  ( 7 -> 1 -> 6 ) + ( 5 -> 9 -> 2).  That is, 617 + 295
    // Output: ( 2 -> 1 -> 9 ).  That is, 912
    //
    // FOLLOW UP
    // Support the digits are stored in forward order.  Repeat the above problem.
    //
    // EXAMPLE
    // Input:  ( 6 -> 1 -> 7 ) + ( 2 -> 9 -> 5).  That is, 617 + 295
    // Output: ( 9 -> 1 -> 2 ).  That is, 912
    //
    // Answer 2.5: use the same logic to add linked lists, use optional param "rev"
    // to reverse the input and output
    //
    class Solution_2_5 {
    public:
        ListNode* sumLists(ListNode* a, ListNode* b, bool rev=false) const {
            if (rev){
                a=reverse(a);
                b=reverse(b);
            }
            ListNode* ans=new ListNode(-1); // use sentinel
            auto ians=ans,ia=a,ib=b;
            int carry=0;
            for (int sum=0; ia && ib; carry=sum>9,ia=ia->next,ib=ib->next,ians=ians->next){
                sum=ia->val+ib->val+carry;
                ians->next=new ListNode(sum%10);
            }
            for(int sum=0; ia; carry=sum>9,ia=ia->next,ians=ians->next){ // a is longer
                sum=ia->val+carry;
                ians->next=new ListNode(sum%10);
            }
            for(int sum=0; ib; carry=sum>9,ib=ib->next,ians=ians->next){ // b is longer
                sum=ib->val+carry;
                ians->next=new ListNode(sum%10);
            }
            if (carry) ians->next=new ListNode(1);
            return (rev) ? reverse(ans->next) : ans->next;
        }
    };
    
    //
    // Question 2.6 Palindrome: Implement a function to check if a linked list is a palindrome.
    //
    // Answer 2.6: Reverse the linked list, and check if the linked lists are equal
    //
    class Solution_2_6 {
    public:
        bool isPalindrome(ListNode* a) const {
            auto b=reverse(a);
            for (auto ia=a,ib=b; ia && ib; ia=ia->next,ib=ib->next) if (ia->val!=ib->val)
                return false;
            return true;
        }
    };
    
    //
    // Question 2.7 Intersection: Given two (singly) linked lists, determine if the two lists interect.
    // Return the intersecting node.  Note that the intersection is defined based on reference, not value.
    // That is, if the kth node of the first linked list is the exact same node (by reference)
    // as the jth node of the second linked list, then they are intersecting.
    //
    // Answer 2.7: If additional data structures are allowed, then iterate through the first linked list
    // and store visited pointers in a set.  Then iterate through the second linked list and check if any nodes
    // have been visisted.  If so, then return the first visited node in common.
    //
    // If additional data structures are not allowed, then iterate through each list until the end.
    // Check if the last node from each list are the same.  If so, then the lists itersect.
    // Keep track of the lengths of each linked list.  Let K be the difference between these lengths.
    // Move the iterator of the longer list forward by K.  Then iterate through each list and return
    // the first common node.
    //
    class Solution_2_7 {
    public:
        ListNode* intersection(ListNode* a, ListNode* b, bool data_structs_allowed=true) const {
            if (data_structs_allowed){
                unordered_set<ListNode*> V;
                for (auto itr=a; itr; itr=itr->next)
                    V.insert(itr);
                for (auto itr=b; itr; itr=itr->next) if (V.find(itr)!=V.end())
                    return itr;
                return nullptr;
            }else{
                int lena=0,lenb=0;
                auto ia=a,ib=b;
                for (; ia && ia->next; ++lena,ia=ia->next);
                for (; ib && ib->next; ++lenb,ib=ib->next);
                if (ia->next==ib->next){
                    ia=a,ib=b;
                    for (; lena > lenb; --lena,ia=ia->next);
                    for (; lenb > lena; --lenb,ib=ib->next);
                    for (; ia && ib; ia=ia->next,ib=ib->next) if (ia==ib)
                        return ia;
                }
                return nullptr;
            }
        }
    };
    
    //
    // Question 2.8 Loop Detection: Given a circular linked list, implement an algorithm
    // that returns the node at the beginning of the loop.
    //
    // DEFINITION
    // Circular linked list: A (corrupt) linked list in which a node's next pointer
    // points to an earlier node, so as to make a loop in the linked list
    //
    // EXAMPLE
    // Input:  A -> B -> C -> D -> E -> C
    //
    // Answer 2.8: if data structures are allowed, then store visited list nodes,
    // and return true if a previously visited node is visited again.  Return false otherwise.
    //
    // If data structures are not allowed, then iterate through the linked list
    // using "s"low and "f"ast pointers.  Slow moves ahead by one node at a time.
    // Fast moves ahead by two nodes at a time.  Evenually if there is a loop
    // then slow and fast will meet up, return true for this case.  Otherwise the list
    // will be exhausted, return false.
    //
    class Solution_2_8 {
    public:
        bool hasLoop(ListNode* head, bool data_structs_allowed=true) const {
            if (!head || !head->next) return false;
            if (data_structs_allowed){
                unordered_set<ListNode*> V;
                for (auto itr=head; itr; itr=itr->next) if (!V.insert(itr).second)
                    return true;
                return false;
            }else{
                for (auto s=head,f=head->next; s && f && f->next; s=s->next,f=f->next->next) if (s==f)
                    return true;
                return false;
            }
        }
    };
}
