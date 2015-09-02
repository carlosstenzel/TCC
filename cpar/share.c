



/***  OBS: Definicao das variaveis  "sharedG, sharedL" no include "tipsh.h" ***/
/* #define DEBUG_SHMEM */

#include   <stdio.h>
#include   <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/shm.h>

/******  #include "semaf.h"  ****/

/* #include "vsharedg.h"
   #include "vsharedl.h"  07/10/91 
*/

#include "tudo.h"
#include "bibpar.h"
#define ERRO -1

extern struct seg_bb * mc_bb;
extern int ma_id;

    /* prototipo de shmat */
/*char * shmat ();*/        /* linux e sun */
/* char * shmat (); */  /* sgi         */


     /* Variaveis utilizadas para as compartilhadas do usuario */

        /* Globais nao compartilhadas */
int id_sharedG;

       /* Ponteiro da estrutura compartilhada global, de uso do usuario */
comp_gl_usu * sharedG;

       /* Ponteiro da estrutura compartilhada local, de uso do usuario */
void * sharedL;


       /* Tamanho da estrutura compartilhada global do usuario */
#define    TAM_sharedG     sizeof (comp_gl_usu)

 


     /* Inicializacao das variaveis da biblioteca */
void inic_shareG ()
  {
#ifdef DEBUG_SHMEM
	printf( "Memoria compartilhada global.\n" );
#endif
	shmalloc(&id_sharedG, &sharedG, TAM_sharedG);
/*
if((id_sharedG=shmget(IPC_PRIVATE,TAM_sharedG,0777|IPC_CREAT))==ERRO)
          printf("Erro na criacao de memoria compartilhada\n");*/
  }


void get_shareL (Tam)
  int Tam;

  {
#ifdef DEBUG_SHMEM
	printf( "Tamanho: %ld.\n" );
#endif
    if ( ((*mc_bb).ma[ma_id].id_sharedL = 
                      shmget (IPC_PRIVATE, Tam, 0777 | IPC_CREAT)) == ERRO )
      {
#ifdef DEBUG_SHMEM
	printf ("Variaveis compartilhadas locais.\n" );
	printf ("Tamanho a ser alocado: %ld\n", Tam );
#endif
        printf ("Erro na criacao de memoria compartilhada\n");
	show_shmem_error();
        Aborta ();
      }
/***
printf ("MA_ID = %d,  ID_SHAREL = %d\n", ma_id, (*mc_bb).ma[ma_id].id_sharedL);
***/
  }

void at_shareL ()
  {
    if ( (sharedL = shmat ((*mc_bb).ma[ma_id].id_sharedL, 0, 0)) == (void *)ERRO )
      {
        printf ("Erro na utilizacao de memoria compartilhada\n");
	show_shmem_error();
        Aborta ();
      }
  }

void at_shareG ()
  {
    if ( (sharedG = (comp_gl_usu *) shmat (id_sharedG, 0, 0)) == (void *) ERRO )
      {
        printf ("Erro na utilizacao de memoria compartilhada\n");
	show_shmem_error();
        Aborta ();
      }
 }

void dt_shareL ()
  {
    shmdt (sharedL);
  }

void dt_shareG ()
  {
    shmdt ((char *)sharedG);
  }

void ctl_shareL ()
  {
    struct shmid_ds *buf;

    shmctl ((*mc_bb).ma[ma_id].id_sharedL, IPC_RMID, buf);
  }

void ctl_shareG ()
  {
    struct shmid_ds *buf;

    shmctl (id_sharedG, IPC_RMID, buf);
  }


