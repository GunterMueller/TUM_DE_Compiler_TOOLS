#ifndef _ATTR_
#define _ATTR_

typedef struct _GLMENTRIES_ {
   char *   ename;
   char *   elabel;
   Boolean  npop;
   Cardinal mno;
} Glmentries;

typedef struct _NOMENTRIES_ {
   char *  ename;
   char *  elabel;
   Boolean sectend;
} Nomentries;


#include "bim_nodeinfo.h"

typedef struct _CALLBACKSTRUCT_ {
   MAX_NODE * node;
   Widget     mwidget;
   Widget     nwidget;
   Widget *   mask_toggles;
} CallbackStruct;

typedef struct _CALLBACKNODES_ {
  MAX_NODE * first_node;
  MAX_NODE * second_node;
} CallbackNodes;

extern void       ConnectMenuToNode(MAX_NODE *,Widget);
extern void       CopyAttributeTreeCallback(Widget,XtPointer,XtPointer);
extern void       CenterNodeCallback(Widget,XtPointer,XtPointer);
extern Boolean    IsMasked(String,AttrMask *);
extern Widget     CreateAttrList(MAX_NODE *,Widget,AttrMask *);
extern void       GlobalMenuNotifyWithName(Widget,XtPointer,XtPointer);
extern void       SetCurrentGlobalIndex(Widget,XtPointer,XtPointer);
extern void       GlobalMenuNotifyWithoutName(Widget,XtPointer,XtPointer);
extern void       GetCoordinates(Widget,XtPointer,XtPointer);
extern void       PopupNameShell(Widget,XtPointer,XtPointer);
extern void       UnselectAll (Widget,XtPointer,XtPointer);
extern void       UpdateMask(Widget,XtPointer,XtPointer);
extern void       PopdownNameShell(Widget,XtPointer,XtPointer);
extern void       PopdownMask(Widget,XtPointer,XtPointer);
extern AttrMask * CopyAttrMask(AttrMask *);
extern AttrMask * GetAttrMask();
extern void       DestroyAttrMask(AttrMask *);
extern void       ResetViewport(Widget,XtPointer,XtPointer);
extern Widget     CreateGlobalMenu(Widget,MAX_NODE *,AttrMask *);
extern void       GetNodeId(Widget,XtPointer,XtPointer);
extern void       NodeMenuNotify(Widget,XtPointer,XtPointer);
extern void       CreateNodeMenu(Widget);

#endif
