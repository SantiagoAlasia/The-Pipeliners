#include <stdint.h>
#include <stdio.h>

int procesar_gini_asm(float valor);

int procesar_gini(float valor) {
    printf("\n>>> Llamando a ASM\n");
    fflush(stdout);

    return procesar_gini_asm(valor);
}
