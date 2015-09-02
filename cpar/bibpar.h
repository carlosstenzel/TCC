

/*
** Este arquivo conte'm as estruturas utilizadas pelas
** rotinas da biblioteca de suporte ao processamento
** paralelo.
*/

/******
#include  "types.h"
#include  "ipc.h"
#include  "shm.h"
#include  "signal.h"
**************************/
#include   <setjmp.h>
#include   "tipos.h"
#define rem_ev  rem_evento

#define   USA_TAS      0


#define   TAM_MC       1000   /* tam. memoria compart. */
#define   END_MC       1000   /* end. memoria compart. */
#define   NUM_MACR       16   /* # de macrotarefas */
#define   NUM_MICR       64   /* # de microtarefas */
#define   NUM_VAR       100   /* # de variaveis de sincr. */
#define   ERRO           -1

/****
#define   TRUE            1
#define   FALSE           0
#define   OK              0
****/

/*
** formato geral das variaveis de sincronismo
*/

struct var_sin {
  int vlr_var;       /* valor da variavel */
  int pid_prop;      /* id do proprietario */
  int num_proc_esp;  /* # de processos esperando */
  int ult_pid;       /* id do ultimo processo a utilizar a variavel */
  int ult_inst;      /* instante da ultima operacao na variavel */
  };

/*
** estrutura do segmento de memo'ria compartilhada local as
** macrotarefas 
*/

#if  USA_TAS == 1

struct mc_loc {
     unsigned char Sec_Crit_;   /* sincronismo para microtarefas */
     int Indice_Processo,
         Ult_Atv,
         Inic_Macro,
         id_macro,   /* utilizada na criacao da variavel comp. "macro"  */
         id_sharedL,  /* utilizada na criacao da variavel comp. "sharedL"  */
         id_sharedS;
     int pid[NUM_MICR];        /* id. dos proc. na macrot. */
     };

#else

struct mc_loc {
     int Sec_Crit_;   /* sincronismo para microtarefas */
     int Indice_Processo,
         Ult_Atv,
         Inic_Macro,
         id_macro,   /* utilizada na criacao da variavel comp. "macro"  */
         id_sharedL,  /* utilizada na criacao da variavel comp. "sharedL"  */
         id_sharedS;  /*utilizacao na criacao da area de variavel comp. de sub. */
     int pid[NUM_MICR];        /* id. dos proc. na macrot. */
     };

#endif

#if  USA_TAS == 1
 
struct comp_loc {
     int num_proc;             /* numero de processos */
     int proc_atv;             /* numero de processos ativos */
     jmp_buf fim_bar;          /* variavel para uso de setjmp e longjmp */
     char barreira;              /* variaveis de */
     unsigned char Sem_Secao_Crit;  /* sincronismo para microtarefas */
     };


#else

struct comp_loc {
     int num_proc;             /* numero de processos */
     int proc_atv;             /* numero de processos ativos */
     jmp_buf fim_bar;          /* variavel para uso de setjmp e gjmp */
     int barreira;              /* variaveis de */
     int Sem_Secao_Crit;      /* sincronismo para microtarefas */
     };

#endif


/*
** organizacao do segmento de memoria compartilhada
** utilizado pela biblioteca
*/

struct str_proc
  {
    char nome_proc[MAX_TAM];
    int TamVarComp;
  };


struct seg_bb {
/*****    struct var_sin exm;               /* var. p/ exclusao mutua */
/*****    struct var_sin var_sinc[NUM_VAR]; /* segmento de memoria global */
/*****    int ProxVar;                      /* proxima variavel livre */
    struct mc_loc ma[NUM_MACR];       /* segmentos locais */
    struct str_proc Tab_Proc[MAX_PROCESSOS];
    int  Tab_Proc_Atv[MAX_PROCESSOS];
    VetP proc_control;
    char Sec_Crit;
    /* incluido para implementar Wait com semaforo - 30/03/99 */
    int semid_wait; /*id do semaforo para wait*/
};

/* quando instalar no sistema voltar a declaracao de time */
/* long int time; */    /* variavel de relogio */

/* Hsiang: prototipo de funcoes */
char _barrier (/*void*/);/* Lais tirou o void */
