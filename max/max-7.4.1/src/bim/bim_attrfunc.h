#ifndef _ATTR_FUNCTS_
#define _ATTR_FUNCTS_

#include "bim_nodeinfo.h"


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
extern void       UpdateMask(Widget,XtPointer,XtPointer);
extern void       PopdownNameShell(Widget,XtPointer,XtPointer);
extern void       PopdownMask(Widget,XtPointer,XtPointer);
extern AttrMask * CopyAttrMask(AttrMask *);
extern AttrMask * GetAttrMask();
extern void       DestroyAttrMask(AttrMask *);
extern Widget     CreateGlobalMenu(Widget,MAX_NODE *,AttrMask *);
extern void       GetNodeId(Widget,XtPointer,XtPointer);
extern void       NodeMenuNotify(Widget,XtPointer,XtPointer);
extern void       CreateNodeMenu(Widget);

#endif
