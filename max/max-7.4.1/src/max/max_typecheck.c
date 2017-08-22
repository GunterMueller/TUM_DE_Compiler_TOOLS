
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "max_global.h"
#include "max_spec.h"
#include "max_metasort.h"
#include "max_typecheck.h"

#ifdef SUNOS_LIB_PROTOTYPES
#define bcopy(quelle,ziel,len) memmove(ziel,quelle,len)
#define bzero(sp,len) memset(sp,0,len)
#endif

/* functions */

MetaSort comp_path_type();
MetaSort comp_func_type();
void iteration();
void check_gfp();
void eval_prio();
void typecheck();
void sigma_init();

/* globals */

MetaSort sigma_true();
MetaSort sigma_false();
MetaSort sigma_root();
MetaSort sigma_fath();
MetaSort sigma_lbroth();
MetaSort sigma_rbroth();
MetaSort sigma_son();
MetaSort sigma_numsons();
MetaSort sigma_front();
MetaSort sigma_back();
MetaSort sigma_appfront();
MetaSort sigma_appback();
MetaSort sigma_conc();
MetaSort sigma_subterm();
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

extern struct OPT max_options;

extern long metasort_length;

extern MetaSort const_ms_PREDECLSORT;
extern MetaSort const_ms_CLASSSORT;
extern MetaSort const_ms_TUPLESORT;
extern MetaSort const_ms_LISTSORT;
extern MetaSort const_ms_NODESORT;
extern MetaSort const_ms_TERMSORT;
extern MetaSort const_ms_CHAR;
extern MetaSort const_ms_INT;
extern MetaSort const_ms_STRING;
extern MetaSort const_ms_UNIV;
extern MetaSort const_ms_NODE;
extern MetaSort const_ms_TERM;
extern MetaSort const_ms_NIL;
extern MetaSort const_ms_CIS;
extern int numofsorts;

Boolean * visited_it;
ELEMENT * eval_it;
long cnt_it;
long tc_errcnt;

Boolean ** att_sortcheck;
Boolean ** att_nilcheck;
Boolean ** fct_sortcheck;
Boolean ** fct_nilcheck;

constr_list it_constraints;
MetaSort    expr_type;
MetaSort    blank_type;

#define TYPE(expr)  (&(expr_type[index(expr,_Expr_) * metasort_length]))   
#define BLANKTYPE(blk)  (&(blank_type[index(blk,_Blank_) * metasort_length]))   


MetaSort comp_path_type(ELEMENT path, MetaSort init_t, MetaSort curr_ms)
{
  int j,k;

  for(j = 0; j < metasort_length; j++)

       curr_ms[j] = init_t[j];

  for(j = numsubterms(path); j >= 1 ; j--)
  {
     switch(sort(subterm(j,path)))
     {
       case _Fath  :  sigpath_fath(curr_ms,curr_ms);  
                      break;

       case _SonTC :  sigpath_son(curr_ms,etoi(subterm(1,subterm(j,path))),
					  etoi(subterm(2,subterm(j,path))),
					  etoi(subterm(3,subterm(j,path))),
					  etoi(subterm(4,subterm(j,path))),
					  etoi(subterm(5,subterm(j,path))),
					  curr_ms); 
                      break;

       case _Lbroth : for(k = 1; k <= etoi(subterm(1,subterm(j,path))); k++)

   			sigpath_lbroth(curr_ms,curr_ms);

		      break;

       case _Rbroth : for(k = 1; k <= etoi(subterm(1,subterm(j,path))); k++)

			sigpath_rbroth(curr_ms,curr_ms);

		      break;


       default : assert( 1==0 );

     }

  }

 return curr_ms;

}


MetaSort comp_func_type(ELEMENT idn, ELEMENT args, MetaSort target)
{
 ELEMENT defid;

 bzero(target, metasort_length); 

 if(!strcmp("true",IDSTR(idn)))
 
  return sigma_true(target);

 if(!strcmp("false",IDSTR(idn)))
 
  return sigma_false(target);

 if(!strcmp("root",IDSTR(idn)))
 
  return sigma_root(target);

 if(!strcmp("fath",IDSTR(idn)))
 
  return sigma_fath(TYPE(son(1,args)),target);

 if(!strcmp("rbroth",IDSTR(idn)))
 
  return sigma_rbroth(TYPE(son(1,args)),target);

 if(!strcmp("lbroth",IDSTR(idn)))
 
  return sigma_lbroth(TYPE(son(1,args)),target);

 if(!strcmp("son",IDSTR(idn)))
 
  return sigma_son(TYPE(son(2,args)),TYPE(son(1,args)),son(1,args),target);

 if(!strcmp("numsons",IDSTR(idn)))
 
  return sigma_numsons(TYPE(son(1,args)),target);

 if(!strcmp("front",IDSTR(idn)))
 
  return sigma_front(TYPE(son(1,args)),target);

 if(!strcmp("back",IDSTR(idn)))
 
  return sigma_back(TYPE(son(1,args)),target);

 if(!strcmp("appfront",IDSTR(idn)))
 
  return sigma_appfront(TYPE(son(1,args)),TYPE(son(2,args)),target);

 if(!strcmp("appback",IDSTR(idn)))
 
  return sigma_appback(TYPE(son(1,args)),TYPE(son(2,args)),target);

 if(!strcmp("conc",IDSTR(idn)))
 
  return sigma_conc(TYPE(son(1,args)),TYPE(son(2,args)),target);

 if(!strcmp("subterm",IDSTR(idn)))
 
  return sigma_subterm(TYPE(son(2,args)),TYPE(son(1,args)),son(1,args),target);

 if(!strcmp("numsubterms",IDSTR(idn)))
 
  return sigma_numsubterms(TYPE(son(1,args)),target);

 if(!strcmp("term",IDSTR(idn)))
 
  return sigma_term(TYPE(son(1,args)),target);

 if(!strcmp("before",IDSTR(idn)))
 
  return sigma_before(TYPE(son(1,args)),target);

 if(!strcmp("after",IDSTR(idn)))
 
  return sigma_after(TYPE(son(1,args)),target);

 if(!strcmp("node",IDSTR(idn)))
 
  return sigma_node(TYPE(son(1,args)),target);

 if(!strcmp("idtos",IDSTR(idn)))
 
  return sigma_idtos(TYPE(son(1,args)),target);

 if(!strcmp("sort",IDSTR(idn)))
 
  return sigma_sort(TYPE(son(1,args)),target);

 if(!strcmp("index",IDSTR(idn)))
 
  return sigma_index(TYPE(son(1,args)),TYPE(son(2,args)),target);

 if(!strcmp("element",IDSTR(idn)))
 
  return sigma_element(TYPE(son(1,args)),TYPE(son(2,args)),target);

 if(!strcmp("number",IDSTR(idn)))
 
  return sigma_number(TYPE(son(1,args)),target);

 else
 {

   defid = idn;
                      
   ms_union(target,const_ms_NIL,target);

                      
   switch(sort(fath(defid)))
   {

     case _Attribute_ :
     case _Function_ :
     case _DynFunc_ :

                       metasort_by_sortid((is(son(4,fath(defid)), _TermSortId_) ? FALSE : TRUE),
					   term(son(1,son(4,fath(defid)))),target);
		       break;

     case _AttrDecl_    :
     case _FuncDecl_    :
     case _DynSemInput_ :

		       metasort_by_sortid((is(son(3,fath(defid)), _TermSortId_) ? FALSE : TRUE),
					   term(son(1,son(3,fath(defid)))),target);
		       break;

     case _ListProd_ :
     case _TupelProd_ :
     case _ClassProd_ :
     case _PredeclProd_ :

   		       metasort_by_prod(FALSE, fath(defid), target);
		       break;
   }

   return target;

 }

}


