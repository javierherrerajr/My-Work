#include "arithmeticExpression.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>

using namespace std;

// constructor for empty tree
arithmeticExpression::arithmeticExpression(const string &exprParam) {
    root = nullptr;
    infixExpression = exprParam;
}

// generates the tree and assigns the root node to the top of the stack
void arithmeticExpression::buildTree(){ 
    infixExpression = infix_to_postfix();
    stack<TreeNode*> treeBuilder;
    
    for(unsigned i = 0; i < infixExpression.length(); i++){ //goes through the length of the expression
        TreeNode* node = new TreeNode(infixExpression.at(i), 'a' + i);
        if(priority(infixExpression.at(i)) == 0){//means its not an operator 
            treeBuilder.push(node); //push onto the stack
        }
        else{ //means its an operator
            node -> right = treeBuilder.top(); //second val is right
            treeBuilder.pop();
            node -> left = treeBuilder.top(); //first val is left
            treeBuilder.pop();
            treeBuilder.push(node); //push the operator 
        }
    }
    root = treeBuilder.top(); // sets the root of the tree
}

//generates .png files
void arithmeticExpression::visualizeTree(const string &outputFilename) { 
    ofstream fout(outputFilename.c_str()); // converts string to an array of characters for system function call later. 

    fout.open(outputFilename);

    if(!fout.is_open()){
        throw runtime_error("Error opeing file"); // exception if file doesn't open 
    }

    fout<<"digraph G {"<<endl;
    visualizeTree(fout,root); // writes everything to file
    fout<<"}";
    fout.close();
    string command = "dot -Tjpg " + outputFilename + " -o " + outputFilename.substr(0,outputFilename.size()-4)+".jpg"; // command to generate the png file
    system(command.c_str()); // generates file. 
}

//private functions
//returns the priority of the given operator. used later to sort Tree. 
int arithmeticExpression::priority(char op){ 
    if(op == '(') {
        return 3;
    }

    else if(op == '*' || op == '/') {
        return 2; 
    }

    else if(op == '+' || op == '-') {
        return 1;
    }

    return 0;
}

// fixes infixExpression to follow postfix notation
string arithmeticExpression::infix_to_postfix(){
    stack<char> infix; // empty stack to create proper postfix notation
    ostringstream fout; // writes it to be able to return final string product
    char option;

    // algorithm for proper postfix notation
    for(unsigned i = 0; i< infixExpression.size();++i) {
        option = infixExpression.at(i);
        if(option == '+' || option == '-' || option == '*' || option == '/' || option == '(' || option == ')') { // option is an operator
            if( option == '(') {
                infix.push(option);
            }

            else if(option == ')') {
                while(infix.top() != '('){
                    fout << infix.top();
                    infix.pop();
                }
                infix.pop();
            }

            else {
                while(!infix.empty() && priority(option) <= priority(infix.top())){
                    if(infix.top() == '('){
                        break;
                    }
                    fout << infix.top();
                    infix.pop();
                }
                infix.push(option);
            }
        }

        else if (option == ' ') {
            continue; 
        }

        else{ //option is an operand
            fout << option;
        }
    }

    while(!infix.empty()) { // final construction for output string stream. 
        fout << infix.top();
        infix.pop();
    }

    return fout.str();
}

//performs the inorder traversal to correct the arithmetic expression tree
void arithmeticExpression::infix(TreeNode *node){ 
     if (node != nullptr) {
        if (node->left != nullptr) {
            cout << '(';
        }
        
        //recursive calls to go through the left and right side of the tree. 
        infix(node->left);
        cout << node->data;
        infix(node->right);

        if (node->left != nullptr) {
            cout << ')';
        }
    }

}

// performs postorder traversal for the tree
void arithmeticExpression::postfix(TreeNode *node){
    //base case
	if (node == nullptr) {
		return;
	}

    // checks the left and right before outputting. 
	postfix(node->left);
	postfix(node->right);
	cout << node->data;
}

// performs preorder traversal for tree
void arithmeticExpression::prefix(TreeNode *node){
    // base case
    if (node == nullptr) {
		return;
	}
    // outputs before ordering. 
	cout << node->data;
	prefix(node->left);
	prefix(node->right);
}

// generates the dotty file to show the graph 
void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *node){ 
    // checks if node exists
    if(node != nullptr ) {
        // if left exists, it writes the left data
        if(node -> left != nullptr){
            out << node->key << " [ label = " << "\"" << node->data << "\"" << "];" << endl;
			out << node->left->key << " [ label = " << "\"" << node->left->data << "\"" << "];" << endl;
			out << node->key << " -> " << node->left->key << endl;
            // vice versa ^
            if(node->right!= nullptr){
                out << node -> right ->key << " [ label = " << "\"" << node->right -> data << "\"" << "];" << endl;
                out << node->key << " -> " << node -> right ->key << endl;
                visualizeTree(out, node->left);
                visualizeTree(out, node->right);
            }
            // if right side doesn't exist
            else {
                visualizeTree(out, node->left);
            }
        }

        else {
            if(node->right != nullptr) {
                out << node->key << " [ label = " << "\"" << node->data << "\"" << "];" << endl;
			    out << node->right->key << " [ label = " << "\"" << node->right->data << "\"" << "];" << endl;
			    out << node->key << " -> " << node->right->key << endl;
                visualizeTree(out, node->right);
            }
        }
    }
}