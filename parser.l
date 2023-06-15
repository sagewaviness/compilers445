%{
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "treeNodes.h"
#include "scanType.h"
#include "parser.tab.h"
using namespace std;


#define YY_DECL extern "C" int yylex()
#define YYSTYPE int

int line = 1;

char *lastToken = (char*)"";

int setValue(int linenum, int tokenClass, char *svalue)
{
   yylval.tokenData = new TokenData;
   yylval.tokenData->tokenclass = tokenClass;
   yylval.tokenData->linenum = linenum;
   yylval.tokenData->tokenstr = lastToken = strdup(svalue);
   yylval.tokenData->cvalue = svalue[0];
   
   // may cause overflow
   yylval.tokenData->nvalue = atoi(svalue);
   yylval.tokenData->svalue = strdup(svalue);

   return tokenClass;
}

%}

%option noyywrap


letter      	[a-zA-Z_]
digit    	[0-9]
underbar	[_]
quote    	[\']
letdig      	{digit}|{letter}|{underbar}
limitters   	[\;\,\(\)\{\}\[\]]
op              [\(\)\*\+\,\-\/\:\;\<\=\>\?\[\]\%\{\}]
colon           [\:]
op2             {op}|{limitters}|{colon}
id   		{letter}{letdig}*
numbers  	{digit}+
chars 		[\']\\?.[\']
strings 	\"[^"]*\"  
whitespace      [\ \t]
comment         "//".* 

%%

^"#DRBC ".* {return setValue(line, PRECOMPILER, yytext);}
^"#DRBCRUN ".* {return setValue(line , PRECOMPILER, yytext);}
"if"	{return setValue(line, IF, yytext);}
"then"  {return setValue(line, THEN, yytext);}
"else"  {return setValue(line, ELSE, yytext);}
"end"   {return setValue(line, END, yytext);}
"loop"  {return setValue(line, LOOP, yytext);}
"loop forever"  {return setValue(line, INFINITYLOOP, yytext);}
"return"        {return setValue(line, RETURN, yytext);}
"while"         {return setValue(line, WHILE, yytext);}
"do"            {return setValue(line, DO, yytext);}
"break"         {return setValue(line, BREAK, yytext);}
"and"           {return setValue(line, AND, yytext);}
"not"           {return setValue(line, NOT, yytext);}
"to"            {return setValue(line, TO, yytext);}
"for"           {return setValue(line, FOR, yytext);}
"true"          {return setValue(line, BOOLCONST, yytext);}
"false"         {return setValue(line, BOOLCONST, yytext);}
"by"            {return setValue(line, BY, yytext);}
"eslif"         {return setValue(line, ELSIF, yytext);}
"or"            {return setValue(line, OR, yytext);}
"char"          {return setValue(line, CHAR, yytext);}
"+="            {return setValue(line, ADDASS, yytext);}
"-="            {return setValue(line, SUBASS, yytext);}
"*="            {return setValue(line, MULASS, yytext);}
"/="            {return setValue(line, DIVASS, yytext);}
"<="		{return setValue(line, LEQ, yytext);}
">=" 		{return setValue(line, GEQ, yytext);}
"=="		{return setValue(line, EQ, yytext);}
"++"            {return setValue(line, INC, yytext);}
"--"            {return setValue(line, DEC, yytext);}
"!="            {return setValue(line, NEQ, yytext);}
"static"        {return setValue(line, STATIC, yytext);}
"int"           {return setValue(line, INT, yytext);}
"bool"          {return setValue(line, BOOL, yytext);}
":<:"           {return setValue(line, MIN, yytext);}
":>:"           {return setValue(line, MAX, yytext);}

{numbers}       {return setValue(line, NUMCONST, yytext);}
{id}    	{return setValue(line, ID, yytext);}
{strings}       {return setValue(line, STRINGCONST, yytext);}
{chars}		{return setValue(line, CHARCONST, yytext);}
{op}|{op2}      {return setValue(line, OP, yytext);}
{comment}       {return setValue(line, COMMENT, yytext);}
\n              {line++ ;}
{whitespace}+  ;
.               {printf("ERROR(%d): Token error, invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]);}

