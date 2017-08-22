
#include "stdio.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "max_spec.h"
#include "max_metasort.h"
#include "max_typecheck.h"

#ifdef SUNOS_LIB_PROTOTYPES
#define bcopy(quelle,ziel,len) memmove(ziel,quelle,len)
#define bzero(sp,len) memset(sp,0,len)
#endif


/* globals */
extern int metasort_length;
extern int numofsorts;
extern meta2max_table MetaMax;
extern MetaSort const_ms_UNIV;
extern MetaSort const_ms_NIL;
extern MetaSort const_ms_NODE;
extern MetaSort const_ms_BOOL;
extern MetaSort const_ms_INT;
extern MetaSort const_ms_STRING;
extern MetaSort const_ms_IDENT;
extern MetaSort const_ms_POINT;
extern MetaSort const_ms_NODESORT;
extern MetaSort const_ms_TERMSORT;
extern MetaSort const_ms_ROOT;

/* functions */
void sigma_init();

MetaSort sigma_true();
MetaSort sigma_false();
MetaSort sigma_root();
MetaSort sigma_fath();
MetaSort fathsorts();
MetaSort sigma_lbroth();
MetaSort lbrothsorts();
MetaSort sigma_rbroth();
MetaSort rbrothsorts();
MetaSort sigma_son();
MetaSort sonsorts();
MetaSort sonsorts_path();
MetaSort sigma_numsons();
MetaSort sigma_front();
MetaSort sigma_back();
MetaSort sigma_appfront();
MetaSort sigma_appback();
MetaSort sigma_conc();
MetaSort sigma_subterm();
MetaSort subtermsorts();
MetaSort sigma_numsubterms();
MetaSort sigma_term();
MetaSort sigma_before();
MetaSort sigma_after();
MetaSort sigma_node();
MetaSort sigma_idtos();
MetaSort sigma_sort();
MetaSort sigma_index();
MetaSort sigma_element();
MetaSort sigma_number();


long lhs_size, rhs_size;
long * rhs_num;
long * submaxsorts_num;
ELEMENT * lhs;
ELEMENT ** rhs;
ELEMENT ** submaxsorts;

Boolean * vis_fath;
MetaSort  lut_fath;
Boolean * vis_rbroth;
MetaSort  lut_rbroth;
Boolean * vis_lbroth;
MetaSort  lut_lbroth;
Boolean * vis_son0;
MetaSort  lut_son0;

#define RHS_SCD(sortid, scd)  (is(sortid, _NodeSortId_) ? -scd : (scd < 0) ? rhs_size + scd : scd)
#define LHS_SCD(scd)          ((scd > 0) ? scd : lhs_size + scd)

