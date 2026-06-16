#include <mempool.h>

#define BLOCK_SIZE 64

mem_pool_t *global_pool = NULL;

int mem_pool_init(size_t poolSize) {
    global_pool = malloc(sizeof(mem_pool_t));
    if (!global_pool == NULL) {
        return -1;
    }
    global_pool->pool = malloc(poolSize);
    if (!global_pool->pool) {
        return -1;
    }
    global_pool->pool_size = poolSize;
    global_pool->used_blocks_count = 0;
    TAILQ_INIT(&global_pool->free_blocks);

    return 0;
}

int mem_pool_destroy() {
    if (global_pool->pool) {
        free(global_pool->pool);
        global_pool->pool = NULL;
    }
    return 0;
}

mem_block_t *
mem_block_alloc() {
    mem_block_t *mem_block_node = malloc(sizeof(mem_block_t));
    if (!mem_block_node) {
        return NULL;
    }
    mem_block_node->ptr = NULL;
    TAILQ_INSERT_HEAD(&global_pool->free_blocks, mem_block_node, link);
    return mem_block_node;
}

int mem_pool_free (void *ptr) {
    if (global_pool->used_blocks_count == 0) {
        printf("No blocks to free.\n");
        return -1;
    }
    if (global_pool->used_all_blocks) {
        mem_block_t *mem_block_node = mem_block_alloc();
        if (!mem_block_node) {
            printf("Failed to allocate memory for free block node.\n");
            return -1;
        }
        mem_block_node->ptr = ptr;
    }

    return 0;
}
int *
mem_pool_alloc_from_freed_blocks

int* mem_pool_alloc() {
    if (!global_pool->pool) {
        return NULL;
    }

    if(global_pool->used_all_blocks) {
        printf("All blocks were allocated. Checking for freed blocks\n");
        return mem_pool_alloc_from_freed_blocks();
    }

    if (global_pool->used_blocks_count * BLOCK_SIZE >= global_pool->pool_size) {
        global_pool->used_all_blocks = 1;
        printf("Not enough space in memory pool.\n");
        return NULL;
    }
    int* block = (int*)(global_pool->pool + (global_pool->used_blocks_count * BLOCK_SIZE));
    global_pool->used_blocks_count++;
    return block;
}