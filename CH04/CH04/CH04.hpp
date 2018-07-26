/*
 
 CCI CH04: Graphs and Trees
 
 */

#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;
using VI=vector<int>;
using VVI=vector<VI>;

//
// Question 4.1 Route Between Nodes: Given a directed graph, design an algorithm
// to find out whether there is a route between two nodes
//
// Answer 4.1: let G be the directed graph represented as a vector of vectors of ints
// where G[i] contains all nodes which i is connected towards.  Let G be of size N,
// where each node is uniquely identified by its integer value [0:N).
//
// Let src be the source node which we will start.  Let dst be the destination node
// which is our target to arrive at from src.  A BFS search can be used to determine
// if there is a route from src to dst.  If found, return true, otherwise return false.
//
class Solution_4_1 {
public:
    bool isRoute(const VVI& G, int src, int dst) const {
        queue<int> q({src}); unordered_set<int> V({src});
        while (!q.empty()){
            auto curr=q.front(); q.pop();
            if (curr==dst) return true;
            for (auto nei: G[curr])
                if (V.insert(nei).second)
                    q.push(nei);
        }
        return false;
    }
};

//
// Question 4.2 Minimal Tree: Given a sorted (increaing order) array with unique integer elements,
// write an algorithm to create a binary search tree with minimal height.
//
// Answer 4.2: for each sub-vector from indices [i:j), calculate the root, then continually
// split into each sub-vector into sub-vectors until the leaf nodes end up with nullptr as left/right children.
// This occurs when i==j
//
struct TreeNode{
    int val;
    TreeNode *left,*right,*parent;
    TreeNode(int x) : val{x},left{nullptr},right{nullptr},parent{nullptr} {}
};
class Solution_4_2 {
public:
    TreeNode* toTree(VI& A) const {
        int i=0,j=(int)A.size();
        return go(A,i,j);
    }
private:
    TreeNode* go(const VI& A, int i, int j) const {
        if (i==j) return nullptr;
        int mid=(i+j)/2;
        TreeNode* node=new TreeNode(A[mid]);
        node->left=go(A,i,mid);
        node->right=go(A,mid+1,j);
        return node;
    }
};

//
// Question 4.3 List of Depths: Given a binary tree, design an algorithm which creates a linked list
// of all nodes at each depth (e.g. if you have a tree with depth D, you'll have D linked lists
//
// Answer 4.3: traverse the tree in any order (pre,in,post) and keep track of the ongoing depth
// if a new depth is reached, append a new linked list onto a vector a linked lists for each depth.
// Note: d is a r-value reference which tracks the current "d"epth.
//
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val{x},next{nullptr} {}
};
class Solution_4_3 {
public:
    vector<ListNode*> toDepthList(TreeNode* root) const {
        vector<ListNode*> ans;
        if (root)
            go(root,ans);
        return ans;
    }
private:
    void go(TreeNode* node, vector<ListNode*>& res, int&& d=0) const {
        if (res.size()==d)
            res.push_back(new ListNode(node->val));
        else{
            auto itr=res.back();
            while (itr->next)
                itr=itr->next;
            itr->next=new ListNode(node->val);
        }
        if (node->left) go(node->left,res,d+1);
        if (node->right) go(node->right,res,d+1);
    }
};

//
// Question 4.4 Check Balanced: Implement a function to check if a binary tree is balanced.
// For the purposes of this question, a balanced tree is defined to be a tree such that the heights
// of the two subtrees of any node never differ by more than one
//
// Answer 4.4: perform post-order traversal, return the maximum of the left/right subtrees for each node
// if ever the left/right subtrees differ by more than one, then set ans false
//
class Solution_4_4{
public:
    bool isBalanced(TreeNode* root) const {
        bool ans=true;
        if (root)
            go(root,ans);
        return ans;
    }
private:
    int go(TreeNode* root, bool& ans, int&& d=0) const {
        if (!ans)
            return 0;
        int left=(root->left) ? go(root->left,ans,d+1) : d;
        int right=(root->right) ? go(root->right,ans,d+1) : d;
        if (abs(left-right)>1)
            ans=false;
        return max(left,right);
    }
};