void sigma_init()
{
 long i,j,k,bound,scd,index,arr_cnt;
 ELEMENT prod, rhs_prod;
 ELEMENT * subsorts;
 MetaSort tmp_ms;
 Boolean skip;
 long num_termsorts;


 lhs_size = number(_Production_) + 1; 
 rhs_size = number(_Production_) * 2 + 1;

 lhs = (ELEMENT *) calloc(lhs_size,sizeof(ELEMENT));

 if( !lhs )
 {
  fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
  exit( EXIT_FAILURE );
 }

 rhs = (ELEMENT **) calloc(rhs_size,sizeof(ELEMENT *));

 if( !rhs )
 {
  fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
  exit( EXIT_FAILURE );
 }
 
 rhs_num = (long *) calloc(rhs_size,sizeof(long));

 if( !rhs_num )
 {
  fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
  exit( EXIT_FAILURE );
 }
 
 submaxsorts = (ELEMENT **) calloc(number(_ClassProd_) + 1,sizeof(ELEMENT *));

 if( !submaxsorts )
 {
  fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
  exit( EXIT_FAILURE );
 }
 
 submaxsorts_num = (long *) calloc(number(_ClassProd_) + 1,sizeof(long));

 if( !submaxsorts_num )
 {
  fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
  exit( EXIT_FAILURE );
 }
 
 for(i = 0; i < rhs_size; i++)
 {
  rhs_num[i] = 0; 

  rhs[i] = (ELEMENT *) calloc(lhs_size,sizeof(ELEMENT));
  
  if( !rhs[i] )
  {
   fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
   exit( EXIT_FAILURE );
  }
 
 }

 for(i = 0; i <= number(_ClassProd_); i++)
 {
  submaxsorts_num[i] = 0; 

  submaxsorts[i] = (ELEMENT *) calloc(rhs_size,sizeof(ELEMENT));
  
  if( !submaxsorts[i] )
  {
   fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
   exit( EXIT_FAILURE );
  }
 
 }

 tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

 if(!tmp_ms)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
   exit( EXIT_FAILURE );
 }
 
 subsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if(!subsorts)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
   exit( EXIT_FAILURE );
 }

 bound = number(_Production_);

 for(i = 1; i <= bound; i++)
 {

  prod = element(i,_Production_);

  switch(sort(prod))
  {

   case _PredeclProd_ :
			lhs[LHS_SCD(prodcd(prod))] = prod;

      			break;

   case _ListProd_    :
			lhs[LHS_SCD(prodcd(prod))] = prod;

                        rhs_prod = fath(decl(son(2,prod)));

                        if(!is(rhs_prod, _ClassProd_))
                        {

 		 	 scd = prodcd(fath(decl(son(2,prod))));
                         index = RHS_SCD(son(2,prod),scd); 

                         skip = FALSE;

                         for(k = 0; k < rhs_num[index]; k++)

                            if( rhs[index][k] == prod ) { skip = TRUE; break; }

                         if(!skip)
                         {
			   rhs[index][rhs_num[index]] = prod;
                       	   rhs_num[index]++;
                         }

                        }

                        else
                        {

                         bzero(tmp_ms,metasort_length);

                         metasort_by_prod(FALSE,rhs_prod,tmp_ms);

                         for(k = 0; k <= numofsorts; k++)
     
                           subsorts[k] = ENDOFARR;

                         maxsorts_by_metasort(tmp_ms,subsorts);
 
                         arr_cnt = 0;
                         while(subsorts[arr_cnt++] != ENDOFARR) 
                         {

                          scd = subsorts[arr_cnt - 1];
			  index = (scd >= 0) ? scd : rhs_size + scd;

                          skip = FALSE;

                          for(k = 0; k < rhs_num[index]; k++)

                             if( rhs[index][k] == prod ) { skip = TRUE; break; }

                          if(!skip)
                          {
			    rhs[index][rhs_num[index]] = prod;
                       	    rhs_num[index]++;
                          }

                         }

                        }

			break;

   case _TupelProd_   :
			lhs[LHS_SCD(prodcd(prod))] = prod;

			for(k = 1; k <= numsons(son(2,prod)); k++)
			{

                          rhs_prod = fath(decl(son(k,son(2,prod))));

                          if(!is(rhs_prod, _ClassProd_))
                          {
			   scd = prodcd(rhs_prod);
			   index = RHS_SCD(son(k,son(2,prod)),scd);

                           skip = FALSE;

                           for(j = 0; j < rhs_num[index]; j++)

                              if( rhs[index][j] == prod ) { skip = TRUE; break; }

                           if(!skip)
                           {
			     rhs[index][rhs_num[index]] = prod;
                       	     rhs_num[index]++;
                           }

        		  }

                          else

                          {

                           bzero(tmp_ms,metasort_length);

                           metasort_by_prod(FALSE,rhs_prod,tmp_ms);

                           for(j = 0; j <= numofsorts; j++)
     
                             subsorts[j] = ENDOFARR;

                           maxsorts_by_metasort(tmp_ms,subsorts);
 
                           arr_cnt = 0;
                           while(subsorts[arr_cnt++] != ENDOFARR) 
                           {

                            scd = subsorts[arr_cnt - 1];
			    index = (scd >= 0) ? scd : rhs_size + scd;

                            skip = FALSE;

                            for(j = 0; j < rhs_num[index]; j++)

                               if( rhs[index][j] == prod ) { skip = TRUE; break; }

                            if(!skip)
                            {
			      rhs[index][rhs_num[index]] = prod;
                       	      rhs_num[index]++;
                            }

                           }

                          }

			}

			break;

   case _ClassProd_   :
			bzero(tmp_ms,metasort_length);

                        metasort_by_prod(FALSE,prod,tmp_ms);

                        for(k = 0; k <= numofsorts; k++)
     
                          subsorts[k] = ENDOFARR;

                        maxsorts_by_metasort(tmp_ms,subsorts);
 
                        arr_cnt = 0;
                        while(subsorts[arr_cnt++] != ENDOFARR) 
                        {

                         submaxsorts[index(prod,_ClassProd_)][submaxsorts_num[index(prod,_ClassProd_)]]
                         = subsorts[arr_cnt - 1];

                         submaxsorts_num[index(prod,_ClassProd_)]++;

                        }


                        break;

   default:
		 	fprintf(stderr,"\n***** Error: unknown ProdSort\n");
                        exit( EXIT_FAILURE );	
			break;

  }

 }


 /* lookup-tables */

 num_termsorts =  number(_PredeclProd_) + number(_ClassProd_)
                + number(_ListProd_) + number(_TupelProd_);

 lut_fath = (MetaSort) malloc((num_termsorts + 1) * metasort_length);

 if(!lut_fath)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate lut_fath\n");
   exit( EXIT_FAILURE );
 }   

 bzero(lut_fath,(num_termsorts + 1) * metasort_length);

 vis_fath = (Boolean *) calloc(num_termsorts + 1,sizeof(Boolean));

 if(!vis_fath)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate vis_fath\n");
   exit( EXIT_FAILURE );
 } 


 lut_rbroth = (MetaSort) malloc((num_termsorts + 1) * metasort_length);

 if(!lut_rbroth)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate lut_rbroth\n");
   exit( EXIT_FAILURE );
 }

 bzero(lut_rbroth,(num_termsorts + 1) * metasort_length);

 vis_rbroth = (Boolean *) calloc(num_termsorts + 1,sizeof(Boolean));

 if(!vis_rbroth)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate vis_rbroth\n");
   exit( EXIT_FAILURE );
 }


 lut_lbroth = (MetaSort) malloc((num_termsorts + 1) * metasort_length);

 if(!lut_lbroth)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate lut_lbroth\n");
   exit( EXIT_FAILURE );
 }   

 bzero(lut_lbroth,(num_termsorts + 1) * metasort_length);

 vis_lbroth = (Boolean *) calloc(num_termsorts + 1,sizeof(Boolean));

 if(!vis_lbroth)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate vis_lbroth\n");
   exit( EXIT_FAILURE );
 } 


 lut_son0 = (MetaSort) malloc((num_termsorts + 1) * metasort_length);

 if(!lut_son0)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate lut_son0\n");
   exit( EXIT_FAILURE );
 }   

 bzero(lut_son0,(num_termsorts + 1) * metasort_length);

 vis_son0 = (Boolean *) calloc(num_termsorts + 1,sizeof(Boolean));

 if(!vis_son0)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate vis_son0\n");
   exit( EXIT_FAILURE );
 } 

 free(subsorts);
 free(tmp_ms);

}