void do_tc()
{

 iteration();
 check_gfp();

 if(tc_errcnt > 0)
 {
   fprintf(stderr," %d type error(s), exiting\n",tc_errcnt);
   exit( EXIT_FAILURE );
 }

}


/***************************************************************
 *                 greatest fixed point iteration              *
 ***************************************************************/

void iteration()
{
 int i;
 Boolean done;
 constr_list curr_constr;
 MetaSort tmp_ms;

 tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

 if(!tmp_ms)
 {
  fprintf(stderr,"\n***** Error: Cannot allocate tmp_ms ");
  exit( EXIT_FAILURE );
 }

 do{

    done = TRUE;

    curr_constr = it_constraints;

    while(curr_constr != NULL)
    {

     switch(curr_constr->constr_descr)
     {

       case EXPR      :   
                          if(!is_subset(curr_constr->constraint.t_t.t1,
                                        curr_constr->constraint.t_t.t2))
                          {                      
                            ms_intersection(curr_constr->constraint.t_t.t1,
                                            curr_constr->constraint.t_t.t2,
                                            curr_constr->constraint.t_t.t1);
                            done = FALSE;
                          }

                          break;

       case CONST     :   
                          if(!is_subset(curr_constr->constraint.t_c.t,
                                        curr_constr->constraint.t_c.c))
                          {                      
                            ms_intersection(curr_constr->constraint.t_c.t,
                                            curr_constr->constraint.t_c.c,
                                            curr_constr->constraint.t_c.t);
                            done = FALSE;
                          }

                          break;

       case SIG_PATH  :   
			  bzero(tmp_ms, metasort_length); 
                           
                          comp_path_type(curr_constr->constraint.t_p.path,
                                         curr_constr->constraint.t_p.source,
                                         tmp_ms);

                          if(!is_subset(curr_constr->constraint.t_p.t,
                                        tmp_ms))
                          {                      
                            ms_intersection(curr_constr->constraint.t_p.t,
                                            tmp_ms,
                                            curr_constr->constraint.t_p.t);
                            done = FALSE;
                          }

                          break;

       case UNION     :   
			  bzero(tmp_ms, metasort_length); 

                          for( i = 1; i <= numsubterms(curr_constr->constraint.t_u.l); i++ )

                              ms_union(tmp_ms,TYPE(subterm(i,curr_constr->constraint.t_u.l)),tmp_ms);

                          if(!is_subset(curr_constr->constraint.t_u.t,
                                        tmp_ms))
                          {                      
                            ms_intersection(curr_constr->constraint.t_u.t,
                                            tmp_ms,
                                            curr_constr->constraint.t_u.t);
                            done = FALSE;
                          }

                          break;

       case SIG       :   
			  bzero(tmp_ms, metasort_length); 

                          comp_func_type(curr_constr->constraint.t_s.idn, curr_constr->constraint.t_s.args, tmp_ms);

                          if(!is_subset(curr_constr->constraint.t_s.t,
                                        tmp_ms))
                          {                      
                            ms_intersection(curr_constr->constraint.t_s.t,
                                            tmp_ms,
                                            curr_constr->constraint.t_s.t);
                            done = FALSE;
                          }

                          break;


       default  :  assert( 1 == 0 );

     }

     curr_constr = curr_constr->next;

    }


 } while(!done);

}


/***************************************************************
 *                        check gfp                            *
 ***************************************************************/

