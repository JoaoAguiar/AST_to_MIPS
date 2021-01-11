%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// Variáveis mantidas pelo analisador lexical
int yyline = 1;
%}

%option noyywrap

/***** Scan dos tokens *****/
%%
[ \t]+ {  }

#.*\n { yyline++; }

\n { yyline++; }

"INT:" { return INTEIRO; }
":=" { return EQUALVAR; }
"PRINT:" { return PRINT; }
"SCAN:" { return SCAN; }
"IF:" { return IF; }
"ELSE:" { return ELSE; }
"WHILE:" { return WHILE; }
"END" { return END; }
"BREAK" { return BREAK; }
"CONTINUE" { return CONTINUE; }
"FOR" { return FOR; }

[a-zA-Z][0-9a-zA-Z\_\!]* {
   yylval.nameValue = strdup(yytext);
   return NAME;
}

\".*\" {
   yylval.stringValue = strdup(yytext);
   return STR;
}

\-?[0-9]+ {
   yylval.intValue = atoi(yytext);
   return INT;
}

"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return MOD; }

"==" { return EQUAL; }
"!=" { return DIFF; }
"<" { return LT; }
">" { return GT; }
"<=" { return LTEQ; }
">=" { return GTEQ; }
"&&" { return AND; }
"||" { return OR; }

.  { yyerror("unexpected character"); }
%%
