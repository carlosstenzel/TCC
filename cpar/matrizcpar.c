/* --- Arquivo : matrizcpar.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include "type_matrizcpar.h"  /* typedef's */
#include "vsg_matrizcpar.h"   /* shared global */
#include "vsl_matrizcpar.h"   /* shared local  */
#include "vst_matrizcpar.h"
#include "bibpar.h"

extern int             mi_id;
extern int             n_proc_macro_;
extern struct comp_loc *macro;
extern comp_gl_usu     *sharedG;
extern void            *sharedL;
extern void            *sharedS;
extern _comp_task_     *sharedT;

/*Multiplicação de matrizes cpar*/
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
void inicializa_matriz ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void inicializa_matriz () 
{
int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   sharedG->size=1000;
        
 {

   if (setjmp ((*macro).fim_bar) == 0)  /* --- forall () */
      end_barrier();

{
   int i_, n_;
   n_ = (sharedG->size-1 - 0 + 1) / n_proc_macro_;
   if (((sharedG->size-1 - 0 + 1) % n_proc_macro_) != 0)
      n_++;
   i_ = 0 + mi_id * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= sharedG->size-1)); i++) {
       for(j=0;j<sharedG->size;j++){
            sharedG->A[i][j]=3*i+j;
            sharedG->B[i][j]=i+3*j;
            sharedG->C[i][j]=0.0;
       }
    }
}
   if (! _barrier())    /* --- forall () */
      longjmp ((*macro).fim_bar, 1);
  }


   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

void multiplica_matriz ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void multiplica_matriz () 
{
int i, j, k;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   sharedG->size=1000;
        
 {

   if (setjmp ((*macro).fim_bar) == 0)  /* --- forall () */
      end_barrier();

{
   int i_, n_;
   n_ = (sharedG->size-1 - 0 + 1) / n_proc_macro_;
   if (((sharedG->size-1 - 0 + 1) % n_proc_macro_) != 0)
      n_++;
   i_ = 0 + mi_id * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= sharedG->size-1)); i++) {
       for(k=0;k<sharedG->size;k++){
          for(j=0;j<sharedG->size;j++){
             sharedG->C[i][j]=sharedG->C[i][j]+sharedG->A[i][k]*sharedG->B[k][j];
          }
       }
    }
}
   if (! _barrier())    /* --- forall () */
      longjmp ((*macro).fim_bar, 1);
  }


   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

main()
{
int nprocs = 4;

//tempo

struct timeval iniciotmp, finaltmp;

int tempogasto;


int pidf,id_wait;
void dt_shareG();

   mc_var_inic ();

   def_task (0, "inicializa_matriz", sizeof (__inicializa_matriz__));
   def_task (1, "multiplica_matriz", sizeof (__multiplica_matriz__));
   id_wait=sem_wait_inic(2);


   alloc_proc(nprocs);
      
   pidf = exec_task (0, nprocs);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      inicializa_matriz();
      end_task();            /* --- rs31() - create --- */
   }

    wait_all();
    gettimeofday(&iniciotmp, NULL);
      
   pidf = exec_task (1, nprocs);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      multiplica_matriz();
      end_task();            /* --- rs31() - create --- */
   }

    wait_all();
    gettimeofday(&finaltmp, NULL);
    tempogasto = (int) (1000 * (finaltmp.tv_sec - iniciotmp.tv_sec) + (finaltmp.tv_usec - iniciotmp.tv_usec) / 1000);
    printf("Tempo decorrido: %d\n", tempogasto);
       wait_all();      /* --- rs307()  */
   end_program();
   remove_semaforo(id_wait);
return 0;
}

