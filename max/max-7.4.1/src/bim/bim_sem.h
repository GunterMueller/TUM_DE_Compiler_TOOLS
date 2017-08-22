#define SUBLISTSIZE (8192)
#define MAX_SORTS (800)
#define MAX_PRODS (800)
#define MAX_ANAMES (800)
#define CLASSPROD 0
#define TUPLEPROD 1
#define LISTPROD 2

extern char sublist_buffer[ SUBLISTSIZE ];

struct ATTR {
   char name[ 100 ];
   char funcname[ 100 ];
   struct SORT * rsort;
   int pointer_to_node;
   int attribute_of_node;
};

struct SORT {
   char name[ 100 ];
   char sublist_buffer[ SUBLISTSIZE ];
   struct SORT * parent[50];
   int parent_count;
   struct ATTR attrs[ 50 ];
   int new_attr_idx;
   int visited;
};

struct PROD {
   int prod_type;
   char left[ 100 ];
   char production[ SUBLISTSIZE ];
};

extern struct SORT sorts[ MAX_SORTS ];
extern int new_sort_idx;

extern char * sem_sublist( char *, char * );
extern void add_classsort( char * );
extern void add_attr( char *, char *, char * );
extern void dump_info( );
extern char * attribute_names[ MAX_ANAMES ];
extern new_attr_name_idx;













