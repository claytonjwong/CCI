/*
 
 CCI CH04 Unit Tests
 
 */

#include "TestHarness.h"
#include "CH04.hpp"

using namespace std;
using VI=vector<int>;
using VVI=vector<VI>;

//************************************************************************

// Solution 4.1

TEST(isRouteSrcAndDstSame,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=0;
    VVI G{{}};
    CHECK(solution.isRoute(G,src,dst))
}

TEST(isRouteSrcAndDstDiff,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=1;
    VVI G{
        {},
        {},
    };
    CHECK(solution.isRoute(G,src,dst)==false)
}

TEST(isRoute1,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=1;
    VVI G{
        {1},
        {},
    };
    CHECK(solution.isRoute(G,src,dst));
}

TEST(isRoute2,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=1;
    VVI G{
        {},
        {0},
    };
    CHECK(solution.isRoute(G,src,dst)==false);
}

TEST(isRoute3,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=2;
    VVI G{
        {1},
        {2},
        {}
    };
    CHECK(solution.isRoute(G,src,dst));
}

TEST(isRoute4,Solution_4_1){
    Solution_4_1 solution;
    int src=1,dst=2;
    VVI G{
        {1},
        {2},
        {}
    };
    CHECK(solution.isRoute(G,src,dst));
}

TEST(isRoute5,Solution_4_1){
    Solution_4_1 solution;
    int src=0,dst=6;
    VVI G{
        {1,3,4,5},
        {2},
        {5,6},
        {},
        {},
        {},
        {},
    };
    CHECK(solution.isRoute(G,src,dst));
}

//************************************************************************

// Solution 4.2

TEST(toTree1,Solution_4_2){
    Solution_4_2 solution;
    VI A;
    CHECK(solution.toTree(A)==nullptr);
}

TEST(toTree2,Solution_4_2){
    Solution_4_2 solution;
    VI A{1,2,3};
    TreeNode* x=solution.toTree(A);
    CHECK(x->val==2);
    CHECK(x->left->val==1);
    CHECK(x->right->val==3);
}

TEST(toTree3,Solution_4_2){
    Solution_4_2 solution;
    VI A{1,2,3,4};
    TreeNode* x=solution.toTree(A);
    CHECK(x->val==3);
    CHECK(x->left->val==2);
    CHECK(x->left->left->val==1);
    CHECK(x->left->right==nullptr);
    CHECK(x->right->val==4);
    CHECK(x->right->left==nullptr);
    CHECK(x->right->right==nullptr);
}

//************************************************************************

// Solution 4.3

TEST(toDepthList,Solution_4_3){
    Solution_4_3 solution;
    TreeNode* root=nullptr;
    auto res=solution.toDepthList(root);
    CHECK(res.empty());
}

TEST(toDepthList2,Solution_4_3){
    Solution_4_3 solution;
    TreeNode* root=new TreeNode(5);
    auto res=solution.toDepthList(root);
    CHECK(res.size()==1);
    CHECK(res[0]->val==5);
}

TEST(toDepthList3,Solution_4_3){
    Solution_4_3 solution;
    TreeNode* root=new TreeNode(5);
    root->left=new TreeNode(3);
    root->right=new TreeNode(4);
    auto res=solution.toDepthList(root);
    CHECK(res.size()==2);
    CHECK(res[0]->val==5);
    CHECK(res[1]->val==3);
    CHECK(res[1]->next->val==4);
}

TEST(toDepthList4,Solution_4_3){
    Solution_4_3 solution;
    TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->left->left=new TreeNode(3);
    root->left->left->left=new TreeNode(4);
    auto res=solution.toDepthList(root);
    CHECK(res.size()==4);
    CHECK(res[0]->val==1);
    CHECK(res[1]->val==2);
    CHECK(res[2]->val==3);
    CHECK(res[3]->val==4);
}

//************************************************************************

// Solution 4.4

TEST(isBalanced1,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=nullptr;
    CHECK(solution.isBalanced(root));
}

TEST(isBalanced2,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    CHECK(solution.isBalanced(root));
}

TEST(isBalanced3,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    root->left=new TreeNode(3);
    CHECK(solution.isBalanced(root));
}

TEST(isBalanced4,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    root->right=new TreeNode(4);
    CHECK(solution.isBalanced(root));
}

TEST(isBalanced5,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    root->right=new TreeNode(4);
    root->right->left=new TreeNode(2);
    CHECK(solution.isBalanced(root)==false);
}

