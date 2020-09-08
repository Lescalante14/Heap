#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MINIMAL 1
#define MAXIMAL 2


typedef int (*comparador_t)(void*, void*);
typedef struct heap heap_t;

heap_t* heap_crear(comparador_t comparador, int tipo_heap);

int heap_insertar(heap_t* heap, void* elemento);

void* heap_extraer_raiz(heap_t* heap);

size_t heap_cantidad(heap_t* heap);

void heap_destruir(heap_t* heap);


#endif /*  __HEAP_H__ */