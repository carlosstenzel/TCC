/* --- Arquivo : vsg_matrizcpar.h - vars. compartilhadas globais */

typedef struct {
   int size;

   float A[1000][1000];

   float B[1000][1000];

   float C[1000][1000];

   unsigned char _t_;
} comp_gl_usu;
