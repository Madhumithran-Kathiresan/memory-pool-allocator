#include <mempool.h>

#define BLOCK_SIZE 64

mem_pool_t *global_pool = NULL;

int
mem_pool_initialize_free_blocks() {
    uint32_t i;
    char *pool;
    pool = (char *)global_pool->pool;
    global_pool->free_blocks = (void **)global_pool->pool;
    for (i = 1; i < global_pool->blocks_count; i++) {
        /**
         * each block's address has to be stored in the previous block's memory
         */
        void **prev_block_holder = (void **)&pool[(i-1)*BLOCK_SIZE];
        *prev_block_holder = (void *)&pool[i*BLOCK_SIZE];
    }
    void **last_block = (void **)&pool[i*BLOCK_SIZE];
    *last_block = NULL;

    return 0;
}

void
print_mem_blocks() {
    printf("Pointer to free_list: %p\n", global_pool->free_blocks);
    for (uint32_t i=0; i<global_pool->blocks_count ; i++) {
        char *pool = (char *)global_pool->pool;
        void **block_holder = (void **)&pool[i*BLOCK_SIZE];
        printf("------------------------------------------------\n");
        printf("Block[%d]\t==>\t|Address: %p\t|Value: %p\t|\n"
                     ,i+1, block_holder, *block_holder);
    }
    printf("------------------------------------------------\n");
    return;
}

int
mem_pool_init(size_t pool_size) {
    global_pool = malloc(sizeof(mem_pool_t));
    if (global_pool == NULL) {
        return -1;
    }
    global_pool->pool = malloc(pool_size);
    if (!global_pool->pool) {
        return -1;
    }
    global_pool->pool_size = pool_size;
    global_pool->used_blocks_count = 0;
    global_pool->blocks_count = pool_size / BLOCK_SIZE;
    global_pool->free_blocks = NULL;

    mem_pool_initialize_free_blocks();
    print_mem_blocks();

    return 0;
}

/**
 * API to check whether the memory lies within the mem_pool
 */
uint8_t
is_ptr_in_mem_pool() {
    return 0;
}

int
mem_pool_destroy() {
    if (global_pool->pool) {
        free(global_pool->pool);
        global_pool->pool = NULL;
    }
    return 0;
}

int
mem_pool_free (void *ptr) {
    /* Store the current free_block address inside the incoming ptr for freeing */
    void **incoming_block = ptr;
    // memset(*incoming_block, 0, BLOCK_SIZE);
    *incoming_block = global_pool->free_blocks;
    global_pool->free_blocks = incoming_block;
    global_pool->used_blocks_count--;

    return 0;
}

void*
mem_pool_alloc() {
    if (!global_pool->pool) {
        return NULL;
    }

    if (global_pool->used_blocks_count >= global_pool->blocks_count) {
        printf("Error!! No Free blocks!\n");
        return NULL;
    }

    void **address_of_block_to_return = global_pool->free_blocks; /* Address of the 1st free block */
    void **next_free_block_address = *address_of_block_to_return; /* storing the address of next free block */
    /* point the next_free_block_address to global free_block */
    global_pool->free_blocks = next_free_block_address;

    *address_of_block_to_return = NULL; /* Clear the value in the mem_block */
    print_mem_blocks();

    global_pool->used_blocks_count++;

    return (void *)address_of_block_to_return;
}

void hex_dump_pool()
{
    const uint8_t *ptr = (const uint8_t *)global_pool->pool;
    size_t max_bytes = 1024;
    size_t bytes_per_line = 64;

    for (size_t i = 0; i < max_bytes; i++) {

        /* Start of a new line */
        if (i % bytes_per_line == 0) {
            printf("%04zx: ", i);
        }

        printf("%02x ", ptr[i]);

        /* End of line */
        if ((i + 1) % bytes_per_line == 0) {
            printf("\n");
        }
    }

    /* Handle partial last line */
    if (max_bytes % bytes_per_line != 0) {
        printf("\n");
    }
}