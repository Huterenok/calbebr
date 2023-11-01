#include "utils.h"

#define INITIAL_VEC_SIZE 16

void initVec(Vec** vecPtr, size_t elementSize) {
  Vec* vec = malloc(sizeof(Vec));
  if (!vec) {
    printf("Error while memory allocation\n");
    exit(1);
  }

  vec->inner = (void**)malloc(INITIAL_VEC_SIZE * sizeof(void*));
  vec->size = 0;
  vec->capacity = INITIAL_VEC_SIZE;
  vec->elementSize = elementSize;
  if (!vec->inner) {
    printf("Error while memory allocation\n");
    exit(1);
  }

  *vecPtr = vec;
}

void pushVec(Vec* vecPtr, void* src) {
  if (vecPtr->size == vecPtr->capacity) {
    vecPtr->capacity *= 2;
    vecPtr->inner =
        (void**)realloc(vecPtr->inner, vecPtr->capacity * sizeof(void*));
    if (!vecPtr->inner) {
      printf("Error while memory allocation\n");
      exit(1);
    }
  }
  void* container = (void*)malloc(vecPtr->elementSize);
  memcpy(container, src, vecPtr->elementSize);
  vecPtr->inner[vecPtr->size++] = container;
}

void* popVec(Vec* vecPtr) {
  if (vecPtr->size == 0) {
    return NULL;
  }
  return vecPtr->inner[--vecPtr->size];
}

void* getVec(Vec* vecPtr, size_t idx) {
  if (vecPtr->size <= idx) {
    return NULL;
  }
  return vecPtr->inner[idx];
}

void setVec(Vec* vecPtr, void* item, size_t idx) {
  if (vecPtr->size <= idx) {
    printf("Vec index out of bounds\n");
    exit(1);
  }
  memcpy(vecPtr->inner[idx], item, vecPtr->elementSize);
}

void* getLastVec(Vec* vecPtr) {
  if (vecPtr->size == 0) {
    return NULL;
  }
  return vecPtr->inner[vecPtr->size - 1];
}

void reverseVec(Vec* vecPtr) {
  for (int i = 0; i < vecPtr->size / 2; i++) {
    void* temp = vecPtr->inner[i];
    vecPtr->inner[i] = vecPtr->inner[vecPtr->size - i - 1];
    vecPtr->inner[vecPtr->size - i - 1] = temp;
  }
}

void printVec(Vec* vecPtr, void (*printFn)(void*, void*), void* arg) {
  for (int i = 0; i < vecPtr->size; i++) {
    printFn(getVec(vecPtr, i), arg);
  }
}

void freeVec(Vec* vecPtr) {
  for (int i = 0; i < vecPtr->size; i++) {
    free(vecPtr->inner[i]);
  }
  free(vecPtr->inner);
  free(vecPtr);
}