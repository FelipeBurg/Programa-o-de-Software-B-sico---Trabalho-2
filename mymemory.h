<<<<<<< HEAD
=======

>>>>>>> 14c1a05 (Add: achiviements by Lucas)
#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h>

typedef struct allocation {
    void *start;
    size_t size;
    struct allocation *next;
} allocation_t;

typedef struct {
<<<<<<< HEAD
    void *pool; // ponteiro para o bloco de memória real
=======
    void *pool;
>>>>>>> 14c1a05 (Add: achiviements by Lucas)
    size_t total_size;
    allocation_t *head;
} mymemory_t;

mymemory_t* mymemory_init(size_t size);
void* mymemory_alloc(mymemory_t *memory, size_t size);
void mymemory_free(mymemory_t *memory, void *ptr);
void mymemory_display(mymemory_t *memory);
void mymemory_stats(mymemory_t *memory);
void mymemory_cleanup(mymemory_t *memory);

<<<<<<< HEAD
#endif /* MYMEMORY_H */
=======
#define mymemory_malloc mymemory_alloc
#define mymemory_release mymemory_cleanup

#endif /* MYMEMORY_H */
>>>>>>> 14c1a05 (Add: achiviements by Lucas)
