/***********************************************************

******************************************************************/

/* Make it safe to include this file more than once. */

#ifndef NODE_H
#define NODE_H

/******************************************************************************
 * 
 * Node Widget (subclass of CompositeClass)
 * 
 ******************************************************************************
 *
 * Parameters:
 *
 * Name			Class		Type		Default
 * ----------------------------------------------------------------------------
 *
 * hiddenTree		HiddenTree	Boolean		FALSE
 * marked		Marked		Boolean		FALSE
 * showAttributes	ShowAttributes	Boolean		FALSE
 * label		Label		String		"NODE"
 * foreground		Foreground	Pixel		XtDefaultForeground
 * lineWidth		LineWidth	Dimension	1
 * highlightWidth	HighlightWidth	Dimension	2
 * callback		Callback	XtCallbackList  NULL
 * commandButton	CommandButton	Widget (R)      ----
 *****************************************************************************/


/* Node is derived from Composite, so no need to include public header file */

/* Define the new resources that Node uses */

#define XtNhiddenTree           "hiddenTree"
#define XtCHiddenTree           "HiddenTree"
#define XtNmarked		"marked"
#define XtCMarked		"Marked"
#define XtNshowAttributes	"showAttributes"
#define XtCShowAttributes	"ShowAttributes"
#define XtNlineWidth            "lineWidth"
#define XtCLineWidth            "LineWidth"
#define XtNhighlightWidth       "highlightWidth"
#define XtCHighlightWidth       "HighlightWidth"
#define XtNcommandButton	"commandButton"
#define XtCCommandButton	"CommandButton"

/* External reference to the class record pointer */

extern WidgetClass nodeWidgetClass;

/* Type definition for node widgets */

typedef struct _NodeRec *NodeWidget;

/* End of preprocessor directives */

#endif /* NODE_H */
