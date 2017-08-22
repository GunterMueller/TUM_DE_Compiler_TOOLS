
#include <string.h>
#include <stdio.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Label.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/MenuButton.h>
#include <X11/Xaw/SimpleMenu.h>
#include <X11/Xaw/SmeBSB.h>
#include <X11/Xaw/SmeLine.h>
#include <X11/Xaw/List.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/Toggle.h>

#include "bim_attr.h"
#include "bim_attrmask.h"
#include "bim_node.h"
#include "bim_tprint.h"

static char buf[1000];
char *ltoa(long l)
{
sprintf(buf,"%ld",l);
return (buf);
}

Widget node_menu;
Cardinal current_global_index;
MAX_NODE * current_node_id;

String * attribute_list;

/* Liste der Titel der Menues in der Menueleiste. Werden andere Titel gewuenscht,
   bitte hier aendern:  */

String menu_list[] = 
   {"Attributes",
	"Find",
	"Mark/Unmark",
	"Hide/Show",
	"Copy",
	"Quit"};

/*************************************************************************
 * Liste der Eintraege fuer die globalen Menues:                         *
 * (Enthaelt Information, ob bei Selektierung eines bestimmten Eintrags  *
 * ein Fenster zur Auswahl eines Sortennamens erscheinen soll sowie eine *
 * Information, zu welchem Menue der Eintrag gehoert.)                   *
 *************************************************************************/

static Glmentries globalm[] =
   {{"choice1","Hide marked",False,3},
    {"choice2","Hide on name",True,3},
    {"choice3","Show marked",False,3},
    {"choice4","Show on name",True,3},
    {"choice5","Mark on name",True,2},
    {"choice6","Unmark on name",True,2},
    {"choice7","Mark all",False,2},
    {"choice8","Unmark all",False,2},
    {"choice9","Mark showed",False,2},
    {"choice10","Unmark showed",False,2},
    {"choice11","Hide Attr.(marked)",False,0},
    {"choice12","Hide Attr.(name)",True,0},
    {"choice13","Hide Attr.(all)",False,0},
    {"choice14","Show Attr.(marked)",False,0},
    {"choice15","Show Attr.(name)",True,0},
    {"choice16","Show Attr.(all)",False,0},
    {"choice17","Attribute Mask",False,0},
    {"choice18","Goto First Named Node (Preord.)",True,1},
    {"choice19","Goto Last Named Node  (Preord.)",True,1},
    {"choice20","Goto First Named Node (Postord.)",True,1},
    {"choice21","Goto Last Named Node  (Postord.)",True,1},
    {"choice22","Copy Tree",False,4},
    {"choice23","Close Window",False,5}};

/************************************************
 * Liste der Eintraege fuer das Knoten-Menue:   *
 * (Enthaelt Information, ob nach einem Eintrag *
 *  eine Trennlinie eingezogen werden soll).    *
 ************************************************/

static Nomentries nodem[] =
   {{"choice1","Show/Hide Attributes",True},
    {"choice2","Mark/Unmark Node",True},
    {"choice3","Show/Hide Subtree",True},
    {"choice4","Mark Subtree",False},
    {"choice5","Unmark Subtree",False},
    {"choice6","Mark Showed Subtree",False},
    {"choice7","Unmark Showed Subtree",False},
    {"choice8","Mark Path",False},
    {"choice9","Unmark Path",True},
    {"choice10","Copy Subtree",True},
    {"choice11","Goto first Node (Preorder)",False},
    {"choice12","Goto last  Node (Preorder)",False},
    {"choice13","Goto next  Node (Preorder)",False},
    {"choice14","Goto previous Node (Preorder)",True},
    {"choice15","Goto first Node (Postorder)",False},
    {"choice16","Goto last  Node (Postorder)",False},
    {"choice17","Goto next  Node (Postorder)",False},
    {"choice18","Goto previous Node (Postorder)",False}};

/*****************************************************************
 * Translationtable zur Erweiterung der Default-Translationtable *
 * des Command-Widgets                                           *
 *****************************************************************/

String translationtable = 
   "<Btn1Down> : set() notifyNode(4) XawPositionSimpleMenu(node_menu) XtMenuPopup(node_menu)";

/***********************************************************************************
 * NAME: ConnectMenuToNode							   *
 *										   *
 * PROCEDURE: Versieht die Command-Buttons mit der Translationtable, die notwendig *
 *   ist, um beim Anklicken eines Buttons das Knoten-Menue aufzupoppen und es      *
 *   richtig handzuhaben. Ausserdem wird dem Node-Widget eine Callback-Funktion    *
 *   angehaengt, die fuer die Speicherung der Id des zuletzt angeklickten Knotens  *
 *   in einer globalen Variable sorgt.						   *
 * INPUT:									   *
 *   MAX_NODE * node: Max-Node-Id des betreffenden Knotens			   *
 *   Widget w:        Node-Widget-Id des betreffenden Knotens			   *
 * OUTPUT: --									   *
 ***********************************************************************************/

void ConnectMenuToNode (MAX_NODE * node, Widget w)

{
  Widget button;

/* Auslesen der zum Node-Widget gehoerigen Button-Id */

  XtVaGetValues(w,XtNcommandButton,&button,NULL);

/* Anhaengen der Translationtable */

  XtOverrideTranslations(button,XtParseTranslationTable(translationtable));

/* Anhaengen einer Callback-Funktion, die bei Anklicken des Buttons seine Id 
   in einer globalen Variable speichert */

  XtAddCallback(w,XtNcallback,GetNodeId,(XtPointer) node);
}

/*************************************************************************************
 * NAME: CopyAttributeTreeCallback						     *
 *										     *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn der Such-Button, der sich *
 *   neben einem angezeigten Tree-Attribut befindet, angeklickt wird. Kopiert den    *
 *   Unterbaum, dessen Wurzel der Wert dieses Tree-Attributs ist.		     *
 * INPUT: 									     *
 *   Widget w:              Id des Such-Buttons, der angeklickt wurde.		     *
 *   XtPointer client_data: MAX_NODE-Id des Wurzelknotens des anzuzeigenden Baums.   *
 *   XtPointer call_data:   wird hier nicht benoetigt.				     *
 * OUTPUT: --									     *
 *************************************************************************************/

void CopyAttributeTreeCallback (Widget w, XtPointer client_data, XtPointer call_data)
{
  CallbackNodes * two_nodes;

  two_nodes = (CallbackNodes *) client_data;

/* Erzeugung eines neuen Windows, das den Unterbaum enthaelt, auf den das Attribut verweist */

  CreateNewShell(two_nodes->first_node,two_nodes->second_node);
}

/*****************************************************************************
 * NAME: CenterNodeCallback						     *
 *									     *
 * PROCEDURE: Callback-Funktion, die durch Anklicken des Such-Buttons bei    *
 *   Attributen vom Typ MAX_NODE aufgerufen wird. Sie sorgt dafuer, dass     *
 *   der Knoten, auf den durch das Attribut verwiesen wird, markiert und     *
 *   und in der Mitte des Fensters positioniert wird. Zuvor werden alle bis- *
 *   her bestehenden Markierungen rueckgaengig gemacht.			     *
 * INPUT:								     *
 *   Widget w:              Id des Buttons, an den CenterNodeCallback        *
 *                          angehaengt wird.				     *
 *   XtPointer client_data: Max-Node-Id des Knotens, auf den verwiesen wird. *
 *   XtPointer call_data:   wird hier nicht benoetigt.			     *
 * OUTPUT: --								     *
 *****************************************************************************/

void CenterNodeCallback (Widget w, XtPointer client_data, XtPointer call_data)

{
  MAX_NODE * node_to_center;

  node_to_center = (MAX_NODE *) client_data;

/* Viewport voruebergehend unsichtbar machen */

  UnmanageViewport(node_to_center);

/* Alle bisher markierten Knoten entmarkieren */

  UnmarkAllNodesFromRoot(node_to_center);
/* Betreffenden Knoten in die Mitte ruecken */
  CenterNode(node_to_center);
/* Betreffenden Knoten markieren */
  MarkNode(node_to_center);

/* Viewport wieder sichtbar machen */

  ManageViewport(node_to_center);
}

/*********************************************************************************
 * NAME: IsMasked								 *
 *										 *
 * PROCEDURE: Untersucht, ob ein bestimmtes Attribut in der fuer es gueltigen	 *
 *   Attributmaske maskiert ist oder nicht und gibt den entsprechende Wahrheits- *
 *   wert zurueck.								 *
 * INPUT:									 *
 *   String name:            Name des zu ueberpruefenden Attributs.		 *
 *   AttrMask * actual_mask: die dazugehoerige Attributmaske.			 *
 * OUTPUT:									 *
 *   - True, falls das Attribut maskiert ist.					 *
 *   - False, falls das Attribut nicht maskiert ist.				 *
 *********************************************************************************/

