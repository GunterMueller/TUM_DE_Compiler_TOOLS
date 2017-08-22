/***********************************************************

******************************************************************/

/* Make it safe to include this file more than once. */

#ifndef NODEP_H
#define NODEP_H

/* Include the public header file for Node */

#include "bim_node.h"

/* Node is derived from Composite, so no need to include private header file */

/* Define the Node instance part */

typedef struct {
  /* New resource fields */
    Boolean             hidden_tree;    /* Node with hidden tree */
    Boolean		marked;		/* Node is marked */
    Boolean		show_attributes; /* Node with attributes */
    String              label;          /* Label of node */
    Pixel               foreground;     /* The foreground */
    Dimension           line_width;     /* The line width */
    Dimension           highlight_width;/* Highlighted line width */
    XtCallbackList      callback;       /* Callback to execute */
    Widget		command_button; /* Command Button Widget */
  /* Privat fields */
    GC                  gc;             /* The graphic context */
    GC                  gc_highlighted; /* The highlighted context */
    Boolean             highlighted;    /* Widget highlighted */
} NodePart;

/* Define the full instance record */

typedef struct _NodeRec {
    CorePart            core;
    CompositePart	composite;
    NodePart            node;
} NodeRec;

/* Define class part structure */

typedef struct {
    XtPointer           extension;
} NodeClassPart;

/* Define the full class record */


typedef struct _NodeClassRec {
    CoreClassPart       core_class;
    CompositeClassPart  composite_class;
    NodeClassPart       node_class;
} NodeClassRec, *NodeClass;

/* External definition for class record */

extern NodeClassRec nodeClassRec;

/* End of preprocessor directives */

#endif /* NODEP_H */

