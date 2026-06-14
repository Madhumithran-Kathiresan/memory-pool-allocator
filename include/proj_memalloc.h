#include <stdio.h>
#include <stdlib.h>
#ifndef PROJ_MEMALLOC_H
#define PROJ_MEMALLOC_H

int* memPoolAlloc();
void memPoolFree(void* ptr);
int memPoolInit(size_t poolSize);
int memPoolDestroy();

#endif // PROJ_MEMALLOC_H
