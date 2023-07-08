#include <iostream>
#include "codegen.h"
#include "emitcode.h"

extern int numErrors;
extern int numWarnings;
extern void yyparse();
extern int yydebug();
extern TreeNode *syntaxTree;
extern char **largerTokens;
extern void initTokenStrings();

FILE *code;
static bool linenumFlag;
static int breakloc;
static SymbolTable *globals;

void codegenHeader(char *srcFile);
void codegenGeneral(TreeNode *currnode);
void codegenInit(int initjump, int globalOffset);
//codegenStatement(TreeNode *currnode);

void codegen(FILE *codeIn, char *srcFile, TreeNode *syntaxTree, SymbolTable *globalsIn, int globalOffset, bool linenumFlagIn)
{
   int initJump;
   code = codeIn;
   globals = globalsIn; 
   linenumFlag = linenumFlagIn; 
   breakloc = 0;
   initJump = emitSkip(1); 
   codegenHeader(srcFile); 
   codegenGeneral(syntaxTree); 
   codegenInit(initJump, globalOffset);
}

void codegenInit(int initjump, int globalOffset)
{

}

void codegenHeader(char *srcFile) 
{
  emitComment((char *)"bC compiler version bC-Su23");
  emitComment((char *)"File compiled: ",(char *) srcFile); 
}

void codegenGeneral(TreeNode *currnode)
{ 
 /*  while (currnode) 
   {
     switch (currnode->nodekind) 
     {
        case StmtK: codegenStatement(currnode); break;
        case ExpK:
           emitComment((char *)"EXPRESSION"); 
	   codegenExpression(currnode);
           break;
        case DeclK: codegenDecl(currnode); break;
     }
     currnode = currnode->sibling;
   }*/ 
}

