#ifndef DOMAIN_H
#define DOMAIN_H

#include "../utils/utils.h"
#include <math.h>
#include <ctype.h>

enum Operator { ADD, SUB, MUL, DIV, EXP };

enum TokenType { OP, NUM, BRACKET };

typedef enum BracketType { CLOSE, OPEN } BracketType;

typedef struct {
  enum TokenType type;
  union {
    enum Operator op;
     double num;
    enum BracketType bracket;
  } value;
} Token;

#define TOKEN_SIZE sizeof(Token)
#define BRACKET_SIZE sizeof(enum BracketType)

#endif //DOMAIN_H