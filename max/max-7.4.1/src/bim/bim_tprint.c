


#include <X11/StringDefs.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/Scrollbar.h>
#include <X11/Xaw/Tree.h>
#include <X11/Xaw/Label.h>

#include "bim_node.h"
#include "bim_nodeinfo.h"
#include "bim_util.h"
#include "bim_attrfunc.h"
#include "bim_tprint.h"
#include "bim_typeconv.c"

#define		WIDTH_OF_VIEWPORT		400
#define		HEIGHT_OF_VIEWPORT		400
#define		BUFFER_SIZE			512

#define 	Name(n)		((n)->node_info->name)

/*****************************************************************************
 *                                                                           *
 * Globale Variablen                                                         *
 *                                                                           *
 *****************************************************************************/

Boolean AppMainLoop = TRUE;
Screen * screen_for_convert;


/*****************************************************************************
 *                                                                           *
 * Vorausdeklarationen                                                       *
 *                                                                           *
 *****************************************************************************/

void NodeCallback ( Widget node,XtPointer client_data, XtPointer call_data );





/*****************************************************************************
 *                                                                           *
 * DUMMYS                                                                    *
 *                                                                           *
 *****************************************************************************/


/*****************************************************************************
 *                                                                           *
 * Private Funktionen                                                        *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                                                                           *
 * NAME      :  BackgroundMapProcedure                                       *
 *                                                                           *
 * PROCEDURE :  BackgroundMapProcedure() ist eine Xt Hintergrundfunktion.    *
 * 		Sie ist fuer das mappen des Viewports                        *
 *              zustaendig.                                                  *
 * INPUT     :  XtPointer client_data ist ein Pointer auf das zu mappende    *
 * 			Widget.                                              *
 * OUTPUT    :  Boolean BackgroundMapProcedure() hat als Rueckgabewert immer *
 *			TRUE, um Xt mitzuteilen, dass die Funktion aus der   * 
 *			Background Procedure Liste wieder entfernt werden    *
 *			soll.                                                *
 *                                                                           *
 *****************************************************************************/

Boolean BackgroundMapProcedure ( XtPointer client_data )
{
   Widget w = (Widget) client_data;

#ifdef DEBUG
printf("BackgroundMapProcedure()\n");
#endif

   XtMapWidget(w);

   return (TRUE);
}


/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateXCONTEXT                                               *
 *                                                                           *
 * PROCEDURE :	CreateXCONTEXT() stellt einen neuen X-Kontext bereit.        *
 *		Der Inhalt der Struktur wird so weit wie moeglich belegt.    *
 * INPUT     :  int argc ist der Argument Counter der Procedur main().       *
 *              char **argv ist der Argument Vektor der Procedur main().     *
 * OUTPUT    :	XCONTEXT *CreateNewXCONTEXT() liefert als Ergebnis einen     *
 *			Pointer auf den neu allocierten und initialisierten  *
 * 			Kontext.                                             *
 *                                                                           *
 *****************************************************************************/