/*------------------------------ SIGMA_PATH ------------------------------*/

MetaSort sigpath_fath(MetaSort M, MetaSort target)
{
 return sigma_fath( M, target );
}


MetaSort sigpath_lbroth(MetaSort M, MetaSort target)
{
 return sigma_lbroth( M, target );
}

 
MetaSort sigpath_rbroth(MetaSort M, MetaSort target)
{
 return sigma_rbroth( M, target );
}


MetaSort sigpath_son(MetaSort M, int sonr, int l, int r, int num_it, int num_ast, MetaSort target)
{

 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target,metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      sonsorts_path( mk_termsortcd(maxsorts[arr_cnt - 1]), sonr, l, r, num_it, num_ast, target );

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}



/*------------------------------ true() ----------------------------------*/

MetaSort sigma_true(MetaSort target)
{
 bcopy(const_ms_BOOL,target,metasort_length);
 return target;
}


/*------------------------------ false() ----------------------------------*/

MetaSort sigma_false(MetaSort target)
{
 bcopy(const_ms_BOOL,target,metasort_length);
 return target;
}


/*------------------------------ root() ----------------------------------*/

MetaSort sigma_root(MetaSort target)
{
 bcopy(const_ms_ROOT,target,metasort_length);
 return target;
}


/*------------------------------ fath() ----------------------------------*/

MetaSort sigma_fath(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target,metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      fathsorts(mk_termsortcd(maxsorts[arr_cnt - 1]),target);

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);

 if(is_subset(const_ms_ROOT,M))

   ms_union(const_ms_NIL,target,target);

 return target;

}


MetaSort fathsorts(ELEMENT maxsortcd, MetaSort target)
{
 ELEMENT prod;
 int i,j;
 MetaSort tmp_ms;
 Boolean skip;
 long scd;


  if(vis_fath[-maxsortcd])
  {
     ms_union(target,&(lut_fath[(-maxsortcd) * metasort_length]),
              target);
     return target;
  }


  scd = (maxsortcd > 0) ? maxsortcd : rhs_size + maxsortcd;

  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  for(i = 0; i < rhs_num[scd]; i++)
  {

   prod = rhs[scd][i];
  
   if(is(prod, _TupelProd_))
   {

    skip = FALSE;

    for(j = 1; j <= numsons(son(2,prod)); j++)
    
      if(is(son(j,son(2,prod)),_NodeSortId_)) {skip = TRUE; break;}

    if(skip) continue;

   }


   if(is(prod, _ListProd_))
   
     if(is(son(2,prod),_NodeSortId_)) continue;

   bzero(tmp_ms, metasort_length); 

   metasort_by_prod(TRUE,prod,tmp_ms);
   ms_union(target,tmp_ms,target);
   ms_union(&(lut_fath[(-maxsortcd) * metasort_length]),
            tmp_ms,
            &(lut_fath[(-maxsortcd) * metasort_length]));

  }
 
  free(tmp_ms);

  vis_fath[-maxsortcd] = TRUE;

  return target;

}

/*------------------------------ lbroth() ----------------------------------*/

MetaSort sigma_lbroth(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      lbrothsorts(mk_termsortcd(maxsorts[arr_cnt - 1]),target);

 }

 free(maxsorts);
 return target;
}


