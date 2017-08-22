/*****************************************************************************
**  Basic Main Program for Compilers/Interpreters implemented with MAX
**  (headers)
**  
**  supports calling options, output files, Timing functions,
**  error counting.
**
**  (c) Copyright 1996,1997 by Aurel Huber, TU Muenchen
**
**  Last change: Oct 8 1997
*****************************************************************************/

/*****************************************************************************
    The following items must be declared by the user:

    char *options[]  = { "option1", "option2", ..., "" };    
    char *switches[] = { "option1", "option2", ..., "" };
          (the available calling options)
    #define BROWSEROPTION "option"
          (one of the options in switches)
    int main_flags = flag1 | flag2 | ...;
          ( flags are: DYNSEM: execute code for dynamic semantics;
                       MERGE:  if more than one input file: do not
                                 attribute each one separately but
                                 merge them to one specification; must
                                 be supported by yyread-function! )
    void       user_init        (void);      (e.g. welcome message)
    void       user_exit        (void);
    ELEMENT    max_init_fct     (ELEMENT tree);(fct calling init_<spec>(tree))
    void       max_dyninit_fct  (void);  (fct calling init_dyninput() and
                                                      eval_dynsem()
                                          if necessary)    
    void       usage            (void);
     
*****************************************************************************

/*
implemented MAX functions; copy declarations into MAX specification:
    
//
// File I/O functions. Currently only output is supported.
// Functions returning a Bool value return true() on success and
// false() on failure.
//

FCT out (String) Bool               // unbuffered output to stdout
    
FCT openFile (String, String) Int   // opens file ( second string describes
             // mode like in C) and returns a file handle >=0 or -1.
                                   
FCT writeToFile (Int, String) Bool  // writes string to the file pointed
                                    // to by the handle.
                                   
FCT closeFile (Int) Bool            // closes file pointed to by handle.
    
FCT inputFilePath () String         // if the command line argument specifying
             // the file to be processed is <path>/<filname>
             // the string "<path>" is returned. 

FCT inputFileName () String         // returns "<filename>" in example above

//
// Error counter
//
        
FCT error() Bool            // increment error counter
FCT nrOfErrors() Int        // current error counter

//
// Calling options (currently just switches (-option) are supported).
//
    
FCT checkOption (String) Bool   // checks if the given option is selected
FCT getOption (String) Bool     // returns value of command line option
                                // "true" or "" for switches

//
// Timing functions
//
    
FCT startTimer () Bool
FCT readTimer () Int        // read timer value in seconds
            
//
// additional auxiliary functions
//
    
FCT itos (Int) String       // Integer -> String
FCT succ (Int) Int
FCT prev (Int) Int
FCT max (Int, Int) Int
FCT add (Int, Int) Int
FCT sub (Int, Int) Int
FCT mult (Int, Int) Int
FCT divide (Int, Int) Int
FCT greater (Int, Int) Bool
FCT greatereq (Int, Int) Bool
FCT less (Int, Int) Bool
FCT lesseq (Int, Int) Bool
    
*/

#ifndef ELEMENT
typedef long mxi_ELEMENT;
#define ELEMENT mxi_ELEMENT
#endif


#define DYNSEM       1
#define MERGE        2
/*  #define <flag i> <2^i> */

extern char *switches[], *options[];
extern char *browser_switch;

extern void       user_init        (void);
extern void       user_exit        (void);
extern ELEMENT    max_init_fct     (ELEMENT);
extern void       max_dyninit_fct  (void);
extern void       usage            (void);

extern int main_flags;

extern int ErrorCounter;









