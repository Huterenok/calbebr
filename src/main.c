#include "main.h"

int main() {
  printf("Enter your math expression: ");

  char* expr = receiveExpression();
  Vec* tokens = parse(expr);
  Vec* configuredExpr = createExpression(tokens);

  double res = eval(configuredExpr);

  printf("Result of math expression - %f\n", res);

  freeVec(tokens);
  freeVec(configuredExpr);
  free(expr);

  return 0;
}