MetaSort lbrothsorts(ELEMENT maxsortcd, MetaSort target)
{
 ELEMENT prod,deflist,brothprod;
 int i,j,k;
 MetaSort tmp_ms;
 Boolean skip,ok,empty;
 long scd;


  if(vis_lbroth[-maxsortcd])
  {
     ms_union(target,&(lut_lbroth[(-maxsortcd) * metasort_length]),
              target);
     return target;
  }


  scd = (maxsortcd > 0) ? maxsortcd : rhs_size + maxsortcd;

  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  empty = TRUE;

  for(i = 0; i < rhs_num[scd]; i++)
  {

   prod = rhs[scd][i];

   if(is(prod, _TupelProd_))
   {

    empty = FALSE;

    skip = FALSE;

    for(j = 1; j <= numsons(son(2,prod)); j++)
    
      if(is(son(j,son(2,prod)),_NodeSortId_)) {skip = TRUE; break;}

    if(skip) continue;

    for(j = 1; j <= numsons(son(2,prod)); j++)
    {
        deflist = idtodecls(term(son(1,son(j,son(2,prod)))));

        brothprod = fath(subterm(1,deflist));

        if(is(brothprod,_ClassProd_))
        {

          ok = FALSE;

          for(k = 0; k < submaxsorts_num[index(brothprod,_ClassProd_)];k++)

             if(maxsortcd == submaxsorts[index(brothprod,_ClassProd_)][k])
             {
              ok = TRUE;
              break;
             }  

        }

        else

         ok = (prodcd(brothprod) == maxsortcd ? TRUE : FALSE);


        if(ok)
        {

          if(lbroth(son(j,son(2,prod))) == nil())
          {
            ms_union(target,const_ms_NIL,target);
            ms_union(&(lut_lbroth[(-maxsortcd) * metasort_length]),
                     const_ms_NIL,
                     &(lut_lbroth[(-maxsortcd) * metasort_length]));
          } 

          else
          {        
           deflist = idtodecls(term(son(1,son(j - 1,son(2,prod)))));

           bzero(tmp_ms,metasort_length);

           metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
           ms_union(target,tmp_ms,target);
           ms_union(&(lut_lbroth[(-maxsortcd) * metasort_length]),
                    tmp_ms,
                    &(lut_lbroth[(-maxsortcd) * metasort_length]));
         
          }

        }

     }
    

   }


   if(is(prod, _ListProd_))
   {
     empty = FALSE;

     if(is(son(2,prod),_NodeSortId_)) continue;

     deflist = idtodecls(term(son(1,son(2,prod))));

     bzero(tmp_ms,metasort_length);

     metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
     ms_union(target,tmp_ms,target);
     ms_union(target,const_ms_NIL,target);
     ms_union(&(lut_lbroth[(-maxsortcd) * metasort_length]),
              tmp_ms,
              &(lut_lbroth[(-maxsortcd) * metasort_length]));
     ms_union(&(lut_lbroth[(-maxsortcd) * metasort_length]),
              const_ms_NIL,
              &(lut_lbroth[(-maxsortcd) * metasort_length]));
         
   }
 
 }

 free(tmp_ms);

 if(empty){

    ms_union(target,const_ms_NIL,target);

    ms_union(&(lut_lbroth[(-maxsortcd) * metasort_length]),
             const_ms_NIL,
             &(lut_lbroth[(-maxsortcd) * metasort_length]));
        
 }

 vis_lbroth[-maxsortcd] = TRUE;

 return target;
}


/*------------------------------ rbroth() ----------------------------------*/

MetaSort sigma_rbroth(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      rbrothsorts(mk_termsortcd(maxsorts[arr_cnt - 1]),target);

 }

 free(maxsorts);
 return target;
}


MetaSort rbrothsorts(ELEMENT maxsortcd, MetaSort target)
{
 ELEMENT prod,deflist,brothprod;
 int i,j,k;
 MetaSort tmp_ms;
 Boolean skip,ok,empty;
 long scd;

  if(vis_rbroth[-maxsortcd])
  {
     ms_union(target,&(lut_rbroth[(-maxsortcd) * metasort_length]),
              target);
     return target;
  }


  scd = (maxsortcd > 0) ? maxsortcd : rhs_size + maxsortcd;

  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  empty = TRUE;

  for(i = 0; i < rhs_num[scd]; i++)
  {

   prod = rhs[scd][i];
  
   if(is(prod, _TupelProd_))
   {
    
    empty = FALSE;

    skip = FALSE;

    for(j = 1; j <= numsons(son(2,prod)); j++)
    
      if(is(son(j,son(2,prod)),_NodeSortId_)) {skip = TRUE; break;}

    if(skip) continue;

    for(j = 1; j <= numsons(son(2,prod)); j++)
    {
        deflist = idtodecls(term(son(1,son(j,son(2,prod)))));

        brothprod = fath(subterm(1,deflist));

        if(is(brothprod,_ClassProd_))
        {

          ok = FALSE;

          for(k = 0; k < submaxsorts_num[index(brothprod,_ClassProd_)];k++)

             if(maxsortcd == submaxsorts[index(brothprod,_ClassProd_)][k])
             {
              ok = TRUE;
              break;
             }

        }

        else

         ok = (prodcd(brothprod) == maxsortcd ? TRUE : FALSE);


        if(ok)
        {

          if(rbroth(son(j,son(2,prod))) == nil())
          {
            ms_union(target,const_ms_NIL,target);
            ms_union(&(lut_rbroth[(-maxsortcd) * metasort_length]),
                     const_ms_NIL,
                     &(lut_rbroth[(-maxsortcd) * metasort_length]));
          }

          else
          {        
           deflist = idtodecls(term(son(1,son(j + 1,son(2,prod)))));

           bzero(tmp_ms,metasort_length);

           metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
           ms_union(target,tmp_ms,target);
           ms_union(&(lut_rbroth[(-maxsortcd) * metasort_length]),
                    tmp_ms,
                    &(lut_rbroth[(-maxsortcd) * metasort_length]));
         

         
          }

        }

     }
    

   }


   if(is(prod, _ListProd_))
   {
     empty = FALSE;

     if(is(son(2,prod),_NodeSortId_)) continue;

     deflist = idtodecls(term(son(1,son(2,prod))));

     bzero(tmp_ms,metasort_length);

     metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
     ms_union(target,tmp_ms,target);
     ms_union(target,const_ms_NIL,target);
     ms_union(&(lut_rbroth[(-maxsortcd) * metasort_length]),
              tmp_ms,
              &(lut_rbroth[(-maxsortcd) * metasort_length]));
     ms_union(&(lut_rbroth[(-maxsortcd) * metasort_length]),
              const_ms_NIL,
              &(lut_rbroth[(-maxsortcd) * metasort_length]));

   }
 
 }

 free(tmp_ms);

 if(empty){

    ms_union(target,const_ms_NIL,target);

    ms_union(&(lut_rbroth[(-maxsortcd) * metasort_length]),
             const_ms_NIL,
             &(lut_rbroth[(-maxsortcd) * metasort_length]));

 }

 vis_rbroth[-maxsortcd] = TRUE;

 return target;
}


