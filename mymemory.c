
#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

mymemory_t* mymemory_init(size_t size) {
    mymemory_t *memory = (mymemory_t*) malloc(sizeof(mymemory_t));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size) {
    char *pool = (char*) memory->pool;
    size_t offset = 0;
    allocation_t *curr = memory->head;
    allocation_t *prev = NULL;
    while (curr) {
        size_t gap = (size_t)((char*)curr->start - (pool + offset));
        if (gap >= size) break;
        offset = (size_t)((char*)curr->start - pool) + curr->size;
        prev = curr;
        curr = curr->next;
    }
    if (memory->total_size - offset < size) return NULL;
    void *ptr = pool + offset;
    allocation_t *new_alloc = (allocation_t*) malloc(sizeof(allocation_t));
    new_alloc->start = ptr;
    new_alloc->size = size;
    new_alloc->next = curr;
    if (prev) {
        prev->next = new_alloc;
    } else {
        memory->head = new_alloc;
    }
    return ptr;
}

void mymemory_free(mymemory_t *memory, void *ptr) {
    allocation_t *curr = memory->head;
    allocation_t *prev = NULL;
    while (curr) {
        if (curr->start == ptr) {
            if (prev) prev->next = curr->next;
            else memory->head = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void mymemory_display(mymemory_t *memory) {
    allocation_t *curr = memory->head;
    printf("Alocações ativas:\n");
    while (curr) {
        printf("Início: %p, Tamanho: %zu bytes\n", curr->start, curr->size);
        curr = curr->next;
    }
}

void mymemory_stats(mymemory_t *memory) {
    allocation_t *curr = memory->head;
    size_t used = 0, largest_free = 0, free_fragments = 0, offset = 0, alloc_count = 0;
    char *pool = (char*) memory->pool;
    while (curr) {
        alloc_count++;
        size_t gap = (size_t)((char*)curr->start - (pool + offset));
        if (gap > 0) {
            free_fragments++;
            if (gap > largest_free) largest_free = gap;
        }
        used += curr->size;
        offset = (size_t)((char*)curr->start - pool) + curr->size;
        curr = curr->next;
    }
    size_t final_gap = memory->total_size - offset;
    if (final_gap > 0) {
        free_fragments++;
        if (final_gap > largest_free) largest_free = final_gap;
    }
    printf("Total de alocações: %zu\n", alloc_count);
    printf("Memória alocada: %zu bytes\n", used);
    printf("Memória livre: %zu bytes\n", memory->total_size - used);
    printf("Maior bloco livre: %zu bytes\n", largest_free);
    printf("Fragmentos livres: %zu\n", free_fragments);
}

void mymemory_cleanup(mymemory_t *memory) {
    allocation_t *curr = memory->head;
    while (curr) {
        allocation_t *next = curr->next;
        free(curr);
        curr = next;
    }
    free(memory->pool);
    free(memory);
}
