/******************************************************************************

  Local Propagation Solver for one-way-constraints
  with single output variable


  (c) Copyright 1997 by Aurel Huber, TU Muenchen


  Last update: 3 Nov 1997

******************************************************************************/

#include "solver.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

extern int Verbose;    /* if 0 the solver produces no messages ... */ 

#define MSG(a)  ( Verbose ? (a) : 0 )


/*
  Access to predefined MAX functions
*/

extern  mxi_ELEMENT  mxi_btoe( char*, int, long );
extern  mxi_ELEMENT  mxi_ptoe( char*, int, void * );
extern  void *       mxi_etop( char*, int, ELEMENT );

#define  btoe(VAL)       mxi_btoe(__FILE__,__LINE__,VAL)
#define  ptoe(VAL)       mxi_ptoe(__FILE__,__LINE__,VAL)
#define  etop(VAL)       mxi_etop(__FILE__,__LINE__,VAL)


int Nr_Of_Constraints = 0;

static Constr_Instance
       *Current_Constraint = NULL; /* The constraint used when
                                      collecting dependency information */

static Constr_Instance_List *Active_Constraints = NULL;


/*
  The function 'init_var__' allocates a new variable and initializes
  it with a given value
*/ 

ELEMENT init_var__(ELEMENT init_value)
{
  Variable *ptr = (Variable*) calloc(1, sizeof(Variable));
  
  if (!ptr) {
    fprintf(stderr, "solver error: cannot allocate variable!\n");
    exit(1);
  }
  ptr->value = init_value;
  return ptoe(ptr);
}


/*
  The function 'get_var_value__' reads the current value of a variable.
  */

ELEMENT get_var_value__(ELEMENT vptr)
{
  return ( (Variable*) etop (vptr) )-> value;
}


/*
  The following function copies the array of arguments of a constraint
*/

static ELEMENT *copy_args(ELEMENT *args, int size)
{
    ELEMENT *new_args=(ELEMENT*)calloc(size, sizeof(ELEMENT));
    int i;

    for (i=0; i<size; i++) new_args[i]=args[i];
    return new_args;
}


/*
  The function '__add_constraint' constructs a new constraint with
  the given data and adds it to the list of active constraints.
  The parameter 'dep' is a function that is used to collect
  dependency information about constraints. This would allow for
  more efficient constraint solving but is not used yet. So just
  pass NULL here. 
*/

void __add_constraint ( int (*method)(ELEMENT env[]),
                        void (*dep)(ELEMENT env[]),
                        int envsize, ...
                      )
{
  ELEMENT *args;
  va_list ap; int i;


  Constr_Instance_List *cl = (Constr_Instance_List*) calloc (1,
                                   sizeof (Constr_Instance_List));
  Constr_Instance *newconstr = (Constr_Instance*) calloc(1,
                                   sizeof (Constr_Instance));

  if (envsize) args = calloc(envsize, sizeof(ELEMENT));
  else args = NULL;
  
  newconstr->method = method;
  newconstr->envsize = envsize;

  va_start(ap, envsize);

  for (i=0; i<envsize; i++) {
    args[i] = va_arg(ap, ELEMENT);
  }
  va_end(ap);

  newconstr->env = args;

  Current_Constraint = newconstr;
  if (dep) (*dep)(args);

  cl->head = newconstr;
  cl->tail = Active_Constraints;
  Active_Constraints = cl;

  Nr_Of_Constraints++;
}  

/*
  Functions to be used in the (*dep)()-function
*/

void __set_output_var ( Variable *var )
{
  Current_Constraint->outputvar = var;
}

void __dep_of_var ( Variable *var )
{
  Constr_Instance_List *cl = (Constr_Instance_List*) calloc(1,
                               sizeof(Constr_Instance_List));
  
  cl->head = Current_Constraint;
  cl->tail = var->depconstrs;
  var->depconstrs = cl;
}

/*
  The following function would build a dependency graph of the
  activated constraints providing a perfect strategy for visiting
  constraints.
*/

static void __make_constr_graph (void)
{
}
  
ELEMENT solve__(void)
{
    int change=1;  Constr_Instance_List *cl;

    MSG(fprintf(stderr, "solving %d constraints ",Nr_Of_Constraints)); 
    while (change) {
        MSG(fprintf(stderr, "*"));
        change=0;
        for (cl = Active_Constraints; cl != NULL; cl = cl->tail ) {
            if ( (cl->head->method)(cl->head->env) )
                change = 1;
        }
    }
    MSG(fprintf(stderr, " done\n"));
    return btoe(1);
}





