Boolean IsMasked (String name, AttrMask * actual_mask)

{
  Boolean result = False;
  int cmp_result;
  Cardinal i,attr_list_length;

/* Anzahl aller Attribute einlesen */

  attr_list_length = Bim_NumberOfAttributes();

/* Schleife, die alle Indizes der Attribumaske durchlaeuft */

  for (i = 0; i < attr_list_length; i++)
  {
/* zu untersuchenden Attributnamen mit dem Namen des Attributs vom Index i vergleichen */

    cmp_result = strcmp(name,attribute_list[i]);

/* falls Attribut maskiert, Ergebnisvariable auf True setzen */

    if (cmp_result == 0 && (actual_mask + i)->masked)

    result = True;
  }

  return(result);
}

/**********************************************************************************
 * NAME: CreateAttrList								  *
 *										  *
 * PROCEDURE: Diese Funktion wird aufgerufen, wenn an einem Knoten die Liste der  *
 *   Attribute angezeigt werden soll. Dann wird die Attributliste als Label-	  *
 *   Widget aus den einzelnen Teilstrings aufgebaut. Neben die Attribute werden   *
 *   ggf. Command-Widgets, die Search-Buttons, plaziert. Dies ist dann der Fall,  *
 *   wenn das betreffende Attribut einen Verweis auf einen Knoten oder einen	  *
 *   Unterbaum darstellt. Das Label-Widget mit der Attributliste sowie die evtl.  *
 *   vorhandenen Search-Buttons werden in ein Form-Widget gepackt, das als Child- *
 *   Widget an das Node-Widget, zu der die Attributliste gehoert, gehaengt wird.  *
 *   Diese Funktion beruecksichtigt dabei, ob bestimmte Attribute maskiert sind.  *
 *   Dazu steht als Eingabe die aktuell gueltige Attributmaske zur Verfuegung.	  *
 * INPUT:									  *
 *   MAX_NODE * node: MAX_NODE-Information des betreffenden Knotens. Hierdurch	  *
 *                    kann auf alle Attributinformationen dieses Knotens zuge-	  *
 *                    griffen werden.						  *
 *   Widget parent:   Id des Node-Widgets, an das die Liste angehaengt wird.	  *
 *   AttrMask * actual_mask: Zeiger auf die im aktuellen Window gueltige Attri-	  *
 *                           butmaske.						  *
 * OUTPUT:									  *
 *   Widget: Id des Form-Widgets, das die Attributliste und die Search-Buttons	  *	
 *           enthaelt.								  *
 **********************************************************************************/

Widget CreateAttrList ( MAX_NODE * node, Widget parent, AttrMask * actual_mask)

