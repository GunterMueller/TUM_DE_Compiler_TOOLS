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


/* include standard libraries:		*/
/* stdlib.h	standard C library	*/
/* stdio.h	standard input output	*/
/* malloc.h	memory allocation	*/

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>


/* include X libraries:				*/
/* Xatom.h		atomar X elements	*/
/* Intrinsics.h		X intrinsics		*/
/* StringDefs.h		X string definitions	*/
/* Shell.h		X shell environment	*/

#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>


/* include X Athena Widget libraries:					*/
/* Cardinals.h		cardinal typedefs				*/
/* Command.h		button widget					*/
/* Dialog.h		dialog widget					*/
/* Form.h		form widget					*/
/* Simple.h		simple widget					*/
/* SimpleMenu.h		simple menu widget				*/
/* SmeBSB.h		simple menu element "bitmap string bitmap"	*/
/* SmeLine.h		simple menu element line			*/
/* MenuButton.h		menu button widget				*/
/* Viewport.h		viewport widget					*/
/* Scrollbar.h		scrollbar widget				*/

#include <X11/Xaw/Cardinals.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Dialog.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Simple.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>
#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/Scrollbar.h>


/* include icon bitmaps:				*/
/* icon		MUG Browser icon			*/
/* imask	MUG Browser iconmask			*/
/* arrow1	menucursor				*/
/* arrow2       drawareacursor				*/
/* amask	cursormask				*/
/* noicon	if attribute configuration fails	*/
/* address	attribut representation image no. 00	*/
/* depth	attribut representation image no. 01	*/
/* level	attribut representation image no. 02	*/
/* list		attribut representation image no. 03	*/
/* pointer	attribut representation image no. 04	*/
/* pointers	attribut representation image no. 05	*/
/* symtab	attribut representation image no. 06	*/
/* table	attribut representation image no. 07	*/
/* tree		attribut representation image no. 08	*/
/* io		attribut representation image no. 09	*/
/* circle	attribut representation image no. 10	*/
/* diamond	attribut representation image no. 11	*/
/* pargram	attribut representation image no. 12	*/
/* pentagon	attribut representation image no. 13	*/
/* rectangle	attribut representation image no. 14	*/
/* square	attribut representation image no. 15	*/
/* triangle	attribut representation image no. 16	*/
/* cross	attribut representation image no. 17	*/
/* crystal	attribut representation image no. 18	*/
/* spindle	attribut representation image no. 19	*/
/* code		attribut representation image no. 20	*/
/* listing	attribut representation image no. 21	*/
/* text		attribut representation image no. 22	*/
/* dictionairy	attribut representation image no. 23	*/
/* document	attribut representation image no. 24	*/
/* arrow	attribut representation image no. 25	*/
/* book		attribut representation image no. 26	*/
/* chair	attribut representation image no. 27	*/
/* clock	attribut representation image no. 28	*/
/* desk		attribut representation image no. 29	*/
/* lightbulp	attribut representation image no. 30	*/
/* paper	attribut representation image no. 31	*/
/* pen		attribut representation image no. 32	*/
/* wall		attribut representation image no. 33	*/
/* man		attribut representation image no. 34	*/
/* wheel	attribut representation image no. 35	*/
/* fence	attribut representation image no. 36	*/
/* phone	attribut representation image no. 37	*/
/* pacman	attribut representation image no. 38	*/
/* face		attribut representation image no. 39	*/
/* basket	attribut representation image no. 40	*/
/* block	attribut representation image no. 41	*/
/* brick	attribut representation image no. 42	*/
/* bubble	attribut representation image no. 43	*/
/* cone		attribut representation image no. 44	*/
/* cylinder	attribut representation image no. 45	*/
/* dice		attribut representation image no. 46	*/
/* ring		attribut representation image no. 47	*/
/* hypnosis	attribut representation image no. 48	*/
/* horseshoe	attribut representation image no. 49	*/
/* zero		attribut representation image no. 50	*/
/* one		attribut representation image no. 51	*/
/* two		attribut representation image no. 52	*/
/* three	attribut representation image no. 53	*/
/* four		attribut representation image no. 54	*/
/* five		attribut representation image no. 55	*/
/* six		attribut representation image no. 56	*/
/* seven	attribut representation image no. 57	*/
/* eight	attribut representation image no. 58	*/
/* nine		attribut representation image no. 59	*/
/* capitala	attribut representation image no. 60	*/
/* capitalb	attribut representation image no. 61	*/
/* capitalc	attribut representation image no. 62	*/
/* capitald	attribut representation image no. 63	*/
/* capitale	attribut representation image no. 64	*/
/* capitalf	attribut representation image no. 65	*/
/* capitalg	attribut representation image no. 66	*/
/* capitalh	attribut representation image no. 67	*/
/* capitali	attribut representation image no. 68	*/
/* capitalj	attribut representation image no. 69	*/
/* capitalk	attribut representation image no. 70	*/
/* capitall	attribut representation image no. 71	*/
/* capitalm	attribut representation image no. 72	*/
/* capitaln	attribut representation image no. 73	*/
/* capitalo	attribut representation image no. 74	*/
/* capitalp	attribut representation image no. 75	*/
/* capitalq	attribut representation image no. 76	*/
/* capitalr	attribut representation image no. 77	*/
/* capitals	attribut representation image no. 78	*/
/* capitalt	attribut representation image no. 79	*/
/* capitalu	attribut representation image no. 80	*/
/* capitalv	attribut representation image no. 81	*/
/* capitalw	attribut representation image no. 82	*/
/* capitalx	attribut representation image no. 83	*/
/* capitaly	attribut representation image no. 84	*/
/* capitalz	attribut representation image no. 85	*/
/* smalla	attribut representation image no. 86	*/
/* smallb	attribut representation image no. 87	*/
/* smallc	attribut representation image no. 88	*/
/* smalld	attribut representation image no. 89	*/
/* smalle	attribut representation image no. 90	*/
/* smallf	attribut representation image no. 91	*/
/* smallg	attribut representation image no. 92	*/
/* smallh	attribut representation image no. 93	*/
/* smalli	attribut representation image no. 94	*/
/* smallj	attribut representation image no. 95	*/
/* smallk	attribut representation image no. 96	*/
/* smalll	attribut representation image no. 97	*/
/* smallm	attribut representation image no. 98	*/
/* smalln	attribut representation image no. 99	*/
/* smallo	attribut representation image no. 100	*/
/* smallp	attribut representation image no. 101	*/
/* smallq	attribut representation image no. 102	*/
/* smallr	attribut representation image no. 103	*/
/* smalls	attribut representation image no. 104	*/
/* smallt	attribut representation image no. 105	*/
/* smallu	attribut representation image no. 106	*/
/* smallv	attribut representation image no. 107	*/
/* smallw	attribut representation image no. 108	*/
/* smallx	attribut representation image no. 109	*/
/* smally	attribut representation image no. 110	*/
/* smallz	attribut representation image no. 111	*/

#include "../icons/internal/icon"
#include "../icons/internal/imask"
#include "../icons/internal/arrow1"
#include "../icons/internal/arrow2"
#include "../icons/internal/amask"
#include "../icons/internal/noicon"
#include "../icons/compiler/address"
#include "../icons/compiler/depth"
#include "../icons/compiler/level"
#include "../icons/compiler/list"
#include "../icons/compiler/pointer"
#include "../icons/compiler/pointers"
#include "../icons/compiler/symtab"
#include "../icons/compiler/table"
#include "../icons/compiler/tree"
#include "../icons/compiler/io"
#include "../icons/geometrics/circle"
#include "../icons/geometrics/diamond"
#include "../icons/geometrics/pargram"
#include "../icons/geometrics/pentagon"
#include "../icons/geometrics/rectangle"
#include "../icons/geometrics/square"
#include "../icons/geometrics/triangle"
#include "../icons/geometrics/cross"
#include "../icons/geometrics/crystal"
#include "../icons/geometrics/spindle"
#include "../icons/listings/code"
#include "../icons/listings/listing"
#include "../icons/listings/text"
#include "../icons/listings/dictionairy"
#include "../icons/listings/document"
#include "../icons/objects/arrow"
#include "../icons/objects/book"
#include "../icons/objects/chair"
#include "../icons/objects/clock"
#include "../icons/objects/desk"
#include "../icons/objects/lightbulp"
#include "../icons/objects/paper"
#include "../icons/objects/pen"
#include "../icons/objects/wall"
#include "../icons/objects/man"
#include "../icons/objects/wheel"
#include "../icons/objects/fence"
#include "../icons/objects/phone"
#include "../icons/objects/pacman"
#include "../icons/objects/face"
#include "../icons/solids/basket"
#include "../icons/solids/block"
#include "../icons/solids/brick"
#include "../icons/solids/bubble"
#include "../icons/solids/cone"
#include "../icons/solids/cylinder"
#include "../icons/solids/dice"
#include "../icons/solids/ring"
#include "../icons/solids/hypnosis"
#include "../icons/solids/horseshoe"
#include "../icons/numbers/zero"
#include "../icons/numbers/one"
#include "../icons/numbers/two"
#include "../icons/numbers/three"
#include "../icons/numbers/four"
#include "../icons/numbers/five"
#include "../icons/numbers/six"
#include "../icons/numbers/seven"
#include "../icons/numbers/eight"
#include "../icons/numbers/nine"
#include "../icons/letters/capitala"
#include "../icons/letters/capitalb"
#include "../icons/letters/capitalc"
#include "../icons/letters/capitald"
#include "../icons/letters/capitale"
#include "../icons/letters/capitalf"
#include "../icons/letters/capitalg"
#include "../icons/letters/capitalh"
#include "../icons/letters/capitali"
#include "../icons/letters/capitalj"
#include "../icons/letters/capitalk"
#include "../icons/letters/capitall"
#include "../icons/letters/capitalm"
#include "../icons/letters/capitaln"
#include "../icons/letters/capitalo"
#include "../icons/letters/capitalp"
#include "../icons/letters/capitalq"
#include "../icons/letters/capitalr"
#include "../icons/letters/capitals"
#include "../icons/letters/capitalt"
#include "../icons/letters/capitalu"
#include "../icons/letters/capitalv"
#include "../icons/letters/capitalw"
#include "../icons/letters/capitalx"
#include "../icons/letters/capitaly"
#include "../icons/letters/capitalz"
#include "../icons/letters/smalla"
#include "../icons/letters/smallb"
#include "../icons/letters/smallc"
#include "../icons/letters/smalld"
#include "../icons/letters/smalle"
#include "../icons/letters/smallf"
#include "../icons/letters/smallg"
#include "../icons/letters/smallh"
#include "../icons/letters/smalli"
#include "../icons/letters/smallj"
#include "../icons/letters/smallk"
#include "../icons/letters/smalll"
#include "../icons/letters/smallm"
#include "../icons/letters/smalln"
#include "../icons/letters/smallo"
#include "../icons/letters/smallp"
#include "../icons/letters/smallq"
#include "../icons/letters/smallr"
#include "../icons/letters/smalls"
#include "../icons/letters/smallt"
#include "../icons/letters/smallu"
#include "../icons/letters/smallv"
#include "../icons/letters/smallw"
#include "../icons/letters/smallx"
#include "../icons/letters/smally"
#include "../icons/letters/smallz"


/* include MUG browser headerfiles:			*/
/* browse_const.h	defined constants		*/
/* browse_len.h		defined sizes			*/
/* browse_types.h	browser datatypes		*/
/* configure.h		configure function prototypes	*/
/* visualize.h		visualizor header		*/

#include "../header/browse_const.h"
#include "../header/browse_len.h"
#include "../header/browse_types.h"
#include "../header/configure.h"
#include "../header/visualize.h"


/* declare variables global in this module:			*/
/* opts contains show options.					*/
/* dparms contains the draw parameters.				*/
/* wm_delete_window is used for window manager abort requests.	*/
/* drawarea ist the widget of the drawarea.			*/
/* redraw_window is the window id of the redraw area.		*/
/* black, dark_grey, light_grey, white, red and green contain 	*/
/* the X-colors.						*/
/* config_file is the file containing the saved/loaded		*/
/* attribute/image configuration.				*/
/* act_modify is the last modified attribute/image setting.	*/
/* act_icon is the selected icon when modifying an a/i setting.	*/
/* last_node, last_attr and last_func point to the last		*/
/* matching appearance found. (see find menu)			*/
/* attr_icon[112] contains all attribut images.			*/
/* attr_name[111], noicon_name contains all a. images' names.	*/

static SO opts;
static DrawPars dparms;
static Atom wm_delete_window;
static Widget drawarea;
static Window redraw_window = 0;
static XColor black, dark_grey, light_grey, white, red, green;
static String config_file = "";
static int act_modify = 0, act_icon = -1;
static XLEP last_node = NULL, last_attr = NULL, last_func = NULL;
static XImage *attr_icon[111], *noicon;
static char *attr_name[111], *noicon_name;


/* procedure shutdown					*/
/* shuts down the MUG Browser application.		*/
/* parameters:						*/
/* Widget widget	any widget of the application	*/

void shutdown(Widget widget)
{
XDestroyWindow(dparms.display, dparms.window);
XCloseDisplay(dparms.display);
exit(0);
} /* shutdown */


/* procedure quit					*/
/* quits application when requested from windowmanager.	*/
/* parameters:						*/
/* Widget widget	root widget of the application	*/
/* XEvent *event	window manager event		*/
/* String *params	not used			*/
/* Cardinal *num_params	not used			*/

void quit(Widget widget, XEvent *event, String *params,
 Cardinal *num_params)
{
if (event->type == ClientMessage && event->xclient.data.l[0] != wm_delete_window) {
  XBell(XtDisplay(widget), 0);
  return;
  } /* if */
printf("Message from MUG Browser: window manager abort request caused MUG Browser to quit. ");
printf("Message from MUG Browser: did you quit the application's window? ");
printf("Message from MUG Browser: anyway ... goodbye!\n");
shutdown(widget);
} /* quit */


/* procedure goodbye					*/
/* quits application when requested from user via quit	*/
/* button.						*/
/* parameters:						*/
/* Widget widget	any widget of the application	*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void goodbye(Widget widget, XtPointer closure, XtPointer call_data)
{
printf("Message from MUG Browser: goodbye!\n");
shutdown(widget);
} /* goodbye */


/* procedure checksize					*/
/* checks the size of a widget and calls quitdialog if	*/
/* size is 1x1.						*/
/* parameters:						*/
/* Widget w		widget to be checked		*/
/* CPAMP params		parameters (see call_params)	*/

void checksize(Widget w, CPAMP params)
{
Arg check_arglist[] = {
  {XtNheight, (XtArgVal) 0},
  {XtNwidth, (XtArgVal) 0},
  };

XtGetValues(w, check_arglist, XtNumber(check_arglist));
if (check_arglist[0].value == 1) {
  printf("Message from MUG Browser: subwindow does not fit - please resize application's window.\n");
  quitdialog(w, (XtPointer) params, (XtPointer) NULL);
  } /* if */
} /* checksize */


/* procedure quitdialog					*/
/* quits dialog widgets.				*/
/* parameters:						*/
/* Widget w		not used			*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void quitdialog(Widget w, XtPointer closure, XtPointer call_data)
{
CPAMP params = (CPAMP) closure;

XtDestroyWidget(params->widget3);
if (params->function != NULL) XtAddCallback(params->widget2, XtNcallback,
 params->function, (XtPointer) params->params);
} /* quitdialog */


