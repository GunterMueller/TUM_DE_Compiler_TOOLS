/***********************************************************

******************************************************************/

#include <X11/IntrinsicP.h>     /* Intrinsics header file */
#include <X11/StringDefs.h>     /* Resource string definitions */
#include "bim_nodep.h"          /* Node private header file */
#include <X11/Xaw/Command.h>    /* Command public header file */

#define Offset(field) XtOffsetOf(NodeRec, node.field)

static XtResource resources[] = {
    {XtNhiddenTree, XtCHiddenTree, XtRBoolean, sizeof(Boolean),
        Offset(hidden_tree), XtRImmediate, (XtPointer) FALSE},
    {XtNmarked, XtCMarked, XtRBoolean, sizeof(Boolean),
        Offset(marked), XtRImmediate, (XtPointer) FALSE},
    {XtNshowAttributes, XtCShowAttributes, XtRBoolean, sizeof(Boolean),
        Offset(show_attributes), XtRImmediate, (XtPointer) FALSE},
    {XtNlabel, XtCLabel, XtRString, sizeof(String),
        Offset(label), XtRString, "NODE"},
    {XtNcallback, XtCCallback, XtRCallback, sizeof(XtPointer),
        Offset(callback), XtRCallback, (XtPointer) NULL},
    {XtNforeground, XtCForeground, XtRPixel, sizeof(Pixel),
        Offset(foreground), XtRString, XtDefaultForeground},
    {XtNlineWidth, XtCLineWidth, XtRDimension, sizeof(Dimension),
        Offset(line_width), XtRImmediate, (XtPointer) 1},
    {XtNhighlightWidth, XtCHighlightWidth, XtRDimension, sizeof(Dimension),
        Offset(highlight_width), XtRImmediate, (XtPointer) 2},
    {XtNcommandButton, XtCReadOnly, XtRWidget, sizeof(Widget),
	Offset(command_button), XtRImmediate, (XtPointer) NULL}
};

#undef Offset

#define CommandChild(w) (((NodeWidget) w)->composite.children[0])
#define AttributeChild(w) (((NodeWidget) w)->composite.children[1])

/* Forward declarations */

static void Initialize(), Realize(), Destroy(), Redisplay(),
            Select(), Unselect();
static Boolean SetValues();

static void InsertChild(), DeleteChild(), ChangeManaged();
static XtGeometryResult GeometryManager();


/* Translations */

static char overrideTranslations[] =
    "<Btn1Up>		: notifyNode(1) unset()		\n\
     <Btn2Down>		: set()				\n\
     <Btn2Up>		: notifyNode(2) unset() 	\n\
     <Btn3Down>		: set()				\n\
     <Btn3Up>		: notifyNode(3) unset() 	\n\
     <EnterWindow> 	: highlightNode() highlight()	\n\
     <LeaveWindow> 	: unhighlightNode() reset()";

static void Highlight(), Unhighlight(), Notify();

static XtActionsRec actions[] = {
    {"highlightNode",   Highlight},
    {"unhighlightNode", Unhighlight},
    {"notifyNode",	Notify},
};

/* Class record declaration */

NodeClassRec nodeClassRec = {
    /* Core class part */
  {
    /* superclass            */ (WidgetClass) &compositeClassRec,
    /* class_name            */ "Node",
    /* widget_size           */ sizeof(NodeRec),
    /* class_initialize      */ NULL,
    /* class_part_initialize */ NULL,
    /* class_inited          */ FALSE,
    /* initialize            */ Initialize,
    /* initialize_hook       */ NULL,
    /* realize               */ XtInheritRealize,
    /* actions               */ actions,
    /* num_actions           */ XtNumber(actions),
    /* resources             */ resources,
    /* num_resources         */ XtNumber(resources),
    /* xrm_class             */ NULLQUARK,
    /* compress_motion       */ TRUE,
    /* compress_exposure     */ XtExposeCompressMultiple,
    /* compress_enterleave   */ TRUE,
    /* visible_interest      */ FALSE,
    /* destroy               */ Destroy,
    /* resize                */ NULL,
    /* expose                */ Redisplay,
    /* set_values            */ SetValues,
    /* set_values_hook       */ NULL,                   
    /* set_values_almost     */ XtInheritSetValuesAlmost,  
    /* get_values_hook       */ NULL,
    /* accept_focus          */ NULL,
    /* version               */ XtVersion,
    /* callback offsets      */ NULL,
    /* tm_table              */ NULL,
    /* query_geometry        */ XtInheritQueryGeometry, 
    /* display_accelerator   */ NULL,
    /* extension             */ NULL,
  },
   /* Composit class part */
  {
    /* geometry_manager      */ GeometryManager,
    /* change_managed        */ ChangeManaged,
    /* insert_child          */ InsertChild,
    /* delete_child          */ DeleteChild,
    /* extension             */ NULL,
  },
   /* Node class part */
  {
    /* extension             */ NULL,
  }
};

