%{
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "treeNodes.h"
#include "treeUtils.h"
#include "dot.h"
#include "scanType.h"
using namespace std;

int numErrors, numWarnings;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *msg);

void printToken(TokenData myData, string tokenName, int type = 0) 
{
	cout << "Line: " << myData.linenum << " Type: " << tokenName;
	if(type==0)
  {
     cout << " Token: " << myData.tokenstr;
  }
	if(type==1)
  {
     cout << " Token: " << myData.nvalue;
  }
	if(type==2)
  {
     cout << " Token: " << myData.cvalue;
  }
		
	cout << endl;
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
    if (s==NULL && numErrors==0) {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
    if (t!=NULL) {
        TreeNode *tmp;

        tmp = t;
        while (tmp->sibling!=NULL) tmp = tmp->sibling;
        tmp->sibling = s;
        return t;
    }
    return s;
}

void setType(TreeNode *t, ExpType type, bool isStatic)
{
   while(t)
   {
      t->type = type;
      t->isStatic = isStatic;
      t = t->sibling;
   }
}

TreeNode *syntaxTree;

%}

%union
{
   TokenData *tokenData;
   TreeNode *tree;
   ExpType type; // for passing typespec up the tree 
}


%type <tree>  program precomList declList decl varDecl scopedVarDecl 
%type <tree>  varDeclList varDeclInit varDeclId 
%type <tree> funDecl localDecls 
%type <tree> parms parmList parmTypeList parmIdList parmId
%type <tree> stmt stmtList
%type <tree> matched unmatched 
%type <tree> iterRange
%type <tree> expstmt  returnstmt breakstmt compoundstmt 
%type <tree> exp simpleExp andExp unaryRelExp relExp sumExp minmaxExp
%type <tree> mulExp unaryExp
%type <tree> mutable immutable factor
%type <tree> call constant
%type <tree> args argList 
%type <type> typeSpec
%type <tokenData> assignop minmaxop mulop relop sumop unaryop


%token <tokenData> FIRSTOP
%token <tokenData> ADDASS AND DEC DIVASS EQ GEQ INC LEQ MAX MIN MULASS NEQ NOT OR SUBASS
%token <tokenData> CHSIGN SIZEOF
%token <tokenData> '*' '+' '-' '/' '<' '=' '>' '%' '?' 
%token <tokenData> PRECOMPILER
%token <tokenData> LASTOP 

// we require that all token classes larger than 255 be followed by LASTTERM
%token <tokenData> BOOL BREAK BY CHAR DO ELSE FOR IF INT RETURN STATIC THEN TO WHILE
%token <tokenData> BOOLCONST CHARCONST ID NUMCONST STRINGCONST
%token <tokenData> '{' ';' ':' '}' '(' ')' ',' '[' ']'
%token <tokenData> LASTTERM
%%

program : precomList declList          {syntaxTree = $2;}
        ;

precomList  : precomList PRECOMPILER                      { $$ = NULL; printf("%s\n", yylval.tokenData->tokenstr);}
             | PRECOMPILER                                 { $$ = NULL; printf("%s\n", yylval.tokenData->tokenstr);}
             | /* empty */                                 { $$ = NULL;}
             ;

declList : declList decl                {$$ = addSibling($1,$2);}
         | decl                         {$$ = $1;}
         ;

decl : varDecl                          {$$ = $1;}
     | funDecl                          {$$ = $1;}
     ;

varDecl :typeSpec varDeclList ';'       {$$ = $2; setType($2, $1, false); yyerrok;}
         ;

scopedVarDecl : STATIC typeSpec varDeclList ';'  {$$ = $3; setType($3,$2,true); yyerrok;}
              | typeSpec varDeclList ';'      {$$ = $2; setType($2, $1, false); yyerrok;}
              ;
varDeclList : varDeclList ',' varDeclInit   {$$ = addSibling($1, $3); yyerrok;}
            | varDeclInit                   {$$ = $1;}
            ;

varDeclInit : varDeclId                   {$$ = $1;}
            | varDeclId ':' simpleExp     { $$ = $1; if ($$ != NULL) $$->child[0] = $3;}
            ;

varDeclId : ID                            {$$ = newDeclNode(VarK, UndefinedType, $1);}
          | ID '[' NUMCONST ']'           {$$ = newDeclNode(VarK, UndefinedType,$1); 
				                                 $$->isArray = true;
				                                 $$->size = $3->nvalue + 1;}
          ;
