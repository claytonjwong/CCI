/*
 
 CH03: Stacks and Queues
 
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

template<class T>
class MinStack{
public:
    MinStack() : _stack{}, _min{} {}
    
    void push(T val){
        _stack.push(val);
        if (_min.empty()){
            _min.push(val);
        } else {
            if (val < _min.top()){
                _min.push(val);
            }
        }
    }
    
    void pop(){
        if (_stack.empty()) { throw out_of_range("stack is empty"); }
        if (_stack.top()==_min.top()){
            _min.pop();
        }
        _stack.pop();
    }
    
    T top(){
        if (_stack.empty()) { throw out_of_range("stack is empty"); }
        return _stack.top();
    }
    
    bool empty() { return _stack.empty(); }
    
    T min(){
        if (_stack.empty()) { throw out_of_range("stack is empty"); }
        return _min.top();
    }
    
private:
    stack<T> _stack;
    stack<T> _min;
};


template<class T>
class SetStack{
public:
    
    SetStack(int size) : _size{size}, _set{} {}
    
    void push(T val){
        if (_set.empty() || (!_set.empty() && _set.back().size() == _size)){
            _set.push_back(stack<T>{});
        }
        _set.back().push(val);
    }
    
    void pop(){
        if (_set.empty()) { throw out_of_range("stack is empty"); }
        _set.back().pop();
        
        if (_set.back().empty()){
            _set.pop_back();
        }
    }
    
    T top(){
        if (_set.empty()) { throw out_of_range("stack is empty"); }
        return _set.back().top();
    }
    
    bool empty() { return _set.empty(); }
    
private:
    int _size;
    vector<stack<T>> _set;
};


template<class T>
class QStack{
public:
    
    QStack() : _main{}, _aux{} {}
    
    void enqueue(T val){
        if (_main.empty()){
            _main.push(val);
        } else {
            while (!_main.empty()){
                _aux.push(_main.top());
                _main.pop();
            }
            _main.push(val);
            while (!_aux.empty()){
                _main.push(_aux.top());
                _aux.pop();
            }
        }
    }
    
    T dequeue(){
        if (_main.empty()) { throw out_of_range("stack is empty"); }
        T res=_main.top();
        _main.pop();
        return res;
    }
    
    bool empty() { return _main.empty(); }
    
private:
    stack<T> _main;
    stack<T> _aux;
};


template<class T>
class SortStack{
public:
    SortStack() : _main{}, _aux{} {}
    
    void push(T val){
        if (_main.empty() || (!_main.empty() && val <= _main.top())){
            _main.push(val);
        } else {
            while (!_main.empty() && val > _main.top()){
                _aux.push(_main.top());
                _main.pop();
            }
            _main.push(val);
            while (!_aux.empty()){
                _main.push(_aux.top());
                _aux.pop();
            }
        }
    }
    
    void pop(){
        if (_main.empty()) { throw out_of_range("stack is empty"); }
        _main.pop();
    }
    
    T top(){
        if (_main.empty()) { throw out_of_range("stack is empty"); }
        return _main.top();
    }
    
    bool empty() { return _main.empty(); }
    
private:
    stack<T> _main;
    stack<T> _aux;
};

template<class T>
class Solution{
public:
    
    /*----------------------------------------------------------------------
     3.2 Stack Min: How would you design a stack which, in addition to push
     and pop, has function min which returns the minimum element?  Push, pop,
     and min should all operate in O(1) time.
     ----------------------------------------------------------------------*/
    MinStack<T> minStack{};
    
    /*----------------------------------------------------------------------
     3.3 Stack of Plates: Imagine a (literal) stack of plates.  If the stack
     gets too high, it might topple.  Therefore, in real life, we would likely
     start a new stack when the previous stack exceeds some threshold.  Implement
     a data structure SetOfStacks that mimics this.  SetOfStacks should be
     composed of several stacks and should create a new stack once the previous
     one exceeds capacity.  SetOfStacks.push() and SetOfStacks.pop() should behave
     identically to a single stack (that is, pop() should return the same values
     as it would if there were just a single stack).
     FOLLOW UP
     Implement a function popAt(int index) which performs a pop operation
     on a specific sub-stack.
     ----------------------------------------------------------------------*/
    const int DEFAULT_SIZE=3;
    SetStack<T> setStack{DEFAULT_SIZE};
    
    /*----------------------------------------------------------------------
     3.4 Queue via Stacks: Implement a MyQueue class which implements a queue
     using two stacks.
     ----------------------------------------------------------------------*/
    QStack<T> queue;
    
    /*----------------------------------------------------------------------
     3.5 Sort Stack: Write a program to sort a stack such that the
     smallest items are on the top.  You can use an additional temporary stack,
     but you may not copy the elements into any other data structure
     (such as an array).  The stack supports the following operations:
     push, pop, peek, and isEmpty.
     ----------------------------------------------------------------------*/
    SortStack<T> sortStack;
};


int main(int argc, const char * argv[]) {

    Solution<int> solution;
    solution.sortStack.push(6);
    solution.sortStack.push(3);
    solution.sortStack.push(5);
    solution.sortStack.push(6);
    solution.sortStack.push(69);
    solution.sortStack.push(7);
    solution.sortStack.push(9);
    solution.sortStack.push(10);
    solution.sortStack.push(1);
    
    while (!solution.sortStack.empty()){
        cout << solution.sortStack.top() << endl;
        solution.sortStack.pop();
    }

    return 0;
}




