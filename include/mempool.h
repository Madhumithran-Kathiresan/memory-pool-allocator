#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdint.h>
#include <string.h>

#ifndef MEMALLOC_H
#define MEMALLOC_H

#if 0
typedef struct mem_block_s {
    void *ptr;
    STAILQ_ENTRY(mem_block_s) link;
} mem_block_t;
#endif

typedef struct mem_pool_s {
    void        *pool;
    size_t      pool_size;
    uint32_t    blocks_count;
    uint32_t    used_blocks_count;
    void        **free_blocks; /* Store pointers to free blocks */
} mem_pool_t;

void*
mem_pool_alloc();

int mem_pool_free(void* ptr);
int mem_pool_init(size_t poolSize);
int mem_pool_destroy();
void hex_dump_pool();

void
print_mem_blocks();

#endif // MEMALLOC_H
