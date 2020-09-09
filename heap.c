#include "heap.h"

#define EXITO 0
#define ERROR -1

struct heap{
   void** vector;
   size_t cantidad;
   size_t capacidad;
   bool es_minimal;
   comparador_t comparador;
   destructor_t destructor;
};

////////////// Func AUX /////////

size_t posicion_padre(size_t indice){
   return (indice-1)/2;
}

void swap(void** vector, size_t p1, size_t p2){
   void* aux =vector[p1];
   vector[p1]=vector[p2];
   vector[p2]=aux;
}

void sift_up(heap_t* heap, size_t indice){
   if(indice==0)
      return;
   size_t pos_padre=posicion_padre(indice);
   if(heap->es_minimal && heap->comparador(heap->vector[indice],heap->vector[pos_padre])<0){
      swap(heap->vector, indice, pos_padre);
      sift_up(heap, pos_padre);
   }else if(!heap->es_minimal && heap->comparador(heap->vector[indice], heap->vector[pos_padre]) > 0){
      swap(heap->vector, indice, pos_padre);
      sift_up(heap, pos_padre);
   }
}

size_t posicion_hijo_izquierdo(size_t indice){
   return 2*indice+1;
}

size_t busca_indice_candidato(heap_t* heap, size_t p1, size_t p2){
   if(heap->es_minimal){
      if(heap->comparador(heap->vector[p1], heap->vector[p2]) < 0)
         return p1;
      return p2;
   }else{
      if(heap->comparador(heap->vector[p1], heap->vector[p2]) > 0)
         return p1;
      return p2;
   }
}

void sift_down(heap_t* heap, size_t indice){

   size_t p_hijo_izq=posicion_hijo_izquierdo(indice);
   size_t p_hijo_der = p_hijo_izq+1;
   if(p_hijo_izq<heap->cantidad){
      size_t indice_candidato=p_hijo_izq;
      if(p_hijo_der<heap->cantidad){
         indice_candidato=busca_indice_candidato(heap,p_hijo_izq, p_hijo_der);
      }
      if(heap->es_minimal && heap->comparador(heap->vector[indice_candidato], heap->vector[indice]) < 0){
         swap(heap->vector, indice_candidato, indice);
         sift_down(heap, indice_candidato);
      }else if(!heap->es_minimal && heap->comparador(heap->vector[indice_candidato], heap->vector[indice]) > 0){
         swap(heap->vector, indice_candidato, indice);
         sift_down(heap, indice_candidato);
      }
   }
}

///////////// PRINCIPALES //////////////////

heap_t *heap_crear(comparador_t comparador, destructor_t destructor, int tipo_heap){
   if(!comparador || !(tipo_heap == MINIMAL || tipo_heap == MAXIMAL))
      return NULL;
   heap_t *heap = calloc(1, sizeof(heap_t));
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
   heap->destructor=destructor;
   return heap;
}

int heap_insertar(heap_t* heap, void* elemento){
   if(!heap || !elemento)
      return ERROR;
   if(heap->cantidad>=heap->capacidad){
      size_t nueva_capacidad=heap->capacidad*2 + 1;
      void** v_aux=realloc(heap->vector, nueva_capacidad * sizeof(void*));
      if(!v_aux)
         return ERROR;
      heap->vector=v_aux;
      heap->capacidad=nueva_capacidad;
   }
   heap->vector[heap->cantidad]=elemento;
   sift_up(heap, (heap->cantidad));
   (heap->cantidad)++;
   return EXITO;
}

void* heap_raiz(heap_t* heap){
   return heap? heap->vector[0] : NULL;
}

int heap_extraer_raiz(heap_t* heap){
   if(!heap)
      return ERROR;
   if(heap_cantidad(heap) > 0){
      swap(heap->vector, 0, (heap->cantidad)-1);
      if(heap->destructor)
         heap->destructor(heap->vector[heap->cantidad-1]);
      (heap->cantidad)--;
      sift_down(heap, 0);
   }
   return EXITO;
}

size_t heap_cantidad(heap_t* heap){
   return heap? heap->cantidad : 0;
}

void heap_destruir(heap_t *heap){
   if(!heap)
      return;
   free(heap->vector);
   free(heap);
}