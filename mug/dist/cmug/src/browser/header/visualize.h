#ifndef VISUALIZE_H
#define VISUALIZE_H

/*
 * (c) copyright 1995 by Technische Universitaet Muenchen, Germany
 *
 *	This product is part of MUGBrowser
 *	MUGBrowser is a part of the compiler writing system
 *	MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *	Prof. Dr. J. Eickel
 *	Institut fuer Informatik
 *	Technische Universitaet Muenchen
 *	D-80290 Muenchen
 *	Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */

/* datastructure show_opts						*/
/* show_opts contains the visualization options (show/don't show).	*/
/* value = 0 means no visualization,					*/
/* value = 1 means visualization.					*/
/* special option monitortype contains the actual selected monitortype:	*/
/* value = 0 means black/white monitor					*/
/* value = 1 means grey monitor						*/
/* value = 2 means color monitor					*/

typedef struct show_opts
	{
	int nodes;
	int attributs;
	int sem_actions;
	int edges;
	int dependencies;
	int copies;
	int monitortype;
	} SO;


/* datastructure draw_pars						*/
/* draw_pars contains the draw parameters:				*/
/* *display is a pointer to the display.				*/
/* window is the root window id. (not the drawarea's id).		*/
/* gc_black, gc_red, gc_green are the graphical contextes.		*/
/* r_xmin, r_xmax, r_ymin, r_ymax define the actual redraw area.	*/
/* *xlist is a pointer to the x-list.					*/
/* *anlist is a pointer to the attribut/image configuration.		*/
/* wurzel is a pointer to the syntaxtree.				*/
/* width, height is the size of the tree in pixels.			*/

typedef struct draw_pars
	{
	Display *display;
	Window window;
	GC gc_black;
	GC gc_red;
	GC gc_green;
	int r_xmin;
	int r_xmax;
	int r_ymin;
	int r_ymax;
	x_list *xlist;
	ANList *anlist;
	TEP wurzel;
	int width;
	int height;
	} DrawPars;


/* datastructure call_params						*/
/* call_params conatins the parameters used in XtCallback functions:	*/
/* widget1 to widget3 are widget anchors.				*/
/* function is a function pointer.					*/
/* *arrow is a cursor pointer.							*/
/* *params is a pointer to a call_params datastructure.			*/

typedef struct call_params{
	Widget widget1;
	Widget widget2;
	Widget widget3;
	XtPointer pointer;
	XtCallbackProc function;
	Cursor *arrow;
	struct call_params *params;
	} CPAMS, *CPAMP;


/* procedure prototypes */

void shutdown(Widget widget);
void quit(Widget widget, XEvent *event, String *params,
 Cardinal *num_params);
void goodbye(Widget widget, XtPointer closure, XtPointer call_data);
void checksize(Widget w, CPAMP params);
void quitdialog(Widget button, XtPointer closure, XtPointer call_data);
void suretoquit(Widget quitbutton, XtPointer closure, XtPointer call_data);
void selectbw(Widget menu4entry1, XtPointer closure, XtPointer call_data);
void selectgrey(Widget menu4entry2, XtPointer closure,
 XtPointer call_data);
void selectcolor(Widget menu4entry3, XtPointer closure,
 XtPointer call_data);
void monitorinfo(Widget menu4entry5, XtPointer closure,
 XtPointer call_data);
void defaultconf(Widget menu1entry4, XtPointer closure,
 XtPointer call_data);
void loadconf(Widget menu1entry1, XtPointer closure,
 XtPointer call_data);
void loadit(Widget loaddialog, XtPointer closure,
 XtPointer call_data);
void saveconf(Widget menu1entry2, XtPointer closure,
 XtPointer call_data);
void saveit(Widget syesbutton, XtPointer closure,
 XtPointer call_data);
void modifyconf(Widget menu1entry3, XtPointer closure,
 XtPointer call_data);
void redraw_requ_im(Widget drawarea, XtPointer image_wdw, XEvent* event,
 Boolean* bool);
void redraw_requ_at(Widget drawarea, XtPointer attr_wdw, XEvent* event,
 Boolean* bool);
void redraw_image(Window image_wdw);
void redraw_attr(Window image_wdw);
void previous(Widget previousbutton, XtPointer closure, XtPointer call_data);
void next(Widget nextbutton, XtPointer closure, XtPointer call_data);
void set(Widget setbutton, XtPointer closure, XtPointer call_data);
void sel(Widget imagearea, XtPointer closure, XEvent* event,
 Boolean *bool);
void elementinfo(Widget inside, XtPointer arrow1, XEvent* event,
 Boolean* bool);
