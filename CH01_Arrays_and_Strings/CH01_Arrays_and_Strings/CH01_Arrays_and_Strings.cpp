/*
 
 CH1: Arrays and Strings
 
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution{
public:
    
    /*----------------------------------------------------------------------
     1.1 Is Unique: Implement an algorithm to determine if a string has all
     unique characters.  What if you cannot use additional data structures?
     ----------------------------------------------------------------------*/
    bool IsUnique(string s, bool ignoreCase=false){
        
        if (s.empty()) { return false; }
        
        if (ignoreCase){
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
        sort(s.begin(), s.end());
        for (int i=0; i < s.size() - 1; i++){
            if (s[i] == s[i+1]) { return false; }
        }
        return true;
    }
    
    /*----------------------------------------------------------------------
     1.2 Check Permutation: Given two strings, write a method to decide
     if one is a permutation of the other.
     ----------------------------------------------------------------------*/
    bool IsPermutation(string a, string b, bool ignoreCase=false){
        
        if (a.size() != b.size()) { return false; }
        
        if (ignoreCase){
            transform(a.begin(), a.end(), a.begin(), ::tolower);
            transform(b.begin(), b.end(), b.begin(), ::tolower);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    }
    
    /*----------------------------------------------------------------------
     1.3 URLify: Write a method to replace all spaces in a string with '%20'.
     You may assume that the string has sufficient space at the end to hold
     the additional characters, and that you are given the "true" length of
     the string.
     ----------------------------------------------------------------------*/
    string Urlify(string s){
        
        int i = (int)s.find_first_of(" ");
        while (i != string::npos){
            s.erase(i, 1);
            s.insert(i, "%20");
            i = (int)s.find_first_of(" ");
        }
        return s;
    }
    
    /*----------------------------------------------------------------------
     1.4 Palindrome Permutation: Given a string, write a functino to check if
     it is a permutation of a palindrome.  A palindrome is a word or phrase
     that is the same forwards and backwards.  A permutation is a rearrangement
     of letters.  The palindrome does not need to be limited to just dictionary
     words.
     
     EXAMPLE:
     Input: Tact Coa
     Output: True ( permutations: "taco cat", "atco cta", etc. )
     ----------------------------------------------------------------------*/
    bool IsPalindromePermutation(string s, bool ignoreCase=false){
        
        if (s.empty()) { return false; }
        if (s.size()==1) { return true; }
        
        if (ignoreCase){
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
        s.erase(remove_if(s.begin(),s.end(), ::isspace), s.end());
        sort(s.begin(), s.end());
        bool single_allowed = s.size()%2==1 ? true : false;
        while(s.size() > 1){
            int size = (int)s.size();
            if (s[size-2] != s[size-1]){
                if (single_allowed){
                    single_allowed = false;
                    s.pop_back();
                } else {
                    return false;
                }
            } else {
                s.pop_back();
                s.pop_back();
            }
        }
        
        if (s.empty() || (s.size()==1 && single_allowed)){
            return true;
        } else {
            return false;
        }
    }
    
    /*----------------------------------------------------------------------
     1.5 One Away: There are three types of edits that can be performed
     on strings: insert a character, remove a character, or replace a character.
     Given two strings, write a function to check if they are one edit
     (or zero edits) away.
     ----------------------------------------------------------------------*/
    bool IsOneAway(string a, string b, bool ignoreCase=false){
        
        if (abs((int)a.size()-(int)b.size()) > 1) { return false; }
        
        if (ignoreCase){
            transform(a.begin(), a.end(), a.begin(), ::tolower);
            transform(b.begin(), b.end(), b.begin(), ::tolower);
        }
        
        unordered_map<char,int> m;
        for (auto ch : a){ if(m.find(ch) == m.end()){ m[ch]= 1; }else{ m[ch]++; } }
        for (auto ch : b){ if(m.find(ch) == m.end()){ m[ch]=-1; }else{ m[ch]--; } }
        
        int cnt=0;
        typedef typename unordered_map<char,int>::iterator m_itr;
        for (m_itr itr=m.begin(); itr != m.end(); itr++){
            cnt += abs(itr->second);
            if (cnt > 1){ return false; }
        }
        
        return true;
    }
    
    /*----------------------------------------------------------------------
     1.6 String Compression: Implement a method to perform basic string
     compression using the counts of repeated characters.  For example,
     the string aabcccccaaa would become a2b1c5a3.  If the "compressed"
     string would not become smaller than the original string, your method
     should return the original string.  You can assume the string has only
     uppercase and lowercase letters (a-z).
     ----------------------------------------------------------------------*/
    string Compress(string s){
        
        if (s.size() < 3) { return s; }
        
        string c = "";
        int cnt=1;
        char prev=-1, curr=s[0];
        for (int i=1; i < (int)s.size(); i++){
            prev = curr;
            curr = s[i];
            if (prev == curr){
                cnt++;
            } else {
                c += prev + to_string(cnt);
                cnt = 1;
            }
        }
        c += curr + to_string(cnt);
        
        if (s.size() < c.size()){
            return s;
        } else {
            return c;
        }
    }
    
    /*----------------------------------------------------------------------
     1.7 Rotate Matrix: Given an image represented by an NxN matrix, where
     each pixel in the image is 4 bytes, write a method to rotate the image
     by 90 degrees.  Can you do this in place?
     ----------------------------------------------------------------------*/
    void Rotate(vector<vector<int>>& m){
        
        /*
         
         A picture and a sample data iteration
         help for writing this operation in place.
         
         Move A->B->C->D->A, and repeat for sub-problems.
        
          0
        0 A
         
          0 1
        0 A B
        1 D C

        int temp = m[1][0];
        m[0][1] = m[0][0];
        m[1][1] = m[0][1];
        m[1][0] = m[1][1];
        m[0][0] = temp;
         
          0 1 2 3
        0 A A A B
        1 D E F B
        2 D H G B
        3 D C C C
        
        temp = m[0][0];
        m[0][0] = m[3][0]; // A=D
        m[3][0] = m[3][3]; // D=C
        m[3][3] = m[0][3]; // C=B
        m[0][3] = temp;    // B=A
        
        temp = m[0][1];
        m[0][1] = m[2][0]; // A=D
        m[2][0] = m[3][2]; // D=C
        m[3][2] = m[1][3]; // C=B
        m[1][3] = temp;    // B=A
         
         */
        
        int start = 0;
        int end = (int)m.size()-1;
        while(start < end){
            for (int offset=0; offset < end-start; offset++){
                int temp = m[start][start+offset];
                /* A=D */ m[start][start+offset] = m[end-offset][start];
                /* D=C */ m[end-offset][start] = m[end][end-offset];
                /* C=B */ m[end][end-offset] = m[start+offset][end];
                /* B=A */ m[start+offset][end] = temp;
            }
            start++; --end; // iterate inwards to sub-problems
        }
    }
    
    /*----------------------------------------------------------------------
     1.8 Zero Matrix: Write an algorithm such that if an element in an MxN matrix
     is 0, its entire row and column are set to 0.
     ----------------------------------------------------------------------*/
    void ZeroMatrix(vector<vector<int>>& m){
        
        if (m.empty()) { return; }
        int colLen = (int)m.size();
        int rowLen = (int)m[0].size();
        
        vector<int> zeroRows, zeroCols;
        for (int r=0; r < colLen; r++){
            for (int c=0; c < rowLen; c++){
                if (!m[r][c]) {
                    zeroRows.push_back(r);
                    zeroCols.push_back(c);
                }
            }
        }
        
        while (!zeroRows.empty()){
            m[zeroRows.back()] = vector<int>(rowLen, 0);
            zeroRows.pop_back();
        }
        
        while (!zeroCols.empty()){
            int c = zeroCols.back();
            zeroCols.pop_back();
            for (int r=0; r < colLen; r++){
                m[r][c] = 0;
            }
        }
    }
    
    /*----------------------------------------------------------------------
     Helper Functions
     ----------------------------------------------------------------------*/
    void PrintMatrix(vector<vector<int>>& m){
        for (auto r : m){
            string row="[";
            for (auto c : r){
                row += to_string(c) + ",";
            }
            row.pop_back();
            row += "]";
            cout << row << endl;
        }
        cout << endl;
    }
    
    /*----------------------------------------------------------------------
     1.9 String Rotation: Assume you have a method isSubstring which checks
     if one word is a sustring of another.  Given two strings, s1 and s2,
     write code to check if s2 is a rotation of s1 using only one call to 
     isSubstring (e.g., "waterbottle" is a rotation of "erbottlewat").
     ----------------------------------------------------------------------*/
    bool IsRotation(string a, string b){
        
        if (a.size() != b.size() || a.size() == 0){ return false; }
        
        /*
         
         C++ STL equivalent of isSubstring() would be string.find()
         
            a="waterbottle"
          a+a="waterbottlewaterbottle"
            b=   "erbottlewat"
         */
        return ((int)(a+a).find(b) != string::npos) ? true : false;
    }
};

int main(int argc, const char * argv[]) {

    Solution solution;
    string a = "waterbottle";
    string b = "erbottlewat";
    cout << solution.IsRotation(a, b) << endl;
    
    return 0;
}