TEST(isBalanced6,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    root->left=new TreeNode(3);
    root->right=new TreeNode(4);
    root->right->left=new TreeNode(2);
    root->right->right=new TreeNode(1);
    CHECK(solution.isBalanced(root));
}

TEST(isBalanced7,Solution_4_4){
    Solution_4_4 solution;
    TreeNode* root=new TreeNode(5);
    root->left=new TreeNode(3);
    root->left->left=new TreeNode(69);
    root->left->left->left=new TreeNode(72);
    root->right=new TreeNode(4);
    root->right->left=new TreeNode(2);
    root->right->right=new TreeNode(1);
    CHECK(solution.isBalanced(root)==false);
}

//************************************************************************

// Solution 4.5

TEST(isBST1,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=nullptr;
    CHECK(solution.isBST(root));
}

TEST(isBST2,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=new TreeNode(10);
    CHECK(solution.isBST(root));
}

TEST(isBST3,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5);
    CHECK(solution.isBST(root));
}

TEST(isBST4,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5);
    root->right=new TreeNode(15);
    CHECK(solution.isBST(root));
}

TEST(isBST5,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5);
    root->left->left=new TreeNode(5);
    root->right=new TreeNode(15);
    CHECK(solution.isBST(root));
}

TEST(isBST6,Solution_4_5){
    Solution_4_5 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5);
    root->left->left=new TreeNode(4);
    root->left->right=new TreeNode(6);
    root->right=new TreeNode(15);
    root->right->left=new TreeNode(9);
    CHECK(solution.isBST(root)==false);
}

//************************************************************************

// Solution 4.6

TEST(successor1,Solution_4_6){
    Solution_4_6 solution;
    TreeNode* root=nullptr;
    CHECK(solution.successor(root)==nullptr);
}

TEST(successor2,Solution_4_6){
    Solution_4_6 solution;
    TreeNode* root=new TreeNode(10);
    CHECK(solution.successor(root)->val==10);
}

TEST(successor3,Solution_4_6){
    Solution_4_6 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5); root->left->parent=root;
    CHECK(solution.successor(root->left)->val==10);
}

TEST(successor4,Solution_4_6){
    Solution_4_6 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5); root->left->parent=root;
    root->left->right=new TreeNode(8); root->left->right->parent=root;
    CHECK(solution.successor(root->left)->val==8);
}

TEST(successor5,Solution_4_6){
    Solution_4_6 solution;
    TreeNode* root=new TreeNode(10);
    root->left=new TreeNode(5); root->left->parent=root;
    root->left->right=new TreeNode(8); root->left->right->parent=root;
    root->left->right->left=new TreeNode(7); root->left->right->left->parent=root->left->right;
    CHECK(solution.successor(root->left)->val==7);
}

//************************************************************************

// Solution 4.7

TEST(validBuildOrder1,Solution_4_7){
    Solution_4_7 solution;
    //
    // 0->1
    //
    VVI G{
        {},
        {0},
    };
    int N=2;
    CHECK(solution.validBuildOrder(G,N));
}

TEST(validBuildOrder2,Solution_4_7){
    Solution_4_7 solution;
    //
    // 0->1->2
    //
    VVI G{
        {},
        {0},
        {1},
    };
    int N=3;
    CHECK(solution.validBuildOrder(G,N));
}

TEST(validBuildOrder3,Solution_4_7){
    Solution_4_7 solution;
    //
    //           3
    // 0->1->2
    //           4
    VVI G{
        {},
        {0},
        {1},
        {},
        {},
    };
    int N=5;
    CHECK(solution.validBuildOrder(G,N));
}

TEST(validBuildOrder4,Solution_4_7){
    Solution_4_7 solution;
    //
    // |---------->3
    // 0->1->2
    //    |------->4
    VVI G{
        {},
        {0},
        {1},
        {0},
        {1},
    };
    int N=5;
    CHECK(solution.validBuildOrder(G,N));
}

TEST(validBuildOrder5,Solution_4_7){
    Solution_4_7 solution;
    //
    // |---------->3
    // 0->1->2
    // |-----^
    VVI G{
        {},
        {0},
        {0,1},
        {0},
    };
    int N=4;
    CHECK(solution.validBuildOrder(G,N));
}