void nodeinfo(Widget inside, XtPointer closure, XtPointer call_data);
void attrinfo(Widget inside, XtPointer closure, XtPointer call_data);
void funcinfo(Widget inside, XtPointer closure, XtPointer call_data);
void redraw_config(Widget csimple, XtPointer closure, XEvent* event,
 Boolean* bool);
void configureinfo(Widget menu1entry6, XtPointer closure,
 XtPointer call_data);
void findnode(Widget menu3entry1, XtPointer closure,
 XtPointer call_data);
void findit_node(Widget nappbutton, XtPointer closure,
 XtPointer call_data);
void findattr(Widget menu3entry2, XtPointer closure,
 XtPointer call_data);
void findit_attr(Widget aappbutton, XtPointer closure,
 XtPointer call_data);
void findfunc(Widget menu3entry3, XtPointer closure,
 XtPointer call_data);
void findit_func(Widget fappbutton, XtPointer closure,
 XtPointer call_data);
void globalview(Widget menu2entry5, XtPointer closure,
 XtPointer call_data);
void redraw_globalview(Widget gsimple, XtPointer closure, XEvent* event,
 Boolean* bool);
void information(Widget infobutton, XtPointer closure,
 XtPointer call_data);
void shownodes(Widget menu3entry1, XtPointer closure,
 XtPointer call_data);
void showedges(Widget menu3entry2, XtPointer closure,
 XtPointer call_data);
void showattributs(Widget menu3entry3, XtPointer closure,
 XtPointer call_data);
void showfunctions(Widget menu3entry4, XtPointer closure,
 XtPointer call_data);
void showdependencies(Widget menu3entry5, XtPointer closure,
 XtPointer call_data);
void showcopies(Widget menu3entry5, XtPointer closure,
 XtPointer call_data);
void showinfo(Widget menu3entry7, XtPointer closure, XtPointer call_data);
void draw_attribut(ALEP attr);
void draw_semaction(SemLEP semaction);
void draw_node(TEP node);
void draw_edge(TEP node1, TEP node2);
void draw_dep_aa(ALEP attr1, ALEP attr2);
void draw_dep_sa(SemLEP semaction, ALEP attr);
void draw_dep_as(ALEP attr, SemLEP semaction);
void draw_dep_ts(TEP terminal, SemLEP semaction);
int minimize(int x1min, int x1max, int x2min, int x2max);
int absolute(int x);
void draw_dep_arrow(SemList *list, int x1, int y1, int x2, int y2);
void draw_line(SemList *list, int color, int x1, int y1, int x2, int y2);
void redraw_request(Widget drawarea, XtPointer inside,
 XtPointer call_data);
void redraw_request2(Widget drawarea, XtPointer closure, XEvent* event,
 Boolean* bool);
void new_area();
void redraw_area(int xmin, int xmax, int ymin, int ymax);
void show_tree(TEP Wurzel, int max_x, int max_y, ANList *an_liste,
 x_list *x_liste);


/* widget argument lists						*/
/* CAUTION: Regard the convention made for several argument lists when	*/
/*          modifying as some argument values are later referenced via	*/
/*          its index.							*/

/* Argument list for root-widget	*/
/* Conventions: XtNiconPixmap must be first argument.	*/
/*              XtNiconMask must be second argument.	*/

static Arg root_arglist[] = {
	{XtNiconPixmap, (XtArgVal) None},
	{XtNiconMask, (XtArgVal) None},
	{XtNiconName, (XtArgVal) "Browser"},
	{XtNtitle, (XtArgVal) "MUG Browser"},
	{XtNheight, (XtArgVal) 500},
	{XtNwidth, (XtArgVal) 700},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for entire-widget	*/
/* Conventions: none.			*/

static Arg entire_arglist[] = {
	{XtNdefaultDistance, (XtArgVal) 10},
	{XtNheight, (XtArgVal) 500},
	{XtNwidth, (XtArgVal) 700},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for inside-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNheight must be second argument.	*/
/*              XtNwidth must be third argument.	*/

static Arg inside_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNheight, (XtArgVal) 0},
	{XtNwidth, (XtArgVal) 0},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for simple-widget			*/
/* Conventions:	XtNheight must be first argument.	*/
/*		XtNwidth must be second argument.	*/
/*		XtNfromVert must be third argument.	*/

static Arg simple_arglist[] = {
	{XtNheight, (XtArgVal) 0},
	{XtNwidth, (XtArgVal) 0},
	{XtNfromVert, (XtArgVal) NULL},
	};

/* Argument list for drawarea-widget			*/
/* Conventions: XtNfromVert must be first argument.	*/
/*		XtNheight must be second argument.	*/
/*		XtNwidth must be third argument.	*/
/*		XtNforceBars must be fourth argument.	*/
/*		XtNallowHoriz must be fifth argument.	*/
/*		XtNallowVert must be sixth argument.	*/

static Arg drawarea_arglist[] = {
	{XtNfromVert, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 390},
	{XtNwidth, (XtArgVal) 680},
	{XtNforceBars, (XtArgVal) True},
	{XtNallowHoriz, (XtArgVal) True},
	{XtNallowVert, (XtArgVal) True},
	{XtNx, (XtArgVal) 10},
	{XtNy, (XtArgVal) 100},
	{XtNresizable, (XtArgVal) True},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainBottom},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainRight},
	{XtNuseBottom, (XtArgVal) True},
	{XtNuseRight, (XtArgVal) True},
	};

