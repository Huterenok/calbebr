#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* receiveExpression();
void removeTrailingZeros(char* str);

typedef struct {
  void** inner;
  size_t size;
  size_t capacity;
} Vec;

void initVec(Vec** vecPtr);
void pushVec(Vec* vecPtr, void* src);
void* popVec(Vec* vecPtr);
void* getVec(Vec* vecPtr, size_t idx);
void setVec(Vec* vecPtr, void* item, size_t idx);
void* getLastVec(Vec* vecPtr);
void reverseVec(Vec* vecPtr);
void freeVec(Vec* vecPtr);
void printVec(Vec* vecPtr, void (*printFn)(void*, void*), void* arg);

#endif // UTILS_H