/*
 
 CCI CH01: Arrays and Strings
 
 */

#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

//
// Question 1.1 Is Unique: implement an algorithm
// to determine if a string has all unique characters.
// what if you cannot use additional data structures?
//
// Answer 1.1: assuming unique characters are alphabetical chars in the string s,
// and case sentitive (i.e. "Aa" would return false, since there are two A's),
// first transform s into t as lowercase, then return the size of the unordered set
// created from t.  If the size is equal, return true.  Otherwise return false.
//
class Solution_1_1 {
public:
    bool IsUnique(const string& s, bool data_structs_allowed=true) const {
        if (data_structs_allowed){
            string t{s}; transform(s.begin(),s.end(),t.begin(),::tolower);
            return unordered_set<char>{t.begin(),t.end()}.size()==t.size();
        }else{
            int N=(int)s.size();
            for (int i=0; i<N-1; ++i)
                for (int j=i+1; j<N; ++j) if (tolower(s[i])==tolower(s[j]))
                    return false;
            return true;
        }
    }
};

//
// Question 1.2 Check Permutation: Given two strings, write a method to decide
// if one is a permutation of the other.
//
// Answer 1.2: use an unordered map to count the instances of each char
// of each string.  "t"ransform each string into all lowercase chars for comparison.
//
class Solution_1_2 {
public:
    bool IsPermutation(const string& s1, const string& s2) const {
        if (s1.size()!=s2.size()) return false;
        string t1,t2;
        transform(s1.begin(),s1.end(),t1.begin(),::tolower);
        transform(s2.begin(),s2.end(),t2.begin(),::tolower);
        unordered_map<char,int> m1,m2;
        for (auto c: t1) ++m1[c];
        for (auto c: t2) ++m2[c];
        return m1==m2;
    }
};

//
// Question 1.3 URLify: Write a method to replace all spaces in a string with '%20'.
// you may assume that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string.
//
// EXAMPLE
//
// Input:   "Mr John Smith    ", 13
// Output:  "Mr%20John%20Smith"
//
// Answer 1.3: create the "next" string based on the "curr"ent string by iterating
// through "curr" and create "next" one char at a time.  Whenever whitespace chars
// are encountered in "curr", append the "r"eplacement string ("%20") onto "next".
// Otherwise append non-whitespace chars from "curr" onto "next".  Finally swap curr/next.
// So that the value of curr is equal to the previous value of curr with whitespace
// replaced with "%20"
//
class Solution_1_3 {
public:
    void URLify(string& curr, int N) const {
        string r("%20"),next;
        next.reserve(2*curr.size());
        for (int i=0; i<N; ++i){
            char c=curr[i];
            if (isspace(c))
                next.append(r);
            else
                next.push_back(c);
        }
        swap(curr,next);
    }
};

//
// Question 1.4 Palindrome Permutation: Given a string, write a function to check
// if it is a permutation of a palindrome.  A palindrome is a word or phrase
// that is the same forwards and backwards.  A permutation is a rearrangement of letters.
// The palindrome does not need to be limited to just dictionary words.
//
// EXAMPLE
// Input:   "Tact Coa"
// Output:  true (permutations: "taco cat", "atco cta", etc.)
//
// Answer 1.4: use an unordered_map to track the count of each char in the "s"tring
// return true if all counts are even with one allowed odd.  Ignore whitespace and check
// for both upper/lower case chars
//
class Solution_1_4 {
public:
    bool isPalindromePermutation(const string& s) const {
        unordered_map<char,int> m;
        for (auto c: s) if (!isspace(c))
            ++m[tolower(c)];
        int odd=0;
        for (auto& p: m) if (p.second%2)
            ++odd;
        return odd<2;
    }
};

