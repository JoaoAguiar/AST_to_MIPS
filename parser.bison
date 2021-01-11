/***** Tokens *****/
%token
  INTEIRO   // int
  EQUALVAR  // =
  PRINT     // printf
  SCAN      // scanf
  IF        // if
  ELSE      // else
  WHILE     // while
  END       // fim
  NAME      // variaveis
  STR       // strings
  INT       // inteiros
  PLUS      // +
  MINUS     // -
  MULT      // *
  DIV       // /
  EQUAL     // ==
  DIFF      // !=
  LT        // <
  GT        // >
  LTEQ      // <=
  GTEQ      // >=
  AND       // &&
  OR        // ||
  MOD       // %
  BREAK     // break
  CONTINUE  // continue
  FOR       // for

/***** Operadores: precedencia e associatividade *****/
// 1 + 2 + 3 usando o %left: (1 + 2) + 3
// 1 + 2 + 3 usando o %right: 1 + (2 + 3)
// O primeiro %left ou %right declaro os operadores com menor precedencia, o seguinte
%left
  DIV
  MULT
%left
  PLUS
  MINUS
%left
  LT
  GT
  LTEQ
  GTEQ
%left
  EQUAL
  DIFF
%left
  AND
  OR

/***** Simbolo da gramatica do nivel Root *****/
// O Bison assume como default que o simbolo inicial da gramatica é o primeiro nãp-terminal especificado na secção de especidifação gramatical
// Podemos alterar o simbolo inicial com o %start
%start program;

/***** Tipos/Valores em associação com os simbolos da gramatica *****/
%union {
  int intValue;
  char* nameValue;
  char* stringValue;
  Instructions* instruction;
  ListInstructions* instructionList;
}

/***** Para especificar multiplos tipos de valores *****/
%type <intValue> INT;
%type <nameValue> NAME;
%type <stringValue> STR
%type <instruction> instruction;
%type <instruction> expression;
%type <instructionList> list;
%type <instructionList> expression_list;


// Uso do %code requires para fazer as declarações irem para o parser.c e para o parser.h
%code requires {
  #include <stdio.h>
  #include <stdlib.h>
  #include "stack.h"

  extern int yylex();
  extern int yyline;
  extern char* yytext;
  extern FILE* yyin;
  extern void yyerror(const char* err);
  ListInstructions* root;
}

%%
// $1, $2, $3, ... refere-se ao 1º simbolo, 2º simbolo, 3º simbolo, ...
// O resultado é guardado no $$.
program:
  list {
    root = $1;
  }

list:
  instruction {
    $$ = addNode($1, NULL);
  }
  |
  instruction list {
    $$ = addNode($1, $2);
  }
  ;

expression_list:
  expression {
    $$ = addNode($1, NULL);
  }
  ;

instruction:
  INTEIRO NAME {
    $$ = stack_DeclareVar($2);
  }
  |
  NAME EQUALVAR expression_list {
    $$ = stack_VarAttribute($1, $3);
  }
  |
  NAME EQUALVAR NAME {
    $$ = stack_VarAttributes($1, $3);
  }
  |
  INTEIRO NAME EQUALVAR expression_list {
    $$ = stack_VarInit($2, $4);
  }
  |
  INTEIRO NAME EQUALVAR NAME {
    $$ = stack_VarsInit($2, $4);
  }
  |
  SCAN NAME {
    $$ = stack_Scan($2);
  }
  |
  PRINT NAME {
    $$ = stack_PrintVar($2);
  }
  |
  PRINT expression_list {
    $$ = stack_Print($2);
  }
  |
  IF expression_list list END {
    $$ = stack_If($2, $3);
  }
  |
  IF expression_list list ELSE list END {
    $$ = stack_IfElse($2, $3, $5);
  }
  |
  WHILE expression_list list END {
    $$ = stack_While($2, $3);
  }
  |
  FOR NAME EQUALVAR expression_list expression_list NAME EQUALVAR expression_list list END {
    $$ = stack_For($2, $4, $5, $8, $9);
  }
  |
  BREAK {
   stack_Break();
  }
  |
  CONTINUE {
   stack_Continue();
  }
  ;

expression:
  INT {
    $$ = stack_Integer($1);
  }
  |
  PLUS expression_list expression_list {
    $$ = stack_Operation(PLUS, $2, $3);
  }
  |
  MULT expression_list expression_list {
    $$ = stack_Operation(MULT, $2, $3);
  }
  |
  MINUS expression_list expression_list {
    $$ = stack_Operation(MINUS, $2, $3);
  }
  |
  DIV expression_list expression_list {
    $$ = stack_Operation(DIV, $2, $3);
  }
  |
  MOD expression_list expression_list {
    $$ = stack_Operation(MOD, $2, $3);
  }
  |
  EQUAL expression_list expression_list {
    $$ = stack_BooleanOperation(EQUAL, $2, $3);
  }
  |
  DIFF expression_list expression_list {
    $$ = stack_BooleanOperation(DIFF, $2, $3);
  }
  |
  LT expression_list expression_list {
    $$ = stack_BooleanOperation(LT, $2, $3);
  }
  |
  GT expression_list expression_list {
    $$ = stack_BooleanOperation(GT, $2, $3);
  }
  |
  LTEQ expression_list expression_list {
    $$ = stack_BooleanOperation(LTEQ, $2, $3);
  }
  |
  GTEQ expression_list expression_list {
    $$ = stack_BooleanOperation(GTEQ, $2, $3);
  }
  |
  AND expression_list expression_list {
    $$ = stack_BooleanOperation(AND, $2, $3);
  }
  |
  OR expression_list expression_list {
    $$ = stack_BooleanOperation(OR, $2, $3);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}
