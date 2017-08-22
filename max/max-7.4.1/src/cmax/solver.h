/******************************************************************************

  Local Propagation Solver for one-way-constraints
  with single output variable

  (headers)

  (c) Copyright 1997 by Aurel Huber, TU Muenchen


  Last update: 3 Nov 1997

******************************************************************************/

/*
  We need the type definition ELEMENT.
  There is no header file for MAX data structures available currently,
  so we have to use the following definition.
  */

#ifndef ELEMENT
typedef long mxi_ELEMENT;
#define ELEMENT mxi_ELEMENT
#endif

/*
  The following data structure realizes logic variables.
  The second entry (the constraints that have to be revisited
  when the variable is modified) is not used yet.
  */

typedef struct {
  ELEMENT value;
  struct constr_instance_list *depconstrs;
} Variable;

/*
  For constraints the following information is managed:
  * the local solving procedure 'method'
  * the arguments as array 'env' plus size of the array, and
  * the variable that is modified by the constraint (not used yet).
*/
  
typedef struct {
  int (*method)(ELEMENT env[]);
  int envsize;
  ELEMENT *env;
  Variable *outputvar;
} Constr_Instance;  

typedef struct constr_instance_list {
  Constr_Instance *head;
  struct constr_instance_list *tail;
} Constr_Instance_List;  



/*
  The function 'init_var__' allocates a new variable and initializes
  it with a given value
*/ 

ELEMENT init_var__(ELEMENT init_value);


/*
  The function  'get_var_value__' reads the current value of a variable.
*/

ELEMENT get_var_value__(ELEMENT vptr);

/*
  same function, but with source code information, and realized
  as a macro
*/

#define get_var_value1__(file,line,vptr) ( ( (Variable*) \
                                      mxi_etop(file,line,vptr) )-> value)

/*
  The function '__add_constraint' constructs a new constraint with
  the given data and adds it to the list of active constraints.
*/

void __add_constraint ( int (*method)(ELEMENT env[]),
                        void (*dep)(ELEMENT env[]),
                        int envsize, ...
                      );

/*
  The function 'solve__' solves all active constraints.
*/

ELEMENT solve__(void);


















