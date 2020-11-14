/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "puzle.h"
#include "listaia.h"
#include "busqueda.h"

void solucionFin(int res){
   printf("\nFin de la busqueda\n");

    if (res)
      printf("Se ha llegado al objetivo\n");
   else
      printf("No se ha llegado al objetivo\n");
}
void dispNodo(tNodo *nodo){
    dispEstado(nodo->estado);
    printf("\n");
}
void dispCamino(tNodo *nodo){
    if (nodo->padre==NULL){
        printf("\n Desde el inicio\n");
        dispEstado(nodo->estado);
    }
    else {
        dispCamino(nodo->padre);
         dispOperador(nodo->operador);
        dispEstado(nodo->estado);
    }
}

void dispSolucion(tNodo *nodo){
   printf("Profundidad=%d\n",nodo->profundidad);
   printf("Coste=%d\n",nodo->costeCamino);
   dispCamino(nodo);
}


/* Crea el nodo raíz. */
tNodo *nodoInicial(){
   tNodo *inicial=(tNodo *) malloc(sizeof(tNodo));
   inicial->estado=estadoInicial();
   inicial->padre=NULL;
   inicial->costeCamino=0;
   inicial->profundidad=0;
   return inicial;
}

LISTA expandir(tNodo *nodo){
    unsigned op;
    LISTA sucesores=VACIA;
    tNodo *nuevo=calloc(1,sizeof(tNodo));
    tEstado *s;
    for (op=1; op<=NUM_OPERADORES;op++){
      if (esValido(op,nodo->estado)){
                        //s=(tEstado *)calloc(1,sizeof(tEstado));
          s=aplicaOperador(op,nodo->estado);
          nuevo->estado=s;
          nuevo->padre=nodo;
          nuevo->operador=op;
          nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
          nuevo->profundidad=nodo->profundidad+1;
          InsertarUltimo(&sucesores,  (tNodo *) nuevo, (sizeof (tNodo)));
      }
  }
return sucesores;
}

int busqueda(){
    int objetivo=0, visitados=0, p = 0;
    tNodo *Actual=(tNodo*) calloc(1,sizeof(tNodo));
    tNodo *Inicial=nodoInicial();

    LISTA Abiertos= VACIA;                                  //Se guardan los nodos abiertos (pendientes a tratar)
    LISTA Sucesores= VACIA;                                 //Se guardan los nodos a expandir
    LISTA Cerrados = VACIA;                                 //Se guardan los nodos que ya han sido tratados
    InsertarPrimero(&Abiertos,(tNodo*) Inicial,sizeof(tNodo));
    while (!esVacia(Abiertos) && !objetivo){

        Actual=(tNodo*) calloc(1,sizeof(tNodo));
        ExtraerPrimero(Abiertos,Actual, sizeof(tNodo));
        EliminarPrimero(&Abiertos);
        p =buscar_repetidos(Actual,Cerrados);
        if(p==0){
            objetivo=testObjetivo(Actual->estado);
            if (!objetivo){
                visitados++;
                Sucesores = expandir(Actual);
                InsertarPrimero(&Cerrados,(tNodo*) Actual, sizeof(tNodo));     //Almalceno el contenido de Abiertos en Cerrado
                imprimir(Cerrados);
                Abiertos=  Concatenar(Abiertos,Sucesores);        //Cambiando los parametros se convierten en ANCHURA o PROFUNDIDAD

                }
            }
        }//while
    //Iteracion lista

    printf("\nVisitados= %d\n", visitados);
    if (objetivo)
        dispSolucion(Actual);
    free(Sucesores);
    free(Inicial);
    free(Actual);
    return objetivo;
}

int buscar_repetidos(tNodo *Actual,  LISTA Cerrados){      // Pasamos la lista de Sucesores y el nodo actual

    int igual = 0;
    tNodo *Sucesor =(tNodo*) calloc(1,sizeof(tNodo));

   if(!esVacia(Cerrados)){
        LISTA Auxiliar = Cerrados;                            //Comparamos todos los nodos de la lista de Sucesores con el nodo actual

        while(!esVacia(Auxiliar) && igual == 0){

            ExtraerPrimero(Auxiliar,Sucesor,sizeof(tNodo));

            igual = iguales(Actual->estado, Sucesor->estado);

            Auxiliar = Auxiliar->next;

            }
   }

    return igual;
}

int profundidad_limitada(int limite, tNodo *Actual){

    return(limite > Actual->profundidad);
}

int funcion_heuristica(tNodo *Actual){         //Vamos a calcular el numero de piezas mal colocadas (filas y columnas)
    tNodo *Final =(tNodo*) calloc(1,sizeof(tNodo));
    Final->estado = estadoObjetivo();
    unsigned int fila1 ,columna1, fila2, columna2, total=0 ;

    for(fila1=0;fila1<N;fila1++){
        for(columna1=0;columna1<N;columna1++){
            for(fila2 = 0; fila2<N; fila2++){
                for(columna2 = 0; columna2<N; columna2++){
                    if(Actual->estado->celdas[fila1][columna1] == Final->estado->celdas[fila2][columna2]){
                        total = abs(fila1-fila2 + columna1 - columna2) + total;
                    }

                }
            }
        }
    }
    Actual->valHeuristica = total;
    return total;

}

void imprimir(LISTA Cerrados){

LISTA Auxiliar = Cerrados;
tNodo *Sucesor =(tNodo*) calloc(1,sizeof(tNodo));
printf("CERRADOS: \n");
while(!esVacia(Auxiliar)){

    ExtraerPrimero(Auxiliar,Sucesor,sizeof(tNodo));

    dispEstado(Sucesor->estado);
    Auxiliar = Auxiliar -> next;
}

printf("\nTERMINA.\n");


}
