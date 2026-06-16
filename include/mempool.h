#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdint.h>
#ifndef MEMALLOC_H
#define MEMALLOC_H

int* mem_pool_alloc();
int mem_pool_free(void* ptr);
int mem_pool_init(size_t poolSize);
int mem_pool_destroy();

typedef struct mem_block_s {
    void *ptr;
    TAILQ_ENTRY(mem_block_s) link;
} mem_block_t;

typedef struct mem_pool_s {
    void        *pool;
    size_t      pool_size;
    uint8_t     used_all_blocks:1;
    int         used_blocks_count;
    TAILQ_HEAD(mem_free_block_list, mem_block_s) free_blocks;
} mem_pool_t;
#endif // MEMALLOC_H
