%{
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "treeUtils.h"
#include "scanType.h"
#include "dot.h"
using namespace std;

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
   if(s == NULL && numErrors == 0)
   {
      printf("ERROR(SYSTEM) : never add a null to sibling list);
      exit(1);
   }
   if(t!= NULL)
   {
      TreeNode *tmp;

      tmp = t; 
      while(tmp->sibling!=NULL) tmp = tmp->sibling;
      tmp->sibling = s;
   }
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
   TokenData *tokenData ;
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
%token <tokenData>  '*' '+' '{' '}' '[' ']' ';' '-' '>' '<' '-' '=' ':' ',' '/' '(' ')' '%' '?'

%type <tree>  program precomList declList decl varDecl scopedVarDecl 
%type <tree>  varDeclList varDeclInit varDeclId 
%type <tree>  typeSpec funDecl 
%type <tree> parms parmList parmTypeList parmIdList parmId
%type <tree> stmt stmtList
%type <tree> matched unmatched 
%type <tree> iterRange
%type <tree> expstmt stmtList returnstmt breakstmt 
%type <tree> exp simpleExp andExp unaryRelExp relExp sumExp minmaxExp
%type <tree> mulExp unaryExp
%type <tree> assignop relop sumop mulop factor
%type <tree> mutable immutablel
%type <tree> call constant
%type <tree> args argList

%%

program : precomList declList 
        ;
precomList : precomList PRECOMPILER    {$$ = $1}
            | PRECOMPILER              {printf("%s\n", yyval.TokenData->tokenstr);}
            | /* empty */              {$$ = NULL}
            ;

declList : declList decl                {}
         | decl                         {}
         ;

decl : varDecl                          {}
     | funDecl                          {}
     ;

varDecl :typeSpec varDeclList';'       {$$ = setType($2, $1, false); yyerrok;}
         ;

scopedVarDecl : STATIC typeSpec varDeclList ';'  {$$ = $3; setType($3,$2,true); yyerrok;}
              | typeSpec varDeclList ';' {$$ = $2; setType($3,$1,false); yyerrok;}
              ;
varDeclList : varDeclList ',' varDeclInit{$$ = addSibling($1, $3); yyerrok;}
            | varDeclInit {$$ = $1;}
            ;

varDeclInit : varDeclId {$$ = $1;}
            ;

varDeclId : ID{$$ = newDeclNode(VarK, UndefinedType, $1);}
          | ID '[' NUMCONST ']' {}
          ;
typeSpec : INT {$$ = Integer;}
         | BOOL {$$ = Boolean;}
         | CHAR  {$$ = Char;}
         ;
funDecl : typeSpec ID '(' parms ')' stmt       {$$ = newDeclNode(Funck, $1, $2, $4, $6)}
        | ID '(' parms ')' stmt                {$$ = newDeclNode(Funck, Void, $1, $3, $5)}
        ;

parms : parmList   {$$ = $1;}
      | /* empty */           {$$ = NULL}
      ;

parmList : parmList ';' parmTypeList {$$ = addSibling($1,$3);}
         | parmTypeList  {$$ = $1;}
         ;

parmTypeList : typeSpec parmIdList {$$ = $2; setType($2, $1, false);}
             ;

parmIdList : parmIdList ',' parmId { $$ = addSibling($1, $3);}
           | parmId {}
           ;

parmId : ID  {}
       | ID '[' ']'  {}
       ;

stmt : matched  {$$ = $1;}
     | unmatched {$$ = $1;}
     ;

matched  : IF simpleExp THEN matched ELSE matched{}
         | WHILE simpleExp DO matched{}
         | FOR ID '=' iterRange DO matched {}
         | expstmt{}
         | compoundstmt{}
         | returnstmt {}
         | breakstmt {}
         ;

iterRange : simpleExp TO simpleExp  {}
          | simpleExp TO simpleExp BY simpleExp{}
          ;

unmatched : IF simpleExp THEN stmt{}
   | IF simpleExp THEN matched ELSE unmatched {}
   | WHILE simpleExp DO unmatched{}
   | FOR ID '=' iterRange DO unmatched{}
   ;

expstmt : exp ';'{}
         ;

compoundstmt : '{' localDecls stmtList '}' {}
             ;

localDecls : localDecls scopedVarDecl     {$$ = newStmtNode(compoundstmt, $1, $2, $3);}
           | /* empty */                  {$$ = NULL}
           ;

stmtList : stmtList stmt  {}
            | /* empty */                 {$$ = NULL}
            ;

returnstmt : RETURN ';' {}
           | RETURN exp ';'   {}
           ;

breakstmt : BREAK ';'      {}
          ;

exp : mutablel assignop exp   {}
      | mutablel INC    {}
      | mutablel DEC    {}
      | simpleExp       {}
      | mutablel assignop error  {}
      ;

assignop : '='    {}
      | ADDASS    {}
      | SUBASS    {}
      | MULASS    {}
      | DIVASS    {}
      ;

simpleExp : simpleExp OR andExp {}
          | andExp         {}
          ;

andExp : andExp AND unaryRelExp  {}
       | unaryRelExp       {}
       ;

unaryRelExp : NOT unaryRelExp {}
            | relExp    {}
            ;

relExp : minmaxExp relop minmaxExp  {}
       | minmaxExp      {}
       ;

relop : LEQ {}
      | '<' {}
      | '>' {}
      | GEQ {}
      | EQ  {}
      | NEQ {}
      ;

minmaxExp : minmaxExp minmaxop sumExp     {}
          | sumExp      {}
          ;


minmaxop : MAX {}
         | MIN {}
         ;

sumExp : sumExp sumop mulExp  {}
      | mulExp {}
      ;

sumop : '+' {}
      | '-' {}
      ;

mulExp : mulExp mulop unaryExp   {}
       | unaryExp {}
       ;

mulop : '*' {}
      | '/' {}
      | '%' {}
      ;

unaryExp : unaryop unaryExp   {}
         | factor             {}
         ;

unaryop : '-'        {}
         | '*'       {}
         | '?'       {}
         ;

factor : immutablel  {}
      | mutablel     {}
      ;

mutablel : ID              {}
         | ID '[' exp ']'  {}
         ;

immutablel : '(' exp ')'   {}
            | call         {}
            | constant  {}
            ;

call : ID '(' args ')'  {}
     ;

args : argList                      {}
     | /*empty*/                    {$$ = NULL}
     ; 

argList : argList ',' exp     {}
        | exp                 {}
        ;

constant : NUMCONST     {}
         | CHARCONST {}
         | STRINGCONST  {}
         | BOOLCONST    {}
         ;

%%
void yyerror (const char *msg)
{ 
   cout << "Error: " <<  msg << endl;
}
int main(int argc, char **argv) {
   //yylval.tinfo.linenum = 1;
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

