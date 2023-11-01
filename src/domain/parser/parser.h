#ifndef PARSER_H
#define PARSER_H

#include "../domain.h"

Vec* parse(char* expr);
void printTokens(Vec* tokens);
char opToChar(Token* token);

#endif //PARSER_H
