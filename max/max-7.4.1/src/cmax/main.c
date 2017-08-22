/*****************************************************************************
**  Basic Main Program for Compilers/Interpreters implemented with MAX
**  and CMAX
**
**  currently supports calling options, file output, timing functions and
**  error counting.
**
**  (c) Copyright 1996,1997 by Aurel Huber, TU Muenchen
**
**  Last change: Oct 30 1997
*****************************************************************************/
 
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern char *file;  /* defined by scanner or parser! */

/*#define DEBUG*/

/*
  Access to predefined MAX functions
  If a header file becomes available in the future include that instead!
*/

extern  mxi_ELEMENT  mxi_btoe( char*, int, long );
extern  mxi_ELEMENT  mxi_itoe( char*, int, long );
extern  mxi_ELEMENT  mxi_atoe( char*, int, char * );
extern  mxi_ELEMENT  mxi_ptoe( char*, int, void * );
extern  void *       mxi_etop( char*, int, ELEMENT );
extern  long         mxi_etoi( char*, int, ELEMENT );
extern  char *       mxi_etoa( char*, int, ELEMENT );

#define  btoe(VAL)       mxi_btoe(__FILE__,__LINE__,VAL)
#define  itoe(VAL)       mxi_itoe(__FILE__,__LINE__,VAL)
#define  atoe(VAL)       mxi_atoe(__FILE__,__LINE__,VAL)
#define  ptoe(VAL)       mxi_ptoe(__FILE__,__LINE__,VAL)
#define  etop(VAL)       mxi_etop(__FILE__,__LINE__,VAL)
#define  etoi(VAL)       mxi_etoi(__FILE__,__LINE__,VAL)
#define  etoa(VAL)       mxi_etoa(__FILE__,__LINE__,VAL)

/*  The predefined constants are :                                        */
#define  minimalInt()   -16777216L
#define  maximalInt()   16777215L

#define  root()         -939524095L
#define  true()         -268435455L
#define  false()        -268435456L
#define  nil()          -536805377L


/****/

extern void init_dyninput();
extern void eval_dynsem(); 

/* some definitions: */

#define NROFHANDLES 256
#define MAXFILENAMELENGTH 1024
#define MAX_NR_OF_OPTIONS 256

#ifdef NO_BROWSER
#define OptBrowser	0
#else
#ifdef BROWSEROPTION
#define OptBrowser	(etob(checkOption(atoe(browser_option))))
#else
#define OptBrowser	0
#endif
#endif


char *opt_names[MAX_NR_OF_OPTIONS];
char *opt_values[MAX_NR_OF_OPTIONS];

/*
    file output. Output files are addressed from the MAX specification
    by handles >=0 which are indices in the following table of
    file pointers.
*/

FILE *outfiles[NROFHANDLES];
int outfile_used_flags[NROFHANDLES];

char input_file_path[MAXFILENAMELENGTH];
char input_file_name[MAXFILENAMELENGTH];

ELEMENT checkOption (ELEMENT s);


extern  ELEMENT yyread( FILE * );

int ErrorCounter=0;

time_t Start, End;


ELEMENT itos(ELEMENT i){        /* Integer -> String */
    char s[20];

    sprintf(s, "%d", i);
    return atoe(s);
}

ELEMENT out(ELEMENT str){       /* Unbuffered output to stdout */
    char *s=etoa(str);

    fprintf(stdout, "%s", s);
    fflush(stdout);
    return btoe(1);
}

static void init_fileoutput (void)
{
    int i;

#ifdef DEBUG
	fprintf(stderr, "Initializing file output\n");
#endif
    outfiles[0] = stdin; outfile_used_flags[0] = 1;
    outfiles[1] = stdout; outfile_used_flags[1] = 1;    
    outfiles[2] = stderr; outfile_used_flags[2] = 1;    
    for (i=3; i<NROFHANDLES; i++) {
        outfiles[i] = (FILE *)0;
        outfile_used_flags[i] = 0;
    }
}