{
  Widget attr_shell,attr_form,label;
  Widget * search_button;
  int na,i,j,k,m1,m2,m3,tm1,tm2,noma,nosb;
  Dimension label_height,button_height;
  String attr_line;
  CallbackNodes * two_nodes = (CallbackNodes *) XtMalloc(sizeof(CallbackNodes));

/* Anzahl der Attribute des betreffenden Knoten einlesen */

  na = node->node_info->no_of_attributes;

/* Laenge des benoetigten Strings berechnen */

  m1 = m2 = m3 = nosb = 0;

  /* Schleife durch alle Attribute dieses Knotens: */
  for (i = 0; i < na; i++)
  {

    /* Nur unmaskierte Attribute werden beruecksichtigt */
    if (!IsMasked((node->node_info->attributes + i)->name,actual_mask))
    {

      /* Berechnung der Laenge des laengsten Attributnamens: */
      tm1 = strlen((node->node_info->attributes + i)->name);
      if (tm1 > m1)
      m1 = tm1;

      /* Berechnung der Laenge des laengsten Attributtyps: */
      tm2 = strlen((node->node_info->attributes + i)->type);
      if (tm2 > m2)
      m2 = tm2;

      /* Berechnung der Laenge des laengsten Attributwerts
         mit Fallunterscheidung nach Attributtypen: */

      /* Typ 'Int' oder 'Bool': */
      if (((node->node_info->attributes + i)->type[0] == 'I'
          || ((node->node_info->attributes + i)->type[0] == 'B'))
          && strlen((String) ltoa((node->node_info->attributes + i)->attr_value)) > m3)
        m3 = strlen((String) ltoa((node->node_info->attributes + i)->attr_value));

      /* Typ 'String': */
      if ((node->node_info->attributes + i)->type[0] == 'S' 
          && strlen((String) (node->node_info->attributes + i)->attr_value) > m3)
        m3 = strlen((String) (node->node_info->attributes + i)->attr_value);

      /* Typ 'MAX_NODE','Point' oder 'Term': */
      if ((((node->node_info->attributes + i)->type[0] == 'M')
          || ((node->node_info->attributes + i)->type[0] == 'T')
          || ((node->node_info->attributes + i)->type[0] == 'P'))
          && ((node->node_info->attributes + i)->attr_value == 0 && m3 < 4))
        m3 = 4;

      /* Berechnung der Anzahl der benoetigten Such-Buttons */

      if ((((node->node_info->attributes + i)->type[0] == 'M')
          || ((node->node_info->attributes + i)->type[0] == 'T')
          || ((node->node_info->attributes + i)->type[0] == 'P'))
          && ((node->node_info->attributes + i)->attr_value != 0 && m3 < 4))
        nosb++;
    }
  }
/* Ende der Berechnung der Laenge des benoetigten Strings. In m1 steht jetzt die
   Laenge des laengsten Attributnamens, in m2 die Laenge des laengsten Attributtyps,
   in m3 die Laenge des laengsten Attributwerts. Die Laenge des Strings, der spaeter
   im Label-Widget erscheint, ergibt sich nun zu (m1+m2+m3+) * (Anzahl der Attribute
   des Knotens). Zusaetzlich muessen bei der Stringlaenge aber noch Blanks fuer
   Zwischenraeume sowie Zeilenumbrueche beruecksichtigt werden. 
   Ausser der benoetigten Stringlaenge wurde soeben noch die Anzahl der benoetigten
   Such-Buttons (in Variable nosb) berechnet. */

/* Speicherzuweisung fuer die Such-Button-Widgets: */

  search_button = (Widget *) XtMalloc(nosb * sizeof(Widget));

/* Erzeugung des Form-Widgets, in dem das Label-Widget sowie die Such-Buttons ange-
   ordnet werden */

  attr_form = XtVaCreateWidget("attr_form",formWidgetClass,parent,
				       NULL);

/* Speicherreservierung fuer den Ausgabestring gemaess der zuvor berechneten Laenge: */

  attr_line = (String) XtMalloc(((na * (m1+m2+m3+5)) + 1) * sizeof(char));

/* Verkettung der Stringkomponenten zum Ausgabestring: */

  strcpy(attr_line,""); /* Initialisierung des Ausgabestrings */
  noma = 0; /* Zaehlvariable fuer maskierte Attribute */
  k = 0; /* Zaehlvariable fuer Index des naechsten Such-Buttons */

  /* Schleife durch alle Attribute dieses Knotens: */
  for (j = 0; j < na; j++)
  {
    /* Nur unmaskierte Attribute werden beruecksichtigt */
    if (IsMasked((node->node_info->attributes + j)->name,actual_mask))
    {
      noma++;
    }
    else
    {
      /* Anhaengen des Attributnamens an Ausgabestring */
      strcat(attr_line,(node->node_info->attributes + j)->name);

      /* falls dieser Name kuerzer als die maximale reservierte Lange ist,
         werden Leerzeichen angehaengt: */
      for (i = 0; i < ((m1 - strlen((node->node_info->attributes + j)->name)) + 2); i++)
      strcat(attr_line," ");

      /* Anhaengen des Attributtyps */
      strcat(attr_line,(node->node_info->attributes + j)->type);

      /* falls dieser Typname kuerzer als die maximale reservierte Lange ist,
         werden Leerzeichen angehaengt: */
      for (i = 0; i < ((m2 - strlen((node->node_info->attributes + j)->type)) + 2); i++)
      strcat(attr_line," ");

      /* Anhaengen des Attributwerts (mit Fallunterscheidung nach Typ) */

      /* Typ 'Int' oder 'Bool' */
      if ((node->node_info->attributes + j)->type[0] == 'I' 
          || (node->node_info->attributes + j)->type[0] == 'B')
          {
           /* Unwandkung des Werts in String notwendig */
           strcat(attr_line,(String) ltoa((node->node_info->attributes + j)->attr_value));

           /* falls der String dieses Werts kuerzer als die maximale reservierte Lange ist,
              werden Leerzeichen angehaengt */
           for (i = 0; i < (m3 - strlen((String) ltoa((node->node_info->attributes + j)->attr_value))); i++)
           strcat(attr_line," ");
           strcat(attr_line,"\n");
          }

      /* Typ 'MAX_NODE','Term' oder 'Point' */
      if (((node->node_info->attributes + j)->type[0] == 'M')
         || ((node->node_info->attributes + j)->type[0] == 'T')
         || ((node->node_info->attributes + j)->type[0] == 'P'))
          {
           /* wenn der Wert eine Adresse ist, wird nichts angehaengt */
           if ((node->node_info->attributes + j)->attr_value != 0)
             {
              /* Leerzeichen auffuellen */
              for (i = 0; i < m3; i++)
              strcat(attr_line," ");
              strcat(attr_line,"\n");
             }

           /* wenn der Wert NULL ist, wird dieser als String angehaengt */
           else
             {
              /* Leerzeichen auffuellen */
              strcat(attr_line,"NIL "); /* War mal "NULL", geaendert von Andy*/
              for (i = 0; i < m3 - 4; i++)
              strcat(attr_line," ");
              strcat(attr_line,"\n");
             }
          }

      /* Typ 'String': */
      if ((node->node_info->attributes + j)->type[0] == 'S')
          {
           /* Wert kann ohne Umwandlung angehaengt werden */
           strcat(attr_line,(String) (node->node_info->attributes + j)->attr_value);
           /* Leerzeichen auffuellen */
           for (i = 0; i < (m3 - strlen((String) (node->node_info->attributes + j)->attr_value)); i++)
           strcat(attr_line," ");
           strcat(attr_line,"\n");
          }

      /* falls unbekannter Attributtyp auftritt, steht nichts beim Wert : */
      if ((node->node_info->attributes + j)->type[0] != 'S' 
          && (node->node_info->attributes + j)->type[0] != 'M' 
          && (node->node_info->attributes + j)->type[0] != 'I' 
          && (node->node_info->attributes + j)->type[0] != 'B'
          && (node->node_info->attributes + j)->type[0] != 'T'
          && (node->node_info->attributes + j)->type[0] != 'P')
          {
           for (i = 0; i < m3; i++)
              strcat(attr_line," ");
              strcat(attr_line,"\n");
          }
/* Ende der Verkettung dieses Attributs mit dem Ausgabestring */

/* Erzeugung und Plazierung der Such-Buttons: */
    
      /* Such-Button nur bei Typ 'MAX_NODE','Term' oder 'Point' vorhanden */
      if ((((node->node_info->attributes + j)->type[0] == 'M')
           || ((node->node_info->attributes + j)->type[0] == 'T')
           || ((node->node_info->attributes + j)->type[0] == 'P')) 
           && ((node->node_info->attributes + j)->attr_value != 0))
      {
        search_button[k] = XtVaCreateManagedWidget("button",commandWidgetClass,attr_form,
					            XtNlabel,"X",
						    XtNheight,14,
					            XtNvertDistance,(j-noma)*14+4,
					            NULL);

        if ((node->node_info->attributes + j)->type[0] == 'M' ||
            (node->node_info->attributes + j)->type[0] == 'P')


        /* Anhaengen der Callback-Funktion zur Zentrierung und Markierung des Knotens: */
        XtAddCallback(search_button[k],XtNcallback,CenterNodeCallback,
                      (XtPointer) (node->node_info->attributes + j)->attr_value);

        else
        {
	  two_nodes = (CallbackNodes *) XtMalloc(sizeof(CallbackNodes));
          two_nodes->first_node = (MAX_NODE *) (node->node_info->attributes + j)->attr_value;

          two_nodes->second_node = node;

          /* Anhaengen der Callback-Funktion zur Erzeugung des neuen Windows: */
          XtAddCallback(search_button[k],XtNcallback,CopyAttributeTreeCallback,
		        (XtPointer) two_nodes);
        }

        k++;
      }
    }
  }

  strcat(attr_line,"\0");
/* In attr_line steht nun der Ausgabestring zur Verfuegung */

/* Erzeugung des Label-Widgets: */

/* falls der Knoten keine Attribute besitzt, enthaelt der Ausgabestring nur die
   Mitteilung 'No Attributes!': */
  if (na == 0)

  label = XtVaCreateManagedWidget("no_attrs",labelWidgetClass,attr_form,
				    /*   XtNlabel,"No Attributes!", */
				       XtNborderWidth,0,
				       NULL);

/* falls alle Attribute maskiert sind, enthaelt der Ausgabestring nur die
   Mitteilung 'Attributes Masked!': */
  else if (na == noma)

  label = XtVaCreateManagedWidget("hidden_label",labelWidgetClass,attr_form,
				/*   XtNlabel,"Attributes Masked!", */
				   XtNborderWidth,0,
				   NULL);

/* falls unmaskierte Attribute vorhanden sind, wird im Label-Widget der 
   zuvor zusammengekettete Ausgabestring attr_line praesentiert */
  else

  {
    label = XtVaCreateManagedWidget("attr_label",labelWidgetClass,attr_form,
                                     XtNlabel,attr_line,
				     XtNborderWidth,0,
				     NULL);
  }

/* Freigabe des Speicherbereichs fuer den Ausgabestring: */
  XtFree(attr_line);


/* Positionierung der Such-Buttons rechts vom Label-Widget (die Angabe dieser
   Ressource ist erst jetzt moeglich, da bei Erzeugung der Such-Buttons die
   Id des Label-Widgets nicht zur Verfuegung stand): */
  for (i = 0; i < k; i++)
  XtVaSetValues(search_button[i],XtNfromHoriz,label,NULL);

/* Managen des Form-Widgets */
  XtManageChild(attr_form);

  return attr_form;
}

/*************************************************************************************
 * NAME: GlobalMenuNotifyWithName						     *
 *										     *
 * PROCEDURE: Callback-Funktion, die nach Auswahl eines bestimmten Sortennamens auf- *
 *   gerufen wird, nachdem zuvor ein Eintrag eines globalen Menues, der zusaetzlich  *
 *   einen Sortennamen benoetigt, selektiert wurde. Die globale Variable	     *
 *   current_global_index enthaelt dabei den Index des zuletzt selektierten Eintrags *
 *   bzgl. der Liste 'globalm'. Gemaess diesem Index wird die entsprechende Funktion *
 *   mit dem zuvor ausgewaehlten Sortennamen aufgerufen.			     *
 * INPUT:									     *
 *   Widget w:      Id des List-Widgets, aus dem der Sortenname ausgewaehlt wird     *
 *   XtPointer									     *
 *     client_data: Zeiger auf die Knoten-Information der Wurzel des entsprechenden  *
 *                  Fensters.							     *
 *   XtPointer									     *
 *     call_data:   Zeiger auf eine Struktur, die die Informationen ueber den selek- *
 *                  tierten Sortennamen enthaelt.				     *
 * OUTPUT: -- 									     *
 *************************************************************************************/


void GlobalMenuNotifyWithName (Widget w, XtPointer client_data, XtPointer call_data)

{
  CallbackStruct * node_and_widget;
  XawListReturnStruct * list_item;

  node_and_widget = (CallbackStruct *) client_data;
  list_item = (XawListReturnStruct *) call_data;

  /* Entmarkieren des gewaehlten Sortennamens: */
  XawListUnhighlight(node_and_widget->nwidget);

  /* Wegpoppen des Fensters der Sortennamen: */
  XtPopdown(XtParent(XtParent(XtParent(node_and_widget->nwidget))));

  /* Ausschnitt, in dem die Sortennamen dargestellt werden, auf Anfang der Liste 
     zuruecksetzen: */
  XawViewportSetCoordinates(XtParent(w),0,0);

  /* Baum voruebergehend unsichtbar machen: */
  UnmanageViewport(node_and_widget->node);

  /* Aufruf der dem gewaehlten Index entsprechenden Funktion: */

  switch(current_global_index)
  {
    case 1: HideSubtreeNamedNodes(node_and_widget->node,list_item->string);break;
    case 3: ShowSubtreeNamedNodes(node_and_widget->node,list_item->string);break;
    case 4: MarkNamedNodes(node_and_widget->node,list_item->string);break;
    case 5: UnmarkNamedNodes(node_and_widget->node,list_item->string);break;
    case 11: HideAttributesNamedNodes(node_and_widget->node,list_item->string);break;
    case 14: ShowAttributesNamedNodes(node_and_widget->node,list_item->string);break;
    case 17: UnmarkAllNodes(node_and_widget->node);
	     GotoFirstNamedNodePreorder(node_and_widget->node,list_item->string);break;
    case 18: UnmarkAllNodes(node_and_widget->node);
	     GotoLastNamedNodePreorder(node_and_widget->node,list_item->string);break;
    case 19: UnmarkAllNodes(node_and_widget->node);
	     GotoFirstNamedNodePostorder(node_and_widget->node,list_item->string);break;
    case 20: UnmarkAllNodes(node_and_widget->node);
	     GotoLastNamedNodePostorder(node_and_widget->node,list_item->string);
  }

  /* Baum wieder sichtbar machen: */
  ManageViewport(node_and_widget->node);
}

