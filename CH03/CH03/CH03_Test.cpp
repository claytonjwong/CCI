//
//  CH03_Test.cpp
//  CH03
//
//  Created by CLAYTON WONG on 7/23/18.
//  Copyright © 2018 Clayton Wong. All rights reserved.
//

#include <vector>
#include <algorithm>
#include "TestHarness.h"
#include "CH03.hpp"

//**********************************************************************

// Solution 3.2

TEST(ctor,MinStack){
    MinStack<int> ms1,ms2;
    CHECK(ms1==ms2);
}

TEST(pushEquality,MinStack){
    MinStack<int> ms1,ms2;
    ms1.push(69);
    CHECK(ms1!=ms2);
    ms2.push(69);
    CHECK(ms1==ms2);
}

TEST(pushPopEquality1,MinStack){
    MinStack<int> ms1,ms2;
    ms1.push(69);
    ms1.pop();
    CHECK(ms1==ms2);
}

TEST(pushPopEquality2,MinStack){
    MinStack<int> ms1,ms2;
    ms1.push(1);
    ms1.push(2);
    ms1.push(3);
    ms1.push(4);
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1==ms2);
}

TEST(pushPopEquality3,MinStack){
    MinStack<int> ms1,ms2;
    ms1.push(4);
    ms1.push(3);
    ms1.push(2);
    ms1.push(1);
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==2);
    ms1.pop();
    CHECK(ms1.min()==3);
    ms1.pop();
    CHECK(ms1.min()==4);
    ms1.pop();
    CHECK(ms1==ms2);
}

TEST(pushDups,MinStack){
    MinStack<int> ms1,ms2;
    ms1.push(4);
    ms1.push(1);
    ms1.push(1);
    ms1.push(1);
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==1);
    ms1.pop();
    CHECK(ms1.min()==4);
    ms1.pop();
    CHECK(ms1==ms2);
}

//**********************************************************************

// Solution 3.4

TEST(ctor,MyQueue){
    MyQueue<int> q1,q2;
    CHECK(q1==q2);
}

TEST(assignment,MyQueue){
    MyQueue<int> q1,q2;
    q1.push(69);
    q2=q1;
}

TEST(pushPop,MyQueue){
    MyQueue<int> q1,q2;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    CHECK(q1.front()==1);
    q1.pop();
    CHECK(q1.front()==2);
    q1.pop();
    CHECK(q1.front()==3);
    q1.pop();
    CHECK(q1.empty());
    CHECK(q1==q2);
}

//**********************************************************************

// Solution 3.5

TEST(sort,SortStack){
    SortStack<int> ss;
    ss.push(3);
    ss.push(1);
    ss.push(5);
    ss.push(9);
    ss.push(2);
    ss.push(4);
    ss.push(7);
    ss.push(6);
    ss.push(8);
    std::vector<int> v;
    while (!ss.empty())
        v.push_back(ss.top()),ss.pop();
    CHECK(is_sorted(v.begin(),v.end()));
}