/*------------------------------ son() ----------------------------------*/

MetaSort sigma_son(MetaSort N, MetaSort ith, ELEMENT sonr, MetaSort target)
{
 ELEMENT * maxsorts;
 int index,arr_cnt = 0;

 bzero(target, metasort_length);

 if(is(sonr, _IntConst_))
 { 
   index = etoi(term(son(1,sonr)));
   if(index == 0)
   {
    ms_union(target,const_ms_NIL,target);
    return target;
   }
 }

 else

   index = 0; /* all */


 if(!(is_subset(const_ms_INT,ith) && is_subset(ith,const_ms_INT)))
 {
  if(is_subset(const_ms_INT,ith))

    ms_union(target,const_ms_NIL,target);

  else
  {
    ms_union(target,const_ms_NIL,target);
    return target;
  }

 }

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(N,maxsorts);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      sonsorts( mk_termsortcd(maxsorts[arr_cnt - 1]), index , target );

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


MetaSort sonsorts(ELEMENT maxsortcd, int sonr, MetaSort target)
{
 ELEMENT prod,deflist;
 int i,j;
 MetaSort tmp_ms;
 Boolean skip;
 long scd;

  if(sonr == 0 && vis_son0[-maxsortcd])
  {
     ms_union(target,&(lut_son0[(-maxsortcd) * metasort_length]),
              target);
     return target;
  }


  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  scd = (maxsortcd > 0) ? maxsortcd : lhs_size + maxsortcd;
  
  prod = lhs[scd];
  
  if(is(prod, _TupelProd_))
  {

   skip = FALSE;

   for(j = 1; j <= numsons(son(2,prod)); j++)
    
     if(is(son(j,son(2,prod)),_NodeSortId_)) {skip = TRUE; break;}

   if(skip)
   {
     ms_union(target,const_ms_NIL,target);
     ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
              const_ms_NIL,
              &(lut_son0[(-maxsortcd) * metasort_length]));

     vis_son0[-maxsortcd] = TRUE;

     free(tmp_ms);
     return target;
   }

   if(sonr != 0)
   {

     if(sonr > numsons(son(2,prod)) || sonr < - numsons(son(2,prod)))
     {
       ms_union(target,const_ms_NIL,target);
       free(tmp_ms);
       return target;
     }

     deflist = idtodecls(term(son(1,son(sonr,son(2,prod)))));

     bzero(tmp_ms,metasort_length);

     metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
     ms_union(target,tmp_ms,target);
     free(tmp_ms);
     return target;

   }

   else

   {

     ms_union(target,const_ms_NIL,target);
     ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
              const_ms_NIL,
              &(lut_son0[(-maxsortcd) * metasort_length]));

     for(j = 1; j <= numsons(son(2,prod)); j++)
     {

        deflist = idtodecls(term(son(1,son(j,son(2,prod)))));
        
        bzero(tmp_ms,metasort_length);

        metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
        ms_union(target,tmp_ms,target);
        ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
                 tmp_ms,
                 &(lut_son0[(-maxsortcd) * metasort_length]));

     }

     free(tmp_ms);

     vis_son0[-maxsortcd] = TRUE;

     return target;

   }

  }

  if(is(prod, _ListProd_))
  {
   
    if(is(son(2,prod),_NodeSortId_)) 
    {
       ms_union(target,const_ms_NIL,target);
       ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
                const_ms_NIL,
                &(lut_son0[(-maxsortcd) * metasort_length]));

       vis_son0[-maxsortcd] = TRUE;

       free(tmp_ms);
       return target;
    }
    
    deflist = idtodecls(term(son(1,son(2,prod))));
             
    bzero(tmp_ms,metasort_length);

    metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
    ms_union(target,tmp_ms,target);
    ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
             tmp_ms,
             &(lut_son0[(-maxsortcd) * metasort_length]));

    ms_union(target,const_ms_NIL,target);
    ms_union(&(lut_son0[(-maxsortcd) * metasort_length]),
             const_ms_NIL,
             &(lut_son0[(-maxsortcd) * metasort_length]));

    vis_son0[-maxsortcd] = TRUE;

    free(tmp_ms);
    return target;
        
  }   

 
  free(tmp_ms);

  ms_union(target,const_ms_NIL,target);
  return target;

}


