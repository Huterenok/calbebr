#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/constants.h"

char* receiveExpression() {
  char* expr;
  expr = (char*)malloc(sizeof(char) * EXPRESSION_LENGTH);
  fgets(expr, EXPRESSION_LENGTH, stdin);

  if (strlen(expr) == 0) {
    puts("You should try to enter something valid\n");
    exit(1);
  }

  return expr;
}