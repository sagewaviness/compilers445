#include <iostream>
#include <string>
#include "semantics.h"
#include "symbolTable.h"
#include "parser.tab.h"

using namespace std;

// some globals
extern int numErrors;
extern int numWarnings;
extern bool printErrors;
extern bool printWarnings;

// // SPECIAL OPTIONS
static bool noDuplicateUndefs;
static bool shareCompoundSpace;

// // expression types
 static ExpectType expectType[LASTOP];
 static ReturnType returnType[LASTOP];

// // memory offsets are GLOBAL
static int goffset;                   // top of global space
static int foffset;                   // top of local space
// Helper function prototypes
bool insertErr(TreeNode *current);

//define the type in here
void treeTraverse(TreeNode *current, SymbolTable *symtab);

//traverse tree with different nodekinds 
void traverseDeclK(TreeNode *current, SymbolTable *symtab);
void traverseStmtK(TreeNode *current, SymbolTable *symtab);
void traverseExpK(TreeNode *current, SymbolTable *symtab);


/**
 * TreeNode*loadIOLib get treenode kinds and  assign them 
 * 
 * @param  {TreeNode*} syntree : syntax tree to pass
 */
TreeNode *loadIOLib(TreeNode *syntree)
{
   TreeNode *input, *output, *param_output; 
   TreeNode *inputb, *outputb, *param_outputb; 
   TreeNode *inputc, *outputc, *param_outputc; 
   TreeNode *outnl;
   
   input = newDeclNode(FuncK, Integer);
   input->lineno = -1; // all are -1
   input->attr.name = strdup("input"); //We named the variables well input->type = Integer;
   input->type = Integer;

   inputb = newDeclNode(FuncK, Boolean);
   inputb->attr.name = strdup("inputb"); //We named the variables well input->type = Integer;
   inputb->lineno = -1; // all are -1
   inputb->type = Boolean;


   inputc = newDeclNode(FuncK, Boolean);
   inputc->type = Char;
   inputc->attr.name = strdup("inputc"); //We named the variables well input->type = Integer;
   inputc->lineno = -1; // all are -1

   param_output = newDeclNode(ParamK, Void);
   param_output->attr.name = strdup("*dummy*"); 
   param_output->type = Integer;
   param_output->lineno = -1; // all are -1

   output = newDeclNode(FuncK, Void);
   output->child[0] = param_output;
   output->attr.name = strdup("output");
   output->type = Void;
   output->lineno = -1; // all are -1

   param_outputb = newDeclNode(ParamK, Void);
   param_outputb->attr.name = strdup("*dummy*");
   param_outputb->type = Boolean;
   param_outputb->lineno = -1; // all are -1

   outputb = newDeclNode(FuncK, Void);
   outputb->child[0] = param_outputb;
   outputb->attr.name = strdup("outputb");
   outputb->lineno = -1; // all are -1
   outputb->type = Void;

   param_outputc = newDeclNode(ParamK, Void);
   param_outputc->attr.name = strdup("*dummy*"); 
   param_outputc->type = Char;
   param_outputc->lineno = -1; // all are -1

   outputc = newDeclNode(FuncK, Void);
   outputc->child[0] = param_outputc;
   outputc->attr.name = strdup("outputc");
   outputc->lineno = -1; // all are -1
   outputc->type = Void;
 
   outnl = newDeclNode(FuncK, Void);
   outnl->child[0] = NULL;
   outnl->attr.name = strdup("outnl");
   outnl->lineno = -1; // all are -1
   outnl->type = Void;
  
   input->sibling = output;
   output->sibling = inputb;
   inputb->sibling = outputb;
   outputb->sibling = inputc;
   inputc->sibling = outputc;
   outputc->sibling = outnl;
   outnl->sibling = syntree; // add in the tree we were given return input;

   return input;
}


/**
 * 
 * @param  {TreeNode*} current   : current tree node 
 * @param  {SymbolTable*} symtab : symbol table 
 *
 */
