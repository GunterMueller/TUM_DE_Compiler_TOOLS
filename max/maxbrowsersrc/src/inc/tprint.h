
#ifndef _TPRINT_H_
#define _TPRINT_H_

/* Defines fuer den Zugriff auf die MAX_NODE Struktur */

#define ShowedAttributes(n) 	((n)->x_info->show_attributes)
#define HiddenTree(n) 		((n)->x_info->hidden_tree)
#define Marked(n) 		((n)->x_info->marked)
#define Widget(n) 		((n)->x_info->widget)
#define AttrWidget(n)		((n)->x_info->attr_widget)
#define Context(n) 		((n)->x_info->context)
#define AttrMask(n)		((n)->x_info->attr_mask)

/* Funktionen zum Verwalten der X_INFO Struktur */

X_INFO *CreateX_INFO		 	();
X_INFO *CopyX_INFO			(X_INFO *);
void DestroyX_INFO			(X_INFO *);

/* Hilfsfunktionen */

AttrMask *GetActualAttrMask		(MAX_NODE *);

void UnmanageViewport			(MAX_NODE *);
void ManageViewport			(MAX_NODE *);

void UnmarkAllNodesFromRoot		(MAX_NODE *);

void RaiseWindow			(MAX_NODE *);
void CenterNode				(MAX_NODE *);

/* Funktionen des Knotenmenues */

void ShowAttributes			(MAX_NODE *);
void HideAttributes			(MAX_NODE *);
void MarkNode				(MAX_NODE *);
void MarkSubtree			(MAX_NODE *);
void MarkShowedSubtree			(MAX_NODE *);
void UnmarkNode				(MAX_NODE *);
void UnmarkSubtree			(MAX_NODE *);
void UnmarkShowedSubtree		(MAX_NODE *);
void ShowSubtree			(MAX_NODE *);
void HideSubtree			(MAX_NODE *);
void MarkePath				(MAX_NODE *);
void UnmarkPath				(MAX_NODE *);

void CopySubtree			(MAX_NODE *);

void GotoFirstNodePreorder		(MAX_NODE *);
void GotoLastNodePreorder		(MAX_NODE *);
void GotoNextNodePreorder		(MAX_NODE *);
void GotoPreviousNodePreorder		(MAX_NODE *);

void GotoFirstNodePostorder		(MAX_NODE *);
void GotoLastNodePostorder		(MAX_NODE *);
void GotoNextNodePostorder		(MAX_NODE *);
void GotoPreviousNodePostorder		(MAX_NODE *);


/* Funktionen des Hauptmenues */

void HideSubtreeMarkedNodes 		(MAX_NODE *);
void ShowSubtreeMarkedNodes		(MAX_NODE *);
void HideSubtreeNamedNodes  		(MAX_NODE *, char *);
void ShowSubtreeNamedNodes  		(MAX_NODE *, char *);
void MarkAllNodes			(MAX_NODE *);
void MarkShowedNodes			(MAX_NODE *);
void MarkNamedNodes   		 	(MAX_NODE *, char *);
void UnmarkAllNodes	  		(MAX_NODE *);
void UnmarkShowedNodes			(MAX_NODE *);
void UnmarkNamedNodes	 		(MAX_NODE *, char *);
void HideAttributesNamedNodes		(MAX_NODE *, char *);
void HideAttributesMarkedNodes		(MAX_NODE *);
void HideAttributesAllNodes		(MAX_NODE *);
void ShowAttributesNamedNodes		(MAX_NODE *, char *);
void ShowAttributesMarkedNodes 		(MAX_NODE *);
void ShowAttributesAllNodes 		(MAX_NODE *);

void GotoFirstNamedNodePreorder		(MAX_NODE *, char *);
void GotoLastNamedNodePreorder		(MAX_NODE *, char *);
void GotoFirstNamedNodePostorder	(MAX_NODE *, char *);
void GotoLastNamedNodePostorder		(MAX_NODE *, char *);

void CopyTree				(MAX_NODE *);
void CloseWindow			(MAX_NODE *);

/* Mainfunktion */

void CreateMainShell			(MAX_NODE *, int, char **);
void CreateNewShell			(MAX_NODE *, MAX_NODE *);

#endif
