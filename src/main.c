#include <mempool.h>
#include <stdlib.h>

int main() {
    int result = mem_pool_init(1024);
    if (result != 0) {
        printf("Failed to initialize memory pool.\n");
        return 1;
    }

    // printf("Enter the number of memory blocks to allocate: ");
    // int numBlocks;
    // scanf("%d", &numBlocks);

    // for(int i = 0; i < numBlocks; i++) {
    //     int* block = mem_pool_alloc();
    //     if (block) {
    //         *block = i + 1;
    //         printf("Allocated block %d at address: %p\n", *block, block);
    //     } else {
    //         printf("Memory allocation failed for block %d.\n", i + 1);
    //         break;
    //     }
    // }

    // hex_dump_pool();
    int *first = mem_pool_alloc();
    printf("-----------After First Allocation-----------\n");
    print_mem_blocks();
    printf("------------------------------------\n");

    int *second = mem_pool_alloc();
    printf("-----------After Second Allocation-----------\n");
    print_mem_blocks();
    printf("------------------------------------\n");

    *second = 100;
    *first = 50;

    printf("-----------***After Updating VALUES***-----------\n");
    print_mem_blocks();
    // hex_dump_pool();
    printf("------------------------------------\n");

    mem_pool_free(first);
    printf("-----------***After Freeing first***-----------\n");
    print_mem_blocks();
    // hex_dump_pool();
    printf("------------------------------------\n");

    printf("-----------***After Freeing second***-----------\n");
    mem_pool_free(second);
    // hex_dump_pool();

    print_mem_blocks();
    printf("------------------------------------\n");



    return 0;
}