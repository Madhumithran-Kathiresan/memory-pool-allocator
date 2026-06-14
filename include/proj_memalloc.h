#include <stdio.h>
#include <stdlib.h>
#ifndef PROJ_MEMALLOC_H
#define PROJ_MEMALLOC_H

void* memPoolAlloc(size_t size);
void memPoolFree(void* ptr);
void memPoolInit(size_t poolSize);
void memPoolDestroy();

#endif // PROJ_MEMALLOC_H