MetaSort sonsorts_path(ELEMENT maxsortcd, int sonr, int l, int r, int num_it, int num_ast, MetaSort target)
{
 ELEMENT prod,deflist;
 int i,j,n;
 MetaSort tmp_ms;
 Boolean skip,empty;
 long scd;

  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  scd = (maxsortcd > 0) ? maxsortcd : lhs_size + maxsortcd;
  
  prod = lhs[scd];
  
  if(is(prod, _TupelProd_))
  {

   skip = FALSE;

   for(j = 1; j <= numsons(son(2,prod)); j++)
    
     if(is(son(j,son(2,prod)),_NodeSortId_)) {skip = TRUE; break;}

   if(skip)
   {
     ms_union(target,const_ms_NIL,target);
     free(tmp_ms);
     return target;
   }

   if(sonr != 0)
   {

     n = numsons(son(2,prod));

     if( (n < num_it)  || ( n > num_it && num_ast == 0) )
     {
       ms_union(target,const_ms_NIL,target);
       free(tmp_ms);
       return target;
     }

     if(sonr > n || sonr < - n)
     {
       ms_union(target,const_ms_NIL,target);
       free(tmp_ms);
       return target;
     }

     if(   (sonr > 0 && l <= sonr && sonr <= n + r + 1 )
	|| (sonr < 0 && -(n - l + 1) <= sonr && sonr <= r) )
     {
        deflist = idtodecls(term(son(1,son(sonr,son(2,prod)))));

        bzero(tmp_ms,metasort_length);

        metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
        ms_union(target,tmp_ms,target);
        free(tmp_ms);
        return target;
     }

     else

     {
        ms_union(target,const_ms_NIL,target);
        free(tmp_ms);
        return target;
     }

   }

   else /* sonr == 0 */

   {

     empty = TRUE;

     for(j = l; j <= numsons(son(2,prod)) + r + 1; j++)
     {

        empty = FALSE;

        deflist = idtodecls(term(son(1,son(j,son(2,prod)))));
        
        bzero(tmp_ms,metasort_length);

        metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
        ms_union(target,tmp_ms,target);

     }

     if(empty)

       ms_union(target,const_ms_NIL,target);

     free(tmp_ms);
     return target;

   }

  }

  if(is(prod, _ListProd_))
  {
   
    if(is(son(2,prod),_NodeSortId_)) 
    {
       ms_union(target,const_ms_NIL,target);
       free(tmp_ms);
       return target;
    }
    
    deflist = idtodecls(term(son(1,son(2,prod))));
             
    bzero(tmp_ms,metasort_length);

    metasort_by_prod(TRUE,fath(subterm(1,deflist)),tmp_ms);
    ms_union(target,tmp_ms,target);
    ms_union(target,const_ms_NIL,target);

    free(tmp_ms);
    return target;
        
  }   

 
  free(tmp_ms);

  ms_union(target,const_ms_NIL,target);
  return target;

}


/*------------------------------ numsons() ----------------------------------*/

MetaSort sigma_numsons(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_nodesort(maxsorts[arr_cnt - 1]))

      ms_union(const_ms_INT,target,target);

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


/*------------------------------ front() ----------------------------------*/

MetaSort sigma_front(MetaSort l, MetaSort target)
{
 ELEMENT * maxsorts;
 ELEMENT prod;
 MetaSort M;
 int i,arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(l,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_termsort(maxsorts[arr_cnt - 1]))
    {
      
     for(i = 1; i <= number(_ListProd_); i++)
     {

       prod = element(i,_ListProd_);

       if( maxsorts[arr_cnt - 1] == prodcd(prod) )
       {
     
         M = (MetaSort) calloc(metasort_length,sizeof(char));

         if( !M )
         {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
         }

         metasort_by_prod(FALSE,prod,M);
         ms_union(target,M,target);
         free(M);

         break;

       }


     }


   }

 }

 ms_union(const_ms_NIL,target,target);
 free(maxsorts);
 return target;

}


/*------------------------------ back() ----------------------------------*/

MetaSort sigma_back(MetaSort l, MetaSort target)
{
 ELEMENT * maxsorts;
 ELEMENT prod;
 MetaSort M;
 int i,arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(l,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_termsort(maxsorts[arr_cnt - 1]))
    {
      
     for(i = 1; i <= number(_ListProd_); i++)
     {

       prod = element(i,_ListProd_);

       if( maxsorts[arr_cnt - 1] == prodcd(prod) )
       {

         M = (MetaSort) calloc(metasort_length,sizeof(char));

         if( !M )
         {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
         }

         metasort_by_prod(FALSE,prod,M);
         ms_union(target,M,target);
         free(M);

         break;

       }


     }


   }

 }

 ms_union(const_ms_NIL,target,target);
 free(maxsorts);
 return target;

}


/*------------------------------ appfront() ----------------------------------*/