//
// Question 1.5 One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character, or replace a character.  Given two strings, write a function to check if they are
// one edit away (or zero edits) away
//
// Answer 1.5: Take care of trivial cases first.  Check if the input strings s1,s2 are equal,
// if so return true immediately.  Also check if the size of each string differs by more than one char,
// if so return false immediately.
//
// use cases:
//
// either s1,s2 are the same size, and only replacement operations should be considered
//
// xor s1,s2 are a different size, and only operations to consider are:
// either insert to smaller of s1,s2 xor remove from larger of s1,s2
//
class Solution_1_5 {
public:
    bool isOneAway(const string& s1, const string& s2) const {
        if (s1==s2) return true;
        int M=(int)s1.size(),N=(int)s2.size();
        if (abs(M-N)>1) return false;
        for (int i=0,j=0,diff=0; i<M && j<N; ++i,++j){
            if (s1[i]==s2[j]) continue;
            if (++diff > 1){
                return false;
            }else{
                if (M==N) continue; else if (M>N) ++i; else ++j;
            }
        }
        return true;
    }
};

//
// Question 1.6 String Compression: Implement a method to perform basic string compression using the counts
// of repeated characters.  For example, the string aabcccccaaa would become a2b1c5a3.  If the "compressed"
// string would not become smaller than the original string, your method should return the original string.
// You can assume the string only has uppercase and lowercase letters (a-z).
//
// Answer 1.6: create the "next" string from the "curr"ent string by iterating through "curr"
// and creating next based on consequetive equal values
//
class Solution_1_6 {
public:
    string compress(const string& curr) const {
        int N=(int)curr.size();
        if (N<3) return curr;
        string next;
        next.reserve(2*curr.size());
        for (int i=0,j=i+1; i<N; i=j,j=i+1){
            while (j<N && curr[i]==curr[j]) ++j;
            next.push_back(curr[i]);
            next.append(to_string(j-i));
        }
        return (curr.size() <= next.size()) ? curr : next;
    }
};

//
// Question 1.7 Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image
// is 4 bytes, write a method to rotate the image by 90 degrees.  Can you do this in place?
//
// Answer 1.7: I'll assume to rotate clockwise 90 degrees.  Use a temp to rotate each side value clockwise.
// Start rotating from the outside, and end in the middle.
//
using VI=vector<int>;
using VVI=vector<VI>;
class Solution_1_7 {
public:
    void rotate(VVI& m) const {
        for (int i=0,N=(int)m.size(); i<N/2; ++i){
            for (int j=0; i+j<N-1-i; ++j){
                int tmp=m[i+j][i];
                m[i+j][i]=m[N-1-i][i+j];
                m[N-1-i][i+j]=m[N-1-i-j][N-1-i];
                m[N-1-i-j][N-1-i]=m[i][N-1-i-j];
                m[i][N-1-i-j]=tmp;
            }
        }
    }
};

//
// Question 1.8 Zero Matrix: Write an algorithm such that if an element in a MxN matrix is 0,
// its entire row and column are set to 0.
//
// Answer 1.8: Create set to track row/cols which should be zero'd out, traverse the matrix
// first to update these sets.  Then update the matrix based on these sets.
//
class Solution_1_8 {
public:
    void zeroMatrix(VVI& m) const {
        unordered_set<int> row,col;
        int M=(int)m.size(),N=m.empty() ? 0 : (int)m[0].size();
        for (int i=0; i<M; ++i)
            for (int j=0; j<N; ++j) if (m[i][j]==0)
                row.insert(i),col.insert(j);
        for (int i=0; i<M; ++i)
            for (int j=0; j<N; ++j) if (row.find(i)!=row.end() || col.find(j)!=col.end())
                m[i][j]=0;
    }
};

//
// Question 1.9 String Rotation: Assume you have a method isSubstring which checks if one word
// is a substring of another.  Given two strings s1 and s2, write code to check if s2 is a rotation
// of s1 using only one call to isSubstring (e.g. "waterbottle" is a rotation of "erbottlewat").
//
// Answer 1.9: append s1 onto itself, then invoke isSubstring, return true if found, otherwise return false
//
class Solution_1_9 {
public:
    bool isRotation(const string& s1, const string& s2) const {
        return isSubstring(s1+s1,s2);
    }
    bool isSubstring(const string& s1, const string& s2) const {
        return s1.find(s2)!=string::npos;
    }
};



