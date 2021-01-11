// Definições da Stack
#ifndef __mips_h__
#define __mips_h__

typedef struct _VarList {
  char* var_name;
  struct _VarList* tail;
} VarList;

void mips(ListInstructions* list);
void mips_code(Instructions* instruction, int nTab, FILE* file);
void mips_expressions(ListInstructions* expr, int nTab, FILE* file);
int check_variable(char* var);
VarList* put_variable(char* var, VarList* list);

#endif