MetaSort sigma_appfront(MetaSort e, MetaSort l, MetaSort target)
{
 ELEMENT * maxsorts;
 ELEMENT prod;
 Boolean full,l_list;
 MetaSort M;
 int i,arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(l,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {
    l_list = FALSE;

    if(is_termsort(maxsorts[arr_cnt - 1]))
    {
      
     for(i = 1; i <= number(_ListProd_); i++)
     {

       prod = element(i,_ListProd_);

       if( maxsorts[arr_cnt - 1] == prodcd(prod) )
       {
  
         l_list = TRUE;

         M = (MetaSort) calloc(metasort_length,sizeof(char));

         if( !M )
         {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
         }

         metasort_by_sortid((is(son(2,prod), _TermSortId_) ? FALSE : TRUE),term(son(1,son(2,prod))),M);
       
         if(!is_subset(e,M))
         {
            bzero(M,metasort_length);
            metasort_by_prod(FALSE,prod,M);
            ms_union(M,target,target);
            ms_union(target,const_ms_NIL,target);
         }

         else
         {
            bzero(M,metasort_length);
            metasort_by_prod(FALSE,prod,M);
            ms_union(M,target,target);
         }
          

         free(M);
         break;

       }


     }


     if(!l_list)

       ms_union(target,const_ms_NIL,target);

    }

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


/*------------------------------ appback() ----------------------------------*/

MetaSort sigma_appback(MetaSort l, MetaSort e, MetaSort target)
{
 ELEMENT * maxsorts;
 ELEMENT prod;
 Boolean full,l_list;
 MetaSort M;
 int i,arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(l,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {
    l_list = FALSE;

    if(is_termsort(maxsorts[arr_cnt - 1]))
    {
      
     for(i = 1; i <= number(_ListProd_); i++)
     {

       prod = element(i,_ListProd_);

       if( maxsorts[arr_cnt - 1] == prodcd(prod) )
       {
  
         l_list = TRUE;

         M = (MetaSort) calloc(metasort_length,sizeof(char));

         if( !M )
         {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
         }

         metasort_by_sortid((is(son(2,prod), _TermSortId_) ? FALSE : TRUE),term(son(1,son(2,prod))),M);

         if(!is_subset(e,M))
         {
             bzero(M,metasort_length);
             metasort_by_prod(FALSE,prod,M);
             ms_union(M,target,target);
             ms_union(target,const_ms_NIL,target);
         }

         else
         {
             bzero(M,metasort_length);
             metasort_by_prod(FALSE,prod,M);
             ms_union(M,target,target);
         }


         free(M);
         break;

       }


     }

     if(!l_list)

       ms_union(target,const_ms_NIL,target);

    }

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


/*------------------------------ conc() ----------------------------------*/

MetaSort sigma_conc(MetaSort l1, MetaSort l2, MetaSort target)
{
 ELEMENT * maxsorts;
 ELEMENT prod;
 Boolean l1_list;
 MetaSort M;
 int i,arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(l1,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    l1_list = FALSE;

    if(is_termsort(maxsorts[arr_cnt - 1]))
    {
      
     for(i = 1; i <= number(_ListProd_); i++)
     {

       prod = element(i,_ListProd_);

       if( maxsorts[arr_cnt - 1] == prodcd(prod) )
       {
  
         l1_list = TRUE;

         M = (MetaSort) calloc(metasort_length,sizeof(char));

         if( !M )
         {
          fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
          exit( EXIT_FAILURE );
         }

         metasort_by_prod(FALSE,prod,M);
           
         if(!(is_subset(M, l2) && is_subset(l2, M)))
         {
          if(is_subset(M, l2))
          {
            ms_union(target,M,target);
            ms_union(target,const_ms_NIL,target);
          }

          else
          
            ms_union(target,const_ms_NIL,target);

         }

         else
  
            ms_union(target,M,target);
 
         free(M);
         break;

       }
                   
     }

     if(!l1_list)

       ms_union(target,const_ms_NIL,target);

    }

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


/*------------------------------ subterm() ----------------------------------*/

MetaSort sigma_subterm(MetaSort T, MetaSort ith, ELEMENT subnr, MetaSort target)
{
 ELEMENT * maxsorts;
 int index,arr_cnt = 0;

 bzero(target, metasort_length);

 if(is(subnr, _IntConst_))
 { 
   index = etoi(term(son(1,subnr)));
   if(index == 0)
   {
    ms_union(target,const_ms_NIL,target);
    return target;
   }
 }

 else

   index = 0; /* all */


 if(!(is_subset(const_ms_INT,ith) && is_subset(ith,const_ms_INT)))
 {
  if(is_subset(const_ms_INT,ith))

    ms_union(target,const_ms_NIL,target);

  else
  {
    ms_union(target,const_ms_NIL,target);
    return target;
  }

 }

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(T,maxsorts);

 while(maxsorts[arr_cnt++] != ENDOFARR) 
 {

    if(is_termsort(maxsorts[arr_cnt - 1]))

      subtermsorts( maxsorts[arr_cnt - 1], index, target );

    else

      ms_union(const_ms_NIL,target,target);

 }

 free(maxsorts);
 return target;

}


MetaSort subtermsorts(ELEMENT maxsortcd, int subnr, MetaSort target)
{
 ELEMENT prod,deflist;
 int j;
 MetaSort tmp_ms;
 long scd;

  tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !tmp_ms )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table "); 
    exit( EXIT_FAILURE );
  }

  scd = (maxsortcd > 0) ? maxsortcd : lhs_size + maxsortcd;
  
  prod = lhs[scd];
  
  if(is(prod, _TupelProd_))
  {

   if(subnr != 0)
   {

     if(subnr > numsons(son(2,prod)) || subnr < - numsons(son(2,prod)))
     {
       ms_union(target,const_ms_NIL,target);
       return target;
     }

     deflist = idtodecls(term(son(1,son(subnr,son(2,prod)))));

     metasort_by_prod((is(son(subnr,son(2,prod)), _TermSortId_) ? FALSE : TRUE),fath(subterm(1,deflist)),tmp_ms);
     ms_union(target,tmp_ms,target);
     free(tmp_ms);
     return target;

   }

   else

   {

    ms_union(const_ms_NIL,target,target);

    for(j = 1; j <= numsons(son(2,prod)); j++)
    {

       deflist = idtodecls(term(son(1,son(j,son(2,prod)))));
        
       bzero(tmp_ms,metasort_length);

       metasort_by_prod((is(son(j,son(2,prod)), _TermSortId_) ? FALSE : TRUE),fath(subterm(1,deflist)),tmp_ms);
       ms_union(target,tmp_ms,target);

    }

    free(tmp_ms);
    return target;

   }

  } 


  if(is(prod, _ListProd_))
  {

    deflist = idtodecls(term(son(1,son(2,prod))));
       
    bzero(tmp_ms,metasort_length);

    metasort_by_prod((is(son(2,prod), _TermSortId_) ? FALSE : TRUE),fath(subterm(1,deflist)),tmp_ms);
    ms_union(target,tmp_ms,target);
    free(tmp_ms);
    ms_union(const_ms_NIL,target,target);
    return target;
        
  }

  free(tmp_ms);

  ms_union(const_ms_NIL,target,target);
  return target;

}


/*------------------------------ numsubterms() ----------------------------------*/

MetaSort sigma_numsubterms(MetaSort M, MetaSort target)
{
 
 bzero(target, metasort_length);

 if(is_subset(const_ms_NIL,M))
 {
   ms_union(target,const_ms_INT,target);
   ms_union(target,const_ms_NIL,target);
 }

 else ms_union(target,const_ms_INT,target);

 return target;

}


/*------------------------------ term() ----------------------------------*/

MetaSort sigma_term(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;
 long scd,ms_byte,ms_bit;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR)
 {
    if(is_nodesort(maxsorts[arr_cnt - 1]))
    {

     if(maxsorts[arr_cnt - 1] != MAXSORTCD_NODE)      
       
       scd = metasort_length * 8 - maxsorts[arr_cnt - 1];

     else scd = MAXSORTCD_NODE;

     ms_byte = scd / 8;
     ms_bit  = scd % 8;

     target[ms_byte] |= 1 << ms_bit;

    }

    else ms_union(target,const_ms_NIL,target);
 }


 free(maxsorts);
 return target;

}


/*------------------------------ before() ----------------------------------*/

MetaSort sigma_before(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR)
 {
    if(is_nodesort(maxsorts[arr_cnt - 1]))
   
       ms_union(target,const_ms_POINT,target);
     
    else
    
       ms_union(target,const_ms_NIL,target);
 }


 free(maxsorts);
 return target;

}


/*------------------------------ after() ----------------------------------*/

MetaSort sigma_after(MetaSort M, MetaSort target)
{
 ELEMENT * maxsorts;
 int arr_cnt = 0;

 maxsorts = (ELEMENT *) calloc(numofsorts + 1,sizeof(ELEMENT));

 if( !maxsorts )
 {
      fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
      exit( EXIT_FAILURE );
 }

 maxsorts_by_metasort(M,maxsorts);

 bzero(target, metasort_length);

 while(maxsorts[arr_cnt++] != ENDOFARR)
 {
    if(is_nodesort(maxsorts[arr_cnt - 1]))
   
       ms_union(target,const_ms_POINT,target);
     
    else
    
       ms_union(target,const_ms_NIL,target);
 }


 free(maxsorts);
 return target;

}


/*------------------------------ node() ----------------------------------*/

MetaSort sigma_node(MetaSort M, MetaSort target)
{

 bzero(target, metasort_length);

 if(!(is_subset(const_ms_POINT, M) && is_subset(M, const_ms_POINT)))
 {
   if(is_subset(const_ms_POINT,M))
   {
     ms_union(target,const_ms_NODE,target);
     ms_union(target,const_ms_NIL,target);
   }

   else
          
     ms_union(target,const_ms_NIL,target);

 }

 else
  
   ms_union(target,const_ms_NODE,target);
 
 return target;

}


/*------------------------------ idtos() ----------------------------------*/

MetaSort sigma_idtos(MetaSort M, MetaSort target)
{

 bzero(target, metasort_length);

 if(!(is_subset(const_ms_IDENT, M) && is_subset(M, const_ms_IDENT)))
 {
   if(is_subset(const_ms_IDENT,M))
   {
     ms_union(target,const_ms_STRING,target);
     ms_union(target,const_ms_NIL,target);
   }

   else
          
     ms_union(target,const_ms_NIL,target);

 }

 else
  
   ms_union(target,const_ms_STRING,target);
 
 return target;

}


/*------------------------------ sort() ----------------------------------*/

MetaSort sigma_sort(MetaSort M, MetaSort target)
{

 bzero(target, metasort_length);

 if(!(is_subset(const_ms_NIL, M) && is_subset(M, const_ms_NIL)))
 {
   if(is_subset(const_ms_NIL,M))
   {
     ms_union(target,const_ms_TERMSORT,target);
     ms_union(target,const_ms_NODESORT,target);
     ms_union(target,const_ms_NIL,target);
   }

   else
   {
     ms_union(target,const_ms_TERMSORT,target);
     ms_union(target,const_ms_NODESORT,target);      
   }

 }

 else

   ms_union(target,const_ms_NIL,target);

 return target;

}


/*------------------------------ index() ----------------------------------*/

MetaSort sigma_index(MetaSort EL, MetaSort S, MetaSort target)
{

 bzero(target, metasort_length);

 ms_union(target,const_ms_NIL,target);
 ms_union(target,const_ms_INT,target);

 return target;

}


/*------------------------------ element() ----------------------------------*/

MetaSort sigma_element(MetaSort ith, MetaSort S, MetaSort target)
{

 bzero(target, metasort_length);

 ms_union(target,const_ms_NIL,target);
 ms_union(target,const_ms_UNIV,target);

 return target;

}


/*------------------------------ number() ----------------------------------*/

MetaSort sigma_number(MetaSort S, MetaSort target)
{

 bzero(target, metasort_length);

 ms_union(target,const_ms_NIL,target);
 ms_union(target,const_ms_INT,target);

 return target;

}