typeSpec : INT 				               {$$ = Integer;}	
         | BOOL 			                  {$$ = Boolean;}
         | CHAR  			                   {$$ = Char;}
         ;
funDecl : typeSpec ID '(' parms ')' stmt       {$$ = newDeclNode(FuncK, $1, $2, $4, $6);}
        | ID '(' parms ')' stmt                {$$ = newDeclNode(FuncK, Void, $1, $3, $5);}
        ;

parms : parmList   	      {$$ = $1;}
      | /* empty */           {$$ = NULL;}
      ;

parmList : parmList ';' parmTypeList           {$$ = addSibling($1,$3);}
         | parmTypeList                        {$$ = $1;}
         ;

parmTypeList : typeSpec parmIdList             {$$ = $2; setType($2, $1, false);}
             ;

parmIdList : parmIdList ',' parmId              { $$ = addSibling($1, $3);}
           | parmId                             {$$ = $1;}
           ;

parmId : ID                         {$$ = newDeclNode(ParamK, UndefinedType, $1);
                                           $$->isArray = false; 
    		                                    $$->size = 1;}
       | ID '[' ']'                 {$$ = newDeclNode(ParamK, UndefinedType, $1);
          	                               $$->isArray = true;
                	                           $$->size = 1;}
       ;

stmt : matched                                 {$$ = $1;}
     | unmatched                               {$$ = $1;}
     ;

matched  : IF simpleExp THEN matched ELSE matched        {$$ = newStmtNode(IfK, $1,$2,$4,$6);}
         | WHILE simpleExp DO matched                    {$$ = newStmtNode(WhileK,$1,$2,$4);}
         | FOR ID '=' iterRange DO matched               {$$ = newStmtNode(ForK, $1, NULL, $4,$6);
                                                            $$->child[0] = newDeclNode(VarK,Integer,$2);
                                                            $$->child[0]->attr.name = $2->svalue;
                                                            $$->child[0]->isArray = false;}
         | expstmt                                       {$$ = $1;}
         | compoundstmt                                  {$$ = $1;}
         | returnstmt                                    {$$ = $1;}
         | breakstmt                                     {$$ = $1;}
         ;

iterRange : simpleExp TO simpleExp                       {$$ = newStmtNode(RangeK, $2,$1,$3);}
          | simpleExp TO simpleExp BY simpleExp          {$$ = newStmtNode(RangeK, $2,$1,$3,$5);}
          ;

unmatched : IF simpleExp THEN stmt                       {$$ = newStmtNode(IfK, $1,$2,$4);}
   | IF simpleExp THEN matched ELSE unmatched            {$$ = newStmtNode(IfK, $1,$2,$4,$6);}
   | WHILE simpleExp DO unmatched                        {$$ = newStmtNode(WhileK, $1,$2,$4);}
   | FOR ID '=' iterRange DO unmatched                   {$$ = newStmtNode(ForK,$1,NULL,$4,$6);
                                                            $$->child[0] = newDeclNode(VarK,Integer,$2);
                                                            $$->child[0]->attr.name = $2->svalue;
                                                            $$->child[0]->isArray = false;
                                                               $$->child[0]->size = 1;}
   ;

expstmt : exp ';'                {$$ = $1;}
        | ';'                    {$$ = NULL;}
         ;

compoundstmt : '{' localDecls stmtList '}'      {$$ = newStmtNode(CompoundK, $1, $2, $3);}
             ;

localDecls : localDecls scopedVarDecl        {$$ = addSibling($1,$2);}
           | /* empty */                     {$$ = NULL;}
           ;

stmtList : stmtList stmt                  {$$ = ($2 ==NULL? $1: addSibling($1, $2));}
            | /* empty */                 {$$ = NULL;}
            ;

returnstmt : RETURN ';'          {$$ = newStmtNode(ReturnK, $1);}
           | RETURN exp ';'      {$$ = newStmtNode(ReturnK, $1, $2);}
           ;

breakstmt : BREAK ';'            {$$ = newStmtNode(BreakK, $1);}
          ;

