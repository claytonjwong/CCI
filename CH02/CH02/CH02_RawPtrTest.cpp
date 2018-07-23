/*
 
 CCI CH02 Unit Tests
 
 */

#include "TestHarness.h"
#include "CH02_RawPtr.hpp"

//********************************************************************************

// Solution 2.1

using namespace RawPtr;

TEST(removeDupsSameList,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(4);
    
    ListNode* orig=head;
    solution.removeDups(head);
    CHECK(isEqual(orig,head));
}

TEST(removeDupsLastDup,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.removeDups(head);
    CHECK(isEqual(ans,head));
}

TEST(removeDupsFirstDup,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(1);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.removeDups(head);
    CHECK(isEqual(ans,head));
}

TEST(removeDupsFromMiddle,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.removeDups(head);
    CHECK(isEqual(ans,head));
}

TEST(removeDupsFromMiddle2,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(1);
    head->next->next->next=new ListNode(2);
    head->next->next->next->next=new ListNode(3);
    head->next->next->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.removeDups(head);
    CHECK(isEqual(ans,head));
}

TEST(removeDupsFromMiddle3,Solution_2_1){
    Solution_2_1 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(2);
    head->next->next->next->next=new ListNode(3);
    head->next->next->next->next->next=new ListNode(3);
    head->next->next->next->next->next->next=new ListNode(1);
    head->next->next->next->next->next->next->next=new ListNode(2);
    head->next->next->next->next->next->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.removeDups(head);
    CHECK(isEqual(ans,head));
}

//********************************************************************************

// Solution 2.2

TEST(kthToLast,Solution_2_2){
    Solution_2_2 solution;
    ListNode* head=new ListNode(4);
    head->next=new ListNode(3);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(1);
    head->next->next->next->next=new ListNode(0);
    for (int k=0; k<5; ++k)
        CHECK(solution.kthToLast(head,k)->val==k);
}

TEST(kthToLast__KtooBig,Solution_2_2){
    Solution_2_2 solution;
    ListNode* head=new ListNode(4);
    head->next=new ListNode(3);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(1);
    head->next->next->next->next=new ListNode(0);
    int k=5;
    CHECK(solution.kthToLast(head,k)==nullptr);
}

//********************************************************************************

// Solution 2.3

TEST(removeNodeMiddle,Solution_2_3){
    Solution_2_3 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(69);
    head->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.deleteNode(head->next->next);
    CHECK(isEqual(ans,head));
}

TEST(removeNodeFirst,Solution_2_3){
    Solution_2_3 solution;
    
    ListNode* head=new ListNode(69);
    head->next=new ListNode(1);
    head->next->next=new ListNode(2);
    head->next->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.deleteNode(head);
    CHECK(isEqual(ans,head));
}

TEST(removeNodeLast,Solution_2_3){
    Solution_2_3 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(69);
    
    ListNode* ans=new ListNode(1);
    ans->next=new ListNode(2);
    ans->next->next=new ListNode(3);
    
    solution.deleteNode(head->next->next->next);
    CHECK(isEqual(ans,head));
}

//********************************************************************************

// Solution 2.4

TEST(partitionPivotExists,Solution_2_4){
    Solution_2_4 solution;
    ListNode* head=new ListNode(3);
    head->next=new ListNode(5);
    head->next->next=new ListNode(8);
    head->next->next->next=new ListNode(5);
    head->next->next->next->next=new ListNode(10);
    head->next->next->next->next->next=new ListNode(2);
    head->next->next->next->next->next->next=new ListNode(1);
    
    int pivot=5;
    auto res=solution.partition(head,pivot);
    
    int cnt=0;
    auto itr=res;
    for (; itr && itr->val < pivot; itr=itr->next)
        ++cnt;
    CHECK_EQUAL(cnt,3);
    
    cnt=0;
    for (; itr && itr->val >= pivot; itr=itr->next)
        ++cnt;
    CHECK_EQUAL(cnt,4);
}

//********************************************************************************

// Solution 2.5

TEST(sumLists,Solution_2_5){
    Solution_2_5 solution;
    
    ListNode* a=new ListNode(7);
    a->next=new ListNode(0);
    a->next->next=new ListNode(6);
    
    ListNode* b=new ListNode(5);
    b->next=new ListNode(9);
    b->next->next=new ListNode(3);
    
    ListNode* ans=new ListNode(2);
    ans->next=new ListNode(0);
    ans->next->next=new ListNode(0);
    ans->next->next->next=new ListNode(1);
    
    auto res=solution.sumLists(a,b);
    
    CHECK(isEqual(ans,res));
}

TEST(sumListsReverse,Solution_2_5){
    Solution_2_5 solution;
    
    ListNode* a=new ListNode(6);
    a->next=new ListNode(1);
    a->next->next=new ListNode(7);
    
    ListNode* b=new ListNode(2);
    b->next=new ListNode(9);
    b->next->next=new ListNode(5);
    
    ListNode* ans=new ListNode(9);
    ans->next=new ListNode(1);
    ans->next->next=new ListNode(2);
    
    auto res=solution.sumLists(a,b,true);
    
    CHECK(isEqual(ans,res));

}
    
