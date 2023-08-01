#include <iostream>
#include "codegen.h"
#include "emitcode.h"
#include "scanType.h"
#include "parser.tab.h"

using namespace std;

extern int numErrors;
extern int numWarnings;
//extern void yyparse();
//extern int yydebug();
extern TreeNode *syntaxTree;
extern char **largerTokens;
extern void initTokenStrings();

FILE *code;
static bool linenumFlag = false;
static int breakloc;
static SymbolTable *globals;

void codegenHeader(char *srcFile);
void codegenGeneral(TreeNode *currnode);
void codegenInit(int initjump, int globalOffset);
void codegenStatement(TreeNode *currnode);
void codegenExpression(TreeNode *currnode);
void codegenDecl(TreeNode *currnode);
void initGlobalArraySizes();
void commentLineNum(TreeNode *currnode);
void initAGlobalSymbol(std::string sym, void *ptr);
#define RETURNOFFSET -1
#define OFPOFF 0

int toffset = 0;


void codegen(FILE *codeIn, char *srcFile, TreeNode *syntaxTree, SymbolTable *globalsIn, int globalOffset, bool linenumFlagIn)
{
   int initJump;

   code = codeIn;
   globals = globalsIn; 
   linenumFlag = linenumFlagIn; 
   breakloc = 0;

   initJump = emitSkip(1); // save place for the jump 
   codegenHeader(srcFile); //header comment 
   codegenGeneral(syntaxTree);  //general code generation including I/O library
   codegenInit(initJump, globalOffset); //initialization for run 
}


void commentLineNum(TreeNode *currnode)
{
    char buf[16];

    if (linenumFlag) {
        sprintf(buf, "%d", currnode->lineno);
        emitComment((char *)"Line: ", buf);
    }
}

// Generate init code ...
void codegenInit(int initJump, int globalOffset)
{ 
    backPatchAJumpToHere(initJump, (char *)"Jump to init [backpatch]");
    emitComment((char *)"INIT");
    //OLD pre 4.6 TM emitRM((char *)"LD", GP, 0, 0, (char *)"Set the global pointer");
    emitRM((char *)"LDA", FP, globalOffset, GP, (char *)"set first frame at end of globals");
    emitRM((char *)"ST", FP, 0, FP, (char *)"store old fp (point to self)");
    initGlobalArraySizes();
    emitRM((char *)"LDA", AC, 1, PC, (char *)"Return address in ac");
    { // jump to main
        TreeNode *funcNode;
        funcNode = (TreeNode *)(globals->lookup((char *)"main"));
        if (funcNode) {
        emitGotoAbs(funcNode->offset, (char *)"Jump to main");
    }
    else {
    printf((char *)"ERROR(LINKER): Procedure main is not defined.\n");
    numErrors++;
    }
    }
    emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
    emitComment((char *)"END INIT");
}

void codegenHeader(char *srcFile) 
{
  emitComment((char *)"bC compiler version bC-Su23");
  emitComment((char *)"File compiled: ",(char *) srcFile); 
}

void codegenGeneral(TreeNode *currnode)
{

   while (currnode) 
   {
     switch (currnode->nodekind) 
     {
        case StmtK: 
	   codegenStatement(currnode); 
	   break;
        case ExpK:
           emitComment((char *)"EXPRESSION"); 
	   codegenExpression(currnode);
           break;
        case DeclK: 
	   codegenDecl(currnode); 
	   break;
     }

     currnode = currnode->sibling;
   }
}

