
#ifndef _NODEINFO
#define _NODEINFO

#include <tprint_structs.h>

typedef char * ATTR_TYPE;

typedef struct _AIS_ {

   char * name;            /* Name of the attribute */
   char * defined_by_sort; /* Sort that defined this aattribute */
   ATTR_TYPE type;         /* Type of the attribute */
   long attr_value;        /* Value of the attribute, has to be interpreted 
			   // Depending on the type
			   */
   
}ATTR_INFO;

#if 0
typedef struct _XIS_ {
   void    *context;	   /* Context of the node */
   void    *widget;	   /* Widget for this node */
   int     hidden_tree;    /* Flag for hidden subtree */
   int     show_attributes; /* Flag for show attributes */
   int     marked;         /* Flag for marked nodes */
   void    *attr_widget;   /* Wunsch von Boris */
} X_INFO;
#endif 

typedef struct _NIS_ {
   char * name;            /* Sort of this Node as C-String */
   char ** parent_sorts;   /* NULL-pointer terminated array of parent sorts */
   int no_of_attributes;   /* Number of attributes that are defined for this 
			   // node
			   */
   ATTR_INFO * attributes; /* Array of attribute descriptions */
}NODE_INFO;


typedef struct _NOD_ {
   struct _NOD_ * parent;     /* Parent node */
   struct _NOD_ * children;   /* First child node */
   struct _NOD_ * next, * prev; /* Linked list of children */
   NODE_INFO * node_info;     /* Information about the node */
   X_INFO      * x_info;        /* Information for Xt handling */
   void * origin_node;
} MAX_NODE;

#endif