//
// Question 4.5 Validate BST: Implement a function to check if a binary tree is a binary search tree.
//
// Answer 4.5: assuming strictly less than or equal / greater than or equal,
// post-order traverse the tree and ensure: left <= root <= right,
// set ans=false immediately when this condition is violated and return immediately
// otherwise return the maximum value from the left and the minimum value from the right
// and keep checking the same during the entire post-order traversal
//
class Solution_4_5{
public:
    bool isBST(TreeNode* root) const {
        bool ans=true;
        if (root)
            go(root,ans);
        return ans;
    }
private:
    pair<int,int> go(TreeNode* root, bool& ans) const {
        if (!ans)
            return {0,0};
        auto L=(root->left) ? go(root->left,ans) : make_pair(root->val,root->val);
        auto R=(root->right) ? go(root->right,ans) : make_pair(root->val,root->val);
        if (! (L.second <= root->val && root->val <= R.first) ){
            ans=false;
            return {0,0};
        }
        return {L.second,R.first};
    }
};

//
// Question 4.6 Successor: Write an algorithm to find the "next" node (i.e., in-order successor)
// of a given node in a binary search tree.  You may assume that each node has a link to its parent
//
// Answer 4.6: assuming the input node is not the largest value in the BST ( i.e. there is an answer )
// then there are two use-cases to consider:
// 1) if there is a right child, then return the left-most child value of the right child
// 2) if there is NO right child, then return the parent
// a third use-case to consider is if there is no valid answer, we can just return the node value
// itself.  this occurs when there is no answer ( i.e. no right child and no parent with value > node value )
//
class Solution_4_6{
public:
    TreeNode* successor(TreeNode* root) const {
        if (!root){
            return root;
        }else if (!root->right){
            if (!root->parent || root->parent->val < root->val)
                return root;
            else
                return root->parent;
        }else{
            auto itr=root->right;
            for (; itr->left; itr=itr->left);
            return itr;
        }
    }
};

//
// Question 4.7 Build Order: You are given a list of projects and a list of dependencies
// (which is a list of pairs of projects, where the second project is dependent on the first project).
// All of a project's dependencies must be built before the project is.  Find a build order that will
// allow the projects to be built.  If there is no valid build order, return an error
//
// Answer: let projects be considered as nodes in a graph, let A->B denote B is dependent upon A.
// This relationship is represented as G[A]={B}.  If C is also dependend upon A, then G[A]={B,C}
// Let D[i] denote the incoming dependency count for node with unique value i.  D[A]=0, D[B]=1, D[C]=1
// Perform BFS by continually trimming projects which have no dependencies.  For above example,
// the queue will be initialized with A and B has 1 depedency.  When A is "removed", B's dependency
// count is decremented, and since it reaches 0, B is also placed on the queue to be processed.
// keep track of the nodes visited by this BFS queue.  If the visited count is equal to the amount of nodes
// then all nodes could be successfully processed in this BFS queue, so return true, otherwise return false.
//
// assume each project is denoted by a unique integer [0:P) for a list of P projects to be checked
//
class Solution_4_7{
public:
    bool validBuildOrder(const VVI& G, const int N) const {
        if (N==0)
            return true;
        VI D(N);
        for (int i=0; i<N; ++i)
            for (auto dep: G[i])
                ++D[dep];
        queue<int> q; unordered_set<int> V;
        for (int i=0; i<N; ++i)
            if (D[i]==0)
                q.push(i),V.insert(i);
        while (!q.empty()){
            auto curr=q.front(); q.pop();
            for (auto nei: G[curr])
                if (--D[nei]==0)
                    q.push(nei),V.insert(nei);
        }
        return V.size()==N;
    }
};

