/*
 
 CCI CH01 Unit Tests
 
 */

#include <string>
#include <algorithm>
#include "TestHarness.h"
#include "CH01.hpp"

using namespace std;

#define DATA_STRUCTS_ALLOWED 0

//********************************************************************************

// Solution 1.1

TEST(LowerAlpha,Solution_1_1){
    string str("abcdefghijklmnopqrstuvwxyz");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==true);
}

TEST(UpperAlpha,Solution_1_1){
    string str("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==true);
}

TEST(UpperAndLowerAlpha,Solution_1_1){
    string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

TEST(EmptyStr1,Solution_1_1){
    string str;
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==true);
}

TEST(EmptyStr2,Solution_1_1){
    Solution_1_1 solution;
    CHECK(solution.IsUnique("",DATA_STRUCTS_ALLOWED)==true);
}

TEST(SingleDup1,Solution_1_1){
    string str("abcda");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

TEST(SingleDup2,Solution_1_1){
    string str("abcdefghijj");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

TEST(SingleChar,Solution_1_1){
    string str("x");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==true);
}

TEST(AllDup1,Solution_1_1){
    string str("aa");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

TEST(AllDup2,Solution_1_1){
    string str("aaa");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

TEST(AllDup3,Solution_1_1){
    string str("aaaa");
    Solution_1_1 solution;
    CHECK(solution.IsUnique(str,DATA_STRUCTS_ALLOWED)==false);
}

//********************************************************************************

// Solution 1.2

TEST(AllPermutations,Solution_1_2){
    string str("abcdefg");
    string orig(str);
    Solution_1_2 solution;
    do{
        CHECK(solution.IsPermutation(orig, str));
        CHECK(solution.IsPermutation(str, orig));
    }while(next_permutation(str.begin(),str.end()));
}

//********************************************************************************

// Solution 1.3

TEST(JohnSmith,Solution_1_3){
    string str("Mr John Smith    ");
    int N=13;
    Solution_1_3 solution;
    solution.URLify(str, N);
    CHECK_EQUAL(str,"Mr%20John%20Smith");
}

//********************************************************************************

// Solution 1.4

TEST(PalindromePermutation,Solution_1_4){
    string s("Tact Coa");
    Solution_1_4 solution;
    CHECK(solution.isPalindromePermutation(s));
}

//********************************************************************************

// Solution 1.4

TEST(OneAway1,Solution_1_5){
    string s1("pale"),s2("ple");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==true);
}

TEST(OneAway2,Solution_1_5){
    string s1("pales"),s2("pale");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==true);
}

TEST(OneAway3,Solution_1_5){
    string s1("pale"),s2("bale");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==true);
}

TEST(OneAway4,Solution_1_5){
    string s1("pale"),s2("bake");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==false);
}

TEST(OneAway5,Solution_1_5){
    string s1("pales"),s2("bake");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==false);
}

TEST(OneAway6,Solution_1_5){
    string s1("abc"),s2("ad");
    Solution_1_5 solution;
    CHECK(solution.isOneAway(s1,s2)==false);
}

//********************************************************************************

// Solution 1.6

TEST(StrComp1,Solution_1_6){
    string s;
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp2,Solution_1_6){
    string s("a");
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp3,Solution_1_6){
    string s("aa");
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp4,Solution_1_6){
    string s("aabcccccaaa");
    Solution_1_6 solution;
    CHECK(solution.compress(s)=="a2b1c5a3");
}

TEST(StrComp5,Solution_1_6){
    string s("abc");
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp6,Solution_1_6){
    string s("aaa");
    Solution_1_6 solution;
    CHECK(solution.compress(s)=="a3");
}

TEST(StrComp7,Solution_1_6){
    string s("aab");
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp8,Solution_1_6){
    string s("aaab");
    Solution_1_6 solution;
    CHECK(solution.compress(s)==s);
}

TEST(StrComp9,Solution_1_6){
    string s("aaaab");
    Solution_1_6 solution;
    CHECK(solution.compress(s)=="a4b1");
}


//********************************************************************************

// Solution 1.7

TEST(rotate1,Solution_1_7){
    VVI m1{
        {1,2,3},
        {4,5,6},
        {7,8,9},
    };
    VVI m2{
        {7,4,1},
        {8,5,2},
        {9,6,3},
    };

    Solution_1_7 solution;
    solution.rotate(m1);
    CHECK(m1==m2);
}

TEST(rotate2,Solution_1_7){
    VVI m1{
        {1,  2, 3,4},
        {12,13,14,5},
        {11,16,15,6},
        {10, 9, 8,7},
    };
    VVI m2{
        {10,11,12,1},
        { 9,16,13,2},
        { 8,15,14,3},
        { 7, 6, 5,4},
    };

    Solution_1_7 solution;
    solution.rotate(m1);
    CHECK(m1==m2);
}

//********************************************************************************

// Solution 1.8

TEST(zeroMatrix1,Solution_1_8){
    VVI m1{
        {1,1,1,1},
        {1,1,1,1},
        {1,0,1,1},
        {1,1,1,1},
    };
    VVI m2{
        {1,0,1,1},
        {1,0,1,1},
        {0,0,0,0},
        {1,0,1,1},
    };
    Solution_1_8 solution;
    solution.zeroMatrix(m1);
    CHECK(m1==m2);
}

//********************************************************************************

// Solution 1.9

TEST(stringRotation1,Solution_1_9){
    string s1("erbottlewat"),s2("waterbottle");
    Solution_1_9 solution;
    CHECK(solution.isRotation(s1, s2)==true);
}

TEST(stringRotation2,Solution_1_9){
    string s1("erbottlewater"),s2("waterbottle");
    Solution_1_9 solution;
    CHECK(solution.isRotation(s1, s2)==false);
}



