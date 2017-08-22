
#include <stdio.h>
#include <stdlib.h>

#include "max_spec.h"
#include "max_metasort.h"
#include "max_typecheck.h"


/* globals */
long metasort_length;
MetaSort const_ms_PREDECLSORT;
MetaSort const_ms_CLASSSORT;
MetaSort const_ms_TUPLESORT;
MetaSort const_ms_LISTSORT;
MetaSort const_ms_NODESORT;
MetaSort const_ms_TERMSORT;
MetaSort const_ms_CHAR;
MetaSort const_ms_INT;
MetaSort const_ms_STRING;
MetaSort const_ms_IDENT;
MetaSort const_ms_BOOL;
MetaSort const_ms_ROOT;
MetaSort const_ms_UNIV;
MetaSort const_ms_NODE;
MetaSort const_ms_TERM;
MetaSort const_ms_POINT;
MetaSort const_ms_NIL;
MetaSort const_ms_CIS;
int numofsorts;
meta2max_table MetaMax;


/* functions */
ELEMENT * maxsorts_by_metasort();
MetaSort metasort_by_sortid();
MetaSort metasort_by_prod();
MetaSort ms_intersection();
MetaSort ms_union();
Boolean is_subset();
void metasort_init();


ELEMENT * maxsorts_by_metasort(MetaSort M, ELEMENT * maxsorts)
{
 int i,arr_cnt = 0;

 for(i = 0; i < numofsorts + 1;i++)

    maxsorts[i] = ENDOFARR;

 for(i = 0; i < numofsorts;i++)

  if(is_subset(MetaMax[i].metasort, M))
     maxsorts[arr_cnt++] = MetaMax[i].maxsortcd; 

 return maxsorts;

}


MetaSort metasort_by_prod( Boolean isnode, ELEMENT prod, MetaSort M )
{
 int i;
 long ms_byte,ms_bit;
 long metasortcd;
 ELEMENT maxsortcd,p_v;

 if(is(prod, _ClassProd_))
 {
     for(i = 1; i <= numsons(son(2,prod)); i++)
     {
      p_v = fath(subterm(1,idtodecls(term(son(1,son(i,son(2,prod)))))));
      metasort_by_prod((isnode || (is(son(i,son(2,prod)), _TermSortId_) ? FALSE : TRUE)), p_v, M);
     }
 }
 else
 {
    if(prodcd(prod) == MAXSORTCD_TERM)

      for(i = 0;i < metasort_length;i++)

         M[i] |= const_ms_TERM[i];


    else if(prodcd(prod) == MAXSORTCD_NODE)

           for(i = 0;i < metasort_length;i++)

	      M[i] |= const_ms_NODE[i];


         else
         {
            if(isnode) maxsortcd = mk_nodesortcd(prodcd(prod));
            else       maxsortcd = prodcd(prod);

	    metasortcd = (maxsortcd < 0) ? metasort_length * 8 + maxsortcd :
                                           maxsortcd;

	    ms_byte = metasortcd / 8;
	    ms_bit  = metasortcd % 8;

	    M[ms_byte] |= 1 << ms_bit; 

	 }

 }

 return M;

} 


MetaSort metasort_by_sortid(Boolean isnode, ELEMENT sortid, MetaSort M)
{
 int i;
 long ms_byte,ms_bit;
 ELEMENT defid = subterm(1,idtodecls(sortid));

 if(!is(fath(defid),_ClassProd_))
 {
    long metasortcd;
    ELEMENT maxsortcd = prodcd(fath(defid));

    if(maxsortcd == MAXSORTCD_TERM)
    {
      for(i = 0;i < metasort_length;i++)

         M[i] |= const_ms_TERM[i];

      return M;
    }

    else if(maxsortcd == MAXSORTCD_NODE)
         {
           for(i = 0;i < metasort_length;i++)

	      M[i] |= const_ms_NODE[i];

           return M;
         }
         else
         {
            if(isnode) 

               maxsortcd = mk_nodesortcd(maxsortcd);

	    metasortcd = (maxsortcd < 0) ? metasort_length * 8 + maxsortcd :
                                           maxsortcd;

	    ms_byte = metasortcd / 8;
	    ms_bit  = metasortcd % 8;

	    M[ms_byte] |= 1 << ms_bit; 
	 }

 }

 else

 {

      for(i = 1; i <= numsons(rbroth(defid)); i++)

         metasort_by_sortid((isnode || (is(son(i,rbroth(defid)), _TermSortId_) ? FALSE : TRUE)), term(son(1,son(i,rbroth(defid)))), M); 

 }

 return M;

} 