void codegenLibraryFun(TreeNode *currnode)
{ 
    emitComment((char *)"");
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    emitComment((char *)"FUNCTION", currnode->attr.name);
    // remember where this function is
    currnode->offset = emitSkip(0);
    // Store retura address
    emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");
    // Next slides here

    if (strcmp(currnode->attr.name, (char *)"input")==0) {
        emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
        else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
        else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
    else if (strcmp(currnode->attr.name, (char *)"input")==0) {
        emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
        else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
        else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
        else if (strcmp(currnode->attr.name, (char *)"output")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
    } else if (strcmp(currnode->attr.name, (char *)"outputb")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
    }else if (strcmp(currnode->attr.name, (char *)"outputc")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
    }
    else if (strcmp(currnode->attr.name, (char *)"input")==0) {
    emitRO((char *)"IN", RT, RT, RT, (char *)"Grab int input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputb")==0) {
        emitRO((char *)"INB", RT, RT, RT, (char *)"Grab bool input");
    }
    else if (strcmp(currnode->attr.name, (char *)"inputc")==0) {
        emitRO((char *)"INC", RT, RT, RT, (char *)"Grab char input");
    }
    else if (strcmp(currnode->attr.name, (char *)"output")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUT", AC, AC, AC, (char *)"Output integer");
    }
    else if (strcmp(currnode->attr.name, (char *)"outputb")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTB", AC, AC, AC, (char *)"Output bool");
    }else if (strcmp(currnode->attr.name, (char *)"outputc")==0) {
        emitRM((char *)"LD", AC, -2, FP, (char *)"Load parameter");
        emitRO((char *)"OUTC", AC, AC, AC, (char *)"Output char");
    }
    else if (strcmp(currnode->attr.name, (char *)"outnl")==0) {
        emitRO((char *)"OUTNL", AC, AC, AC, (char *)"Output a newline");
    }
    else {
        emitComment((char *)"ERROR(LINKER): No support for special function");
        emitComment(currnode->attr.name);
    }


    emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
    emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
    emitGoto(0, AC, (char *)"Return");
    emitComment((char *)"END FUNCTION", currnode->attr.name);
}

void codegenFun(TreeNode *currnode)
{ 
    emitComment((char *)"");
    emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
    emitComment((char *)"FUNCTION", currnode->attr.name);
    toffset = currnode->size; // recover the end of activation record
    emitComment((char *)"TOFF set:", toffset);
    currnode->offset = emitSkip(0); // offset holds the instruction address!!
    // Store return address
    emitRM((char *)"ST", AC, RETURNOFFSET, FP, (char *)"Store return address");
    // Generate code for the statements...
    codegenGeneral(currnode->child[1]);
    // In case there was no return statement
    // set return register to 0 and return
    emitComment((char *)"Add standard closing in case there is no return statement");
    emitRM((char *)"LDC", RT, 0, 6, (char *)"Set return value to 0");
    emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
    emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
    emitGoto(0, AC, (char *)"Return");
    emitComment((char *)"END FUNCTION", currnode->attr.name);
}


int offsetRegister(VarKind v) {
    switch (v) {
    case Local:       return FP;
    case Parameter:   return FP;
    case Global:      return GP;
    case LocalStatic: return GP;
    default:
        printf((char *)"ERROR(codegen): looking up offset register for a variable of type %d\n", v);
        return 666;
    }
}


// given the syntax tree for declarations generate the code
void codegenDecl(TreeNode *currnode) 
{ 
   commentLineNum(currnode);
   switch(currnode->kind.decl) 
   {
      case VarK:
//
//
	if (currnode->isArray) {
          switch (currnode->varKind) {
            case Local:
                emitRM((char *)"LDC", AC, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
                emitRM((char *)"ST", AC, currnode->offset+1, offsetRegister(currnode->varKind), (char *)"save size of array", currnode->attr.name);
                break;
            case LocalStatic:
            case Parameter:
            case Global:
	     break;
            case None:
		printf("ERROR(SYSTEM): lhs->varKind is None for variable declaration\n");
            }

	    if (currnode->child[0]) {
                codegenExpression(currnode->child[0]);
                emitRM((char *)"LDA", AC1, currnode->offset, offsetRegister(currnode->varKind), (char *)"address of lhs");
                emitRM((char *)"LD", AC2, 1, AC, (char *)"size of rhs");
                emitRM((char *)"LD", AC3, 1, AC1, (char *)"size of lhs");
                emitRO((char *)"SWP", AC2, AC3, 6, (char *)"pick smallest size");
                emitRO((char *)"MOV", AC1, AC, AC2, (char *)"array op =");
            }
        }
	else {
	   if (currnode->child[0]) {
                switch (currnode->varKind) {
                case Local:
		    codegenExpression(currnode->child[0]);
		    emitRM((char *)"ST", AC, currnode->offset, FP,
                           (char *)"Store variable", currnode->attr.name);
                case LocalStatic:
                case Parameter:
                case Global:
		    break;
                case None:
                    printf("ERROR(SYSTEM): lhs->varKind is None for variable declaration\n");
                }
            }
        }
        break;
/*
	if(currnode->isArray){
	  emitRM((char *)"LDC", AC, currnode->size -1, 6,
                 (char *)"load size of array", currnode->attr.name);
          emitRM((char *)"ST", AC, -2 , 1, (char *)"save size of array", 
                currnode->attr.name);
  	  if(currnode->child[0]){
	    codegenExpression(currnode->child[0]);
	  }
	   
printf("end of is array vark\n");
	}
*/
//
//
         // You have a LOT to do here!!!!!
         break;
      case FuncK:
         if (currnode->lineno == -1) { // These are the library functions we just added
            codegenLibraryFun(currnode);
         }
         else {
            codegenFun(currnode);
         }
         break;
      case ParamK:
         // IMPORTANT: no instructions need to be allocated for parameters here
         break;
   }
}

void codegenStatement(TreeNode *currnode) 
{
// local state to remember stuff
int skiploc=0, skiploc2=0, currloc=0;  // some temporary instuction addresses
TreeNode *loopindex=NULL;              // a pointer to the index variable declaration node

commentLineNum(currnode);

switch (currnode->kind.stmt) {
    case CompoundK:
    {
       int savedToffset;

       savedToffset = toffset;            // zzz huh?
       toffset = currnode->size;               // recover the end of activation record
       emitComment((char *)"COMPOUND");
       emitComment((char *)"TOFF set:", toffset);
       
       codegenGeneral(currnode->child[0]);     // process inits
       emitComment((char *)"Compound Body");
       codegenGeneral(currnode->child[1]);     // process body
       toffset = savedToffset;          // zzz huh?
       emitComment((char *)"TOFF set:", toffset);
       emitComment((char *)"END COMPOUND");
    }
    break;

    case WhileK:
       emitComment((char *)"WHILE");
       currloc = emitSkip(0); // return to here to do the test
       codegenExpression(currnode->child[0]); // test expression
       emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to while part");
       emitComment((char *)"DO");
       skiploc = breakloc; // save the old break statement return point
       breakloc = emitSkip(1); // addr of instr that jumps to end of loop
       //codegenStatement(currnode->child[0]);
       codegenGeneral(currnode->child[1]); // do body of loop
       emitGotoAbs(currloc, (char *)"go to beginning of loop");
       backPatchAJumpToHere(breakloc, (char *)"Jump past loop [backpatch]");
       // backpatch jump to end of loop
       breakloc = skiploc; // restore for break statement
       emitComment((char *)"END WHILE");
       break;
    case IfK:
	
	 emitComment((char *)"IF");	
	
	codegenExpression(currnode->child[0]);
	skiploc = emitSkip(1); 

	emitComment((char *)"THEN");
	codegenGeneral(currnode->child[1]);

	if(currnode->child[2])
        {
	  skiploc2 = emitSkip(1);
	}

	backPatchAJumpToHere((char *)"JZR", AC, skiploc, (char *)"Jump around the THEN if false [backpatch]");
 	
	if(currnode->child[2])
	{
	   emitComment((char *)"ELSE");
	   codegenGeneral(currnode->child[2]);
	   backPatchAJumpToHere(skiploc2, (char *)"Jump around the ELSE [backpatch]");
	}
//add JZR  3,0(7)	Jump around the THEN if false [backpa
	emitComment((char *)"END IF");
	break;
    case ForK:
	int savedToffset;int startoff, stopoff, stepoff;
	savedToffset = toffset;
	toffset = currnode->size;
	loopindex = currnode->child[0];
	startoff = loopindex->offset;
	stopoff = startoff-1;
	stepoff = startoff-2;

	TreeNode *rangenode;rangenode = currnode->child[1];
	emitComment((char *)"TOFF set:", toffset);
        emitComment((char *)"FOR");
	codegenExpression(rangenode->child[0]);	
        emitRM((char *)"ST", AC, savedToffset, 1, (char *)"save starting value in index variable");
	codegenExpression(rangenode->child[1]);
	emitRM((char *)"ST", AC, stopoff, 1, (char *)"save stop value"); 

	if (rangenode->child[2]!=NULL){
		codegenExpression(rangenode->child[2]);
	}
	else{
	    emitRM((char *)"LDC", AC, 1, 6, (char *)"default increment by 1");
	}
	//currloc = emitSkip(0);

	emitRM((char *)"ST", AC, stepoff, FP, (char *)"save step value");

	currloc = emitSkip(0);

	emitRM((char *)"LD", AC1, startoff, FP, (char *)"loop index");
	emitRM((char *)"LD", AC2, stopoff, FP, (char *)"stop value");
	emitRM((char *)"LD", AC, stepoff, FP, (char *)"step value");
	emitRO((char *)"SLT", AC, AC1, AC2, (char *)"Op <");
	emitRM((char *)"JNZ", AC, 1, PC, (char *)"Jump to loop body"); 

	skiploc = breakloc; 
	breakloc = emitSkip(1); 
	
	codegenGeneral(currnode->child[2]);

        emitComment((char *)"Bottom of loop increment and jump");
	emitRM((char *)"LD", AC, startoff, FP, (char *)"Load index");
        emitRM((char *)"LD", AC2, stepoff, FP, (char *)"Load step");
        emitRO((char *)"ADD", AC, AC, AC2, (char *)"increment");
	emitRM((char *)"ST", AC, startoff, FP, (char *)"store back to index");
	emitGotoAbs(currloc, (char *)"go to beginning of loop");
        backPatchAJumpToHere(breakloc, (char *)"Jump past loop [backpatch]");

        breakloc = skiploc;

	emitComment((char *)"END LOOP");
	break; 
    case ReturnK:
	emitComment((char *)"RETURN");
        if(currnode->child[0])
	{
	   codegenExpression(currnode->child[0]);
	   emitRM((char *)"LDA", RT, 0, AC, (char *)"Copy result to return register");
	}
	emitRM((char *)"LD", AC, RETURNOFFSET, FP, (char *)"Load return address");
        emitRM((char *)"LD", FP, OFPOFF, FP, (char *)"Adjust fp");
        emitGoto(0, AC, (char *)"Return");
// LDA copy result to return register
	break; 
    case BreakK:
	emitComment((char *)"BREAK");
        emitGotoAbs(breakloc, (char *)"break");
	break;
     case RangeK:
	break;
  }
}

}


void codegenExpression(TreeNode *currnode) {
    int off;
    int callLoc;
    TreeNode *param;
    commentLineNum(currnode);
    switch(currnode->kind.exp) {
      case CallK:
	emitComment((char *)"CALL", currnode->attr.name);
	off = toffset;	
	emitRM((char *)"ST", FP, toffset, 1, (char *)"Store fp in ghost frame for", currnode->attr.name);
	toffset--;
	emitComment((char *)"TOFF dec:", toffset);			
	toffset--;
	emitComment((char *)"TOFF dec:", toffset);	
	TreeNode *Node;
	Node = (TreeNode *)(globals->lookup(currnode->attr.name));
	callLoc  = Node->offset;
	//int tempoff = toffset; 
	param = currnode->child[0];
	int i;
        char buf[16];
        i = 1;  

	while(param)
	{
	   sprintf(buf, "%d" , i);
	   emitComment((char *)"Param", buf);	
	   codegenExpression(param);
	   emitRM((char *)"ST", AC, toffset, 1, (char *)"Push parameter");
	   toffset--; emitComment((char *)"TOFF dec:", toffset); //deal with parameters
	   i++;
	   param = param->sibling;
	  
	}
	
	emitComment((char *)"Param end", currnode->attr.name);
	toffset = off;
        emitRM((char *)"LDA", FP, toffset, 1, (char *)"Ghost frame becomes new active frame");

////currnode->attr.value or currnode->attr.value-1 unsure
	emitRM((char *)"LDA", AC, currnode->attr.value+1, 7, (char *)"Return address in ac");
/////
//
//
//
	emitRMAbs((char *)"JMP", PC, callLoc, (char *)"CALL", currnode->attr.name);
	//emitGotoAbs(callLoc, (char *)"CALL", currnode->attr.name);
	//emitRM((char *)"JMP", 7, -5, 7, (char *)"CALL main");
	emitRM((char *)"LDA", AC, currnode->attr.value, 2, (char *)"Save the result in ac");
	      /*>	 42:    LDA  3,1(7)	Return address in ac 
		  >	 43:    JMP  7,-5(7)	CALL main
	      >	 44:    LDA  3,0(2)	Save the result in ac 
		     >	* Call end main
	      >	* TOFF set: -2 */
	emitComment((char *)"Call end", currnode->attr.name);
	emitComment((char *)"TOFF set:", toffset);
	break;
      case ConstantK: 
           switch(currnode->type){
		case Void:
		   break;
		case Integer:
		    emitRM((char *)"LDC", AC, currnode->attr.value, 6, (char *)"Load integer constant");
		   break; 
		case  Boolean:
		    emitRM((char *)"LDC", AC, currnode->attr.value, 6, (char *)"Load Boolean constant");
		   break; 
		case  Char:
		 if (currnode->isArray) {
                    emitStrLit(currnode->offset, currnode->attr.string);  // at this point offset<=0
                    emitRM((char *)"LDA", AC, currnode->offset, 0, (char *)"Load address of char array");
	         }
                 else {
                    emitRM((char *)"LDC", AC, int(currnode->attr.cvalue), 6, (char *)"Load char constant");
                 }
		   break;
		case  UndefinedType:
	           break; 
		default:
		   printf("ERROR(SYSTEM): unknown constant type %d\n", currnode->type); 
		   break;
           }
	break;
      case IdK:
	off = offsetRegister(currnode->varKind);
	if(!currnode->isArray){
	 emitRM((char *)"LD", AC, currnode->offset, off, (char *)"Load variable", currnode->attr.name); 
	}
	else{
	   if(currnode->varKind != Parameter)
	   {
              emitRM((char *)"LDA", AC, currnode->offset, off, (char *)"Load address of base of array", currnode->attr.name);
	   }
	   else{
	      emitRM((char *)"LD", AC, currnode->offset, off, (char *)"Load address of base of array", currnode->attr.name);
	   }
	}
        break;
      case OpK:
	codegenExpression(currnode->child[0]);
       if(currnode->child[1]) {
	  emitRM((char *)"ST", AC, toffset, FP, (char *)"Push left side"); 
	   toffset--;
            
	   emitComment((char *)"TOFF dec:", toffset); 
	   codegenExpression(currnode->child[1]);
	   toffset++; 
	   emitComment((char *)"TOFF inc:", toffset); 	
 	   emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop left into ac1");
	 }
	  switch(currnode->attr.op){
	     case '[':
	       emitRO((char *)"SUB", AC, AC1, AC, (char *)"compute location from index");
               emitRM((char *)"LD", AC, 0, AC,(char *)"Load array element");
	       break;
	     case '+':
	       emitRO((char *)"ADD", AC, AC1, AC, (char *)"Op +");
	       break;
	     case AND:
		emitRO((char *)"AND", AC, AC1, AC, (char *)"Op AND"); 
	       break;
	     case OR:
                emitRO((char *)"OR", AC, AC1, AC, (char *)"Op OR");
               break;
	     case LEQ:
                emitRO((char *)"TLE", AC, AC1, AC, (char *)"Op <=");
               break;
	     case '<':
                emitRO((char *)"TLT", AC, AC1, AC, (char *)"Op <");
               break;
	     case '>':
                emitRO((char *)"TGT", AC, AC1, AC, (char *)"Op >");
               break;
	     case GEQ:
                emitRO((char *)"TGE", AC, AC1, AC, (char *)"Op >=");
               break;
	     case EQ:
                emitRO((char *)"TEQ", AC, AC1, AC, (char *)"Op ==");
               break;
	     case NEQ:
                emitRO((char *)"TNE", AC, AC1, AC, (char *)"Op !=");
               break;
	     case '-':
                emitRO((char *)"SUB", AC, AC1, AC, (char *)"Op -");
               break;
	     case '*':
                emitRO((char *)"MUL", AC, AC1, AC, (char *)"Op *");
               break;
	     case '/':
                emitRO((char *)"DIV", AC, AC1, AC, (char *)"Op /");
               break;
	     case '%':
                emitRO((char *)"MOD", AC, AC1, AC, (char *)"Op %");
               break;
	     case MAX:
                emitRO((char *)"SWP", AC1, AC, AC, (char *)"Op :>:");
               break;
	     case MIN:
                emitRO((char *)"SWP", AC, AC1, AC, (char *)"Op :<:");
               break;
	     case '?':
                emitRO((char *)"RND", AC, AC, 6, (char *)"Op ?");
               break;
	     case NOT:
	        emitRM((char *)"LDC", AC1, 1, 6, (char *)"Load 1");	
                emitRO((char *)"XOR", AC, AC, AC1, (char *)"Op XOR to get logical not");
               break;
	     case SIZEOF:

	           emitRM((char *)"LD", AC, 1, AC, (char *)"Load array size");
               break;
	     case CHSIGN:
		emitRO((char *)"NEG", AC, AC, AC, (char *)"Op unary -");
	       break;
             default: 
	        printf("Error in opk");
	 
 	}
	break;
    case AssignK:
            TreeNode *rhs, *lhs;
            lhs = currnode->child[0];
            rhs = currnode->child[1];
            // handle indexing of arrays
            if (lhs->attr.op == '[') {  // fist if is array kinds
                TreeNode *var, *index;
                var = lhs->child[0];
                index = lhs->child[1];
                codegenExpression(index);               // index -> AC
                if (rhs) {                        // have rhs?  ++ does not have rhs
                    emitRM((char *)"ST", AC, toffset, FP, (char *)"Push index");
                    toffset--;  emitComment((char *)"TOFF dec:", toffset);
                    codegenExpression(rhs);     // rhs -> AC;
                    toffset++;  emitComment((char *)"TOFF inc:", toffset);
                    emitRM((char *)"LD", AC1, toffset, FP, (char *)"Pop index");  // index -> AC1
                }
                switch (var->varKind) { // test caes for all these
                    case Parameter:
                        emitRM((char *)"LD", AC2, var->offset, FP, (char *)"Load address of base of array", var->attr.name);
                        break;
                    case Local:
                        emitRM((char *)"LDA", AC2, var->offset, FP, (char *)"Load address of base of array", var->attr.name);
                        break;
                    case LocalStatic:
                    case Global:
                        emitRM((char *)"LDA", AC2, var->offset, GP, (char *)"Load address of base of array", var->attr.name);
		        break;
                    case None:
                        printf("ERROR(SYSTEM): var->varKind is None for indexed array\n");
                }
                // if doing ++ then don't use temp storage and AC1

                if (rhs) {                        // have rhs?  ++ does not have rhs
                    emitRO((char *)"SUB", AC2, AC2, AC1, (char *)"Compute offset of value");
                }
                else {
                    emitRO((char *)"SUB", AC2, AC2, AC, (char *)"Compute offset of value");
                }
                switch (currnode->attr.op) {                                // test cases for all these
                    case '=':                                               // this one is done
                        emitRM((char *)"ST", AC, 0, AC2,
                            (char *)"Store variable", var->attr.name);
                        break;
                    case ADDASS:
                        emitRM((char *)"LD", AC1, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRO((char *)"ADD", AC, AC1, AC, (char *)"op +=");

                        emitRM((char *)"ST", AC, 0 , AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                    case SUBASS:

                        emitRM((char *)"LD", AC1, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRO((char *)"SUB", AC, AC1, AC, (char *)"op -=");

                        emitRM((char *)"ST", AC, 0, AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                    case MULASS:

                        emitRM((char *)"LD", AC1, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRO((char *)"MUL", AC, AC1, AC, (char *)"op *=");

                        emitRM((char *)"ST", AC, 0, AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                    case DIVASS:

                        emitRM((char *)"LD", AC1, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRO((char *)"DIV", AC, AC1, AC, (char *)"op /=");

                        emitRM((char *)"ST", AC, 0, AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                    case INC:

                        emitRM((char *)"LD", AC, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRM((char *)"LDA", AC, 1, AC,

                            (char *)"increment value of", var->attr.name);

                        emitRM((char *)"ST", AC, 0 , AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                    case DEC:

                        emitRM((char *)"LD", AC, 0, AC2,

                            (char *)"load lhs variable", var->attr.name);

                        emitRM((char *)"LDA", AC, -1, AC,

                            (char *)"decrement value of", var->attr.name);

                        emitRM((char *)"ST", AC, 0 , AC2,

                            (char *)"Store variable", var->attr.name);

                        break;

                }

            }  // end of indexed array assignment

    

            // lhs a simple variable assignment

            else {

                int offReg;


                offReg = offsetRegister(lhs->varKind);
	        if (rhs) codegenExpression(rhs);
                // compute rhs -> AC;   Note that ++ does not have rhs
                // save it

                switch (currnode->attr.op) {

                case '=':
                    if (lhs->isArray) {
                        if (lhs->varKind == Parameter) {

                            emitRM((char *)"LD", AC1, lhs->offset, offReg, (char *)"address of lhs");

                        }

                        else {

                            emitRM((char *)"LDA", AC1, lhs->offset, offReg, (char *)"address of lhs");

                        }

                        emitRM((char *)"LD", AC2, 1, AC, (char *)"size of rhs");

                        emitRM((char *)"LD", AC3, 1, AC1, (char *)"size of lhs");

                        emitRO((char *)"SWP", AC2, AC3, 6, (char *)"pick smallest size");

                        emitRO((char *)"MOV", AC1, AC, AC2, (char *)"array op =");

                    }

                    else {

                        emitRM((char *)"ST", AC, lhs->offset, offReg, (char *)"Store variable", lhs->attr.name);

                    }

                    break;

                case ADDASS:

                    emitRM((char *)"LD", AC1, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRO((char *)"ADD", AC, AC1, AC, (char *)"op +=");

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                case SUBASS:

                    emitRM((char *)"LD", AC1, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRO((char *)"SUB", AC, AC1, AC, (char *)"op -=");

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                case MULASS:

                    emitRM((char *)"LD", AC1, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRO((char *)"MUL", AC, AC1, AC, (char *)"op *=");

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                case DIVASS:

                    emitRM((char *)"LD", AC1, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRO((char *)"DIV", AC, AC1, AC, (char *)"op /=");

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                case INC:

                    emitRM((char *)"LD", AC, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRM((char *)"LDA", AC, 1, AC,

                        (char *)"increment value of", lhs->attr.name);

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                case DEC:

                    emitRM((char *)"LD", AC, lhs->offset, offReg,

                        (char *)"load lhs variable", lhs->attr.name);

                    emitRM((char *)"LDA", AC, -1, AC,

                        (char *)"decrement value of", lhs->attr.name);

                    emitRM((char *)"ST", AC, lhs->offset, offReg,

                        (char *)"Store variable", lhs->attr.name);

                    break;

                }

            }

            break;
    }
}


void initAGlobalSymbol(std::string sym, void *ptr)
{
    TreeNode *currnode;

    currnode = (TreeNode *)ptr;
    if (currnode->lineno != -1) {
        if (currnode->isArray) {
            emitRM((char *)"LDC", AC, currnode->size-1, 6, (char *)"load size of array", currnode->attr.name);
            emitRM((char *)"ST", AC, currnode->offset+1, GP, (char *)"save size of array", currnode->attr.name);
        }
        if (currnode->kind.decl==VarK &&
            (currnode->varKind == Global || currnode->varKind == LocalStatic)) {	
           if (currnode->child[0]) {

                // compute rhs -> AC;
                codegenExpression(currnode->child[0]);
                // save it
                emitRM((char *)"ST", AC, currnode->offset, GP,
                       (char *)"Store variable", currnode->attr.name);
            }
        }
    }
}


void initGlobalArraySizes()
{
    emitComment((char *)"INIT GLOBALS AND STATICS");
    globals->applyToAllGlobal(initAGlobalSymbol);
    emitComment((char *)"END INIT GLOBALS AND STATICS");
}

