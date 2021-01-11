#include <stdio.h>
#include "parser.h"
#include "mips.h"

int main(int argc, char* argv[]) {
  argc--;
  argv++;

  if(argc != 0) {
    // yyin é uma variavel to tipo FILE* que aponta para o ficheiro input que vai ser scanned ou tokenised
    // yyin é definido automaticamente pelo LEX (ferramenta usada para gerar uma analizador lexical)
    yyin = fopen(*argv, "r");

    if(yyin == NULL) {
      printf("'%s': could not open file\n", *argv);

      return 1;
    }
  }

  // yyparse() é: 0 se o parsing correr bem de acordo com as regras da gramatica, 1 se houver uma falhar no parsing por causa de um input invalido ou 2 se falhar o parsing devido a exaustão da memoria
  if(yyparse() == 0) {
    ListInstructions* list = root;

    mips(list);
  }

  return 0;
}