XCONTEXT *CreateXCONTEXT ( int argc,
	                   char **argv )
{
   XCONTEXT *xcontext = (XCONTEXT *) XtMalloc (sizeof(XCONTEXT));

#ifdef DEBUG
printf("CreateXCONTEXT()\n");
#endif

   /*
    * Save the arguments
    */

   xcontext->argc = argc;
   xcontext->argv = (char **) XtMalloc (argc * sizeof(char *));
   bcopy(argv, xcontext->argv, argc * sizeof(char *));

   /*
    * Create the Xt context
    */

   XtToolkitInitialize();

   xcontext->app_context = XtCreateApplicationContext();

   xcontext->display = XtOpenDisplay(xcontext->app_context,NULL,NULL,"TBrowser",
			            NULL, 0, &xcontext->argc,xcontext->argv);

   xcontext->argc = argc;
   bcopy(argv, xcontext->argv, argc * sizeof(char *));

   xcontext->attr_mask = GetAttrMask();

   return(xcontext);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CopyXCONTEXT                                                 *
 *                                                                           *
 * PROCEDURE :	CopyXCONTEXT() kopiert einen X-Kontext, wobei auch           *
 *		der entsprchend benoetigte Speicherbereich reserviert wird.  *
 *		Der Inhalt der neuen Struktur wird so weit wie moeglich      *
 *		belegt.                                                      *
 * INPUT     :  XCONTEXT *xcontext ist ein Pointer auf den zu kopierenden    *
 *			Kontext.                                             *
 * OUTPUT    :	XCONTEXT *CopyXCONTEXT() liefert als Ergebnis einen          *
 *			Pointer auf den neu allocierten und initialisierten  *
 * 			Kontext.                                             *
 *                                                                           *
 *****************************************************************************/

XCONTEXT *CopyXCONTEXT ( XCONTEXT *xcontext )
{
   XCONTEXT *xcontext_new = (XCONTEXT *) XtMalloc (sizeof(XCONTEXT));

#ifdef DEBUG
printf("CopyXCONTEXT()\n");
#endif

   /*
    * Save the arguments
    */

   xcontext_new->argc = xcontext->argc;
   xcontext_new->argv = (char **) XtMalloc (xcontext->argc * sizeof(char *));
   bcopy(xcontext->argv, xcontext_new->argv, xcontext->argc * sizeof(char *));

   xcontext_new->display = xcontext->display;
   xcontext_new->app_context = xcontext->app_context;

   xcontext_new->attr_mask = CopyAttrMask(xcontext->attr_mask);

   return(xcontext_new);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  DestroyXCONTEXT                                              *
 *                                                                           *
 * PROCEDURE :	DestroyXCONTEXT() gibt den durch einen X-Kontext belegten    *
 *		Speicherbereich frei.                                        *
 * INPUT     :  XCONTEXT *xcontext ist ein Pointer auf den zu zerstoerenden  *
 *			Kontext.                                             *
 * OUTPUT    :	                                                             *
 *                                                                           *
 *****************************************************************************/

void DestroyXCONTEXT ( XCONTEXT *xcontext )
{
#ifdef DEBUG
printf("DestroyXCONTEXT()\n");
#endif

   XtFree((char *) xcontext->argv);

   DestroyAttrMask(xcontext->attr_mask);

   XtFree((char *) xcontext);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UpdateMaxTree                                                *
 *                                                                           *
 * PROCEDURE :	UpdateMaxTree() verbindet alle MAX Knoten eines Baumes mit   *
 *		einem vorgegebenen Kontext.                                  *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf die Wurzel des        *
 *			MAX-Baumes, der an den Kontext gebunden werden soll. *
 *              Context *context ist ein Pointer auf den zu setzenden        *
 *			Kontext.                                             *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UpdateMaxTree( MAX_NODE *max_tree,
		    Context  *context )
{
   MAX_NODE *akt_node = max_tree;

#ifdef DEBUG
printf("UpdateMaxTree()\n");
#endif

   while (akt_node != NULL)
      {
      Context(akt_node) = context;
      Widget(akt_node) = NULL;

      if (akt_node->children != NULL)
	 UpdateMaxTree(akt_node->children,context);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CopyContext                                                  *
 *                                                                           *
 * PROCEDURE :	CopyContext() kopiert einen Kontext, wobei Speicher fuer die *
 *		Kopie allociert und der Inhalt der Struktur belegt wird.     *
 *		Der zu diesem Kontext gehoerende MAX-Baum muss mit angegeben *
 *		werden. Der Kontext wird ausserdem in die Kontexthierarchie  *
 *		eingehaengt.                                                 *
 * INPUT     :  Context *source ist ein Pointer auf die Quelle.              *
 *		MAX_NODE *max_node ist ein Pointer auf die Wurzel des        *
 *			MAX-Baumes, der an den Kontext gebunden werden soll. *
 * OUTPUT    :  Context *CopyContext() gibt einen Pointer auf den neu        *
 * 			allocierten und initialisierten Kontext zurueck.     *
 *                                                                           *
 *****************************************************************************/

Context *CopyContext ( Context  *source,
		       MAX_NODE *max_node )
{
   int      count;
   Context  *last;
   Context  *context = (Context *) XtMalloc (sizeof(Context));

#ifdef DEBUG
printf("CopyContext()\n");
#endif

   context->xcontext = CopyXCONTEXT(source->xcontext);

   context->max_tree = (void *) Bim_CopyMaxTree(max_node,(MAX_NODE *) NULL); 

   UpdateMaxTree((MAX_NODE *) context->max_tree,context);

   context->incarnation = source->incarnation + 1;
   context->children = NULL;
   context->next = NULL;
   context->parent = source;

   if (source->children == NULL)
      {
      count = 1;
      context->prev = NULL;
      source->children = context;
      }
   else
      {
      last = source->children;
      count = 2;
      while (last->next != NULL)
	 {
	 count++;
	 last = last->next;
	 }
      last->next = context;
      context->prev = last;
      }

   context->number = count;

   return (context);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  DestroyContext                                               *
 *                                                                           *
 * PROCEDURE :	DestroyContext() zerstoert einen Baum von Kontexten,         *
 *		einschliesslich aller rechten Nachbarn.                      *
 * INPUT     :  Context *context ist ein Pointer die Wurzel des zu           *
 *			zerstoerenden Kontextbaumes.                         *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void DestroyContext( Context *context )
{
#ifdef DEBUG
printf("DestroyContext()\n");
#endif

   if (context == NULL)
      return;

   if (context->children != NULL)
      DestroyContext(context->children);

   if (context->next != NULL)
      DestroyContext(context->next);

   XtDestroyWidget(context->xcontext->toplevel);

   DestroyXCONTEXT(context->xcontext);

   XtFree((char *) context);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  InsertNodeWidget                                             *
 *                                                                           *
 * PROCEDURE :	InsertNodeWidget() fuegt abhaengig von einem MAX-Node ein    *
 *		NodeWidget in ein TreeWidget ein.                            *
 * INPUT     :	Widget tree ist das TreeWidget, in welches der neue Knoten   *
 *			eingefuegt werden soll.                              *
 *		Widget parent ist das Parent Widget, unter welchem der neue  *
 *			Knoten im Baum eingehaengt werden soll.              *
 *  		MAX_NODE *node ist ein Pointer auf einen MAX-Knoten, welcher *
 *			fuer den Inhalt des neuen NodeWidgets verantwortlich *
 *			sein soll.                                           *
 * OUTPUT    :	Widget InsertNodeWidget() gibt das neu erzeugte NodeWidget   *
 *			zurueck.                                             *
 *                                                                           *
 *****************************************************************************/

Widget InsertNodeWidget ( Widget   tree,
                          Widget   parent,
	                  MAX_NODE *node )
{
   Widget new;
   Widget test;
   int number;
   MAX_NODE *akt_node = node;

#ifdef DEBUG
printf("InsertNodeWidget()\n");
#endif

   /*
    * Insert the new node
    */

   if (parent == NULL)
      new = XtVaCreateManagedWidget(
	 node->node_info->name,
	 nodeWidgetClass,
	 tree,
	 XtNlabel, node->node_info->name,
	 XtNhiddenTree, HiddenTree(node),
	 XtNmarked, Marked(node),
	 NULL);
   else
      new = XtVaCreateManagedWidget(
	 node->node_info->name,
	 nodeWidgetClass,
	 tree,
	 XtNlabel, node->node_info->name,
	 XtNtreeParent, parent,
	 XtNhiddenTree, HiddenTree(node),
	 XtNmarked, Marked(node),
	 NULL);

   XtAddCallback(new,XtNcallback,NodeCallback,(XtPointer) node);

   ConnectMenuToNode(node, new);

   /*
    * Create the attribute child widget
    */

   if (ShowedAttributes(node) == TRUE)
      {
      AttrWidget(akt_node) = CreateAttrList(node,new,AttrMask(akt_node));
      XtVaSetValues(
         new,
         XtNshowAttributes, TRUE,
         NULL);
      }

   return(new);
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  MakeCleanTree                                                *
 *                                                                           *
 * PROCEDURE :	MakeCleanTree() sorgt dafuer, dass der MAX-Baum in einem     *
 *		definierten Initialzustand uebergeht.                        *
 * INPUT     :	MAX_NODE *max_tree ist ein Pointer auf die Wurzel des Baums. *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MakeCleanTree ( MAX_NODE *max_tree )
{
   MAX_NODE *akt_node = max_tree;

#ifdef DEBUG
printf("MakeCleanTree()\n");
#endif

   while (akt_node != NULL)
      {
      ShowedAttributes(akt_node) = FALSE;
      HiddenTree(akt_node) = TRUE;
      Marked(akt_node) = FALSE;
      Widget(akt_node) = NULL;
      AttrWidget(akt_node) = NULL;
      Context(akt_node) = NULL;
      AttrMask(akt_node) = NULL;

      if (akt_node->children == NULL)
	 HiddenTree(akt_node) = FALSE;
      else
	 MakeCleanTree(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateTree                                                   *
 *                                                                           *
 * PROCEDURE :	CreateTree() ist eine rekursive Funktion zur Umwandlung eins *
 *		MAX-Baumes in ein Tree Widget.                               *
 * INPUT     :	Context *context ist ein Pointer auf die Kontextstruktur     *
 *			des Baumes.                                          *
 *		MAX_NODE *max_tree ist ein Pointer auf die Wurzel des        *
 *			umzuwandelnden MAX-Baumes.                           *
 *		Widget parent ist das Eltern Widget des zu erzeugenden       *
 *			Unterbaums (gegebenenfalls NULL).                    *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreateTree ( Context  *context, 
		  MAX_NODE *max_tree,
	          Widget   parent )
{
   MAX_NODE *akt_node = max_tree;

#ifdef DEBUG
printf("CreateTree()\n");
#endif

   while (akt_node != NULL)
      {
      Widget(akt_node) = InsertNodeWidget(context->xcontext->tree,
						   parent,akt_node);
      if (akt_node->children != NULL && HiddenTree(akt_node) != TRUE)
         CreateTree(context,akt_node->children,Widget(akt_node));
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CreatePath                                                   *
 *                                                                           *
 * PROCEDURE :	CreatePath() ueberprueft, ob zu einem gegebenen MAX Knoten   *
 *		ein entsprechender Pfad im Widget Baum existiert und         *
 *		legt diesen gegebenenfalls an, d.h. zugefaltete Unterbaeume  *
 *		werden aufgeklappt.                                          *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreatePath ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("CreatePath()\n");
#endif

   if (Widget(max_node) == NULL)
      {

      /*
       * Pfad bis zum ersten Knoten mit Widget suchen
       */

      if (max_node->parent != NULL)
         CreatePath (max_node->parent);

      /*
       * Pfad oeffnen
       */

      if (HiddenTree(max_node->parent) == TRUE)
	 {
         HiddenTree(max_node->parent) = FALSE;
         XtVaSetValues(
            Widget(max_node->parent),
            XtNhiddenTree, FALSE,
            NULL);
         CreateTree (Context(max_node->parent),
		     max_node->parent->children,
		     Widget(max_node->parent));
	 }
      }
}

 


/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateTreeViewport                                           *
 *                                                                           *
 * PROCEDURE : 	CreateTreeViewport() generiert zu einem gegebenen Kontext    *
 *		einen Viewport mit dem entsprechenden Widget Baum.           *
 * INPUT     :  Context *context ist ein Pointer auf den Kontext.            *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreateTreeViewport ( Context *context )
{
   char	  buffer[BUFFER_SIZE];
   String name;
   int    argc;
   char   **argv;
   Cardinal num_children;
   Widget *children;
   Dimension sum_width, child_width;

#ifdef DEBUG
printf("CreateTreeViewport()\n");
#endif

   /*
    * Anlegen einer Sicherheitskopie fuer Toplevel-Shell-Parameter
    */

   argc = context->xcontext->argc;
   argv = (char **) XtMalloc (context->xcontext->argc * sizeof(char *));
   bcopy(context->xcontext->argv,argv,context->xcontext->argc * sizeof(char *));

   if (context->incarnation == 0)
      strcpy(buffer,(argc) ? context->xcontext->argv[0] : "MAX AST-browser");
   else
      {
      XtVaGetValues((context->parent)->xcontext->toplevel,
	 XtNiconName, &name,
	 NULL);
      sprintf(buffer,"%s.%d",name,context->number);
      }

   context->xcontext->toplevel = XtVaAppCreateShell("Shell", 
      "TBrowser", 
      topLevelShellWidgetClass,
      context->xcontext->display, 
      XtNargc, argc,
      XtNargv, argv,
      XtNiconName, buffer,
      NULL);

   screen_for_convert = XtScreen(context->xcontext->toplevel);

   XtFree((char *) argv);

   XtAppSetTypeConverter(context->xcontext->app_context,XtRString,XtRPixmap,strToPixmap, 
                         NULL,0,XtCacheByDisplay,NULL);

   /*
    * Generieren des Viewport- und Tree-Widgets
    */

   context->xcontext->form = XtVaCreateWidget(
      "Form",
      formWidgetClass,
      context->xcontext->toplevel,
      XtNdefaultDistance, 0,
      NULL);

   context->xcontext->global_menu = CreateGlobalMenu(
      context->xcontext->form,
      (MAX_NODE *) context->max_tree,
      context->xcontext->attr_mask);

   /*
    * Berechnung der Breite des Viewports
    */

   XtVaGetValues(context->xcontext->global_menu,
      XtNnumChildren, &num_children,
      XtNchildren, &children,
      NULL);

   sum_width = 0;
   for (; num_children > 0; num_children--)
      {
      XtVaGetValues(*children,
	 XtNwidth, &child_width,
	 NULL);
      children++;
      sum_width += child_width;
      }

   context->xcontext->viewport = XtVaCreateWidget(
      "Viewport",
      viewportWidgetClass,
      context->xcontext->form,
      XtNtop, XtChainTop,
      XtNallowHoriz, True,
      XtNallowVert, True,
      XtNforceBars, True,
      XtNheight, HEIGHT_OF_VIEWPORT,
      XtNwidth, sum_width,
      XtNfromVert, context->xcontext->global_menu,
      XtNvertDistance, 0,
      NULL);

   /*
    * Einhaengen der Menuezeile
    */

   CreateNodeMenu(context->xcontext->viewport);

   context->xcontext->h_scrollbar = XtNameToWidget(
      context->xcontext->viewport,
      "horizontal");
   context->xcontext->v_scrollbar = XtNameToWidget(
      context->xcontext->viewport,
      "vertical");

   context->xcontext->tree = XtVaCreateManagedWidget(
      "Tree",
      treeWidgetClass,
      context->xcontext->viewport,
      XtNgravity, NorthGravity,
      NULL);

   /*
    * Aufbau des Widget-Baumes
    */

   CreateTree(context,(MAX_NODE *) context->max_tree,(Widget) NULL);

   XawTreeForceLayout(context->xcontext->tree);
   XtManageChild(context->xcontext->viewport);
   XtManageChild(context->xcontext->form);
   XtRealizeWidget(context->xcontext->toplevel);
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  DestroySubtree                                               *
 *                                                                           *
 * PROCEDURE :	DestroySubtree() loescht einen Widget-Baum.                  *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den Wurzelknoten im   *
 *			zugehoerigen MAX-Baum.                               *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void DestroySubtree ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node->children;

#ifdef DEBUG
printf("DestroySubtree()\n");
#endif

   while (akt_node != NULL)
      {
      if (Widget(akt_node) == NULL)
         return;

      DestroySubtree(akt_node);
      XtUnmanageChild(Widget(akt_node));
      XtDestroyWidget(Widget(akt_node));
      Widget(akt_node) = NULL;
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateSubtree                                                *
 *                                                                           *
 * PROCEDURE :	CreateSubtree() generiert den zu einem MAX Knoten gehoeren-  *
 *		den Unterbaum als Widget Unterbaum - es wird NUR der Unter-  *
 *		baum generiert.                                              *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den MAX Knoten, dessen*
 *			Unterbaum dargestellt werden soll.                   *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreateSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("CreateSubtree()\n");
#endif

   if (max_node->children != NULL)
    CreateTree(Context(max_node),max_node->children,
	       Widget(max_node));
}






/*****************************************************************************
 *                                                                           *
 * NAME      :  FindNextNodePreorderSubtree                                  *
 *                                                                           *
 * PROCEDURE :	FindNextNodePreorderSubtree() sucht zu einem vorgegebenen    *
 *              Namen rekursiv nach dem naechsten Knoten in Preorder.        *
 *		Es wird nur im Unterbaum gesucht.                            *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindNextNodePreorderSubtree() liefert den Pointer  *
 *                      auf einen eventuell gefundenen Knoten.               *
 *			Bei erfolgloser suche wird NULL zurueckgegeben.      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindNextNodePreorderSubtree ( MAX_NODE *max_node,
					char     *name )
{
   MAX_NODE *child_node, *res_node;

#ifdef DEBUG
printf("FindNextNodePreorderSubtree()\n");
#endif

   if (max_node == NULL)
      return(max_node);

   if (Bim_IsOfSort(max_node,name) == TRUE)
      return(max_node);

   child_node = max_node->children;
   while (child_node != NULL)
      {
      res_node = FindNextNodePreorderSubtree(child_node,name);
      if (res_node != NULL)
	 return(res_node);
      child_node = child_node->next;
      }

   return(NULL);
}






/*****************************************************************************
 *                                                                           *
 * NAME      :  FindNextNodePreorder                                         *
 *                                                                           *
 * PROCEDURE :	FindNextNodePreorder() sucht zu einem vorgegebenen Namen     *
 *		nach dem naechsten Knoten in Preorder.                       *
 *		Es werden auch die entsprechenden uebergeordneten Knoten     *
 *		durchsucht.                                                  *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindNextNodePreorder() liefert den Pointer auf     *
 *			einen eventuell gefundenen Knoten. Bei erfolgloser   *
 *			Suche wird NULL zurueckgegeben.                      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindNextNodePreorder ( MAX_NODE *max_node,
		                 char     *name)
{
   MAX_NODE *res_node, *child_node, *parent_node, *next_node;

#ifdef DEBUG
printf("FindNextNodePreorder()\n");
#endif
  
   if (max_node == NULL)
      return (NULL);

   child_node = max_node->children;
   while (child_node != NULL)
      {
      res_node = FindNextNodePreorderSubtree(child_node,name);
      if (res_node != NULL)
	 return(res_node);
      child_node = child_node->next;
      }

   parent_node = max_node;
   while (parent_node != NULL)
      {
      next_node = parent_node->next;
      while (next_node != NULL)
	 {
	 res_node = FindNextNodePreorderSubtree(next_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 next_node = next_node->next;
	 }
      parent_node = parent_node->parent;
      }

   return(NULL);
}






/*****************************************************************************
 *                                                                           *
 * NAME      :  FindPreviousNodePreorderSubtree                              *
 *                                                                           *
 * PROCEDURE :	FindPreviousNodePreorderSubtree() sucht zu einem vorgegebenen*
 *              Namen rekursiv nach dem naechsten Knoten in Preorder.        *
 *		Es wird nur im Unterbaum gesucht.                            *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindPreviousNodePreorderSubtree() liefert den Pointer*
 *                      auf einen eventuell gefundenen Knoten.               *
 *			Bei erfolgloser suche wird NULL zurueckgegeben.      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindPreviousNodePreorderSubtree( MAX_NODE *max_node,
					   char     *name )
{
   MAX_NODE *last_node, *res_node;

#ifdef DEBUG
printf("FindPreviousNodePreorderSubtree()\n");
#endif

   if (max_node == NULL)
      return(NULL);

   if (max_node->children != NULL)
      {
      last_node = max_node->children;
      while (last_node->next != NULL)
	 last_node = last_node->next;
	
      while(last_node != NULL)
	 {
	 res_node = FindPreviousNodePreorderSubtree(last_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 last_node = last_node->prev;
	 }
      }

   if (Bim_IsOfSort(max_node,name) == TRUE)
      return(max_node);

   return(NULL);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  FindPreviousNodePreorder                                     *
 *                                                                           *
 * PROCEDURE :	FindPreviousNodePreorder() sucht zu einem vorgegebenen Namen *
 *		nach dem vorhergehenden Knoten in Preorder.                  *
 *		Es werden auch Vorgaengerknoten beruecksichtigt.             *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindPreviousNodePreorder() liefert den Pointer auf *
 *			einen eventuell gefundenen Knoten. Bei erfolgloser   *
 *			Suche wird NULL zurueckgegeben.                      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindPreviousNodePreorder ( MAX_NODE *max_node,
		                     char     *name )
{
   MAX_NODE *res_node, *parent_node, *prev_node;

#ifdef DEBUG
printf("FindPreviousNodePreorder()\n");
#endif

   if (max_node == NULL)
      return (NULL);

   parent_node = max_node;
   while (parent_node != NULL)
      {
      prev_node = parent_node->prev;
      while (prev_node != NULL)
	 {
	 res_node = FindPreviousNodePreorderSubtree(prev_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 prev_node = prev_node->prev;
	 }
      parent_node = parent_node->parent;
      if (parent_node != NULL && Bim_IsOfSort(parent_node,name) == TRUE)
	 return(parent_node);
      }

   return(NULL);
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  FindNextNodePostorderSubtree                                 *
 *                                                                           *
 * PROCEDURE :	FindNextNodePostorderSubtree() sucht zu einem vorgegebenen   *
 *              Namen rekursiv nach dem naechsten Knoten in Postorder.       *
 *		Es wird nur im Unterbaum gesucht.                            *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindNextNodePostorderSubtree() liefert den Pointer *
 *                      auf einen eventuell gefundenen Knoten.               *
 *			Bei erfolgloser suche wird NULL zurueckgegeben.      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindNextNodePostorderSubtree ( MAX_NODE *max_node,
			                 char     *name )
{
   MAX_NODE *child_node, *res_node;

#ifdef DEBUG
printf("FindNextNodePostorderSubtree()\n");
#endif

   if (max_node == NULL)
      return(max_node);

   child_node = max_node->children;
   while (child_node != NULL)
      {
      res_node = FindNextNodePostorderSubtree(child_node,name);
      if (res_node != NULL)
	 return(res_node);
      child_node = child_node->next;
      }

   if (Bim_IsOfSort(max_node,name) == TRUE)
      return(max_node);

   return(NULL);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  FindNextNodePostorder                                        *
 *                                                                           *
 * PROCEDURE :	FindNextNodePostorder() sucht zu einem vorgegebenen Namen    *
 *		nach dem naechsten Knoten in Postorder.                      *
 *		Es werden auch Vorgaengerknoten beruecksichtigt.             *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindNextNodePostorder() liefert den Pointer auf    *
 *			einen eventuell gefundenen Knoten. Bei erfolgloser   *
 *			Suche wird NULL zurueckgegeben.                      *
 *                                                                           *
 *****************************************************************************/
  
MAX_NODE *FindNextNodePostorder ( MAX_NODE *max_node,
		                  char     *name )
{
   MAX_NODE *res_node, *parent_node, *next_node;

#ifdef DEBUG
printf("FindNextNodePostorder()\n");
#endif
 
   if (max_node == NULL)
      return (NULL);

   parent_node = max_node;
   while (parent_node != NULL)
      {
      next_node = parent_node->next;
      while (next_node != NULL)
	 {
	 res_node = FindNextNodePostorderSubtree(next_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 next_node = next_node->next;
	 }
      parent_node = parent_node->parent;
      if (parent_node != NULL && Bim_IsOfSort(parent_node,name) == TRUE)
	 return(parent_node);
      }

   return(NULL);
}






/*****************************************************************************
 *                                                                           *
 * NAME      :  FindPreviousNodePostorderSubtree                             *
 *                                                                           *
 * PROCEDURE :	FindPreviousNodePostorderSubtree() sucht zu einem vorgegebenen*
 *              Namen rekursiv nach dem vorgehenden Knoten in Postorder.     *
 *		Es wird nur im Unterbaum gesucht.                            *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindPreviousNodePostorderSubtree() liefert den     *
 *			Pointer auf einen eventuell gefundenen Knoten.       *
 *			Bei erfolgloser suche wird NULL zurueckgegeben.      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindPreviousNodePostorderSubtree( MAX_NODE *max_node,
					    char     *name )
{
   MAX_NODE *last_node, *res_node;

#ifdef DEBUG
printf("FindPreviousNodePostorderSubtree()\n");
#endif

   if (max_node == NULL)
      return(NULL);

   if (Bim_IsOfSort(max_node,name) == TRUE)
      return(max_node);

   if (max_node->children != NULL)
      {
      last_node = max_node->children;
      while (last_node->next != NULL)
	 last_node = last_node->next;
	
      while(last_node != NULL)
	 {
	 res_node = FindPreviousNodePostorderSubtree(last_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 last_node = last_node->prev;
	 }
      }

   return(NULL);
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  FindPreviousNodePostorder                                    *
 *                                                                           *
 * PROCEDURE :	FindPreviousNodePostorder() sucht zu einem vorgegebenen Namen*
 *		nach dem vorhergehenden Knoten in Postorder.                 *
 *		Es werden auch uebergeordnete Knoten beruecksichtigt.        *
 * INPUT     :  MAX_NODE *max_node ist ein Pointer auf den ersten Knoten     *
 *			des Suchdurchlaufes.                                 *
 * 		char *name ist ein Pointer auf eine Zeichenkette, die den    *
 *			Namen des gesuchten Knoten enthaelt.                 *
 * OUTPUT    :	MAX_NODE *FindPreviousNodePostorder() liefert den Pointer auf*
 *			einen eventuell gefundenen Knoten. Bei erfolgloser   *
 *			Suche wird NULL zurueckgegeben.                      *
 *                                                                           *
 *****************************************************************************/

MAX_NODE *FindPreviousNodePostorder ( MAX_NODE *max_node,
		                      char     *name )
{
   MAX_NODE *res_node, *last_node, *parent_node, *prev_node;

#ifdef DEBUG
printf("FindPreviousNodePostorder()\n");
#endif

   if (max_node == NULL)
      return (NULL);

   if (max_node->children != NULL)
      {
      last_node = max_node->children;
      while (last_node->next != NULL)
	 last_node = last_node->next;
      
      while (last_node != NULL)
	 {
	 res_node = FindPreviousNodePostorderSubtree(last_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 last_node = last_node->prev;
	 }
      }

   parent_node = max_node;
   while (parent_node != NULL)
      {
      prev_node = parent_node->prev;
      while (prev_node != NULL)
	 {
	 res_node = FindPreviousNodePostorderSubtree(prev_node,name);
	 if (res_node != NULL)
	    return(res_node);
	 prev_node = prev_node->prev;
	 }
      parent_node = parent_node->parent;
      }

   return(NULL);
}




/*****************************************************************************
 *                                                                           *
 * NAME      : NodeCallback                                                  *
 *                                                                           *
 * PROCEDURE : NodeCallback() ist als Callback-Procedure zu jedem Baumknoten *
 *		eingehaengt. Sie uebernimmt die Reaktion auf die mittlere und *
 *		die rechte Maustaste.                                        *
 * INPUT     : Widget node ist das angeklickte Widget                        *
 *		XtPointer client_data ist ein Pointer auf den zugehoerigen   *
 *			Max-Knoten.                                          *
 *		XtPointer call_data gibt den Mausbutton an.                  *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void NodeCallback ( Widget    node,
		    XtPointer client_data,
		    XtPointer call_data )
{
#ifdef DEBUG
printf("NodeCallback()\n");
#endif

   switch((int) call_data)
      {
   case 2:
      /*
       * Mark / Unmark node
       */

      if (Marked((MAX_NODE *)client_data) == TRUE)
         UnmarkNode((MAX_NODE *)client_data);
      else
         MarkNode((MAX_NODE *)client_data);
      break;
   case 3:
      /*
       * Show / Hide subtree
       */

      if (HiddenTree((MAX_NODE *)client_data) == TRUE)
         ShowSubtree((MAX_NODE *)client_data);
      else
         HideSubtree((MAX_NODE *)client_data);
      break;
      }
}



/*****************************************************************************
 *                                                                           *
 * Funktionen zum Verwalten der X_INFO Struktur                              *
 *                                                                           *
 *****************************************************************************/



/*****************************************************************************
 *                                                                           *
 * NAME      : CreateX_INFO                                                  *
 *                                                                           *
 * PROCEDURE : CreateX_INFO() generiert eine neue X_INFO Struktur und belegt *
 *		sie mit Defaultwerten.                                       *
 * INPUT     :                                                               *
 * OUTPUT    : X_INFO *CreateX_INFO() liefert einen Pointer auf die neu      *
 *  			bereitgestellte X_INFO Struktur.                     *
 *                                                                           *
 *****************************************************************************/

X_INFO *CreateX_INFO ()
{
   X_INFO *xinfo = (X_INFO *) XtMalloc(sizeof(X_INFO));

#ifdef DEBUG
printf("CreateX_INFO()\n");
#endif

   xinfo->context 		= (Context *) NULL;
   xinfo->widget 		= (Widget) NULL;
   xinfo->hidden_tree 		= FALSE;
   xinfo->show_attributes 	= FALSE;
   xinfo->marked          	= FALSE;
   xinfo->attr_widget 		= (Widget) NULL;
   xinfo->attr_mask   		= (AttrMask *) NULL;

   return(xinfo);
}


/*****************************************************************************
 *                                                                           *
 * NAME      : CopyX_INFO                                                    *
 *                                                                           *
 * PROCEDURE : CopyX_INFO() kopiert den Inhalt einer X_INFO Struktur und     *
 *		allokiert den benoetigten Speicherbereich.                   *
 * INPUT     : X_INFO *xinfo ist ein Pointer auf die zu kopierende Struktur. *
 * OUTPUT    : X_INFO *CopyX_INFO() liefert einen Pointer auf die neu      *
 *  			bereitgestellte X_INFO Struktur.                     *
 *                                                                           *
 *****************************************************************************/

X_INFO *CopyX_INFO (X_INFO *xinfo)
{
   X_INFO *xinfo_new = (X_INFO *) XtMalloc(sizeof(X_INFO));

#ifdef DEBUG
printf("CopyX_INFO()\n");
#endif

   xinfo_new->context 		= (Context *) NULL;
   xinfo_new->widget 		= (Widget) NULL;
   xinfo_new->hidden_tree 	= xinfo->hidden_tree;
   xinfo_new->show_attributes 	= xinfo->show_attributes;
   xinfo_new->marked          	= xinfo->marked;
   xinfo_new->attr_widget 	= (Widget) NULL;

   if (xinfo->attr_mask != NULL)
      xinfo_new->attr_mask 	= CopyAttrMask(xinfo->attr_mask);
   else
      xinfo_new->attr_mask	= (AttrMask *) NULL;

   return(xinfo_new);
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  DestroyX_INFO                                                *
 *                                                                           *
 * PROCEDURE : DestroyX_INFO() zerstoert eine X_INFO Struktur.               *
 * INPUT     : X_INFO *xinfo ist ein Pointer auf die zu zerstoerende Struktur. *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void DestroyX_INFO (X_INFO *xinfo)
{
#ifdef DEBUG
printf("DestroyX_INFO()\n");
#endif

   if (xinfo->attr_mask != NULL)
      DestroyAttrMask(xinfo->attr_mask);

   XtFree((char *) xinfo);
}

/*****************************************************************************
 *                                                                           *
 * Hilfsfunktionen                                                           *
 *                                                                           *
 *****************************************************************************/



/*****************************************************************************
 *                                                                           *
 * NAME      :  GetActualAttrMask                                            *
 *                                                                           *
 * PROCEDURE : 	GetActualAttrMask() gibt die zu einem Kontext, der durch     *
 *		einen MAX Knoten angegeben wird, gehoerende Attributmaske    *
 * 		zurueck.                                                     *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen MAX Knoten im   *
 *			gewuenschten Kontext.                                *
 * OUTPUT    :  AttrMask *GetActualAttrMask() liefert einen Pointer auf      *
 *			die Attributmaske.                                   *
 *                                                                           *
 *****************************************************************************/

AttrMask *GetActualAttrMask (MAX_NODE *node)
{
#ifdef DEBUG
printf("GetActualAttrMask()\n");
#endif

   return(Context(node)->xcontext->attr_mask);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmanageViewport                                             *
 *                                                                           *
 * PROCEDURE : 	UnmanageViewport() sorgt dafuer, dass der Viewport nicht     *
 *		mehr gemanaged wird.                                         *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen MAX Knoten im   *
 *			Viewport.                                            *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmanageViewport ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("UnmanageViewport()\n");
#endif

   XtUnmapWidget(Context(max_node)->xcontext->viewport); 
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ManageViewport                                               *
 *                                                                           *
 * PROCEDURE : 	ManageViewport() sorgt dafuer, dass der Viewport wieder      *
 *		gemanaged wird.                                              *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen MAX Knoten im   *
 *			Viewport.                                            *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ManageViewport ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("ManageViewport()\n");
#endif

      XawTreeForceLayout(Context(max_node)->xcontext->tree);

      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkAllNodesFromRoot                                       *
 *                                                                           *
 * PROCEDURE : 	UnmarkAllNodesFromRoot() entfernt eventuell vorhandene       *
 *		Markierungen (ab Root des MAX_NODE)                          *
 *		von allen MAX Knoten.                                        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen beliebigen      *
 *			MAX Knoten des Baumes.                               *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkAllNodesFromRoot ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("UnmarkAllNodesFromRoot()\n");
#endif

   UnmarkAllNodes((MAX_NODE *) Context(max_node)->max_tree);
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  RaiseWindow                                                  *
 *                                                                           *
 * PROCEDURE : 	RaiseWindow() legt das Window, das zu angegebenem Knoten     *
		gehoert oben auf den Windowstack.                            *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen beliebigen      *
 *			MAX Knoten innerhalb des Fensters.                   *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void RaiseWindow( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("RaiseWindow()\n");
#endif

   XRaiseWindow(Context(max_node)->xcontext->display,
                XtWindow(Context(max_node)->xcontext->toplevel));
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CenterNode                                                   *
 *                                                                           *
 * PROCEDURE :  CenterNode() zentriert einen MAX Knoten in seinem Fenster.   *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu zentrierenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CenterNode( MAX_NODE *max_node )
{
   Dimension  h_length, v_length;
   Position n_xpos, n_ypos;
   Dimension n_width, n_height;
   Position win_xpos, win_ypos;

#ifdef DEBUG
printf("CenterNode()\n");
#endif

   if (Widget(max_node) == NULL)
      CreatePath(max_node);

   XtVaGetValues(
      Context(max_node)->xcontext->h_scrollbar,
      XtNlength, &h_length,
      NULL);

   XtVaGetValues(
      Context(max_node)->xcontext->v_scrollbar,
      XtNlength, &v_length,
      NULL);

   XtVaGetValues(
      Widget(max_node),
      XtNx, &n_xpos,
      XtNy, &n_ypos,
      XtNwidth, &n_width,
      XtNheight, &n_height,
      NULL);

   /*
    * Berechne Position innerhalb sichtbaren Bereichs 
    */

   win_xpos = (Position) (n_xpos + n_width/2) - h_length/2;
   win_ypos = (Position) (n_ypos + n_height/2) - v_length/2;

   XawViewportSetCoordinates(Context(max_node)->xcontext->viewport,
			     win_xpos,win_ypos);

   RaiseWindow(max_node);
}







/*****************************************************************************
 *                                                                           *
 * Funktionen des Knotenmenues                                               *
 *                                                                           *
 *****************************************************************************/




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowAttributes                                               *
 *                                                                           *
 * PROCEDURE :	ShowAttributes() bewirkt das Anzeigen der Attribute eines    *
 *		MAX Knotens.                                                 *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowAttributes ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("ShowAttributes()\n");
#endif

   if (AttrMask(max_node) == NULL)
      AttrMask(max_node) = CopyAttrMask(Context(max_node)->xcontext->attr_mask);

   ShowedAttributes(max_node) = TRUE;

   if (Widget(max_node) != NULL)
      {
      AttrWidget(max_node) = CreateAttrList(max_node,
				      Widget (max_node),
				      AttrMask(max_node));

      XtVaSetValues(
         Widget(max_node),
         XtNshowAttributes, TRUE,
         NULL);

      XawTreeForceLayout(XtParent(Widget(max_node)));
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideAttributes                                               *
 *                                                                           *
 * PROCEDURE : 	HideAttributes() bewirkt das Verstecken der Attribute eines  *
 *		MAX Knotens.                                                 *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideAttributes ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("HideAttributes()\n");
#endif

   ShowedAttributes(max_node) = FALSE;

   DestroyAttrMask(AttrMask(max_node));
   AttrMask(max_node) = NULL;

   if (Widget(max_node) != NULL)
      {
      XtVaSetValues(
         Widget(max_node),
         XtNshowAttributes, FALSE,
         NULL);

      XtDestroyWidget(AttrWidget(max_node));
      AttrWidget(max_node) = NULL;

      XawTreeForceLayout(XtParent(Widget(max_node)));
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkNode                                                     *
 *                                                                           *
 * PROCEDURE :  MarkNode() bewirkt das Markieren eines MAX Knotens.          *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkNode ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("MarkNode()\n");
#endif

   Marked(max_node) = TRUE;
   XtVaSetValues(
      Widget(max_node),
      XtNmarked, TRUE,
      NULL);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkSubtree                                                  *
 *                                                                           *
 * PROCEDURE :  MarkSubtree() bewirkt das Markieren eines MAX Unterbaumes.   *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaums.                        *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("MarkSubtree()\n");
#endif

   if (Marked(max_node) != TRUE)
      {
      Marked(max_node) = TRUE;
      if (Widget(max_node) != NULL)
         XtVaSetValues(Widget(max_node),XtNmarked,TRUE,NULL);
      }
   if (max_node->children != NULL)
       MarkAllNodes(max_node->children);
}



 
/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkShowedSubtree                                            *
 *                                                                           *
 * PROCEDURE :  MarkShowedSubtree() bewirkt das Markieren des sichtbaren     *
 *		Bereichs eines MAX Unterbaumes.                              *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaum.                         *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkShowedSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("MarkShowedSubtree()\n");
#endif

   if (Marked(max_node) != TRUE && Widget(max_node) != NULL)
      {
      Marked(max_node) = TRUE;
      XtVaSetValues(Widget(max_node),XtNmarked,TRUE,NULL);
      }
   if (max_node->children != NULL)
       MarkShowedNodes(max_node->children);
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkNode                                                   *
 *                                                                           *
 * PROCEDURE :	UnmarkNode() bewirkt das Entfernen der Markierung eines      *
 *		MAX Knotens.                                                 *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkNode ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("UnmarkNode()\n");
#endif

   Marked(max_node) = FALSE;
   XtVaSetValues(
      Widget(max_node),
      XtNmarked, FALSE,
      NULL);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkSubtree                                                *
 *                                                                           *
 * PROCEDURE :	UnmarkSubtree() bewirkt das Entfernen der Markierungen in    *
 *		einem MAX Unterbaum.                                         *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaums.                        *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("UnmarkSubtree()\n");
#endif

   if (Marked(max_node) == TRUE)
      {
      Marked(max_node) = FALSE;
      if (Widget(max_node) != NULL)
         XtVaSetValues(Widget(max_node),XtNmarked,FALSE,NULL);
      }
   if (max_node->children != NULL)
      UnmarkAllNodes(max_node->children);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkShowedSubtree                                          *
 *                                                                           *
 * PROCEDURE :	UnmarkShowedSubtree() bewirkt das Entfernen der Markierungen *
 		im sichtbaren Bereich eines MAX Unterbaums.                  *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Baum.                                            *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkShowedSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("UnmarkShowedSubtree()\n");
#endif

   if (Marked(max_node) == TRUE && Widget(max_node) != NULL)
      {
      Marked(max_node) = FALSE;
      XtVaSetValues(Widget(max_node),XtNmarked,FALSE,NULL);
      }
   if (max_node->children != NULL)
      UnmarkAllNodes(max_node->children);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowSubtree                                                  *
 *                                                                           *
 * PROCEDURE :	ShowSubtree() bewirkt das Auffalten des zu einem MAX Knoten  *
 *		gehoerenden Unterbaums.	                                     *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("ShowSubtree()\n");
#endif

   if (max_node->children == NULL)
      return;

   HiddenTree(max_node) = FALSE;
   XtVaSetValues(
      Widget(max_node),
      XtNhiddenTree, FALSE,
      NULL);

   XtUnmapWidget(Context(max_node)->xcontext->viewport); 

   CreateSubtree(max_node);

   XawTreeForceLayout(Context(max_node)->xcontext->tree);

   XtAppAddWorkProc(
      Context(max_node)->xcontext->app_context,
      BackgroundMapProcedure,
      (XtPointer) Context(max_node)->xcontext->viewport);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideSubtree                                                  *
 *                                                                           *
 * PROCEDURE : 	HideSubtree() bewirkt das Verschatten des zu einem MAX Knoten*
 *		gehoerenden Unterbaums.                                      *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideSubtree ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("HideSubtree()\n");
#endif

   if (max_node->children == NULL)
      return;

   HiddenTree(max_node) = TRUE;
   XtVaSetValues(
      Widget(max_node),
      XtNhiddenTree, TRUE,
      NULL);

   XtUnmapWidget(Context(max_node)->xcontext->viewport); 

   DestroySubtree(max_node);

   XawTreeForceLayout(Context(max_node)->xcontext->tree);

   XtAppAddWorkProc(
      Context(max_node)->xcontext->app_context,
      BackgroundMapProcedure,
      (XtPointer) Context(max_node)->xcontext->viewport);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkPath                                                     *
 *                                                                           *
 * PROCEDURE :	MarkPath() bewirkt das Markieren aller Knoten zwischen der   *
 *		Wurzel des MAX Baumes und dem angegebenen MAX Knoten.        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkPath ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("MarkPath()\n");
#endif

   while (akt_node != NULL)
      {
      if (Marked(akt_node) != TRUE)
	 {
	 Marked(akt_node) = TRUE;
	 if (Widget(akt_node) != NULL)
	    XtVaSetValues(Widget(akt_node),XtNmarked,TRUE,NULL);
         }
      akt_node = akt_node->parent;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkPath                                                   *
 *                                                                           *
 * PROCEDURE :	UnmarkPath() bewirkt das Loeschen der Markierungen an allen  *
 *		MAX Knoten zwischen der Wurzel des MAX Baumes und dem ange-  *
 *		gebenen MAX Knoten.                                          *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den zu bearbeitenden  *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkPath ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("MarkPath()\n");
#endif

   while (akt_node != NULL)
      {
      if (Marked(akt_node) == TRUE)
	 {
	 Marked(akt_node) = FALSE;
	 if (Widget(akt_node) != NULL)
	    XtVaSetValues(Widget(akt_node),XtNmarked,FALSE,NULL);
         }
      akt_node = akt_node->parent;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CopySubtree                                                  *
 *                                                                           *
 * PROCEDURE :	CopySubtree() kopiert den zu einem angegebenen MAX Knoten    *
 *		gehoerenden Unterbaum und Kontext, und zeigt diesen in einem *
 *		neuen Fenster an.                                            *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			kopierenden MAX Knoten.                              *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CopySubtree ( MAX_NODE *max_node )
{
   Context *context_new;

#ifdef DEBUG
printf("CopySubtree()\n");
#endif

   context_new = CopyContext(Context(max_node),max_node);

   CreateTreeViewport(context_new);

   XawTreeForceLayout(context_new->xcontext->tree);
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoFirstNodePreorder                                        *
 *                                                                           *
 * PROCEDURE :	GotoFirstNodePreorder() bewirkt einen Sprung zum ersten      *
 *		MAX Knoten mit gleichem Namen in Preorder. Dieser Knoten     *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoFirstNodePreorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoFirstNodePreorder()\n");
#endif

   res_node = FindNextNodePreorderSubtree(
		       (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoLastNodePreorder                                         *
 *                                                                           *
 * PROCEDURE :	GotoLastNodePreorder() bewirkt einen Sprung zum letzten      *
 *		MAX Knoten mit gleichem Namen in Preorder. Dieser Knoten     *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoLastNodePreorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoLastNodePreorder()\n");
#endif

   res_node = FindPreviousNodePreorderSubtree(
		             (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoNextNodePreorder                                         *
 *                                                                           *
 * PROCEDURE :	GotoNextNodePreorder() bewirkt einen Sprung zum naechsten    *
 *		MAX Knoten mit gleichem Namen in Preorder. Dieser Knoten     *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoNextNodePreorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node = NULL; 

#ifdef DEBUG
printf("GotoNextNodePreorder()\n");
#endif

   if ((res_node = FindNextNodePreorder(max_node,name)) != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport); 
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoPreviousNodePreorder                                     *
 *                                                                           *
 * PROCEDURE :	GotoPreviousNodePreorder() bewirkt einen Sprung zum vorgaen- *
 *		ger MAX Knoten mit gleichem Namen in Preorder. Dieser Knoten *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoPreviousNodePreorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node = NULL; 

#ifdef DEBUG
printf("GotoPreviousNodePreorder()\n");
#endif

   if ((res_node = FindPreviousNodePreorder(max_node,name)) != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport); 
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoFirstNodePostorder                                       *
 *                                                                           *
 * PROCEDURE :	GotoFirstNodePostorder() bewirkt einen Sprung zum ersten     *
 *		MAX Knoten mit gleichem Namen in Postorder. Dieser Knoten    *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoFirstNodePostorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoFirstNodePostorder()\n");
#endif

   res_node = FindNextNodePostorderSubtree(
		 (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoLastNodePostorder                                        *
 *                                                                           *
 * PROCEDURE :	GotoLastNodePostorder() bewirkt einen Sprung zum letzten     *
 *		MAX Knoten mit gleichem Namen in Postorder. Dieser Knoten    *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoLastNodePostorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoLastNodePostorder()\n");
#endif

   res_node = FindPreviousNodePostorderSubtree(
                  (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoNextNodePostorder                                        *
 *                                                                           *
 * PROCEDURE :	GotoNextNodePostorder() bewirkt einen Sprung zum naechsten   *
 *		MAX Knoten mit gleichem Namen in Postorder. Dieser Knoten    *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoNextNodePostorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node = NULL; 

#ifdef DEBUG
printf("GotoNextNodePostorder()\n");
#endif

   if ((res_node = FindNextNodePostorder(max_node,name)) != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoPreviousNodePostorder                                    *
 *                                                                           *
 * PROCEDURE :	GotoPreviousNodePostorder() bewirkt einen Sprung zum vorgaen-*
 *		ger MAX Knoten mit gleichem Namen in Postorder. Dieser Knoten*
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf den urspruenglichen   *
 *			MAX Knoten.                                          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoPreviousNodePostorder ( MAX_NODE *max_node )
{
   char     *name = max_node->node_info->name;
   MAX_NODE *res_node = NULL; 

#ifdef DEBUG
printf("GotoPreviousNodePostorder()\n");
#endif

   if ((res_node = FindPreviousNodePostorder(max_node,name)) != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport); 
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}





/*****************************************************************************
 *                                                                           *
 * Funktionen des Hauptmenues                                                *
 *                                                                           *
 *****************************************************************************/




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideSubtreeMarkedNodes                                       *
 *                                                                           *
 * PROCEDURE :  HideSubtreeMarkedNodes() bewirkt das Zusammenfalten aller    *
 *		an markierten MAX Knoten haengenden Unterbaeume. Es werden   *
 *		auch Unterbaeume in Unterbaeumen zusammengefaltet.           *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Baum.                              *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideSubtreeMarkedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("HideSubtreesMarkedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Marked(akt_node) == TRUE) &&
	  (HiddenTree(akt_node) == FALSE) &&
	  (akt_node->children != NULL))
         {
	 HiddenTree(akt_node) = TRUE;
	 if (Widget(akt_node) != NULL)
	    {
	    XtVaSetValues(Widget(akt_node),XtNhiddenTree,TRUE,NULL);
	    DestroySubtree(akt_node);
	    }
         }
      HideSubtreeMarkedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowSubtreeMarkedNodes                                       *
 *                                                                           *
 * PROCEDURE :	ShowSubtreeMarkedNodes() bewirkt das Anzeigen aller an       *
 *		markierten MAX Knoten haengenden Unterbaeume. Die Funktion   *
 *		wirkt auch auf markierte aber eventuell nicht sichtbare      *
 *		Knoten.                                                      *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaums.                        *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowSubtreeMarkedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("ShowSubtreesMarkedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Marked(akt_node) == TRUE) &&
	  (HiddenTree(akt_node) == TRUE) &&
	  (akt_node->children != NULL))
         {
	 HiddenTree(akt_node) = FALSE;
	 if (Widget(akt_node) != NULL)
	    {
	    XtVaSetValues(Widget(akt_node),XtNhiddenTree,FALSE,NULL);
	    CreateSubtree(akt_node);
	    }
         }
      ShowSubtreeMarkedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideSubtreeNamedNodes                                        *
 *                                                                           *
 * PROCEDURE :  HideSubtreeNamedNodes() bewirkt das Zusammenfalten aller an  *
 *		MAX Knoten mit bestimmten Namen haengenden Unterbaeume. Es   *
 *              werden auch Unterbaeume in Unterbaeumen zusammengefaltet.    *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaums.         *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideSubtreeNamedNodes ( MAX_NODE *max_node,
		             char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("HideSubtreesNamedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (HiddenTree(akt_node) == FALSE) &&
	  (akt_node->children != NULL))
         {
	 HiddenTree(akt_node) = TRUE;
	 if (Widget(akt_node) != NULL)
	    {
	    XtVaSetValues(Widget(akt_node),XtNhiddenTree,TRUE,NULL);
	    DestroySubtree(akt_node);
	    }
         }
      HideSubtreeNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowSubtreeNamedNodes                                        *
 *                                                                           *
 * PROCEDURE :  ShowSubtreeNamedNodes() bewirkt das Auffalten aller an       *
 *		MAX Knoten mit bestimmten Namen haengenden Unterbaeume. Es   *
 *              werden auch Unterbaeume in Unterbaeumen aufgefaltet.         *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu  *
 *			bearbeitenden MAX Knoten.            *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowSubtreeNamedNodes ( MAX_NODE *max_node,
			     char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("ShowNamedSubtrees()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (HiddenTree(akt_node) == TRUE) &&
	  (akt_node->children != NULL))
         {
	 HiddenTree(akt_node) = FALSE;
	 if (Widget(akt_node) != NULL)
	    {
	    XtVaSetValues(Widget(akt_node),XtNhiddenTree,FALSE,NULL);
	    CreateSubtree(akt_node);
	    }
         }
      ShowSubtreeNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkAllNodes                                                 *
 *                                                                           *
 * PROCEDURE :  MarkAllNodes() markiert alle Knoten in einem MAX Unterbaum.  *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.             *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkAllNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("MarkAllNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if (Marked(akt_node) != TRUE)
	 {
         Marked(akt_node) = TRUE;
         if (Widget(akt_node) != NULL)
            XtVaSetValues(Widget(akt_node),XtNmarked,TRUE,NULL);
         }
      if (akt_node->children != NULL)
	 MarkAllNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkShowedNodes                                              *
 *                                                                           *
 * PROCEDURE :  MarkShowedNodes() markiert alle auf dem Bildschirm sichtbaren*
 *		MAX Knoten.                                                  *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.          *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkShowedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("MarkShowedNodes()\n");
#endif

   while (akt_node != NULL && Widget(akt_node) != NULL)
      {
      if (Marked(akt_node) != TRUE)
	 {
         Marked(akt_node) = TRUE;
         XtVaSetValues(Widget(akt_node),XtNmarked,TRUE,NULL);
	 }
      if (akt_node->children != NULL)
	 MarkShowedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}



		    
/*****************************************************************************
 *                                                                           *
 * NAME      :  MarkNamedNodes                                               *
 *                                                                           *
 * PROCEDURE :  MarkNamedNodes() markiert alle mit einem bestimmten Namen    *
 *		benannten MAX Knoten.                                        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu *
 *			bearbeitenden MAX Unterbaumes.             *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void MarkNamedNodes ( MAX_NODE *max_node,
		       char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("MarkNamedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (Marked(akt_node) == FALSE))
         {
	 Marked(akt_node) = TRUE;
	 if (Widget(akt_node) != NULL)
	    XtVaSetValues(Widget(akt_node),XtNmarked,TRUE,NULL);
         }
      MarkNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkAllNodes                                               *
 *                                                                           *
 * PROCEDURE : 	UnmarkAllNodes() entfernt eventuell vorhandene Markierungen  *
 *		von allen MAX Knoten.                                        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkAllNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("UnmarkAllNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if (Marked(akt_node) == TRUE)
         {
	 Marked(akt_node) = FALSE;
	 if (Widget(akt_node) != NULL)
	    XtVaSetValues(Widget(akt_node),XtNmarked,FALSE,NULL);
         }
      if (akt_node->children != NULL)
         UnmarkAllNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkShowedNodes                                            *
 *                                                                           *
 * PROCEDURE : 	UnmarkShowedNodes() entfernt alle vorhandene Markierungen im *
 *		sichtbaren Bereich des Baumes.                               *
 *		von allen MAX Knoten.                                        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkShowedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("UnmarkShowedNodes()\n");
#endif

   while (akt_node != NULL && Widget(akt_node) != NULL)
      {
      if (Marked(akt_node) == TRUE)
         {
	 Marked(akt_node) = FALSE;
	 XtVaSetValues(Widget(akt_node),XtNmarked,FALSE,NULL);
         }
      UnmarkShowedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  UnmarkNamedNodes                                             *
 *                                                                           *
 * PROCEDURE :  UnmarkNamedNodes() entfernt Markierungen an allen mit einem  *
 *		bestimmten Namen benannten MAX Knoten.                       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void UnmarkNamedNodes ( MAX_NODE *max_node,
		        char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("UnmarkNamedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (Marked(akt_node) == TRUE))
         {
	 Marked(akt_node) = FALSE;
	 if (Widget(akt_node) != NULL)
	    XtVaSetValues(Widget(akt_node),XtNmarked,FALSE,NULL);
         }
      UnmarkNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideAttributesNamedNodes                                     *
 *                                                                           *
 * PROCEDURE :  HideAttributesNamedNodes() bewirkt das Verstecken der        *
 *		Attribute an allen mit einem bestimmten Namen bezeichneten   *
 *		MAX Knoten.                                                  *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideAttributesNamedNodes ( MAX_NODE *max_node,
			        char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("HideAttributesNamedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (ShowedAttributes(akt_node) == TRUE))
         {
	 HideAttributes(akt_node);
         }
      HideAttributesNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideAttributesMarkedNodes                                    *
 *                                                                           *
 * PROCEDURE :  HideAttributesMarkedNodes() bewirkt das Verstecken der       *
 *		Attribute an allen markierten MAX Knoten.                    *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideAttributesMarkedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("HideAttributesMarkedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Marked(akt_node) == TRUE) &&
	  (ShowedAttributes(akt_node) == TRUE))
         {
	 HideAttributes(akt_node);
         }
      HideAttributesMarkedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  HideAttributesAllNodes                                       *
 *                                                                           *
 * PROCEDURE :  HideAttributesAllNodes() bewirkt das Verstecken aller        *
 *		Attribute.                                                   *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void HideAttributesAllNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("HideAttributesAllNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if (ShowedAttributes(akt_node) == TRUE)
         {
	 HideAttributes(akt_node);
         }
      HideAttributesAllNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowAttributesNamedNodes                                     *
 *                                                                           *
 * PROCEDURE :  ShowAttributesNamedNodes() bewirkt das Anzeigen der          *
 *		Attribute an allen mit einem bestimmten Namen bezeichneten   *
 *		MAX Knoten.                                                  *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowAttributesNamedNodes ( MAX_NODE *max_node,
			        char     *name )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("ShowAttributesNamedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Bim_IsOfSort(akt_node,name) == TRUE) &&
	  (ShowedAttributes(akt_node) == FALSE))
         {
	 ShowAttributes(akt_node);
         }
      ShowAttributesNamedNodes(akt_node->children,name);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowAttributesMarkedNodes                                    *
 *                                                                           *
 * PROCEDURE :  ShowAttributesMarkedNodes() bewirkt das Anzeigen der         *
 *		Attribute an allen markierten MAX Knoten.                    *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowAttributesMarkedNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("ShowAttributesMarkedNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if ((Marked(akt_node) == TRUE) &&
	  (ShowedAttributes(akt_node) == FALSE))
         {
	 ShowAttributes(akt_node);
         }
      ShowAttributesMarkedNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  ShowAttributesAllNodes                                       *
 *                                                                           *
 * PROCEDURE :	ShowAttributesAllNodes() bewirkt das Anzeigen aller Attribu- *
 *		te in einem MAX Baum.                                        *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void ShowAttributesAllNodes ( MAX_NODE *max_node )
{
   MAX_NODE *akt_node = max_node;

#ifdef DEBUG
printf("ShowAttributesAllNodes()\n");
#endif

   while (akt_node != NULL)
      {
      if (ShowedAttributes(akt_node) == FALSE)
         {
	 ShowAttributes(akt_node);
         }
      ShowAttributesAllNodes(akt_node->children);
      akt_node = akt_node->next;
      }
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoFirstNamedNodePreorder                                   *
 *                                                                           *
 * PROCEDURE :	GotoFirstNamedNodePreorder() bewirkt einen Sprung zum ersten *
 *		MAX Knoten mit bestimmtem Namen in Preorder. Dieser Knoten   *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoFirstNamedNodePreorder ( MAX_NODE *max_node,
				  char     *name )
{
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoFirstNamedNodePreorder()\n");
#endif

   res_node = FindNextNodePreorderSubtree(
	                 (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoLastNamedNodePreorder                                    *
 *                                                                           *
 * PROCEDURE :	GotoLastNamedNodePreorder() bewirkt einen Sprung zum letzten *
 *		MAX Knoten mit bestimmtem Namen in Preorder. Dieser Knoten   *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoLastNamedNodePreorder ( MAX_NODE *max_node,
				  char     *name )
{
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoLastNamedNodePreorder()\n");
#endif

   res_node = FindPreviousNodePreorderSubtree(
		     (MAX_NODE *) Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoFirstNamedNodePostorder                                  *
 *                                                                           *
 * PROCEDURE :	GotoFirstNamedNodePostorder() bewirkt einen Sprung zum ersten*
 *		MAX Knoten mit bestimmtem Namen in Postorder. Dieser Knoten  *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoFirstNamedNodePostorder ( MAX_NODE *max_node,
			       	   char     *name )
{
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoFirstNamedNodePostorder()\n");
#endif

   res_node = FindNextNodePostorderSubtree(
		   (MAX_NODE*)Context(max_node)->max_tree, name);
   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  GotoLastNamedNodePostorder                                   *
 *                                                                           *
 * PROCEDURE :	GotoLastNamedNodePostorder() bewirkt einen Sprung zum letzten*
 *		MAX Knoten mit bestimmtem Namen in Postorder. Dieser Knoten  *
 *		wird in der Mitte des Fensters zentriert und markiert.       *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 *		char *name ist ein Pointer auf die Zeichenkette mit dem      *
 *			MAX Knotennamen.                                     *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void GotoLastNamedNodePostorder ( MAX_NODE *max_node,
				  char     *name )
{
   MAX_NODE *res_node;

#ifdef DEBUG
printf("GotoLastNamedNodePostorder()\n");
#endif

   res_node = FindPreviousNodePostorderSubtree(
			      (MAX_NODE *) Context(max_node)->max_tree, name);

   if (res_node != NULL)
      {
      XtUnmapWidget(Context(max_node)->xcontext->viewport);
      CreatePath(res_node);
      XawTreeForceLayout(Context(max_node)->xcontext->tree);
      XtAppAddWorkProc(
         Context(max_node)->xcontext->app_context,
         BackgroundMapProcedure,
         (XtPointer) Context(max_node)->xcontext->viewport);
      CenterNode(res_node);
      MarkNode(res_node);
      }
}




/*****************************************************************************
 *                                                                           *
 * NAME      :  CopyTree                                                     *
 *                                                                           *
 * PROCEDURE :	CopyTree() kopiert den zu einem angegebenen MAX Knoten       *
 *		gehoerenden Gesamtbaum und Kontext, und zeigt diesen in      *
 *		einem neuen Fenster an.                                      *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf die Wurzel des zu     *
 *			bearbeitenden MAX Unterbaumes.                       *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CopyTree ( MAX_NODE *max_node )
{
   Context *context_new;

#ifdef DEBUG
printf("CopyTree()\n");
#endif

   context_new = CopyContext(Context(max_node),
			     (MAX_NODE *) Context(max_node)->max_tree);

   CreateTreeViewport(context_new);
}





/*****************************************************************************
 *                                                                           *
 * NAME      :  CloseWindow                                                  *
 *                                                                           *
 * PROCEDURE :  CloseWindow() schliesst das zu einem MAX Knoten gehoerende   *
 *		Fenster.                                                     *
 * INPUT     :	MAX_NODE *max_node ist ein Pointer auf einen beliebigen      *
 *			MAX Knoten innerhalb des zu schliessenden Fensters.  *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CloseWindow ( MAX_NODE *max_node )
{
#ifdef DEBUG
printf("CloseWindow()\n");
#endif 

   /*
    * Aushaengen des Kontextes aus der Kontexthierarchie
    */

   if (Context(max_node)->prev != NULL)
      (Context(max_node)->prev)->next = Context(max_node)->next;
   if (Context(max_node)->next != NULL)
      (Context(max_node)->next)->prev = Context(max_node)->prev;

   if (Context(max_node)->prev == NULL && Context(max_node)->parent != NULL)
      (Context(max_node)->parent)->children = Context(max_node)->next;

   if (Context(max_node)->children != NULL)
      DestroyContext(Context(max_node)->children);

   XtDestroyWidget(Context(max_node)->xcontext->toplevel);

   DestroyXCONTEXT(Context(max_node)->xcontext);

   XtFree((char *) Context(max_node));

   if (Context(max_node)->parent == NULL)
      AppMainLoop = FALSE;
}





/*****************************************************************************
 *                                                                           *
 * NAME      :                                                               *
 * PROCEDURE :                                                               *
 * INPUT     :                                                               *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

/******************************************************************************
 *
 * Mainfunktion 
 *
 *****************************************************************************/




/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateMainShell                                              *
 *                                                                           *
 * PROCEDURE :                                                               *
 * INPUT     :	MAX_NODE *max_tree ist ein Pointer auf den darzustellenden   *
 *			MAX Baum.                                            *
 *		int argc ist der von main() bereitgestellte Argumentcounter. *
 *		char **argv ist der von main() bereitgestellte Argument-     *
 *			vektor.                                              *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreateMainShell( MAX_NODE *max_tree,
                      int      argc,
                      char     **argv )
{
   Context *context = (Context *) XtMalloc (sizeof(Context));
   XEvent event;

#ifdef DEBUG
printf("CreateMainShell()\n");
#endif

   MakeCleanTree(max_tree);
   UpdateMaxTree(max_tree,context);

   context->xcontext = CreateXCONTEXT(argc,argv);

   context->max_tree = (void *) max_tree;
   context->incarnation = 0;
   context->number = 0;
   context->children = NULL;
   context->next = NULL;
   context->prev = NULL;
   context->parent = NULL;

   CreateTreeViewport(context);

   /*
    * XtAppMainLoop
    */

   while (AppMainLoop == TRUE)
      {
      XtAppNextEvent(context->xcontext->app_context, &event);
      XtDispatchEvent(&event);
      }


#ifdef DEBUG
printf("Exit CreateMainShell()\n");
#endif
}



/*****************************************************************************
 *                                                                           *
 * NAME      :  CreateNewShell                                               *
 *                                                                           *
 * PROCEDURE :	CreateNewShell oeffnet eine neue Shell fuer einen MAX-Tree.  *
 *		Dieser MAX-Tree muss keinen eigenen Kontext besitzen.        *
 * INPUT     :	MAX_NODE *max_tree ist ein Pointer auf die Wurzel des        *
 *			darzustellenden MAX Baumes.                          *
 *		MAX_NODE *max_node ist ein Pointer auf den MAX-Knoten, dessen*
 *			Kontext kopiert werden soll.                         *
 * OUTPUT    :                                                               *
 *                                                                           *
 *****************************************************************************/

void CreateNewShell ( MAX_NODE *max_tree, MAX_NODE *max_node )
{
   Context *context_new;

#ifdef DEBUG
printf("CreateNewShell()\n");
#endif

   context_new = CopyContext(Context(max_node),max_tree);

   CreateTreeViewport(context_new);

   XawTreeForceLayout(context_new->xcontext->tree);
}