/************************************************************************************
 * NAME: SetCurrentGlobalIndex							    *
 *										    *
 * PROCEDURE: Callback-Funktion, die durch Auswahl eines Eintrags in einem globalen *
 *   Menue aufgerufen wird. Besetzt die globale Variable current_global_index mit   *
 *   dem Index dieses Eintrags bzgl der Liste globalm (s.o.).                       *
 * INPUT:									    *
 *   Widget w:      Id des smeBSB-Widgets, das selektiert wurde.		    *
 *   XtPointer									    *
 *     client_data: der zu speichernde Index.					    *
 *   XtPointer									    *
 *     call_data:   wird hier nicht benoetigt.					    *
 * OUTPUT: --									    *
 ************************************************************************************/

void SetCurrentGlobalIndex (Widget w, XtPointer client_data, XtPointer call_data)

{
  current_global_index = (Cardinal) client_data;
}

/***********************************************************************************
 * NAME: GlobalMenuNotifyWithoutName						   *
 *										   *
 * PROCEDURE: Callback-Funktion, die durch Selektieren eines Eintrags eines globa- *
 *   len Menues, der keinen zusaetzlichen Sortennamen benoetigt, aufgerufen wird.  *
 *   Die globale Variable current_global_index enthaelt dabei den Index des zu-    *
 *   letzt selektierten Eintrags bzgl. der Liste 'globalm'. Gemaess diesem Index   *
 *   wird die entsprechende Funktion aufgerufen. Bei Selektion des Eintrags	   *
 *   'Attribute Mask' (case 16) im Menue 'Attributes' wird die im betreffenden	   *
 *   Fenster aktuelle Attributmaske eingelesen und das Popup-Window der Attribut-  *
 *   maske aufgepoppt.								   *
 * INPUT:									   *
 *   Widget w:      Id des smeBSB-Widgets, das selektiert wurde.		   *
 *   XtPointer									   *
 *     client_data: Zeiger auf eine Struktur, die die Knoten-Information der	   *
 *                  Wurzel, die Id des Shell-Widgets der Attributmaske und einen   *
 *                  Zeiger auf das Array der Toggle-Buttons fuer die einzelnen	   *
 *                  Attribute enthaelt.						   *
 *   XtPointer									   *
 *     call_data:   wird hier nicht benoetigt.					   *
 * OUTPUT: --									   *
 ***********************************************************************************/

void GlobalMenuNotifyWithoutName (Widget w, XtPointer client_data, XtPointer call_data)

{
  CallbackStruct * node_and_widget;
  Cardinal i,no_of_attrs;
  AttrMask * maske;

  node_and_widget = (CallbackStruct *) client_data;

  /* Einlesen der aktuellen Attributmaske */
  maske = (AttrMask *) GetActualAttrMask(node_and_widget->node);

  if (current_global_index != 16)

  /* Baum voruebergehend unsichtbar machen */
  UnmanageViewport(node_and_widget->node);

  /* Aufruf der dem gewaehlten Index entsprechenden Funktion: */

  switch(current_global_index)
  {
    case 0: HideSubtreeMarkedNodes(node_and_widget->node);break;
    case 2: ShowSubtreeMarkedNodes(node_and_widget->node);break;
    case 6: MarkAllNodes(node_and_widget->node);break;
    case 7: UnmarkAllNodes(node_and_widget->node);break;
    case 8: MarkShowedNodes(node_and_widget->node);break;
    case 9: UnmarkShowedNodes(node_and_widget->node);break;
    case 10: HideAttributesMarkedNodes(node_and_widget->node);break;
    case 12: HideAttributesAllNodes(node_and_widget->node);break;
    case 13: ShowAttributesMarkedNodes(node_and_widget->node);break;
    case 15: ShowAttributesAllNodes(node_and_widget->node);break;
    case 16: /* Schleife durch den Indexbereich der Attribute: */
             no_of_attrs = Bim_NumberOfAttributes();
             for (i = 0; i < no_of_attrs; i++)
             /* Attributmaskenfenster gemaess der aktuellen Maske aktualisieren */
             XtVaSetValues(node_and_widget->mask_toggles[i],
			   XtNstate,(maske + i)->masked,
			   NULL);
             /* Attributmaskenfenster aufpoppen */
             XtPopup(node_and_widget->mwidget,XtGrabExclusive);
             break;
    case 21: CopyTree(node_and_widget->node);break;
    case 22: CloseWindow(node_and_widget->node);
  }

  if (current_global_index != (XtNumber(globalm) - 1) &&  current_global_index != 16)

     /* Baum wieder sichtbar machen (nicht bei 'Close Window') */
     ManageViewport(node_and_widget->node);
} 

/*************************************************************************************
 * NAME: GetCoordinates								     *
 *										     *
 * PROCEDURE: Event-Handler-Funktion, die die absoluten Cursor-Koordinaten aus den   *
 *   Koordinaten des Toplevel-Windows und den Koordinaten des Cursors relativ zum    *
 *   Toplevel-Window berechnet. Letztere werden aus den Event-Information, die       *
 *   durch Anklicken eines Menue-Buttons an den Event-Handler weitergereicht werden, *
 *   ausgelesen. Schliesslich werden mit den so berechneten Koordinaten die Ressour- *
 *   cen fuer die x- und y-Koordinaten der Widgets name_shell (Sortenliste) und      *
 *   mask_shell (Attributmaske) neu belegt.					     *
 * INPUT:									     *
 *   Widget w:      Id des angeklickten Widgets.				     *
 *   XtPointer									     *
 *     client_data: wird hier nicht benoetigt.					     *
 *   XtPointer									     *
 *     call_data:   Event-Informationen mit den relativen Cursor-Koordinaten.        *
 * OUTPUT: --									     *
 *************************************************************************************/

void GetCoordinates (Widget w, XtPointer client_data, XtPointer call_data)

{
  XEvent * event;
  Dimension kx,ky,kx_button,ky_button;
  Widget toplevel;
  Widget mask_shell,name_shell;
  CallbackStruct * node_and_widget;

  node_and_widget = (CallbackStruct *) client_data;

  /* Id der Shell des Attributmaskenfensters: */
  mask_shell = node_and_widget->mwidget;

  /* Id der Shell des Sortenlistenfensters wird mittels Id des List-Widgets der
     Sortennamen berechnet: */
  name_shell = XtParent(XtParent(XtParent(node_and_widget->nwidget)));

  /* Event-Information fuer den Klick auf den Menue-Button einlesen: */
  event = (XEvent *) call_data;

  /* Id der Applikationsshell mittels Id des Menue-Buttons berechnen: */
  toplevel = XtParent(XtParent(XtParent(w)));

  /* aktuelle x- und y-Koordinaten der Applikationsshell auslesen: */
  XtVaGetValues(toplevel,XtNx,&kx,
                         XtNy,&ky,
                         NULL);

  /* absolute Cursor-Koordinaten werden als Summe aus den Koordinaten der Applikations-
     shell und den relativen Koordinaten des Cursors bzgl. Applikationsshell berehnet: */
  kx = event->xbutton.x + kx;
  ky = event->xbutton.y + ky;

  /* Die Koordinaten des Attributmaskenfensters und des Sortennamenfensters werden so
     gesetzt, dass sie an der Cursor-Position aufpoppen: */ 

  XtVaSetValues(name_shell,XtNx,kx,
			   XtNy,ky,
			   NULL);

  XtVaSetValues(mask_shell,XtNx,kx,
			   XtNy,ky,
			   NULL);
}

