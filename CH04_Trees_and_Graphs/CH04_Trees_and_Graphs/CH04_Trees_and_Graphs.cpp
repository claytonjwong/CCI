/*
 
 CH4: Trees and Graphs
 
 */

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <unordered_map>
#include <time.h>

using namespace std;

template <class T>
class GraphNode{
public:
    T val;
    enum { INIT, ANALYSIS, COMPLETE } state;
    vector<shared_ptr<GraphNode<T>>> next;
    GraphNode(T val) : val{val}, state{INIT}, next{} {}
};

template <class T>
class TreeNode{
public:
    T val;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    shared_ptr<TreeNode<T>> parent;
    TreeNode(T val) : val{val}, left{nullptr}, right{nullptr}, parent{NULL} {}
};

template <class T>
class ListNode{
public:
    T val;
    shared_ptr<ListNode<T>> next;
    ListNode(T val) : val{val}, next{nullptr} {}
};

class BuildOrderException : public exception {
public:
    virtual const char* what() const throw(){
        return "build order exception";
    }
} build_order_error;

template <class T>
class Solution{
    
public:
    
    Solution(){
        srand(time(nullptr));
    }
    
    /*----------------------------------------------------------------------
     4.1 Route Between Nodes: Given a directed graph, design an algorithm
     to find out whether there is a route between two nodes.
     ----------------------------------------------------------------------*/
    bool IsRoute(shared_ptr<GraphNode<T>>& A, shared_ptr<GraphNode<T>>& B){
        if (A==nullptr || B==nullptr) { return nullptr; }
        set<shared_ptr<GraphNode<T>>> visited{};
        stack<shared_ptr<GraphNode<T>>> stack{}; stack.push(A);
        while (!stack.empty()){
            shared_ptr<GraphNode<T>> curr=stack.top(); stack.pop();
            visited.insert(curr);
            if (curr.get()==B.get()) { return true; }
            for (auto n : curr->next){
                if (visited.find(n)==visited.end()){
                    stack.push(n);
                }
            }
        }
        return false;
    }
    
    /*----------------------------------------------------------------------
     4.2 Minimal Tree: Given a sorted (increasing order) array with unique
     integer elements, write an algorithm to create a binary search tree
     with minimal height.
     ----------------------------------------------------------------------*/
    shared_ptr<TreeNode<T>> CreateTree(vector<T>& A){
        if (A.empty()) { return nullptr; }
        if (!is_sorted(A.begin(), A.end())){
            sort(A.begin(), A.end());
        }
        return CreateTree(A, 0, (int)A.size()-1);
    }
    
    shared_ptr<TreeNode<T>> CreateTree(vector<T>& A, int lo, int hi){
        if (lo > hi) { return nullptr; }
        int mid=(int)(lo+hi)/2;
        auto root=make_shared<TreeNode<T>>(A[mid]);
        root->left=CreateTree(A, lo, mid-1);
        root->right=CreateTree(A, mid+1, hi);
        return root;
    }
    
    /*----------------------------------------------------------------------
     4.3 List of Depths: Given a binary tree, design an algorithm
     which creates a linked list of all nodes at each depth
     (e.g., if you have a tree with depth D, you'll have D linked lists).
     ----------------------------------------------------------------------*/
    void CreateDepthList(shared_ptr<TreeNode<T>> root,
                         vector<shared_ptr<ListNode<T>>>& depthList){
        CreateDepthList(root, 0, depthList);
    }
    
    void CreateDepthList(shared_ptr<TreeNode<T>> treeNode, int depth,
                         vector<shared_ptr<ListNode<T>>>& depthList){
        if (treeNode==nullptr) { return; }
        auto listNode=make_shared<ListNode<T>>(treeNode->val);
        if (depth==depthList.size()){ depthList.push_back(listNode); }
        else {
            auto itr=depthList[depth];
            while(itr && itr->next){ itr=itr->next; }
            itr->next=listNode;
        }
        if (treeNode->left) { CreateDepthList(treeNode->left, depth+1, depthList); }
        if (treeNode->right) { CreateDepthList(treeNode->right, depth+1, depthList); }
    }

    /*----------------------------------------------------------------------
     4.4 Check Balanced: Implement a function to check if a binary tree
     is balanced.  For the purpose of this question, a balanced tree
     is defined to be a tree such that the heights of the two subtrees
     of any node never differ by more than one.
     ----------------------------------------------------------------------*/
    bool IsBalanced(shared_ptr<TreeNode<T>> root){
        return IsBalanced(root, 0) != -1;
    }
    