WidgetClass nodeWidgetClass = (WidgetClass) &nodeClassRec;


static void Highlight(w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    NodeWidget nw = (NodeWidget) XtParent(w);

    nw->node.highlighted = TRUE;

    /*
     * Expose only if hidden_tree
     */

    if (XtIsRealized((Widget) nw) && nw->node.hidden_tree)
       {
       XClearWindow(XtDisplay(nw), XtWindow(nw));
       (*(XtClass(nw)->core_class.expose))((Widget) nw, event, NULL);
       }

}

static void Unhighlight(w, event, params, num_params)
    Widget w;
    XEvent *event;
    String *params;
    Cardinal *num_params;
{
    NodeWidget nw = (NodeWidget) XtParent(w);

    nw->node.highlighted = FALSE;

    /*
     * Expose only if hidden_tree
     */

    if (XtIsRealized((Widget) nw) && nw->node.hidden_tree)
       {
       XClearWindow(XtDisplay(nw), XtWindow(nw));
       (*(XtClass(nw)->core_class.expose))((Widget) nw, event, NULL);
       }
}

static void Notify(w, event, params, num_params)
   Widget w;
   XEvent *event;
   String *params;
   Cardinal *num_params;
{
   Dimension width, height;
   NodeWidget nw = (NodeWidget) XtParent(w);

#ifdef WDEBUG
printf("Notify()\n");
#endif

   XtVaGetValues(w, XtNwidth, &width, XtNheight, &height, NULL);

   if (event != NULL && event->type == ButtonRelease &&
       event->xany.window == XtWindow(w))
      {
      XButtonEvent *b = &event->xbutton;
      if (b->x < 0 || b->y < 0 || b->x >= width || b->y >= height)
         return;
      }

#ifdef WDEBUG
printf("vor Callback\n");
#endif


    XtCallCallbackList((Widget) nw, nw->node.callback, 
		       (XtPointer) atoi(params[0]));

#ifdef WDEBUG
printf("nach Callback\n");
#endif
}


static GC GetGC(nw,line_width)
    NodeWidget nw;
    Dimension  line_width;
{
    XtGCMask  valuemask = GCForeground | GCLineWidth;
    XGCValues values;
    
    values.foreground = nw->node.foreground;

    if (line_width != 0)
       values.line_width = line_width;
    else
       values.line_width = 1;

    return XtGetGC((Widget) nw, valuemask, &values);
}


static void CalculateSize(nw, width, height)
    NodeWidget nw;
    Dimension *width, *height;
{
    int command_width = CommandChild(nw)->core.width + 
                        2*CommandChild(nw)->core.border_width,
        command_height = CommandChild(nw)->core.height + 
                         2*CommandChild(nw)->core.border_width,
        attr_width = 0,
	attr_height = 0,
        max;

#ifdef WDEBUG
printf("CalculateSize()\n");
#endif

    max = command_width > 2*command_height ? command_width : 2*command_height;

    if (nw->node.show_attributes == TRUE && nw->composite.num_children > 1)
       {
       XtManageChild(AttributeChild(nw));
       attr_width = AttributeChild(nw)->core.width + 
                        2*AttributeChild(nw)->core.border_width;
       attr_height = AttributeChild(nw)->core.height + 
                        2*AttributeChild(nw)->core.border_width;
       }

    *width = command_width > attr_width ? command_width : attr_width;
    if (nw->node.hidden_tree == TRUE)
        *height = attr_height + max;
    else
        *height = attr_height + command_height;
}

