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
   /////////
   //printf("int %d char %c \n",tokenClass, tokenClass);
   yylval.tokenData = new TokenData;
   yylval.tokenData->tokenclass = tokenClass;
   yylval.tokenData->linenum = linenum;
   yylval.tokenData->tokenstr = lastToken = strdup(svalue);
   yylval.tokenData->cvalue = svalue[0];
   
   // may cause overflow
   yylval.tokenData->nvalue = atoi(svalue);
   yylval.tokenData->svalue = strdup(svalue);
   
   switch(tokenClass)
   {
      case BOOLCONST: 
	yylval.tokenData->nvalue = ((lastToken[0]=='t') ? 1 : 0);
	break;
      case STRINGCONST: 
	yylval.tokenData->nvalue = strlen(svalue) - 2; //take quotes off ""

	//char* temp;
	//temp = strdup(svalue);
        //temp = &temp[1];
	//snprintf(yylval.tokenData->svalue, yylval.tokenData->nvalue, temp);

        for(int i=0 ; i < strlen(svalue)-1; i++)
	{
         yylval.tokenData->svalue[i] = yylval.tokenData->svalue[i+1];
	}

        break;
      case CHARCONST:
	yylval.tokenData->cvalue = svalue[1];
        if(svalue[1] == '\\')
        {
	    if(svalue[2] == 'n')
                yylval.tokenData->cvalue = '\n';
            if(svalue[2] == '0')
		yylval.tokenData->cvalue = '\0';
        }
        break;
   } 
   return tokenClass;
}

%}

%option noyywrap


letter      	[a-zA-Z]
digit    	[0-9]
underbar	[_]
quote    	[\']
letdig      	{digit}|{letter}|{underbar}
op              [\(\)\*\+\,\-\/\:\;\<\=\>\?\[\]\%\{\}]
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
{op}      {return setValue(line, yytext[0], yytext);}
{comment}       ;
\n              {line++ ;}
{whitespace}+  ;
.               {printf("ERROR(%d): Token error, invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]);}

