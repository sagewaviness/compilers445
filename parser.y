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

void printToken(TokenData myData, string tokenName, int type = 0) {
	cout << "Line: " << myData.linenum << " Type: " << tokenName;
	if(type==0)
		cout << " Token: " << myData.tokenstr;
	if(type==1)
		cout << " Token: " << myData.nvalue;
	if(type==2)
		cout << " Token: " << myData.cvalue;
	cout << endl;
}
%}
%union
{
   struct   TokenData tinfo ;
}
%token <tinfo> IF THEN ELSE END REPEAT ASSIGN TO 
%token <tinfo> INFINITYLOOP RETURN WHILE DO BREAK 
%token <tinfo> AND NOT BOOLCONST ELSIF 
%token <tinfo> PLUSEQ MULASS TIMEEQ DIVASS LEQ EQ
%token <tinfo> SUBASS ADDASS INC DEC NEQ 
%token <tinfo> STATIC INT BOOL GEQ MIN MAX 
%token <tinfo> BY ID NUMCONST STRINGCONST CHARCONST E OR OP
%token <tinfo> PRECOMPILER LOOP FOR CHAR
%token   <tinfo>  ERROR 

%type <tinfo>  program term 
%%


program :  program term
   |  term  {$$=$1;}
   ;
term  :
      PRECOMPILER {printToken(yylval.tinfo, "PRECOMPILER");}
   |  BOOL {printToken(yylval.tinfo, "BOOL");}
   |  AND {printToken(yylval.tinfo, "AND");}
   |  TO {printToken(yylval.tinfo, "TO");}
   |  IF  {printToken(yylval.tinfo, "IF");}
   |  FOR {printToken(yylval.tinfo, "FOR");} 
   |  THEN {printToken(yylval.tinfo, "THEN");}
   |  ELSE {printToken(yylval.tinfo, "ELSE");}
   |  END  {printToken(yylval.tinfo, "END");}
   |  REPEAT {printToken(yylval.tinfo, "REPEAT");}
   |  BY {printToken(yylval.tinfo, "BY");}
   |  INFINITYLOOP {printToken(yylval.tinfo, "INFINITYLOOP");}
   |  BREAK {printToken(yylval.tinfo, "BREAK");}
   |  NUMCONST {printToken(yylval.tinfo, "NUMCONST");} 
   |  STRINGCONST {printToken(yylval.tinfo, "STRINGCONST");}
   |  RETURN {printToken(yylval.tinfo, "RETURN");}
   |  WHILE {printToken(yylval.tinfo, "WHILE");}
   |  NOT {printToken(yylval.tinfo, "NOT");}
   |  BOOLCONST {printToken(yylval.tinfo, "BOOLCONST");}
   |  ELSIF {printToken(yylval.tinfo, "ELSIF");}
   |  STATIC {printToken(yylval.tinfo, "STATIC");} 
   |  INT {printToken(yylval.tinfo, "INT");}
   |  CHARCONST {printToken(yylval.tinfo, "CHARCONST");}
   |  OR  {printToken(yylval.tinfo, "OR");}
   |  OP  {printToken(yylval.tinfo, "OP");}
   |  ID  {printToken(yylval.tinfo, "ID");}
   |  DO  {printToken(yylval.tinfo, "DO");}
   |  PLUSEQ {printToken(yylval.tinfo, "PLUSEQ");} 
   |  MULASS {printToken(yylval.tinfo, "MULASS");}
   |  TIMEEQ {printToken(yylval.tinfo, "TIMEEQ");}
   |  DIVASS {printToken(yylval.tinfo, "DIVASS");}
   |  LEQ   {printToken(yylval.tinfo, "LEQ");}
   |  GEQ   {printToken(yylval.tinfo, "GEQ");}
   |  EQ    {printToken(yylval.tinfo, "EQ");}
   |  SUBASS {printToken(yylval.tinfo, "SUBASS");}
   |  ADDASS  {printToken(yylval.tinfo, "ADDASS");}
   |  INC   {printToken(yylval.tinfo, "INC");}
   |  DEC   {printToken(yylval.tinfo, "DEC");}
   |  NEQ   {printToken(yylval.tinfo, "NEQ");}
   |  MIN   {printToken(yylval.tinfo, "MIN");}
   |  MAX   {printToken(yylval.tinfo, "MAX");}
   |  CHAR  {printToken(yylval.tinfo, "CHAR");}
   |  ERROR    {cout << "ERROR(SCANNER Line " << yylval.tinfo.linenum << "): Invalid input character " << yylval.tinfo.tokenstr << endl; }
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