static void PositionChildren(nw)
   NodeWidget nw;
{
#define Abs(n) ((n)>0?(n):0)

   int attr_width, attr_height, command_width;

#ifdef WDEBUG
printf("PositionChildren()\n");
#endif

   if (nw->node.show_attributes == TRUE && nw->composite.num_children > 1)
      {
      attr_width = AttributeChild(nw)->core.width + 
                        2*AttributeChild(nw)->core.border_width;
      attr_height = AttributeChild(nw)->core.height + 
                        2*AttributeChild(nw)->core.border_width;
      command_width = CommandChild(nw)->core.width +
			2*CommandChild(nw)->core.border_width;
      XtMoveWidget(AttributeChild(nw),Abs(command_width - attr_width)/2,0);
      XtMoveWidget(CommandChild(nw),Abs(attr_width - command_width)/2,
				    attr_height);
      }
   else
      {
      XtMoveWidget(CommandChild(nw),0,0);
      if (nw->composite.num_children > 1)
         XtMoveWidget(AttributeChild(nw),0,0);
      }

#undef Abs
}

/******************************************************************************

 Procedures for CORE part

******************************************************************************/

static void Initialize(req, new, args, num_args)
    Widget req, new;
    ArgList args;
    Cardinal *num_args;
{
    Pixel    foreground, background;
    NodeWidget nw = (NodeWidget) new;

#ifdef WDEBUG
printf("Initialize()\n");
#endif

    /*
     * Build the command widget
     */

    nw->node.label = XtNewString(nw->node.label);
    nw->node.command_button = XtVaCreateManagedWidget(
		       "Command", 
		       commandWidgetClass,
                       new,
                       XtNlabel, nw->node.label,
                       XtNforeground, nw->node.foreground,
                       XtNborderWidth, nw->node.line_width,
                       XtNhighlightThickness, nw->node.highlight_width,
		       NULL);

    XtOverrideTranslations(CommandChild(nw),
			   XtParseTranslationTable(overrideTranslations));

    /*
     * Is the node marked ?
     */

    if (nw->node.marked == TRUE)
       {
       XtVaGetValues(CommandChild(nw),
       		  XtNforeground, &foreground,
		  XtNbackground, &background,
		  NULL);
       XtVaSetValues(CommandChild(nw),
		  XtNforeground, background,
		  XtNbackground, foreground,
		  NULL);
        }
                                       
    /*
     * Are the attributes shown ?
     */

    if (nw->composite.num_children > 1)
       XtSetMappedWhenManaged(AttributeChild(nw),
			     nw->node.show_attributes);

    /*
     * General stuff
     */

    nw->node.gc = GetGC(nw,nw->node.line_width); 
    nw->node.gc_highlighted = GetGC(nw,
                               nw->node.line_width + nw->node.highlight_width);
    nw->node.highlighted = FALSE;
                                        /* Initialize Core */
    nw->core.border_width = 0;          /* No Border */

    PositionChildren(nw);
}

static void Redisplay(w, event, region)
Widget w;
XEvent *event;
Region region;
{
    NodeWidget nw = (NodeWidget) w;

    Display *disp = XtDisplay(w);
    Window   wind = XtWindow(w);
    GC       gc;

    Cardinal xpos = CommandChild(nw)->core.x,
	     ypos = CommandChild(nw)->core.y,
	     width = CommandChild(nw)->core.width,
	     ymax = nw->core.height - 1;

#ifdef WDEBUG
printf("Redisplay()\n");
#endif

    if (nw->node.highlighted)
       gc = nw->node.gc_highlighted;
    else
       gc = nw->node.gc;

    /*
     * Draw triangle
     */

    if (nw->node.hidden_tree)
       {
       XDrawLine(disp, wind, gc, xpos + width/2, ypos, xpos, ymax);
       XDrawLine(disp, wind, gc, xpos + width/2, ypos, xpos + width, ymax);
       XDrawLine(disp, wind, gc, xpos, ymax, xpos + width, ymax);
       }
}


static void Destroy(w)
    Widget w;
{
    NodeWidget nw = (NodeWidget) w;

#ifdef WDEBUG
printf("Destroy()\n");
#endif
   
    XtFree((char *) nw->node.label);
}

