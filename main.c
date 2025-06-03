#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

#define MAX_PTRS 100

int main() {
    int option;
    size_t size;
    void *ptrs[MAX_PTRS] = {NULL};
    int ptr_count = 0;

    size_t mem_size;
    printf("Informe o tamanho da memória a ser inicializada: ");
    scanf("%zu", &mem_size);

    mymemory_t *memory = mymemory_init(mem_size);
    if (!memory) {
        printf("Erro ao inicializar a memória.\n");
        return 1;
    }

    do {
        printf("\n====== MENU ======\n");
        printf("1. Alocar memória\n");
        printf("2. Liberar memória\n");
        printf("3. Exibir memória\n");
        printf("4. Mostrar estatísticas\n");
        printf("5. Encerrar e liberar tudo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (ptr_count >= MAX_PTRS) {
                    printf("Limite de alocações atingido.\n");
                    break;
                }
                printf("Informe o tamanho a alocar (em bytes): ");
                scanf("%zu", &size);
                ptrs[ptr_count] = mymemory_alloc(memory, size);
                if (ptrs[ptr_count]) {
                    printf("Memória alocada no índice %d: %p\n", ptr_count, ptrs[ptr_count]);
                    ptr_count++;
                } else {
                    printf("Falha na alocação.\n");
                }
                break;

            case 2:
                printf("Informe o índice do ponteiro a liberar (0 a %d): ", ptr_count - 1);
                int index;
                scanf("%d", &index);
                if (index >= 0 && index < ptr_count && ptrs[index] != NULL) {
                    mymemory_free(memory, ptrs[index]);
                    printf("Memória no índice %d liberada.\n", index);
                    ptrs[index] = NULL;
                } else {
                    printf("Índice inválido ou ponteiro já liberado.\n");
                }
                break;

            case 3:
                mymemory_display(memory);
                break;

            case 4:
                mymemory_stats(memory);
                break;

            case 5:
                mymemory_cleanup(memory);
                printf("Memória liberada e programa encerrado.\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (option != 5);

    return 0;
}