//done til assignment 5 no touchy 
void traverseDeclK(TreeNode *current, SymbolTable *symtab)
{
 char *id = strdup(current->attr.name);
 static int varCounter = 0;
   switch(current->kind.decl) 
   {
   	case FuncK: 
	    //foffset =-2;
	    if (!symtab->insertGlobal(id, (void*)current) && current->lineno != -1) {
               //printf("SEMANTIC ERROR(%d): Symbol '%s' is already declared at line UNKNOWN.\n", current->lineno, id);
             // exit(1);
             }
	     current->varKind = Global;
	     current->size = foffset; 
	   break;
	case VarK:
	//no break here
	case ParamK:
 	    if (!symtab->insert(id, (void*)current) && current->lineno != -1) 
      	    {
               //printf("SEMANTIC ERROR(%d): Symbol '%s' is already declared at line UNKNOWN.\n", current->lineno, id);
            //           // exit(1);
            }
            if (symtab->depth() == 1)
            {
               current->varKind = Global;
               current->offset = goffset;
               goffset -= current->size;
            }
            else if(current->isStatic)
            {
               current->varKind = LocalStatic;
               current->offset = goffset;
               goffset -= current->size;
               {//meant to have new scope dont delete {}   
                  char *newName;
                  newName = new char[strlen(id)+10];
                  sprintf(newName, "%s-%d" , id , ++varCounter);
  	          symtab->insertGlobal(newName, current);

                  delete [] newName;
               }
		      }
		else
		{
		   current->varKind = Local;
		   current->offset = foffset;
		   foffset -= current->size;
		}               
		
	   if(current->kind.decl== ParamK)
		{
		  current->varKind = Parameter;
		}
		else if(current->isArray)
		{
		  current->offset--;
		}

	   break;
   }

}

/**
 * traverseStmtK travers the tree ifor statement kind and assigning size 
 *       and and types
 * 
 * @param  {TreeNode*} current   :  for current node get it set up correctly 
 * @param  {SymbolTable*} symtab : add to symbol table
 */

void traverseStmtK(TreeNode *current, SymbolTable *symtab)
{
   switch (current->kind.stmt) 
    {
        case IfK:
	    if(current->child[0]->type != Boolean)
	    {
	       printf("SEMANTIC ERROR(%d): Expecting Boolean test condition in if statement but got %s.\n", 
		       current->lineno, expTypeToStr(current->child[0]->type));
	       numErrors++;
	    }
            break;
        case WhileK:
            break;
        case CompoundK:
             current->size = foffset; 
            break;
        case ForK:
           break;
        case RangeK:
            break;
        case ReturnK:
	
	     if (current != NULL && current->child[0] != NULL && current->child[0]->isArray)
	     {
	       printf("SEMANTIC ERROR(%d): Cannot return an array.\n", current->lineno);
	       numErrors++;
	     }
            break;
        case BreakK:
            break;
        default:
            printf( "Unknown  statement node kind: %d",
                current->kind.stmt);
            break;
    }
   return;
}

/**
 * traverseExpK set current node type/size 
 * @param  {TreeNode*} current   :  current node 
 * @param  {SymbolTable*} symtab : symbol table type
 */
void traverseExpK(TreeNode *current, SymbolTable *symtab)
{ 
   switch (current->kind.exp) 	
   {
      case AssignK:
	  if(current->child[0] && current->child[1] && current->child[1]->type != UndefinedType)
          {
	      if (current->child[0]->type != current->child[1]->type)
	    {
		//SEMANTIC ERROR(12): '=' requires operands of the same type but lhs is type int and rhs is type char.
	       printf("SEMANTIC ERROR(%d): '=' requires operands of the same type but lhs is %s and rhs is %s.\n",
			 current->lineno, expTypeToStr(current->child[0]->type), expTypeToStr(current->child[1]->type));
 	       numErrors++;
	    }
	  }
      case OpK: 
         switch (returnType[current->attr.op]) 
         {
            treeTraverse(current->child[0], symtab);
            treeTraverse(current->child[1], symtab);
            case RetInt:
               current->type = Integer;
               break;
            case RetBool:
               current->type = Boolean;
               break;
            case RetLHS:
               current->type = current->child[0]->type;
               if (current->attr.op == int('='))
               {	
                  current->isArray = current->child[0]->isArray;
               }
               break;
            }
            break;
      case ConstantK:
         current->isConst = true;

               switch (current->type) 
               {
                  case Boolean:
                     current->type = Boolean;
                     break;
                  case Integer:
                     current->type = Integer;
                     break;
                  case Char:
                     if(current->isArray)
                     {
                        current->varKind = Global;
                        current->offset = goffset - 1;
                        goffset -= current->size;
                     }
                     break;
                  case Void:
                  case UndefinedType:
                     break;
               }               
               break;
      case IdK:
      case CallK:
         { 
            char *id = strdup(current->attr.name);
            TreeNode *temp = (TreeNode*)symtab->lookup(id);
                        
            if(temp == NULL)
            {
		printf("SEMANTIC ERROR(%d): Symbol '%s' is not declared.\n", current->lineno, id); 
		numErrors++;
		break;	
            }

            current->type = temp->type;
            current->isArray = temp->isArray;
            current->isStatic = temp->isStatic;
            current->size = temp->size;
            current->varKind = temp->varKind;
            current->offset = temp->offset;
         }
         break;
      default:
         break;
   }
   return;
}

/**
 * treeTraverse()  traberse the tree and call needed functions for 
 *          certain kinds 
 * @param  {TreeNode*} current   : 
 * @param  {SymbolTable*} symtab : 
 */
