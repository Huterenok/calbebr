#include "parser.h"

Vec* parse(char* expr) {
  Vec* tokens;
  initVec(&tokens, TOKEN_SIZE);

  Vec* bracketVec;

  initVec(&bracketVec, BRACKET_SIZE);

  for (int i = 0; i < strlen(expr) - 1; i++) {
    if (isspace(expr[i])) {
      continue;
    }

    Token token;
    switch (expr[i]) {
    case '+':
      token.type = OP;
      token.value.op = ADD;
      break;
    case '-':
      token.type = OP;
      token.value.op = SUB;
      break;
    case '/':
      token.type = OP;
      token.value.op = DIV;
      break;
    case '*':
      token.type = OP;
      token.value.op = MUL;
      break;
    case '^':
      token.type = OP;
      token.value.op = EXP;
      break;
    case '(':
      token.type = BRACKET;
      token.value.bracket = OPEN;

      enum BracketType push = OPEN;
      pushVec(bracketVec, &push);
      break;
    case ')':
      token.type = BRACKET;
      token.value.bracket = CLOSE;

      BracketType* popped = (BracketType*)popVec(bracketVec);
      if (popped == NULL || *popped != OPEN) {
        puts("Wrong ')' bracket order");
        exit(1);
      }

      break;
    default:
      if (isdigit(expr[i])) {
        int num = i;
        bool isFloating = false;
        while (isdigit(expr[i + 1]) || expr[i + 1] == '.') {
          if (expr[i + 1] == '.' && isFloating) {
            puts("Wrong floating-point number format");
            exit(1);
          } else {
            isFloating = true;
          }
          i++;
        }
        token.type = NUM;
        token.value.num = atof(&expr[num]);
      } else {
        printf("Unexpected element: '%c'\n", expr[i]);
        exit(1);
      }

      break;
    }

    pushVec(tokens, &token);
  }

  if (bracketVec->size != 0) {
    puts("Wrong bracket order");
    exit(1);
  }

  freeVec(bracketVec);
  return tokens;
}

char opToChar(Token* token) {
  switch (token->value.op) {
  case ADD:
    return '+';
  case SUB:
    return '-';
  case MUL:
    return '*';
  case DIV:
    return '/';
  case EXP:
    return '^';
  }
}

void printTokens(Vec* tokens) {
  for (int i = 0; i < tokens->size; i++) {
    Token* token = (Token*)getVec(tokens, i);
    switch (token->type) {
    case OP:
      printf("type - OP, type - %c\n", opToChar(token));
      break;
    case NUM:
      printf("type - NUM, value - %f\n", token->value.num);
      break;
    case BRACKET:
      printf("type - BRACKET, type - %c\n",
             token->value.bracket == OPEN ? '(' : ')');
    }
  }
}