exp : mutable assignop exp       {$$ = newExpNode(AssignK, $2, $1, $3);}
      | mutable INC              {$$ = newExpNode(AssignK, $2, $1);}
      | mutable DEC              {$$ = newExpNode(AssignK, $2, $1);}
      | simpleExp                {$$ = $1;}
      | mutable assignop error   {$$ = NULL;}
      ;

assignop : '='    {$$ = $1;}
      | ADDASS    {$$ = $1;}
      | SUBASS    {$$ = $1;}
      | MULASS    {$$ = $1;}
      | DIVASS    {$$ = $1;}
      ;

simpleExp : simpleExp OR andExp        {$$ = newExpNode(OpK, $2, $1,$3);}
          | andExp                     {$$ = $1;}
          ;

andExp : andExp AND unaryRelExp     {$$ = newExpNode(OpK, $2,$1,$3);}
       | unaryRelExp                {$$ = $1;}
       ;

unaryRelExp : NOT unaryRelExp        {$$ = newExpNode(OpK, $1, $2);}
            | relExp                 {$$ = $1;}
            ;

relExp : minmaxExp relop minmaxExp  {$$ = newExpNode(OpK, $2,$1,$3);}
       | minmaxExp                  {$$ = $1;}
       ;

relop : LEQ {$$ = $1;}
      | '<' {$$ = $1;}
      | '>' {$$ = $1;}
      | GEQ {$$ = $1;}
      | EQ  {$$ = $1;}
      | NEQ {$$ = $1;}
      ;

minmaxExp : minmaxExp minmaxop sumExp     {$$ = newExpNode(OpK, $2,$1,$3);}
          | sumExp                        {$$ = $1;}
          ;


minmaxop : MAX                   {$$ = $1;}
         | MIN                   {$$ = $1;}
         ;

sumExp : sumExp sumop mulExp     {$$ = newExpNode(OpK, $2,$1,$3);}
      | mulExp                   {$$ = $1;}
      ;

sumop : '+'                {$$ = $1;}
      | '-'                {$$ = $1;}
      ;

mulExp : mulExp mulop unaryExp   {$$ = newExpNode(OpK, $2,$1,$3);}
       | unaryExp                {$$ = $1;}
       ;

mulop : '*'                      {$$ = $1;}
      | '/'                      {$$ = $1;}
      | '%'                      {$$ = $1;}
      ;

unaryExp : unaryop unaryExp   {$$ = newExpNode(OpK, $1,$2);}
         | factor             {$$ = $1;}
         ;

unaryop : '-'        {$1->tokenclass = CHSIGN; $$ = $1;}
         | '*'       {$1->tokenclass = SIZEOF; $$ = $1;}
         | '?'       {$$ = $1;}
         ;

factor : immutable  {$$ = $1;}
      | mutable     {$$ =$1;}
      ;

mutable : ID                  {$$ = newExpNode(IdK, $1); 
                                 $$->attr.name = $1->svalue; 
                                 $$->isArray = false; }
         | ID '[' exp ']'     {$$ = newExpNode(OpK, $2, NULL, $3);
                                 $$->child[0] = newExpNode(IdK,$1);
                                 $$->child[0]->attr.name = $1->svalue; 
                                 $$->isArray = false;
			     
				}
         ;

immutable : '(' exp ')'   {$$ = $2;}
            | call        {$$ = $1;}
            | constant    {$$ = $1;}
            ;

call : ID '(' args ')'  {$$ = newExpNode(CallK, $1, $3); $$->attr.name = $1->svalue;}
     ;

args : argList                      {$$ = $1;}
     | /*empty*/                    {$$ = NULL;}
     ; 

argList : argList ',' exp     {$$ = addSibling($1, $3);}
        | exp                 {$$ = $1;}
        ;

constant : NUMCONST     { $$ = newExpNode(ConstantK, $1); 
                           $$->attr.value = $1->nvalue;
                           $$->type = Integer; 
                           $$->isArray = false;
                           $$->size = 1;}
         | CHARCONST    {$$ = newExpNode(ConstantK, $1); 
                           $$->attr.cvalue = $1->cvalue;
                           $$->type = Char; 
                           $$->isArray = false;
                           $$->size = 1;}
         | STRINGCONST  {$$ = newExpNode(ConstantK, $1); 
                           $$->attr.string = $1->svalue;
                           $$->type = Char; 
                           $$->isArray = true;
                           $$->size = $1->nvalue+1;/* this is probably wrong*/} 
         | BOOLCONST    {$$ = newExpNode(ConstantK, $1); 
                           $$->attr.value = $1->nvalue;
                           $$->type = Boolean; 
                           $$->isArray = false;
                           $$->size = 1;}
         ;

