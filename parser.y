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

//void printToken(TokenData myData, string tokenName, int type = 0) 
//{
//	cout << "Line: " << myData.linenum << " Type: " << tokenName;
//	if(type==0)
//   {
//      cout << " Token: " << myData.tokenstr;
//   }
//	if(type==1)
//   {
//      cout << " Token: " << myData.nvalue;
//   }
//	if(type==2)
//   {
//      cout << " Token: " << myData.cvalue;
//   }
		
//	cout << endl;
//}

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

%token <tokenData> IF THEN ELSE END REPEAT ASSIGN TO 
%token <tokenData> INFINITYLOOP RETURN WHILE DO BREAK 
%token <tokenData> AND NOT BOOLCONST ELSIF 
%token <tokenData> PLUSEQ MULASS TIMEEQ DIVASS LEQ EQ
%token <tokenData> SUBASS ADDASS INC DEC NEQ 
%token <tokenData> STATIC INT BOOL GEQ MIN MAX 
%token <tokenData> BY ID NUMCONST STRINGCONST CHARCONST E OR OP
%token <tokenData> PRECOMPILER LOOP FOR CHAR
%token <tokenData>  ERROR COMMENT
%token <tokenData>  '*' '+' '{' '}' '[' ']' ';' '>' '<' '-' '=' ':' ',' '/' '(' ')' '%' '?'
%token <tokenData> CHSIGN SIZEOF LASTOP

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
%type <tokenData> assignop unaryop minmaxop relop sumop mulop 
%type <tree> mutablel immutablel factor
%type <tree> call constant
%type <tree> args argList 
%type <type> typeSpec
%%

program : precomList declList 
        ;
precomList : precomList PRECOMPILER    {$$ = $1;}
            | PRECOMPILER              {printf("%s\n", yyval.tokenData->tokenstr);}
            | /* empty */              {$$ = NULL;}
            ;

declList : declList decl         {}
         | decl                  {}
         ;

decl : varDecl                   {}
     | funDecl                   {}
     ;

varDecl :typeSpec varDeclList ';'               {$$ = $2; setType($2, $1, false); yyerrok;}
         ;

scopedVarDecl : STATIC typeSpec varDeclList ';' {$$ = $3; setType($3,$2,true); yyerrok;}
              | typeSpec varDeclList ';'        {$$ = $2; setType($2, $1, false); yyerrok;}
              ;
varDeclList : varDeclList ',' varDeclInit       {$$ = addSibling($1, $3); yyerrok;}
            | varDeclInit                       {$$ = $1;}
            ;

varDeclInit : varDeclId            {$$ = $1;}
            ;

varDeclId : ID                                  {$$ = newDeclNode(VarK, UndefinedType, $1);}
          | ID '[' NUMCONST ']'                 {}
          ;
typeSpec : INT                   {$$ = Integer;}
         | BOOL                  {$$ = Boolean;}
         | CHAR                  {$$ = Char;}
         ;
funDecl : typeSpec ID '(' parms ')' stmt       {$$ = newDeclNode(FuncK, $1, $2, $4, $6);}
        | ID '(' parms ')' stmt                {$$ = newDeclNode(FuncK, Void, $1, $3, $5);}
        ;

parms : parmList                               {$$ = $1;}
      | /* empty */                            {$$ = NULL;}
      ;

parmList : parmList ';' parmTypeList           {$$ = addSibling($1,$3);}
         | parmTypeList                        {$$ = $1;}
         ;

parmTypeList : typeSpec parmIdList             {$$ = $2; setType($2, $1, false);}
             ;

parmIdList : parmIdList ',' parmId             {$$ = addSibling($1, $3);}
           | parmId                            {$$ = $1}
           ;

parmId : ID                                    {}
       | ID '[' ']'                            {}
       ;

stmt : matched                                 {$$ = $1;}
     | unmatched                               {$$ = $1;}
     ;

matched  : IF simpleExp THEN matched ELSE matched  {}
         | WHILE simpleExp DO matched              {}
         | FOR ID '=' iterRange DO matched         {}
         | expstmt                                 {}
         | compoundstmt                            {}
         | returnstmt                              {}
         | breakstmt                               {}
         ;

iterRange : simpleExp TO simpleExp                 {}
          | simpleExp TO simpleExp BY simpleExp    {}
          ;

unmatched : IF simpleExp THEN stmt                {}
   | IF simpleExp THEN matched ELSE unmatched     {}
   | WHILE simpleExp DO unmatched                 {}
   | FOR ID '=' iterRange DO unmatched            {}
   ;

expstmt : exp ';'                           {$$ = $1;}
         ;

