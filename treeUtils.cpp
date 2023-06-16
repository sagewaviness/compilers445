#include <string> 
#include "treeUtils.h"
#include "treeNodes.h"

 
extern void yyerror(const char *msg);

static int nodeNum = 0; 



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

        newNode->size = 1; 
        newNode->varKind = Local;
        newNode->offset = 0;
        newNode->isArray = false; 
        newNode->isStatic = false;
        newNode->isConst = false; 

        newNode->nodekind = StmtK; 
        newNode->kind.stmt = kind; 
    }

    return newNode;
}

TreeNode *newExpNode(ExpKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
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

        newNode->size = 1;
        newNode->varKind = Local;
        newNode->offset = 0;
        newNode->isArray = false;
        newNode->isStatic = false;
        newNode->isConst = false;

        newNode->nodekind = ExpK;
        newNode->kind.exp = kind;
    }

    return newNode;
}

TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
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

char *varKindTokenStr(int kind)
{
    switch(kind)
    {
       case None: 
            return (char *) "None";
       case Local: 
            return (char *) "Local";
       case Global:
            return (char *) "Global";
       case Parameter:
            return (char *) "Parameter";
       case LocalStatic:
            return (char *) "LocalStatic";
       default: 
            return (char *) "unknownVarKind";

    }
}

// allocate a FIX BUFFER.  You must copy the string if you
// // are referencing the function twice in the same printf for example.
char expTypeToStrBuffer[80]; 
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
        return buffer;
    }
   // add static and array attributes
    // static type int
    // static array of type int
    sprintf(expTypeToStrBuffer, "%s%s%s", isStatic ? "static" : "", isArray ? "array of " : "");
    return strdup(expTypeToStrBuffer); // memory leak
    
}

void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
  //add stuff
}


char *tokenToStr(int type)
{
  // add stuff here
  return expTypeToStrBuffer;
}