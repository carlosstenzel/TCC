/* --- Arquivo : exemplo.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include "type_exemplo.h"  /* typedef's */
#include "vsg_exemplo.h"   /* shared global */
#include "vsl_exemplo.h"   /* shared local  */
#include "vst_exemplo.h"
#include "bibpar.h"

extern int             mi_id;
extern int             n_proc_macro_;
extern struct comp_loc *macro;
extern comp_gl_usu     *sharedG;
extern void            *sharedL;
extern void            *sharedS;
extern _comp_task_     *sharedT;

#include <stdio.h>
void tarefa1 ();   /* --- spec () */
void tarefa2 ();   /* --- spec () */
void tarefa3 ();   /* --- spec () */
/* -- rs400() : definicao de task  */
void tarefa1 () 
{
int i;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for(i=0;i<1500;i++)
 {printf("%c",'a');
  fflush(stdout);
 }

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void tarefa2 () 
{
int i;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for(i=0;i<1500;i++)
 {printf("%c",'b');
  fflush(stdout);
 }

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

/* -- rs400() : definicao de task  */
void tarefa3 () 
{
int i;


   if (! _barrier())                    /* --- acao6()  */
      longjmp ((*macro).fim_bar, 1);
   for(i=0;i<1500;i++)
 {printf("%c",'c');
  fflush(stdout);
 }

   if (setjmp ((*macro).fim_bar) == 0) /* --- acao7()  */
      end_barrier();
}

main()
{

int pidf,id_wait;
void dt_shareG();

   mc_var_inic ();

   def_task (0, "tarefa1", sizeof (__tarefa1__));
   def_task (1, "tarefa2", sizeof (__tarefa2__));
   def_task (2, "tarefa3", sizeof (__tarefa3__));
   id_wait=sem_wait_inic(3);


   printf("INICIO TESTE\n");
 fflush(stdout);
 alloc_proc(3);
  
   pidf = exec_task (0, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      tarefa1();
      end_task();            /* --- rs31() - create --- */
   }

  
   pidf = exec_task (1, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      tarefa2();
      end_task();            /* --- rs31() - create --- */
   }

  
   pidf = exec_task (2, 1);  /* --- rs30() - create --- */
   if (pidf == 0)   {
      tarefa3();
      end_task();            /* --- rs31() - create --- */
   }

 printf("FIM\n");
 fflush(stdout);
   wait_all();      /* --- rs307()  */
   end_program();
   remove_semaforo(id_wait);
   return 0;
}

