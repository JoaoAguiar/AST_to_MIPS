#include <stdio.h>
#include "parser.h"
#include "stack.h"
#include "mips.h"
#include <string.h>

VarList* var_list = NULL;

// Indices para MIPS
int index_mips = 0;

void mips(ListInstructions* list) {
  FILE* file = fopen("mips.asm", "w");
  int nTab = 6;

  if(file == NULL) {
    printf("Error opening file!\n");

    exit(1);
  }

  fprintf(file, ".text\n");
  fprintf(file, "main:\n");

  while(list != NULL) {
    mips_code(list->head, nTab, file);
    list = list->tail;
  }

  for(int i=0; i<nTab; i++) {
    fprintf(file, " ");
  }

  fprintf(file, "li $v0, 10\n");

  for(int i=0; i<nTab; i++) {
    fprintf(file, " ");
  }

  fprintf(file, "syscall\n");
}

// Faz print de instruções
void mips_code(Instructions* instruction, int nTab, FILE* file) {
  if(instruction->kind == instructionsDECLARE) {
    char* var = instruction->attribute.declare_var.var_name;

    if(check_variable(var) == 0) {
      var_list = put_variable(var, var_list);
    }
  }
  else if(instruction->kind == instructionsATTRIBUTE) {
    char* var = instruction->attribute.attribute_var.var_name;

    if(check_variable(var) == 0) {
      printf("Variable '%c' not declared!\n\n\n", *var);

      exit(-1);
    }

    ListInstructions* expression = instruction->attribute.var_init.list_expression;

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "addi $sp, $sp, -4\n");

    mips_expressions(expression, nTab, file);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a1, $t1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1, %s\n", var);
  }
  else if(instruction->kind == instructionsATTRIBUTE_2) {
    char* var = instruction->attribute.attribute_vars.var_name2;

    if(check_variable(var) == 0) {
      printf("Variable '%c' not declared!\n\n\n", *var);

      exit(-1);
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "addi $sp, $sp, -4\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "lw $a1, %s\n", var);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1, %s\n", instruction->attribute.attribute_vars.var_name1);
  }
  else if(instruction->kind == instructionsINIT) {
    char* var = instruction->attribute.var_init.var_name;

    if(check_variable(var) == 0) {
      var_list = put_variable(var, var_list);
    }

    ListInstructions* expression = instruction->attribute.var_init.list_expression;

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "addi $sp, $sp, -4\n");

    mips_expressions(expression, nTab, file);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a1, $t1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1, %s\n", var);
  }
  else if(instruction->kind == instructionsINIT_2) {
    char* var = instruction->attribute.vars_init.var_name1;

    if(check_variable(var) == 0) {
      var_list = put_variable(var, var_list);
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "lw $a1, %s\n", instruction->attribute.vars_init.var_name2);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "addi $sp, $sp, -4\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1, %s\n", var);
  }
  else if(instruction->kind == instructionsSCAN) {
    char* var = instruction->attribute.scan_function.var_name;

    if(check_variable(var) == 0) {
      printf("Variable '%c' not declared!\n\n\n", *var);

      exit(-1);
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "li $v0, 5\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "syscall\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a1, $v0\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1 %s\n", var);
  }
  else if(instruction->kind == instructionsPRINT) {
    ListInstructions* expression = instruction->attribute.print_function.list_expression;

    mips_expressions(expression, nTab, file);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a0, $t1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "syscall\n");
  }
  else if(instruction->kind == instructionsPRINT_VAR) {
    char* var = instruction->attribute.print_var.var_name;

    if(check_variable(var) == 0) {
      printf("Variable '%c' not declared!\n\n\n", *var);

      exit(-1);
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "lw $a1, %s\n", var);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "li $v0, 1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a0, $a1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "syscall\n");
  }
  else if(instruction->kind == instructionsIF) {
    ListInstructions* expression = instruction->attribute.if_function.expression;
    ListInstructions* list = instruction->attribute.if_function.list;

    index_mips += 1;

    mips_expressions(expression, nTab, file);

    while(list != NULL) {
      mips_code(list->head, nTab, file);
      list = list->tail;
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "j L%d\n", index_mips);
    fprintf(file, "L%d:\n", index_mips);
  }
  else if(instruction->kind == instructionsIF_ELSE) {
    ListInstructions* expression = instruction->attribute.if_else_function.expression;
    ListInstructions* if_list = instruction->attribute.if_else_function.list_if;
    ListInstructions* else_list = instruction->attribute.if_else_function.list_else;

    index_mips += 1;

    mips_expressions(expression, nTab, file);

    index_mips += 1;

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "j L%d\n", index_mips);
    fprintf(file, "L%d:\n", index_mips-1);

    while(if_list != NULL) {
      mips_code(if_list->head, nTab, file);
      if_list = if_list->tail;
    }

    fprintf(file, "L%d:\n", index_mips);

    while(else_list != NULL) {
      mips_code(else_list->head, nTab, file);
      else_list = else_list->tail;
    }
  }
  else if(instruction->kind == instructionsWHILE) {
    ListInstructions* expression = instruction->attribute.while_function.expression;
    ListInstructions* list = instruction->attribute.while_function.list;

    index_mips += 1;

    fprintf(file, "L%d:\n", index_mips);

    index_mips += 1;

    mips_expressions(expression, nTab, file);

    while(list != NULL) {
      mips_code(list->head, nTab, file);
      list = list->tail;
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "j L%d\n", index_mips-1);
    fprintf(file, "L%d:\n", index_mips);
  }
  else if(instruction->kind == instructionsFOR) {
    char* var = instruction->attribute.for_function.var_name;

    if(check_variable(var) == 0) {
      printf("Variable '%c' not declared!\n\n\n", *var);

      exit(-1);
    }

    ListInstructions* expression = instruction->attribute.for_function.expression1;

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "addi $sp, $sp, -4\n");

    mips_expressions(expression, nTab, file);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "move $a1, $t1\n");

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "sw $a1, %s\n", var);

    ListInstructions* expression1 = instruction->attribute.for_function.expression2;
    ListInstructions* list = instruction->attribute.for_function.list;

    index_mips += 1;

    fprintf(file, "L%d:\n", index_mips);

    index_mips += 1;

    mips_expressions(expression1, nTab, file);

    while(list != NULL) {
      mips_code(list->head, nTab, file);
      list = list->tail;
    }

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    ListInstructions* expression2 = instruction->attribute.for_function.expression3;

    mips_expressions(expression2, nTab, file);

    for(int i=0; i<nTab; i++) {
      fprintf(file, " ");
    }

    fprintf(file, "j L%d\n", index_mips-1);
    fprintf(file, "L%d:\n", index_mips);
  }
  else if(instruction->kind == instructionsBREAK) {
    fprintf(file, "j L%d:\n", index_mips);
  }
  else if(instruction->kind == instructionsCONTINUE) {
    printf(":)\n");
  }
}