%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}

char *largerTokens[LASTTERM+1];
void initTokenStrings() 
{
   //const char* defaultMessage = "Unknown (or more likely unimplemented) largerTokens"; 
   //for (int q = 0; q < 512; q++) 
   //{
     //largerTokens[q] = (char*)defaultMessage; 
   //}
   largerTokens[ADDASS] = (char *)"+=";
   largerTokens[AND] = (char *)"and";
   largerTokens[BOOL] = (char *)"bool";
   largerTokens[BOOLCONST] = (char *)"boolconst";
   largerTokens[BREAK] = (char *)"break";
   largerTokens[BY] = (char *)"by";
   largerTokens[CHAR] = (char *)"char";
   largerTokens[CHARCONST] = (char *)"charconst";
   largerTokens[CHSIGN] = (char *)"chsign";
   largerTokens[DEC] = (char *)"--";
   largerTokens[DIVASS] = (char *)"/=";
   largerTokens[DO] = (char *)"do";
   largerTokens[ELSE] = (char *)"else";
   largerTokens[EQ] = (char *)"==";
   largerTokens[FOR] = (char *)"for";
   largerTokens[GEQ] = (char *)">=";
   largerTokens[ID] = (char *)"id";
   largerTokens[IF] = (char *)"if";
   largerTokens[INC] = (char *)"++";
   largerTokens[INT] = (char *)"int";
   largerTokens[LEQ] = (char *)"<=";
   largerTokens[MAX] = (char *)":>:";
   largerTokens[MIN] = (char *)":<:";
   largerTokens[MULASS] = (char *)"*=";
   largerTokens[NEQ] = (char *)"!=";
   largerTokens[NOT] = (char *)"not";
   largerTokens[NUMCONST] = (char *)"numconst";
   largerTokens[OR] = (char *)"or";
   largerTokens[RETURN] = (char *)"return";
   largerTokens[SIZEOF] = (char *)"sizeof";
   largerTokens[STATIC] = (char *)"static";
   largerTokens[STRINGCONST] = (char *)"stringconst";
   largerTokens[SUBASS] = (char *)"-=";
   largerTokens[THEN] = (char *)"then";
   largerTokens[TO] = (char *)"to";
   largerTokens[WHILE] = (char *)"while";
   largerTokens[LASTTERM] = (char *)"lastterm";
}

static char tokenBuffer[16];
char *tokenToStr(int type)
{
    if (type > LASTTERM) {
      //////////////
    // printf("int %d char %c lastterm %d\n", type,type, LASTTERM);
      return (char *)"UNKNOWN";
    }
    else if (type > 256) {
      return largerTokens[type];
    }
    else if ((type < 32) || (type > 127)) {
      sprintf(tokenBuffer, "Token#%d", type);
    } else {
      tokenBuffer[0] = type;
      tokenBuffer[1] = '\0';
    }
    return tokenBuffer;
}

int main(int argc, char **argv) {
   //yylval.tokenData->linenum = 1;
   initTokenStrings();
   yylval.tokenData = (TokenData*)malloc(sizeof(TokenData));
   yylval.tree = (TreeNode*)malloc(sizeof(TreeNode));
     
   numErrors = 0; 
   numWarnings = 0; 
   int index;
   char *file = NULL;
   bool dotAST = false;             // make dot file of AST
   extern FILE *yyin;
   
   int ch;
   while ((ch = getopt(argc, argv, "d")) != -1) {
      switch (ch) {
         case 'd':
                 dotAST = true;
                 break;
         case '?':
         default:
                 //usage();
               ;
      }
   }
   if ( optind == argc ) yyparse();
   for (index = optind; index < argc; index++)
   {
      yyin = fopen (argv[index], "r");
      yyparse();
      fclose (yyin);
   }
   if (numErrors==0) {
      printTree(stdout, syntaxTree, false, false);
      if(dotAST) {
         printDotTree(stdout, syntaxTree, false, false);
      }
   }
   else {
      printf("-----------\n");
      printf("Errors: %d\n", numErrors);
      printf("-----------\n");
   }
   
   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}

