
/* ----------------------------------------
 * Modulo : ShareAux.C
 *
 * Objetivo : complementa o modulo SHARE.C
 * Ultima alteracao : 2-3-92  (Paulo T. Ota)
 * ----------------------------------------
 */
 
#include   <stdio.h>
#include   <sys/types.h>
#include   <sys/ipc.h>
#include   <sys/shm.h>

#include "tudo.h"
#include "bibpar.h"
extern struct seg_bb *mc_bb;
extern int ma_id;

int id_sharedT;
_comp_task_ *sharedT;

void get_sharedT (size)
int size;
{
   if ((id_sharedT = shmget (0, sizeof (_comp_task_) , 0777 | IPC_CREAT)) == ERRO) {
      printf ("get_sharedT : erro na alocacao de memoria compart.\n");
      Aborta();
   }
}

void at_sharedT ()
{
   if ( (sharedT = (_comp_task_ *) shmat (id_sharedT, 0, 0)) == (void *) ERRO) {
      printf ("at_sharedT : erro na alocacao de memoria compart.\n");
      Aborta();
   }
}

void dt_sharedT ()
{
   shmdt ((char *)sharedT);
}

void ctl_sharedT()
{
    struct shmid_ds *buf;

    shmctl (id_sharedT, IPC_RMID, buf);
}


/* ------ rotinas para o tipo sharedS ------ */

/*int  id_sharedS;*/
void *sharedS;

void get_sharedS (size)
int size;
{
   if (((*mc_bb).ma[ma_id].id_sharedS = shmget (0, size, 0777 | IPC_CREAT)) == ERRO) {
      printf ("get_sharedS : erro na alocacao de memoria compart.\n");
      Aborta();
   }
}

void at_sharedS ()
{
   if ( (sharedS = (void *) shmat ((*mc_bb).ma[ma_id].id_sharedS, 0, 0)) ==(void *) ERRO) {
      printf ("at_sharedS : erro na alocacao de memoria compart.\n");
      Aborta();
   }
}

void dt_sharedS ()
{
   shmdt ((char *)sharedS);
}

void ctl_sharedS()
{
    struct shmid_ds *buf;

    shmctl ((*mc_bb).ma[ma_id].id_sharedS, IPC_RMID, buf);
}

void aloca_comp_task (tamanho)
int tamanho;
{
   get_sharedS (tamanho);
   at_sharedS();
}

void libera_comp_task ()
{
   dt_sharedS();
   ctl_sharedS();
}
