/*
Multiplicação de matrizes OpenMP
*/
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#define SIZE 1000
int size;
float A[SIZE][SIZE];
float B[SIZE][SIZE];
float C[SIZE][SIZE];

main(){
    int nproc;
    int i, j, k, n;
    size = SIZE;
    /*
        num de proc
    */
    nproc =2;
    struct timeval inicio, final;
    int tempogasto;

    #pragma omp parallel shared(A, B, C, size) private(i,j, k)
    {
    #pragma omp for
        for(i=0; i <size; i++){
                for(j=0;j<size;j++){
                    A[i][j]=3*i+j;
                    B[i][j]=i+3*j;
                    C[i][j]=0.0;
                }
        }

        gettimeofday(&inicio, NULL);
        #pragma omp for
        for(i=0; i<size; i++){
                for(k=0;k<size;k++){
                    for(j=0;j<size;j++){
                        C[i][j]=C[i][j]+A[i][k]*B[k][j];
                    }
                }
        }

    }

    gettimeofday(&final, NULL);
    tempogasto = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("tempo decorrido: %d\n", tempogasto);

}
