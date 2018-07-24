/*
 
 CCI CH03: Stacks and Queues
 
 */

#include <iostream>
#include <stack>
#include <vector>

//
// Question 3.2: How would you design a stack which, in addition to push and pop,
// has a function min which returns the minimum element?  Push, pop, and min
// should all operator in O(1) time.
//
// Answer 3.2: use an auxillary stack to store minimums pushed onto the stack
// then min can always return the auxillary stack's top, which is always the
// ongoing minimum on the stack.
//
template <typename T>
class MinStack {
public:
    MinStack()=default;
    ~MinStack()=default;
    MinStack(MinStack& src)=default;
    MinStack(MinStack&& src)=default;
    MinStack& operator=(MinStack& rhs)=default;
    MinStack& operator=(MinStack&& rhs)=default;
    bool operator==(const MinStack& rhs) const { return myStack==rhs.myStack; }
    bool operator!=(const MinStack& rhs) const { return !(myStack==rhs.myStack); }
    void push(const T& x){
        myStack.push(x);
        if (myMinStack.empty() || x<=myMinStack.top()) myMinStack.push(x);
    }
    const T pop() {
        T x=myStack.top(); myStack.pop();
        if (x==myMinStack.top()) myMinStack.pop();
        return x;
    }
    const T& top() const { return myStack.top(); }
    const T& min() const { return myMinStack.top(); }
    bool empty() const { return myStack.empty(); }
private:
    std::stack<T> myStack,myMinStack;
};

//
// Question 3.4 Queue via Stacks: implement a MyQueue class which implements a queue
// using two stacks.
//
// Answer 3.4: its easier to debug code using a vector mimic a stack, otherwise
// it is difficult to see the stack contents.
//
template <typename T>
class MyQueue {
public:
    MyQueue()=default;
    ~MyQueue()=default;
    MyQueue(MyQueue& src)=default;
    MyQueue(MyQueue&& src)=default;
    MyQueue& operator=(MyQueue& rhs)=default;
    MyQueue& operator=(MyQueue&& rhs)=default;
    bool operator==(const MyQueue& rhs) const { return myStack==rhs.myStack; }
    bool operator!=(const MyQueue& rhs) const { return !(myStack==rhs.myStack); }
    void push(const T& x) {
        unstack();
        myStack.push_back(x);
        restack();
    }
    T pop() {
        T x=myStack.back();
        myStack.pop_back();
        return x;
    }
    const T& front() const { return myStack.back(); }
    bool empty() const { return myStack.empty(); }
private:
    std::vector<T> myStack,myAuxStack;
    void unstack(){
        while (!myStack.empty()){
            myAuxStack.push_back(myStack.back());
            myStack.pop_back();
        }
    }
    void restack(){
        while (!myAuxStack.empty()){
            myStack.push_back(myAuxStack.back());
            myAuxStack.pop_back();
        }
    }
};

//
// Question 3.5 Sort Stack: Write a program to sort a stack such that the smallest items
// are on the top.  You can use an additional temporary stack, but you may not copy
// the elements into any other data structure (such as an array).  The stack supports
// the following operations: push, pop, peek, and  isEmpty
//
// Answer 3.5: Using a vector's push_back/pop_back functionality to mimic a stack.
// This is easier to debug, since I can clearly see the vector's contents
//
template <typename T>
class SortStack{
public:
    SortStack()=default;
    ~SortStack()=default;
    SortStack(SortStack& src)=default;
    SortStack(SortStack&& src)=default;
    SortStack& operator=(SortStack& rhs)=default;
    SortStack& operator=(SortStack&& rhs)=default;
    bool operator==(const SortStack& rhs) const { return myStack==rhs.myStack; }
    bool operator!=(const SortStack& rhs) const { return !(myStack==rhs.myStack); }
    void push(const T& x){
        if (myStack.empty()){
            myStack.push_back(x);
        }else{
            while (!myStack.empty() && x > myStack.back()){
                myAuxStack.push_back(myStack.back());
                myStack.pop_back();
            }
            myStack.push_back(x);
            while (!myAuxStack.empty()){
                myStack.push_back(myAuxStack.back());
                myAuxStack.pop_back();
            }
        }
    }
    T pop(){
        T x=myStack.back();
        myStack.pop_back();
        return x;
    }
    bool empty() const { return myStack.empty(); }
    T top() const { return myStack.back(); }
private:
    std::vector<T> myStack,myAuxStack;
};