void treeTraverse(TreeNode *current, SymbolTable *symtab)
{
   bool isCompound = false;
   if(current == NULL){ return;}
   
   if(current->nodekind == StmtK &&
          (current->kind.stmt == CompoundK || current->kind.stmt == ForK)) 
   {
      isCompound = true;
   }
 
   if(current->nodekind == DeclK  && current->kind.decl == FuncK)
   {  
      foffset = -2;
      isCompound = true;
   }
 
   if(isCompound)
   {
      char* id = strdup(current->attr.name);
      //printf("NewScope from %s\n",id);
      symtab->enter("NewScope from " + (std::string)id);
   }
   
   int tempOff = foffset;
   //must traverse to first child       
   treeTraverse(current->child[0], symtab);
               
 
   switch(current->nodekind)
   {
      case DeclK:
         traverseDeclK(current, symtab);
	      break;
      case StmtK:
         traverseStmtK(current, symtab);
         break;
      case ExpK:
         traverseExpK(current, symtab);
         break;
      default: 
	//printErrorSystem("Unknown nodekind!");
         printf("unknown nodekind\n");
         break;
   }
   
   if(current->nodekind == StmtK && current->kind.stmt == ForK)
   {
      foffset -= 2;
   }	
	//now can travel to child 1 and 2 
   treeTraverse(current->child[1], symtab);
   treeTraverse(current->child[2], symtab);

   if(current->nodekind == StmtK && current->kind.stmt == CompoundK)
   {
      current->size =foffset;
      foffset = tempOff;
   }
  
   if (current->nodekind == StmtK && current->kind.stmt == ForK)
   {
      current->size = foffset;
   }	

   if(isCompound)
   {
     symtab->leave();
   }   

   treeTraverse(current->sibling, symtab);

   if(current->nodekind ==StmtK && current->kind.stmt ==ForK)
   {
     foffset = tempOff;
   }
   return;   
}

static bool newScope = true;
static int loopCount = 0;
static int varCounter = 0;
static bool isAssignedErrOk = true;
static bool isUsedErrOk = true;

/**
 * TreeNode*semanticAnalysis set left hand side of tree (last operator)
 * 
 * @param  {TreeNode*} syntree         : the syntax tree we are searchin g
 * @param  {bool} shareCompoundSpaceIn : is it in shared space
 * @param  {bool} noDuplicateUndefsIn  : is it duplicated 
 * @param  {SymbolTable*} symtabX      : symtab referencing 
 * @param  {int} globalOffset          : global opps 
 */
TreeNode *semanticAnalysis(TreeNode *syntree,bool shareCompoundSpaceIn, bool noDuplicateUndefsIn, SymbolTable *symtabX, int &globalOffset)
{
   noDuplicateUndefs = noDuplicateUndefsIn;
   shareCompoundSpace = shareCompoundSpaceIn;
   
   
   newScope = true;
   loopCount = 0;
   varCounter = 0;
   isAssignedErrOk = true;
   isUsedErrOk = true;
   goffset = 0;

  //OPERAND TYPES
   //Binary Ops
   for (int i = 0; i < LASTOP; i++) expectType[i] = IntInt; // everything is IntInt
   //except the following
   expectType[AND] = BoolBool;
   expectType[OR] = BoolBool;
   expectType[EQ] = Equal;
   expectType[NEQ] = Equal;
   expectType[LEQ] = Equal;
   expectType[int('<')] = Equal;
   expectType[GEQ] = Equal;
   expectType[int('>')] = Equal;
   expectType[int('=')] = Equal;
   expectType[int('[')] = ArrayInt;

   //unary ops
   expectType[NOT] = OneBool;
   expectType[int('?')] = OneInt;
   expectType[SIZEOF] = OneArray;
   expectType[CHSIGN] = OneInt;
   expectType[DEC] = OneInt;
   expectType[INC] = OneInt;
   //OP vals
   
   //binary ops
   for (int i=0; i<LASTOP; i++) returnType[i] = RetInt;
   returnType[AND] = RetBool;
   returnType[OR] = RetBool;
   returnType[EQ] = RetBool;
   returnType[NEQ] = RetBool;
   returnType[LEQ] = RetBool;
   returnType[int('<')] = RetBool;
   returnType[GEQ] = RetBool;
   returnType[int('>')] = RetBool;
   returnType[int('=')] = RetLHS;
   returnType[int('[')] = RetLHS;
   
   //unary ops
   returnType[NOT] = RetBool;

   //anything else to add
   syntree = loadIOLib(syntree);

   //traverse the syntax tree
   treeTraverse(syntree, symtabX);

   // remember where the globals are
   globalOffset = goffset;

  return syntree;
}
