struct sxpinfo_struct {
  SEXPTYPE type      :  3;
  unsigned int scalar:  1;
  unsigned int obj   :  1;
  unsigned int alt   :  1;
  unsigned int gp    : 16;
  unsigned int mark  :  1;
  unsigned int debug :  1;
  unsigned int trace :  1;
  unsigned int spare :  1;
  unsigned int gcgen :  1;
  unsigned int gccls :  3;
  unsigned int named : 16;
  unsigned int extra : 16;
}; 
  
struct vecsxp_struct {
  R_xlen_t	length;
  R_xlen_t	truelength;
};

struct primsxp_struct {
  int offset;
};

struct symsxp_struct {
  struct SEXPREC *pname;
  struct SEXPREC *value;
  struct SEXPREC *internal;
};

struct listsxp_struct {
  struct SEXPREC *carval;
  struct SEXPREC *cdrval;
  struct SEXPREC *tagval;
};

struct envsxp_struct {
  struct SEXPREC *frame;
  struct SEXPREC *enclos;
  struct SEXPREC *hashtab;
};

struct closxp_struct {
  struct SEXPREC *formals;
  struct SEXPREC *body;
  struct SEXPREC *env;
};

struct promsxp_struct {
  struct SEXPREC *value;
  struct SEXPREC *expr;
  struct SEXPREC *env;
};

#define SEXPREC_HEADER \
    struct sxpinfo_struct sxpinfo; \
    struct SEXPREC *attrib; \
struct SEXPREC *gengc_next_node, *gengc_prev_node

typedef struct SEXPREC {
  SEXPREC_HEADER;
  union {
    struct primsxp_struct primsxp;
    struct symsxp_struct symsxp;
    struct listsxp_struct listsxp;
    struct envsxp_struct envsxp;
    struct closxp_struct closxp;
    struct promsxp_struct promsxp;
  } u;
} SEXPREC;

typedef struct VECTOR_SEXPREC {
  SEXPREC_HEADER;
  struct vecsxp_struct vecsxp;
} VECTOR_SEXPREC, *VECSEXP;
