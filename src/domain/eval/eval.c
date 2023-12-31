#include "eval.h"
#include <stdio.h>
#include <stdlib.h>

double eval(Vec* tokens) {
  reverseVec(tokens);

  Vec* stack;
  initVec(&stack);

  size_t count = 1;
  Token* popped = popVec(tokens);

  while (popped != NULL) {
    double* res = malloc(sizeof(double));
    double right;
    double left;
    char op;

    switch (popped->type) {
    case NUM:
      pushVec(stack, &popped->value.num);
      break;
    case OP:
      if (stack->size < 2) {
        printf("Error while evaluating expression\n");
        exit(1);
      }

      left = *(double*)popVec(stack);
      right = *(double*)popVec(stack);
      op = opToChar(popped);

      switch (popped->value.op) {
      case ADD:
        *res = left + right;
        break;
      case SUB:
        *res = left - right;
        break;
      case DIV:
        if (right == 0) {
          printf("Division by zero)\n");
          exit(1);
        }
        *res = left / right;
        break;
      case MUL:
        *res = right * left;
        break;
      case EXP:
        *res = pow(left, right);
        break;
      }

      pushVec(stack, res);
      printf("%zu) %f %c %f = %f\n", count, left, op, right, *res);
      count++;

      break;
    case BRACKET:
      break;
    }

    popped = popVec(tokens);
  }

  if (stack->size != 1) {
    printf("Error while evaluating expression\n");
    exit(1);
  }

  double res = *(double*)popVec(stack);
  freeVec(stack);

  return res;
}