static Boolean SetValues(old, req, new, args, num_args)
    Widget old, req, new;
    ArgList args;
    Cardinal *num_args;
{
    String params[1];
    Cardinal num_params;
    Pixel foreground, background;
    register NodeWidget oldnw = (NodeWidget) old;
    register NodeWidget newnw = (NodeWidget) new;
    Boolean redraw = FALSE;

#ifdef WDEBUG
printf("SetValues()\n");
#endif

#define NE(field) (oldnw->field != newnw->field)

    if (NE(node.label)) 
	{
        XtFree((char *) oldnw->node.label);
        newnw->node.label = XtNewString(newnw->node.label);
        XtVaSetValues(CommandChild(newnw), 
		  XtNlabel, newnw->node.label,
		  NULL);
        redraw = TRUE;
        }

    if (NE(node.marked))
       {
       XtVaGetValues(CommandChild(oldnw),
       		  XtNforeground, &foreground,
		  XtNbackground, &background,
		  NULL);
       XtVaSetValues(CommandChild(newnw),
		  XtNforeground, background,
		  XtNbackground, foreground,
		  NULL);
       redraw = TRUE;
       }

    if (NE(node.show_attributes))
       {
       if (oldnw->composite.num_children < 2)
	  {
          params[0] = XtClass(new)->core_class.class_name;
          num_params = 1;
          XtAppErrorMsg(XtWidgetToApplicationContext(new),
	      "childError", "number", "WidgetError",
	      "Widget %s need child widget with attributes to display",
	      params, &num_params);
          }

       XtSetMappedWhenManaged(AttributeChild(newnw),
			      newnw->node.show_attributes);

       redraw = TRUE;
       }

    if (NE(node.hidden_tree) || redraw) 
	{
        CalculateSize(newnw, &newnw->core.width, &newnw->core.height);
	PositionChildren(newnw);
        }

    return (redraw);
#undef NE
}


/******************************************************************************

 Procedures for COMPOSITE class part

******************************************************************************/


static void InsertChild(w)
   Widget w;
{
   String params[1];
   Cardinal num_params;
   NodeWidget parent = (NodeWidget) XtParent(w);

#ifdef WDEBUG
printf("InsertChild()\n");
#endif

   /*
    * Unmap second child
    */

   if (parent->composite.num_children == 1)
      XtSetMappedWhenManaged(w,FALSE);

   if (parent->composite.num_children >= 2)
      {
      params[0] = XtClass(parent)->core_class.class_name;
      num_params = 1;
      XtAppErrorMsg(XtWidgetToApplicationContext(w),
	  "childError", "number", "WidgetError",
	  "Applications cannot add children to %s widgets",
	  params, &num_params);
      }

   (*((CompositeWidgetClass)(nodeWidgetClass->core_class.superclass))->
       composite_class.insert_child)(w);
}


static void DeleteChild(w)
   Widget w;
{
   NodeWidget parent = (NodeWidget) XtParent(w);

#ifdef WDEBUG
printf("DeleteChild()\n");
#endif

   (*((CompositeWidgetClass) (nodeWidgetClass->core_class.superclass))->
       composite_class.delete_child) (w);
}


static void ChangeManaged(w)
   Widget w;
{
   NodeWidget nw = (NodeWidget) w;
   XtWidgetGeometry request;
   XtGeometryResult result;

#ifdef WDEBUG
printf("ChangeManaged()\n");
#endif


   CalculateSize(nw, &request.width, &request.height);
   PositionChildren(nw);

   if (request.width != nw->core.width ||
       request.height != nw->core.height)
      {
      request.request_mode = CWWidth | CWHeight;
      do {
	 result = XtMakeGeometryRequest(w, &request, &request);
	 } while (result == XtGeometryAlmost);
      }

}

static XtGeometryResult GeometryManager(w, desired, allowed)
   Widget w;
   XtWidgetGeometry *desired, *allowed;
{
   NodeWidget nw = (NodeWidget) XtParent(w);
   XtWidgetGeometry request;
   XtGeometryResult result;

#ifdef WDEBUG
printf("GeometryManager()\n");
#endif

#define Wants(flag) (desired->request_mode & flag)

   /*
    * No position changes allowed!
    */

   if ((Wants(CWX) && desired->x!=w->core.x) ||
       (Wants(CWY) && desired->y!=w->core.y))
      return (XtGeometryNo);

   /*
    * Allow all resize requests.
    */

   if (Wants(XtCWQueryOnly)) 
      return (XtGeometryYes);

   if (Wants(CWWidth)) w->core.width = desired->width;
   if (Wants(CWHeight)) w->core.height = desired->height;
   if (Wants(CWBorderWidth)) w->core.border_width = desired->border_width;

   CalculateSize(nw, &request.width, &request.height);

   if (request.width != nw->core.width ||
       request.height != nw->core.height)
      {
      request.request_mode = CWWidth | CWHeight;
      do {
	 result = XtMakeGeometryRequest((Widget) nw, &request, &request);
	 } while (result == XtGeometryAlmost);
      }

   return (XtGeometryYes);

#undef Wants
}
