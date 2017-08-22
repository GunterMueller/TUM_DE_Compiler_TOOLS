
#ifndef _TPRINTP_H_
#define _TPRINTP_H_

typedef struct 
   {
   Display	*display;	/* Display */
   Widget	toplevel;	/* Toplevel widget */
   XtAppContext	app_context; 	/* Kontext der Applikation */
   int		argc;		/* Anzahl der Argumente */
   char		**argv;		/* Argumentarray */
   Widget	form;		/* Form widget */
   Widget	global_menu;	/* Global menu widget */
   Widget	viewport;	/* Viewport widget */
   Widget	h_scrollbar;    /* Horizontal scrollbar des viewport */
   Widget	v_scrollbar;	/* Vertical scrollbar des viewport */
   Widget	tree;		/* Syntax tree as tree widget */
   AttrMask     *attr_mask; 
   } XCONTEXT;

typedef struct _Context_
   {
   MAX_NODE     *max_tree;	/* Aktueller MAX Tree (MAX_NODE *) */
   XCONTEXT	*xcontext;	/* Kontext fuer die Darstellung */
   int		incarnation;    /* Inkarnationsnummer des Kontexts */
   int		number;		/* Seriennummer des Kontexts */
   struct _Context_ *children;  /* Child Context */
   struct _Context_ *next;	/* Next Context */
   struct _Context_ *prev;	/* Previous Context */
   struct _Context_ *parent;    /* Parent Context */
   } Context;

#endif
