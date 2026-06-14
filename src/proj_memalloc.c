#include <proj_memalloc.h>

int main() {
    // Initialize memory pool with 1024 bytes
    memPoolInit(1024);

    // Allocate memory for an integer
    int* num = (int*)memPoolAlloc(sizeof(int));
    if (num) {
        *num = 42;
        printf("Allocated number: %d\n", *num);
        memPoolFree(num);
    } else {
        printf("Memory allocation failed.\n");
    }

    // Destroy the memory pool
    memPoolDestroy();
    return 0;
}