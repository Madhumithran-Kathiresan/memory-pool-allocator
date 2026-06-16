#include <mempool.h>
#include <stdlib.h>

int main() {
    int result = mem_pool_init(1024);
    if (result != 0) {
        printf("Failed to initialize memory pool.\n");
        return 1;
    }

    printf("Enter the number of memory blocks to allocate: ");
    int numBlocks;
    scanf("%d", &numBlocks);

    for(int i = 0; i < numBlocks; i++) {
        int* block = mem_pool_alloc();
        if (block) {
            *block = i + 1;
            printf("Allocated block %d at address: %p\n", *block, block);
        } else {
            printf("Memory allocation failed for block %d.\n", i + 1);
            break;
        }
    }

    mem_pool_destroy();
    return 0;
}