/* Argument list for menu1button-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/

static Arg menu1button_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Configure"},
	{XtNmenuName, (XtArgVal) "Menu1"},
	{XtNx, (XtArgVal) 10},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for menu2button-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/
/*		XtNx must be third argument.		*/

static Arg menu2button_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 110},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Find"},
	{XtNmenuName, (XtArgVal) "Menu2"},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for menu3button-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/

static Arg menu3button_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Show"},
	{XtNmenuName, (XtArgVal) "Menu3"},
	{XtNx, (XtArgVal) 210},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for menu4button-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/

static Arg menu4button_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Monitortype"},
	{XtNmenuName, (XtArgVal) "Menu4"},
	{XtNx, (XtArgVal) 310},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for quitbutton-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/

static Arg quitbutton_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Quit"},
	{XtNx, (XtArgVal) 410},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for infobutton-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNHoriz must be second argument.	*/

static Arg infobutton_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 20},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) "Information"},
	{XtNx, (XtArgVal) 510},
	{XtNy, (XtArgVal) 10},
	{XtNresizable, (XtArgVal) True},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for dialog-widget			*/
/* Conventions: XtNVert must be first argument.		*/
/*              XtNHoriz must be second argument.	*/
/*              XtNlabel must be third argument.	*/
/*              XtNheight must be fourth argument.	*/
/*              XtNwidth must be fifth argument.	*/
/*		XtNvalue must be sixth argument.	*/

static Arg dialog_arglist[] = {
	{XtNfromVert, (XtArgVal) NULL},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNlabel, (XtArgVal) NULL},
	{XtNheight, (XtArgVal) 1},
	{XtNwidth, (XtArgVal) 1},
	{XtNvalue, (XtArgVal)  NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	{XtNresizable, (XtArgVal) True},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	};

/* Argument list for diabutton-widget			*/
/* Conventions: XtNcursor must be first argument.	*/
/*              XtNfromHoriz must be second argument.	*/
/*              XtNlabel must be third argument.	*/
/*              XtNleft must be fourth argument.	*/
/*              XtNright must be fifth argument.	*/


static Arg diabutton_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNfromHoriz, (XtArgVal) NULL},
	{XtNlabel, (XtArgVal) NULL},
	{XtNleft, (XtArgVal) XawChainLeft},
	{XtNright, (XtArgVal) XawChainLeft},
	{XtNfromVert, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	{XtNresizable, (XtArgVal) True},
	{XtNbottom, (XtArgVal) XawChainTop},
	{XtNtop, (XtArgVal) XawChainTop},
	};

/* Argument list for menu1-widget			*/
/* Conventions: XtNcursor must be first argument.	*/

static Arg menu1_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNheight, (XtArgVal) 90},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu1entry1-widget			*/
/* Conventions: none.					*/

static Arg menu1entry1_arglist[] = {
	{XtNlabel, (XtArgVal) "Load"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu1entry2-widget			*/
/* Conventions: none.					*/

static Arg menu1entry2_arglist[] = {
	{XtNlabel, (XtArgVal) "Save"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 15},
	};

/* Argument list for menu1entry3-widget			*/
/* Conventions: none.					*/

static Arg menu1entry3_arglist[] = {
	{XtNlabel, (XtArgVal) "Modify"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 30},
	};

/* Argument list for menu1entry4-widget			*/
/* Conventions: none.					*/

static Arg menu1entry4_arglist[] = {
	{XtNlabel, (XtArgVal) "Default"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 45},
	};

/* Argument list for menu1entry5-widget			*/
/* Conventions: none.					*/

static Arg menu1entry5_arglist[] = {
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 60},
	};

/* Argument list for menu1entry6-widget			*/
/* Conventions: none.					*/

static Arg menu1entry6_arglist[] = {
	{XtNlabel, (XtArgVal) "Actual"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 75},
	};

/* Argument list for menu2-widget			*/
/* Conventions: XtNcursor must be first argument.	*/

static Arg menu2_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNheight, (XtArgVal) 75},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu2entry1-widget			*/
/* Conventions: none.					*/