MetaSort ms_intersection(MetaSort M1, MetaSort M2, MetaSort target)
{
 int i;

 for(i = 0; i < metasort_length; i++)

    target[i] = (M1[i] & M2[i]);

 return target;

}


MetaSort ms_union(MetaSort M1, MetaSort M2, MetaSort target)
{
 int i;
 
 for(i = 0; i < metasort_length; i++)

    target[i] = (M1[i] | M2[i]);

 return target;

}


Boolean is_subset(MetaSort M1, MetaSort M2)
{
 int i;

 for(i = 0; i < metasort_length; i++)

    if ((int)(M2[i] | ~M1[i]) != -1) return FALSE; 
 
 return TRUE;

}


void metasort_init()
{
 int i,j;
 long metasortcd;
 ELEMENT maxsortcd;
 ELEMENT prod;
 long ms_byte,ms_bit;
 ELEMENT p;
 MetaSort M;
 int entry_cnt = 0;

  /* 
    Term + point,nil = Predecl - 2 (Term,Node) + Tuple + List
    Node = Term - 2 (Point,nil)
  */

 metasort_length = number(_PredeclProd_) - 2 + number(_TupelProd_)
                   + number(_ListProd_);
 
 metasort_length += (metasort_length - 2);


 metasort_length = (metasort_length % 8 == 0) ? (metasort_length / 8) :
                                                (metasort_length / 8) + 1;

 metasort_length++;

 /* metasort constants */

    const_ms_PREDECLSORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_PREDECLSORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_CLASSSORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_CLASSSORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_TUPLESORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_TUPLESORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_LISTSORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_LISTSORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_NODESORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_NODESORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_CHAR = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_CHAR )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_INT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_INT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_STRING = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_STRING )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_IDENT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_IDENT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_BOOL = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_BOOL )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_ROOT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_ROOT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    metasort_by_sortid(TRUE,term(son(1,son(2,element(1,_Structure_)))),
                       const_ms_ROOT);

    const_ms_UNIV = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_UNIV )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_TERMSORT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_TERMSORT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

    const_ms_NIL = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_NIL )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }


    const_ms_NODE = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_NODE )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }
    
    const_ms_POINT = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_POINT )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }
    
    const_ms_CIS = (MetaSort) calloc(metasort_length,sizeof(char));

    if( !const_ms_CIS )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }


      for(i = 1;i <= number(_Production_);i++)
      {
        prod = element(i,_Production_);

        if(is(prod,_ClassProd_)) continue;

        maxsortcd = - prodcd(prod);

        if(maxsortcd == - MAXSORTCD_NODE)  continue;
        if(maxsortcd == - MAXSORTCD_TERM)  continue;
        if(maxsortcd == - MAXSORTCD_POINT) continue;
        if(maxsortcd == - MAXSORTCD_NIL)   continue;

        metasortcd = (maxsortcd < 0) ? metasort_length * 8 + maxsortcd :
                                       maxsortcd;

        ms_byte = metasortcd / 8;
        ms_bit  = metasortcd % 8;
        const_ms_NODE[ms_byte] |= 1 << ms_bit; 
      }

 
    const_ms_TERM = (MetaSort) calloc(metasort_length,sizeof(char));
    
    if( !const_ms_TERM )
    {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
    }

      for(i = 1;i <= number(_Production_);i++)
      {
        prod = element(i,_Production_);

        if(is(prod,_ClassProd_)) continue;

        maxsortcd = prodcd(prod);

        if(maxsortcd == MAXSORTCD_NODE)  continue;
        if(maxsortcd == MAXSORTCD_TERM)  continue;
        if(maxsortcd == MAXSORTCD_POINT) continue;
        if(maxsortcd == MAXSORTCD_NIL){
           metasort_by_prod(FALSE,prod,const_ms_NIL);
           continue;
        }

        metasortcd = (maxsortcd < 0) ? metasort_length * 8 + maxsortcd :
                                       maxsortcd;

        ms_byte = metasortcd / 8;
        ms_bit  = metasortcd % 8;
        const_ms_TERM[ms_byte] |= 1 << ms_bit;
      }


      numofsorts  =   number(_PredeclProd_) - 2 + number(_TupelProd_)
                    + number(_ListProd_);
      numofsorts +=   numofsorts - 2;

      MetaMax = (meta2max_table) calloc(numofsorts,sizeof(struct meta2max_table_entry));

      if( !MetaMax )
      {
       fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
       exit( EXIT_FAILURE );
      }

      /* compute metasort -> maxsort table */

      for(i = 1; i <= number(_Production_); i++)
      {
        p = element(i, _Production_);

        metasort_by_prod(FALSE,p,const_ms_UNIV);
        metasort_by_prod(TRUE,p,const_ms_UNIV);

        if(!strcmp(IDSTR(son(1,p)),"Char"))
	  metasort_by_prod(FALSE,p,const_ms_CHAR);

        if(!strcmp(IDSTR(son(1,p)),"Int"))
	  metasort_by_prod(FALSE,p,const_ms_INT);

        if(!strcmp(IDSTR(son(1,p)),"String"))
	  metasort_by_prod(FALSE,p,const_ms_STRING);

        if(!strcmp(IDSTR(son(1,p)),"Ident"))
	  metasort_by_prod(FALSE,p,const_ms_IDENT);

        if(!strcmp(IDSTR(son(1,p)),"Bool"))
	  metasort_by_prod(FALSE,p,const_ms_BOOL);

        if(!strcmp(IDSTR(son(1,p)),"Point"))
	  metasort_by_prod(FALSE,p,const_ms_POINT);

        if(!strcmp(IDSTR(son(1,p)),"PredeclSort"))
	  metasort_by_prod(FALSE,p,const_ms_PREDECLSORT);

        if(!strcmp(IDSTR(son(1,p)),"ClassSort"))
	  metasort_by_prod(FALSE,p,const_ms_CLASSSORT);

        if(!strcmp(IDSTR(son(1,p)),"TupelSort"))
	  metasort_by_prod(FALSE,p,const_ms_TUPLESORT);

        if(!strcmp(IDSTR(son(1,p)),"ListSort"))
	  metasort_by_prod(FALSE,p,const_ms_LISTSORT);

        if(!strcmp(IDSTR(son(1,p)),"NodeSort"))
	  metasort_by_prod(FALSE,p,const_ms_NODESORT);


        /* generate maxsortcd -> Prod@ table */

        if(prodcd(p) == MAXSORTCD_NODE || prodcd(p) == MAXSORTCD_TERM) 
          continue;

        if(is(p,_ClassProd_)) continue;

        M = (MetaSort) calloc(metasort_length,sizeof(char));

        if( !M )
        {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
        }

        for(j = 0; j < metasort_length; j++)
   
           M[j] = 0;

        metasort_by_prod(FALSE,p,M); 

        /* in Tabelle eintragen */

        MetaMax[entry_cnt].metasort  = M;
        MetaMax[entry_cnt].maxsortcd = prodcd(p);

        entry_cnt++;

        if(is_termsort(prodcd(p)))
        {

          M = (MetaSort) calloc(metasort_length,sizeof(char));

          if( !M )
          {
            fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
            exit( EXIT_FAILURE );
          }

          for(j = 0; j < metasort_length; j++)
   
             M[j] = 0;

          metasort_by_prod(TRUE,p,M); 

          /* in Tabelle eintragen */

          MetaMax[entry_cnt].metasort  = M;
          MetaMax[entry_cnt].maxsortcd = mk_nodesortcd(prodcd(p));

          entry_cnt++;

        }

      }


      ms_union(const_ms_TERMSORT,
               const_ms_CLASSSORT,
               const_ms_TERMSORT);
      ms_union(const_ms_TERMSORT,
               const_ms_TUPLESORT,
               const_ms_TERMSORT);
      ms_union(const_ms_TERMSORT,
               const_ms_LISTSORT,
               const_ms_TERMSORT);
      ms_union(const_ms_TERMSORT,
               const_ms_PREDECLSORT,
               const_ms_TERMSORT);

      ms_union(const_ms_CIS,
               const_ms_TERMSORT,
               const_ms_CIS);
      ms_union(const_ms_CIS,
               const_ms_NODESORT,
               const_ms_CIS);
      ms_union(const_ms_CIS,
               const_ms_NIL,
               const_ms_CIS);
      ms_union(const_ms_CIS,
               const_ms_INT,
               const_ms_CIS);
      ms_union(const_ms_CIS,
               const_ms_CHAR,
               const_ms_CIS);

}