/*********************************************************************************
 * NAME: PopupNameShell								 *
 *										 *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn in einem globalen	 *
 *   Menue ein Eintrag selektiert wird, der die Auswahl eines Sortennamens	 *
 *   erfordert. Sie sorgt fuer das Aufpoppen der Sortenliste, wobei deren Ti-	 *
 *   tel gemaess dem selektierten Menuepunkt gesetzt wird.			 *
 * INPUT:									 *
 *   Widget w:      Id des selektierten smeBSB-Widgets.				 *
 *   XtPointer									 *
 *     client_data: Index des Menuepunkts bzgl. der Liste globalm (s.o.).	 *
 *   XtPointer									 *
 *     call_data:   wird hier nicht benoetigt.					 *
 * OUTPUT: --									 *
 *********************************************************************************/

void PopupNameShell (Widget w, XtPointer client_data, XtPointer call_data)

{
  Widget name_shell,name_label;

  name_label = (Widget) client_data;
  name_shell = XtParent(XtParent(name_label));

  /* Das Fenster zur Auswahl des Sortennamens erhaelt als Titel den Namen der zuvor
     gewaehlten Funktion: */
  XtVaSetValues(name_label,XtNlabel,globalm[current_global_index].elabel,NULL);

  /* Sortennamenfenster aufpoppen: */
  XtPopup(name_shell,XtGrabExclusive);
}

/*************************************************************************************
 * NAME: UnselectAll								     *
 *										     *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn im Fenster zur Manipu-    *
 *   lation der Attributmaske der Button 'Unselect All' bedient wird. Sie sorgt      *
 *   dafuer, dass alle Toggle-Buttons dieses Fensters, die sich im Highlight-Zustand *
 *   befinden, zurueckgesetzt werden.						     *
 * INPUT:									     *
 *   Widget w:      Id des Buttons 'Unselect All'.				     *
 *   XtPointer									     *
 *     client_data: Zeiger auf eine Struktur, die unter anderem einen Zeiger auf     *
 *                  das Array der Toggle-Buttons enthaelt.			     *
 *   XtPointer									     *
 *     call_data:   wird hier nicht benoetigt.					     *
 * OUTPUT: --									     *
 *************************************************************************************/

void UnselectAll (Widget w, XtPointer client_data, XtPointer call_data)

{
  Cardinal no_of_attr,i;
  CallbackStruct * node_and_widget;

  node_and_widget = (CallbackStruct *) client_data;

  no_of_attr = Bim_NumberOfAttributes();

  /* Schleife durch den Indexbereich der Attribute: */
  for (i = 0; i < no_of_attr; i++)
  {
    /* gesetzte Toggle-Buttons im Attributmaskenfenster zuruecksetzen: */
    XtVaSetValues(node_and_widget->mask_toggles[i],XtNstate,False,NULL);
  }
}

/**************************************************************************************
 * NAME: UpdateMask								      *
 *										      *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn im Fenster zur Manipu-     *
 *   lation der Attributmaske der Button 'OK' bedient wird. Sie sorgt dafuer, dass    *
 *   die durch selektierte und nicht selektierte Toggle-Buttons dargestellte	      *
 *   Attributmaske in der entsprechenden Struktur abgespeichert wird.		      *
 * INPUT:									      *
 *   Widget w:      Id des Buttons 'OK'.					      *
 *   XtPointer									      *
 *     client_data: Zeiger auf eine Struktur, die unter anderem die Knoteninformation *
 *                  des Wurzelknotens des betreffenden Fensters und einen Zeiger auf  *
 *                  das Array der Toggle-Buttons enthaelt.			      *
 *   XtPointer									      *
 *     call_data:   wird hier nicht benoetigt.					      *
 * OUTPUT: --									      *
 **************************************************************************************/

void UpdateMask (Widget w, XtPointer client_data, XtPointer call_data)

{
  Cardinal no_of_attr,i;
  Boolean actually_masked;
  CallbackStruct * node_and_widget;
  AttrMask * maske;

  node_and_widget = (CallbackStruct *) client_data;

  /* Ermitteln der Attributmaske, die fuer das Fenster, dessen Wurzelknoten in 
     'client_data' als 'node_and_widget->node' uebergeben wurde, aktuell gueltig ist: */
  maske = (AttrMask *) GetActualAttrMask(node_and_widget->node);

  no_of_attr = Bim_NumberOfAttributes();

  /* Schleife durch den Indexbereich der Attribute: */
  for (i = 0; i < no_of_attr; i++)
  {
    /* Auslesen des Zustands des (i+1)-ten Toggle-Buttons im Attributmaskenfenster: */
    XtVaGetValues(node_and_widget->mask_toggles[i],XtNstate,&actually_masked,NULL);

    /* Die Maske wird nun mit dem soeben ausgelesenen boole'schen Zustand aktualisiert: */
    (maske + i)->masked = actually_masked;
  }

  /* Attributmaskenfenster wird weggepoppt: */
  XtPopdown(node_and_widget->mwidget);

  /* Unsichtbar- und wieder Sichtbarmachen des Baums, um evtl. ueberschriebene Bild-
     ausschnitte zu restaurieren: */
  UnmanageViewport(node_and_widget->node);
  ManageViewport(node_and_widget->node);
}

/***********************************************************************************
 * NAME: PopdownNameShell							   *
 *										   *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn im Fenster der Liste	   *
 *   der Sortennamen der Button 'Cancel' betaetigt wird. Sie sorgt dafuer, dass	   *
 *   dieses Fenster verschwindet, ohne dass weitere Aktionen durchgefuehrt werden. *
 * INPUT:									   *
 *   Widget w:      Id des Buttons 'Cancel'.					   *
 *   XtPointer									   *
 *     client_data: Id des Shell-Widgets des Sortenlistenfensters.		   *
 *   XtPointer									   *
 *     call_data:   wird hier nicht benoetigt.					   *
 * OUTPUT: --									   *
 ***********************************************************************************/

void PopdownNameShell (Widget w, XtPointer client_data, XtPointer call_data)

{
  Widget name_shell;

  name_shell = (Widget) client_data;

  XtPopdown(name_shell);
}

/************************************************************************************
 * NAME: PopdownMask								    *
 *										    *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn im Fenster zur Manipu-   *
 *   lation der Attributmaske der Button 'Cancel' betaetigt wird. Sie sorgt dafuer, *
 *   da"ss dieses Fenster verschwindet, ohne da"ss die aktuell g"ultige Attribut-   *
 *   maske modifiziert wird.							    *
 * INPUT:									    *
 *   Widget w:      Id des Butoons 'Cancel' .					    *
 *   XtPointer									    *
 *     client_data: Id des Shell-Widgets des Attributmaskenfensters.		    *
 *   XtPointer									    *
 *     call_data:   wird hier nicht benoetigt.					    *
 * OUTPUT: --									    *
 ************************************************************************************/

void PopdownMask (Widget w, XtPointer client_data, XtPointer call_data)

{
  Widget mask_shell;

  mask_shell = (Widget) client_data;

  XtPopdown(mask_shell);
}

/*************************************************************************************
 * NAME: CopyAttrMask								     *
 *										     *
 * PROCEDURE: Diese Funktion wird aufgerufen, wenn aus einem bestehenden Window der  *
 *   gesamte Baum oder ein Unterbaum in ein neues Window kopiert werden soll. Dann   *
 *   soll auch die im Ausgangs-Window gueltige Attributmaske mit uebernommen werden. *
 *   Dazu kopiert die Funktion CopyAttrMask eine bestehende Attributmaske in eine    *
 *   identische Maske (jeweils als Zeiger auf die Struktur 'AttrMask'.		     *
 * INPUT:									     *
 *   AttrMask * attr_mask: die zu kopierende Maske.				     *
 * OUTPUT:									     *
 *   AttrMask *: Die kopierte Maske.						     *
 *************************************************************************************/

AttrMask * CopyAttrMask (AttrMask * attr_mask)

{
  AttrMask * copied_attr_mask;
  Cardinal n,attr_list_length;

  attr_list_length = Bim_NumberOfAttributes();

  /* Speicher fuer neue Attributmaske belegen: */
  copied_attr_mask = (AttrMask *) XtMalloc(attr_list_length * sizeof(AttrMask));

  /* Schleife durch den Indexbereich der Attribute: */
  for (n = 0; n < attr_list_length; n++)
  {
    /* alle boole'schen Werte der alten Maske in die neue kopieren: */
    (copied_attr_mask + n)->masked    = (attr_mask + n)->masked;
  }

  return copied_attr_mask;
}