static Arg menu2entry1_arglist[] = {
	{XtNlabel, (XtArgVal) "Node"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu2entry2-widget			*/
/* Conventions: none.					*/

static Arg menu2entry2_arglist[] = {
	{XtNlabel, (XtArgVal) "Attribute"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 15},
	};

/* Argument list for menu2entry3-widget			*/
/* Conventions: none.					*/

static Arg menu2entry3_arglist[] = {
	{XtNlabel, (XtArgVal) "Function"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 30},
	};

/* Argument list for menu2entry3-widget			*/
/* Conventions: none.					*/

static Arg menu2entry4_arglist[] = {
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 45},
	};

/* Argument list for menu2entry3-widget			*/
/* Conventions: none.					*/

static Arg menu2entry5_arglist[] = {
	{XtNlabel, (XtArgVal) "Global View"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 60},
	};
/* Argument list for menu3-widget			*/
/* Conventions: XtNcursor must be first argument.	*/

static Arg menu3_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNheight, (XtArgVal) 120},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu3entry1-widget			*/
/* Conventions: none.					*/

static Arg menu3entry1_arglist[] = {
	{XtNlabel, (XtArgVal) "Nodes"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu3entry2-widget			*/
/* Conventions: none.					*/

static Arg menu3entry2_arglist[] = {
	{XtNlabel, (XtArgVal) "Edges"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 15},
	};

/* Argument list for menu3entry3-widget			*/
/* Conventions: none.					*/

static Arg menu3entry3_arglist[] = {
	{XtNlabel, (XtArgVal) "Attributes"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 30},
	};

/* Argument list for menu3entry4-widget			*/
/* Conventions: none.					*/

static Arg menu3entry4_arglist[] = {
	{XtNlabel, (XtArgVal) "Functions"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 45},
	};

/* Argument list for menu3entry5-widget			*/
/* Conventions: none.					*/

static Arg menu3entry5_arglist[] = {
	{XtNlabel, (XtArgVal) "Dependencies"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 60},
	};

/* Argument list for menu3entry5b-widget		*/
/* Conventions: none.					*/

static Arg menu3entry5b_arglist[] = {
	{XtNlabel, (XtArgVal) "Copies"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 75},
	};

/* Argument list for menu3entry6-widget			*/
/* Conventions: none.					*/

static Arg menu3entry6_arglist[] = {
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 90},
	};

/* Argument list for menu3entry7-widget			*/
/* Conventions: none.					*/

static Arg menu3entry7_arglist[] = {
	{XtNlabel, (XtArgVal) "Actual"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 105},
	};

/* Argument list for menu4-widget			*/
/* Conventions: XtNcursor must be first argument.	*/

static Arg menu4_arglist[] = {
	{XtNcursor, (XtArgVal) None},
	{XtNheight, (XtArgVal) 75},
	{XtNwidth, (XtArgVal) 90},
	{XtNlabel, (XtArgVal) NULL},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu4entry1-widget			*/
/* Conventions: none.					*/

static Arg menu4entry1_arglist[] = {
	{XtNlabel, (XtArgVal) "Black/White"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 0},
	};

/* Argument list for menu4entry2-widget			*/
/* Conventions: none.					*/

static Arg menu4entry2_arglist[] = {
	{XtNlabel, (XtArgVal) "Grey Scale"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 15},
	};

/* Argument list for menu4entry3-widget			*/
/* Conventions: none.					*/

static Arg menu4entry3_arglist[] = {
	{XtNlabel, (XtArgVal) "Color"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 30},
	};

/* Argument list for menu4entry4-widget			*/
/* Conventions: none.					*/

static Arg menu4entry4_arglist[] = {
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 45},
	};

/* Argument list for menu4entry5-widget			*/
/* Conventions: none.					*/

static Arg menu4entry5_arglist[] = {
	{XtNlabel, (XtArgVal) "Actual"},
	{XtNx, (XtArgVal) 0},
	{XtNy, (XtArgVal) 60},
	};


/* root-widget action list */

static XtActionsRec root_actions[] = {
	{"quit", quit},
	};


#endif