/* procedure suretoquit					*/
/* opens a dialog window "Sure to quit" so the user can	*/
/* confirm or cancel the quit selection.		*/
/* parameters:						*/
/* Widget quitbutton	quitbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void suretoquit(Widget quitbutton, XtPointer closure, XtPointer call_data)
{
Widget quitsure, qbutton1, qbutton2;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "   Are you sure to quit\nthe fabulous MUG Browser ?";
quitsure = XtCreateWidget("QuitDialog", dialogWidgetClass, params->widget1,
 dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = quitbutton;
params->widget3 = quitsure;
params->function = suretoquit;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Confirm";
qbutton2 = XtCreateManagedWidget("QButton2", commandWidgetClass, quitsure,
 diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Cancel";
qbutton1 = XtCreateManagedWidget("QButton1", commandWidgetClass, quitsure,
 diabutton_arglist, XtNumber(diabutton_arglist));XtAddCallback(qbutton1, XtNcallback, quitdialog, (XtPointer) params);
XtAddCallback(qbutton2, XtNcallback, goodbye, (XtPointer) NULL);
XtManageChild(quitsure);
XtRemoveCallback(quitbutton, XtNcallback, suretoquit, closure);
checksize(quitsure, params);
} /* suretoquit */


/* procedure selectbw					*/
/* selects black/white monitor.				*/
/* parameters:						*/
/* Widget menu4entry1	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void selectbw(Widget menu4entry1, XtPointer closure, XtPointer call_data)
{
XSetForeground(dparms.display, dparms.gc_red, black.pixel);
XSetForeground(dparms.display, dparms.gc_green, black.pixel);
opts.monitortype = 0;
new_area();
} /* selectbw */


/* procedure selectgrey					*/
/* selects grey monitor.				*/
/* parameters:						*/
/* Widget menu4entry2	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void selectgrey(Widget menu4entry2, XtPointer closure, XtPointer call_data)
{
XSetForeground(dparms.display, dparms.gc_red, light_grey.pixel);
XSetForeground(dparms.display, dparms.gc_green, dark_grey.pixel);
opts.monitortype = 1;
new_area();
} /* selectgrey */


/* procedure selectcolor				*/
/* selects color monitor.				*/
/* parameters:						*/
/* Widget menu4entry3	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void selectcolor(Widget menu4entry3, XtPointer closure, XtPointer call_data)
{
XSetForeground(dparms.display, dparms.gc_red, red.pixel);
XSetForeground(dparms.display, dparms.gc_green, green.pixel);
opts.monitortype = 2;
new_area();
} /* selectcolor */


/* procedure monitorinfo				*/
/* opens a dialog window which shows the actual monitor */
/* selection.						*/
/* parameters:						*/
/* Widget menu4entry5	menu4entry5 widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void monitorinfo(Widget menu4entry5, XtPointer closure, XtPointer call_data)
{
Widget monitordialog, mbutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
switch(opts.monitortype) {
case 0:
  dialog_arglist[2].value = (XtArgVal) "Selected Monitortype:\nBlack/White";
  break;
case 1:
  dialog_arglist[2].value = (XtArgVal) "Selected Monitortype:\nGrey Scale";
  break;
case 2:
  dialog_arglist[2].value = (XtArgVal) "Selected Monitortype:\nColor";
  break;
default:
  dialog_arglist[2].value = (XtArgVal) "Selected Monitortype:\nUnknown";
  break;
  } /* switch */
