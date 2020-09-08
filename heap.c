#include "heap.h"

#define EXITO 0
#define ERROR -1

struct heap{
   void** vector;
   size_t cantidad;
   size_t capacidad;
   bool es_minimal;
   comparador_t comparador;
};

////////////// Func AUX /////////

int posicion_padre(int indice){
   return (indice-1)/2;
}

void swap(void** vector, int p1,int p2){
   void* aux =vector[p1];
   vector[p1]=vector[p2];
   vector[p2]=aux;
}

void sift_up(heap_t* heap, int indice){

   int pos_padre=posicion_padre(indice);
   if(heap->es_minimal && heap->comparador(heap->vector[indice],heap->vector[pos_padre])<0){
      swap(heap->vector, indice, pos_padre);
      sift_up(heap, pos_padre);
   }else if(!heap->es_minimal && heap->comparador(heap->vector[indice], heap->vector[pos_padre]) > 0){
      swap(heap->vector, indice, pos_padre);
      sift_up(heap, pos_padre);
   }
}


heap_t* heap_crear(comparador_t comparador, int tipo_heap){
   heap_t* heap=calloc(1,sizeof(heap_t));
   if(!heap)
      return NULL;
   heap->vector=calloc(1,sizeof(void*));
   if(!heap->vector){
      free(heap);
      return NULL;
   }
   if(tipo_heap==MINIMAL)
      heap->es_minimal=true;
   heap->capacidad=1;
   heap->comparador=comparador;
   return heap;
}

int heap_insertar(heap_t* heap, void* elemento){
   if(!heap || !elemento)
      return ERROR;
   if(heap->cantidad>=heap->capacidad){
      void** v_aux=realloc(heap->vector, heap->capacidad * 2 * sizeof(void*));
      if(!v_aux)
         return ERROR;
      heap->vector=v_aux;
   }
   heap->vector[heap->cantidad]=elemento;
   sift_up(heap, heap->cantidad);
   return EXITO;
}

void* heap_extraer_raiz(heap_t* heap);

size_t heap_cantidad(heap_t* heap){
   return heap? heap->cantidad : 0;
}

void heap_destruir(heap_t *heap);