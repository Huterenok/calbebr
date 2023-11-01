#include "expr.h"

Vec* createExpression(Vec* tokens) {
  Vec* queue;
  Vec* stack;
  initVec(&queue, TOKEN_SIZE);
  initVec(&stack, TOKEN_SIZE);

  Token* popped = popVec(tokens);
  while (popped != NULL) {
    switch (popped->type) {
    case NUM:
      pushVec(queue, popped);
      break;

    case OP:
      while (stack->size != 0 && (Token*)getLastVec(stack) != NULL &&
             ((Token*)getLastVec(stack))->type >= popped->type) {
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
        while (stack->size != 0 && (Token*)getLastVec(stack) != NULL &&
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
