typedef char * MetaSort;

#define MAXSORTCD_NODE 2
#define MAXSORTCD_TERM -2
#define MAXSORTCD_POINT 1 
#define MAXSORTCD_NIL -1

#define is_nodesort(maxsortcd) (maxsortcd >= MAXSORTCD_NODE) 
#define is_termsort(maxsortcd) (maxsortcd <= MAXSORTCD_TERM) 

#define mk_nodesortcd(termsortcd) (is_termsort(termsortcd) ? - termsortcd : termsortcd ) 
#define mk_termsortcd(nodesortcd) (is_nodesort(nodesortcd) ? - nodesortcd : nodesortcd )

#define NO_MAXSORT 0
#define ENDOFARR   NO_MAXSORT

struct meta2max_table_entry{

 MetaSort metasort;
 ELEMENT maxsortcd;

};

typedef struct meta2max_table_entry * meta2max_table; 