TEST(sumListsDiffLen,Solution_2_5){
    Solution_2_5 solution;
    
    ListNode* a=new ListNode(6);
    
    ListNode* b=new ListNode(4);
    b->next=new ListNode(3);
    
    ListNode* ans=new ListNode(0);
    ans->next=new ListNode(4);
    
    auto res1=solution.sumLists(a,b);
    CHECK(isEqual(ans,res1));
    
    auto res2=solution.sumLists(b,a);
    CHECK(isEqual(ans,res2));
}
    
    
TEST(sumListsDiffLenAndCarry,Solution_2_5){
    Solution_2_5 solution;
    
    ListNode* a=new ListNode(1);
    
    ListNode* b=new ListNode(9);
    b->next=new ListNode(9);
    b->next->next=new ListNode(9);
    b->next->next->next=new ListNode(9);
    
    ListNode* ans=new ListNode(0);
    ans->next=new ListNode(0);
    ans->next->next=new ListNode(0);
    ans->next->next->next=new ListNode(0);
    ans->next->next->next->next=new ListNode(1);
    
    auto res1=solution.sumLists(a,b);
    CHECK(isEqual(ans,res1));
    
    auto res2=solution.sumLists(b,a);
    CHECK(isEqual(ans,res2));
}

//********************************************************************************

// Solution 2.6

TEST(isPalindromeOdd,Solution_2_6){
    Solution_2_6 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(2);
    head->next->next->next->next=new ListNode(1);
    
    CHECK(solution.isPalindrome(head)==true);
}

TEST(isPalindromeEven,Solution_2_6){
    Solution_2_6 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(3);
    head->next->next->next->next=new ListNode(2);
    head->next->next->next->next->next=new ListNode(1);
    
    CHECK(solution.isPalindrome(head)==true);
}

TEST(isPalindromeNotPalindrome1,Solution_2_6){
    Solution_2_6 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(2);
    
    CHECK(solution.isPalindrome(head)==false);
}

TEST(isPalindromeNotPalindrome2,Solution_2_6){
    Solution_2_6 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=new ListNode(3);
    head->next->next->next->next=new ListNode(2);
    head->next->next->next->next->next=new ListNode(2);
    
    CHECK(solution.isPalindrome(head)==false);
}

//********************************************************************************

// Solution 2.7

TEST(itersectionFirst,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    ListNode* b=a;
    
    auto res=solution.intersection(a,b);
    CHECK(res==b);
}

TEST(itersectionLast,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    ListNode* b=a->next->next;
    
    auto res=solution.intersection(a,b);
    CHECK(res==b);
}

TEST(itersectionNone,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    
    ListNode* b=new ListNode(1);
    b->next=new ListNode(2);
    b->next->next=new ListNode(3);

    auto res=solution.intersection(a,b);
    CHECK(res==nullptr);
}

TEST(itersectionFirst_without_data_struct,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    ListNode* b=a;
    
    auto res=solution.intersection(a,b,false);
    CHECK(res==b);
}

TEST(itersectionLast_without_data_struct,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    ListNode* b=a->next->next;
    
    auto res=solution.intersection(a,b,false);
    CHECK(res==b);
}

TEST(itersectionNone_without_data_struct,Solution_2_7){
    Solution_2_7 solution;
    
    ListNode* a=new ListNode(1);
    a->next=new ListNode(2);
    a->next->next=new ListNode(3);
    
    ListNode* b=new ListNode(1);
    b->next=new ListNode(2);
    b->next->next=new ListNode(3);
    
    auto res=solution.intersection(a,b,false);
    CHECK(res==nullptr);
}

//********************************************************************************

// Solution 2.7

TEST(hasLoop1,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=nullptr;
    
    CHECK(solution.hasLoop(head)==false);
}

TEST(hasLoop2,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    
    CHECK(solution.hasLoop(head)==false);
}

TEST(hasLoop3,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    
    CHECK(solution.hasLoop(head)==false);
}

TEST(hasLoop4,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=head;
    
    CHECK(solution.hasLoop(head)==true);
}

TEST(hasLoop1_without_data_struct,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=nullptr;
    
    CHECK(solution.hasLoop(head,false)==false);
}

TEST(hasLoop2_without_data_struct,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    
    CHECK(solution.hasLoop(head,false)==false);
}

TEST(hasLoop3_without_data_struct,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    
    CHECK(solution.hasLoop(head,false)==false);
}

TEST(hasLoop4_without_data_struct,Solution_2_8){
    Solution_2_8 solution;
    
    ListNode* head=new ListNode(1);
    head->next=new ListNode(2);
    head->next->next=new ListNode(3);
    head->next->next->next=head;
    
    CHECK(solution.hasLoop(head,false)==true);
}
