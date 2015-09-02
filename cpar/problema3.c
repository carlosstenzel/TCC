/* --- Arquivo : problema3.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include "type_problema3.h"  /* typedef's */
#include "vsg_problema3.h"   /* shared global */
#include "vsl_problema3.h"   /* shared local  */
#include "vst_problema3.h"
#include "bibpar.h"

extern int             mi_id;
extern int             n_proc_macro_;
extern struct comp_loc *macro;
extern comp_gl_usu     *sharedG;
extern void            *sharedL;
extern void            *sharedS;
extern _comp_task_     *sharedT;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void init ();   /* --- spec () */
void desv_std ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void init () 
{
int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i=0; i<100; i++){
        for (j = 0; j < 100; j++)
        {
            sharedG->matriz[i][j] =i+j;

        }
    }


   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void desv_std () 
{
float mean = 0.0, sum_deviation = 0.0;

int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i=0; i<100; i++){
        for (j = 0; j < 100; j++)
        {
            mean += sharedG->matriz[i][j];

        }
    }
    int n = 100*100;
    mean=mean/n;

    for (i=0; i<100; i++){
        for (j = 0; j < 100; j++)
        {
            sum_deviation+=(sharedG->matriz[i][j]-mean)*(sharedG->matriz[i][j]-mean);

        }
    }

    printf ("Desviacion: %f\n",sqrt(sum_deviation/n));  

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

int main()
{

int pidf,id_wait;
void dt_shareG();

   mc_var_inic ();

   def_task (0, "init", sizeof (__init__));
   def_task (1, "desv_std", sizeof (__desv_std__));
   id_wait=sem_wait_inic(2);


   alloc_proc(2); 

      
   pidf = exec_task (0, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      init();
      end_task();            /* --- rs31() - create --- */
   }

    wait();

      
   pidf = exec_task (1, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      desv_std();
      end_task();            /* --- rs31() - create --- */
   }

    wait_all();

       wait_all();      /* --- rs307()  */
   end_program();
   remove_semaforo(id_wait);
return 0;
}