    int IsBalanced(shared_ptr<TreeNode<T>> node, int depth){
        if (!node) { return depth-1; }
        int left=IsBalanced(node->left, depth+1);
        int right=IsBalanced(node->right, depth+1);
        int diff=abs(left-right);
        if (left==-1 || right==-1 || diff > 1) { return -1; }
        return max(left,right);
    }

    /*----------------------------------------------------------------------
     4.5 Validate BST: Implement a function to check if a binary tree
     is a binary search tree.
     ----------------------------------------------------------------------*/
    bool IsBST(shared_ptr<TreeNode<T>> root){
        if (!root) { return false; }
        vector<T> inorder{};
        IsBST(root, inorder);
        return is_sorted(inorder.begin(), inorder.end());
    }
    
    void IsBST(shared_ptr<TreeNode<T>> node, vector<T>& inorder){
        if (node->left) { IsBST(node->left, inorder); }
        inorder.push_back(node->val);
        if (node->right) { IsBST(node->right, inorder); }
    }

    /*----------------------------------------------------------------------
     4.6 Successor: Write an algorithm to find the "next" node (i.e. in-order
     successor) of a given node in a binary search tree.  You may assume
     that each node has a link to its parent.
     ----------------------------------------------------------------------*/
    shared_ptr<TreeNode<T>> Successor(shared_ptr<TreeNode<T>> node){
        //
        // successor is the left-most node in the right-subtree,
        // if there is no right-subtree, then take the closet
        // parent whom's value is > target
        //
        if (!node) { return nullptr; }
        if (!node->right && !node->parent) { return nullptr; }

        if (node->right) {
            auto itr=node->right;
            while (itr->left){ itr=itr->left; }
            return itr;
        }
        if (node->parent){
            auto itr=node->parent;
            while (itr->val < node->val && itr->parent) { itr=itr->parent; }
            if (itr->val > node->val) { return itr; }
        }
        return nullptr;
    }
    
    /*----------------------------------------------------------------------
     4.7 Build Order: You are given a list of projects and a list of dependencies
     (which is a list of pairs of projects, where the second project is dependent
     on the first project).  All of a project's dependencies must be built
     before the project is.  Find a build order that will allow the projects
     to be built.  If there is no valid build order, return an error.
     EXAMPLE
     Input:
        projects: a, b, c, d, e, f
        dependencies: (a,d), (f,b), (b,d), (f,a), (d,c)
     Output: f, e, a, b, d, c
     ----------------------------------------------------------------------*/
    stack<shared_ptr<GraphNode<T>>> BuildOrder(vector<shared_ptr<GraphNode<T>>>& projects){
        stack<shared_ptr<GraphNode<T>>> res{};
        for (auto &proj : projects){
            if (proj->state==GraphNode<T>::INIT){
                BuildOrderHelper(proj, res);
            }
        }
        return res;
    }
    
    void BuildOrderHelper(shared_ptr<GraphNode<T>>& proj,
                          stack<shared_ptr<GraphNode<T>>>& stack){
        if (proj->state==GraphNode<T>::ANALYSIS){
            throw build_order_error;
        }
        proj->state=GraphNode<T>::ANALYSIS;
        for (auto &child : proj->next){
            if (child->state != GraphNode<T>::COMPLETE){
                BuildOrderHelper(child, stack);
            }
        }
        proj->state=GraphNode<T>::COMPLETE;
        stack.push(proj);
    }
    
    /*----------------------------------------------------------------------
     4.8 First Common Ancestor: Design an algorithm and write code to find
     the first common ancestor of two nodes in a binary tree.  Avoid storing
     additional nodes in a data structure.  NOTE: this is not necessarily
     a binary search tree.
     ----------------------------------------------------------------------*/
    shared_ptr<TreeNode<T>> FirstCommonAncestor(
        shared_ptr<TreeNode<T>> root,
        shared_ptr<TreeNode<T>> p,
        shared_ptr<TreeNode<T>> q){
        if (!root || !p || !q) { return nullptr; }
        return FirstCommonAncestorHelper(root, p, q);
    }
    
