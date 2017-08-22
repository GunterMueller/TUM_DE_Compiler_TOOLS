typedef long Boolean;

#define TRUE 1
#define FALSE (!TRUE)

#define IDSTR(idn)    etoa(idtos(term(son(1,idn))))

#define EXPR      1
#define CONST     2
#define SIG_PATH  3
#define UNION     4 
#define SIG       5 

typedef struct constrlist_entry * constr_list; 

struct constrlist_entry{

 ELEMENT expn;
 int constr_descr;
 union {
	struct 
	{
		MetaSort t1;
		MetaSort t2;
	} t_t;

	struct
	{
		MetaSort t;
		MetaSort c;
	} t_c;

	struct
	{
		MetaSort t;
		ELEMENT path;
		MetaSort source;
	} t_p;

	struct 
	{
		MetaSort t;
		ELEMENT l;
	} t_u;

        struct
        {
                MetaSort t;
                ELEMENT idn;
                ELEMENT args;
        } t_s;

 } constraint;

 constr_list next;
 
}; 
		
