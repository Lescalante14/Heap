#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MINIMAL 1
#define MAXIMAL 2

/* 
 * Compara los dos elementos.
 * Retorno: <0 si el primero es menor, >0 si el primero es mayor, =0 si son iguales
 */
typedef int (*comparador_t)(void*, void*);

/* 
 * Libera la memoria reservada del elemento almacenado
 */
typedef void (*destructor_t)(void*);

typedef struct heap heap_t;

/* 
 * Crea e inicializa un heap en memoria dinamica 
 * El tipo de heap esta dada por las constantes MINIMAL Y MAXIMAL en este .h
 */
heap_t* heap_crear(comparador_t comparador, destructor_t destructor, int tipo_heap);

/* 
 * Inserta un elemento no NULO al heap
 * Retorno: 0 Si se inserta bien, -1 si algo falla
 */
int heap_insertar(heap_t* heap, void* elemento);

/* 
 * Devuelve la raiz del heap (el menor o mayor segun sea el tipo)
 */
void* heap_raiz(heap_t* heap);

/* 
 * Extrae(remueve) la raiz del heap (el menor o mayor segun sea el tipo)
 * Retorno: 0 Si se remueve bien, -1 si algo falla
 */
int heap_extraer_raiz(heap_t* heap);

/* 
 * Devuelve la cantidad de elementos almacenados en el heap
 */
size_t heap_cantidad(heap_t* heap);

/* 
 * Libera la memoria reservada por el heap
 */
void heap_destruir(heap_t* heap);


#endif /*  __HEAP_H__ */