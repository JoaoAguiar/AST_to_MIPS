#include <stdlib.h>
#include "stack.h"

Instructions* stack_Integer(int value) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsINTEGER;
  node->attribute.value = value;

  return node;
}
Instructions* stack_Operation(int operator, ListInstructions* left, ListInstructions* right) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsOPERATION;
  node->attribute.instruction_operator.operator = operator;
  node->attribute.instruction_operator.expression_left = left;
  node->attribute.instruction_operator.expression_right = right;

  return node;
}
Instructions* stack_BooleanOperation(int operator, ListInstructions* left, ListInstructions* right) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsBOOLEAN;
  node->attribute.boolean.operator = operator;
  node->attribute.boolean.expression_left = left;
  node->attribute.boolean.expression_right = right;

  return node;
}
Instructions* stack_DeclareVar(char *var) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsDECLARE;
  node->attribute.declare_var.var_name = var;

  return node;
}
Instructions* stack_VarAttribute(char *var, ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsATTRIBUTE;
  node->attribute.attribute_var.var_name = var;
  node->attribute.attribute_var.expression = list;

  return node;
}
Instructions* stack_VarAttributes(char *var1, char *var2) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsATTRIBUTE_2;
  node->attribute.attribute_vars.var_name1 = var1;
  node->attribute.attribute_vars.var_name2 = var2;

  return node;
}
Instructions* stack_VarInit(char *var, ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsINIT;
  node->attribute.var_init.var_name = var;
  node->attribute.var_init.list_expression = list;

  return node;
}
Instructions* stack_VarsInit(char *var1, char *var2) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsINIT_2;
  node->attribute.vars_init.var_name1 = var1;
  node->attribute.vars_init.var_name2 = var2;

  return node;
}
Instructions* stack_Scan(char *var) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsSCAN;
  node->attribute.scan_function.var_name = var;

  return node;
}
Instructions* stack_PrintVar(char *var) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsPRINT_VAR;
  node->attribute.print_var.var_name = var;

  return node;
}
Instructions* stack_Print(ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsPRINT;
  node->attribute.print_function.list_expression = list;

  return node;
}
Instructions* stack_If(ListInstructions* expression, ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsIF;
  node->attribute.if_function.expression = expression;
  node->attribute.if_function.list = list;

  return node;
}
Instructions* stack_IfElse(ListInstructions* expression, ListInstructions* list1, ListInstructions* list2) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsIF_ELSE;
  node->attribute.if_else_function.expression = expression;
  node->attribute.if_else_function.list_if = list1;
  node->attribute.if_else_function.list_else = list2;

  return node;
}
Instructions* stack_While(ListInstructions* expression, ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsWHILE;
  node->attribute.while_function.expression = expression;
  node->attribute.while_function.list = list;

  return node;
}
Instructions* stack_For(char *var, ListInstructions* expression1, ListInstructions* expression2, ListInstructions* expression3, ListInstructions* list) {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsFOR;
  node->attribute.for_function.var_name = var;
  node->attribute.for_function.expression1 = expression1;
  node->attribute.for_function.expression2 = expression2;
  node->attribute.for_function.expression3 = expression3;
  node->attribute.for_function.list = list;

  return node;
}
Instructions* stack_Break() {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsBREAK;

  return node;
}
Instructions* stack_Continue() {
  Instructions* node = (Instructions*)malloc(sizeof(Instructions));

  node->kind = instructionsCONTINUE;

  return node;
}

// Para adicionar uma instrução á lista de intruções
ListInstructions* addNode(Instructions* instruction, ListInstructions* list) {
  ListInstructions* node = (ListInstructions*)malloc(sizeof(ListInstructions));

  node->head = instruction;
  node->tail = list;

  return node;
}
