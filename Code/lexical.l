%option yylineno


%{
	#include "syntax.tab.h"
	#include <string.h>
	#include <stdlib.h>
	//#include "gtree.h"
	#define SYNTAX

	extern int is_error;
	int yycolumn = 1;
	#define YY_USER_ACTION {\
		yylloc.first_line = yylloc.last_line = yylineno; \
		yylloc.first_column = yycolumn; \
		yylloc.last_column = yycolumn + yyleng - 1; \
		yycolumn += yyleng;	\
	}
	extern void yyerror(const char* s);
	//#define LEX
%}
%option yylineno
digit	[0-9]
letter	[_a-zA-Z]
IntDec_type1	0|([1-9]({digit}{0,8})?)
IntDec_type2	1({digit}{9})
IntDec_type3	20({digit}{8})
IntDec_type4	21[0-3]({digit}{7})
IntDec_type5	214[0-6]({digit}{6})
IntDec_type6	2147[0-3]({digit}{5})
IntDec_type7	21474[0-7]({digit}{4})
IntDec_type8	214748[0-2]({digit}{3})
IntDec_type9	2147483[0-5]({digit}{2})
IntDec_type10	21474836[0-3]({digit}{1})
IntDec_type11	214748364[0-7]
nIntDec_type1	-([1-9]({digit}{0,8})?)
nIntDec_type2	-1({digit}{9})
nIntDec_type3	-20({digit}{8})
nIntDec_type4	-21[0-3]({digit}{7})
nIntDec_type5	-214[0-6]({digit}{6})
nIntDec_type6	-2147[0-3]({digit}{5})
nIntDec_type7	-21474[0-7]({digit}{4})
nIntDec_type8	-214748[0-2]({digit}{3})
nIntDec_type9	-2147483[0-5]({digit}{2})
nIntDec_type10	-21474836[0-3]({digit}{1})
nIntDec_type11	-214748364[0-8]
pIntDec	{IntDec_type1}|{IntDec_type2}|{IntDec_type3}|{IntDec_type4}|{IntDec_type5}|{IntDec_type6}|{IntDec_type7}|{IntDec_type8}|{IntDec_type9}|{IntDec_type10}|{IntDec_type11}
nIntDec	{nIntDec_type1}|{nIntDec_type2}|{nIntDec_type3}|{nIntDec_type4}|{nIntDec_type5}|{nIntDec_type6}|{nIntDec_type7}|{IntDec_type8}|{nIntDec_type9}|{nIntDec_type10}|{nIntDec_type11}
IntDec	{pIntDec}|{nIntDec}
IntOct	0(([1-7]([0-7]{0,9})?)|(1[0-7]{10})|([2-3][0-7]{10}))
IntHex	(0x|0X)[1-9a-fA-F]([0-9a-fA-F]{0,7})?
INT		{IntDec}|{IntOct}|{IntHex}
pFloat	[0-9]+\.[0-9]+
nFloat	-[0-9]+\.[0-9]+
pFloExp	[0-9]*(\.)?[0-9]*[Ee][+-]?[0-9]+
nFloExp -[0-9]*(\.)?[0-9]*[Ee][+-]?[0-9]+
FLOAT	{pFloat}|{nFloat}|{pFloExp}|{nFloExp}
ID		[_a-zA-Z]([_a-zA-Z0-9]{1,51})?
SEMI	;
COMMA	,
ASSIGNOP	\=
RELOP	>|<|>=|<=|==|!=
PLUS	\+
MINUS	\-
STAR	\*
DIV		\/
AND		\&\&
OR		\|\|
DOT		\.
NOT		\!
type_int	int
type_float	float
TYPE	{type_int}|{type_float}
LP		\(
RP		\)
LB		\[
RB		\]
LC		\{
RC		\}
STRUCT	struct
RETURN	return
IF		if
ELSE	else
WHILE	while

