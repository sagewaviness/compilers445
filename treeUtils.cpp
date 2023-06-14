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
    newNode->nodeNum = nodeNum++;

    if(newNode == NULL)
    {
        yyerror("ERROR: Out of memory");
    }
    else
    {
        newNode->child[0] = c0; 
        newNode->child[1] = c1; 
        newNode->child[2] = c2;

        newNode->sibling = NULL;
        newNode->lineno = (token ? token->linenum: -1);
        newNode->attr.name =(token ? token->svalue : strdup("BLAH"));
        newNode->type = type; 

        newNode->size = 1; 
        newNode->varKind = Local;
        newNode->offset = 0;
        newNode->isArray = false; 
        newNode->isStatic = false;
        newNode->isConst = false; 

        newNode->nodekind = DeclK; 
        newNode->kind.decl = kind; 
    }

    return newNode;
}

char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
    char *typeName;

    switch(type)
    {
        case Void: 
                typeName = (char *)"type void";
                break;
        case Integer: 
                typeName = (char *)"type int";
                break;
        case Boolean: 
                typeName = (char *)"type bool";
                break;
        case Char: 
                typeName = (char *)"type char";
                break;
        case UndefinedType: 
                typeName = (char *)"type undefined type";
                break;
        default: 
                char *buffer;
                buffer = new char[80]; 
                sprintf(buffer, "invalid expType: %d", (int)type);
    }

    sprintf(expTypeToStrBuffer, "%s%s%s", isStatic ? "static" : "", isArray ? "array of " : "");
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