void check_gfp()
{
 MetaSort tmp_ms;
 int i,j,k;
 ELEMENT expr, defid, sid, prod;
 Boolean empty;
 MetaSort const_ms_lists;

 tmp_ms = (MetaSort) calloc(metasort_length,sizeof(char));

 if(!tmp_ms)
 {
  fprintf(stderr,"\n***** Error: Cannot allocate tmp_ms ");
  exit( EXIT_FAILURE );
 }

 for(i = 1; i <= number(_Expr_); i++)
 {

  expr = element(i,_Expr_);

  empty = TRUE;

  for(j = 0; j < metasort_length; j++)

     if(TYPE(expr)[j] != 0) { empty = FALSE; break; }

  if(empty)
  {
    if(is(expr,_Name_) && is(fath(expr),_Pattern_)){

      fprintf(stderr,"### error: pattern never matches in line %d, column %d\n",lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;

    }

    else{

      fprintf(stderr,"### error: conflicting types in line %d, column %d\n",lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;

    }

  }


  if(max_options.warn)
  {
     if(   is_subset(const_ms_NIL,TYPE(expr)) 
        && is_subset(TYPE(expr),const_ms_NIL) 
        && ( is(expr, _FuncAppl_) ? strcmp("nil", etoa(idtos(term(son(1,decl(son(1,expr))))))) : TRUE ) )
     {
       fprintf(stderr,"### warning: type nil in line %d, column %d\n",lineof(expr),colof(expr));
       fflush(stderr);
     }

  }


  /* ----------------         CaseRule     --------------*/

  if(is(fath(expr), _CaseRule_)) 
  {

   bzero(tmp_ms,metasort_length);
   if(!is_subset(TYPE(expr), const_ms_CIS))
   {

    empty = TRUE;
    ms_intersection(TYPE(expr),const_ms_CIS,tmp_ms);

    for(j = 0; j < metasort_length; j++)

      if(tmp_ms[j] != 0) { empty = FALSE; break; }

    if(empty || is_subset(tmp_ms, const_ms_NIL))
    {
      fprintf(stderr,"### error: type mismatch in `CASE` condition in line %d, column %d\n",lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;
    }
    else

      if(max_options.warn)
      {
        fprintf(stderr,"### warning: type mismatch possible in `CASE` condition line %d, column %d\n",lineof(expr),colof(expr));
        fflush(stderr);
      }
   }

  }

  /* ----------------         Update       --------------*/
  
  if(is(fath(expr), _Update_) && rbroth(expr) == nil()) 
  {

   bzero(tmp_ms,metasort_length);
   if(!is_subset(TYPE(expr), TYPE(lbroth(expr))))
   {

    empty = TRUE;
    ms_intersection(TYPE(lbroth(expr)),TYPE(expr),tmp_ms);
    
    for(j = 0; j < metasort_length; j++)

      if(tmp_ms[j] != 0) { empty = FALSE; break; }

    if(empty || is_subset(tmp_ms, const_ms_NIL))
    {
      fprintf(stderr,"### error: type mismatch in update assignment line %d, column %d\n",lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;
    }
    else

      if(max_options.warn) 
      { 
	fprintf(stderr,"### warning: type mismatch possible in update assignment line %d, column %d\n",lineof(expr),colof(expr));
	fflush(stderr);
      }
   }

  }


  /*----------------- Rumpf vs. Deklaration ------------------*/

  if(is(fath(expr), _Function_) || is(fath(expr), _Attribute_) || is(fath(expr), _DynFunc_))
  {
   bzero(tmp_ms,metasort_length);
   metasort_by_sortid(is(lbroth(expr), _TermSortId_) ? FALSE : TRUE,
		      term(son(1,lbroth(expr))),tmp_ms);

   ms_union(tmp_ms,const_ms_NIL,tmp_ms);

   if(!is_subset(TYPE(expr), tmp_ms))
   {

    empty = TRUE;
    ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
    for(j = 0; j < metasort_length; j++)

      if(tmp_ms[j] != 0) { empty = FALSE; break; }

    if(empty || is_subset(tmp_ms, const_ms_NIL))
    {
      fprintf(stderr,"### error: function \"%s\": declaration/definition type mismatch in line %d, column %d\n",etoa(idtos(term(son(1,son(1,fath(expr)))))),lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;
    }
    else

      if(max_options.warn) 
      { 
	fprintf(stderr,"### warning: function \"%s\": declaration/definition type mismatch possible in line %d, column %d\n",etoa(idtos(term(son(1,son(1,fath(expr)))))),lineof(expr),colof(expr));
	fflush(stderr);
      }
   }

  }


  /*------------------- formale/aktuelle Parameter bei PRD ---------------------*/

  if(is(fath(fath(expr)), _PredAppl_))    
  {

   defid = subterm(1,idtodecls(term(son(1,lbroth(fath(expr))))));
                      
   bzero(tmp_ms,metasort_length);
   sid = son(actpar_pos(expr,1), rbroth(defid));
   metasort_by_sortid(is(sid, _TermSortId_) ? FALSE : TRUE,
                      term(son(1,sid)),
		      tmp_ms);

   ms_union(tmp_ms,const_ms_NIL,tmp_ms);

   if(!is_subset(TYPE(expr), tmp_ms))
   {
    empty = TRUE;
    ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
    for(j = 0; j < metasort_length; j++)

      if(tmp_ms[j] != 0) { empty = FALSE; break; }

    if(empty || is_subset(tmp_ms, const_ms_NIL))
    {
      fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
      fflush(stderr);
      tc_errcnt++;
    }

    else

     if(max_options.warn)
     {
       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
     fflush(stderr);
     }
   }

  }

  /* LISTS */

  const_ms_lists = (MetaSort) calloc(metasort_length,sizeof(char));

  if( !const_ms_lists )
  {
    fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
    exit( EXIT_FAILURE );
  }

  for(k = 1; k <= number(_ListProd_); k++)
  {
    prod = element(k, _ListProd_);
    metasort_by_prod(FALSE,prod,const_ms_lists);
  }

  ms_union(const_ms_NIL,const_ms_lists,const_ms_lists);

  if(is(fath(fath(expr)), _FuncAppl_))    
  {

   defid = subterm(1,idtodecls(term(son(1,lbroth(fath(expr))))));
                      
   switch(sort(fath(defid)))
   {

     case _DynFunc_ :
                        bzero(tmp_ms,metasort_length);
			sid = son(actpar_pos(expr,1), rbroth(defid));
                        metasort_by_sortid(is(sid, _TermSortId_) ? FALSE : TRUE,
                                           term(son(1,sid)),
					   tmp_ms);

                        ms_union(tmp_ms,const_ms_NIL,tmp_ms);

                        if(!is_subset(TYPE(expr), tmp_ms))
                        {
           
                         empty = TRUE;
                         ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
                         for(j = 0; j < metasort_length; j++)

                           if(tmp_ms[j] != 0) { empty = FALSE; break; }

                         if(empty || is_subset(tmp_ms, const_ms_NIL))
                         {
                           fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			   fflush(stderr);
			   tc_errcnt++;
                         }

                         else

                           if(max_options.warn)
			   {
			     fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
                           }
                        }

                        break;

     


     case _Attribute_ :
                        bzero(tmp_ms,metasort_length);
			sid = son(actpar_pos(expr,1), rbroth(defid));
                        metasort_by_sortid(is(sid, _TermSortId_) ? FALSE : TRUE,
                                           term(son(1,sid)),
					   tmp_ms);

                        ms_union(tmp_ms,const_ms_NIL,tmp_ms);

                        if(!is_subset(TYPE(expr), tmp_ms))
                        {

                         att_sortcheck[index(fath(defid),_Attribute_)][etoi(actpar_pos(expr,1))] = TRUE;
                         empty = TRUE;
                         ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
                         for(j = 0; j < metasort_length; j++)

                           if(tmp_ms[j] != 0) { empty = FALSE; break; }

                         if(empty || is_subset(tmp_ms, const_ms_NIL))
                         {
                           fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			   fflush(stderr);
			   tc_errcnt++;
                         }

                         else

                           if(max_options.warn)
			   {
			     fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
                           }
                        }

                        if(is_subset(const_ms_NIL,TYPE(expr)))

			  att_nilcheck[index(fath(defid),_Attribute_)][etoi(actpar_pos(expr,1))] = TRUE;

                        break;

     case _Function_ :
                        bzero(tmp_ms,metasort_length);
			sid = son(actpar_pos(expr,1), rbroth(defid));
                        metasort_by_sortid(is(sid, _TermSortId_) ? FALSE : TRUE,
                                           term(son(1,sid)),
					   tmp_ms);

                        ms_union(tmp_ms,const_ms_NIL,tmp_ms);

                        if(!is_subset(TYPE(expr), tmp_ms))
                        {

                         fct_sortcheck[index(fath(defid),_Function_)][etoi(actpar_pos(expr,1))] = TRUE;
                         empty = TRUE;
                         ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
                         for(j = 0; j < metasort_length; j++)

                           if(tmp_ms[j] != 0) { empty = FALSE; break; }

                         if(empty || is_subset(tmp_ms, const_ms_NIL))
                         {
                           fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			   fflush(stderr);
			   tc_errcnt++;
                         }

                         else

                           if(max_options.warn)
			   {
			     fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
                           }
                        }

                        if(is_subset(const_ms_NIL,TYPE(expr)))

			  fct_nilcheck[index(fath(defid),_Function_)][etoi(actpar_pos(expr,1))] = TRUE;

                        break;

     case _AttrDecl_    :
     case _FuncDecl_    :
     case _DynSemInput_ :

			/* check front,back,appfront,appback -> List
				 conc -> List1,List2 && List1 == List2
			*/
			
			if(!strcmp(etoa(idtos(term(son(1,defid)))),"front"))
			{
			 if(!is_subset(TYPE(expr),const_ms_lists))
                         {
			   empty = TRUE;
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(const_ms_lists,TYPE(expr),tmp_ms);
    
                           for(j = 0; j < metasort_length; j++)

                             if(tmp_ms[j] != 0) { empty = FALSE; break; }

                           if(empty || is_subset(tmp_ms, const_ms_NIL))
                           {
                             fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
			     tc_errcnt++;
                           }

                           else

                             if(max_options.warn)
			     {
			       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			       fflush(stderr);
                             }

			  }

			  break;

		 	}	

			if(!strcmp(etoa(idtos(term(son(1,defid)))),"back"))
			{
			 if(!is_subset(TYPE(expr),const_ms_lists))
                         {
                           empty = TRUE;
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(const_ms_lists,TYPE(expr),tmp_ms);
    
                           for(j = 0; j < metasort_length; j++)

                             if(tmp_ms[j] != 0) { empty = FALSE; break; }

                           if(empty || is_subset(tmp_ms, const_ms_NIL))
                           {
                             fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
			     tc_errcnt++;
                           }

                           else

                             if(max_options.warn)
			     {
			       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			       fflush(stderr);
                             }

			  }

			  break;

			}

			if(!strcmp(etoa(idtos(term(son(1,defid)))),"appfront") && etoi(actpar_pos(expr,1)) == 2)
			{
			 if(!is_subset(TYPE(expr),const_ms_lists))
                         {
                           empty = TRUE;
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(const_ms_lists,TYPE(expr),tmp_ms);
    
                           for(j = 0; j < metasort_length; j++)

                             if(tmp_ms[j] != 0) { empty = FALSE; break; }

                           if(empty || is_subset(tmp_ms, const_ms_NIL))
                           {
                             fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
			     tc_errcnt++;
                           }

                           else

                             if(max_options.warn)
			     {
			       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			       fflush(stderr);
                             }

			 }

			 break;

			}

			
			if(!strcmp(etoa(idtos(term(son(1,defid)))),"appback") && etoi(actpar_pos(expr,1)) == 1)
			{
			 if(!is_subset(TYPE(expr),const_ms_lists))
                         {
                           empty = TRUE;
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(const_ms_lists,TYPE(expr),tmp_ms);
    
                           for(j = 0; j < metasort_length; j++)

                             if(tmp_ms[j] != 0) { empty = FALSE; break; }

                           if(empty || is_subset(tmp_ms, const_ms_NIL))
                           {
                             fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
			     tc_errcnt++;
                           }

                           else

                             if(max_options.warn)
			     {
			       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			       fflush(stderr);
                             }

    			 }

			 break;

			}


			if(!strcmp(etoa(idtos(term(son(1,defid)))),"conc"))
			{
			 if(!is_subset(TYPE(expr),const_ms_lists))
                         {
                           empty = TRUE;
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(const_ms_lists,TYPE(expr),tmp_ms);
    
                           for(j = 0; j < metasort_length; j++)

                             if(tmp_ms[j] != 0) { empty = FALSE; break; }

                           if(empty || is_subset(tmp_ms, const_ms_NIL))
                           {
                             fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
			     tc_errcnt++;
                           }

                           else

                             if(max_options.warn)
			     {
			       fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			       fflush(stderr);
                             }

                          }

			  if( etoi(actpar_pos(expr,1)) == 1)
			  {
			   bzero(tmp_ms,metasort_length);
                           ms_intersection(TYPE(expr),TYPE(rbroth(expr)),tmp_ms);
   			   ms_union(tmp_ms,const_ms_NIL,tmp_ms);

			   if(!is_subset(TYPE(expr), tmp_ms) || !is_subset(TYPE(rbroth(expr)), tmp_ms))
                           {
                            empty = TRUE;
                            for(j = 0; j < metasort_length; j++)

                              if(tmp_ms[j] != 0) { empty = FALSE; break; }

                            if(empty || is_subset(tmp_ms, const_ms_NIL))
                            {
                              fprintf(stderr,"### error: parameter (1,2) type mismatch in application of \"%s\" (line %d, column %d)\n",etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			      fflush(stderr);
			      tc_errcnt++;
                            }

                            else

                              if(max_options.warn)
			      {
			        fprintf(stderr,"### warning: parameter (1,2) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			        fflush(stderr);
                              }

                           }

                          }

			 break;

		       }					

     case _TupelProd_ :

                        bzero(tmp_ms,metasort_length);
			sid = son(actpar_pos(expr,1), rbroth(defid));
                        metasort_by_sortid(is(sid, _TermSortId_) ? FALSE : TRUE,
                                           term(son(1,sid)),
					   tmp_ms);

                        ms_union(tmp_ms,const_ms_NIL,tmp_ms);

                        if(!is_subset(TYPE(expr), tmp_ms))
                        {

                         empty = TRUE;
                         ms_intersection(tmp_ms,TYPE(expr),tmp_ms);
    
                         for(j = 0; j < metasort_length; j++)

                           if(tmp_ms[j] != 0) { empty = FALSE; break; }

                         if(empty || is_subset(tmp_ms, const_ms_NIL))
                         {
                           fprintf(stderr,"### error: parameter (%d) type mismatch in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			   fflush(stderr);
			   tc_errcnt++;
                         }

                         else

                           if(max_options.warn)
			   {
			     fprintf(stderr,"### warning: parameter (%d) type mismatch possible in application of \"%s\" (line %d, column %d)\n",etoi(actpar_pos(expr,1)),etoa(idtos(term(son(1,defid)))),lineof(expr),colof(expr));
			     fflush(stderr);
                           }
                        }

                        break;


     default :          fprintf(stderr,"\n illegal function application in line %d, column %d\n",lineof(expr),colof(expr));
			fflush(stderr);
			exit(EXIT_FAILURE);

   }

  }

 } /* end for */

}


void eval_prio( ELEMENT expr )
{
 int i;
 ELEMENT dep_list;

 if(visited_it[index(expr,_Expr_)]) return;

 dep_list = dep_expr(expr);

 if(numsubterms(dep_list) == 0) 
 {
  visited_it[index(expr,_Expr_)] = TRUE;
  eval_it[cnt_it++] = expr;
 }
 
 else

 {

   visited_it[index(expr,_Expr_)] = TRUE;

   for(i = 1; i <= numsubterms(dep_list); i++)

      eval_prio(subterm(i,dep_list));

   eval_it[cnt_it++] = expr;

 }

}


void typecheck()
{
 int i,j,numpar;
 ELEMENT expr,defid,blank;
 constr_list entry,prev_entry;
 MetaSort M,ims,c_ms;
 Boolean entry_used;

 tc_errcnt = 0;

 metasort_init();

 sigma_init();

 expr_type = (MetaSort) malloc((number(_Expr_) + 1) * metasort_length);

 if(!expr_type)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate expr_type ");
   exit( EXIT_FAILURE );
 }   

 blank_type = (MetaSort) malloc((number(_Blank_) + 1) * metasort_length);

 if(!blank_type)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate blank_type ");
   exit( EXIT_FAILURE );
 }   

 visited_it = (Boolean *) calloc((number(_Expr_) + 1),sizeof(Boolean));

 if(!visited_it)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate visited_it");
   exit( EXIT_FAILURE );
 }   

 eval_it = (ELEMENT *) calloc((number(_Expr_) + 1),sizeof(ELEMENT));

 if(!eval_it)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate eval_it");
   exit( EXIT_FAILURE );
 }   

 att_sortcheck = (Boolean **) calloc(number(_Attribute_) + 1,sizeof(Boolean*));

 if(!att_sortcheck)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate att_sortcheck");
   exit( EXIT_FAILURE );
 }   

 att_nilcheck = (Boolean **) calloc(number(_Attribute_) + 1,sizeof(Boolean*));

 if(!att_nilcheck)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate att_nilcheck");
   exit( EXIT_FAILURE );
 }   

 for(i = 1; i <= number(_Attribute_); i++)
 {
   numpar = etoi(numsons(son(2,element(i,_Attribute_)))) + 1;

   att_sortcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

   if(!att_sortcheck[i])
   {
     fprintf(stderr,"\n***** Error: Cannot allocate att_sortcheck");
     exit( EXIT_FAILURE );
   }   

   for(j = 1; j < numpar; j++)

      att_sortcheck[i][j] = FALSE;


   att_nilcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

   if(!att_nilcheck[i])
   {
     fprintf(stderr,"\n***** Error: Cannot allocate att_nilcheck");
     exit( EXIT_FAILURE );
   }   

   for(j = 1; j < numpar; j++)

      att_nilcheck[i][j] = FALSE;

 }


 fct_sortcheck = (Boolean **) calloc(number(_Function_) + 1,sizeof(Boolean*));

 if(!fct_sortcheck)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate fct_sortcheck");
   exit( EXIT_FAILURE );
 }   

 fct_nilcheck = (Boolean **) calloc(number(_Function_) + 1,sizeof(Boolean*));

 if(!fct_nilcheck)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate fct_nilcheck");
   exit( EXIT_FAILURE );
 }   

 for(i = 1; i <= number(_Function_); i++)
 {
   numpar = etoi(numsons(son(2,element(i,_Function_)))) + 1;

   fct_sortcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

   if(!fct_sortcheck[i])
   {
     fprintf(stderr,"\n***** Error: Cannot allocate fct_sortcheck");
     exit( EXIT_FAILURE );
   }   

   for(j = 1; j < numpar; j++)

      fct_sortcheck[i][j] = FALSE;


   fct_nilcheck[i] = (Boolean *) calloc(numpar,sizeof(Boolean));

   if(!fct_nilcheck[i])
   {
     fprintf(stderr,"\n***** Error: Cannot allocate fct_nilcheck");
     exit( EXIT_FAILURE );
   }   

   for(j = 1; j < numpar; j++)

      fct_nilcheck[i][j] = FALSE;

 }


 for(i = 1; i <= number(_Blank_); i++)
 {

    blank = element(i,_Blank_); 
    bcopy(const_ms_UNIV, BLANKTYPE(blank), metasort_length);

 }


 for(i = 1; i <= number(_Expr_); i++)
 {

    visited_it[i] = FALSE;
    expr = element(i,_Expr_); 
    bcopy(const_ms_UNIV, TYPE(expr), metasort_length);

 }

           /*---------------------------------
             generate iteration constraint list 
             --------------------------------*/
 
 /* eval_prio */

 cnt_it = 1;

 for(i = 1; i <= number(_Expr_); i++)

    if(visited_it[i]) continue;
    else eval_prio(element(i,_Expr_));


 entry = (constr_list) malloc(sizeof(struct constrlist_entry));

 if(!entry)
 {
   fprintf(stderr,"\n***** Error: Cannot allocate internal table ");
   exit( EXIT_FAILURE );
 }

 it_constraints = entry;

 prev_entry = entry;

 for(i = 1; i <= number(_Expr_); i++)
 {

  expr = eval_it[i];
  entry_used = TRUE;

  switch(sort(expr))
  {

   case _Name_ :
		if(bind_pos(expr) == expr)        /* frei */ 
		{

		 if(is(fath(expr),_NameList_))   /* formaler Parameter */
                 {
                   M = (MetaSort) calloc(metasort_length,sizeof(char));

                   if(!M)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate M ");
   		    exit( EXIT_FAILURE );
    		   }

                   metasort_by_sortid((is(corresp_parsort(expr),_TermSortId_) ? FALSE : TRUE),
				      term(son(1,corresp_parsort(expr))), M);

		   if(is(fath(fath(expr)),_Predicate_))

		      ms_union(M,const_ms_NIL,M);

                   /* init */

                   bcopy(M,TYPE(expr),metasort_length);

                   free(M);
                   entry_used = FALSE;
 
                   break;
                 }

	         if(is(fath(expr),_LetExpr_))    /* LetExpr */
                 {
                   prev_entry = entry;

                   entry->expn              = expr;
                   entry->constr_descr      = EXPR;
		   entry->constraint.t_t.t1 = TYPE(expr);
		   entry->constraint.t_t.t2 = TYPE(rbroth(expr));

                   entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                   if(!entry)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate entry (1) ");
   		    exit( EXIT_FAILURE );
    		   }

 		   prev_entry->next = entry;
                   prev_entry = entry;

                   entry->expn              = expr;
                   entry->constr_descr      = EXPR;
		   entry->constraint.t_t.t2 = TYPE(expr);
		   entry->constraint.t_t.t1 = TYPE(rbroth(expr));

                 }

		 else                            /* Name im Pattern */
		 {
                  ELEMENT bnl = search_patt_names(top_pattern(expr),term(son(1,expr)));  
                  ELEMENT scl = search_patt_sorts(top_pattern(expr));
                  ELEMENT bl  = search_blanks(top_pattern(expr));

                  if(numsubterms(bnl) + numsubterms(bl) > 0) prev_entry = entry;

                  for(j = 1; j <= numsubterms(bnl); j++)
                  {
                   entry->expn                  = expr;
                   entry->constr_descr          = SIG_PATH;
		   entry->constraint.t_p.t      = TYPE(expr);
                   entry->constraint.t_p.path   = univ_path(fath(subterm(j,bnl)),fath(expr));
		   entry->constraint.t_p.source = TYPE(subterm(j,bnl));

                   if( j < numsubterms(bnl) + numsubterms(bl) )
                   {
                    entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                    if(!entry)
  		    {
   		     fprintf(stderr,"\n***** Error: Cannot allocate entry (2)");
   		     exit( EXIT_FAILURE );
    		    }

                    prev_entry->next = entry;
                    prev_entry = entry;

                   }

                  }

                  for(j = 1; j <= numsubterms(bl); j++)
                  {
                   entry->expn                  = expr;
                   entry->constr_descr          = SIG_PATH;
		   entry->constraint.t_p.t      = TYPE(expr);
                   entry->constraint.t_p.path   = univ_path(subterm(j,bl),fath(expr));
		   entry->constraint.t_p.source = BLANKTYPE(subterm(j,bl));

                   entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                   if(!entry)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate entry (2)");
   		    exit( EXIT_FAILURE );
    		   }

                   prev_entry->next = entry;
                   prev_entry = entry;

                  }


                  for(j = 1; j <= numsubterms(bl); j++)
                  {
                   entry->expn                  = expr;
                   entry->constr_descr          = SIG_PATH;
		   entry->constraint.t_p.t      = BLANKTYPE(subterm(j,bl));
                   entry->constraint.t_p.path   = univ_path(fath(expr),subterm(j,bl));
		   entry->constraint.t_p.source = TYPE(expr);

                   if( j < numsubterms(bl) )
                   { 
		    entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                    if(!entry)
  		    {
   		     fprintf(stderr,"\n***** Error: Cannot allocate entry (2)");
   		     exit( EXIT_FAILURE );
    		    }

                    prev_entry->next = entry;
                    prev_entry = entry;

                   }

                  }


                  if(numsubterms(bnl) + numsubterms(bl) == 0) entry_used = FALSE;


                  for(j = 1; j <= numsubterms(scl); j++)
                  {

                   M = (MetaSort) calloc(metasort_length,sizeof(char));

                   if(!M)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate M ");
   		    exit( EXIT_FAILURE );
    		   }

                   metasort_by_sortid(TRUE,term(son(1,subterm(j,scl))),M);
  
                   /* init */

                   ims = (MetaSort) calloc(metasort_length,sizeof(char));

                   if(!ims)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate ims ");
   		    exit( EXIT_FAILURE );
    		   }

                   comp_path_type(univ_path(fath(subterm(j,scl)),fath(expr)),
                                  M,
                                  ims);

                   if(!is_subset(TYPE(expr),
                                 ims))
                                              
                      ms_intersection(TYPE(expr),
                                      ims,
                                      TYPE(expr));
                      
                   free(ims);
                   free(M);     

                  }

		 }

                 break;

		}
		
		else                                        /* gebunden */
		{
                    if(is(fath(expr),_Pattern_))            /* im Pattern */
                    {
                     ELEMENT bnl = search_patt_names(top_pattern(expr),term(son(1,expr))); 
                     ELEMENT scl = search_patt_sorts(top_pattern(expr));
                     ELEMENT bl  = search_blanks(top_pattern(expr));

                     if(numsubterms(bnl) + numsubterms(bl) > 0) prev_entry = entry;

                     for(j = 1; j <= numsubterms(bnl); j++)
                     {
                      entry->expn                  = expr;
                      entry->constr_descr          = SIG_PATH;
		      entry->constraint.t_p.t      = TYPE(expr);
                      entry->constraint.t_p.path   = univ_path(fath(subterm(j,bnl)),fath(expr));
		      entry->constraint.t_p.source = TYPE(subterm(j,bnl));

                      if( j < numsubterms(bnl) + numsubterms(bl) )
                      {
                       entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                       if(!entry)
  		       {
   		        fprintf(stderr,"\n***** Error: Cannot allocate entry (4)");
   		        exit( EXIT_FAILURE );
    		       }

                       prev_entry->next = entry;
                       prev_entry = entry;

                      }

                     }

                     for(j = 1; j <= numsubterms(bl); j++)
                     {
                      entry->expn                  = expr;
                      entry->constr_descr          = SIG_PATH;
		      entry->constraint.t_p.t      = TYPE(expr);
                      entry->constraint.t_p.path   = univ_path(subterm(j,bl),fath(expr));
		      entry->constraint.t_p.source = BLANKTYPE(subterm(j,bl));

                      entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                      if(!entry)
  		      {
   		       fprintf(stderr,"\n***** Error: Cannot allocate entry (2)");
   		       exit( EXIT_FAILURE );
    		      }

                      prev_entry->next = entry;
                      prev_entry = entry;

                     }


                     for(j = 1; j <= numsubterms(bl); j++)
                     {
                      entry->expn                  = expr;
                      entry->constr_descr          = SIG_PATH;
		      entry->constraint.t_p.t      = BLANKTYPE(subterm(j,bl));
                      entry->constraint.t_p.path   = univ_path(fath(expr),subterm(j,bl));
		      entry->constraint.t_p.source = TYPE(expr);

                      if( j < numsubterms(bl) )
                      { 
		       entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                       if(!entry)
  		       {
   		        fprintf(stderr,"\n***** Error: Cannot allocate entry (2)");
   		        exit( EXIT_FAILURE );
    		       }

                       prev_entry->next = entry;
                       prev_entry = entry;

                      }

                     }

                     for(j = 1; j <= numsubterms(scl); j++)
                     {

                      M = (MetaSort) calloc(metasort_length,sizeof(char));

                      if(!M)
  		      {
   		       fprintf(stderr,"\n***** Error: Cannot allocate M ");
   		       exit( EXIT_FAILURE );
    		      }

                      metasort_by_sortid(TRUE,term(son(1,subterm(j,scl))),M);

                      /* init */

                      ims = (MetaSort) calloc(metasort_length,sizeof(char));

                      if(!ims)
  		      {
   		       fprintf(stderr,"\n***** Error: Cannot allocate ims ");
   		       exit( EXIT_FAILURE );
    		      }

                      comp_path_type(univ_path(fath(subterm(j,scl)),fath(expr)),
                                     M,
                                     ims);

                      if(!is_subset(TYPE(expr),
                                    ims))
                                              
                         ms_intersection(TYPE(expr),
                                         ims,
                                         TYPE(expr));
                      
                      free(ims);
                      free(M);     

                     }
   

                     if(numsubterms(bnl) + numsubterms(bl) > 0) 
                     {

                      entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                      if(!entry)
  		      {
   		       fprintf(stderr,"\n***** Error: Cannot allocate entry(5) ");
   		       exit( EXIT_FAILURE );
    		      }

                      prev_entry->next = entry;
                      prev_entry = entry;

                     }

                     entry->expn                = expr;
                     entry->constr_descr        = EXPR;
		     entry->constraint.t_t.t1   = TYPE(expr);
                     entry->constraint.t_t.t2   = TYPE(latest_bindpos(fath(encl_patterncase(expr)),expr));

                    }

                    else                                    /*   sonst    */
                    {

                      prev_entry = entry;

                      entry->expn                = expr;
                      entry->constr_descr        = EXPR;
		      entry->constraint.t_t.t1   = TYPE(expr);
                      entry->constraint.t_t.t2   = TYPE(latest_bindpos(expr,expr));

                    }

		}

		break;


   case _IfExpr_ :
    
                   prev_entry = entry;

                   entry->expn             = expr;
	           entry->constr_descr     = UNION;
		   entry->constraint.t_u.t = TYPE(expr);
		   entry->constraint.t_u.l = allexpr(expr);

	           break;

   case _LetExpr_ :

                   prev_entry = entry;

                   entry->expn              = expr;
                   entry->constr_descr      = EXPR;
		   entry->constraint.t_t.t1 = TYPE(expr);
		   entry->constraint.t_t.t2 = TYPE(son(3,expr));

                   entry = (constr_list) malloc(sizeof(struct constrlist_entry));

                   if(!entry)
  		   {
   		    fprintf(stderr,"\n***** Error: Cannot allocate entry(6) ");
   		    exit( EXIT_FAILURE );
    		   }

 		   prev_entry->next = entry;
                   prev_entry = entry;

                   entry->expn              = expr;
                   entry->constr_descr      = EXPR;
		   entry->constraint.t_t.t2 = TYPE(expr);
		   entry->constraint.t_t.t1 = TYPE(son(3,expr));

	           break;

   case _StringExpr_ :

                   entry_used = FALSE;

                   /* init */

                   bcopy(const_ms_STRING,TYPE(expr),metasort_length);

	           break;

   
   case _CharConst_  :  

                   entry_used = FALSE;

                   /* init */

                   bcopy(const_ms_CHAR,TYPE(expr),metasort_length);

                   break;
                  
   case _IntConst_   :  

                   entry_used = FALSE;

                   /* init */

                   bcopy(const_ms_INT,TYPE(expr),metasort_length);

                   break;

   case _StringConst_ : 

                   entry_used = FALSE;

                   /* init */

                   bcopy(const_ms_STRING,TYPE(expr),metasort_length);

                   break;

   case _SortConst_ : 

                      entry_used = FALSE;

                      switch(sort(son(1,expr)))
                      {

                        case _TermSortId_ :
                                              
                                            /* init */

                                            bcopy(const_ms_TERMSORT,TYPE(expr),metasort_length);
 
                                            break;

                        case _NodeSortId_ :
                                              
                                            /* init */

                                            bcopy(const_ms_NODESORT,TYPE(expr),metasort_length);
 
                                            break;

                        default: assert ( 1 == 0 );

                      }

                      break;

   case _FuncAppl_ :  
                      prev_entry = entry;

                      defid = subterm(1,idtodecls(term(son(1,son(1,expr)))));
                      
                      entry->expn                = expr;
                      entry->constr_descr        = SIG;
		      entry->constraint.t_s.t    = TYPE(expr);
	              entry->constraint.t_s.idn  = defid; 
                      entry->constraint.t_s.args = son(2,expr);	 
  
	   	      break;


   case _DynUndef_ :  
                      prev_entry = entry;

                      entry->expn                = expr;
                      entry->constr_descr        = CONST;
                      entry->constraint.t_c.t    = TYPE(expr);

                      c_ms = (MetaSort) calloc(metasort_length,sizeof(char));

                      if(!c_ms)
                      {
                       fprintf(stderr,"\n***** Error: Cannot allocate c_ms ");
                       exit( EXIT_FAILURE );
                      }

                      metasort_by_sortid((is(son(4,encl_dynfunc(expr)), _TermSortId_) ? FALSE : TRUE),term(son(1,son(4,encl_dynfunc(expr)))),c_ms);

                      entry->constraint.t_c.c    = c_ms;

                      break;


   default: fprintf(stderr,"\n gen_constrlist: sort = %d\n",sort(expr));
	    exit(EXIT_FAILURE);


  }

  if( i < number(_Expr_) && entry_used )
  {
   entry = (constr_list) malloc(sizeof(struct constrlist_entry));

   if(!entry)
   {
    fprintf(stderr,"\n***** Error: Cannot allocate entry(7)");
    exit( EXIT_FAILURE );
   }

   prev_entry->next = entry;

  }

  else if( i >= number(_Expr_) ) prev_entry->next = NULL; 

 }

 do_tc();

}