ELEMENT openFile (ELEMENT filename, ELEMENT mode)
{
    int i;
    
    for (i=0; i<NROFHANDLES && outfile_used_flags[i]; i++) ;
    if (i == NROFHANDLES ) {
        fprintf(stderr, "fatal error in main.c: not enough file handles!\n");
        exit(1);
    }
    
    if (!(outfiles[i] = fopen (etoa(filename), etoa(mode))))
        return itoe(-1);
        
    outfile_used_flags[i] = 1;
    return itoe(i);
}

ELEMENT writeToFile (ELEMENT handle, ELEMENT str)
{
    if (!fprintf(outfiles[etoi(handle)], "%s", etoa(str)))
        return btoe(0);
    else
        return btoe(1);
}

ELEMENT closeFile (ELEMENT handle)
{
    int i = etoi(handle);
    
    if (i<0 || i>=NROFHANDLES)
        return btoe(0);
    fclose (outfiles[i]); outfiles[i] = (FILE *)0;
    outfile_used_flags[i] = 0;
}

ELEMENT inputFilePath (void)
{
    return atoe(input_file_path);
}

ELEMENT inputFileName (void)
{
    return atoe(input_file_name);
}
         
/*
 * Management of calling options
 */

static void init_options (void)
{
	int i;
	
#ifdef DEBUG
	fprintf(stderr, "Initializing calling options\n");
#endif
	for (i=0; i<MAX_NR_OF_OPTIONS; i++) {
		opt_names[i] = "";
		opt_values[i] = "";
	}
}

ELEMENT getOption ( ELEMENT s)
{
    char *s1 = etoa(s);
    int i;

    for (i=0; i<MAX_NR_OF_OPTIONS; i++)
        if (strcmp(s1, opt_names[i])==0)
            return atoe(opt_values[i]);
    return atoe("");
}

ELEMENT checkOption ( ELEMENT s)
{
    ELEMENT v;
    char *s1;

    v = getOption(s);
    s1  = etoa(v);
    if (strcmp(s1, "true")==0 || strcmp(s1, "1")==0)
        return btoe(1);
    else
        return btoe(0);
}

void setOption (char *s1, char *s2)
{
    int i;

    for (i=0; i<MAX_NR_OF_OPTIONS; i++)
        if (strcmp(s1, opt_names[i])==0 || strcmp(opt_names[i], "")==0) {
            opt_values[i] = s2; opt_names[i] = s1; return;
        }
    fprintf(stderr,"fatal error in main.c: no more free options available!\n");
    exit(1);
}   

int get_nr_of_switch (char *option)
{
    int i;
    
    for (i=0; strcmp(switches[i], "" ) != 0 &&
              strcmp(switches[i], option) != 0; i++) ;
    
    if (strcmp(switches[i], "") == 0)
        return -1;
    else
        return i;
}

int get_nr_of_option (char *option)
{
    int i;

    for (i=0; strcmp(options[i], "" )!= 0 &&
              strcmp(options[i], option) != 0; i++) ;

    if (strcmp(options[i], "") ==0)
      return -1;
    else
      return i;
}

/*
 */


ELEMENT startTimer(void){
    time(&Start);
}

ELEMENT readTimer(void){
    time(&End);
    return itoe(End-Start);
}

ELEMENT succ(ELEMENT i){        /* Successor function */
    return itoe(etoi(i)+1);
}

ELEMENT prev(ELEMENT i){
    return itoe(etoi(i)-1);
}

ELEMENT max(ELEMENT i1, ELEMENT i2){    /* Maximum of two numbers */
    if (etoi(i1)>etoi(i2))
        return i1;
    else
        return i2;
}

ELEMENT add(ELEMENT i1, ELEMENT i2){
    return itoe(etoi(i1)+etoi(i2));
}

ELEMENT sub(ELEMENT i1, ELEMENT i2){
    return itoe(etoi(i1)-etoi(i2));
}

ELEMENT mult(ELEMENT i1, ELEMENT i2){
    return itoe(etoi(i1)*etoi(i2));
}

ELEMENT divide(ELEMENT i1, ELEMENT i2){
    return itoe(etoi(i1)/etoi(i2));
}

ELEMENT greater(ELEMENT i1, ELEMENT i2){
    return btoe(etoi(i1)>etoi(i2));
}

