/*
 
 CH2: Linked Lists
 
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>

using namespace std;

template<class T>
class ListNode{
public:
    T val;
    shared_ptr<ListNode> next;
    ListNode(T val) : val{val}, next{nullptr} {}
};

template<class T>
class Solution{
public:
    
    /*----------------------------------------------------------------------
     2.1 Write code to remove duplicates from an unosorted linked list.
     ----------------------------------------------------------------------*/
    void RemoveDups(shared_ptr<ListNode<T>> head){
        
        if (head==nullptr) { return; }
        if (head->next==nullptr) { return; }
        
        shared_ptr<ListNode<T>> prev=head, curr=head->next;
        set<T> seen{ head->val };
        
        while(curr){
            if (seen.find(curr->val)==seen.end()){
                seen.insert(curr->val);
            } else {
                prev->next=curr->next;
            }
            prev=curr;
            curr=curr->next;
        }
    }

    /*----------------------------------------------------------------------
     FOLLOW UP
     How would you solve this problem if a temporary buffer is not allowed?
     ----------------------------------------------------------------------*/
    void RemoveDups2(shared_ptr<ListNode<T>> head){
        
        if (head==nullptr) { return; }
        if (head->next==nullptr) { return; }
        
        shared_ptr<ListNode<T>> solo=head, prev=nullptr, curr=nullptr;
        while (solo && solo->next){
            prev=solo;
            curr=solo->next;
            while(curr){
                if (curr->val==solo->val){
                    prev->next = curr->next;
                }
                prev=curr;
                curr=curr->next;
            }
            solo=solo->next;
        }
    }
    
    /*----------------------------------------------------------------------
     2.2 Return Kth to Last: Implement an algorithm to find the kth to the last
     element of a singly linked list.
     ----------------------------------------------------------------------*/
    T GetKthToLast(shared_ptr<ListNode<T>> head, unsigned int k){
        
        if (head==nullptr) { throw out_of_range("linked list is empty"); }
        
        auto lead=head, follow=head;
        while (lead && lead->next && k > 0){
            lead=lead->next; k--;
        }
        if (k!=0){ throw out_of_range("k > size of the linked list"); }
        
        while(lead && lead->next){
            follow=follow->next; lead=lead->next;
        }
        return follow->val;
    }
    
    /*----------------------------------------------------------------------
     2.3 Delete Middle Node: Implement an algorithm to delete a node
     ----------------------------------------------------------------------*/
    void RemoveNode(shared_ptr<ListNode<T>> head, shared_ptr<ListNode<T>> remove){
        
        if (head==nullptr) { return; }
        if (head->next==nullptr) { return; }
        if (remove==nullptr) { return; }
        
        auto prev=head, curr=head->next;
        while (curr){
            if (curr.get()==remove.get()){
                prev->next=curr->next;
                return;
            }
            prev=curr;
            curr=curr->next;
        }
    }
    
    /*----------------------------------------------------------------------
     2.4 Partition: Write code to partition a linked list around a value x,
     such that all nodes less than x come before all nodes greater than or
     equal to x.  If x is contained within the list, the values of x only
     need to be after the elements less than x (see below).  The partition
     element x can appear anywhere in the "right partition"; it does not need
     to appear between the left and right partitions.
     ----------------------------------------------------------------------*/
    shared_ptr<ListNode<T>> Partition(shared_ptr<ListNode<T>> head, T x){
        
        shared_ptr<ListNode<T>> under_head=nullptr, under_tail=nullptr;
        shared_ptr<ListNode<T>> over_head=nullptr, over_tail=nullptr;
        
        auto itr=head;
        while (itr){
            auto curr=make_shared<ListNode<T>>(itr->val);
            if (itr->val < x){
                if (under_head==nullptr){
                    under_head=curr;
                    under_tail=under_head;
                } else {
                    under_tail->next=curr;;
                    under_tail=under_tail->next;
                }
            } else {
                if (over_head==nullptr){
                    over_head=curr;;
                    over_tail=over_head;
                } else {
                    over_tail->next=curr;
                    over_tail=over_tail->next;
                }
            }
            itr=itr->next;
        }
        under_tail->next=over_head;
        return under_head;
    }
    
    /*----------------------------------------------------------------------
     2.5 Sum Lists: You have two numbers represented by a linked list,
     where each node contains a single digit.  The digits are stored
     in reverse order, such that the 1's digit is at the head of the list.
     Write a function that adds the two numbers and returns the sum
     as a linked list.
     EXAMPLE
     Input: (7->1->6) + (5->9->2).  That is 617 + 295.
     Output: 2->1->9.  That is 912.
     ----------------------------------------------------------------------*/
    shared_ptr<ListNode<int>> SumLists(
        shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b){
        
        shared_ptr<ListNode<int>> sum=nullptr, sum_head=nullptr;
        bool carry=false;
        while (a || b){
            
            int curr=0;
            if (a){ curr += a->val; }
            if (b){ curr += b->val; }
            if (carry){
                curr+=1;
                carry=false;
            }
            if (curr > 10){
                curr %= 10;
                carry=true;
            }
            
            if (sum==nullptr){
                sum=make_shared<ListNode<int>>(curr);
                sum_head=sum;
            } else {
                sum->next=make_shared<ListNode<int>>(curr);
                sum=sum->next;
            }
            
            a=a->next;
            b=b->next;
        }
        
        if (carry){
            sum->next=make_shared<ListNode<int>>(1);
        }
        return sum_head;
    }
    
    /*----------------------------------------------------------------------
     FOLLOW UP
     Suppose the digits are stored in forward order.  Repeat the above problem.
     EXAMPLE
     Input: (6->1->7) + (2->9->5).  That is 617+295
     Output: 9->1->2.  That is 912.
     ----------------------------------------------------------------------*/
    shared_ptr<ListNode<int>> SumLists2(
        shared_ptr<ListNode<int>> a, shared_ptr<ListNode<int>> b){
        
        if (a==nullptr) { return b; }
        if (b==nullptr) { return a; }
        
        int sum=Int(a)+Int(b);
        if (sum==0) { return make_shared<ListNode<int>>(0); }
        
        shared_ptr<ListNode<int>> res=nullptr;
        while (sum > 0){
            auto head=make_shared<ListNode<int>>(sum % 10);
            head->next=res;
            res=head;
            sum/=10;
        }
        return res;
    }
    
    
    /*----------------------------------------------------------------------
     2.6 Palindrome: Implement a function to check if a linked list is a palindrome
     ----------------------------------------------------------------------*/
    bool IsPalindrome(shared_ptr<ListNode<T>> head){
        
        if (head==nullptr) { return true; }
        if (head->next==nullptr) { return true; }
        
        auto slow=head, fast=head;
        stack<T> first_half;
        do {
            first_half.push(slow->val);
            slow=slow->next;
            fast=fast->next->next;
        } while (fast && fast->next);
        
        if (fast){
            slow=slow->next; // skip past the middle of an odd length linked list
        }
        
        while (slow && slow->val==first_half.top()){
            first_half.pop();
            slow=slow->next;
        }
        return first_half.empty();
    }
    
    /*----------------------------------------------------------------------
     2.7 Intersection: Given two (singly) linked lists, determine if the two
     lists intersect.  Return the intersecting node.  Note that the intersection
     is defined based on reference, not value.  That is, if the kth node
     of the first linked list is the exact same node (by reference) as the jth node
     of the second linked list, then they are intersecting.
     ----------------------------------------------------------------------*/
    shared_ptr<ListNode<T>> IsIntersection(shared_ptr<ListNode<T>> a, shared_ptr<ListNode<T>> b){
        
        if (a==nullptr || b==nullptr) { return nullptr; }
        
        int lenA=1;
        shared_ptr<ListNode<T>> itrA=a;
        while (itrA->next) { lenA++; itrA=itrA->next; }
        
        int lenB=1;
        shared_ptr<ListNode<T>> itrB=b;
        while (itrB->next) { lenB++; itrB=itrB->next; }
        
        /*
         If there is an intersection between a and b,
         then the last node must be the same node
         */
        if (itrA.get() != itrB.get()) { return nullptr; }

        /*
         Move itr of the longer list forward,
         then iterate through both lists together
         in order to find the first intersecting node
         */
        itrA=a; while (lenA > lenB) { lenA--; itrA=itrA->next; }
        itrB=b; while (lenB > lenA) { lenB--; itrB=itrB->next; }
        while (itrA && itrB && itrA.get() != itrB.get()){
            itrA=itrA->next;
            itrB=itrB->next;
        }
        
        return itrA; // itrA.get()==itrB.get(), arbitrarily return itrA or itrB they are the same
    }
    
    /*----------------------------------------------------------------------
     2.8 Loop Detection: Given a circular linked link, implement an algorithm
     that returns the node at the beginning of the loop.
     DEFINITION
     Circular linked list: A (corrupt) linked list in which a node's next pointer
     points to an earlier node, so as to make a look in the linked list.
     EXAMPLE
     Input
     ----------------------------------------------------------------------*/
    bool IsLoop(shared_ptr<ListNode<T>> head){
        shared_ptr<ListNode<T>> slow=head, fast=head;
        
        while (slow && slow->next && fast && fast->next && fast->next->next){
            slow=slow->next; fast=fast->next->next;
            if (slow.get() == fast.get()) { return true; }
        }
        return false;
    }
    
    /*----------------------------------------------------------------------
     Helper Functions
     ----------------------------------------------------------------------*/
    shared_ptr<ListNode<T>> Generate(vector<T>&& v){
        
        if (v.empty()) { return nullptr; }
        
        auto head=make_shared<ListNode<T>>(v[0]);
        auto itr=head;
        for (int i=1; i < (int)v.size(); i++){
            itr->next=make_shared<ListNode<T>>(v[i]);
            itr=itr->next;
        }
        return head;
    }
    
    void Append(shared_ptr<ListNode<T>> lhs, shared_ptr<ListNode<T>> rhs){
        
        if (lhs==nullptr) { return; }
        if (rhs==nullptr) { return; }
        
        auto itr=lhs, res=lhs;
        while (itr && itr->next){
            itr=itr->next;
        }
        itr->next = rhs;
    }
    
    void Print(shared_ptr<ListNode<T>> head){
        string res="";
        while (head){
            res+=to_string(head->val) + ",";
            head=head->next;
        }
        res.pop_back();
        cout << res << endl;
    }
    
    
private:
    
    int Int(shared_ptr<ListNode<int>> head){
        int res=0;
        
        while(head){
            res *= 10;
            res += head->val;
            head=head->next;
        }
        return res;
    }
};

int main(int argc, const char * argv[]) {
    
    
    return 0;
}