compoundstmt : '{' localDecls stmtList '}'  {$$ = newStmtNode(CompoundK, $1, $2, $3);}
             ;

localDecls : localDecls scopedVarDecl       {$$ = addSibling($1,$2);}
           | /* empty */                    {$$ = NULL;}
           ;

stmtList : stmtList stmt                    {$$ = ($2 ==NULL? $1: addSibling($1, $2));}
            | /* empty */                   {$$ = NULL;}
            ;

returnstmt : RETURN ';'                     {$$ = newStmtNode(ReturnK, $1);}
           | RETURN exp ';'                 {$$ = newStmtNode(ReturnK, $1, $2);}
           ;

breakstmt : BREAK ';'                       {$$ = newStmtNode(BreakK, $1);}
          ;

exp : mutablel assignop exp               {$$ = newExpNode(AssignK, $2, $1, $3);}
      | mutablel INC                      {$$ = newExpNode(AssignK, $2, $1);}
      | mutablel DEC                      {$$ = newExpNode(AssignK, $2, $1);}
      | simpleExp                         {$$ = $1;}
      | mutablel assignop error           {$$ = NULL;}
      ;

assignop : '='    {$$ = $1;}
      | ADDASS    {$$ = $1;}
      | SUBASS    {$$ = $1;}
      | MULASS    {$$ = $1;}
      | DIVASS    {$$ = $1;}
      ;

simpleExp : simpleExp OR andExp     {$$ = newExpNode(OpK, $2, $1,$3);}
          | andExp                  {$$ = $1;}
          ;

andExp : andExp AND unaryRelExp     {$$ = newExpNode(OpK, $2,$1,$3);}
       | unaryRelExp                {$$ = $1;}
       ;

unaryRelExp : NOT unaryRelExp       {$$ = newExpNode(OpK, $1, $2);}
            | relExp                {$$ = $1;}
            ;

relExp : minmaxExp relop minmaxExp  {$$ = newExpNode(OpK, $2,$1,$3);}
       | minmaxExp                  {$$ = $1;}
       ;

relop : LEQ       {$$ = $1;}
      | '<'       {$$ = $1;}
      | '>'       {$$ = $1;}
      | GEQ       {$$ = $1;}
      | EQ        {$$ = $1;}
      | NEQ       {$$ = $1;}
      ;

minmaxExp : minmaxExp minmaxop sumExp     {$$ = newExpNode(OpK, $2,$1,$3);}
          | sumExp                        {$$ = $1;}
          ;


minmaxop : MAX       {$$ = $1;}
         | MIN       {$$ = $1;}
         ;

sumExp : sumExp sumop mulExp     {$$ = newExpNode(OpK, $2,$1,$3);}
      | mulExp                   {$$ = $1;}
      ;

sumop : '+'       {$$ = $1;}
      | '-'       {$$ = $1;}
      ;

mulExp : mulExp mulop unaryExp   {$$ = newExpNode(OpK, $2,$1,$3);}
       | unaryExp                {$$ = $1;}
       ;

mulop : '*'       {$$ = $1;}
      | '/'       {$$ = $1;}
      | '%'       {$$ = $1;}
      ;

unaryExp : unaryop unaryExp   {$$ = newExpNode(OpK, $1,$2);}
         | factor             {$$ = $1;}
         ;

unaryop : '-'        {$1->tokenclass = CHSIGN; $$ = $1;}
         | '*'       {$1->tokenclass = SIZEOF; $$ = $1;}
         | '?'       {$$ = $1;}
         ;

factor : immutablel  {$$ = $1;}
      | mutablel     {$$ =$1;}
      ;

mutablel : ID              {$$ = newExpNode(IdK, $1); 
			                     $$->attr.name = $1->svalue; 
			                     $$->isArray = false; }
         | ID '[' exp ']'  {$$ = newExpNode(OpK, $2, NULL, $3);
			                     $$->child[0] = newExpNode(IdK,$1);
                              $$->child[0]->attr.name = $1->svalue; 
                              $$->isArray = false; }
         ;

immutablel : '(' exp ')'   {$$ = $2;}
            | call         {$$ = $1;}
            | constant     {$$ = $1;}
            ;

call : ID '(' args ')'     {$$ = newExpNode(CallK, $1); $$->attr.name = $1->svalue;}
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
                           $$->isArray = true;
                           $$->size = 1;}
         ;

%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}

int main(int argc, char **argv) {
   //yylval.tokenData.linenum = 1;
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
      printTree(stdout, syntaxTree, true, true);
      if(dotAST) {
         printDotTree(stdout, syntaxTree, false, false);
      }
   }
   else {
      printf("-----------\n");
      printf("Errors: %d\n", numErrors);
      printf("-----------\n");
   }
   return 0;
}

