#include "heap.h"

int compara_numeros(void* _n1, void* _n2){
   int* n1= _n1;
   int* n2= _n2;
   return (*n1)-(*n2);
}

void destruye_numero(void* elemento){
   free(elemento);
}
   
void probar_heap_elementos_estaticos(){
   heap_t *heap = heap_crear(compara_numeros, NULL, MINIMAL);
   if(!heap)
      return;

   int n1 = 1;
   int n2 = 2;
   int n3 = 3;
   int n4 = 4;
   int n5 = 5;
   int n6 = 6;
   int n7 = 7;
   int n8 = 8;
   heap_insertar(heap, &n8);
   heap_insertar(heap, &n6);
   heap_insertar(heap, &n3);
   heap_insertar(heap, &n2);
   heap_insertar(heap, &n1);
   heap_insertar(heap, &n7);
   heap_insertar(heap, &n4);
   heap_insertar(heap, &n5);

   size_t cantidad = heap_cantidad(heap);
   for (size_t i = 0; i < cantidad; i++){
      printf("%i-", *(int *)(heap_raiz(heap)));
      heap_extraer_raiz(heap);
   }
   heap_destruir(heap);
   printf("\n");
}   

int* crear_numero(int valor){
   int* numero=malloc(sizeof(int));
   if(numero)
      *numero=valor;
   return numero;
}

void probar_heap_elementos_dinamicos(){

   heap_t* heap = heap_crear(compara_numeros, destruye_numero, MAXIMAL);
   if(!heap)
      return;
   int estado=0; // insercion exitosa en el heap
   int* elemento=NULL;
   for(size_t i=0; i<8 && estado==0; i++){
      elemento = crear_numero((int)i + 1);
      estado = heap_insertar(heap, elemento);
   }
   if(estado==-1)//fallo insercion en heap
      destruye_numero(elemento);
   
   size_t cantidad = heap_cantidad(heap);
   for (size_t i = 0; i < cantidad; i++){
      printf("%i-", *(int *)(heap_raiz(heap)));
      heap_extraer_raiz(heap);
   }
   heap_destruir(heap);
   printf("\n");
}

int main(){
   
   probar_heap_elementos_estaticos();
   probar_heap_elementos_dinamicos();

   return 0;
}
