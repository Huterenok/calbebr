#ifndef DOMAIN_H
#define DOMAIN_H

#include "../utils/utils.h"
#include <ctype.h>
#include <math.h>

typedef enum Operator { ADD, SUB, MUL, DIV, EXP } Operator;

typedef enum TokenType { OP, NUM, BRACKET } TokenType;

typedef enum BracketType { CLOSE, OPEN } BracketType;

typedef struct {
  enum TokenType type;
  union {
    Operator op;
    double num;
    BracketType bracket;
  } value;
} Token;

#define TOKEN_SIZE sizeof(Token)
#define BRACKET_SIZE sizeof(enum BracketType)

#endif // DOMAIN_H