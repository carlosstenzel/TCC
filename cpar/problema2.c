/* --- Arquivo : problema2.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include "type_problema2.h"  /* typedef's */
#include "vsg_problema2.h"   /* shared global */
#include "vsl_problema2.h"   /* shared local  */
#include "vst_problema2.h"
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
void buscar ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void buscar () 
{
int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i = 0; i < 100; ++i)
        {
            for (j = 0; j < 100; ++j)
            {
                if (sharedG->A[i][j]==sharedG->tosearch){
                    printf("Encontrado en: i->%i, j->%i \n",i,j);
                }
            }
        }
    //printf("No se encontro el numero\n");

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

int main()
{
int i, j;


int pidf,id_wait;
void dt_shareG();

   mc_var_inic ();

   def_task (0, "buscar", sizeof (__buscar__));
   id_wait=sem_wait_inic(1);


   srand (time(NULL));
    for (i=0; i<100; i++){
        for (j = 0; j < 100; j++)
        {
            sharedG->A[i][j] =rand() % 1000;

        }
    }

    alloc_proc(4); 

    printf("Ingresa el numero:");
    scanf("%f",&sharedG->tosearch);

      
   pidf = exec_task (0, 4);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      buscar();
      end_task();            /* --- rs31() - create --- */
   }


    wait_all();

       wait_all();      /* --- rs307()  */
   end_program();
   remove_semaforo(id_wait);
return 0;
}

