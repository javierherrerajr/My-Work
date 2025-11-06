#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H
#include <iostream>
#include <cstdlib>

using namespace std;

//structure for TreeNode type variables
struct TreeNode{ 
    char data; // data passed in
    char key; // used to keep track of nodes in Tree
    TreeNode* left; // left side of a node if applicable
    TreeNode* right; // right side of a node if applicable
    TreeNode(char data, char key):data(data),key(key),left(nullptr),right(nullptr){} // constructor for node
};

// arithmeticExpression class 
class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;
  public:
    /* Initializes an empty tree and sets the infixExpression
    to the value of parameter passed in. */
    arithmeticExpression(const string &exprParam);

    /* Implementation of destrucor is optional.
       The destructor should deallocate all the nodes in the tree. */
    //~arithmeticExpression();

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
    void buildTree();

    /* Calls the recursive infix function. */
    void infix() {infix(root);}

    /* Calls the recursive prefix function. */
    void prefix() {prefix(root);}

    /* Calls the recursive postfix function. */
    void postfix() {postfix(root);}

    /* Calls the recursive visualizeTree function and generates the .png file using system call. */
    void visualizeTree(const string &);

 private:
    /* Helper function that returns an integer according to
       the priority of the given operator. */
    int priority(char);

    /* Helper function that returns the postfix notation equivalent
       to the given infix expression */
    string infix_to_postfix();

    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
    void infix(TreeNode *);

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
    void prefix(TreeNode *);

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void postfix(TreeNode *);

    /* Helper function for generating the dotty file. This is a recursive function. */
    void visualizeTree(ofstream &, TreeNode *);
};

#endif