%%
{STRUCT} {
	#ifdef LEX
	printf("this is \033[47;30mkeyword\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("STRUCT", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return STRUCT;
	#endif
	/*~!@#$%%^&*()_+`-=[]\{}|;':",./<>?*/
	}
{RETURN} {
	#ifdef LEX
	printf("this is \033[47;30mkeyword\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("RETURN", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return RETURN;
	#endif
	}
{IF}	{
	#ifdef LEX
	printf("this is \033[47;30mkeyword\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("IF", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return IF;
	#endif
	return IF;
	}
{ELSE}	{
	#ifdef LEX
	printf("this is \033[47;30mkeyword\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("ELSE", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return ELSE;
	#endif	
	return  ELSE;	
	}
{WHILE}	{
	#ifdef LEX
	printf("this is \033[47;30mkeyword\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("WHILE", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return WHILE;
	#endif
	}
{INT}	{
	#ifdef LEX
	printf("this is \033[47;30mint\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	int num = 0;
	if(yytext[0] == '0' && (yytext[1] == 'x'||yytext[1] == 'X'))
		num = HextoDec(yytext);
	else if(yytext[0] == '0')
		num = OcttoDec(yytext);
	else
		num = atoi(yytext);
	yylval.gnode = CreateIntGNode(num, yylineno);
	#ifdef SYNTAX	
		return INT;
	#endif
	}
{TYPE}	{
	#ifdef LEX
	printf("this is \033[47;30mtype\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateTypeGNode(yytext, yylineno);
	#ifdef SYNTAX	
		return TYPE;
	#endif
	}
{FLOAT}	{
	#ifdef LEX
	printf("this is \033[47;30mfloat\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateFloatGNode(atof(yytext), yylineno);
	#ifdef SYNTAX	
		return FLOAT;
	#endif
	}
{ID}	{
	#ifdef LEX
	printf("this is \033[47;30mid\033[0m at line \033[45;37m%d \033[0m\n", yylineno);
	#endif
	yylval.gnode = CreateIdGNode(yytext, yylineno);
	#ifdef SYNTAX	
		return ID;
	#endif
	}
{SEMI}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("SEMI", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return SEMI;
	#endif		
	}
{COMMA}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("COMMA", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return COMMA;
	#endif
	}
{ASSIGNOP}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("ASSIGNOP", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return ASSIGNOP;
	#endif	
	}
{RELOP}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateRelopGNode(yylineno, yytext);
	#ifdef SYNTAX	
		return RELOP;
	#endif
	}
{PLUS}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("PLUS", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return PLUS;
	#endif		
	}
{MINUS}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("MINUS", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return MINUS;
	#endif
	}
{STAR}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("STAR", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return STAR;
	#endif
	}
{DIV}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("DIV", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return DIV;
	#endif
	}
{AND}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("AND", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return AND;
	#endif	
	}
{OR}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("OR", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return OR;
	#endif
	}
{DOT}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("DOT", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return DOT;
	#endif	
	}
{NOT}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("NOT", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return NOT;
	#endif
	}
{LP}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("LP", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return LP;
	#endif
	}
{RP}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("RP", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return RP;
	#endif
	}
{LB}	{	
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("LB", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return LB;
	#endif	
	}
{RB}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("RB", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return RB;
	#endif
	}
{LC}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("LC", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return LC;
	#endif	
	}	
{RC}	{
	#ifdef LEX
	printf("this is \033[47;30msymbol\033[0m \033[46;37m%s\033[0m at line \033[45;37m%d \033[0m\n", yytext, yylineno);
	#endif
	yylval.gnode = CreateGNode("RC", yylineno, _INIT_, Terminal, 0);
	#ifdef SYNTAX	
		return RC;
	#endif
	}
"#"		{
	char c = input();
	while (c != '\n') 
		c = input();
	#ifdef LEX
	printf("this is \033[42;35mpre-process parts\033[0m in line \033[42;37m%d\033[0m\n", yylineno-1);
	#endif
}
\n		{ yycolumn = 1; }
[ ]*|(\t)		{}
"//"	{
	char c = input();
	while (1) {
		c = input();
		if(c == '\n')
			break;
		if(c == -1) {
			#ifdef LEX
			printf("in the end\n");
			#endif
			yyerror("SYNTAX ERROR");
			break;
		}
	}
	#ifdef LEX
	printf("\033[42;35mthis is //annotation\033[0m\n");
	#endif
}
"/*"	{
	char c1 = input();
	while (1) {
		//printf("c1c2: %c%c %d %d\n", c1, c2, c1, c2);
		if((c1=='*')){
			char c2 = input();
			if(c2 == '/') {
				#ifdef LEX
				printf("\033[42;35mthis is /**/annotation\033[0m\n");
				#endif
				break;
			}
		}
		if(c1 == -1) {
			#ifdef LEX
			printf("this is read end\n");
			#endif
			is_error = 1;
			yyerror("SYNTAX ERROR");
			break;
		}	
		c1 = input();
	}
}
.		{
		is_error = 1;
		//printf("\033[45;37mError type A at Line %d: Mysterious characters \'%s\'\033[0m\n", yylineno, yytext);
		printf("Error type A at Line %d: Mysterious characters \'%s\'.\n", yylineno, yytext);
	}


%%

