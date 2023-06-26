#include <string>
#include <iostream> 
#include "treeUtils.h"
#include <cstdio>
#include "treeNodes.h"
using namespace std;
 
extern void yyerror(const char *msg);

static int nodeNum = 0; 

//void printTreeNode(FILE *out, TreeNode *node, bool showExpType, bool showAllocation);

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
    //printf("in new statment node int %d, char %c\n", token,token );
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
	newNode->type = UndefinedType;
	////
	//printf("in newexpnode int %d char %c\n" ,token->tokenclass, token->tokenclass );
        newNode->attr.op = OpKind(token->tokenclass);
        //printf("in newexpnode attr.op int %d char %c\n" ,newNode->attr.op, newNode->attr.op);
        //newNode->attr.name =(token ? token->svalue : strdup("BLAH"));

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

char *varKindToStr(int kind)
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
/*
char expTypeToStrBuffer[80]; 
char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
    //cout << "in exptypetostr\n";
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
   
    sprintf(expTypeToStrBuffer, "%s%s%s", isStatic ? "static" : "", isArray ? "array of " : "");
    return strdup(expTypeToStrBuffer);
}*/

char expTypeToStrBuffer[80];
char *expTypeToStr(ExpType type, bool isArray, bool isStatic)
{
    char *typeName;

    switch (type) {
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
       typeName = (char *)"undefined type";
       break;
    default:
       char *buffer;
       buffer = new char [80];
       sprintf(buffer, "invalid expType: %d", (int)type);
       return buffer;
    }

    sprintf(expTypeToStrBuffer, "%s%s%s",
            (isStatic ? "static " : ""),
            (isArray ? "array of " : ""),
            typeName);

    return strdup(expTypeToStrBuffer); // memory leak
}


// allocate a FIX BUFFER.  You must copy the string if you
// // are referencing the function twice in the same printf for example.

void printTreeNode(FILE *out, TreeNode *tree, bool showExpType, bool showAllocation) 
{
  
  //cout << "in printTreeNode\n";
  if (tree->nodekind == DeclK) {
   switch (tree->kind.decl) {
   case VarK:
            printf("Var: %s ", tree->attr.name);
            printf("of %s", expTypeToStr(tree->type, tree->isArray, tree->isStatic));
            if (showAllocation) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
       break;
   case FuncK:
            printf("Func: %s ", tree->attr.name);
            printf("returns %s", expTypeToStr(tree->type, tree->isArray, tree->isStatic));
            if (showAllocation) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
       break;
   case ParamK:
            printf("Parm: %s ", tree->attr.name);
            printf("of %s", expTypeToStr(tree->type, tree->isArray, tree->isStatic));
            if (showAllocation) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
       break;
   default:
       fprintf(out, "Unknown declaration node kind: %d",
          tree->kind.decl);
       break;
     }
    }
   else if (tree->nodekind == StmtK) {
   switch (tree->kind.stmt) {
   case IfK:
       fprintf(out, "If");
       break;
   case WhileK:
       fprintf(out, "While");
       break;
   case CompoundK:
       fprintf(out, "Compound");
            if (showAllocation) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
       break;
        case ForK:
       fprintf(out, "For");
            if (showAllocation) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
       break;
        case RangeK:
       fprintf(out, "Range");
       break;
   case ReturnK:
       fprintf(out, "Return");
       break;
   case BreakK:
       fprintf(out, "Break");
       break;
   default:
       fprintf(out, "Unknown  statement node kind: %d",
          tree->kind.stmt);
       break;
   }
    }
   else if (tree->nodekind == ExpK) {
   switch (tree->kind.exp) {
   case AssignK:
       //////////////////////////////
       //printf(" in printtreenode int %d char %c\n", tree->attr.op,tree->attr.op);
       fprintf(out, "Assign: %s", tokenToStr(tree->attr.op));
       break;
   case OpK:
       fprintf(out, "Op: %s", tokenToStr(tree->attr.op));
       break;
   case ConstantK:
            switch (tree->type) {
            case Boolean:
      fprintf(out, "Const %s", (tree->attr.value) ?  "true" : "false");
                break;
            case Integer:
      fprintf(out, "Const %d", tree->attr.value);
                break;
            case Char:
                if (tree->isArray) {
                    fprintf(out, "Const ");
                 //   printf("\"");
                    for (int i=0; i<tree->size-1; i++) {
                        printf("%c", tree->attr.string[i]);
                    }
                   // printf("\"");
                }
      else fprintf(out, "Const '%c'", tree->attr.cvalue);
                break;
            case Void:
            case UndefinedType:
                fprintf(out, "SYSTEM ERROR: parse tree contains invalid type for constant: %s\n", expTypeToStr(tree->type));
       }
       break;
   case IdK:
       fprintf(out, "Id: %s", tree->attr.name);
       break;
   case CallK:
       fprintf(out, "Call: %s", tree->attr.name);
       break;
   default:
       fprintf(out, "Unknown expression node kind: %d", tree->kind.exp);
       break;
   }
   if (showExpType) {
       fprintf(out, " of %s", expTypeToStr(tree->type, tree->isArray, tree->isStatic));
   }
        if (showAllocation) {
            if (tree->kind.exp == IdK || tree->kind.exp == ConstantK && tree->type == Char && tree->isArray) {
                printf(" [mem: %s loc: %d size: %d]", varKindToStr(tree->varKind), tree->offset, tree->size);
            }
        }
    }
    else fprintf(out, "Unknown class of node: %d",
       tree->nodekind);

    fprintf(out, " [line: %d]", tree->lineno); 
}  

void printSpaces(FILE *out,int depth)
{
   for(int i =0; i < depth; i++){
   fprintf(out, ".   ");
   }
}

void printFullTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation, int depth, int sibcount)
{
   //cout << "in printFullTree\n";
   int childcount; 
   if(syntaxTree != NULL)
   {
      printTreeNode(out, syntaxTree, showExpType ,showAllocation);
      fprintf(out, "\n");
  }
  for(childcount =0; childcount < 3; childcount++)
  {
     if(syntaxTree->child[childcount])
     {
       printSpaces(out, depth);
        fprintf(out, "Child: %d  ", childcount);
        printFullTree(out, syntaxTree->child[childcount], showExpType, showAllocation, depth+1, 1);    
     }
  }
  syntaxTree = syntaxTree->sibling; 
  if(syntaxTree != NULL)
  {
    if(depth)
    {
       printSpaces(out, depth - 1); 
       fprintf(out, "Sibling: %d  ", sibcount);
    }
    printFullTree(out, syntaxTree, showExpType, showAllocation, depth, sibcount+1);
   
  }
  fflush(out);   
}

void printTree(FILE *out, TreeNode *syntaxTree, bool showExpType, bool showAllocation)
{
   // cout << "in printTree\n";
    //printTreeNode(out, syntaxTree, showExpType ,showAllocation);
    //fprintf(out, "\n");
    printFullTree(out, syntaxTree, showExpType, showAllocation, 1, 1);
}