// Faz print do tipo de instruções
void mips_expressions(ListInstructions* expression, int nTab, FILE* file) {
  if(expression == 0) {
    yyerror("Null expression!!");
  }
  else {
    Instructions* instruction = expression->head;

    if(instruction->kind == instructionsINTEGER) {
      for(int i=0; i<nTab; i++) {
        fprintf(file, " ");
      }

      fprintf(file, "li $t1, %d\n", instruction->attribute.value);
    }
    else if(instruction->kind == instructionsOPERATION) {
      ListInstructions* expression_left = instruction->attribute.instruction_operator.expression_left;
      ListInstructions* expression_right = instruction->attribute.instruction_operator.expression_right;

      mips_expressions(expression_left, nTab, file);

      for(int i=0; i<nTab; i++) {
        fprintf(file, " ");
      }

      fprintf(file, "move $t2, $t1\n");

      mips_expressions(expression_right, nTab, file);

      for(int i=0; i<nTab; i++) {
        fprintf(file, " ");
      }

      fprintf(file, "move $t3, $t1\n");

      switch(instruction->attribute.instruction_operator.operator) {
        case PLUS: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "add $t1, $t2, $t3\n");
        } break;
        case MULT: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "mult $t1, $t2, $t3\n");
        } break;
        case MINUS: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "sub $t1, $t2, $t3\n");
        } break;
        case DIV: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "div $t1, $t2, $t3\n");
        } break;
        case MOD: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "div $t1, $t2, $t3\n");
          fprintf(file, "mult $t5, $t4, $t1\n");
          fprintf(file, "sub $t7, $t6, $t5\n");
        } break;
      }
    }
    else if(instruction->kind == instructionsBOOLEAN) {
      ListInstructions* expression_left = instruction->attribute.boolean.expression_left;
      ListInstructions* expression_right = instruction->attribute.boolean.expression_right;

      mips_expressions(expression_left, nTab, file);

      for(int i=0; i<nTab; i++) {
        fprintf(file, " ");
      }

      fprintf(file, "move $t2, $t1\n");

      mips_expressions(expression_right, nTab, file);

      for(int i=0; i<nTab; i++) {
        fprintf(file, " ");
      }

      fprintf(file, "move $t3, $t1\n");

      switch(instruction->attribute.boolean.operator) {
        case EQUAL: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "bne $t2, $t3, L%d\n", index_mips);
        } break;
        case DIFF: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "beq $t2, $t3, L%d\n", index_mips);
        } break;
        case LT: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "bgt $t2, $t3, L%d\n", index_mips);
        } break;
        case GT: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "blt $t2, $t3, L%d\n", index_mips);
        } break;
        case LTEQ: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "bge $t2, $t3, L%d\n", index_mips);
        } break;
        case GTEQ: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "ble $t2, $t3, L%d\n", index_mips);
        } break;
        case AND: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "and $t1, $t2, $t3\n");

          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "beq $t1, $zero, L%d\n", index_mips);
        } break;
        case OR: {
          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "or $t1, $t2, $t3\n");

          for(int i=0; i<nTab; i++) {
            fprintf(file, " ");
          }

          fprintf(file, "beq $t1, $zero, L%d\n", index_mips);
        } break;
      }
    }
  }
}

// Verifica se a variavel ja existe na lista de variaveis
int check_variable(char* var) {
  VarList* list = var_list;

  while(list != NULL) {
    char* var_aux = list->var_name;

    if(strcmp(var, var_aux) == 0) {
      return 1;
    }

    list = list->tail;
  }

  return 0;
}

// Adiciona uma variavel na lista de variaveis
VarList* put_variable(char* var, VarList* list) {
  VarList* node = (VarList*)malloc(sizeof(VarList));

  node->var_name = var;
  node->tail = list;

  return node;
}