/*********************************************************************************
 * NAME: GetAttrMask								 *
 *										 *
 * PROCEDURE: Diese Funktion wird nach Aufruf des Browsers benutzt, um fuer das	 *
 *   erste Window eine Attributmaske zu generieren. Dazu wird zuerst eine Liste	 *
 *   aller Attributnamen erzeugt und schliesslich alle Werte der Maske mit False *
 *   belegt, da zu beginn keine Attribute maskiert sein sollen.			 *
 * INPUT: --									 *
 * OUTPUT:									 *
 *   AttrMask *: Die generierte Maske						 *
 *********************************************************************************/

AttrMask * GetAttrMask ()

{
  AttrMask * initialized_mask;
  Cardinal n,attr_list_length;

  attr_list_length = Bim_NumberOfAttributes();

  /* String-Array mit den Namen der Attribute erzeugen: */
  attribute_list = (String *) XtMalloc(attr_list_length * sizeof(String));
  attribute_list = (String *) Bim_ListOfAttributes();

  /* Speicher fuer neue Attributmaske belegen: */
  initialized_mask = (AttrMask *) XtMalloc(attr_list_length * sizeof(AttrMask));

  /* Schleife durch den Indexbereich der Attribute: */
  for (n = 0; n < attr_list_length; n++)
  {
    /* alle Werte mit False (= nicht maskiert) vorbelegen: */ 
    (initialized_mask + n)->masked = False;
  }

  return initialized_mask;
} 

/************************************************************************************
 * NAME: DestroyAttrMask							    *
 *										    *
 * PROCEDURE: Diese Funktion wird aufgerufen, wenn das Window eines Baums geschlos- *
 *   sen wird. Dann wird auch die zugehoerige Maske nicht mehr benoetigt und der    *
 *   von ihr belegte Speicherplatz wird freigegeben.				    *
 * INPUT:									    *
 *   AttrMask * attr_mask: Die zu zerstoerende Attributmaske			    *
 * OUTPUT: --									    *
 ************************************************************************************/

void DestroyAttrMask (AttrMask * attr_mask)

{
  XtFree((char *) attr_mask);
}

/*************************************************************************************
 * NAME: ResetViewport								     *
 *										     *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn das Fenster der Attribut- *
 *   maske durch Betaetigen der Button 'OK' oder 'Cancel' weggepoppt wird. Sie sorgt *
 *   dann dafuer, dass der Ausschnitt, in dem die Attributnamen dargestellt werden,  *
 *   das Viewport-Widget, in den Ausgangszustand zurueckgesetzt wird, d.h. dass er   *
 *   beim naechsten Aufpoppen des Fensters den Anfang der Liste der Attributnamen    *
 *   darstellt.									     *
 * INPUT:									     *
 *   Widget w:      Id des 'OK'- bzw. 'Cancel'-Buttons.				     *
 *   XtPointer									     *
 *     client_data: Id des Viewport-Widgets.					     *
 *   XtPointer									     *
 *     call_data:   wird hier nicht benoetigt.					     *
 * OUTPUT: --									     *
 *************************************************************************************/

void ResetViewport (Widget w, XtPointer client_data, XtPointer call_data)

{
    /* Der folgende Befehl setzt den sichtbaren Ausschnitt an die linke obere Ecke
       des darzustellenden Bilds (Koordinaten (0,0)) */
    XawViewportSetCoordinates((Widget) client_data,0,0);
}

/***********************************************************************************
 * NAME: CreateGlobalMenu							   *
 *										   *
 * PROCEDURE: Diese Funktion wird immer aufgerufen, wenn ein neues Window erzeugt  *
 *   wird. Sie sorgt haupsaechlich fuer die Ausstattung eines Windows mit der glo- *
 *   balen Menueleiste. Dazu werden zunaechst die Menue-Buttons in ein gemeinsames *
 *   Form-Widget verpackt. An jeden Menue-Button wird ein Popup-Menue gehaengt,    *
 *   deren Eintraege der Liste 'globalm', die zu Beginn dieses Files deklariert    *
 *   wurde, entnommen werden. Die einzelnen smeBSB-Widgets der Menueeintraege wer- *
 *   den mit der entsprechenden Callback-Routine ausgestattet. Ausserdem erzeugt   *
 *   diese Funktion die Popup-Windows, in denen die Menuemaske geaendert bzw. ein  *
 *   Sortenname ausgewaehlt wird.						   *
 * INPUT:									   *
 *   Widget parent:   Id des Form-Widgets, das die Menueleiste und den Viewport,   *
 *                    der den Baum darstellt, enthaelt.				   *
 *   MAX_NODE * root: MAX_NODE-Information des Wurzelknotens des zur Menueleiste   *
 *                    gehoerenden Baums. Sie wird zur Uebergabe fuer Callback-     *
 *                    Listen benoetigt.						   *
 *   AttrMask * maske: Zeiger auf eine neu generierte, initialisierte Attribut-    *
 *                     maske, die fuer das Popup-Window zur Aenderung der Attri-   *
 *                     butmaske benoetigt wird.					   *
 * OUTPUT:									   *
 *   Widget: Id des Form-Widgets, das die Menu-Buttons enthaelt.		   *
 ***********************************************************************************/

Widget CreateGlobalMenu (Widget parent, MAX_NODE * root, AttrMask * maske)

