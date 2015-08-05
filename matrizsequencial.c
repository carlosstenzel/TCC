/*
Multiplicação de matrizes sequencial
Com
Marcação de tempo
*/
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 1000

float A[SIZE][SIZE];
float B[SIZE][SIZE];
float C[SIZE][SIZE];

void inicializa_matriz(){
    int i,j;
    for (i=0;i < SIZE;i++){
        for(j=0;j<SIZE;j++){
            A[i][j]=3*i+j;
            B[i][j]=i+3*j;
            C[i][j]=0.0;
        }
     }
}
void multiplica_matriz(){
    int i,j,k;
    for (i=0;i < SIZE;i++){
        for(k=0;k<SIZE;k++){
            for(j=0;j<SIZE;j++){
                C[i][j]=C[i][j]+A[i][k]*B[k][j];
            }
        }
    }
}
main(){
    inicializa_matriz();
    struct timeval inicio, final;
    int tempogasto;
    gettimeofday(&inicio, NULL);
    multiplica_matriz();
    gettimeofday(&final, NULL);
    tempogasto = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("tempo decorrido: %d\n", tempogasto);
    return 0;
}