ELEMENT greatereq(ELEMENT i1, ELEMENT i2){
    return btoe(etoi(i1)>=etoi(i2));
}

ELEMENT lesseq(ELEMENT i1, ELEMENT i2){
    return btoe(etoi(i1)<=etoi(i2));
}

ELEMENT less(ELEMENT i1, ELEMENT i2){
    return btoe(etoi(i1)<etoi(i2));
}


ELEMENT error(void){        /* Counter for errors */
    ++ErrorCounter;
    return btoe(1);
}

ELEMENT nrOfErrors(void){
    return itoe(ErrorCounter);
}


int main(int argc,char *argv[]){
    char *filename = NULL;
    int i, j, k, option;
    ELEMENT elem;
    int printflag = 0;
    FILE *fileptr;

#ifdef DEBUG
        fprintf(stderr, "Start of main program\n");
#endif

    user_init();
    
    init_fileoutput();
    init_options();

#ifdef DEBUG
        fprintf(stderr, "Reading options\n");
#endif

    i=1;
    while(((*(argv[i])=='-')) && i<argc){
        if ( (j = get_nr_of_option(argv[i]+1)) >= 0 && i < argc-1) {
          setOption(argv[i]+1, argv[i+1]); ++i;
        }
        else if ( (j = get_nr_of_switch(argv[i]+1)) >= 0) {
            setOption(argv[i]+1, "true");
#ifdef NO_BROWSER
            if (strcmp(argv[i]+1, browser_switch) == 0 )
                fprintf(stderr, "Sorry, his version does not support "
                            "the MAX browser!\n");
#endif
	}
        else {
            usage(); exit(1);
        }
        ++i;
    }
    if (i>=argc){
        usage();
        exit(1);
    }

    for (; i<argc; i++) {

      filename = argv[i];

      fprintf(stderr, "Open file %s\n", filename);

      for (j=0; filename[j]!='\0' && j<MAXFILENAMELENGTH; j++){
          input_file_path[j]=filename[j];
      }

      if (j==MAXFILENAMELENGTH) {
        fprintf(stderr, "fatal error in main.c: Input filename too long!\n");
        exit(1);
      }

      /* delete chars after last '/'*/

      while (j>=0 && input_file_path[j]!='/') {  
          input_file_path[j] = '\0';
	  --j;
      }

      if (input_file_path[j]=='/') input_file_path[j++]='\0';
      else { input_file_path[0]='.'; input_file_path[1]='\0'; j=0; }

      for (k=0; filename[j+k]!='\0'; k++){
          input_file_name[k] = filename[j+k];
      }
      input_file_name[k] = filename[j+k];

      file = input_file_name;  /* now scanner and parser know the
                                  file name */
      
#ifdef DEBUG
      fprintf(stderr, "input file path: %s\n", input_file_path);
      fprintf(stderr, "input file name: %s\n", input_file_name);
#endif

      /*
       * open file and call parser
       */

#ifdef DEBUG
      fprintf(stderr, "open and parse input file\n");
#endif
      fileptr = fopen(filename, "r");
      if (!fileptr) {
	fprintf(stderr, "fatal error in main.c: cannot open input file!\n");
	exit(1);
      }
	
      if( (elem = yyread( fileptr )) == nil() ){
        fprintf(stdout,"fatal error in main.c: parsing failure!\n",filename);
        exit(1);
      }

      fclose(fileptr);

      if (! (main_flags & MERGE) ) {
        /*
         * start attribute evaluation for each input file if files are not
         * merged
         */

#ifdef DEBUG
        fprintf(stderr, "start attribution\n");
#endif

	max_init_fct(elem);
	
        if (main_flags & DYNSEM)
          max_dyninit_fct();

      }

    }  /* for all input files */

    if (main_flags & MERGE) {

      /*
       * start attribute evaluation for merged input files
       */

#ifdef DEBUG
      fprintf(stderr, "start attribution\n");
#endif

      if (main_flags & DYNSEM)
        max_dyninit_fct();
    }

    user_exit();
    
    if (ErrorCounter) exit(1); else exit(0);
}


/* end of file */