{
  Cardinal n,m,attr_list_length,string_list_length;
  Widget menu_button_cont;
  Widget menu_button[XtNumber(menu_list)],menu[XtNumber(menu_list)];
  Widget wl[XtNumber(globalm)];
  Widget name_shell,name_form,name_label,name_viewport,name_list,name_cancel;
  Widget mask_shell,mask_form1,mask_viewport,mask_form2;
  Widget mask_cancel,mask_ok,mask_unselect;
  Widget * mask_toggles;
  Dimension viewport_width,toggle_width;
  String * string_list;
  CallbackStruct * node_and_widget;

/* Einlesen der Anzahl der Attribute. Wird fuer Schleifen benoetigt: */
  attr_list_length = Bim_NumberOfAttributes();

/* Erzeugen des Popup-Fensters fuer die Attributmaske: */

  mask_shell = XtVaCreatePopupShell("Maske",overrideShellWidgetClass,parent,
				     NULL);

  mask_form1 = XtVaCreateManagedWidget("mask_form1",formWidgetClass,mask_shell,
				       NULL);

/* Erzeugung eines Viewport-Widgets zur Darstellung der Toggle-Buttons: */

  mask_viewport = XtVaCreateManagedWidget("mask_viewport",viewportWidgetClass,mask_form1,
					   XtNallowVert,True, 
					   XtNforceBars,True,
					   XtNheight,150,
					   NULL);

  mask_form2 = XtVaCreateManagedWidget("mask_form2",formWidgetClass,mask_viewport,
				        NULL);

/* Erzeugung einer Liste von Toggle-Buttons. Jeder Button entspricht einem Attribut-
   namen. Die beiden Zustaende des Buttons entsprechen den Zustaenden markiert/
   nicht markiert: */

  mask_toggles = (Widget *) XtMalloc(attr_list_length * sizeof(Widget));

  mask_toggles[0] = XtVaCreateManagedWidget("mask_toggle",toggleWidgetClass,mask_form2,
					     XtNlabel,attribute_list[0],
					     NULL);

/* Die naechsten drei Anweisungen sorgen fuer eine Verbreiterung des zuvor erzeugten
   Toggle-Buttons. Dies ist aufgrund einer offensichtlichen Unzulaenglichkeit des
   Toggle-Button-Widgets noetig, da dieses den Label-String nicht vollstaendig
   drastellt. */

  XtVaGetValues(mask_toggles[0],XtNwidth,&toggle_width,NULL);
  toggle_width = toggle_width + 16;
  XtVaSetValues(mask_toggles[0],XtNwidth,toggle_width,NULL);

/* Schleife durch den Indexbereich der Attribute. Damit werden ebensoviel Toggle-
   Buttons erzeugt, wie Attribute vorhanden sind. */

  for (n = 1; n < attr_list_length; n++)
  {
  mask_toggles[n] = XtVaCreateManagedWidget("mask_toggle",toggleWidgetClass,mask_form2,
					     XtNlabel,attribute_list[n],
					     XtNfromVert,mask_toggles[n-1],
					     NULL);

/* Die naechsten drei Anweisungen sorgen fuer eine Verbreiterung des zuvor erzeugten
   Toggle-Buttons. Dies ist aufgrund einer offensichtlichen Unzulaenglichkeit des
   Toggle-Button-Widgets noetig, da dieses den Label-String nicht vollstaendig
   drastellt. */

  XtVaGetValues(mask_toggles[n],XtNwidth,&toggle_width,NULL);
  toggle_width = toggle_width + 16;
  XtVaSetValues(mask_toggles[n],XtNwidth,toggle_width,NULL);
  }

/* Erzeugung der Buttons zur Bedienung des Attributmaskenfensters mit den zugehoerigen
   Callback-Listen */

  mask_unselect = XtVaCreateManagedWidget("mask_unselect",commandWidgetClass,mask_form1,
					  XtNlabel,"Unselect All",
					  XtNfromVert,mask_viewport,
					  NULL);

  mask_cancel = XtVaCreateManagedWidget("mask_cancel",commandWidgetClass,mask_form1,
					 XtNlabel,"Cancel",
					 XtNfromVert,mask_unselect,
					 NULL);
  
  XtAddCallback(mask_cancel,XtNcallback,PopdownMask,(XtPointer) mask_shell);
  XtAddCallback(mask_cancel,XtNcallback,ResetViewport,(XtPointer) mask_viewport);

  mask_ok = XtVaCreateManagedWidget("mask_ok",commandWidgetClass,mask_form1,
				     XtNlabel,"OK",
				     XtNfromVert,mask_unselect,
				     XtNfromHoriz,mask_cancel,
				     NULL);

/* In den naechsten vier Zeilen werden mehrere Information in die Struktur
   'CallbackStruct' "gepackt". Diese Informationen werden in den verschie-
   densten Callback-Funktionen benoetigt. Die neu definierte Struktur wird
   benoetigt, da an die Callback-Funktionen nur Zeiger uebergeben werden 
   duerfen. Einige Zeilen weiter unten kommt noch der Inhalt einer weiteren
   Variablen dazu, der hier noch nicht bereitsteht. */

  node_and_widget = (CallbackStruct *) XtMalloc(sizeof(CallbackStruct));

  node_and_widget->node          = root;
  node_and_widget->mwidget       = mask_shell;
  node_and_widget->mask_toggles  = mask_toggles;

  XtAddCallback(mask_ok,XtNcallback,UpdateMask,(XtPointer) node_and_widget);
  XtAddCallback(mask_ok,XtNcallback,ResetViewport,(XtPointer) mask_viewport);
  XtAddCallback(mask_unselect,XtNcallback,UnselectAll,(XtPointer) node_and_widget);

/* Erzeugung des Form-Widgets, das alle Menue-Buttons der Menueleiste enthaelt: */

  menu_button_cont = XtVaCreateManagedWidget("menu_button_cont",formWidgetClass,parent,
					      XtNbottom,XtChainTop,
					      XtNleft,XtChainLeft,
					      XtNtop,XtChainTop, 
					      XtNdefaultDistance,0,
					      NULL);

/* Erzeugung der alfabetischen Liste aller Sortennamen */

  string_list_length = Bim_NumberOfSorts();
  string_list = (String *) XtMalloc(string_list_length * sizeof(String));
  string_list = (String *) Bim_ListOfSorts();

/* Erzeugen des Popup-Fensters fuer die Sortennamenauswahl: */

  name_shell = XtVaCreatePopupShell("Sortenliste",overrideShellWidgetClass,menu_button_cont,
				       NULL);

  name_form = XtVaCreateManagedWidget("name_form",formWidgetClass,name_shell,
				         NULL);

/* Erzeugung eines Label-Widgets. Seine Ressource XtNlabel wird nach Auswahl einer 
   Funktion aus der Menueleiste neu gesetzt, so dass das Popup-Fenster einen Titel
   besitzt, der die zuvor ausgewaehlte Funktion bezeichnet, auf die sich der
   Sortenname dann bezieht. */

  name_label = XtVaCreateManagedWidget("name_label",labelWidgetClass,name_form,
				        XtNwidth,50,
				        XtNlabel,"Hide on Name",
				        NULL);

/* Erzeugung eines Viewport-Widgets, das die alfabetische Liste der Sortennamen aus-
   schnittsweise darstellt. */

  name_viewport = XtVaCreateManagedWidget("name_viewport",viewportWidgetClass,name_form,
					     XtNfromVert,name_label,
					     XtNallowVert,True,
					     XtNforceBars,True,
					     XtNheight,200,
					     NULL);

/* Erzeugung eines List-Widgets, das die Liste der Sortennamen enthaelt. */

  name_list = XtVaCreateManagedWidget("name_list",listWidgetClass,name_viewport,
				         XtNlist,string_list,
				         XtNdefaultColumns,1,
				         XtNforceColumns,True,
				         XtNborderWidth,1,
				         NULL);

/* Erzeugung eines Command-Buttons, dessen Bedienung dem vorzeitigen Wegpoppen des
   Popup-Fensters dient, sowie der dazugehoerigen Callback-Liste. */

  name_cancel = XtVaCreateManagedWidget("name_cancel",commandWidgetClass, name_form,
				        XtNfromVert,name_viewport,
				        XtNlabel,"Cancel",
				        NULL);

  XtAddCallback(name_cancel,XtNcallback,PopdownNameShell,(XtPointer) name_shell);

/* Die beiden naechsten Zeilen dienen der Verbreiterung des Viewport-Widgets, in dem
   die Liste der Sortennamen dargestellt wird. Dies ist noetig, da dieses Widget aus
   unerfindlichen Gruenden immer zu schmal berechnet ist. */

  XtVaGetValues(name_list,XtNwidth,&viewport_width,NULL);
  XtVaSetValues(name_viewport,XtNwidth,viewport_width + 8,NULL);

/* Hinzuname der Shell-Id des Sortenlisten-Fenters zur Struktur 'CallbackStruct',
   die bereits oben belegt wurde. */

  node_and_widget->nwidget = name_list;

/* Anhaengen einer Callback-Funktion an das List-Widget, die nach Auswahl eines Sorten-
   namens fuer den Aufruf der richtigen Funktion sorgt. */

  XtAddCallback(name_list,XtNcallback,GlobalMenuNotifyWithName,(XtPointer) node_and_widget);

/* Speicherbereich fuer die alfabetische Liste der Sortennamen wieder freigeben. Diese Liste wird in-
   zwischen vom List-Widget verwaltet. */

#ifndef linux
  XtFree((char *) string_list);
#else
  #error "bug needs to be fixed"
#endif

/* Erzeugung der Menue-Button der Menueleiste gemaess der Liste 'menu_list' (s.o.). */

  menu_button[0] = XtVaCreateManagedWidget((String) menu_list[0],menuButtonWidgetClass,menu_button_cont,
					 XtNborderWidth,0,
					 XtNbottom,XtChainTop,
					 XtNleft,XtChainLeft,
					 XtNright,XtChainLeft,
					 XtNtop,XtChainTop,
					 NULL);

/* Anhaengen einer Event-Handler-Funktion, die fuer die richtige Positionierung eines evtl. Popup-
   Fensters sorgt. */

  XtAddEventHandler(menu_button[0],ButtonPressMask,False,(XtEventHandler) GetCoordinates,(XtPointer) node_and_widget);

/* Schleife durch den Indexbereich der Liste der Menue-Button-Titel. */

  for (n = 1; n < XtNumber(menu_list); n++)

  {
    menu_button[n] = XtVaCreateManagedWidget((String) menu_list[n],menuButtonWidgetClass,menu_button_cont,
					    XtNfromHoriz,menu_button[n-1],
					    XtNhorizDistance,4,
					    XtNborderWidth,0,
					    XtNbottom,XtChainTop,
					    XtNleft,XtChainLeft,
					    XtNright,XtChainLeft,
					    XtNtop,XtChainTop,
					    XtNfromHoriz,menu_button[n-1],
					    XtNhorizDistance,0,
					    NULL);

/* Anhaengen einer Event-Handler-Funktion, die fuer die richtige Positionierung eines evtl. Popup-
   Fensters sorgt. */

   XtAddEventHandler(menu_button[n],ButtonPressMask,False,(XtEventHandler) GetCoordinates,(XtPointer) node_and_widget);
  }

/* Ende der Erzeugung der Menue-Button. */

/* Erzeugung und Anhaengung der zu den Buttons gehoerigen Menues gemaess der Liste 'globalm'. */

  /* Schleife durch den Indexbereich der Liste der Menue-Button-Titel. */
  for (n = 0; n < XtNumber(menu_list); n++)

  {
    /* Erzeugung eines Simple-Menu-Widgets, in das die einzelnen Menuepunkte gepackt werden. */
    menu[n] = XtVaCreatePopupShell("menu",simpleMenuWidgetClass,menu_button[n],
			            NULL);

    /* Schleife durch den Indexbereich der Liste der Manueeintraege. */
    for (m = 0; m < XtNumber(globalm); m++)
    {
      /* falls Menuepunkt m zum Menue n gehoert: */
      if (globalm[m].mno == n)

      {
        /* Erzeugung eines Widgets fuer einen einzelnen Menueeintrag */
        wl[m] = XtVaCreateManagedWidget(globalm[m].ename,smeBSBObjectClass,menu[n],
                                        XtNlabel,globalm[m].elabel,
                                        NULL);

        /* falls Menuepunkt m bei Selektion das Aufpoppen des Fensters der Sortennamen erfordert: */
        if (globalm[m].npop)
        {
          /* Anhaengen von Callback-Funktionen zum Abspeichern des Index des gewaehlten Menue-
             punkts und zum Aufpoppen des Fensters der Sortennamen. */
          XtAddCallback(wl[m],XtNcallback,SetCurrentGlobalIndex,(XtPointer) m);
          XtAddCallback(wl[m],XtNcallback,PopupNameShell,(XtPointer) name_label);
        }
        /* falls Menuepunkt m bei Selektion das Fensters der Sortennamen nicht erfordert: */
        else
        {
          /* Anhaengen von Callback-Funktionen zum Abspeichern des Index des gewaehlten Menue-
             punkts und zum direkten Ausfuehren der gewuenschten Funktion. */
          XtAddCallback(wl[m],XtNcallback,SetCurrentGlobalIndex,(XtPointer) m);
          XtAddCallback(wl[m],XtNcallback,GlobalMenuNotifyWithoutName,(XtPointer) node_and_widget);
        }
      }
    }
  }

  return (menu_button_cont);
} 

