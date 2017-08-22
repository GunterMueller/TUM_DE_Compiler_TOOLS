
#ifndef _TPRINT_STRUCTS_H_
#define _TPRINT_STRUCTS_H_

#include <X11/Intrinsic.h>
#if 0
#include "/usr/stud/graf/fopra/export/attr.h"
#else
#include <attr_mask.h>
#endif

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
   void         *max_tree;	/* Aktueller MAX Tree (MAX_NODE *) */
   XCONTEXT	*xcontext;	/* Kontext fuer die Darstellung */
   int		incarnation;    /* Inkarnationsnummer des Kontexts */
   int		number;		/* Seriennummer des Kontexts */
   struct _Context_ *children;  /* Child Context */
   struct _Context_ *next;	/* Next Context */
   struct _Context_ *prev;	/* Previous Context */
   struct _Context_ *parent;    /* Parent Context */
   } Context;

/* Definition der X_INFO Struktur */

typedef struct _XIS_ {
   Context	*context;       	/* Zeiger auf Kontext des Knotens */
   Widget  	widget;                 /* Widget, das den Knoten darstellt */
   Boolean     	hidden_tree;    	/* Unterbaum ist zusammengefaltet */
   Boolean     	show_attributes;  	/* Attribute werden Angezeigt */
   Boolean     	marked;         	/* Knoten ist markiert */
   Widget   	attr_widget;   		/* Widget, das die Attribute darst. */
   AttrMask 	*attr_mask;		/* Zeiger auf zugeh. Attributmaske */
} X_INFO;

/* Defines fuer den Zugriff auf die MAX_NODE Struktur */

#define ShowedAttributes(n) 	((n)->x_info->show_attributes)
#define HiddenTree(n) 		((n)->x_info->hidden_tree)
#define Marked(n) 		((n)->x_info->marked)
#define Widget(n) 		((n)->x_info->widget)
#define AttrWidget(n)		((n)->x_info->attr_widget)
#define Context(n) 		((n)->x_info->context)
#define AttrMask(n)		((n)->x_info->attr_mask)


#endif
