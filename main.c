
#include <stdio.h>
#include "mymemory.h"

int main() {
    mymemory_t *memory = mymemory_init(1000);
    int *v = mymemory_malloc(memory, sizeof(int) * 32);
    for (int i = 0; i < 32; i++) v[i] = i + 1;
    int *v2 = mymemory_malloc(memory, sizeof(int) * 16);
    mymemory_free(memory, v);
    char *str = mymemory_malloc(memory, sizeof(char) * 16);
    sprintf(str, "ola mundo");
    printf("%s\n", str);
    mymemory_display(memory);
    mymemory_stats(memory);
    mymemory_release(memory);
    return 0;
}
