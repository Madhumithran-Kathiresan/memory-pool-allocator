#include <proj_memalloc.h>

#define BLOCK_SIZE 64 // Define a block size for memory allocation

void *memPool = NULL; // Pointer to the memory pool
int memPoolUsageCounter = 0; // Counter to track memory usage
int memPoolSize = 0; // Size of the memory pool

int memPoolInit(size_t poolSize) {
    memPool = malloc(poolSize);
    memPoolSize = poolSize;
    if (!memPool) {
        return -1; // Return -1 on failure
    }
    return 0; // Return 0 on success
}

int memPoolDestroy() {
    // Destroy the memory pool
    // Implementation details would go here
    if (memPool) {
        free(memPool);
        memPool = NULL;
    }
    return 0; // Return 0 on success
}

int* memPoolAlloc() {
    // Allocate memory from the pool
    // Implementation details would go here
    if (!memPool) {
        return NULL; // Return NULL if the pool is not initialized
    }
    if (memPoolUsageCounter * BLOCK_SIZE >= memPoolSize) {
        printf("Not enough space in memory pool.\n");
        return NULL; // Return NULL if there is not enough space
    }
    int* block = (int*)(memPool + (memPoolUsageCounter * BLOCK_SIZE)); // Placeholder for actual allocation logic
    memPoolUsageCounter++; // Increment usage counter
    return block;
}

int main() {
    // Initialize memory pool with 1024 bytes
    int result = memPoolInit(1024);
    if (result != 0) {
        printf("Failed to initialize memory pool.\n");
        return 1;
    }

    printf("Enter the number of memory blocks to allocate: ");
    int numBlocks;
    scanf("%d", &numBlocks);

    for(int i = 0; i < numBlocks; i++) {
        int* block = memPoolAlloc();
        if (block) {
            *block = i + 1; // Assign a value to the allocated block
            printf("Allocated block %d at address: %p\n", *block, block);
        } else {
            printf("Memory allocation failed for block %d.\n", i + 1);
            break;
        }
    }

    // Destroy the memory pool
    memPoolDestroy();
    return 0;
}