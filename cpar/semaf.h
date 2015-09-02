#define rem_sem rem_semaph

#if  USA_TAS == 1

typedef struct 
  {
    char Sem_,
         Sec_Crit_;
  } Semaph;


typedef  struct
  {
    int Evt_,
        ContEv_;
    char Sec_Crit_;
  }  Event;

#else

typedef struct 
  {
    char Sem_;
    int  Sec_Crit_;
  } Semaph;


typedef  struct
  {
    int Evt_,
        ContEv_;
    int Sec_Crit_;
  }  Event;

#endif