//
// Question 4.8 First Common Ancestor: Design an algorithm and write code to find
// the first commmon ancestor of two nodes in a binary tree.  Avoid storing additional nodes
// in a data structure.  NOTE: this is not necessaryily a binary search tree.
//
// Answer 4.8: ensure both p and q exist in the tree first.  If one is missing, then return nullptr.
// Otherwise find and return the FCA.
//
// use cases:
//
// p equals q return either p or q immediately
// p & q are in the left subtree --> further check left
// p & q are in the right subtree --> further check right
// p is in one subtree and q is in the other subtree --> return current node as FCA
// p xor q are the current node, and p xor q is a child of the current node --> return the current node
//
class Solution_4_8{
public:
    TreeNode* firstCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) const {
        if (p==q)
            return p;
        else if (!root || !p || !q)
            return nullptr;
        else
            return go(root,p,q);
    }
private:
    TreeNode* go(TreeNode* root, TreeNode* p, TreeNode* q) const {
        auto L=(root->left) ? go(root->left,p,q) : nullptr;
        auto R=(root->right) ? go(root->right,p,q) : nullptr;
        if (L && R)
            return root;
        if (p==root || q==root)
            return root;
        return L ? L : R;
    }
};

//
// Question 4.9 BST Sequences: A binary search tree was created by traversing through an array
// from left to right and inserting each element.  Given a binary search tree with distinct elements,
// print all possible arrays that could have led to this tree.
//
// EXAMPLE:
//     2
//    / \
//   1   3
//
// Output: {2,1,3},{2,3,1}
//



//
// Question 4.10 Check Subtree: T1 and T2 are two very large binary trees, with T1 much bigger than T2.
// Create an algorithm to determine if T2 is a substree of T1.
// A tree T2 is a subtree of T1 if there exists a node n in T1 such that the substree of n is identical to T2.
// That is, if you cut off the tree at node n, the two trees would be identical.
//
// Answer 4.10: post-order traverse T1, for each node in T1 traversal which matches T2 root,
// try to traverse both T1 and T2 together, if T2 is completely traversed, then return true
// keep track of complete traversal by tracking the size of T2 as N
//
class Solution_4_10{
public:
    bool isSubtree(TreeNode* T1, TreeNode* T2) const {
        int N=traverseBoth(T2,T2);
        return go(T1,T2,N);
    }
private:
    int traverseBoth(TreeNode* T1, TreeNode* T2) const {
        if (T1==nullptr && T2==nullptr)
            return 1;
        if (T1==nullptr || T2==nullptr || T1->val != T2->val)
            return 0;
        int L=traverseBoth(T1->left,T2->left);
        int R=traverseBoth(T1->right,T2->right);
        return 1+L+R;
        
    }
    bool go(TreeNode* T1, TreeNode* T2, const int N) const {
        if (traverseBoth(T1,T2)==N)
            return true;
        bool L=T1->left ? go(T1->left,T2,N) : false;
        bool R=T1->right ? go(T1->right,T2,N) : false;
        return L || R;
    }
};

//
// Question 4.12 Paths with Sum: You are given a binary tree in which each node contains an integer value
// (which might be positive or negative).  Design an algorithm to count the number of paths that sum
// to a given value.  The path does not need to start or end at the root or a leaf, but it must go downwards
// (traveling only from parent nodes to child nodes).
//
// Answer 4.12: traverse the tree, (pre,in,post) order doesn't matter.  Then perform DFS starting at each
// node in the traversal to see if there is a path with target sum beginning at the current node.
// Each time the sum is equal to the target, increment the ongoing count to be returned
//
class Solution_4_12 {
public:
    int pathsWithSum(TreeNode* root, const int target) const {
        int ans=0;
        if (root)
            traverse(root,target,ans);
        return ans;
    }
private:
    void traverse(TreeNode* root, const int target, int& ans) const {
        go(root,target,ans);
        if (root->left)
            traverse(root->left,target,ans);
        if (root->right)
            traverse(root->right,target,ans);
    }
    void go(TreeNode* root, const int target, int& ans, int&& sum=0) const {
        sum+=root->val;
        if (sum==target)
            ++ans;
        if (root->left)
            go(root->left,target,ans,std::move(sum));
        if (root->right)
            go(root->right,target,ans,std::move(sum));
    }
};

