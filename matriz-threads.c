/*
Multiplicação de matrizes com threads

gcc matriz-threads.c -o matriz-threads -lpthread -lm -w
./matriz-threads [TAM DA MATRIZ] [NUM DE PROCS]
*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// definindo as matrizes globais
int **a, **b, **c;
// definindo tamanho da matriz e num de threads
int tam, num_thread;

// função para gerar uma matriz
// que vai preenchendo somando 1
int **gera_matriz(){
    int i;
    int *valores, **temp;

    // alocando memória
    valores = (int *)malloc(tam * tam * sizeof(int));
    temp = (int **)malloc(tam * sizeof(int*));

    for (i = 0; i < tam; i++){
	temp[i] = &(valores[i * tam]);
    }
    // retorna para poder ocupar na main
    return temp;
}

void multiplica_matriz(int thread_id){
    int i, j, k;
    int inicio, final;

    float passo = ceil((float)tam/num_thread);
    inicio = thread_id * passo;
    final = (thread_id + 1)* passo - 1;
    if(final > tam){
	final = tam -1;
    }

    // multiplicação
    printf("Inicio %d => Final %d \n", inicio, final );
    for (i = inicio; i <= final; i++){  
	for (j = 0; j < tam; j++){
	    c[i][j] = 0;
	    for ( k = 0; k < tam; k++){
		c[i][j] += a[i][k]*b[k][j];
	    }
        }
    }
}

int main(int argc, char* argv[]){
    int i,j;
    pthread_t *threads;
    //tempo
    struct timeval iniciotmp, finaltmp;
    int tempogasto;
    

    // definindo o tamanho da matriz
    tam = atoi(argv[1]);

    // definindo tamanho da matriz
    num_thread = atoi(argv[2]);

    // Tratamento para evitar que o número de threads 
    // seja maior que o tam da matriz
    if(num_thread > tam){
	printf("O número de threads é maior que o tamanho da matriz. Por favor selecione um número menor de threads.\n");
	return 0;
    }

    // alocando matriz
    a = gera_matriz();
    b = gera_matriz();
    c = gera_matriz();

    // populando matriz com valor 1
    for(i=0;i<tam;i++){
	for(j=0;j<tam;j++){
	   a[i][j] = 1;
	   b[i][j] = 1;
	}
    }
    gettimeofday(&iniciotmp, NULL);
    // alocando as threads
    threads = (pthread_t *)malloc(num_thread * sizeof(pthread_t));

    // criando as threads e chamando multiplica
    for(i=0; i < num_thread; i++){
	pthread_create(&threads[i], NULL, multiplica_matriz, i);
    }

    for (i = 0; i < num_thread; i++){
	pthread_join(threads[i], NULL);
    }

    // libera as memórias alocadas
    free(threads);
    
    gettimeofday(&finaltmp, NULL);
    tempogasto = (int) (1000 * (finaltmp.tv_sec - iniciotmp.tv_sec) + (finaltmp.tv_usec - iniciotmp.tv_usec) / 1000);
    printf("Tempo decorrido: %d\n", tempogasto);
    return 0;
}
