#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {

    printf("The memory size is %d\n", memsize());

    // malloc(x): if x < 64KB malloc allocates 64KB.
    char *ptr = malloc(20 * (2^10)); // 1KB = 2^10 bytes

    printf("The MEMORY size after memory allocation is %d\n", memsize());

    free(ptr);

    printf("The memory size after memory allocation freed is %d\n", memsize());
    
    exit(0);
}