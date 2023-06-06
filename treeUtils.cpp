#include "treeUtils.h"

#include "dot.h"

/**
 * @brief creates a new node
 * 
 * @param kind passes what type of statement it is
 * @param token what the data is 
 * @param c0 child one
 * @param c1 child tw0
 * @param c2 child 3
 * @return TreeNode* 
 */
TreeNode *newStmtNode(StmtKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *newNode; 
    int i; 
    
    newNode = new TreeNode;
    // newNode->nodeNum = nodeNum++;
    // more code 

    return newNode;
}

//  newExpNode • exp
//     • simpleExp
//     • andExp
//     • unaryRelExp • relExp
//     • minmaxExpn • sumExp
//     • mulExp
//     • unaryExp
//     • mutable
//     • call
//     • constant
// • newDeclNode 
//  • varDeclId
//  • funDecl
//  • matched : FOR ID '=' iterRange DO matched
//  • unmatched : FOR ID '=' iterRange DO unmatched
// • printTree
//  • Put a call to printTree at the end of your main
// to print dot tree add this line after your tree is created 
// printDotTree(astDot, syntaxTree, false, false);