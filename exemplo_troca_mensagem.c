/*
 C Example 
 Para compilar - mpicc te.c -o teste
 Para rodar    - mpirun -np 4 ./teste 
*/
#include <mpi.h>
#include <stdio.h>

int msg,dest,tag;

int main (int argc, char* argv[]){
  int rank, size, i, dest, recebe, number;

  MPI_Init (&argc, &argv);                /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);  /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);  /* get number of processes */
  
  //printf("%d", rank);  

  int test = size-1;
  
  int processo = rank;
  /* processo mestre */
  if(processo == 0){
	number = 1;
    	MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
  }
  /* processo escravo */
  for(i=1;i<=test;i++){
     if (rank == i) {
        recebe = i-1;
        dest = i+1;
    	MPI_Recv(&number, 1, MPI_INT, recebe, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    	number+=10;
    	printf("Processo %d recebeu a soma do numero %d do processo %d\n",rank, number, recebe);
        if(i==test){break;}
    	MPI_Send(&number, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
     }
    
  }
  

  MPI_Finalize();

   return 0;
}
