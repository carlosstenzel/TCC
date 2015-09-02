/* --- Arquivo : problema1.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include "type_problema1.h"  /* typedef's */
#include "vsg_problema1.h"   /* shared global */
#include "vsl_problema1.h"   /* shared local  */
#include "vst_problema1.h"
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
void multiplicarAB ();   /* --- spec () */
void multiplicarCD ();   /* --- spec () */
void sumar ();   /* --- spec () */
void print ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void print () 
{
int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i = 0; i < 100; ++i)
        {
            for (j = 0; j < 100; ++j)
            {
                printf("%f ",sharedG->res3[i][j]);
            }
            printf("/n");
        }
    printf("/n");

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void multiplicarAB () 
{
int i, j, k;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i = 0; i < 100; ++i)
    {
        for (j = 0; j < 100; ++j)
        {
            sharedG->res1 [i][j] = 0;
            for (k = 0; k < 100; ++k)
            {
               sharedG->res1[i][j] = sharedG->res1[i][j] + (sharedG->A[i][k] * sharedG->B[k][j]);
            }
        }
    }

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void multiplicarCD () 
{
int i, j, k;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for (i = 0; i < 100; ++i)
    {
        for (j = 0; j < 100; ++j)
        {
            sharedG->res2 [i][j] = 0;
            for (k = 0; k < 100; ++k)
            {
               sharedG->res2[i][j] = sharedG->res2[i][j] + (sharedG->A[i][k] * sharedG->B[k][j]);
            }
        }
    }

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void sumar () 
{
int i, j;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
       
 {

   if (setjmp ((*macro).fim_bar) == 0)  /* --- forall () */
      end_barrier();

{
   int i_, n_;
   n_ = (100 - 1 + 1) / n_proc_macro_;
   if (((100 - 1 + 1) % n_proc_macro_) != 0)
      n_++;
   i_ = 1 + mi_id * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= 100)); i++) {
        for (j = 0; j < 100; ++j)
        {
            sharedG->res3[i][j]= sharedG->res1[i][j] + sharedG->res2[i][j];
        }
    }
}
   if (! _barrier())    /* --- forall () */
      longjmp ((*macro).fim_bar, 1);
  }


   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

int main()
{
int i, j;


int pidf,id_wait;
void dt_shareG();

   mc_var_inic ();

   def_task (0, "multiplicarAB", sizeof (__multiplicarAB__));
   def_task (1, "multiplicarCD", sizeof (__multiplicarCD__));
   def_task (2, "sumar", sizeof (__sumar__));
   def_task (3, "print", sizeof (__print__));
   id_wait=sem_wait_inic(4);


   for (i=0; i<100; i++){
        for (j = 0; j < 100; j++)
        {
            /*A[i][j] = i + j;
            B[i][j] = i + 2*j;
            C[i][j] = i*2 + j*3;
            D[i][j] = i*2 + j;*/
            sharedG->A[i][j] = 1;
            sharedG->B[i][j] = 1;
            sharedG->C[i][j] = 1;
            sharedG->D[i][j] = 1;
        }
    }

    alloc_proc(4);

      
   pidf = exec_task (0, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      multiplicarAB();
      end_task();            /* --- rs31() - create --- */
   }

      
   pidf = exec_task (1, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      multiplicarCD();
      end_task();            /* --- rs31() - create --- */
   }


    wait_all();

      
   pidf = exec_task (2, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      sumar();
      end_task();            /* --- rs31() - create --- */
   }

    
    
   wait_proc (2);    /* --- wait_proc() --- */


      
   pidf = exec_task (3, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      print();
      end_task();            /* --- rs31() - create --- */
   }


       wait_all();      /* --- rs307()  */
   end_program();
   remove_semaforo(id_wait);
return 0;
}

