#include "heap.h"

int compara_numeros(void* _n1, void* _n2){
   int* n1= _n1;
   int* n2= _n2;
   return (*n1)-(*n2);
}

int main(){
   
   heap_t* heap=heap_crear(compara_numeros, NULL, MINIMAL);

   int n1=1;
   int n2=2;
   int n3=3;
   int n4=4;
   int n5=5;
   int n6=6;
   int n7=7;
   int n8=8;
   heap_insertar(heap, &n8);
   heap_insertar(heap, &n6);
   heap_insertar(heap, &n3);
   heap_insertar(heap, &n2);
   heap_insertar(heap, &n1);
   heap_insertar(heap, &n7);
   heap_insertar(heap, &n4);
   heap_insertar(heap, &n5);

   size_t cantidad=heap_cantidad(heap);
   for(size_t i=0; i<cantidad; i++)
      printf("%i-",*(int*)(heap_extraer_raiz(heap)));
   heap_destruir(heap);
   return 0;
}