monitordialog = XtCreateWidget("MonitorDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu4entry5;
params->widget3 = monitordialog;
params->function = monitorinfo;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
mbutton = XtCreateManagedWidget("MButton", commandWidgetClass, monitordialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(mbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(monitordialog);
XtRemoveCallback(menu4entry5, XtNcallback, monitorinfo, closure);
checksize(monitordialog, params);
} /* monitorinfo */


/* procedure defaultconf				*/
/* selects default icon/attribut configuration.		*/
/* parameters:						*/
/* Widget menu1entry4	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void defaultconf(Widget menu1entry4, XtPointer closure,
 XtPointer call_data)
{
if (!(config_load(dparms.anlist, "default.config"))) {
  image_refresh(dparms.wurzel, dparms.anlist);
  new_area();
  } /* if */
else
 printf("Message from MUG Browser: could not open file default.config - no configuration loaded.\n");
} /* defaultconf */


/* procedure loadconf						*/
/* opens window to enter icon/attribut configuration file.	*/
/* parameters:							*/
/* Widget menu1entry1	menu1entry1 widget			*/
/* XtPointer closure	parameters (see call_params)		*/
/* XtPointer call_data	not used				*/

void loadconf(Widget menu1entry1, XtPointer closure,
 XtPointer call_data)
{
Widget loaddialog, lyesbutton, lnobutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Load Attribute/Image Configuration:";
dialog_arglist[5].value = (XtArgVal) config_file;
loaddialog = XtCreateWidget("LoadDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
dialog_arglist[5].value = (XtArgVal) NULL;
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu1entry1;
params->widget3 = loaddialog;
params->function = loadconf;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Load";
lyesbutton = XtCreateManagedWidget("LYesButton", commandWidgetClass, loaddialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Cancel";
lnobutton = XtCreateManagedWidget("LNoButton", commandWidgetClass, loaddialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(lyesbutton, XtNcallback, loadit, (XtPointer) params);
XtAddCallback(lnobutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(loaddialog);
XtRemoveCallback(menu1entry1, XtNcallback, loadconf, closure);
checksize(loaddialog, params);
} /* loadconf */


/* procedure loadit					*/
/* loads icon/attribut configuration from file.		*/
/* parameters:						*/
/* Widget lyesbutton	lyesbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void loadit(Widget lyesbutton, XtPointer closure,
 XtPointer call_data)
{
CPAMP params = (CPAMP) closure;

config_file = XawDialogGetValueString(params->widget3);
if (!(config_load(dparms.anlist, config_file))) {
  image_refresh(dparms.wurzel, dparms.anlist);
  new_area();
  } /* if */
else
 printf("WARNING: could not open file %s - no configuration loaded.\n",
 config_file);
quitdialog(lyesbutton, closure, NULL);
} /* loadit */


/* procedure saveconf						*/
/* opens window to enter icon/attribut configuration file.	*/
/* parameters:							*/
/* Widget menu1entry2	menu1entry2 widget			*/
/* XtPointer closure	parameters (see call_params)		*/
/* XtPointer call_data	not used				*/

void saveconf(Widget menu1entry2, XtPointer closure,
 XtPointer call_data)
{
Widget savedialog, syesbutton, snobutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Save Attribute/Image Configuration:";
dialog_arglist[5].value = (XtArgVal) config_file;
savedialog = XtCreateWidget("SaveDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
dialog_arglist[5].value = (XtArgVal) NULL;
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu1entry2;
params->widget3 = savedialog;
params->function = saveconf;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Save";
syesbutton = XtCreateManagedWidget("SYesButton", commandWidgetClass, savedialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Cancel";
snobutton = XtCreateManagedWidget("SNoButton", commandWidgetClass, savedialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(syesbutton, XtNcallback, saveit, (XtPointer) params);
XtAddCallback(snobutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(savedialog);
XtRemoveCallback(menu1entry2, XtNcallback, saveconf, closure);
checksize(savedialog, params);
} /* saveconf */


/* procedure saveit					*/
/* saves icon/attribut configuration to file.		*/
/* parameters:						*/
/* Widget lyesbutton	syesbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void saveit(Widget syesbutton, XtPointer closure,
 XtPointer call_data)
{
CPAMP params = (CPAMP) closure;

config_file = XawDialogGetValueString(params->widget3);
if (config_save(dparms.anlist, config_file))
 printf("WARNING: could not create file %s - configuration not saved.\n",
 config_file);
quitdialog(syesbutton, closure, NULL);
} /* saveit */


/* procedure modifyconf					*/
/* opens window to modify icon/attribut configuration.	*/
/* parameters:						*/
/* Widget menu1entry3	menu1entry3 widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void modifyconf(Widget menu1entry3, XtPointer closure,
 XtPointer call_data)
{
Widget modifydialog, previousbutton, nextbutton, setbutton, exitbutton,
 imagearea, attrarea;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);
Window attr_wdw, image_wdw;
int i;
ANLEP ptr;

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Modify Attribute/Image Configuration:";
modifydialog = XtCreateWidget("ModifyDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu1entry3;
params->widget3 = modifydialog;
params->function = modifyconf;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Previous";
previousbutton = XtCreateManagedWidget("PreviousButton", commandWidgetClass,
 modifydialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[1].value = (XtArgVal) previousbutton;
diabutton_arglist[2].value = (XtArgVal) "Next";
nextbutton = XtCreateManagedWidget("NextButton", commandWidgetClass,
 modifydialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[1].value = (XtArgVal) nextbutton;
diabutton_arglist[2].value = (XtArgVal) "Set";
setbutton = XtCreateManagedWidget("SetButton", commandWidgetClass,
 modifydialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[1].value = (XtArgVal) setbutton;
diabutton_arglist[2].value = (XtArgVal) "Exit";
exitbutton = XtCreateManagedWidget("ExitButton", commandWidgetClass,
 modifydialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[1].value = (XtArgVal) NULL;
simple_arglist[0].value = (XtArgVal) 20;
simple_arglist[1].value = (XtArgVal) 200;
simple_arglist[2].value = (XtArgVal) previousbutton;
attrarea = XtCreateManagedWidget("AttrArea", simpleWidgetClass,
 modifydialog, simple_arglist, XtNumber(simple_arglist));
simple_arglist[0].value = (XtArgVal) 240;
simple_arglist[2].value = (XtArgVal) attrarea;
imagearea = XtCreateManagedWidget("ImageArea", simpleWidgetClass,
 modifydialog, simple_arglist, XtNumber(simple_arglist));
XtAddCallback(exitbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(modifydialog);
XtRemoveCallback(menu1entry3, XtNcallback, modifyconf, closure);
image_wdw = XtWindow(imagearea);
redraw_image(image_wdw);
ptr = dparms.anlist->first;
for(i = 0; i < act_modify; i++) ptr = ptr->next;
act_icon = ptr->nr;
attr_wdw = XtWindow(attrarea);
redraw_attr(attr_wdw);
XtAddCallback(previousbutton, XtNcallback, previous, (XtPointer) attr_wdw);
XtAddCallback(nextbutton, XtNcallback, next, (XtPointer) attr_wdw);
XtAddCallback(setbutton, XtNcallback, set, (XtPointer) NULL);
XtAddEventHandler(imagearea, VisibilityChangeMask, FALSE, redraw_requ_im,
 (XtPointer) image_wdw);
XtAddEventHandler(attrarea, VisibilityChangeMask, FALSE, redraw_requ_at,
 (XtPointer) attr_wdw);
XtAddEventHandler(imagearea, ButtonPressMask, FALSE, sel,
 (XtPointer) attr_wdw);
checksize(modifydialog, params);
} /* modifyconf */


/* procedure redraw_requ_im			*/
/* called by the X-Windows eventhandler		*/
/* whenever image's window visibility changes.	*/
/* parameters:					*/
/* Widget drawarea	drawarea widget		*/
/* XtPointer closure	image_wdw		*/
/* XEvent* event	not used		*/
/* Boolean* bool	not used		*/

void redraw_requ_im(Widget drawarea, XtPointer image_wdw, XEvent* event,
 Boolean* bool)
{
redraw_image((Window) image_wdw);
} /* redraw_requ_im */


/* procedure redraw_requ_at			*/
/* called by the X-Windows eventhandler		*/
/* whenever attr's window visibility changes.	*/
/* parameters:					*/
/* Widget drawarea	drawarea widget		*/
/* XtPointer closure	attr_wdw		*/
/* XEvent* event	not used		*/
/* Boolean* bool	not used		*/

void redraw_requ_at(Widget drawarea, XtPointer attr_wdw, XEvent* event,
 Boolean* bool)
{
redraw_attr((Window) attr_wdw);
} /* redraw_requ_at */


/* procedure redraw_image			*/
/* redraws images table.			*/
/* parameters:					*/
/* Window image_wdw	window id		*/

void redraw_image(Window image_wdw)
{
int i, j;

for(i = 0; i <= 11; i++) for(j = 0; j<= 9; j++)
 if (i < 11 || j < 2) XPutImage(dparms.display, image_wdw, dparms.gc_red,
 attr_icon[i*10+j], 0, 0, (j*20+2), (i*20+2), IMAGE_WIDTH, IMAGE_HEIGHT);
} /* redraw_image */


/* procedure redraw_attr			*/
/* redraws actual image/attribute.		*/
/* parameters:					*/
/* Window attr_wdw	window id		*/

void redraw_attr(Window attr_wdw)
{
char *str = (char *) malloc(2*L_ATTRIBUT);
int i;
ANLEP ptr;

if (attr_wdw != 0) {		/* avoid errors */
  ptr = dparms.anlist->first;
  for(i = 0; i < act_modify; i++) ptr = ptr->next;
  if (act_icon == -1) XPutImage(dparms.display, attr_wdw, dparms.gc_red, noicon,
   0, 0, 2, 2, IMAGE_WIDTH, IMAGE_HEIGHT);
  else XPutImage(dparms.display, attr_wdw, dparms.gc_red, attr_icon[act_icon],
   0, 0, 2, 2, IMAGE_WIDTH, IMAGE_HEIGHT);
  sprintf(str, "%s", ptr->attr);
  for(i = 1; i <= L_ATTRIBUT; i++) sprintf(str, "%s ", str);
  XDrawImageString(dparms.display, attr_wdw, dparms.gc_black,
   4 + IMAGE_WIDTH, 2 + SM_LETTER_H, str, L_ATTRIBUT);
  } /* if */
free(str);
} /* redraw_attr */


/* procedure previous				*/
/* selects previous attribute.			*/
/* parameters:					*/
/* Widget previousbutton	not used	*/
/* XtPointer closure		window id	*/
/* XtPointer call_data		not used	*/

void previous(Widget previousbutton, XtPointer closure, XtPointer call_data)
{
Window window = (Window) closure;
ANLEP ptr;
int i;

if ((--act_modify) < 0) act_modify = dparms.anlist->anzahl - 1;
ptr = dparms.anlist->first;
for(i = 0; i < act_modify; i++) ptr = ptr->next;
act_icon = ptr->nr;
redraw_attr(window);
} /* previous */


/* procedure next				*/
/* selects next attribute.			*/
/* parameters:					*/
/* Widget nextbutton		not used	*/
/* XtPointer closure		window id	*/
/* XtPointer call_data		not used	*/

void next(Widget nextbutton, XtPointer closure, XtPointer call_data)
{
Window window = (Window) closure;
ANLEP ptr;
int i;

if ((++act_modify) == dparms.anlist->anzahl) act_modify = 0;
ptr = dparms.anlist->first;
for(i = 0; i < act_modify; i++) ptr = ptr->next;
act_icon = ptr->nr;
redraw_attr(window);
} /* next */


/* procedure set						*/
/* changes the actual attribute's image to the selected one.	*/
/* parameters:							*/
/* Widget setbutton		not used			*/
/* XtPointer closure		not used			*/
/* XtPointer call_data		not used			*/

void set(Widget setbutton, XtPointer closure, XtPointer call_data)
{
ANLEP ptr = dparms.anlist->first;
int i;

for(i = 0; i < act_modify; i++) ptr = ptr->next;
ptr->nr = act_icon;
new_area();
} /* set */


/* procedure sel					*/
/* image from image table selected -> actual.		*/
/* parameter:						*/
/* Widget imagearea	imagearea widget		*/
/* XtPointer closure	attr_wdw id			*/
/* XEvent* event	occured event			*/
/* Boolean*		not used			*/

void sel(Widget imagearea, XtPointer closure, XEvent* event,
 Boolean *bool)
{
int yw, xw, nr;

if (event->type == ButtonPress) {		/* avoid errors */
  xw = (event->xbutton.x - 2) / 20;
  yw = (event->xbutton.y - 2) / 20;
  nr = yw * 10 + xw;
  if (nr < 112) {
    act_icon = nr;
    redraw_attr((Window) closure);
    } /* if */
  } /* if */
} /* sel */



/* procedure elementinfo				*/
/* elementinfo is called whenever the user clicks a	*/
/* mouse button in the inside widget's window.		*/
/* it decides if and which element was selected and	*/
/* calls the corresponding ...info procedure.		*/
/* parameters:						*/
/* Widget inside	inside widget			*/
/* XtPointer arrow1	parameters (see call_params) 	*/
/* XEvent* event	occured event			*/
/* Boolean* bool	not used			*/

void elementinfo(Widget inside, XtPointer closure, XEvent* event,
 Boolean* bool)
{
int x, y;
char el_art = 'N';
XLEP ptr = dparms.xlist->first_max;
CPAMP params = (CPAMP) closure;

if (event->type == ButtonPress) {		/* avoid errors */
  x = event->xbutton.x;
  y = event->xbutton.y;
  while((ptr != NULL) && (ptr->x_max < x)) ptr = ptr->next_max;
  while((el_art == 'N') && (ptr != NULL)) {
    if ((x >= ptr->x_min) && (y >= ptr->y_min) && (y <= ptr->y_max))
     el_art = ptr->art;
    else ptr = ptr->next_max;
    } /* while */
  switch(el_art) {
  case 'A': /* clicked on attribute */
    params->pointer = (XtPointer) ptr->info.a_element;
    attrinfo(inside, (XtPointer) params, (XtPointer) NULL);
    break;
  case 'S': /* clicked on semantic action */
    params->pointer = (XtPointer) ptr->info.s_element;
    funcinfo(inside, (XtPointer) params, (XtPointer) NULL);
    break;
  case 'T': /* clicked on node or terminal */
    params->pointer = (XtPointer) ptr->info.t_element;
    nodeinfo(inside, (XtPointer) params, (XtPointer) NULL);
    break;
  case 'N': /* clicked somewhere in the desert => do nothing */
    printf("Message from MUG Browser: no element in cursor's scope, mouseclick ignored.\n");
    break;
    } /* switch */
  } /* if */
} /* elementinfo */


/* procedure nodeinfo					*/
/* opens a dialog window which shows information about	*/
/* the selected node.					*/
/* selection.						*/
/* parameters:						*/
/* Widget inside	inside widget			*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void nodeinfo(Widget inside, XtPointer closure, XtPointer call_data)
{
Widget nodedialog, nbutton;
CPAMP params = (CPAMP) closure;
TEP node = (TEP) params->pointer;
Cursor arrow1 = (Cursor) *(params->arrow);
char* finalline = (char*) malloc((17+L_SYMBOL)*15);
char* nameline = (char*) malloc(L_SYMBOL);
char* typeline = (char*) malloc(4);
char* predecline = (char*) malloc(L_SYMBOL);
char* sucline = (char*) malloc((17+L_SYMBOL)*11);	/* max. 10 sons */
int i = 0;
TEPLEP son;

sprintf(nameline, node->symbol);
if (node->is_terminal) {
  sprintf(typeline, "leaf");
  sprintf(sucline, "none\n");
  } /* if */
else {
  sprintf(typeline, "node");
  son = node->soehne.first;
  sprintf(sucline, "");
  while((son != NULL) && (i < 10)) {
    sprintf(sucline, "%s%s\n                ", sucline, son->symbol->symbol);
    son = son->next;
    i++;
    } /* while */
  if ((i == 10) && (son != NULL)) sprintf(sucline, "%s...\n", sucline);
  } /* else */
if (node->vater == NULL) sprintf(predecline, "none");
else sprintf(predecline, node->vater->symbol);
sprintf(finalline, "Info on node:\n\nname            %s\ntype            %s\npredecessor     %s\nsuccessor(s)    %s", nameline, typeline, predecline, sucline);
dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) finalline;
nodedialog = XtCreateWidget("NodeDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = inside;
params->widget3 = nodedialog;
params->function = NULL;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
nbutton = XtCreateManagedWidget("NButton", commandWidgetClass, nodedialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(nbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(nodedialog);
free(nameline);
free(typeline);
free(predecline);
free(sucline);
free(finalline);
checksize(nodedialog, params);
} /* nodeinfo */


/* procedure attrinfo					*/
/* opens a dialog window which shows information about	*/
/* the selected attribut.				*/
/* selection.						*/
/* parameters:						*/
/* Widget inside	inside widget			*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void attrinfo(Widget inside, XtPointer closure, XtPointer call_data)
{
Widget attrdialog, abutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);
ALEP attr = (ALEP) params->pointer;
char* finalline = (char*) malloc((17+L_ATTRIBUT)*17);
char* nameline = (char*) malloc(L_ATTRIBUT);
char* appline = (char*) malloc(9);
char* typeline = (char*) malloc(L_ATTR_TYP);
char* valueline = (char*) malloc(30);
char* inputline = (char*) malloc(L_ATTRIBUT);
char* outputline = (char*) malloc((17+L_ATTRIBUT)*11);	/* max. 10 outputs */
int i = 0;
ILEP inp;

sprintf(nameline, attr->attr);
switch(attr->art) {
case 'I':
  sprintf(appline, "inherited");
  break;
case 'D':
  sprintf(appline, "derived");
  break;
case 'A':
  sprintf(appline, "auxiliary");
  break;
default:
  sprintf(appline, "unknown");
  break;
  } /* switch */
sprintf(typeline, attr->typ);
switch(attr->wertlen) {
case 1:
  if (isprint(*(attr->wert))) sprintf(valueline, "%c", *(attr->wert));
  else sprintf(valueline, "%d", (int) *(attr->wert));
  break;
case 2:
  sprintf(valueline, "%d", (int) *((short*) (attr->wert)));
  break;
case 4:
  sprintf(valueline, "%d", *((int*) (attr->wert)));
  break;
default:
  sprintf(valueline, "complex");
  break;
} /* switch */
if (attr->copy_of == NULL) sprintf(inputline, attr->result_of->aktion);
else if (attr->copy_of->attr == NULL)
 sprintf(inputline, attr->copy_of->terminal->symbol);
else sprintf(inputline, attr->copy_of->attr->attr);
if (attr->input_to.anzahl == 0) sprintf(outputline, "none\n");
else {
  sprintf(outputline, "");
  inp = attr->input_to.first;
  while ((inp != NULL) && (i < 10)) {
    if (inp->aktion == NULL)
     sprintf(outputline, "%s%s\n                ", outputline, inp->attr->attr);
    else sprintf(outputline, "%s%s\n                ", outputline,
     inp->aktion->aktion);
    inp = inp->next;
    i++;
    } /* while */
  if ((i == 10) && (inp != NULL)) sprintf(outputline, "%s...\n", outputline);
  } /* else */
sprintf(finalline, "Info on attribute:\n\nname            %s\nappearance      %s\ntype            %s\nvalue           %s\ninput           %s\noutput          %s", nameline, appline, typeline, valueline, inputline, outputline);
dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) finalline;
attrdialog = XtCreateWidget("AttrDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = inside;
params->widget3 = attrdialog;
params->function = NULL;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
abutton = XtCreateManagedWidget("AButton", commandWidgetClass, attrdialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(abutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(attrdialog);
free(nameline);
free(appline);
free(typeline);
free(valueline);
free(inputline);
free(outputline);
free(finalline);
checksize(attrdialog, params);
} /* attrinfo */


/* procedure funcinfo					*/
/* opens a dialog window which shows information about	*/
/* the selected function.				*/
/* selection.						*/
/* parameters:						*/
/* Widget inside	inside widget			*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void funcinfo(Widget inside, XtPointer closure, XtPointer call_data)
{
Widget funcdialog, fbutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);
SemLEP func = (SemLEP) params->pointer;
char* finalline = (char*) malloc((17+L_ATTRIBUT)*24);
char* nameline = (char*) malloc(L_SEMACTION);
char* retline = (char*) malloc((17+L_ATTRIBUT)*6); /* max. 5 return types */
char* parline = (char*) malloc((17+L_ATTRIBUT)*16); /* max. 15 parameters */
int i = 0;
ArgLEP arg;

sprintf(nameline, func->aktion);
if (func->results.anzahl == 0) sprintf(retline, "none\n");
else {
  sprintf(retline, "");
  arg = func->results.first;
  while((arg != NULL) && (i < 5)) {
    if (arg->attr == NULL)
     sprintf(retline, "%s%s\n                ", retline, arg->terminal->symbol);
    else
     sprintf(retline, "%s%s\n                ", retline, arg->attr->attr);
    arg = arg->next;
    i++;
    } /* while */
  if ((i == 5) && (arg != NULL)) sprintf(retline, "%s...\n", retline);
  } /* else */
if (func->argumente.anzahl == 0) sprintf(parline, "none\n");
else {
  sprintf(parline, "");
  arg = func->argumente.first;
  i = 0;
  while((arg != NULL) && (i < 15)) {
    if (arg->attr == NULL)
     sprintf(parline, "%s%s\n                ", parline, arg->terminal->symbol);
    else
     sprintf(parline, "%s%s\n                ", parline, arg->attr->attr);
    arg = arg->next;
    i++;
    } /* while */
  if ((i == 15) && (arg != NULL)) sprintf(parline, "%s...\n", parline);
  } /* else */
sprintf(finalline, "Info on function:\n\nname            %s\nreturn type(s)  %s\nparameter(s)    %s", nameline, retline, parline);
dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) finalline;
funcdialog = XtCreateWidget("FuncDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = inside;
params->widget3 = funcdialog;
params->function = NULL;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
fbutton = XtCreateManagedWidget("FButton", commandWidgetClass, funcdialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(fbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(funcdialog);
free(nameline);
free(retline);
free(parline);
free(finalline);
checksize(funcdialog, params);
} /* funcinfo */


/* procedure redraw_config				*/
/* redraws attribute configuration.			*/
/* parameters:						*/
/* Widget cviewport	csimple widget			*/
/* XtPointer closure	not used			*/
/* XEvent* event	event				*/
/* Boolean* bool	not used			*/

void redraw_config(Widget csimple, XtPointer closure, XEvent* event,
 Boolean* bool)
{
int i, j, ymin, ymax;
ANLEP ap = dparms.anlist->first;
Window simple_window;
char *astr = malloc(30 + L_ATTRIBUT);

ymin = event->xgraphicsexpose.y / (IMAGE_HEIGHT + ATTR_SPACE);
if (ymin < 1) ymin = 1;
ymax = ((event->xgraphicsexpose.y + event->xgraphicsexpose.height) /
 (IMAGE_HEIGHT + ATTR_SPACE)) + 1;
if (ymax > dparms.anlist->anzahl) ymax = dparms.anlist->anzahl;

simple_window = XtWindow((Widget) csimple);
if (simple_window != 0) {			/* avoid errors */
  if (ymin > 1) for(i = 1; i < ymin; i++) ap = ap -> next;
  for(i = ymin; i <= ymax; i++) {
    if (ap->nr == -1) {
       XPutImage(dparms.display, simple_window, dparms.gc_red, noicon, 0, 0,
       ATTR_SPACE, (i * (IMAGE_HEIGHT + ATTR_SPACE) - IMAGE_HEIGHT),
       IMAGE_WIDTH, IMAGE_HEIGHT);
      sprintf(astr, "%s[ ", noicon_name);
      } /* if */
    else {
      XPutImage(dparms.display, simple_window, dparms.gc_red,
       attr_icon[ap->nr], 0, 0, ATTR_SPACE, (i * (IMAGE_HEIGHT + ATTR_SPACE) -
       IMAGE_HEIGHT), IMAGE_WIDTH, IMAGE_HEIGHT);
      sprintf(astr, "%s[ ", attr_name[ap->nr]);
      } /* else */
    for(j = 0; j <= 3; j++)
     if (ap->prefix[j] != ' ') sprintf(astr, "%s%c ", astr, ap->prefix[j]); 
    sprintf(astr, "%s] %s", astr, ap->attr);
    XDrawImageString(dparms.display, simple_window, dparms.gc_black,
     (ATTR_SPACE + IMAGE_WIDTH + ATTR_SPACE), (i * (IMAGE_HEIGHT + ATTR_SPACE) -
     IMAGE_HEIGHT + BIG_LETTER_H), astr, strlen(astr));
    ap = ap->next;
    } /* for */
  } /* if */
free(astr);
} /* redraw_config */


/* procedure configureinfo				*/
/* opens a dialog window which shows the actual		*/
/* icon/attribut configuration.				*/
/* parameters:						*/
/* Widget menu1entry6	menu1entry6 widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void configureinfo(Widget menu1entry6, XtPointer closure,
 XtPointer call_data)
{
Widget configuredialog, cbutton, cviewport, csimple;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
if (dparms.anlist->anzahl > 0) dialog_arglist[2].value = (XtArgVal) "Actual Attribute/Image Configuration:";
else dialog_arglist[2].value = (XtArgVal) "WARNING!\nempty configuration.\n";
configuredialog = XtCreateWidget("ConfigureDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu1entry6;
params->widget3 = configuredialog;
params->function = configureinfo;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
diabutton_arglist[3].value = (XtArgVal) XawChainRight;
diabutton_arglist[4].value = (XtArgVal) XawChainRight;
cbutton = XtCreateManagedWidget("CButton", commandWidgetClass,
 configuredialog, diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(cbutton, XtNcallback, quitdialog, (XtPointer) params);
if (dparms.anlist->anzahl > 0) {
  drawarea_arglist[0].value = (XtArgVal) cbutton;
  drawarea_arglist[1].value = (XtArgVal) (dparms.r_ymax - dparms.r_ymin -
   ATTR_YDIAOFF);
  drawarea_arglist[2].value = (XtArgVal) (ATTR_NAME + ATTR_VP_W + SCROLL_SIZE);
  drawarea_arglist[3].value = (XtArgVal) False;
  drawarea_arglist[4].value = (XtArgVal) True;
  drawarea_arglist[5].value = (XtArgVal) True;
  cviewport = XtCreateWidget("CViewport", viewportWidgetClass,
   configuredialog, drawarea_arglist, XtNumber(drawarea_arglist));
  inside_arglist[0].value = (XtArgVal) None;
  inside_arglist[1].value = (XtArgVal) (dparms.anlist->anzahl *
   (ATTR_SPACE + IMAGE_HEIGHT));
  inside_arglist[2].value = (XtArgVal) (ATTR_NAME + ATTR_VP_W);
  csimple = XtCreateManagedWidget("CSimple", simpleWidgetClass,
   cviewport, inside_arglist, XtNumber(inside_arglist));
  XtManageChild(cviewport);
  XtAddEventHandler(csimple, ExposureMask, FALSE, redraw_config,
   (XtPointer) NULL);
  } /* if */
XtManageChild(configuredialog);
XtRemoveCallback(menu1entry6, XtNcallback, configureinfo, closure);
checksize(configuredialog, params);
} /* configureinfo */


/* procedure findnode						*/
/* opens window to enter node to search for.			*/
/* parameters:							*/
/* Widget menu2entry1	menu2entry1 widget			*/
/* XtPointer closure	parameters (see call_params)		*/
/* XtPointer call_data	not used				*/

void findnode(Widget menu2entry1, XtPointer closure,
 XtPointer call_data)
{
Widget findndialog, nappbutton, nexbutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Find Node:";
if (last_node != NULL)
 dialog_arglist[5].value = (XtArgVal) last_node->info.t_element->symbol;
else dialog_arglist[5].value = (XtArgVal) "";
findndialog = XtCreateWidget("FindNodeDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
dialog_arglist[5].value = (XtArgVal) NULL;
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu2entry1;
params->widget3 = findndialog;
params->function = findnode;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Next Appearance";
nappbutton = XtCreateManagedWidget("NodeAppButton", commandWidgetClass,
 findndialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Exit";
nexbutton = XtCreateManagedWidget("NodeExitButton", commandWidgetClass,
 findndialog, diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(nappbutton, XtNcallback, findit_node, (XtPointer) params);
XtAddCallback(nexbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(findndialog);
XtRemoveCallback(menu2entry1, XtNcallback, findnode, closure);
checksize(findndialog, params);
} /* findnode */


/* procedure findit_node				*/
/* finds next appearance of given node.			*/
/* parameters:						*/
/* Widget nappbutton	nappbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void findit_node(Widget nappbutton, XtPointer closure,
 XtPointer call_data)
{
CPAMP params = (CPAMP) closure;
String lookfor = XawDialogGetValueString(params->widget3);
XLEP ptr;
int width = (dparms.r_xmax - dparms.r_xmin);
int height = (dparms.r_ymax - dparms.r_ymin);
int widthhalf = width / 2, heighthalf = height / 2, diffx = 0, diffy = 0;

if (last_node == NULL) ptr = dparms.xlist->first_min; /* default node if */
else ptr = last_node->next_min;		    /* none was previously found */
while((ptr != NULL) &&
 !((ptr->art == 'T') && (strcmp(lookfor, ptr->info.t_element->symbol) == 0)))
 ptr = ptr->next_min; /* skip all not matching nodes */
if (ptr == NULL && last_node != NULL) { /* switch over to first node if */
  ptr = dparms.xlist->first_min;	/* search did not start there */
  while((ptr != last_node) &&
   !((ptr->art == 'T') && (strcmp(lookfor, ptr->info.t_element->symbol) == 0)))
   ptr = ptr->next_min; /* skip all not matching nodes */
  } /* if */
if ((ptr == NULL) || (strcmp(lookfor, ptr->info.t_element->symbol) != 0))
 printf("Message from MUG Browser: node %s could not be found.\n", lookfor);
else { /* node found => justify viewport */
  dparms.r_xmin = ptr->x_min - widthhalf;
  dparms.r_ymin = ptr->y_min - heighthalf;
  dparms.r_xmax = dparms.r_xmin + width;
  dparms.r_ymax = dparms.r_ymin + height;
  if (dparms.r_xmin < X_START) diffx = X_START - dparms.r_xmin;
  if (dparms.r_xmax > (X_START + dparms.width))
   diffx = X_START + dparms.width - dparms.r_xmax;
  if (dparms.r_ymin < Y_START) diffy = Y_START - dparms.r_ymin;
  if (dparms.r_ymax > (Y_START + dparms.height))
   diffy = Y_START + dparms.height - dparms.r_ymax;
  if (diffx != 0) {
    dparms.r_xmin += diffx;
    dparms.r_xmax += diffx;
    } /* if */
  if (diffy != 0) {
    dparms.r_ymin += diffy;
    dparms.r_ymax += diffy;
    } /* if */
  XawViewportSetCoordinates(drawarea, dparms.r_xmin, dparms.r_ymin);
  new_area();
  last_node = ptr;
  } /* else */
} /* findit_node */


/* procedure findattr						*/
/* opens window to enter node to search for.			*/
/* parameters:							*/
/* Widget menu2entry2	menu2entry2 widget			*/
/* XtPointer closure	parameters (see call_params)		*/
/* XtPointer call_data	not used				*/

void findattr(Widget menu2entry2, XtPointer closure,
 XtPointer call_data)
{
Widget findadialog, aappbutton, aexbutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Find Attribute:";
if (last_node != NULL)
 dialog_arglist[5].value = (XtArgVal) last_node->info.a_element->attr;
else dialog_arglist[5].value = (XtArgVal) "";
findadialog = XtCreateWidget("FindAttrDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
dialog_arglist[5].value = (XtArgVal) NULL;
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu2entry2;
params->widget3 = findadialog;
params->function = findattr;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Next Appearance";
aappbutton = XtCreateManagedWidget("AttrAppButton", commandWidgetClass,
 findadialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Exit";
aexbutton = XtCreateManagedWidget("AttrExitButton", commandWidgetClass,
 findadialog, diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(aappbutton, XtNcallback, findit_attr, (XtPointer) params);
XtAddCallback(aexbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(findadialog);
XtRemoveCallback(menu2entry2, XtNcallback, findattr, closure);
checksize(findadialog, params);
} /* findattr */


/* procedure findit_attr				*/
/* finds next appearance of given attribute.		*/
/* parameters:						*/
/* Widget aappbutton	aappbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void findit_attr(Widget aappbutton, XtPointer closure,
 XtPointer call_data)
{
CPAMP params = (CPAMP) closure;
String lookfor = XawDialogGetValueString(params->widget3);
XLEP ptr;
int width = (dparms.r_xmax - dparms.r_xmin);
int height = (dparms.r_ymax - dparms.r_ymin);
int widthhalf = width / 2, heighthalf = height / 2, diffx = 0, diffy = 0;

if (last_attr == NULL) ptr = dparms.xlist->first_min; /* default attribute */
else ptr = last_attr->next_min;		   /* if none was previously found */
while((ptr != NULL) &&
 !((ptr->art == 'A') && (strcmp(lookfor, ptr->info.a_element->attr) == 0)))
 ptr = ptr->next_min; /* skip all not mathcing attributes */
if (ptr == NULL && last_attr != NULL) { /* switch over to first attribute */
  ptr = dparms.xlist->first_min;	/* if search did not start there */
  while((ptr != last_attr) &&
   !((ptr->art == 'A') && (strcmp(lookfor, ptr->info.a_element->attr) == 0)))
   ptr = ptr->next_min; /* skip all not matching attributes */
  } /* if */
if ((ptr == NULL) || (strcmp(lookfor, ptr->info.a_element->attr) != 0))
 printf("Message from MUG Browser: attribute %s could not be found.\n", lookfor);
else { /* attribute found => justify viewport */
  dparms.r_xmin = ptr->x_min - widthhalf;
  dparms.r_ymin = ptr->y_min - heighthalf;
  dparms.r_xmax = dparms.r_xmin + width;
  dparms.r_ymax = dparms.r_ymin + height;
  if (dparms.r_xmin < X_START) diffx = X_START - dparms.r_xmin;
  if (dparms.r_xmax > (X_START + dparms.width))
   diffx = X_START + dparms.width - dparms.r_xmax;
  if (dparms.r_ymin < Y_START) diffy = Y_START - dparms.r_ymin;
  if (dparms.r_ymax > (Y_START + dparms.height))
   diffy = Y_START + dparms.height - dparms.r_ymax;
  if (diffx != 0) {
    dparms.r_xmin += diffx;
    dparms.r_xmax += diffx;
    } /* if */
  if (diffy != 0) {
    dparms.r_ymin += diffy;
    dparms.r_ymax += diffy;
    } /* if */
  XawViewportSetCoordinates(drawarea, dparms.r_xmin, dparms.r_ymin);
  new_area();
  last_attr = ptr;
  } /* else */
} /* findit_attr */


/* procedure findfunc						*/
/* opens window to enter function to search for.		*/
/* parameters:							*/
/* Widget menu2entry3	menu2entry3 widget			*/
/* XtPointer closure	parameters (see call_params)		*/
/* XtPointer call_data	not used				*/

void findfunc(Widget menu2entry3, XtPointer closure,
 XtPointer call_data)
{
Widget findfdialog, fappbutton, fexbutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Find Function:";
if (last_func != NULL)
 dialog_arglist[5].value = (XtArgVal) last_func->info.s_element->aktion;
else dialog_arglist[5].value = (XtArgVal) "";
findfdialog = XtCreateWidget("FindFuncDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
dialog_arglist[5].value = (XtArgVal) NULL;
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu2entry3;
params->widget3 = findfdialog;
params->function = findfunc;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Next Appearance";
fappbutton = XtCreateManagedWidget("FuncAppButton", commandWidgetClass,
 findfdialog, diabutton_arglist, XtNumber(diabutton_arglist));
diabutton_arglist[2].value = (XtArgVal) "Exit";
fexbutton = XtCreateManagedWidget("FuncExitButton", commandWidgetClass,
 findfdialog, diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(fappbutton, XtNcallback, findit_func, (XtPointer) params);
XtAddCallback(fexbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(findfdialog);
XtRemoveCallback(menu2entry3, XtNcallback, findfunc, closure);
checksize(findfdialog, params);
} /* findfunc */


/* procedure findit_func				*/
/* finds next appearance of given function.		*/
/* parameters:						*/
/* Widget fappbutton	fappbutton widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void findit_func(Widget fappbutton, XtPointer closure,
 XtPointer call_data)
{
CPAMP params = (CPAMP) closure;
String lookfor = XawDialogGetValueString(params->widget3);
XLEP ptr;
int width = (dparms.r_xmax - dparms.r_xmin);
int height = (dparms.r_ymax - dparms.r_ymin);
int widthhalf = width / 2, heighthalf = height / 2, diffx = 0, diffy = 0;

if (last_func == NULL) ptr = dparms.xlist->first_min; /* default function */
else ptr = last_func->next_min;		  /* if none was previously found */
while((ptr != NULL) &&
 !((ptr->art == 'S') && (strcmp(lookfor, ptr->info.s_element->aktion) == 0)))
 ptr = ptr->next_min; /* skip all not matching functions */
if (ptr == NULL && last_func != NULL) { /* switch over to first function */
  ptr = dparms.xlist->first_min;	/* if search didi not start there */
  while((ptr != last_func) &&
   !((ptr->art == 'S') && (strcmp(lookfor, ptr->info.s_element->aktion) == 0)))
   ptr = ptr->next_min; /* skip alll not matching functions */
  } /* if */
if ((ptr == NULL) || (strcmp(lookfor, ptr->info.s_element->aktion) != 0))
 printf("Message from MUG Browser: function %s could not be found.\n", lookfor);
else { /* function found => justify viewport */
  dparms.r_xmin = ptr->x_min - widthhalf;
  dparms.r_ymin = ptr->y_min - heighthalf;
  dparms.r_xmax = dparms.r_xmin + width;
  dparms.r_ymax = dparms.r_ymin + height;
  if (dparms.r_xmin < X_START) diffx = X_START - dparms.r_xmin;
  if (dparms.r_xmax > (X_START + dparms.width))
   diffx = X_START + dparms.width - dparms.r_xmax;
  if (dparms.r_ymin < Y_START) diffy = Y_START - dparms.r_ymin;
  if (dparms.r_ymax > (Y_START + dparms.height))
   diffy = Y_START + dparms.height - dparms.r_ymax;
  if (diffx != 0) {
    dparms.r_xmin += diffx;
    dparms.r_xmax += diffx;
    } /* if */
  if (diffy != 0) {
    dparms.r_ymin += diffy;
    dparms.r_ymax += diffy;
    } /* if */
  XawViewportSetCoordinates(drawarea, dparms.r_xmin, dparms.r_ymin);
  new_area();
  last_func = ptr;
  } /* else */
} /* findit_func */


/* procedure globalview					*/
/* opens a dialog window which shows the tree's global	*/
/* view.						*/
/* parameters:						*/
/* Widget menu2entry5	menu2entry5 widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void globalview(Widget menu2entry5, XtPointer closure,
 XtPointer call_data)
{
Widget gvdialog, gbutton, gviewport, gsimple;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "Global View:";
gvdialog = XtCreateWidget("GVDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu2entry5;
params->widget3 = gvdialog;
params->function = globalview;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
diabutton_arglist[3].value = (XtArgVal) XawChainRight;
diabutton_arglist[4].value = (XtArgVal) XawChainRight;
gbutton = XtCreateManagedWidget("GButton", commandWidgetClass,
 gvdialog, diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(gbutton, XtNcallback, quitdialog, (XtPointer) params);
drawarea_arglist[0].value = (XtArgVal) gbutton;
if ((dparms.height / GV_FAKTOR) > (dparms.r_ymax - dparms.r_ymin -
 ATTR_YDIAOFF)) drawarea_arglist[1].value = (XtArgVal)
 (dparms.r_ymax - dparms.r_ymin - ATTR_YDIAOFF);
else drawarea_arglist[1].value = (XtArgVal) (dparms.height / GV_FAKTOR);
if ((dparms.width / GV_FAKTOR) > (dparms.r_xmax - dparms.r_xmin -
 menu2button_arglist[2].value)) drawarea_arglist[2].value = (XtArgVal)
 (dparms.r_xmax - dparms.r_xmin - menu2button_arglist[2].value);
else drawarea_arglist[2].value = (XtArgVal) (dparms.width / GV_FAKTOR);
drawarea_arglist[3].value = (XtArgVal) False;
drawarea_arglist[4].value = (XtArgVal) True;
drawarea_arglist[5].value = (XtArgVal) True;
gviewport = XtCreateWidget("GViewport", viewportWidgetClass,
 gvdialog, drawarea_arglist, XtNumber(drawarea_arglist));
inside_arglist[0].value = (XtArgVal) None;
inside_arglist[1].value = (XtArgVal) (dparms.height / GV_FAKTOR);
inside_arglist[2].value = (XtArgVal) (dparms.width / GV_FAKTOR);
gsimple = XtCreateManagedWidget("GSimple", simpleWidgetClass,
 gviewport, inside_arglist, XtNumber(inside_arglist));
XtManageChild(gviewport);
XtAddEventHandler(gsimple, ExposureMask, FALSE, redraw_globalview,
 (XtPointer) NULL);
XtManageChild(gvdialog);
XtRemoveCallback(menu2entry5, XtNcallback, globalview, closure);
checksize(gvdialog, params);
} /* globalview */


/* procedure redraw_globalview			*/
/* redraws the tree's global view.		*/
/* parameters:					*/
/* Widget gsimple	gsimple widget		*/
/* XtPointer closure	notused			*/
/* XEvent* event	not used		*/
/* Boolean* bool	not used		*/

void redraw_globalview(Widget gsimple, XtPointer closure, XEvent* event,
 Boolean* bool)
{
int i, j, anz;
TEPLEP son;
XLEP element;
Window simple_window;

if (simple_window = XtWindow((Widget) gsimple)) { /* avoid errors */
  if (opts.monitortype == 0) { /* square, if b/w graph */
    XDrawRectangle(dparms.display, simple_window, dparms.gc_black,
     (dparms.r_xmin / GV_FAKTOR), (dparms.r_ymin / GV_FAKTOR),
     ((dparms.r_xmax - dparms.r_xmin)/ GV_FAKTOR),
     ((dparms.r_ymax - dparms.r_ymin)/ GV_FAKTOR));
    } /* if */
  else { /* block if color or greyscale graph */
    XFillRectangle(dparms.display, simple_window, dparms.gc_red,
     (dparms.r_xmin / GV_FAKTOR), (dparms.r_ymin / GV_FAKTOR),
     ((dparms.r_xmax - dparms.r_xmin)/ GV_FAKTOR),
     ((dparms.r_ymax - dparms.r_ymin)/ GV_FAKTOR));
    } /* else */
  element = dparms.xlist->first_min;
  for(i = 1; i <= dparms.xlist->anzahl; i++) { /* go through all elements */
    if (element->art == 'T') { /* test for node */
      if (element->info.t_element->vater != NULL) /* edge to father */
       XDrawLine(dparms.display, simple_window, dparms.gc_black,
       (element->info.t_element->vater->x / GV_FAKTOR),
       (element->info.t_element->vater->y / GV_FAKTOR),
       (element->info.t_element->x / GV_FAKTOR),
       (element->info.t_element->y / GV_FAKTOR));
      anz = element->info.t_element->soehne.anzahl;
      son = element->info.t_element->soehne.first;
      for (j = 1; j <= anz; j++) { /* edges to sons */
        XDrawLine(dparms.display, simple_window, dparms.gc_black,
         (element->info.t_element->x / GV_FAKTOR),
         (element->info.t_element->y / GV_FAKTOR),
         (son->symbol->x / GV_FAKTOR), (son->symbol->y / GV_FAKTOR));
        son = son->next;
        } /* for */
      } /* if */
    element = element->next_min;
    } /* for */
  } /* if */
} /* redraw_globalview */


/* procedure information						*/
/* opens a dialog window with information about the MUG Browser.	*/
/* parameters:								*/
/* Widget infobutton	infobutton widget				*/
/* XtPointer closure	parameters (see call_params)			*/
/* XtPointer call_data	not used					*/

void information(Widget infobutton, XtPointer closure, XtPointer call_data)
{
Widget infodialog, ibutton;
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) "MUG Browser V 1.0\n\nCoding:\nFrontend - Peter Mueller\nBackend - Michael Guntersdorfer\n\nJul 94 - May 95\n";
infodialog = XtCreateWidget("InfoDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = infobutton;
params->widget3 = infodialog;
params->function = information;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
ibutton = XtCreateManagedWidget("IButton", commandWidgetClass, infodialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(ibutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(infodialog);
XtRemoveCallback(infobutton, XtNcallback, information, closure);
checksize(infodialog, params);
} /* information */


/* procedure shownodes					*/
/* switches show/don't show nodes.			*/
/* parameters:						*/
/* Widget menu3entry1	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void shownodes(Widget menu3entry1, XtPointer closure, XtPointer call_data)
{
if (opts.nodes == 0) opts.nodes = 1;
else opts.nodes = 0;
new_area();
} /* shownodes */


/* procedure showedges					*/
/* switches show/don't show edges.			*/
/* parameters:						*/
/* Widget menu3entry2	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void showedges(Widget menu3entry2, XtPointer closure, XtPointer call_data)
{
if (opts.edges == 0) opts.edges = 1;
else opts.edges = 0;
new_area();
} /* showedges */


/* procedure showattributs				*/
/* switches show/don't show attributs.			*/
/* parameters:						*/
/* Widget menu3entry3	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void showattributs(Widget menu3entry3, XtPointer closure,
 XtPointer call_data)
{
if (opts.attributs == 0) opts.attributs = 1;
else opts.attributs = 0;
new_area();
} /* showattributs */


/* procedure showfunctions				*/
/* switches show/don't show functions.			*/
/* parameters:						*/
/* Widget menu3entry4	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void showfunctions(Widget menu3entry4, XtPointer closure,
 XtPointer call_data)
{
if (opts.sem_actions == 0) opts.sem_actions = 1;
else opts.sem_actions = 0;
new_area();
} /* showfunctions */


/* procedure showdependencies				*/
/* switches show/don't show dependencies.		*/
/* parameters:						*/
/* Widget menu3entry5	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void showdependencies(Widget menu3entry5, XtPointer closure,
 XtPointer call_data)
{
if (opts.dependencies == 0) opts.dependencies = 1;
else opts.dependencies = 0;
new_area();
} /* showdependencies */


/* procedure showcopies					*/
/* switches show/don't show copies.			*/
/* parameters:						*/
/* Widget menu3entry5b	not used			*/
/* XtPointer closure	not used			*/
/* XtPointer call_data	not used			*/

void showcopies(Widget menu3entry5b, XtPointer closure,
 XtPointer call_data)
{
if (opts.copies == 0) opts.copies = 1;
else opts.copies = 0;
new_area();
} /* showcopies */


/* procedure showinfo					*/
/* opens a dialog window which shows the actual		*/
/* visuality of the several graph elements.		*/
/* parameters:						*/
/* Widget menu3entry7	menu3entry7 widget		*/
/* XtPointer closure	parameters (see call_params)	*/
/* XtPointer call_data	not used			*/

void showinfo(Widget menu3entry7, XtPointer closure, XtPointer call_data)
{
Widget showdialog, sbutton;
char* nodesline = (char*) malloc(4);
char* edgesline = (char*) malloc(4);
char* attributsline = (char*) malloc(4);
char* functionsline = (char*) malloc(4);
char* dependenciesline = (char*) malloc(4);
char* copiesline = (char*) malloc(4);
char* finalline = (char*) malloc(180);
CPAMP params = (CPAMP) closure;
Cursor arrow1 = (Cursor) *(params->arrow);

if (opts.nodes == 1) sprintf(nodesline, "yes");
else sprintf(nodesline, "no");
if (opts.edges == 1) sprintf(edgesline, "yes");
else sprintf(edgesline, "no");
if (opts.attributs == 1) sprintf(attributsline, "yes");
else sprintf(attributsline, "no");
if (opts.sem_actions == 1) sprintf(functionsline, "yes");
else sprintf(functionsline, "no");
if (opts.dependencies == 1) sprintf(dependenciesline, "yes");
else sprintf(dependenciesline, "no");
if (opts.copies == 1) sprintf(copiesline, "yes");
else sprintf(copiesline, "no");
sprintf(finalline, "Actual Mask:\n\nelement        show\n-------------------\nnode           %s\nedge           %s\nattribute      %s\nfunction       %s\ndependency     %s\ncopy           %s\n\n", nodesline, edgesline, attributsline, functionsline, dependenciesline, copiesline);
dialog_arglist[0].value = (XtArgVal) params->widget2;
dialog_arglist[1].value = (XtArgVal) params->widget3;
dialog_arglist[2].value = (XtArgVal) finalline;
showdialog = XtCreateWidget("ShowDialog", dialogWidgetClass,
 params->widget1, dialog_arglist, XtNumber(dialog_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget2 = menu3entry7;
params->widget3 = showdialog;
params->function = showinfo;
params->params = (CPAMP) closure;
diabutton_arglist[0].value = (XtArgVal) arrow1;
diabutton_arglist[2].value = (XtArgVal) "Noticed";
sbutton = XtCreateManagedWidget("SButton", commandWidgetClass, showdialog,
 diabutton_arglist, XtNumber(diabutton_arglist));
XtAddCallback(sbutton, XtNcallback, quitdialog, (XtPointer) params);
XtManageChild(showdialog);
XtRemoveCallback(menu3entry7, XtNcallback, showinfo, closure);
free(nodesline);
free(edgesline);
free(attributsline);
free(functionsline);
free(dependenciesline);
free(finalline);
checksize(showdialog, params);
} /* showinfo */


/* procedure draw_attribut				*/
/* draw_attribut draws an attribut.			*/
/* parameters:						*/
/* ALEP attr			attribut		*/

void draw_attribut(ALEP attr)
{
int image_nr;

if (opts.attributs == 1 && !((opts.sem_actions == 0) && (attr->art == 'A'))) {
  image_nr = get_image(attr, dparms.anlist);
  if (image_nr != -1) XPutImage(dparms.display, redraw_window, dparms.gc_red,
   attr_icon[image_nr], 0, 0, attr->x, attr->y, IMAGE_WIDTH, IMAGE_HEIGHT);
  else 
	{
	XPutImage(dparms.display, redraw_window, dparms.gc_red, noicon,
   	0, 0, attr->x, attr->y, IMAGE_WIDTH, IMAGE_HEIGHT);
	}
  } /* if */
} /* draw_attribut */


/* procedure draw_semaction				*/
/* draw_semaction draws a semantic action.		*/
/* parameters:						*/
/* SemLEP semaction		semantic action		*/

void draw_semaction(SemLEP semaction)
{
int len = strlen(semaction->aktion);

if (opts.sem_actions) {
  XDrawRectangle(dparms.display, redraw_window, dparms.gc_green,
   semaction->x_min, semaction->y, (semaction->x_max - semaction->x_min),
   SEM_HEIGHT);
  XDrawImageString(dparms.display, redraw_window, dparms.gc_green,
   (semaction->x - SM_HW_LETTER(len)), (semaction->y + SM_LETTER_H),
   semaction->aktion, len);
  } /* if */
} /* draw_semaction */


/* procedure draw_node					*/
/* draw_node draws a node.				*/
/* parameters:						*/
/* TEP node			Node			*/

void draw_node(TEP node)
{
int len = strlen(node->symbol);

if (opts.nodes) {
  XDrawRectangle(dparms.display, redraw_window, dparms.gc_black,
   (node->x - HALFW_RECT(len)), node->y, RECT_WIDTH(len),
   KNOTEN_HEIGHT);
  XDrawImageString(dparms.display, redraw_window, dparms.gc_black,
   (node->x - BIG_HW_LET(len)), (node->y + BIG_LETTER_H),
   node->symbol, len);
  } /* if */
} /* draw_node */


/* procedure draw_edge					*/
/* draw_edge draws an edge from one node to another.	*/
/* parameters:						*/
/* TEP node1			father node		*/
/* TEP node2			son node		*/

void draw_edge(TEP node1, TEP node2)
{
if (opts.nodes && opts.edges) {
  if (opts.sem_actions) draw_line(&node1->aktionen, BLACK, node1->x,
   node1->y + KNOTEN_HEIGHT, node2->x, node2->y);
  else XDrawLine(dparms.display, redraw_window, dparms.gc_black, node1->x,
   node1->y + KNOTEN_HEIGHT, node2->x, node2->y);
  } /* if */
} /* draw_edge */


/* procedure draw_dep_aa					*/
/* draw_dep_aa draws a dependency arrow from one attribut to	*/
/* another.							*/
/* parameters:							*/
/* ALEP attr1			sending attribut		*/
/* ALEP attr2			receiving attribut		*/

void draw_dep_aa(ALEP attr1, ALEP attr2)
{
int x1, x2, y1, y2, xm, ym, y_move;
SemList *list;

if (opts.dependencies && opts.attributs && opts.copies &&
 !((opts.sem_actions == 0) && (attr1->art == 'A' || attr2->art == 'A'))) {
  x1 = attr1->x;
  x2 = attr2->x;
  y1 = attr1->y;
  y2 = attr2->y;
  if (y2 > (y1 + IMAGE_HEIGHT)) { /* draw from attr1's bottom to attr2's */
    x1 += IMAGE_HWIDTH;		  /* top */
    x2 += IMAGE_HWIDTH;
    y1 += IMAGE_HEIGHT;
    list = &attr1->node->aktionen;
    goto aa_done;
    } /* if */
  if ((y2 + IMAGE_HEIGHT) < y1) { /* draw from attr1's top to attr2's */
    x1 += IMAGE_HWIDTH;		  /* bottom */
    x2 += IMAGE_HWIDTH;
    y2 += IMAGE_HEIGHT;
    list = &attr2->node->aktionen;
    goto aa_done;
    } /* if */
  x1 += IMAGE_HWIDTH;	/* attributes at an even y level */
  x2 += IMAGE_HWIDTH;	/* => avoid kollision with node */
  y_move = ((absolute(x2 - x1) / (IMAGE_WIDTH + IMAGE_SPACE)) % COPY_LOOP)
   * DEP_Y_SPACE; /* calculate y-distance used to draw around node */
		  /* a little trick is used here: the bigger the distance */
		  /* between the two attributes, the bigger the y-distance */
		  /* to the node. To avoid too big y-distances % COPY_LOOP */
		  /* was added. The whole thing usually avoids from going */
		  /* around the node at the same y-level, if several */
		  /* dependencies exist from left to right. */
  if (y1 >= y_move) { /* must be the root node, draw around it's bottom */
    list = &attr1->node->vater->aktionen;
    ym = y1 - y_move;
    } /* if */
  else { /* oridinairy node, draw around it's top */
    list = &attr1->node->aktionen;
    ym = y1 + y_move;
    y1 += IMAGE_HEIGHT;
    y2 += IMAGE_HEIGHT;
    } /* else */
  if (x2 > x1) { /* draw from attr1's right to attr2's left */
    xm = x2 - IMAGE_HWIDTH;
    if (opts.sem_actions) { /* use draw_line if semantic actions may be in */
      draw_line(list, RED, x1, y1, x1 + IMAGE_HWIDTH, ym);	/* the way */
      draw_line(list, RED, x1 + IMAGE_HWIDTH, ym, xm, ym);
      } /* if */
    else { /* no obstacles expected */
      XDrawLine(dparms.display, redraw_window, dparms.gc_red, x1, y1,
       x1 + IMAGE_HWIDTH, ym);
      XDrawLine(dparms.display, redraw_window, dparms.gc_red, x1 + IMAGE_HWIDTH,
       ym, xm, ym);
      } /* else */
    } /* if */
  else { /* draw from attr1's left to attr2's right */
    xm = x2 + IMAGE_HWIDTH;
    if (opts.sem_actions) { /* use draw_line if semantic actions may be in */
      draw_line(list, RED, x1, y1, x1 - IMAGE_HWIDTH, ym);	/* the way */
      draw_line(list, RED, x1 - IMAGE_HWIDTH, ym, xm, ym);
      } /* if */
    else { /* no obstacles expected */
      XDrawLine(dparms.display, redraw_window, dparms.gc_red, x1, y1,
       x1 - IMAGE_HWIDTH, ym);
      XDrawLine(dparms.display, redraw_window, dparms.gc_red, x1 - IMAGE_HWIDTH,
       ym, xm, ym);
      } /* else */
    } /* else */
  x1 = xm; /* reset coordinates for draw_dep_arrow call, as a big part */
  y1 = ym; /* of the dependency is already drawn. */
aa_done: ;/* done */
  draw_dep_arrow(list, x1, y1, x2, y2);
  } /* if */
} /* draw_dep_aa */


/* procedure draw_dep_sa					*/
/* draw_dep_sa draws a dependency arrow from a semantic action	*/
/* to an attribut.						*/
/* parameters:							*/
/* SemLEP semaction		semantic action			*/
/* ALEP attr			attribut			*/

void draw_dep_sa(SemLEP semaction, ALEP attr)
{
int x1, x2, y1, y2;
SemList *list;

if (opts.dependencies && opts.attributs && opts.sem_actions) {
  x1 = semaction->x_min;
  x2 = attr->x;
  y1 = semaction->y;
  y2 = attr->y;
  if (y2 > (y1 + SEM_HHEIGHT)) { /* draw from semaction's bottom to attr's */
    x2 += IMAGE_HWIDTH;		 /* top */
    if (x2 > semaction->x_max) x1 = semaction->x_max;
    else if (x2 < semaction->x_min) x1 = semaction->x_min;
    else x1 = x2;
    y1 += SEM_HEIGHT;
    list = &attr->node->vater->aktionen;
    goto sa_done;
    } /* if */
  if ((y2 + IMAGE_HEIGHT) < y1) { /* draw from semaction's top to attr's */
    x1 = semaction->x;		  /* bottom */
    x2 += IMAGE_HWIDTH;
    if (x2 > semaction->x_max) x1 = semaction->x_max;
    else if (x2 < semaction->x_min) x1 = semaction->x_min;
    else x1 = x2;
    y2 += IMAGE_HEIGHT;
    list = &attr->node->aktionen;
    goto sa_done;
    } /* if */
  list = &attr->node->aktionen;
  if ((x2 + IMAGE_WIDTH) < x1) { /* draw from semaction's left to attr's */
    y1 += SEM_HHEIGHT;		 /* right */
    y2 += IMAGE_HHEIGHT;
    x2 += IMAGE_WIDTH;
    } /* if */
  else { /* draw from semaction's right to attr's left */
    y1 += SEM_HHEIGHT;
    y2 += IMAGE_HHEIGHT;
    x1 = semaction->x_max;
    } /* else */
sa_done: ; /*done */
  draw_dep_arrow(list, x1, y1, x2, y2);
  } /* if */
} /* draw_dep_sa */


/* procedure draw_dep_as					*/
/* draw_dep_as draws a dependency arrow from an attribut to a	*/
/* semantic action.						*/
/* parameters:							*/
/* ALEP attr			attribut			*/
/* SemLEP semaction		semantic action			*/

void draw_dep_as(ALEP attr, SemLEP semaction)
{
int x1, x2, y1, y2;
SemList *list;

if (opts.dependencies && opts.attributs && opts.sem_actions) {
  x1 = attr->x;
  x2 = semaction->x_min;
  y1 = attr->y;
  y2 = semaction->y;
  list = &attr->node->aktionen;
  if (y2 > (y1 + IMAGE_HEIGHT)) { /* draw from attr's bottom to */
    x1 += IMAGE_HWIDTH;		  /* semaction's top */
    if (x1 > semaction->x_max) x2 = semaction->x_max;
    else if (x1 < semaction->x_min) x2 = semaction->x_min;
    else x2 = x1;
    y1 += IMAGE_HEIGHT;
    list = &attr->node->aktionen;
    goto as_done;
    } /* if */
  if ((y2 + SEM_HEIGHT) < y1) { /* draw from attr's top to semaction's */
    x1 += IMAGE_HWIDTH;		/* bottom */
    if (x1 > semaction->x_max) x2 = semaction->x_max;
    else if (x1 < semaction->x_min) x2 = semaction->x_min;
    else x2 = x1;
    y2 += SEM_HEIGHT;
    list = (attr->art == 'A') ? &attr->node->aktionen :
     &attr->node->vater->aktionen;
    goto as_done;
    } /* if */
  list = &attr->node->aktionen;
  if (x2 > (x1 + IMAGE_WIDTH)) { /* draw from attr's left to semaction's */
      y1 += IMAGE_HHEIGHT;	 /* right */
      y2 += SEM_HHEIGHT;
      x1 += IMAGE_WIDTH;
    } /* if */
  else { /* draw from attr's right to semaction's left */
      y1 += IMAGE_HHEIGHT;
      y2 += SEM_HHEIGHT;
      x2 = semaction->x_max;
    } /* else */
as_done: ; /* done */
  draw_dep_arrow(list, x1, y1, x2, y2);
  } /* if */
} /* draw_dep_as */


/* procedure draw_dep_ts					*/
/* draw_dep_as draws a dependency arrow from a terminal to a	*/
/* semantic action.						*/
/* parameters:							*/
/* TEP terminal			terminal			*/
/* SemLEP semaction		semantic action			*/

void draw_dep_ts(TEP terminal, SemLEP semaction)
{
int x1, x2, y1, y2, khw;
SemList *list;

if (opts.dependencies && opts.nodes && opts.sem_actions) {
  x1 = terminal->x;
  x2 = semaction->x_min;
  y1 = terminal->y;
  y2 = semaction->y;
  list = &terminal->vater->aktionen;
  khw = HALFW_RECT(strlen(terminal->symbol));
  if (y2 > (y1 + KNOTEN_HEIGHT)) { /* draw from terminal's bottom to	  */
	/* semaction's top. This is not possible in a regular syntax-	  */
	/* tree, as semantic action's can only get input from terminals   */
	/* which can never be father of a production and for that reason  */
	/* not be positioned above semantic actions. But as this backend  */
	/* should operate as general as possible it accepts this case.	  */
    if ((terminal->x - khw) > semaction->x_max) { /* draw from terminal's */
      x1 -= khw;		   /* left edge to semaction's right edge */
      x2 = semaction->x_max;
      } /* if */
    else if (semaction->x_min > (terminal->x + khw)) { /* draw from */
      x1 += khw;  /* terminal's right edge to semaction's left edge */
      x2 = semaction->x_min;
      } /* if */
    else { /* elements share the same x-area, use minimize (see there) */
      x1 = minimize(terminal->x - khw, terminal->x + khw, semaction->x_min,
       semaction->x_max);
      x2 = x1;
      } /* else */
    y1 += KNOTEN_HEIGHT;
    goto ts_done;
    } /* if */
  if ((y2 + SEM_HEIGHT) < y1) { /* draw from terminal's top to semaction's */
						  /* bottom (regular case) */
    if ((terminal->x - khw) > semaction->x_max) { /* draw from terminal's */
      x1 -= khw;		   /* left edge to semaction's right edge */
      x2 = semaction->x_max;
      } /* if */
    else if (semaction->x_min > (terminal->x + khw)) { /* draw from */
      x1 += khw;  /* terminal's right edge to semaction's left edge */
      x2 = semaction->x_min;
      } /* if */
    else { /* elements share the same x-area, use minimize (see there) */
      x1 = minimize(terminal->x - khw, terminal->x + khw, semaction->x_min,
       semaction->x_max);
      x2 = x1;
      } /* else */
    y2 += SEM_HEIGHT;
    goto ts_done;
    } /* if */
  /* elements at same y-level, don't know if this is possible at all */
  if (x2 > (x1 + khw)) { /* draw from terminal's right to semaction's left */
      y1 += KNOTEN_HHEIGHT;
      y2 += SEM_HHEIGHT;
      x1 += khw;
    } /* if */
  else { /* draw from terminal's left to semaction's right */
      y1 += KNOTEN_HHEIGHT;
      y2 += SEM_HHEIGHT;
      x2 -= khw;
    } /* else */
ts_done: ; /* done */
  draw_dep_arrow(list, x1, y1, x2, y2);
  } /* if */
} /* draw_dep_ts */


/* procedure minimize						*/
/* calculates the x pos of an dependency arrow between two	*/
/* elements with a shared x-area. In other words: a vertical	*/
/* dependency arrow will be drawn.				*/
/* paramters:							*/
/* int x1min, x1max	edges of the first element		*/
/* int x2min, x2max	edges of the second element		*/
/* result:							*/
/* int			x value					*/

int minimize(int x1min, int x1max, int x2min, int x2max)
{
int both_min, both_max, both_x;

if (x1min < x2min) both_min = x2min;
else both_min = x1min;
if (x1max < x2max) both_max = x1max;
else both_max = x2max;
both_x = both_min + (both_max - both_min) / 2;
return(both_x);
} /* minimize */


/* procedure absolute						*/
/* gives back the unsigned value of an integer.			*/
/* parameters:							*/
/* int x	signed integer value				*/

int absolute(int x)
{
if (x < 0) return -x;
else return x;
} /* absolute */


/* procedure draw_dep_arrow					*/
/* draw_dep_as draws a dependency arrow from x1, y1 to x2, y2.	*/
/* parameters:							*/
/* SemList *list	list of semantic actions		*/
/* int x1, y1		arrow's foot				*/
/* int x2, y2		arrow's head				*/

void draw_dep_arrow(SemList *list, int x1, int y1, int x2, int y2)
{
int dx, dy, dg;
double rx, ry;

dx = x2 - x1;
dy = y2 - y1;
dg = absolute(dx) + absolute(dy);
rx = ((double) dx) / ((double) dg);
ry = ((double) dy) / ((double) dg);
if (opts.sem_actions) draw_line(list, RED, x1, y1, x2, y2); /* obstacles */
else XDrawLine(dparms.display, redraw_window, dparms.gc_red, x1, y1, x2, y2);
if (rx < -0.75) { /* arrow points to the left */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_LENGTH, y2 - ARROW_WIDTH, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_LENGTH, y2 + ARROW_WIDTH, x2, y2);
   goto done;
  } /* if */
if (rx > 0.75) { /* arrow points to the right */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_LENGTH, y2 - ARROW_WIDTH, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_LENGTH, y2 + ARROW_WIDTH, x2, y2);
  goto done;
  } /* if */
if (ry < -0.75) { /* arrow points up */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_WIDTH, y2 + ARROW_LENGTH, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_WIDTH, y2 + ARROW_LENGTH, x2, y2);
  goto done;
  } /* if */
if (ry > 0.75) { /* arrow points down */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_WIDTH, y2 - ARROW_LENGTH, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_WIDTH, y2 - ARROW_LENGTH, x2, y2);
  goto done;
  } /* if */
if ((rx < 0.) && (ry < 0.)) { /* arrow points up/left */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_DIA, y2, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2, y2 + ARROW_DIA, x2, y2);
  goto done;
  } /* if */
if ((rx < 0.) && (ry > 0.)){ /* arrow points down/left */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_DIA, y2 - ARROW_DIAW, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 + ARROW_DIAW, y2 - ARROW_DIA, x2, y2);
  goto done;
  } /* if */
if ((rx > 0.) && (ry < 0.)){ /* arrow points up/right */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_DIA, y2 + ARROW_DIAW, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_DIAW, y2 + ARROW_DIA, x2, y2);
  goto done;
  } /* if */
if ((rx > 0.) && (ry > 0.)){ /* arrow points down/right */
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_DIA, y2 - ARROW_DIAW, x2, y2);
  XDrawLine(dparms.display, redraw_window, dparms.gc_red,
   x2 - ARROW_DIAW, y2 - ARROW_DIA, x2, y2);
  } /* if */
done: ;/* done */
} /* draw_dep_arrow */


/* procedure draw_line							*/
/* draw_line draws a line skipping obstacles = semantic actions.	*/
/* the strategy is to split the line everytime it cuts an obstacle and	*/
/* recursively call this procedure until no obstacle is cut, then draw.	*/
/* parameters:								*/
/* SemList *list	list of semantic actions			*/
/* int color		color of line (BLACK or RED)			*/
/* int x1, y1		line's beginning				*/
/* int x2, y2		line's end					*/

void draw_line(SemList *list, int color, int x1, int y1, int x2, int y2)
{
SemLEP ptr = list->first;
int s, i, dist = 0, distvx = 0, distvy = 0;
int schnitt[2][2];
int min_x = MIN(x1, x2);
int max_x = MAX(x1, x2);
int min_y = MIN(y1, y2);
int max_y = MAX(y1, y2);
int delta_x = x2 - x1;
int delta_y = y2 - y1;
int x, y, pxmax, y_unten;
ArgLEP ap;

if (color == RED) { /* red color means dependency arrow => do not draw */
  dist = DIST;	    /* exactly to the obstacle's edge, keep a distance */
  if ((delta_y != 0) && (delta_x != 0)) {
    distvx = DIST * delta_x / delta_y;
    distvy = DIST * delta_y / delta_x;
    } /* if */
  } /* if */
while(ptr) { /* go through all semantic actions in production */
  s = 0;
  y_unten = ptr->y + SEM_HEIGHT;
  pxmax = ptr->x_max;
  ap = ptr->results.first;
  while (ap) {
    if (ap->attr->art == 'A') { /* regard auxiliaries */
      pxmax +=IMAGE_WIDTH + IMAGE_SPACE;
      break;
      } /* if */
    ap = ap->next;
    } /* while */
  if (ptr->y >= min_y && ptr->y <= max_y && delta_y) { /* top cut */
    x = (ptr->y-y1)*delta_x/delta_y + x1;
    if (x >= ptr->x_min && x <= pxmax) {
      schnitt[0][s] = OBEN;
      schnitt[1][s++] = x;
      } /* if */
    } /* if */
  if (y_unten >= min_y && y_unten <= max_y && delta_y) { /* bottom cut */
    x = (y_unten-y1)*delta_x/delta_y + x1;
    if (x >= ptr->x_min && x <= pxmax) {
      schnitt[0][s] = UNTEN;
      schnitt[1][s++] = x;
      } /* if */
    } /* if */
  if (s<2 && ptr->x_min > min_x && ptr->x_min < max_x && delta_x) { /* left */
    y = (ptr->x_min-x1)*delta_y/delta_x + y1;			    /* cut */
    if (y > ptr->y && y < y_unten) {
      schnitt[0][s] = LINKS;
      schnitt[1][s++] = y;
      } /* if */
    } /* if */
  if (s<2 && pxmax > min_x && pxmax < max_x && delta_x) { /* right cut */
    y = (pxmax-x1)*delta_y/delta_x + y1;
    if (y > ptr->y && y < y_unten) {
      schnitt[0][s] = RECHTS;
      schnitt[1][s++] = y;
      } /* if */
    } /* if */
  if (s == 2) { /* two cuts => line goes through obstacle */
    for(i = 0; i <= 1; i++) {
      switch(schnitt[0][i]) {
      case OBEN: /* draw from top cut to element */
        if (y1 <= ptr->y)
         draw_line(list, color, x1, y1, schnitt[1][i] - distvx, ptr->y - dist);
        else draw_line(list, color, x2, y2, schnitt[1][i] - distvx,
         ptr->y - dist);
        break;
      case UNTEN: /* draw from bottom cut to element */
        if (y1 >= y_unten)
         draw_line(list, color, x1, y1, schnitt[1][i] + distvx, y_unten + dist);
        else draw_line(list, color, x2, y2, schnitt[1][i] + distvx,
         y_unten + dist);
        break;
      case LINKS: /* draw from left cut to element */
        if (x1 <= ptr->x_min)
         draw_line(list, color, x1, y1, ptr->x_min - dist,
          schnitt[1][i] - distvy);
        else draw_line(list, color, x2, y2, ptr->x_min - dist,
          schnitt[1][i] - distvy);
        break;
      case RECHTS: /* draw from right cut to element */
        if (x1 >= pxmax)
         draw_line(list, color, x1, y1, pxmax + dist, schnitt[1][i] + distvy);
        else draw_line(list, color, x2, y2, pxmax + dist,
         schnitt[1][i] + distvy);
        break;
      default:
        break;
        } /* switch */
      } /* for */
    return;
    } /* if */
  ptr = ptr->next;
  } /* while */
/* if this line is reached, no obstacle is in the way, because draw_line */
/* was not recursively called => really draw a line */
if (color == BLACK) XDrawLine(dparms.display, redraw_window, dparms.gc_black,
 x1, y1, x2, y2);
if (color == RED) XDrawLine(dparms.display, redraw_window, dparms.gc_red,
 x1, y1, x2, y2);
} /* draw_line */


/* procedure redraw_request					*/
/* redraw_request is called by the X-Viewport callback		*/
/* whenever the viewport's window is resized or scrolled.	*/
/* it simply actualizes the values of the global parameters	*/
/* dparms.r_.... .						*/
/* parameters:							*/
/* Widget drawarea	drawarea widget				*/
/* XtPointer inside	inside widget				*/
/* XtPointer call_data	redraw area data			*/

void redraw_request(Widget drawarea, XtPointer inside, XtPointer call_data)
{
XawPannerReport *report = (XawPannerReport*) call_data;
dparms.r_xmin = report->slider_x;
dparms.r_xmax = report->slider_x + report->slider_width;
dparms.r_ymin = report->slider_y;
dparms.r_ymax = report->slider_y + report->slider_height;
} /* redraw_request */


/* procedure redraw_request2					*/
/* redraw_request2 is called by the X-Windows eventhandler	*/
/* whenever an area in the inside window must be redrawed.	*/
/* parameters:							*/
/* Widget drawarea	inside widget				*/
/* XtPointer closure	not used				*/
/* XEvent* event	event					*/
/* Boolean* bool	not used				*/

void redraw_request2(Widget inside, XtPointer closure, XEvent* event,
 Boolean* bool)
{
redraw_area(event->xgraphicsexpose.x, event->xgraphicsexpose.x +
 event->xgraphicsexpose.width, event->xgraphicsexpose.y,
 event->xgraphicsexpose.y + event->xgraphicsexpose.height);
} /* redraw_request2 */


/* procedure new_area		*/
/* clears and redraws area.	*/
/* parameters:			*/
/* none				*/

void new_area()
{
XClearArea(dparms.display, redraw_window, dparms.r_xmin, dparms.r_ymin,
 (dparms.r_xmax - dparms.r_xmin), (dparms.r_ymax - dparms.r_ymin), False);
redraw_area(dparms.r_xmin, dparms.r_xmax, dparms.r_ymin, dparms.r_ymax);
}


/* procedure redraw_area					*/
/* redraw_area redraws the requested area.			*/
/* parameters:							*/
/* xmin		redraw area's left edge				*/
/* xmax		redraw area's right edge			*/
/* ymin		redraw area's top edge				*/
/* ymax		redraw area's bottom edge			*/

void redraw_area(int xmin, int xmax, int ymin, int ymax)
{
XLEP element = dparms.xlist->first_min;
ArgLEP argument;
TEPLEP son;
int i, anz;
ILEP inp;

	/* 1. PASS: redraw all "solid" elements in redraw area */

if (element != NULL) /* non-empty list */
 while ((element->x_max < xmin) && (element->next_max != NULL))
 /* skip all elements left of redraw area's left edge */
 element = element->next_min;
while ((element != NULL) && (element->x_min <= xmax))	{
 /* go through all elements left of redraw area's right edge */
  if ((element->x_max >= xmin) && (element->y_min <= ymax)
   && (element->y_max >= ymin)) { /* element is in redraw area */
    switch(element->art) {
    case 'A': /* element is an attribut */
      draw_attribut(element->info.a_element);
      break;
    case 'S': /* element is a semantic action */
      draw_semaction(element->info.s_element);
      break;
    case 'T': /* element is a node/leaf (terminal) */
      draw_node(element->info.t_element);
      break;
    default:
      break;
      } /* switch */
    } /* if */
  element = element->next_min;
  } /* while */

	/* 2. PASS: redraw all edges & dependecies in window */

element = dparms.xlist->first_min;
if (element != NULL) /* non-empty list */
 while ((element->x_max < dparms.r_xmin) && (element->next_max != NULL))
 /* skip all elements left of window's left edge */
 element = element->next_min;
while ((element != NULL) && (element->x_min < dparms.r_xmax))	{
 /* go through all elements left of window's right edge */
  if ((element->x_max > dparms.r_xmin) && (element->y_min < dparms.r_ymax)
   && (element->y_max > dparms.r_ymin)) { /* element is in redraw area */
    switch(element->art) {
    case 'A': /* element is an attribut */
      if (element->info.a_element->copy_of != NULL) draw_dep_aa(
       element->info.a_element->copy_of->attr, element->info.a_element);
      if (element->info.a_element->result_of != NULL) draw_dep_sa(
       element->info.a_element->result_of, element->info.a_element);
      anz = element->info.a_element->input_to.anzahl;
      inp = element->info.a_element->input_to.first;
      for (i = 1; i <= anz; i++) { /* Draw all input_to dependencies */
        if (inp->aktion != NULL) draw_dep_as(element->info.a_element,
         inp->aktion);
        if (inp->attr != NULL) draw_dep_aa(element->info.a_element,
         inp->attr);
        inp = inp->next;
        } /* for */
      break;
    case 'S': /* element is a semantic action */
      anz = element->info.s_element->argumente.anzahl;
      argument = element->info.s_element->argumente.first;
      for (i = 1; i <= anz; i++) { /* Draw all argument dependencies */
        if (argument->attr != NULL) draw_dep_as(argument->attr,
         element->info.s_element);
        if (argument->terminal != NULL) draw_dep_ts(argument->terminal,
         element->info.s_element);
        argument = argument->next;
	} /*for */
      anz = element->info.s_element->results.anzahl;
      argument = element->info.s_element->results.first;
      for (i = 1; i <= anz; i++) { /* Draw all result dependencies */
        if (argument->attr != NULL) draw_dep_sa(element->info.s_element,
         argument->attr);
        argument = argument->next;
        } /* for */
      break;
    case 'T': /* element is a node/leaf (terminal) */
      if (element->info.t_element->vater != NULL) /* Draw edge to father */
       draw_edge(element->info.t_element->vater, element->info.t_element);
      anz = element->info.t_element->soehne.anzahl;
      son = element->info.t_element->soehne.first;
      for (i = 1; i <= anz; i++) { /* Draw all edges to sons */
        draw_edge(element->info.t_element, son->symbol);
        son = son->next;
        } /* for */
      anz = element->info.t_element->input_to.anzahl;
      inp = element->info.t_element->input_to.first;
      for (i = 1; i <= anz; i++) { /* Draw all input_to dependencies */
        if (inp->aktion != NULL) draw_dep_ts(element->info.t_element,
         inp->aktion);
        inp = inp->next;
        } /* for */
      break;
    default:
      break;
      } /* switch */
    } /* if */
  element = element->next_min;
  } /* while */
} /* redraw_area */


/* procedure show_tree						*/
/* show_tree shows the attributed syntaxtree in an X-window.	*/
/* parameters:							*/
/* TEP Wurzel		root of the attributed syntaxtree	*/
/* int max_x		maximum calculated x-position		*/
/* int max_y		maximum calculated y-position		*/
/* ANList *an_liste	list of attribut-image configuration	*/
/* x_list *x_liste	x-pos ordered list of all elements	*/

void show_tree(TEP Wurzel, int max_x, int max_y, ANList *an_liste,
 x_list *x_liste)
{
Widget root, entire, quitbutton, inside, infobutton;
Widget menu1, menu1button, menu1entry1, menu1entry2, menu1entry3,
 menu1entry4, menu1entry5, menu1entry6;
Widget menu2, menu2button, menu2entry1, menu2entry2, menu2entry3,
 menu2entry4, menu2entry5;
Widget menu3, menu3button, menu3entry1, menu3entry2, menu3entry3,
 menu3entry4, menu3entry5, menu3entry5b, menu3entry6, menu3entry7;
Widget menu4, menu4button, menu4entry1, menu4entry2, menu4entry3,
 menu4entry4, menu4entry5;
Widget entire_children[7];
XtAppContext app_con;
int argc = 0, i;
Display *dpy;
Screen *screen;
Window scr_wdw;
Cursor arrow1, arrow2;
CPAMP params;
Font font_big, font_small;
unsigned long valuemask = GCForeground | GCBackground | GCFont |
 GCLineWidth | GCLineStyle | GCCapStyle | GCJoinStyle | GCDashOffset |
 GCDashList;
Colormap cmap;
static char dot[] = {1, 1};


/* initialize options */
opts.nodes = 1;
opts.attributs = 1;
opts.sem_actions = 1;
opts.edges = 1;
opts.dependencies = 1;
opts.copies = 1;
opts.monitortype = 0;

/* initialize colours */
black.red = 0;
black.green = 0;
black.blue = 0;
dark_grey.red = 0x6fff;
dark_grey.green = 0x6fff;
dark_grey.blue = 0x6fff;
light_grey.red = 0xafff;
light_grey.green = 0xafff;
light_grey.blue = 0xafff;
white.red = 0xffff;
white.green = 0xffff;
white.blue = 0xffff;
red.red = 0xefff;
red.green = 0;
red.blue = 0;
green.red = 0;
green.green = 0x9fff;
green.blue = 0;

/* initialize application */
root = XtAppInitialize(&app_con, "Xvisualize", (XrmOptionDescList) NULL,
 0, &argc, NULL, NULL, root_arglist, XtNumber(root_arglist));
dpy = XtDisplay(root);
screen = XtScreen(root);
scr_wdw = screen->root;
root_arglist[0].value = (XtArgVal) XCreateBitmapFromData(dpy, scr_wdw,
 (char*) icon_bits, icon_width, icon_height);
root_arglist[1].value = (XtArgVal) XCreateBitmapFromData(dpy, scr_wdw,
 (char*) imask_bits, imask_width, imask_height);
XtSetValues(root, root_arglist, XtNumber(root_arglist));
XtAppAddActions(app_con, root_actions, XtNumber(root_actions));
XtOverrideTranslations(root,
 XtParseTranslationTable("<Message>WM_PROTOCOLS: quit()"));


/* initialize draw parameters */
dparms.display = dpy;
dparms.window = scr_wdw;
cmap = screen->cmap;
XAllocColor(dpy, cmap, &black);
XAllocColor(dpy, cmap, &dark_grey);
XAllocColor(dpy, cmap, &light_grey);
XAllocColor(dpy, cmap, &white);
XAllocColor(dpy, cmap, &red);
XAllocColor(dpy, cmap, &green);
font_big = XLoadFont(dpy, "9x15");
font_small = XLoadFont(dpy, "6x12");
dparms.gc_black = XCreateGC(dpy, scr_wdw, 0, 0);
XSetForeground(dpy, dparms.gc_black, black.pixel);
XSetBackground(dpy, dparms.gc_black, white.pixel);
XSetFont(dpy, dparms.gc_black, font_big);
XSetDashes(dpy, dparms.gc_black, 0, dot, 2);
dparms.gc_red = XCreateGC(dpy, scr_wdw, 0, 0);
XCopyGC(dpy, dparms.gc_black, valuemask, dparms.gc_red);
XSetForeground(dpy, dparms.gc_red, black.pixel);
dparms.gc_green = XCreateGC(dpy, scr_wdw, 0, 0);
XCopyGC(dpy, dparms.gc_black, valuemask, dparms.gc_green);
XSetForeground(dpy, dparms.gc_green, black.pixel);
XSetFont(dpy, dparms.gc_green, font_small);
dparms.r_xmin = 0;
dparms.r_xmax = 680;
dparms.r_ymin = 0;
dparms.r_ymax = 420;
dparms.xlist = x_liste;
dparms.anlist = an_liste;
dparms.wurzel = Wurzel;
dparms.width = max_x - X_START;
dparms.height = max_y - Y_START;

/* create arrow cursors */
arrow1 = XCreatePixmapCursor(dpy, XCreateBitmapFromData(dpy, scr_wdw,
 (char*) arrow1_bits, arrow1_width, arrow1_height), XCreateBitmapFromData(
 dpy, scr_wdw, (char*) amask_bits, amask_width, amask_height),
 &black, &white, 0, 0);
arrow2 = XCreatePixmapCursor(dpy, XCreateBitmapFromData(dpy, scr_wdw,
 (char*) arrow2_bits, arrow2_width, arrow2_height), XCreateBitmapFromData(
 dpy, scr_wdw, (char*) amask_bits, amask_width, amask_height),
 &black, &white, 0, 0);

/* create attribut images */
attr_icon[0] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 address_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[0] = "address        compiler       ";
attr_icon[1] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 depth_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[1] = "depth          compiler       ";
attr_icon[2] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 level_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[2] = "level          compiler       ";
attr_icon[3] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 list_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[3] = "list           compiler       ";
attr_icon[4] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pointer_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[4] = "pointer        compiler       ";
attr_icon[5] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pointers_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[5] = "pointers       compiler       ";
attr_icon[6] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 symtab_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[6] = "symtab         compiler       ";
attr_icon[7] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 table_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[7] = "table          compiler       ";
attr_icon[8] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 tree_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[8] = "tree           compiler       ";
attr_icon[9] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 io_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[9] = "io             compiler       ";
attr_icon[10] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 circle_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[10] = "circle         geometric      ";
attr_icon[11] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 diamond_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[11] = "diamond        geometric      ";
attr_icon[12] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pargram_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[12] = "pargram        geometric      ";
attr_icon[13] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pentagon_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[13] = "pentagon       geometric      ";
attr_icon[14] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 rectangle_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[14] = "rectangle      geometric      ";
attr_icon[15] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 square_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[15] = "square         geometric      ";
attr_icon[16] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 triangle_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[16] = "triangle       geometric      ";
attr_icon[17] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 cross_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[17] = "cross          geometric      ";
attr_icon[18] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 crystal_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[18] = "crystal        geometric      ";
attr_icon[19] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 spindle_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[19] = "spindle        geometric      ";
attr_icon[20] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 code_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[20] = "code           listing        ";
attr_icon[21] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 listing_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[21] = "listing        listing        ";
attr_icon[22] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 text_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[22] = "text           listing        ";
attr_icon[23] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 dictionairy_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[23] = "dictionairy    listing        ";
attr_icon[24] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 document_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[24] = "document       listing        ";
attr_icon[25] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 arrow_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[25] = "arrow          object         ";
attr_icon[26] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 book_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[26] = "book           object         ";
attr_icon[27] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 chair_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[27] = "chair          object         ";
attr_icon[28] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 clock_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[28] = "clock          object         ";
attr_icon[29] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 desk_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[29] = "desk           object         ";
attr_icon[30] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 lightbulp_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[30] = "lightbulp      object         ";
attr_icon[31] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 paper_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[31] = "paper          object         ";
attr_icon[32] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pen_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[32] = "pen            object         ";
attr_icon[33] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 wall_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[33] = "wall           object         ";
attr_icon[34] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 man_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[34] = "man            object         ";
attr_icon[35] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 wheel_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[35] = "wheel          object         ";
attr_icon[36] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 fence_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[36] = "fence          object         ";
attr_icon[37] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 phone_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[37] = "phone          object         ";
attr_icon[38] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 pacman_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[38] = "pacman         object         ";
attr_icon[39] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 face_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[39] = "face           object         ";
attr_icon[40] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 basket_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[40] = "basket         solid          ";
attr_icon[41] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 block_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[41] = "block          solid          ";
attr_icon[42] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 brick_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[42] = "brick          solid          ";
attr_icon[43] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 bubble_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[43] = "bubble         solid          ";
attr_icon[44] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 cone_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[44] = "cone           solid          ";
attr_icon[45] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 cylinder_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[45] = "cylinder       solid          ";
attr_icon[46] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 dice_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[46] = "dice           solid          ";
attr_icon[47] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 ring_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[47] = "ring           solid          ";
attr_icon[48] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 hypnosis_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[48] = "hypnosis       solid          ";
attr_icon[49] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 horseshoe_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[49] = "horseshoe      solid          ";
attr_icon[50] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 zero_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[50] = "zero           number         ";
attr_icon[51] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 one_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[51] = "one            number         ";
attr_icon[52] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 two_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[52] = "two            number         ";
attr_icon[53] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 three_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[53] = "three          number         ";
attr_icon[54] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 four_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[54] = "four           number         ";
attr_icon[55] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 five_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[55] = "five           number         ";
attr_icon[56] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 six_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[56] = "six            number         ";
attr_icon[57] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 seven_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[57] = "seven          number         ";
attr_icon[58] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 eight_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[58] = "eight          number         ";
attr_icon[59] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 nine_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[59] = "nine           number         ";
attr_icon[60] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitala_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[60] = "capital A      letter         ";
attr_icon[61] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalb_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[61] = "capital B      letter         ";
attr_icon[62] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalc_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[62] = "capital C      letter         ";
attr_icon[63] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitald_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[63] = "capital D      letter         ";
attr_icon[64] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitale_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[64] = "capital E      letter         ";
attr_icon[65] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalf_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[65] = "capital F      letter         ";
attr_icon[66] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalg_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[66] = "capital G      letter         ";
attr_icon[67] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalh_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[67] = "capital H      letter         ";
attr_icon[68] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitali_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[68] = "capital I      letter         ";
attr_icon[69] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalj_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[69] = "capital J      letter         ";
attr_icon[70] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalk_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[70] = "capital K      letter         ";
attr_icon[71] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitall_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[71] = "capital L      letter         ";
attr_icon[72] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalm_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[72] = "capital M      letter         ";
attr_icon[73] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitaln_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[73] = "capital N      letter         ";
attr_icon[74] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalo_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[74] = "capital O      letter         ";
attr_icon[75] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalp_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[75] = "capital P      letter         ";
attr_icon[76] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalq_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[76] = "capital Q      letter         ";
attr_icon[77] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalr_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[77] = "capital R      letter         ";
attr_icon[78] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitals_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[78] = "capital S      letter         ";
attr_icon[79] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalt_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[79] = "capital T      letter         ";
attr_icon[80] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalu_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[80] = "capital U      letter         ";
attr_icon[81] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalv_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[81] = "capital V      letter         ";
attr_icon[82] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalw_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[82] = "capital W      letter         ";
attr_icon[83] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalx_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[83] = "capital X      letter         ";
attr_icon[84] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitaly_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[84] = "capital Y      letter         ";
attr_icon[85] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 capitalz_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[85] = "capital Z      letter         ";
attr_icon[86] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalla_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[86] = "small a        letter         ";
attr_icon[87] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallb_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[87] = "small b        letter         ";
attr_icon[88] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallc_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[88] = "small c        letter         ";
attr_icon[89] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalld_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[89] = "small d        letter         ";
attr_icon[90] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalle_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[90] = "small e        letter         ";
attr_icon[91] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallf_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[91] = "small f        letter         ";
attr_icon[92] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallg_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[92] = "small g        letter         ";
attr_icon[93] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallh_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[93] = "small h        letter         ";
attr_icon[94] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalli_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[94] = "small i        letter         ";
attr_icon[95] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallj_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[95] = "small j        letter         ";
attr_icon[96] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallk_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[96] = "small k        letter         ";
attr_icon[97] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalll_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[97] = "small l        letter         ";
attr_icon[98] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallm_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[98] = "small m        letter         ";
attr_icon[99] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalln_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[99] = "small n        letter         ";
attr_icon[100] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallo_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[100] = "small o        letter         ";
attr_icon[101] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallp_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[101] = "small p        letter         ";
attr_icon[102] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallq_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[102] = "small q        letter         ";
attr_icon[103] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallr_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[103] = "small r        letter         ";
attr_icon[104] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smalls_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[104] = "small s        letter         ";
attr_icon[105] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallt_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[105] = "small t        letter         ";
attr_icon[106] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallu_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[106] = "small u        letter         ";
attr_icon[107] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallv_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[107] = "small v        letter         ";
attr_icon[108] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallw_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[108] = "small w        letter         ";
attr_icon[109] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallx_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[109] = "small x        letter         ";
attr_icon[110] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smally_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[110] = "small y        letter         ";
attr_icon[111] = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 smallz_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
attr_name[111] = "small z        letter         ";
noicon = XCreateImage(dpy, screen->root_visual, 1, XYBitmap, 0,
 noicon_bits, IMAGE_WIDTH, IMAGE_HEIGHT, 8, 2);
noicon_name = "no icon        undefined      ";


/* create entire widget which is parent of all other widgets */
entire = XtCreateWidget("Entire", formWidgetClass, root, entire_arglist,
 XtNumber(entire_arglist));

/* create all widgets for the configure menu */
menu1_arglist[0].value = (XtArgVal) arrow1;
menu1 = XtCreateWidget("Menu1", simpleMenuWidgetClass, entire,
 menu1_arglist, XtNumber(menu1_arglist));
menu1entry1 = XtCreateManagedWidget("M1E1", smeBSBObjectClass, menu1,
 menu1entry1_arglist, XtNumber(menu1entry1_arglist));
menu1entry2 = XtCreateManagedWidget("M1E2", smeBSBObjectClass, menu1,
 menu1entry2_arglist, XtNumber(menu1entry2_arglist));
menu1entry3 = XtCreateManagedWidget("M1E3", smeBSBObjectClass, menu1,
 menu1entry3_arglist, XtNumber(menu1entry3_arglist));
menu1entry4 = XtCreateManagedWidget("M1E4", smeBSBObjectClass, menu1,
 menu1entry4_arglist, XtNumber(menu1entry4_arglist));
menu1entry5 = XtCreateManagedWidget("M1E5", smeLineObjectClass, menu1,
 menu1entry5_arglist, XtNumber(menu1entry5_arglist));
menu1entry6 = XtCreateManagedWidget("M1E6", smeBSBObjectClass, menu1,
 menu1entry6_arglist, XtNumber(menu1entry6_arglist));
menu1button_arglist[0].value = (XtArgVal) arrow1;
menu1button = XtCreateWidget("Menu1Button", menuButtonWidgetClass, entire,
 menu1button_arglist, XtNumber(menu1button_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = menu1button;
params->widget3 = NULL;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(menu1entry1, XtNcallback, loadconf, (XtPointer) params);
XtAddCallback(menu1entry2, XtNcallback, saveconf, (XtPointer) params);
XtAddCallback(menu1entry3, XtNcallback, modifyconf, (XtPointer) params);
XtAddCallback(menu1entry4, XtNcallback, defaultconf, NULL);
XtAddCallback(menu1entry6, XtNcallback, configureinfo, (XtPointer) params);

/* create all widgets for the find menu */
menu2_arglist[0].value = (XtArgVal) arrow1;
menu2 = XtCreateWidget("Menu2", simpleMenuWidgetClass, entire,
 menu2_arglist, XtNumber(menu2_arglist));
menu2entry1 = XtCreateManagedWidget("M2E1", smeBSBObjectClass, menu2,
 menu2entry1_arglist, XtNumber(menu2entry1_arglist));
menu2entry2 = XtCreateManagedWidget("M2E2", smeBSBObjectClass, menu2,
 menu2entry2_arglist, XtNumber(menu2entry2_arglist));
menu2entry3 = XtCreateManagedWidget("M2E3", smeBSBObjectClass, menu2,
 menu2entry3_arglist, XtNumber(menu2entry3_arglist));
menu2entry4 = XtCreateManagedWidget("M2E4", smeLineObjectClass, menu2,
 menu2entry4_arglist, XtNumber(menu2entry4_arglist));
menu2entry5 = XtCreateManagedWidget("M2E5", smeBSBObjectClass, menu2,
 menu2entry5_arglist, XtNumber(menu2entry5_arglist));
menu2button_arglist[0].value = (XtArgVal) arrow1;
menu2button_arglist[1].value = (XtArgVal) menu1button;
menu2button = XtCreateWidget("Menu2Button", menuButtonWidgetClass, entire,
 menu2button_arglist, XtNumber(menu2button_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = menu2button;
params->widget3 = menu1button;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(menu2entry1, XtNcallback, findnode, (XtPointer) params);
XtAddCallback(menu2entry2, XtNcallback, findattr, (XtPointer) params);
XtAddCallback(menu2entry3, XtNcallback, findfunc, (XtPointer) params);
XtAddCallback(menu2entry5, XtNcallback, globalview, (XtPointer) params);

/* create all widgets for the show menu */
menu3_arglist[0].value = (XtArgVal) arrow1;
menu3 = XtCreateWidget("Menu3", simpleMenuWidgetClass, entire,
 menu3_arglist, XtNumber(menu3_arglist));
menu3entry1 = XtCreateManagedWidget("M3E1", smeBSBObjectClass, menu3,
 menu3entry1_arglist, XtNumber(menu3entry1_arglist));
menu3entry2 = XtCreateManagedWidget("M3E2", smeBSBObjectClass, menu3,
 menu3entry2_arglist, XtNumber(menu3entry2_arglist));
menu3entry3 = XtCreateManagedWidget("M3E3", smeBSBObjectClass, menu3,
 menu3entry3_arglist, XtNumber(menu3entry3_arglist));
menu3entry4 = XtCreateManagedWidget("M3E4", smeBSBObjectClass, menu3,
 menu3entry4_arglist, XtNumber(menu3entry4_arglist));
menu3entry5 = XtCreateManagedWidget("M3E5", smeBSBObjectClass, menu3,
 menu3entry5_arglist, XtNumber(menu3entry5_arglist));
menu3entry5b = XtCreateManagedWidget("M3E5b", smeBSBObjectClass, menu3,
 menu3entry5b_arglist, XtNumber(menu3entry5b_arglist));
menu3entry6 = XtCreateManagedWidget("M3E6", smeLineObjectClass, menu3,
 menu3entry6_arglist, XtNumber(menu3entry6_arglist));
menu3entry7 = XtCreateManagedWidget("M3E7", smeBSBObjectClass, menu3,
 menu3entry7_arglist, XtNumber(menu3entry7_arglist));
menu3button_arglist[0].value = (XtArgVal) arrow1;
menu3button_arglist[1].value = (XtArgVal) menu2button;
menu3button = XtCreateWidget("Menu3Button", menuButtonWidgetClass, entire,
 menu3button_arglist, XtNumber(menu3button_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = menu3button;
params->widget3 = menu2button;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(menu3entry1, XtNcallback, shownodes, NULL);
XtAddCallback(menu3entry2, XtNcallback, showedges, NULL);
XtAddCallback(menu3entry3, XtNcallback, showattributs, NULL);
XtAddCallback(menu3entry4, XtNcallback, showfunctions, NULL);
XtAddCallback(menu3entry5, XtNcallback, showdependencies, NULL);
XtAddCallback(menu3entry5b, XtNcallback, showcopies, NULL);
XtAddCallback(menu3entry7, XtNcallback, showinfo, (XtPointer) params);

/* create all widgets for the monitortype menu */
menu4_arglist[0].value = (XtArgVal) arrow1;
menu4 = XtCreateWidget("Menu4", simpleMenuWidgetClass, entire,
 menu4_arglist, XtNumber(menu4_arglist));
menu4entry1 = XtCreateManagedWidget("M4E1", smeBSBObjectClass, menu4,
 menu4entry1_arglist, XtNumber(menu4entry1_arglist));
menu4entry2 = XtCreateManagedWidget("M4E2", smeBSBObjectClass, menu4,
 menu4entry2_arglist, XtNumber(menu4entry2_arglist));
menu4entry3 = XtCreateManagedWidget("M4E3", smeBSBObjectClass, menu4,
 menu4entry3_arglist, XtNumber(menu4entry3_arglist));
menu4entry4 = XtCreateManagedWidget("M4E4", smeLineObjectClass, menu4,
 menu4entry4_arglist, XtNumber(menu4entry4_arglist));
menu4entry5 = XtCreateManagedWidget("M4E5", smeBSBObjectClass, menu4,
 menu4entry5_arglist, XtNumber(menu4entry5_arglist));
menu4button_arglist[0].value = (XtArgVal) arrow1;
menu4button_arglist[1].value = (XtArgVal) menu3button;
menu4button = XtCreateWidget("Menu4Button", menuButtonWidgetClass, entire,
 menu4button_arglist, XtNumber(menu4button_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = menu4button;
params->widget3 = menu3button;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(menu4entry1, XtNcallback, selectbw, NULL);
XtAddCallback(menu4entry2, XtNcallback, selectgrey, NULL);
XtAddCallback(menu4entry3, XtNcallback, selectcolor, NULL);
XtAddCallback(menu4entry5, XtNcallback, monitorinfo, (XtPointer) params);

/* create quit & info button widgets */
quitbutton_arglist[0].value = (XtArgVal) arrow1;
quitbutton_arglist[1].value = (XtArgVal) menu4button;
quitbutton = XtCreateWidget("QuitButton", commandWidgetClass, entire,
 quitbutton_arglist, XtNumber(quitbutton_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = quitbutton;
params->widget3 = menu4button;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(quitbutton, XtNcallback, suretoquit, (XtPointer) params);
infobutton_arglist[0].value = (XtArgVal) arrow1;
infobutton_arglist[1].value = (XtArgVal) quitbutton;
infobutton = XtCreateWidget("InfoButton", commandWidgetClass, entire,
 infobutton_arglist, XtNumber(infobutton_arglist));
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = infobutton;
params->widget3 = quitbutton;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddCallback(infobutton, XtNcallback, information, (XtPointer) params);

/* create drawarea widgets */
drawarea_arglist[0].value = (XtArgVal) infobutton;
drawarea = XtCreateWidget("DrawArea", viewportWidgetClass, entire, drawarea_arglist, XtNumber(drawarea_arglist));
inside_arglist[0].value = (XtArgVal) arrow2;
inside_arglist[1].value = (XtArgVal) dparms.height;
inside_arglist[2].value = (XtArgVal) dparms.width;
inside = XtCreateManagedWidget("Inside", simpleWidgetClass, drawarea,
 inside_arglist, XtNumber(inside_arglist));
XtAddCallback(drawarea, XtNreportCallback, redraw_request, (XtPointer)
 inside);
XtAddEventHandler(inside, ExposureMask, FALSE, redraw_request2,
 (XtPointer) NULL);
params = (CPAMP) malloc(sizeof(CPAMS));
params->widget1 = entire;
params->widget2 = menu1button;
params->widget3 = NULL;
params->arrow = &arrow1;
params->function = NULL;
params->params = NULL;
XtAddEventHandler(inside, ButtonPressMask, FALSE, elementinfo,
 (XtPointer) params);

/* Manage and realize widgets */
entire_children[0] = menu1button;
entire_children[1] = menu2button;
entire_children[2] = menu3button;
entire_children[3] = menu4button;
entire_children[4] = quitbutton;
entire_children[5] = infobutton;
entire_children[6] = drawarea;
XtManageChildren(entire_children, 7);
XtManageChild(entire);
XtRealizeWidget(root);

/* set variable wm_delete_window for window manager abort request */
wm_delete_window = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
XSetWMProtocols(dpy, XtWindow(root), &wm_delete_window, 1);

/* draw_area */
redraw_window = XtWindow(inside);
new_area();

/* enter application's main loop */
XtAppMainLoop(app_con);

} /* show_tree */
