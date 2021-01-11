// Definições da Stack
#ifndef __stack_h__
#define __stack_h__

// Tipo de Instrucões
typedef struct _Instructions {
  enum {
    instructionsINTEGER,
    instructionsOPERATION,
    instructionsBOOLEAN,
    instructionsDECLARE,
    instructionsATTRIBUTE,
    instructionsATTRIBUTE_2,
    instructionsINIT,
    instructionsINIT_2,
    instructionsSCAN,
    instructionsPRINT,
    instructionsPRINT_VAR,
    instructionsIF,
    instructionsIF_ELSE,
    instructionsWHILE,
    instructionsFOR,
    instructionsBREAK,
    instructionsCONTINUE
  } kind;

  union {
    int value;

    struct {
      int operator;
      struct _ListInstructions* expression_left;
      struct _ListInstructions* expression_right;
    } instruction_operator;
    struct {
      int operator;
      struct _ListInstructions* expression_left;
      struct _ListInstructions* expression_right;
    } boolean;
    struct {
      char* var_name;
    } declare_var;
    struct {
      char* var_name;
      struct _ListInstructions* expression;
    } attribute_var;
    struct {
      char* var_name1;
      char* var_name2;
    } attribute_vars;
    struct {
      char* var_name;
      struct _ListInstructions* list_expression;
    } var_init;
    struct {
      char* var_name1;
      char* var_name2;
    } vars_init;
    struct {
      char* var_name;
    } scan_function;
    struct {
      struct _ListInstructions* list_expression;
    } print_function;
    struct {
      char* var_name;
    } print_var;
    struct {
      struct _ListInstructions* expression;
      struct _ListInstructions* list;
    } if_function;
    struct {
      struct _ListInstructions* list_if;
      struct _ListInstructions* expression;
      struct _ListInstructions* list_else;
    } if_else_function;
    struct {
      struct _ListInstructions* expression;
      struct _ListInstructions* list;
    } while_function;
    struct {
      char* var_name;
      struct _ListInstructions* expression1;
      struct _ListInstructions* expression2;
      struct _ListInstructions* expression3;
      struct _ListInstructions* list;
    } for_function;
  } attribute;
} Instructions;
// Lista de Instruções
typedef struct _ListInstructions {
  struct _Instructions* head;
  struct _ListInstructions* tail;
} ListInstructions;

Instructions* stack_Integer(int value);
Instructions* stack_Operation(int operator, ListInstructions* left, ListInstructions* right);
Instructions* stack_BooleanOperation(int operator, ListInstructions* left, ListInstructions* right);
Instructions* stack_DeclareVar(char *var);
Instructions* stack_VarAttribute(char *var, ListInstructions* list);
Instructions *stack_VarAttributes(char *var1, char *var2);
Instructions* stack_VarInit(char *var, ListInstructions* list);
Instructions* stack_VarsInit(char *var1, char *var2);
Instructions* stack_Scan(char *var);
Instructions* stack_PrintVar(char *var);
Instructions* stack_Print(ListInstructions* list);
Instructions* stack_If(ListInstructions* expression, ListInstructions* list);
Instructions* stack_IfElse(ListInstructions* expression, ListInstructions* list1, ListInstructions* list2);
Instructions* stack_While(ListInstructions* expression, ListInstructions* list);
Instructions* stack_For(char *var, ListInstructions* expression1, ListInstructions* expression2, ListInstructions* expression3, ListInstructions* list);
Instructions* stack_Break();
Instructions* stack_Continue();

ListInstructions* addNode(Instructions* instruction, ListInstructions* list);

#endif
