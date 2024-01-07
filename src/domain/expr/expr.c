#include "expr.h"

int getOpPriority(Operator op) {
  switch (op) {
  case ADD:
  case SUB:
    return 1;
  case MUL:
  case DIV:
    return 2;
  case EXP:
    return 3;
  default:
    return 0;
  }
}

Vec* createExpression(Vec* tokens) {
  Vec* queue;
  Vec* stack;
  initVec(&queue);
  initVec(&stack);

  Token* popped = popVec(tokens);
  while (popped != NULL) {
    switch (popped->type) {
    case NUM:
      pushVec(queue, popped);
      break;

    case OP:
      while (stack->size != 0 &&
             getOpPriority(((Token*)getLastVec(stack))->value.op) >
                 getOpPriority(popped->value.op)) {
        Token* poppedStack = popVec(stack);
        if (poppedStack->type == OP) {
          pushVec(queue, poppedStack);
        }
      }
      pushVec(stack, popped);
      break;

    case BRACKET:
      if (popped->value.bracket == OPEN) {
        pushVec(stack, popped);
      } else {
        while (stack->size != 0 &&
               ((Token*)getLastVec(stack))->value.bracket != OPEN) {
          Token* poppedStack = popVec(stack);
          if (poppedStack->type == OP) {
            pushVec(queue, poppedStack);
          }
        }
        popVec(stack);
      }
      break;
    }
    popped = popVec(tokens);
  }

  while (stack->size != 0) {
    Token* poppedStack = popVec(stack);
    pushVec(queue, poppedStack);
  }

  freeVec(stack);

  return queue;
}