    shared_ptr<TreeNode<T>> FirstCommonAncestorHelper(
        shared_ptr<TreeNode<T>> root,
        shared_ptr<TreeNode<T>> p,
        shared_ptr<TreeNode<T>> q){
        if (!root) { return nullptr; }
        if (root.get()==p.get() || root.get()==q.get()) { return root; }
        auto left=FirstCommonAncestorHelper(root->left, p, q);
        auto right=FirstCommonAncestorHelper(root->right, p, q);
        if (left && right){ return root; }
        return left!=nullptr ? left : right;
    }
    
    /*----------------------------------------------------------------------
     4.9 BST Sequences: A binary search tree was created by traversing
     though an array from left to right and inserting each element.  Given
     a binary search tree with distinct elements, print all possible arrays
     that could have led to this tree.
     ----------------------------------------------------------------------*/
    vector<vector<T>> GetSequencesFromBST(shared_ptr<TreeNode<T>> root){
        vector<vector<T>> res{};
        
        //
        // TODO
        //
        
        return res;
    }
    
    /*----------------------------------------------------------------------
     4.10 Check Subtree: T1 and T2 are two very large binary trees, with T1 much
     bigger than T2.  Create an algorithm to determine if T2 is a substree of T1.
     A tree T2 is a subtree of T1 if there exists a node in T1 such that the subtree
     of n is identical to T2.  That is, if you cut off the tree at node n,
     the two trees could be identical.
     ----------------------------------------------------------------------*/
    bool IsSubtree(shared_ptr<TreeNode<T>> t1, shared_ptr<TreeNode<T>> t2){
        if (!t1) { return false; }
        if (!t2) { return true; }
        string s1{}, s2{};
        preorder(t1,s1);
        preorder(t2,s2);
        return s1.find(s2) != string::npos;
    }
    
    void preorder(shared_ptr<TreeNode<T>> root, string& str){
        if (!root) { str+="(X)"; return; }
        str+="("+to_string(root->val)+")";
        preorder(root->left, str);
        preorder(root->right, str);
    }
    

    /*----------------------------------------------------------------------
     4.11 Random Node: You are implementing a binary tree class from scratch which,
     in addition to insert, find, and delete, has a method getRandomNode()
     which returns a random node from the tree.  All Nodes should be equally
     likely to be chosen.  Design and implement an algorithm for getRandomNode,
     and explain how you would implement the rest of the methods.
     ----------------------------------------------------------------------*/
    shared_ptr<TreeNode<T>> RandomNode(shared_ptr<TreeNode<T>> root){
        if (!root) { return nullptr; }
        vector<shared_ptr<TreeNode<T>>> v{};
        queue<shared_ptr<TreeNode<T>>> q{};
        q.push(root);
        while (!q.empty()){
            v.push_back(q.front());
            q.pop();
            if (v.back()->left) { q.push(v.back()->left); }
            if (v.back()->right) { q.push(v.back()->right); }
        }
        return v[rand()%v.size()];
    }
    

    /*----------------------------------------------------------------------
     4.12 Paths with Sum: You are given a binary tree in which each node
     contains an integer value (which might be positive or negative).  Design
     an algorithm to count the number of paths that sum to a given value.
     The path does not need to start or end at the root or a leaf, but it must
     go downwards (traveling only from parent nodes to child nodes).
     ----------------------------------------------------------------------*/
    int PathsWithSum(shared_ptr<TreeNode<T>> root, int target){
        int paths=0;
        queue<shared_ptr<TreeNode<T>>> q{};
        q.push(root);
        while (!q.empty()){
            auto curr=q.front(); q.pop();
            PathSum(curr,0,target,paths);
            if (curr->left) { q.push(curr->left); }
            if (curr->right) { q.push(curr->right); }
        }
        return paths;
    }
    
    void PathSum(shared_ptr<TreeNode<T>> root, int currSum, int target, int& paths){
        if (!root) { return; }
        currSum+=root->val;
        if (currSum==target) { paths++; }
        PathSum(root->left, currSum, target, paths);
        PathSum(root->right, currSum, target, paths);
    }
    
};


int main(int argc, const char * argv[]) {

    auto root=make_shared<TreeNode<int>>(10);
    root->right=make_shared<TreeNode<int>>(-2);
    root->left=make_shared<TreeNode<int>>(3);
    root->left->left=make_shared<TreeNode<int>>(3);
    root->left->right=make_shared<TreeNode<int>>(5);
    root->left->left->left=make_shared<TreeNode<int>>(2);
    root->left->right->right=make_shared<TreeNode<int>>(-10);
    Solution<int> solution;
    
    while(true){
        cout << solution.RandomNode(root)->val << endl;
    }
    
    return 0;
}






