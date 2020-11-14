/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
   tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
   int i, j, ficha;

   for (i=0;i<N;i++)
      for (j=0;j<N;j++)
      {
         ficha=puzle[i][j];
         estado->celdas[i][j]=ficha;
         estado->fila[ficha]=i;
         estado->col[ficha]=j;
      }
   return estado;
}


tEstado *estadoInicial()
{
   return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
   return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
   return 1;
}

/* VISUALIZACIÓN DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
   int i,j;

   for (i=0; i<N; i++)
   {
      for (j=0; j<N; j++)
         printf("%d",estado->celdas[i][j]);
      printf("\n");
   }
   printf("\n");
}


void dispOperador(unsigned op)
{
   switch(op)
   {
      case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
      case ABAJO:     printf("Movimiento ABAJO:\n"); break;
      case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
      case DERECHA:   printf("Movimiento DERECHA:\n"); break;
   }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// Función auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
   int i = 0, j = 0, iguales = 1;

  for(i=0;i<N && iguales != 0;i++){
    for(j=0;j<N && iguales != 0;j++){
        if(s->celdas[i][j] != t->celdas[i][j]){
            iguales = 0;
        }
    }
}


  return iguales;
}


int testObjetivo(tEstado *estado)
{
    tEstado *objetivo;
    objetivo = estadoObjetivo();

return iguales(objetivo,estado);
}


int esValido(unsigned op, tEstado *estado)
{
    int Valido,i,j;
     i =  estado->fila[0]; //filaDelHueco(*estado);
     j =  estado->col[0];
    switch(op){
        case ARRIBA: Valido = ( i>0);break;
        case ABAJO: Valido = (i<N-1);break;
        case IZQUIERDA: Valido =(j>0);break;
        case DERECHA: Valido = (j<N-1);break;
        default: Valido = 0; break;
    }
return Valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
      int i,j,aux,FilaNueva,ColNueva,v;
     tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
      i =  estado->fila[0]; //filaDelHueco(*estado);
      j =  estado->col[0];
     switch(op){
        case ARRIBA: nuevo->fila[0] = nuevo->fila[0] - 1;break;
        case ABAJO: nuevo->fila[0] = nuevo->fila[0] +1;break;
        case IZQUIERDA: nuevo->col[0] = nuevo->col[0] -1;break;
        case DERECHA: nuevo->col[0] = nuevo->col[0] +1;break;
        default:break;
    }

    FilaNueva = nuevo->fila[0];    //Guardo la fila nueva originada en la que se almacenará el 0
    ColNueva = nuevo->col[0];      //Guardo la columna nueva originada en la que se almacenará el 0
    aux = nuevo->celdas[FilaNueva][ColNueva]; //Obtengo el número almacenado en la posición en la que vamos a intercambiarlo por el 0

    nuevo->fila[aux] = i;                     //Guardo en la fila el numero a cambiar, por la posicion de la fila del 0
    nuevo->col[aux] = j;                      //Guardo en la columna el numero a cambiar, por la posición de la columna del 0
    nuevo->celdas[i][j] = aux;                //Guardo en la matriz con las posiciones de donde estaba antes el 0, con el numero intercambiado
    nuevo->celdas[FilaNueva][ColNueva] = 0;   //Guardo en la matriz con la fila nueva y la columna nueva, la posicion del 0


return nuevo;
}