/***************************************************************************************
 * NAME: GetNodeId								       *
 *										       *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn ein bestimmter Knoten an-   *
 *    klickt wurde. Sie schreibt die MAX_NODE-Adresse dieses Knotens in eine globale   *
 *    Variable. Diese Adresse wird ausgelesen, wenn eine Funktion aus dem Knotenmenue  *
 *    ausgefuehrt wird. Somit wird gewaehrleistet, dass diese Funktion auf dem zuletzt *
 *    angeklickten, also dem richtigen, Knoten operiert.			       *
 * INPUT:									       *
 *   Widget w:      Id des angeklickten Node-Widgets.				       *
 *   XtPointer									       *
 *     client_data: Die zum angeklickten Knoten gehoerige MAX_NODE-Adresse.	       *
 *   XtPointer									       *
 *     call_data:   wird hier nicht benoetigt.					       *
 * OUTPUT: --									       *
 ***************************************************************************************/

void GetNodeId (Widget w, XtPointer client_data, XtPointer call_data)

{
  current_node_id = (MAX_NODE *) client_data;
}

/*************************************************************************************
 * NAME: NodeMenuNotify								     *
 *										     *
 * PROCEDURE: Callback-Funktion, die aufgerufen wird, wenn aus dem Knotenmenue ein   *
 *   Menuepunkt selektiert wird. Abhaengig vom Index des gewaehlten Menuepunkts wird *
 *   die entsprechende Funktion aufgerufen.					     *
 * INPUT:									     *
 *   Widget w:      Id des smeBSB-Widgets, das selektiert wurde.		     *
 *   XtPointer									     *
 *     client_data: Index des gewaehlten Menueeintrags im Knotenmenue.		     *
 *   XtPointer									     *
 *     call_data:   wird hier nicht benoetigt.					     *
 * OUTPUT: --									     *
 *************************************************************************************/

void NodeMenuNotify (Widget w, XtPointer client_data, XtPointer call_data)

{
  Cardinal n;

/* Index der im Knotenmenu gewaehlten Funktion aus 'client_data' entnehmen */

  n = (Cardinal) client_data;

/* Aufruf der entsprechenden Funktion */

  switch(n)
  {
     /* In den Faellen 1-3 wird zunaechst der Zustand des Knotens erfragt, um dann die 
        jeweils komplementaere Funktion aufzurufen. */
     case 1: if (ShowedAttributes(current_node_id))
                {HideAttributes(current_node_id);break;}
             else
                {ShowAttributes(current_node_id);break;}
     case 2: if (Marked(current_node_id))
                {UnmarkNode(current_node_id);break;}
             else
                {MarkNode(current_node_id);break;}
     case 3: if (HiddenTree(current_node_id))
                {ShowSubtree(current_node_id);break;}
             else
                {HideSubtree(current_node_id);break;}
     case 4: MarkSubtree(current_node_id);break;
     case 5: UnmarkSubtree(current_node_id);break;
     case 6: MarkShowedSubtree(current_node_id);break;
     case 7: UnmarkShowedSubtree(current_node_id);break;
     case 8: MarkPath(current_node_id);break;
     case 9: UnmarkPath(current_node_id);break;
     case 10: CopySubtree(current_node_id);break;
     case 11: UnmarkAllNodesFromRoot(current_node_id);
	      GotoFirstNodePreorder(current_node_id);break;
     case 12: UnmarkAllNodesFromRoot(current_node_id);
	      GotoLastNodePreorder(current_node_id);break;
     case 13: UnmarkAllNodesFromRoot(current_node_id);
	      GotoNextNodePreorder(current_node_id);break;
     case 14: UnmarkAllNodesFromRoot(current_node_id);
	      GotoPreviousNodePreorder(current_node_id);break;
     case 15: UnmarkAllNodesFromRoot(current_node_id);
	      GotoFirstNodePostorder(current_node_id);break;
     case 16: UnmarkAllNodesFromRoot(current_node_id);
	      GotoLastNodePostorder(current_node_id);break;
     case 17: UnmarkAllNodesFromRoot(current_node_id);
	      GotoNextNodePostorder(current_node_id);break;
     case 18: UnmarkAllNodesFromRoot(current_node_id);
	      GotoPreviousNodePostorder(current_node_id);
  }
}

/*******************************************************************************
 * NAME: CreateNodeMenu							       *
 *									       *
 * PROCEDURE: Diese Funktion haengt die Popup-Shell des Knotenmenues an den    *
 *   Viewport, der den Baum ausschnittsweise darstellt. In diese Shell wer-    *
 *   den die einelnen Eintraege als semBSB-Widgets gepackt. Deren Titel wer-   *
 *   der Liste 'nodem' entnommen, die zu beginn dieses Files deklariert wurde. *
 * INPUT:								       *
 *   Widget parent: Id des Viewport-Widgets, das den Baum enthaelt.	       *
 * OUTPUT: --								       *
 *******************************************************************************/


void CreateNodeMenu (Widget parent)

{
  Cardinal n;
  Widget wl[XtNumber(nodem)+1],ll[XtNumber(nodem)+1];

/* Erzeugung des Shell-Widgets fuer das Popup-Fensters des Knotenmenues. */

  node_menu = XtVaCreatePopupShell("node_menu",simpleMenuWidgetClass,parent,
			       XtNheight,(XtNumber(nodem)+1) * 15 + 2,
			       XtNwidth,215,
			       XtNlabel,"- Node menu -",
			       NULL); 

/* Einfuegung einer Trennlinie zwischen den Menuetitel und die Menueoptionen durch
   Erzeugung eines Line-Widgets. */

  wl[0] = XtVaCreateManagedWidget("line",smeLineObjectClass,node_menu,
				   XtNy,15,
				   NULL);

/* Erzeugung von Widgets fuer jeden Menueeintrag gemaess der List 'nodem' (s.o.).
   Diese Widgets werden an das zuvor erzeugte Shell-Widget angehaengt. */

  /* Schleife durch den Indexbereich der Liste 'nodem'. */
  for (n = 1; n < (XtNumber(nodem) + 1); n++)
  {
    wl[n] = XtVaCreateManagedWidget(nodem[n-1].ename,smeBSBObjectClass,node_menu,
				    XtNy,n*15,
				    XtNlabel,nodem[n-1].elabel,
				    NULL);
				    
    XtAddCallback(wl[n],XtNcallback,NodeMenuNotify,(XtPointer) n);

    /* Einfuegung einer Trennlinie zwischen Gruppen von zusammengehoerenden Menue-
       optionen durch Line-Widgets. Zwischen welchen Optionen eingefuegt werden,
       geht aus der Liste 'nodem' hervor. */

    if (nodem[n-1].sectend)
    {
      ll[n] = XtVaCreateManagedWidget("line",smeLineObjectClass,node_menu,
				       XtNy,(n+1)*15,
				       NULL);
    }
  }
}