TEST(validBuildOrder6,Solution_4_7){
    Solution_4_7 solution;
    //
    // V-----|
    // 0->1->2
    // |-----^
    VVI G{
        {2},
        {0},
        {0,1},
    };
    int N=3;
    CHECK(solution.validBuildOrder(G,N)==false);
}

//************************************************************************

// Solution 4.8

TEST(firstCommonAncestor1,Solution_4_8){
    Solution_4_8 solution;
    TreeNode *root=nullptr,*p=nullptr,*q=nullptr;
    CHECK(solution.firstCommonAncestor(root,p,q)==nullptr);
}

TEST(firstCommonAncestor2,Solution_4_8){
    Solution_4_8 solution;
    TreeNode *root=new TreeNode(10),*p=root,*q=root;
    CHECK(solution.firstCommonAncestor(root,p,q)==root);
}

TEST(firstCommonAncestor3,Solution_4_8){
    Solution_4_8 solution;
    TreeNode *root=new TreeNode(10);
    root->left=new TreeNode(22);
    root->right=new TreeNode(33);
    auto p=root->left,q=root->right;
    CHECK(solution.firstCommonAncestor(root,p,q)==root);
}

TEST(firstCommonAncestor4,Solution_4_8){
    Solution_4_8 solution;
    TreeNode *root=new TreeNode(10);
    root->left=new TreeNode(22);
    root->right=new TreeNode(33);
    auto p=root,q=root->right;
    CHECK(solution.firstCommonAncestor(root,p,q)==root);
}

TEST(firstCommonAncestor5,Solution_4_8){
    Solution_4_8 solution;
    TreeNode *root=new TreeNode(10);
    root->left=new TreeNode(22);
    root->right=new TreeNode(33);
    auto p=root->left,q=root;
    CHECK(solution.firstCommonAncestor(root,p,q)==root);
}


//************************************************************************

// Solution 4.10

TEST(isSubtree1,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=nullptr;
    TreeNode* T2=nullptr;
    CHECK(solution.isSubtree(T1,T2));
}

TEST(isSubtree2,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    TreeNode* T2=nullptr;
    CHECK(solution.isSubtree(T1,T2)==false);
}

TEST(isSubtree3,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    TreeNode* T2=new TreeNode(10);
    CHECK(solution.isSubtree(T1,T2));
}

TEST(isSubtree4,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    T1->left=new TreeNode(5);
    TreeNode* T2=new TreeNode(10);
    CHECK(solution.isSubtree(T1,T2)==false);
}

TEST(isSubtree5,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    T1->left=new TreeNode(5);
    TreeNode* T2=new TreeNode(10);
    T2->left=new TreeNode(5);
    CHECK(solution.isSubtree(T1,T2));
}

TEST(isSubtree6,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    T1->left=new TreeNode(5);
    TreeNode* T2=new TreeNode(10);
    T2->right=new TreeNode(5);
    CHECK(solution.isSubtree(T1,T2)==false);
}

TEST(isSubtree7,Solution_4_10){
    Solution_4_10 solution;
    TreeNode* T1=new TreeNode(10);
    T1->left=new TreeNode(5);
    T1->right=new TreeNode(6);
    TreeNode* T2=new TreeNode(10);
    T2->left=new TreeNode(5);
    T2->right=new TreeNode(6);
    CHECK(solution.isSubtree(T1,T2));
}

//************************************************************************

// Solution 4.12

TEST(pathsWithSum1,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=nullptr;
    CHECK(solution.pathsWithSum(root,0)==0);
}

TEST(pathsWithSum2,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=new TreeNode(69);
    CHECK(solution.pathsWithSum(root,69)==1);
}

TEST(pathsWithSum3,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=new TreeNode(69);
    root->left=new TreeNode(0);
    CHECK(solution.pathsWithSum(root,69)==2);
}

TEST(pathsWithSum4,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=new TreeNode(69);
    root->left=new TreeNode(0);
    root->right=new TreeNode(0);
    CHECK(solution.pathsWithSum(root,69)==3);
}

TEST(pathsWithSum5,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=new TreeNode(69);
    root->left=new TreeNode(0);
    root->right=new TreeNode(10);
    root->right->right=new TreeNode(-10);
    CHECK(solution.pathsWithSum(root,69)==3);
}

TEST(pathsWithSum6,Solution_4_12){
    Solution_4_12 solution;
    TreeNode* root=new TreeNode(1);
    root->left=new TreeNode(2);
    root->right=new TreeNode(3);
    CHECK(solution.pathsWithSum(root,3)==2);
}

