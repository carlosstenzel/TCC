/*
Multiplicaçã de matrizes MPI
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <sys/time.h>

int main(int argc , char *argv[]){
    int tam = atoi(argv[1]);
    int size,rank,sum=0,i,j,k;
    int **a, **b, **c;
    struct timeval inicio, final;
    int tempogasto;
    gettimeofday(&inicio, NULL);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // criando um array de ponteiros
    a =(int **)malloc(tam * sizeof(int*));
    b =(int **)malloc(tam * sizeof(int*));
    c=(int **)malloc(tam * sizeof(int*));

    // alocando memória para as matrizes
    for(i = 0; i < tam; i++){
	a[i]=(int *)malloc(tam * sizeof(int));
	c[i]=(int *)malloc(tam * sizeof(int));
	b[i]=(int *)malloc(tam * sizeof(int));
    }

    // inicializando as matrizes com valor 1
    for(i = 0; i < tam; i++){
	for(j = 0; j < tam; j++){
	     a[i][j] = 1;
	     b[i][j] = 1;
	}
    }
	
    // dividindo as tarefas nos vários processos
    for(i = rank; i < tam; i = i+size){
	for(j = 0; j < tam; j++){
	     sum=0;
	     for(k = 0; k < tam; k++){
		 sum = sum + a[i][k] * b[k][j];
	     }
	     c[i][j] = sum;
	}
    }

    // Se o rank for diferente de um, ele envia o resultado
    // para o rank principal
    if(rank != 0){
	for(i = rank; i < tam; i = i+size){
	     MPI_Send(&c[i][0], tam, MPI_INT, 0, 10+i, MPI_COMM_WORLD);
	} 
    }
 
    // Sendo o rank principal, ele vai receber todas as partes calculadas
    // de cada um dos outros processos
    if(rank == 0){
	for(j = 1; j < size; j++){
	    for(i = j; i < tam; i = i+size){
	 	MPI_Recv(&c[i][0], tam, MPI_INT, j, 10+i, MPI_COMM_WORLD, &status);
	    }
	}
    }

    MPI_Barrier(MPI_COMM_WORLD);
	
    // Finaliza
    if(rank == 0){
	MPI_Finalize();      
    }
    if(rank == argc){
	gettimeofday(&final, NULL);
        tempogasto = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
        printf("tempo decorrido: %d\n", tempogasto);
    }

    return 0;
}
