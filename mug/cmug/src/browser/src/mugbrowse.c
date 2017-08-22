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

/************************************************************************/
/*									*/
/* Allgemeine C-Includes						*/
/*									*/
/************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/************************************************************************/
/*									*/
/* spezifische Includes 						*/
/*									*/
/************************************************************************/
#include "../header/browse_len.h"
#include "../header/browse_ds.h"
#include "../header/browse_types.h"
#include "../header/browse_const.h"
#include "../header/configure.h"

/************************************************************************/
/*									*/
/* globale Variable attr_num						*/
/*									*/
/************************************************************************/

int attr_num = 0;

/* #define DEBUG 1 */

/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zum Allokieren von Speicherplatz 		       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* ALE_alloc								*/
/*									*/
/* allokiert Speicher fuer ein Attributlistenelement			*/
/************************************************************************/
ALEP ALE_alloc(void)
{
ALEP ptr = (ALEP)calloc(1, sizeof(ALE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

return ptr;
}


/************************************************************************/
/* ArgLE_alloc								*/
/*									*/
/* allokiert Speicher fuer ein Argumentlistenelement			*/
/************************************************************************/
ArgLEP ArgLE_alloc(void)
{
ArgLEP ptr = (ArgLEP)calloc(1, sizeof(ArgLE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

return ptr;
}


/************************************************************************/
/* TE_alloc								*/
/*									*/
/* allokiert Speicher fuer ein Baumelement				*/
/************************************************************************/
TEP TE_alloc(void)
{
TEP ptr;

ptr = (TEP)calloc(1, sizeof(TE));
if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

return ptr;
}


/************************************************************************/
/* XLE_alloc								*/
/*									*/
/* Speicher fuer ein x_list-Element allokieren				*/
/************************************************************************/
XLEP XLE_alloc(void)
{
XLEP ptr = (XLEP)calloc(1, sizeof(XLE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}
return ptr;
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Allgemeine Funktionen					       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* usage								*/
/*									*/
/* Ausgabe der Befehlsschablone 					*/
/************************************************************************/
void usage(void)
{
printf("USAGE: MUGbrowse [-c config-file] prog[.browse]\n");
exit (0);
}


/************************************************************************/
/* hole_satz								*/
/*									*/
/* Holt einen Satz aus dem browsefile					*/
/************************************************************************/
char hole_satz(union satz_info *s, FILE *fp)
{
char c;

c= (char)fgetc(fp);				/* Satzart holen	*/
if (c != EOF)
	fread((char *)s, sizeof(union satz_info), 1, fp);

return c;					/* Satzart zurueckgeben */
}


/************************************************************************/
/* get_attr_ptr (Pass2) 						*/
/*									*/
/* berechnet Zeiger auf ein Attribut, dess Namen wir kennen		*/
/************************************************************************/
ALEP get_attr_ptr(AList *list, char *attr)
{
ALEP ptr = list->first;

/* Wir suchen in der Liste nach dem Attribut und geben die Adresse zurueck */
while (ptr)
	{
	if (strcmp(ptr->attr, attr) == 0)
		break;
	ptr = ptr->next;
	}

if (ptr == NULL)
	{
	printf("get_attr_ptr: %s nicht gefunden!\n", attr);
	exit(0);
	}

return ptr;
}


/************************************************************************/
/* get_terminal (Pass2) 						*/
/*									*/
/* berechnet den Zeigen auf ein Terminal				*/
/************************************************************************/
TEP get_terminal(TEPList *list, char *symbol, int id)
{
TEPLEP ptr = list->first;

while (ptr)
	{
	if (ptr->symbol->sohn_id == id)
		return ptr->symbol;
	ptr=ptr->next;
	}

printf("Can't find terminal %s\n", symbol);
exit(0);
}


/************************************************************************/
/* get_arg_ptr (Pass2)							*/
/*									*/
/* berechnet den Zeiger auf ein Argument, egal wozu es gehoert. 	*/
/************************************************************************/
ArgLEP get_arg_ptr(TEP akt_vater, struct argument *g)
{
ArgLEP ptr=ArgLE_alloc();
TEPLEP sohn;
TEP akt_sohn;

/* Zuerst schauen wir, ob es ein Terminal ist		*/
if (strlen(g->attr) == 0)		/* Terminal	*/
	{
	ptr->terminal = get_terminal(&akt_vater->soehne, g->symbol, g->id);
	return ptr;
	}

/* Jetzt schauen wir, ob das Attribut zum Vater gehoert */
if (akt_vater->vater_id == g->id)
	{
	switch (g->art)
		{
		case 'A':
			ptr->attr = get_attr_ptr(&akt_vater->aattr, g->attr);
			break;
		case 'D':
			ptr->attr = get_attr_ptr(&akt_vater->dattr, g->attr);
			break;
		case 'I':
			ptr->attr = get_attr_ptr(&akt_vater->iattr, g->attr);
			break;
		default:
			printf("Illegal type of attribute\n");
			exit(0);
		}
	}
else			/* Jetzt suchen wir bei den Soehnen	*/
	{
	sohn = akt_vater->soehne.first;
	while (sohn)
		{
		akt_sohn = sohn->symbol;
		if (akt_sohn->sohn_id == g->id)
			{
			switch (g->art)
				{
				case 'A':
					ptr->attr = get_attr_ptr(&akt_sohn->aattr, g->attr);
					break;
				case 'D':
					ptr->attr = get_attr_ptr(&akt_sohn->dattr, g->attr);
					break;
				case 'I':
					ptr->attr = get_attr_ptr(&akt_sohn->iattr, g->attr);
					break;
				default:
					printf("Illegal type of attribute\n");
					exit(0);
				}
			}
		sohn = sohn ->next;
		}
	}
if (ptr->attr == NULL)
	{
	printf("Can't fint attribut %s\n", g->attr);
	exit(0);
	}

return ptr;
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zur Listenbearbeitung				       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* AList_insert 							*/
/*									*/
/* Einfuegen eines Attributs in die Liste				*/
/************************************************************************/
ALEP AList_insert(AList *list, struct attribut *a, ANList *anlist, TEP node)
{
ANLEP ptr;
ALEP alep= ALE_alloc();
int icon_num;
int slen = strlen(alep->attr) + 1;
char *attr_str = (char *) malloc(slen), *remind = attr_str, prefix = '-';

strcpy(alep->attr, a->attr);
strcpy(alep->typ,  a->typ );
alep->wertlen = a->wertlen;
alep->art = a->art;
alep->copy_of = NULL;	/* Besetzung im zweiten Pass */
alep->result_of = NULL; /* Besetzung im zweiten Pass */
alep->node = node;	/* Zugehoeriger Baumknoten	*/
icon_num = get_image(alep, anlist);
if (icon_num == -1) {
	config_equal(anlist, alep, attr_num);
	icon_num = attr_num++;
	if (attr_num == 112) attr_num = 0;
	}
else {
	/* Loesche Praefix, falls vorhanden */
	strcpy(attr_str, alep->attr);
	if ((*attr_str == 'a' && alep->art == 'A') ||
	 (*attr_str == 'd' && alep->art == 'D') ||
	 (*attr_str == 'i' && alep->art == 'I')) {
		prefix = *attr_str;
		attr_str = attr_str + 1;
		}
	ptr = anlist->first;
	while (ptr)
		{
		if (strcmp(ptr->attr, attr_str) == 0) {
			switch(prefix) {
				case 'a':
					ptr->prefix[1] = 'a';
					break;
				case 'd':
					ptr->prefix[2] = 'd';
					break;
				case 'i':
					ptr->prefix[3] = 'i';
					break;
				default:
					ptr->prefix[0] = '-';
				}
			break;
			}
		ptr = ptr->next;
		}
	free(remind);
	}

alep->image = icon_num;

if (list->anzahl == 0)
	{
	list->first = alep;
	list->last = alep;
	alep->prev = NULL;
	alep->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	alep->prev=list->last;
	list->last->next=alep;
	alep->next=NULL;
	list->last = alep;
	}
list->anzahl++;
return alep;
}


/************************************************************************/
/* ArguList_insert							*/
/*									*/
/* Einfuegen eines Arguments in die Argumentliste			*/
/************************************************************************/
void ArguList_insert(ArguList *list, ArgLEP ptr)
{
if (list->anzahl == 0)
	{
	list->first = ptr;
	list->last = ptr;
	ptr->prev = NULL;
	ptr->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	ptr->prev=list->last;
	list->last->next=ptr;
	ptr->next=NULL;
	list->last = ptr;
	}
list->anzahl++;
}


/************************************************************************/
/* InputList_insert (Pass2)						*/
/*									*/
/* Einfuegen einer Aktion in die Inputliste				*/
/************************************************************************/
void InputList_insert(InputList *list, SemLEP sem, ALEP attr)
{
ILEP ptr = (ILEP)malloc(sizeof(ILE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(0);
	}

ptr->aktion = sem;
ptr->attr = attr;

if (list->anzahl == 0)
	{
	list->first = ptr;
	list->last = ptr;
	ptr->prev = NULL;
	ptr->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	ptr->prev=list->last;
	list->last->next=ptr;
	ptr->next=NULL;
	list->last = ptr;
	}
list->anzahl++;
}


/************************************************************************/
/* NameList_insert							*/
/*									*/
/* Eintragen eines neuen Ergebnisses in die Namelist			*/
/************************************************************************/
void NameList_insert(NameList *list, struct argument *res)
{
NLEP ptr = (NLEP)calloc(1, sizeof(NLE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

strcpy(ptr->attr, res->attr);
strcpy(ptr->symbol, res->symbol);
ptr->id = res->id;

if (list->anzahl == 0)
	{
	list->first = ptr;
	list->last = ptr;
	ptr->prev = NULL;
	ptr->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	ptr->prev=list->last;
	list->last->next=ptr;
	ptr->next=NULL;
	list->last = ptr;
	}
list->anzahl++;
}


/************************************************************************/
/* SemList_insert (Pass1)						*/
/*									*/
/* Eintragen einer neuen Aktion in die Aktionenliste			*/
/************************************************************************/
SemLEP SemList_insert(SemList *list, struct funktion *aktion)
{
SemLEP ptr = (SemLEP)calloc(1, sizeof(SemLE));

if (ptr == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

strcpy(ptr->aktion, aktion->aktion);
ptr->id = aktion->id;

if (list->anzahl == 0)
	{
	list->first = ptr;
	list->last = ptr;
	ptr->prev = NULL;
	ptr->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	ptr->prev=list->last;
	list->last->next=ptr;
	ptr->next=NULL;
	list->last = ptr;
	}
list->anzahl++;
return ptr;
}


/************************************************************************/
/* TEPList_insert (Pass1)						*/
/*									*/
/* Eintragen eines Sohnes in die Liste					*/
/************************************************************************/
TEPLEP TEPList_insert(TEPList *list, TEP tep)
{
TEPLEP teplep = (TEPLEP)calloc(1, sizeof(TEPLE));
if (teplep == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

teplep->symbol = tep;
if (list->anzahl == 0)		/* Leere Liste */
	{
	list->first = teplep;
	list->last = teplep;
	teplep->prev = NULL;
	teplep->next=NULL;
	}
else				/* Hinten anhaengen */
	{
	teplep->prev=list->last;
	list->last->next=teplep;
	teplep->next=NULL;
	list->last = teplep;
	}
list->anzahl++;
return teplep;
}


/************************************************************************/
/* xlist_insert 							*/
/*									*/
/* sortiertes Einfuegen eines Eintrages in die x_list			*/
/************************************************************************/
void xlist_insert(XLEP ptr, x_list *list)
{
XLEP cursor;

/* Ist die Liste noch leer?			*/
if (list->anzahl == 0)
	{
	list->first_min = list->first_max = ptr;
	ptr->next_min = ptr->next_max = NULL;
	}
else
	{
	/* Zuerst suchen wir die Minima-Liste durch	*/
	if (ptr->x_min < list->first_min->x_min)
		{
		ptr->next_min = list->first_min;
		list->first_min = ptr;
		}
	else
		{
		cursor = list->first_min;
		while (cursor->next_min)
			{
			if (ptr->x_min < cursor->next_min->x_min)
				{
				ptr->next_min = cursor->next_min;
				cursor->next_min = ptr;
				break;
				}
			cursor = cursor->next_min;
			}
		if (cursor->next_min == NULL)
			{
			ptr->next_min = NULL;
			cursor->next_min = ptr;
			}
		}

	/* Jetzt die Maxima-Liste			*/
	if (ptr->x_max < list->first_max->x_max)
		{
		ptr->next_max = list->first_max;
		list->first_max = ptr;
		}
	else
		{
		cursor = list->first_max;
		while (cursor->next_max)
			{
			if (ptr->x_max < cursor->next_max->x_max)
				{
				ptr->next_max = cursor->next_max;
				cursor->next_max = ptr;
				break;
				}
			cursor = cursor->next_max;
			}
		if (cursor->next_max == NULL)
			{
			ptr->next_max = NULL;
			cursor->next_max = ptr;
			}
		}
	}

list->anzahl++;
}


/************************************************************************/
/* free_ANList								*/
/*									*/
/* Der Speicher einer ANlist wird freigegeben				*/
/************************************************************************/
void free_ANList(ANList *list)
{
ANLEP ptr, help;

ptr = list->first;
while (ptr)
	{
	help = ptr->next;
	free (ptr);
	ptr=help;
	}

list->anzahl = 0;
list->first =NULL;
}


/************************************************************************/
/* free_NameList							*/
/*									*/
/* Der Speicher einer Namelist wird freigegeben 			*/
/************************************************************************/
void free_NameList(NameList *list)
{
NLEP ptr, help;

ptr = list->first;
while (ptr)
	{
	help = ptr->next;
	free (ptr);
	ptr=help;
	}

list->anzahl = 0;
list->first =NULL;
list->last  =NULL;
}


/************************************************************************/
/* Sem_remove (Pass1)							*/
/*									*/
/* entfernt eine Aktion aus der Aktionenliste				*/
/************************************************************************/
void Sem_remove(SemList *list, SemLEP cursor)
{
/* Entfernen der Ergebnisliste	*/
free_NameList(&cursor->result_name);

/* Die Argumentlisten sind zu diesem Zeitpunkt noch leer!	*/

/* Cursor wird entfernt */
if (cursor == list->last)
	list->last = cursor->prev;	/* Der existiert sicher */
else
	cursor->next->prev = cursor->prev;

cursor->prev->next = cursor->next;
free(cursor);
}


/************************************************************************/
/* sort_AList (Pass1)							*/
/*									*/
/* Fuer den Anordnungsalgorithmus muessen inherited und derived Attri-	*/
/* bute sortiert vorliegen, jeweils vom Knoten nach aussen		*/
/************************************************************************/
void sort_AList(AList *list, char mode)
{
ALEP ptr;
ALEP cursor;

if (list)
	{
	ptr = list->first;
	while (ptr)
		{
		cursor = ptr->next;
		while (cursor)
			{
			if (	(mode == 'D' && cursor->x < ptr->x) ||
				(mode == 'I' && cursor->x > ptr->x)     )
				{
				/* Hole cursor nach vorne	*/
				if (ptr == list->first)
					list->first = cursor;
				else
					ptr->prev->next = cursor;

				if (cursor == list->last)
					list->last = cursor->prev;
				else
					cursor->next->prev = cursor->prev;

				cursor->prev->next = cursor->next;
				cursor->prev = ptr->prev;
				cursor->next = ptr;
				ptr->prev = cursor;

				ptr = cursor;
				}
			cursor = cursor->next;
			}
		ptr = ptr->next;
		}
	}
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Ausgabefunktionen zum Debuggen				       **/
/**								       **/
/************************************************************************/
/************************************************************************/

void print_x_union(union xunion *info, XLEP x)
{
switch (x->art)
	{
	case 'T':
		printf("Knoten %s, x_min = %d, x_max = %d, y_min = %d\n", info->t_element->symbol, x->x_min, x->x_max, x->y_min);
		break;
	case 'A':
		printf("Attribut %s, x_min = %d, x_max = %d, y_min = %d\n", info->a_element->attr, x->x_min, x->x_max, x->y_min);
		break;
	case 'S':
		printf("Aktion %s, x_min = %d, x_max = %d, y_min = %d\n", info->s_element->aktion, x->x_min, x->x_max, x->y_min);
		break;
	default:
		printf("Unbekannter Eintrag in xlist: %c\n", x->art);
	}
}


void print_x_list(x_list *list)
{
XLEP ptr;

printf("\n\nListe nach Minima sortiert:\n");
ptr = list->first_min;
while (ptr)
	{
	print_x_union(&ptr->info, ptr);
	ptr = ptr->next_min;
	}

printf("\n\nListe nach Maxima sortiert:\n");
ptr = list->first_max;
while (ptr)
	{
	print_x_union(&ptr->info, ptr);
	ptr = ptr->next_max;
	}
}


void print_ArguList(list)
ArguList *list;
{
ArgLEP ptr = list->first;

while(ptr)
	{
	if (ptr->attr)
		printf("\t\t\t%s\n", ptr->attr->attr);
	else
		printf("\t\t\t%s\n", ptr->terminal->symbol);
	ptr=ptr->next;
	}
}


void print_aktion(list)
SemList *list;
{
SemLEP ptr = list->first;

while (ptr)
	{
	printf("\t\tSem. Aktion: %s (%d/%d)\n", ptr->aktion, ptr->x, ptr->y);
	printf("\t\t\tArgumente:\n");
	print_ArguList(&ptr->argumente);
	printf("\t\t\tErgebnisse:\n");
	print_ArguList(&ptr->results);

	ptr=(SemLEP)ptr->next;
	}
}


void print_attr(list)
AList *list;
{
ALEP ptr = list->first;

while (ptr)
	{
	printf("\t\tAttribut: %s (%d/%d),  ", ptr->attr, ptr->x, ptr->y);
	if (ptr->copy_of)
		{
		if (ptr->copy_of->attr)
			printf("Zuweisung von %s\n", ptr->copy_of->attr->attr);
		else
			printf("Zuweisung von %s\n", ptr->copy_of->terminal->symbol);
		}
	else
		{
		printf("Ergebnis von %s\n", ptr->result_of->aktion);
		}
	printf("\t\tinputs: %d, Image: %d\n", ptr->input_to.anzahl, ptr->image);
	ptr=ptr->next;
	}
}


void print_tree(t)
TEP t;
{
TEPLEP ptr;

if (t)
	{
	printf("Knoten: %s  (%d/%d),  links: %d, rechts: %d\n", t->symbol, t->x, t->y, t->breite_links, t->breite_rechts);
	if (t->is_terminal)
		printf("Terminal: inputs: %d\n", t->input_to.anzahl);
	else
		{
		printf("\tAuxiliaries:\n");
		print_attr(&t->aattr);
		printf("\tInherited:\n");
		print_attr(&t->iattr);
		printf("\tDerived:\n");
		print_attr(&t->dattr);
		printf("\tSem. Aktionen:\n");
		print_aktion(&t->aktionen);

		ptr = t->soehne.first;
		while (ptr)
			{
			print_tree(ptr->symbol);
			ptr = ptr->next;
			}
		printf("--------------\n");
		}
	}
else
	printf("Leerer Baum\n");
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zur Behandlung semantischer Aktionen		       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* NameList_cmp 							*/
/*									*/
/* Vergleich zweier Namelists						*/
/************************************************************************/
int NameList_cmp(NameList *x, NameList *y)
{
NLEP px, py;

/* Die Ergebnisse stehen in der gleichen Reihenfolge		*/
px=x->first;
py=y->first;

/* Beide Listen muessen gleich lang sein, da es sich um die	*/
/* gleiche semantische Aktion handelt!				*/
while (px && py)
	{
	if (px->id != py->id)
		return 1;
	if (strcmp(px->symbol, py->symbol) != 0)
		return 1;
	if (strcmp(px->attr, py->attr) != 0)
		return 1;

	px = px->next;
	py = py->next;
	}

return 0;		/* Gleichheit!	*/
}


/************************************************************************/
/* remove_multiple_action (Pass1)					*/
/*									*/
/* Funktion zum Entfernen doppelter semantischer Aktionen		*/
/* D.h. Semantische Aktionen, die mehrere Ergebnisse liefern,		*/
/* stehen mehrmals in der Liste, was unnoetig ist.			*/
/************************************************************************/
void remove_multiple_action(SemList *list)
{
SemLEP base, cursor;

base = list->first;
while (base)
	{
	if (base->result_name.anzahl >1)	/* Das ist so ein Fall	*/
		{
		cursor = base->next;		/* Cursor zum Suchen	*/
		while (cursor)
			{
			if (base->id == cursor->id)	/* gleiche Aktion */
				if (NameList_cmp(&base->result_name, &cursor->result_name) == 0)	/* Gleichheit!	*/
					{
					Sem_remove(list, cursor);
					break;
					}
			cursor= cursor->next;
			}
		}
	base = base->next;
	}
}


/************************************************************************/
/* hole_aktion (Pass1)							*/
/*									*/
/* Eintragen einer semantischen Aktion, Aufbau der Namensliste der	*/
/* Ergebnisse, um doppelte identifizieren zu koennen			*/
/************************************************************************/
void hole_aktion(TEP tep, union satz_info *s, FILE *fp)
{
SemLEP ptr;

/* Zuerst wird die Aktion eingetragen */
ptr = SemList_insert(&tep->aktionen, &s->f);

/* Ergebnisse und Argumente werden erst in Pass 2 eingetragen	*/

while (hole_satz(s, fp) == 'G')         /* Holen der Ergebnisse */
	NameList_insert(&ptr->result_name, &s->g);

while (hole_satz(s, fp) != 'E');
	/* Holen der Argumente	*/

/* Aktionen mit mehreren Ergebnissen kommen mehrmals vor	*/
remove_multiple_action(&tep->aktionen);
}


/************************************************************************/
/* get_funk_ptr (Pass2) 						*/
/*									*/
/* berechnet den Zeiger auf die semantische Aktion, die durch ihre	*/
/* Ergebnisse eindeutig festgelegt ist. 				*/
/* Ausserdem wird die Parameterliste aufgebaut. 			*/
/************************************************************************/
SemLEP get_funk_ptr(TEP akt_vater, struct funktion *f, FILE *fp)
{
union satz_info s;
NameList nl;
SemLEP sptr;
ArgLEP aptr;

nl.anzahl=0;
nl.first=NULL;
nl.last=NULL;

/* Zuerst bauen wir die Namensliste der Ergebnisse auf	*/
while (hole_satz(&s, fp) == 'G')                /* Holen der Ergebnisse */
	NameList_insert(&nl, &s.g);

/* Damit suchen wir die richtige Aktion beim Vater	*/
sptr = akt_vater->aktionen.first;
while (sptr)
	{
	if (strcmp(sptr->aktion, f->aktion) == 0)
		if (NameList_cmp(&nl, &sptr->result_name) == 0)
			break;
	sptr = sptr->next;
	}

/* Die Namesliste kann weggeworfen werden				*/
free_NameList(&nl);

/* Jetzt wird die Argumentliste fuer die Argumente			*/
/* aufgebaut und die Pointer besetzt					*/
while (hole_satz(&s, fp) == 'G')                /* Holen der Argumente  */
	{
	aptr = get_arg_ptr(akt_vater, &s.g);
	ArguList_insert(&sptr->argumente, aptr);
	if (aptr->attr)
		InputList_insert(&aptr->attr->input_to, sptr, NULL);
	else
		InputList_insert(&aptr->terminal->input_to, sptr, NULL);
	}

/* Die Adresse der Aktion wird zurueckgegeben				*/
return sptr;
}


/************************************************************************/
/* platz_fuer_aux (Pass2)						*/
/*									*/
/* berechnet den Platz in Pixeln, die die Auxiliaries rechts von einer	*/
/* semantischen Aktion brauchen 					*/
/************************************************************************/
int platz_fuer_aux(SemLEP akt)
{
ArgLEP arg = akt->results.first;
int count =0;

while (arg)
	{
	if (arg->attr && arg->attr->art == 'A')
		count ++;

	arg = arg->next;
	}

if (count == 0)
	return 0;
else
	return IMAGE_BORDER + (count-1)*IMAGE_SPACE + count*IMAGE_WIDTH;
}


/************************************************************************/
/* sem_aux_layout (Pass2)						*/
/*									*/
/* Anordnen der Auxiliaries, die das Ergebnis eine semantischen Aktion	*/
/* aufnehmen								*/
/************************************************************************/
void sem_aux_layout(SemList *list)
{
SemLEP akt = list->first;
ArgLEP arg;
int x;

while(akt)
	{
	arg = akt->results.first;
	x = IMAGE_BORDER;
	while(arg)
		{
		if (arg->attr)		/* Das muss immer so sein!	*/
			{
			if (arg->attr->art == 'A')
				{
				arg->attr->y = akt->y;
				arg->attr->x = akt->x_max + x;
				x += IMAGE_WIDTH + IMAGE_SPACE;
				}
			}
		arg = arg->next;
		}
	akt = akt->next;
	}
}


/************************************************************************/
/* move_sem_action (Pass2)						*/
/*									*/
/* Eine semantische Aktion wird verschoben				*/
/************************************************************************/
void move_sem_action(SemLEP ptr, int x, int y)
{
#ifdef DEBUG
	printf("Move: %s (%d/%d) (%d-%d), ->(%d/%d)\n", ptr->aktion, ptr->x, ptr->y, ptr->x_min, ptr->x_max, x, y);
#endif

ptr->x +=x;
ptr->x_min +=x;
ptr->x_max +=x;
ptr->y +=y;
}


/************************************************************************/
/* move_sem_block (Pass2)						*/
/*									*/
/* Der ganze bereits gesetzte Block von Aktionen wird verschoben	*/
/************************************************************************/
void move_sem_block(SemList *list, SemLEP ptr, int x, int y)
{
SemLEP akt = list->first;

if (x==0 && y==0)
	return;

#ifdef DEBUG
	printf("Beginn move_sem_block (%d/%d)\n", x, y);
#endif

if (x==0 && y==0)
	return;

while(akt && akt != ptr)
	{
	move_sem_action(akt, x, y);
	akt = akt->next;
	}
#ifdef DEBUG
	printf("End move_sem_block\n");
#endif
}


/************************************************************************/
/* collision (Pass2)							*/
/*									*/
/* Hier wird ermittelt, mit welcher Aktion die aktuelle kollidiert,	*/
/* falls sie um den Vektor (x/y)  und der schon gesetzte Aktionsblock	*/
/* um (bx/by) verschoben wird.						*/
/* Die Adresse der Aktion steht dann in res, die laufende Nummer wird	*/
/* zurueckgegeben							*/
/************************************************************************/
int collision(SemLEP akt, SemList *list, int x, int y, int bx, int by, SemLEP *res)
{
SemLEP ptr;
int count =0;
int x_aux = platz_fuer_aux(akt);
int p_aux;

#ifdef DEBUG
	printf("Collision: Aktion (%d/%d), Block (%d/%d)\n", x, y, bx, by);
#endif

ptr = list->first;
while (ptr && ptr != akt)	/* alle schon gesetzten durchlaufen	*/
	{
	p_aux = platz_fuer_aux(ptr);
	if (	akt->y + y + SEM_HEIGHT + SEM_Y_SPACE <= ptr->y + by	/* drueber	*/
	   ||	akt->y + y >= ptr->y + by + SEM_HEIGHT + SEM_Y_SPACE	/* drunter	*/
	   ||	akt->x_max + x_aux + x + SEM_X_SPACE <= ptr->x_min + bx 	/* links	*/
	   ||	akt->x_min + x >= ptr->x_max + p_aux + bx + SEM_X_SPACE )	/* rechts	*/
		{
		ptr = ptr->next;
		count++;
		}
	else			/* Kollision	*/
		{
		#ifdef DEBUG
		printf("Kollision: neu: %s mit %s\n", akt->aktion, ptr->aktion);
		#endif
		*res = ptr;
		return count;
		}
	}

*res = NULL;
return -1;
}


/************************************************************************/
/* check_sem_pos (Pass2)						*/
/*									*/
/* Diese Funktion verschiebt die Aktionen so, dass keine Ueberlappungen */
/* auftreten. Gleichzeitig werden Auxiliaries, die das Ergebnis einer	*/
/* Aktion aufnehmen, rechts neben der Aktion plaziert.			*/
/************************************************************************/
void  check_sem_pos(TEP akt_vater)
{
int rechts, links, oben, unten;
int x_min, x_max, y_min, y_max;
int x_aux, p_aux;
int highest_kollision;
int move_x, move_y;
int move[4][2];
int move_block[4][2];
int move_block_x, move_block_y;
int block_x_min, block_x_max;
int block_y_min, block_y_max;
int kollision[4];
int links_ueber, rechts_ueber;
int bewertung;
int beste_wahl;
SemLEP kptr[4];
SemLEP akt, ptr;
int max_moves;
int i;

/* Zuerst werden linker und rechter Rand der Produktion bestimmt.	*/
/* Diese Grenzen sind nur Richtlinien, sie duerfen notfalls missachtet	*/
/* werden.								*/
if (akt_vater->soehne.anzahl >0)
	{
	x_min = akt_vater->soehne.first->symbol->x - akt_vater->soehne.first->symbol->breite_links;
	x_max = akt_vater->soehne.last->symbol->x + akt_vater->soehne.last->symbol->breite_rechts;
	}
else
	{
	x_min = akt_vater->x - akt_vater->breite_links;
	x_max = akt_vater->x + akt_vater->breite_rechts;
	}

/* Die Grenzen in y-Richtung sind fest vorgeschrieben, weil sonst die	*/
/* Attribute und Knoten ueberschrieben werden.				*/
y_min = akt_vater->y + IMAGE_HEIGHT + IMAGE_Y_SPACE;
y_max = akt_vater->y + PROD_HEIGHT - SEM_HEIGHT - IMAGE_Y_SPACE;

/* Jetzt koennen die Speilraeume nach jeder Seite berechnet werden	*/
block_x_min = x_max;
block_y_min = y_max;
block_x_max = x_min;
block_y_max = y_min;

#ifdef DEBUG
	printf("Vater: %s\n", akt_vater->symbol);
	printf("Breite: %d - %d\n", x_min, x_max);
	printf("Hoehe:  %d - %d\n", y_min, y_max);
#endif

akt = akt_vater->aktionen.first;
while (akt)
	{
	max_moves = akt_vater->aktionen.anzahl;
	x_aux = platz_fuer_aux(akt);

	/* Die neue Aktion wird in den Rahmen gerueckt		*/
	if (akt->y > y_max)
		akt->y = y_max;
	if (akt->y < y_min)
		akt->y = y_min;

	if (akt->x_max + x_aux >x_max && akt->x_min >x_min)	/* Man kann nach links ruecken! */
		move_sem_action(akt, -MIN(akt->x_min - x_min, akt->x_max + x_aux - x_max), 0);
	if (akt->x_max + x_aux <x_max && akt->x_min <x_min)	/* Man kann nach rechts ruecken! */
		move_sem_action(akt, MIN(x_min - akt->x_min, x_max - (akt->x_max + x_aux)), 0);
	if (akt->x_max + x_aux >= x_max && akt->x_min <= x_min) /* weingstens zentrieren	*/
		move_sem_action(akt, (x_min - akt->x_min - (akt->x_max + x_aux) + x_max) /2, 0);

	if (akt->x_min < X_START)				/* das ist nicht mehr im Fenster	*/
		move_sem_action(akt, -akt->x_min, 0);

#ifdef DEBUG
	printf("Aktion %s (%d/%d) im Rahmen: %d - %d\n", akt->aktion, akt->x, akt->y, akt->x_min, akt->x_max + x_aux);
#endif

/* Hier muss die Ueberpruefung auf Kollision mit anderen Aktionen kommen! */
	move_x =0;
	move_y =0;
	move_block_x =0;
	move_block_y =0;
	while ((collision(akt, &akt_vater->aktionen, move_x, move_y, move_block_x, move_block_y, &ptr) != -1) && max_moves != 0)
		{
		p_aux = platz_fuer_aux(ptr);

		/* Wieviel Platz ist nach jeder Seite?		*/
		oben = block_y_min - y_min;
		unten = y_max - block_y_max;
		rechts = x_max - block_x_max;
		links = block_x_min - x_min;

		#ifdef DEBUG
			printf("Spielraum: oben: %d, unten: %d, links: %d, rechts: %d\n", oben, unten, links, rechts);
		#endif

		/* Verschiebung nach oben	*/
		move[0][0] = move_x;
		move[0][1] = move_y + ptr->y + move_block_y - SEM_Y_SPACE - SEM_HEIGHT - (akt->y + move_y);
		move_block[0][0] = move_block_x;
		move_block[0][1] = move_block_y;

		kollision[0] = collision(akt, &akt_vater->aktionen, move[0][0], move[0][1], move_block_x, move_block_y, &kptr[0]);
		if (kollision[0] == -1) 	/* keine Kollision	*/
			{
			/* Jetzt schauen wir, ob ueberhaupt Platz waere */
			if (akt->y + move[0][1] < y_min)
				if (unten < y_min - (akt->y + move[0][1]))
					kollision[0] = -2;	/* NEIN! */
				else
					{
					move_block[0][1] += y_min - (akt->y + move[0][1]);
					move[0][1] += y_min - (akt->y + move[0][1]);
					}
			}

		/* Verschiebung nach unten	*/
		move[1][0] = move_x;
		move[1][1] = move_y + ptr->y + move_block_y + SEM_Y_SPACE + SEM_HEIGHT - (akt->y + move_y);
		move_block[1][0] = move_block_x;
		move_block[1][1] = move_block_y;

		kollision[1] = collision(akt, &akt_vater->aktionen, move[1][0], move[1][1], move_block_x, move_block_y, &kptr[1]);
		if (kollision[1] == -1) 	/* keine Kollision	*/
			{
			/* Jetzt schauen wir, ob ueberhaupt Platz waere */
			if (akt->y + move[1][1] > y_max)
				if (oben < akt->y + move[1][1] -y_max)
					kollision[1] = -2;	/* NEIN! */
				else
					{
					move_block[1][1] -= akt->y + move[1][1] -y_max;
					move[1][1]  -= akt->y + move[1][1] -y_max;
					}
			}

		/* Verschiebung nach rechts	*/
		move[2][0] = move_x + ptr->x_max + p_aux + move_block_x - (akt->x_min + move_x) + SEM_X_SPACE;
		move[2][1] = move_y;
		move_block[2][0] = move_block_x;
		move_block[2][1] = move_block_y;

		kollision[2] = collision(akt, &akt_vater->aktionen, move[2][0], move[2][1], move_block_x, move_block_y, &kptr[2]);
		if (kollision[2] == -1) 	/* keine Kollision	*/
			{
			/* Jetzt schauen wir, ob ueberhaupt Platz waere */
			/* Sollte die Aktion nicht reinpassen, merken wir uns,
			   wie weit sie uebersteht und alles andere und machen
			   weiter!		*/
			rechts_ueber = 0;
			if (akt->x_max + x_aux + move[2][0] > x_max)
				if (links < akt->x_max + x_aux + move[2][0] -x_max)
					{
					rechts_ueber = akt->x_max + x_aux + move[2][0] -x_max-rechts;
					move_block[2][0] -= links;
					move[2][0] -= links;
					}
				else
					{
					move_block[2][0] += akt->x_max + x_aux + move[2][0] -x_max;
					move[2][0] -= akt->x_max + x_aux + move[2][0] -x_max;
					}
			}

		/* Verschiebung nach links	*/
		move[3][0] = move_x + ptr->x_min + move_block_x - (akt->x_max + x_aux + move_x) - SEM_X_SPACE;
		move[3][1] = move_y;
		move_block[3][0] = move_block_x;
		move_block[3][1] = move_block_y;

		kollision[3] = collision(akt, &akt_vater->aktionen, move[3][0], move[3][1], move_block_x, move_block_y, &kptr[3]);
		if (kollision[3] == -1) 	/* keine Kollision	*/
			{
			/* Jetzt schauen wir, ob ueberhaupt Platz waere */
			/* Sollte die Aktion nicht reinpassen, merken wir uns,
			   wie weit sie uebersteht und alles andere und machen
			   weiter!		*/
			links_ueber = 0;
			if (akt->x_min + move[3][0] < x_min)
				if (rechts < x_min - (akt->x_min + move[3][0]))
					{
					links_ueber = x_min - (akt->x_min + move[3][0]) - links;
					move_block[3][0] -= rechts;
					move[3][0] -= rechts;

		/* Wir duerfen das Fenster nicht verlassen!	*/
					if (x_min - links_ueber < X_START)
						kollision[3] = -2;
					}
				else
					{
					move_block[3][0] += (x_min - (akt->x_min + move[3][0]));
					move[3][0] += (x_min - (akt->x_min + move[3][0]));
					}
			}

		/* Ist ein Totpunkt erreicht?		*/
		if (	kollision[0] == -2 &&
			kollision[1] == -2 &&
			kollision[2] == -2 &&
			kollision[3] == -2	)
			{
			max_moves = 0;		/* Anzeichen fuer Totpunkt! */
			break;
			}

		/* Wurde ein freier Platz gefunden?	*/
		if (kollision[0] == -1) 	/* Nach oben ist Platz */
			{
			move_y = move[0][1];
			move_block_y = move_block[0][1];
			break;
			}
		if (kollision[1] == -1) 	/* Nach unten ist Platz */
			{
			move_y = move[1][1];
			move_block_y = move_block[1][1];
			break;
			}

		if (kollision[2] == -1 && kollision[3] == -1)
			{
			if (links_ueber < rechts_ueber)
				{
				move_x = move[3][0];
				move_block_x = move_block[3][0];
				}
			else
				{
				move_block_x = move_block[2][0];
				move_x = move[2][0];
				}
			break;
			}

		if (kollision[2] == -1) 	/* Nach rechts ist Platz */
			{
			move_x = move[2][0];
			move_block_x = move_block[2][0];
			break;
			}


		if (kollision[3] == -1) 	/* Nach links ist Platz */
			{
			move_x = move[3][0];
			move_block_x = move_block[3][0];
			break;
			}

		/* Wir haben hier also keinen freien Platz gefunden, sonst */
		/* waeren wir auf ein break gestossen. Ein Totpunkt ist    */
		/* aber auch nicht erreicht!				   */

		/* Auswahl der besten Kollision 			*/
		/* Wir suchen die Kollision mit der hoechsten Nummer.	*/
		/* Dabei soll aber ein ueberstehen ueber die Raender	*/
		/* der Produktion vermieden werden.			*/

		/* Eine gute Bewertung enthaelt eine moeglichst kleine	*/
		/* Zahl. Daher werden die Kollisionsnummern negativ	*/
		/* eingetragen, ueberstehende Pixel positiv.		*/

		bewertung = MAXIMUM;

		for (i=3; i>=0; i--)
			{
			if(kollision[i] != -2)
				switch (i)
					{
					case 3: 	/* nach links	*/
						if (links_ueber > 0)
							bewertung = links_ueber;
						else
							bewertung = -kollision[i];
						beste_wahl = i;
						break;
					case 2: 	/* nach rechts	*/
						if (rechts_ueber >0)
							{
							if (rechts_ueber < bewertung)
								{
								bewertung = rechts_ueber;
								beste_wahl = i;
								}
							}
						else
							if (kollision[i] > -bewertung)
								{
								bewertung = -kollision[i];
								beste_wahl = i;
								}
						break;
					default:
						if (kollision[i] > -bewertung)
							{
							bewertung = -kollision[i];
							beste_wahl = i;
							}
					}
			}


		/* Besetzung von move_x, move_y, ...			*/
		move_x = move[beste_wahl][0];
		move_y = move[beste_wahl][1];
		move_block_x = move_block[beste_wahl][0];
		move_block_y = move_block[beste_wahl][1];


		/* Der Zaehler max_moves verhindert Endlosschleifen,	*/
		/* die bei diesem Algorithmus auftauchen koenen, aber	*/
		/* sehr unwahrscheinlich sind!				*/
		max_moves--;
		}

	/* Setzen der neuen Aktion ------------------------------------ */
	/* Warum wurde die Schleife abgebrochen?			*/
	if (max_moves == 0)		/* Totpunkt	*/
		{
		;
		}
	else				/* Platz gefunden	*/
		{
		move_sem_action(akt, move_x, move_y);
		move_sem_block(&akt_vater->aktionen, akt, move_block_x, move_block_y);
		block_x_max += move_block_x;
		block_x_min += move_block_x;
		block_y_max += move_block_y;
		block_y_min += move_block_y;
		}

	/* Ueberschreitet die neue Aktion die alten Grenzen?		*/
	block_x_max = MAX(block_x_max, akt->x_max + x_aux);
	block_x_min = MIN(block_x_min, akt->x_min);
	block_y_max = MAX(block_y_max, akt->y);
	block_y_min = MIN(block_y_min, akt->y);

#ifdef DEBUG
	printf("\tAktion %s (%d/%d) gesetzt: %d - %d\n", akt->aktion, akt->x, akt->y, akt->x_min, akt->x_max);
#endif

	akt = akt->next;
	}

/* Jetzt sind alle Aktionen endgueltig plaziert, wir koennen nun also	*/
/* die zugehoerigen Auxiliaries anordnen				*/
sem_aux_layout(&akt_vater->aktionen);
}


/************************************************************************/
/* sem_layout (Pass2)							*/
/*									*/
/* Anordnung der semantischen Aktionen durch Schwerpunktbildung von	*/
/* Argumenten und Ergebnissen (ausser Auxiliaries)			*/
/************************************************************************/
void sem_layout(TEP akt_vater)
{
int x, y;
int breite;
ArgLEP arg_ptr;
SemLEP ptr = akt_vater->aktionen.first;
int count;

while (ptr)
	{
	x=0;
	y=0;
	count = 0;
	/* Wir berechnen die Mitte aller beteiligten Argumente	*/
	/* Ausgenommen sind Auxiliaries, die direkt neben der	*/
	/* semantischen Aktion plaziert werden. 		*/
	arg_ptr = ptr->argumente.first;
	while (arg_ptr)
		{
		if (arg_ptr->attr)		/* Attribut	*/
			{
			if (arg_ptr->attr->art != 'A')
				{
				x+= arg_ptr->attr->x;
				y+= arg_ptr->attr->y;
				count++;
				}
			}
		else				/* Terminal	*/
			{
			x+= arg_ptr->terminal->x;
			y+= arg_ptr->terminal->y;
			count++;
			}
		arg_ptr = arg_ptr->next;
		}

	arg_ptr = ptr->results.first;
	while (arg_ptr)
		{
		if (arg_ptr->attr->art != 'A')
			{
			x+= arg_ptr->attr->x;
			y+= arg_ptr->attr->y;
			count++;
			}

		arg_ptr = arg_ptr->next;
		}

	if (count == 0) 	/* irgendwohin plazieren	*/
		{
		ptr->x = 0;
		ptr->y = akt_vater->y;
		}
	else
		{
		ptr->x = x/count + IMAGE_WIDTH /2;
		ptr->y = y/count;
		}
	breite = SEM_WIDTH(strlen(ptr->aktion));
	ptr->x_min = ptr->x - breite/2;
	ptr->x_max = ptr->x + breite/2;

	ptr= ptr->next;
	}

/* Jetzt wird ueberprueft, ob sich Aktionen ueberlappen (->Verschieben) */
/* Gleichzeitig werden die Auxiliaries angeordnet			*/
check_sem_pos(akt_vater);
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zur Behandlung von Attributen			       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* get_image								*/
/*									*/
/* Diese Funktion vergibt die Images fuer die einzelnen Attribute.	*/
/* Sie kann dafuer auf das Konfig-File zugreifen, bzw. die eingebauten	*/
/* Images nutzen, evtl. selbst Images generieren.			*/
/************************************************************************/
int get_image(ALEP a, ANList *list)
{
int slen = strlen(a->attr) + 1; 
char *attr_str = (char *) malloc(slen), *remind = attr_str;
ANLEP ptr = list->first;

if (attr_str == NULL) {
	printf("not enough memory!\n");
	exit(1);
	}

strcpy(attr_str, a->attr);
if ((*attr_str == 'a' && a->art == 'A') ||
   (*attr_str == 'd' && a->art == 'D') ||
   (*attr_str == 'i' && a->art == 'I')) 
	attr_str++;

while (ptr && strcmp(ptr->attr, attr_str) != 0)
	ptr = ptr->next;

free(remind);
if (ptr == NULL)		/* nicht gefunden	*/
	return -1;
else				/* Image zuweisen	*/
	return ptr->nr;
}


/************************************************************************/
/* hole_attribute (Pass1)						*/
/*									*/
/* Aufbau der Attributlisten, Holen des Attributwerts			*/
/************************************************************************/
void hole_attribute(TEP akt_knoten, char attr_art, union satz_info *s, ANList *list, FILE *fp)
{
char c;
ALEP ptr;

while ((c= hole_satz(s, fp)) == 'A')
	{
	switch (attr_art)
		{
		case 'A':
			ptr= AList_insert(&akt_knoten->aattr, &s->a, list, akt_knoten);
			break;
		case 'D':
			ptr= AList_insert(&akt_knoten->dattr, &s->a, list, akt_knoten);
			break;
		case 'I':
			ptr= AList_insert(&akt_knoten->iattr, &s->a, list, akt_knoten);
			break;
		default:
			printf("Illegal Type of Attribute\n");
			exit(0);
		}
	/* Jetzt holen wir den Wert des Attributs */
	ptr->wert = malloc(ptr->wertlen);
	if (ptr->wert == NULL)
		{
		printf("Not enough memory!\n");
		exit(1);
		}
	fread(ptr->wert, ptr->wertlen, 1, fp);

	/* Jetzt schauen wir, wie es berechnet wird */
	switch (hole_satz(s, fp))
		{
		case 'F':               /* Semantische Aktion   */
			if (attr_art == 'I')    /* Die gehoeren zum Sohn */
				hole_aktion(akt_knoten->vater, s, fp);
			else
				hole_aktion(akt_knoten, s, fp);
			break;
		case 'G':               /* Zuweisung                    */
					/* Bearbeitung im Pass 2	*/
			break;
		default:
			printf("Illegal entry!\n");
			exit(0);
		}
	}

if (c != 'E')
	{
	printf("Illegal entry in attributelist\n");
	exit(0);
	}
}


/************************************************************************/
/* is_pair (Pass1)							*/
/*									*/
/* prueft, ob die beiden Attribute korrespondieren			*/
/************************************************************************/
int is_pair(ALEP a, ALEP b, int start)
{
if (strcmp(a->attr+start, b->attr+start) == 0)
	return 1;

return 0;
}


/************************************************************************/
/* find_pair (Pass1)							*/
/*									*/
/* sucht zum angegebenen Attribut ein korrespondierendes in der Liste	*/
/* evtl. wird eine Imagenummer vergeben, falls ein Paar gefunden wird	*/
/************************************************************************/
ALEP find_pair(ALEP attr, AList *list, int start)
{
ALEP ptr;

if (list)
	{
	ptr=list->first;
	while (ptr)
		{
		if (is_pair(attr, ptr, start))
			return ptr;

		ptr =ptr->next;
		}
	}

return NULL;
}


/************************************************************************/
/* aux_layout (Pass1)							*/
/*									*/
/* Diejenigen (eigentlich ueberfluessigen Auxiliaries, die nicht das	*/
/* Ergebnis einer semantischen Aktion speichern, werden rechts von den	*/
/* derived Attributen dargestellt.					*/
/************************************************************************/
int aux_layout(AList *list, TEP knoten)
{
ALEP ptr = list->first;
int x = knoten->breite_rechts + 2*IMAGE_BORDER;
int count =0;

while (ptr)
	{
	if (ptr->result_of == NULL)	/* Kein Ergebnis	*/
		{
		ptr->x = x;
		ptr->y = knoten->y;
		x += IMAGE_WIDTH + IMAGE_SPACE;
		count++;
		}
	ptr=ptr->next;
	}

if (count == 0)
	return 0;
else
	return 2*IMAGE_BORDER + count*IMAGE_WIDTH + (count-1)*IMAGE_SPACE;
}


/************************************************************************/
/* attr_layout (Pass1)							*/
/*									*/
/* Anordnung der inherited und derived Attribute			*/
/* 1. derived Attribute in gleicher Reihenfolge wie beim Vater		*/
/* 2. zugehoerige inherited spiegelbildlich zum Knoten			*/
/* 3. restliche inherited wie beim Vater, soweit vorhanden		*/
/************************************************************************/
void attr_layout(AList *inh, AList *der, TEP akt_vater, TEP akt_sohn)
{
ALEP iptr, dptr;
ALEP vptr;
int xi, xd;

xi = -KNOTEN_WIDTH(strlen(akt_sohn->symbol)) /2 - IMAGE_BORDER - IMAGE_WIDTH;
xd = KNOTEN_WIDTH(strlen(akt_sohn->symbol)) /2 + IMAGE_BORDER;

/* Zuerst werden in beiden Listen alle x-Werte auf MINIMUM gesetzt, um	*/
/* anzuzeigen, dass der Wert noch nicht berechnet wurde 		*/
/* Gleichzeitig werden die y-Werte gesetzt				*/
dptr = der->first;
while (dptr)
	{
	dptr->x = MINIMUM;
	dptr->y = akt_sohn->y;
	dptr=dptr->next;
	}

if (inh)
	{
	iptr = inh->first;
	while (iptr)
		{
		iptr->x = MINIMUM;
		iptr->y = akt_sohn->y;
		iptr = iptr->next;
		}
	}

/* Wir durchlaufen die derived-Liste des Vaters 			*/
if (akt_vater)
	{
	vptr = akt_vater->dattr.first;
	while (vptr)
		{
		dptr = find_pair(vptr, der, 0);
		if (dptr)
			{
			dptr->x = xd;
			xd += IMAGE_WIDTH + IMAGE_SPACE;
			iptr = find_pair(dptr, inh, 1);
			if (iptr)
				{
				iptr->x = xi;
				xi -= (IMAGE_WIDTH + IMAGE_SPACE);
				}
			}
		vptr = vptr->next;
		}
	}

/* Jetzt werden alle restlichen derived-Attribute gesetzt		*/
dptr = der->first;
while (dptr)
	{
	if (dptr->x == MINIMUM) 	/* Noch nicht berechnet */
		{
		dptr->x = xd;
		xd += IMAGE_WIDTH + IMAGE_SPACE;
		iptr = find_pair(dptr, inh, 1);
		if (iptr)
			{
			iptr->x = xi;
			xi -= (IMAGE_WIDTH + IMAGE_SPACE);
			}
		}
	dptr =dptr->next;
	}

/* Jetzt werden die restlichen inherited-Attribute gesetzt		*/
/* Zuerst die, die auch beim Vater vorkommen				*/
if (akt_vater)
	{
	vptr = akt_vater->iattr.first;
	while (vptr)
		{
		iptr = find_pair(vptr, inh, 0);
		if (iptr && iptr->x == MINIMUM)
			{
			iptr->x = xi;
			xi -= (IMAGE_WIDTH + IMAGE_SPACE);
			}
		vptr =vptr->next;
		}
	}

/* Dann der Rest							*/
if (inh)
	{
	iptr = inh->first;
	while (iptr)
		{
		if (iptr->x == MINIMUM) /* Noch nicht berechnet */
			{
			iptr->x = xi;
			xi -= (IMAGE_WIDTH + IMAGE_SPACE);
			}
		iptr = iptr->next;
		}
	}

/* Die Liste muessen nach Koordinaten sortiert vorliegen!		*/
sort_AList(der, 'D');
sort_AList(inh, 'I');
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zum Baumaufbau					       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* ziehe_pfeil (Pass2)							*/
/*									*/
/* berechnet die Verknuepfungen zwischen Attributen, Terminals und	*/
/* semantischen Aktionen.						*/
/* Dabei werden gleich aus relativen Koordinaten der Attribute		*/
/* absolute gemacht.							*/
/************************************************************************/
void ziehe_pfeil(TEP akt_vater, TEP akt_sohn, union satz_info *s, FILE *fp)
{
ALEP attr_ptr;
ArgLEP arg_ptr;

/* Zuerst suchen wir das gelesene Attribut	*/
switch (s->a.art)
	{
	case 'A':
		attr_ptr = get_attr_ptr(&akt_vater->aattr, s->a.attr);
		break;
	case 'D':
		attr_ptr = get_attr_ptr(&akt_vater->dattr, s->a.attr);
		break;
	case 'I':
		attr_ptr = get_attr_ptr(&akt_sohn->iattr, s->a.attr);
		break;
	default:
		printf("Illegal type of attribute!\n");
		exit(0);
	}

/* Hier koennen wir gleich aus den relativen x-Koordinaten absolute	*/
/* machen, aber nicht bei Auxiliaries, ausser schon plazierten		*/
if (s->a.art != 'A' || (s->a.art == 'A' && attr_ptr->result_of == NULL))
	attr_ptr->x += akt_sohn->x;

/* Jetzt schauen wir, wie es berechnet wird */
switch (hole_satz(s, fp))
	{
	case 'G':
		arg_ptr = get_arg_ptr(akt_vater, &s->g);
		attr_ptr->copy_of = arg_ptr;
		if (arg_ptr->attr)
			InputList_insert(&arg_ptr->attr->input_to, NULL, attr_ptr);
		else
			InputList_insert(&arg_ptr->terminal->input_to, NULL, attr_ptr);

		break;
	case 'F':
		attr_ptr->result_of = get_funk_ptr(akt_vater, &s->f, fp);
		arg_ptr = ArgLE_alloc();
		arg_ptr->attr = attr_ptr;
		ArguList_insert(&attr_ptr->result_of->results, arg_ptr);
		break;
	default:
		printf("Illegal entry\n");
	}
}


/************************************************************************/
/* get_max (Pass1)							*/
/*									*/
/* berechnet den groessten x-Wert je Zeile im Teilbaum			*/
/************************************************************************/
void get_max(TEP links, int *max)
{
TEPLEP ptr;

if (links->x + links->breite_rechts > *max)
	*max = links->x + links->breite_rechts;

ptr = links->soehne.first;
while (ptr)
	{
	get_max(ptr->symbol, max+1);
	ptr = ptr->next;
	}
}


/************************************************************************/
/* get_min (Pass1)							*/
/*									*/
/* berechnet den kleinsten x-Wert je Zeile im Teilbaum			*/
/************************************************************************/
void get_min(TEP rechts, int *min)
{
TEPLEP ptr;

if (rechts->x - rechts->breite_links < *min)
	*min = rechts->x - rechts->breite_links;

ptr = rechts->soehne.first;
while (ptr)
	{
	get_min(ptr->symbol, min+1);
	ptr = ptr->next;
	}
}


/************************************************************************/
/* add_x_koord (Pass1)							*/
/*									*/
/* Verschiebt den kompletten Teilbaum in x-Richtung			*/
/************************************************************************/
void add_x_koord(TEP tree, int offset)
{
TEPLEP ptr;

tree->x +=offset;

ptr = tree->soehne.first;
while (ptr)
	{
	add_x_koord(ptr->symbol, offset);
	ptr = ptr->next;
	}
}


/************************************************************************/
/* layout (Pass1)							*/
/*									*/
/* berechnet die Anordnung zweier Teilbaeume				*/
/* Der modus entscheidet, ob das Layout beliebig ('A'ny) veraendert     */
/* oder nur verbreitert ('W'idth) werden darf                           */
/************************************************************************/
void layout(TEP links, TEP rechts, char modus)
{
int *max = (int *)calloc(links->baumhoehe+1, sizeof(int));
int *min = (int *)calloc(rechts->baumhoehe+1, sizeof(int));
int offset = MINIMUM;
int i;
int abstand;

if (max == NULL || min == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

/* Vorbelegung der Minima mit sehr grossen Werten	*/
for (i=0; i<rechts->baumhoehe+1; i++)
	min[i]=MAXIMUM;

/* Wir holen die groesste Ausdehnung je Zeile im Baum	*/
get_max(links, max);
get_min(rechts, min);

for (i=0; i<links->baumhoehe+1 && i<rechts->baumhoehe+1; i++)
	{
	abstand = min[i] - max[i];
	if (offset < PROD_SPACE-abstand)
		offset = PROD_SPACE-abstand;
	}

if (modus != 'W' || offset>0)
	add_x_koord(rechts, offset);

free(min);
free(max);
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Scanner / Parser						       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* scan_pass1								*/
/*									*/
/* Scanner/Parser Pass2:						*/
/* Baumaufbau								*/
/* Layout der Attribute (ausser Auxiliaries) relativ zum Knoten 	*/
/* Layout der Teilbaeume						*/
/* Verschieben des Baums aus (X_START/Y_START)				*/
/************************************************************************/
Tree *scan_pass1(char *filename, ANList *list)
{
FILE *fp;
char c;
union satz_info s;
char do_work =1;
Tree *wurzel = NULL;
TEP akt_vater =NULL;
TEP akt_sohn = NULL;
TEP tep= NULL;
TEPLEP ptr, ptr2;
int i;
int offset =X_START;
int *min;

fp = fopen(filename, "r");
if (fp == NULL)
	{
	printf("Can't open %s!\n", filename);
	exit(1);
	}

while (do_work)
	{
	c = hole_satz(&s, fp);
	switch (c)
		{
		case 'H':
			printf("Message from MUG Browser: processing ... %s\n", s.h.filename);
			break;
		case 'T':
			/* Jetzt schauen wir nach, ob überhaupt ein Satz gelesen wurde */
			if (wurzel == NULL)
				exit(0);

			do_work =0;
			break;
		case 'V':
			#ifdef DEBUG
				printf("Vater: %s\n", s.v.symbol);
			#endif
			if (wurzel == NULL)		/* Noch nichts getan	*/
				{
				wurzel = TE_alloc();
				strcpy(wurzel->symbol, s.v.symbol);
				wurzel->elem_of = NULL;
				akt_sohn = wurzel;
				wurzel->y=Y_START;
				wurzel->breite_rechts =KNOTEN_WIDTH(strlen(wurzel->symbol)) /2;
				wurzel->breite_links =KNOTEN_WIDTH(strlen(wurzel->symbol)) /2;
				}
			akt_vater= akt_sohn;
			akt_vater->vater_id = s.v.id;
			akt_vater->baumhoehe = 0;

			/* Jetzt holen wir die Auxiliaries	*/
			hole_attribute(akt_vater, 'A', &s, list, fp);

			/* Jetzt holen wir die Derived	*/
			hole_attribute(akt_vater, 'D', &s, list, fp);

/* Im Pass 1 werden fuer die Attribute dir x-Koordinaten nur relativ	*/
/* zum Knoten angegeben. Im Pass 2 muessen sie dann auf absolute	*/
/* Koordinaten umgerechnet werden (Funktion ziehe_pfeil)		*/
			attr_layout(&akt_vater->iattr, &akt_vater->dattr, akt_vater->vater, akt_vater);
			if (akt_vater->dattr.anzahl >0)
				akt_vater->breite_rechts +=IMAGE_BORDER + ( akt_vater->dattr.anzahl-1)*(IMAGE_SPACE + IMAGE_WIDTH) + IMAGE_WIDTH;

			/* Diejenigen Auxiliaries, die nicht Ergebnis	*/
			/* einer semantischen Aktion sind, werden hier	*/
			/* rechts von den derived angeordnet.		*/
			akt_vater->breite_rechts += aux_layout(&akt_vater->aattr, akt_vater);

			break;
		case 'S':
			#ifdef DEBUG
				printf("Sohn: %s\n", s.s.symbol);
			#endif
			tep = TE_alloc();
			strcpy(tep->symbol, s.s.symbol);
			tep->sohn_id = s.s.id;
			tep->is_terminal = s.s.is_terminal;
			tep->vater = akt_vater;
			tep->elem_of = TEPList_insert(&akt_vater->soehne, tep);
			tep->y=akt_vater->y+PROD_HEIGHT;
			tep->breite_rechts =KNOTEN_WIDTH(strlen(tep->symbol)) /2;
			tep->breite_links =KNOTEN_WIDTH(strlen(tep->symbol)) /2;

			if (s.s.is_terminal)
				{
				tep->x = X_START;
				tep->baumhoehe = 0;
				}
			else
				{
				akt_sohn = tep;

				/* Jetzt holen wir die Inherited */
				hole_attribute(akt_sohn, 'I', &s, list, fp);
				if (akt_sohn->iattr.anzahl >0)
					akt_sohn->breite_links +=IMAGE_BORDER + ( akt_sohn->iattr.anzahl-1)*(IMAGE_SPACE + IMAGE_WIDTH) + IMAGE_WIDTH;
				}

			break;
		case 'P':
			ptr = akt_vater->soehne.first;
			while (ptr)
				{
				if (akt_vater->baumhoehe < ptr->symbol->baumhoehe)
					akt_vater->baumhoehe = ptr->symbol->baumhoehe;

				if (ptr->next)
					layout(ptr->symbol, ptr->next->symbol, 'A');
				ptr = ptr->next;
				}

/* Es kann passieren, dass die Baeume jetzt zu dicht liegen, falls die	*/
/* Kollision nicht zwischen Nachbarn, sondern weiter entfernten Teil-	*/
/* baeumen stattfindet! 						*/
			ptr = akt_vater->soehne.first;
			while (ptr)
				{
				ptr2 = ptr->next;
				while(ptr2)
					{
					layout(ptr->symbol, ptr2->symbol, 'W');
					ptr2 = ptr2->next;
					}
				ptr = ptr->next;
				}

			akt_vater->baumhoehe++;

/* Es kann passieren, dass auch nonterminals keine Soehne haben, z.B.	*/
/* eine leere Parameterliste						*/
			if (akt_vater->soehne.anzahl >0)
				akt_vater->x = (akt_vater->soehne.first->symbol->x + akt_vater->soehne.last->symbol->x) /2;
			else
				{
				akt_vater->x = X_START;
				akt_vater->baumhoehe =0;
				}

			akt_vater = akt_vater->vater;
			break;

		case 'E':
		case 'G':
		case 'A':
		case 'F':
			printf("Illegal entry: %c\n", c);
			break;
		case EOF:
			printf("ERROR: Unexpexted end of file!\n");
			break;
		default:
			printf("Illegal entry in browse-file\n");
			exit(1);
		}
	}

fclose (fp);

/* Jetzt wird der ganz Baum noch so verschoben, dass die kleinste	*/
/* x-Koordinate == X_START ist. 					*/
min = (int *)calloc(wurzel->baumhoehe+1, sizeof(int));
if (min == NULL)
	{
	printf("Not enough memory!\n");
	exit(1);
	}

for (i=0; i<wurzel->baumhoehe+1; i++)
	min[i]=MAXIMUM;

get_min(wurzel, min);
for (i=0; i<wurzel->baumhoehe+1; i++)
	if (min[i] < offset)
		offset = min[i];
free(min);

add_x_koord(wurzel, X_START-offset);

return wurzel;
}


/************************************************************************/
/* scan_pass2								*/
/*									*/
/* Scanner/Parser Pass2:						*/
/* Verknuepfen der Attribute und semantischen Aktionen			*/
/* Umrechnen von relativen auf absolute Koordinaten bei den Attributen	*/
/* Layout der semantischen Aktionen und Auxiliaries berechnen		*/
/************************************************************************/
void scan_pass2(char *filename, Tree *wurzel)
{
FILE *fp;
char c;
union satz_info s;
char do_work =1;
TEP akt_vater =wurzel;
TEP akt_sohn = wurzel;

char *buffer;

fp = fopen(filename, "r");
if (fp == NULL)
	{
	printf("Can't open %s!\n", filename);
	exit(1);
	}

while (do_work)
	{
	c = hole_satz(&s, fp);
	switch (c)
		{
		case 'H':
			break;
		case 'T':
			do_work =0;
			break;
		case 'V':
			akt_vater = akt_sohn;
			break;
		case 'S':
			/* Ist es der erste Sohn?	*/
			if (akt_sohn == akt_vater)
				akt_sohn = akt_vater->soehne.first->symbol;
			else
				{
				while (akt_sohn->elem_of->next ==NULL)
					akt_sohn = akt_sohn->vater;

				akt_sohn = akt_sohn->elem_of->next->symbol;
				}
			break;
		case 'P':
			sem_layout(akt_vater);
			akt_vater = akt_vater->vater;
			break;
		case 'E':
			break;
		case 'A':
			buffer = malloc(s.a.wertlen);
			if (buffer == NULL)
				{
				printf("Not enough memory!\n");
				exit(1);
				}
			fread(buffer, s.a.wertlen, 1, fp);
			free (buffer);

			ziehe_pfeil(akt_vater, akt_sohn, &s, fp);
			break;
		case 'G':
		case 'F':
			printf("Illegal entry: %c\n", c);
			break;
		case EOF:
			printf("ERROR: Unexpexted end of file!\n");
			break;
		default:
			printf("Illegal entry in browse-file\n");
			exit(1);
		}
	}

fclose (fp);
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zum Aufbau der x_list				       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* attr_into_xlist							*/
/*									*/
/* Einfuegen einer ganzen Attributliste in die x_list			*/
/************************************************************************/
void attr_into_xlist(AList *alist, x_list *list, int *x, int *y)
{
ALEP ptr = alist->first;
XLEP new;

while (ptr)
	{
	new = XLE_alloc();
	new->x_min = ptr->x;
	new->x_max = ptr->x + IMAGE_WIDTH;
	new->y_min = ptr->y;
	new->y_max = ptr->y + IMAGE_HEIGHT;
	new->art = 'A';
	new->info.a_element = ptr;
	xlist_insert(new, list);
	*x = MAX(*x, new->x_max);
	*y = MAX(*y, new->y_max);

	ptr = ptr->next;
	}
}


/************************************************************************/
/* build_x_list 							*/
/*									*/
/* Rekursiver Baumdurchlauf, Aufbau der x_list fuer das Backend 	*/
/************************************************************************/
void build_x_list(TEP knoten, x_list *list, int *x, int *y)
{
XLEP new;
SemLEP sem;
TEPLEP sohn;

/* Eintragen des Knotens				*/
new = XLE_alloc();
new->x_min = knoten->x - HALFW_RECT(strlen(knoten->symbol));
new->x_max = knoten->x + HALFW_RECT(strlen(knoten->symbol));
new->y_min = knoten->y;
new->y_max = knoten->y + KNOTEN_HEIGHT;
new->art = 'T';
new->info.t_element = knoten;
xlist_insert(new, list);
*x = MAX(*x, new->x_max);
*y = MAX(*y, new->y_max);

/* Eintragen der Attribute				*/
attr_into_xlist(&knoten->aattr, list, x, y);
attr_into_xlist(&knoten->iattr, list, x, y);
attr_into_xlist(&knoten->dattr, list, x, y);

/* Eintragen der semantischen Aktionen			*/
sem = knoten->aktionen.first;
while (sem)
	{
	new = XLE_alloc();
	new->x_min = sem->x_min;
	new->x_max = sem->x_max;
	new->y_min = sem->y;
	new->y_max = sem->y + SEM_HEIGHT;
	new->art = 'S';
	new->info.s_element = sem;
	xlist_insert(new, list);
	*x = MAX(*x, new->x_max);
	*y = MAX(*y, new->y_max);

	sem = sem->next;
	}

/* Rekursion fuer die Soehne				*/
sohn = knoten->soehne.first;
while (sohn)
	{
	build_x_list(sohn->symbol, list, x, y);
	sohn = sohn->next;
	}
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Funktionen zur Behandlung von Konfigurationsfile und ANList        **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* config_equal 							*/
/*									*/
/* Traegt ein neues Paar in die Konfigurationsliste ein.		*/
/************************************************************************/
void config_equal(ANList *list, ALEP a, int image)
{
ANLEP ptr;
int slen = strlen(a->attr) + 1;
char *attr_str = (char *) malloc(slen), *remind = attr_str, prefix = '-';

if (attr_str == NULL) {
	printf("not enough memory!\n");
	exit(1);
	}

/* Loesche Praefix, falls vorhanden */
strcpy(attr_str, a->attr);
if ((*attr_str == 'a' && a->art == 'A') ||
 (*attr_str == 'd' && a->art == 'D') ||
 (*attr_str == 'i' && a->art == 'I')) {
	prefix = *attr_str;
	attr_str = attr_str + 1;
	}

if(!(ptr = (ANLEP) malloc(sizeof(ANLE))))
	{
	printf("Not enough memory!\n");
	exit(1);
	}
strcpy(ptr->attr, attr_str);
free(remind);
ptr->nr = image;
ptr->next = list->first;
list->first = ptr;
ptr->prefix[0] = ' ';
ptr->prefix[1] = ' ';
ptr->prefix[2] = ' ';
ptr->prefix[3] = ' ';
switch(prefix) {
	case 'a':
		ptr->prefix[1] = 'a';
		break;
	case 'd':
		ptr->prefix[2] = 'd';
		break;
	case 'i':
		ptr->prefix[3] = 'i';
		break;
	default:
		ptr->prefix[0] = '-';
	}
(list->anzahl)++;
}


/************************************************************************/
/* config_init								*/
/*									*/
/* Traegt die Empfehlungen des MUGbrowsers in Konfigurationsliste ein	*/
/* !! Nicht mehr, loescht jetzt einfach - m. guntersdorfer, 7.10.94 !!	*/
/* Die Default Konfiguration wird nun waehrend der Baumberechnung	*/
/* gemacht: Jedem Attribut wird ein neutrales Image zugewiesen, diese	*/
/* Konfiguration wird unter "default.config" gespeichert.		*/
/************************************************************************/
void config_init(ANList *list)
{
/* Die bisherige Liste werfen wir weg					*/
if (list->anzahl > 0)
	free_ANList(list);
}


/************************************************************************/
/* config_load								*/
/*									*/
/* Liest den Inhalt der Konfigurationsdatei in die Liste		*/
/************************************************************************/
int config_load(ANList *list, char *file)
{
FILE *fp;
ANLE new;
ANLEP ptr, ptr_read;
int i;

/* Zuerst wird das File geoeffnet					*/
fp = fopen(file, "r");
if (fp == NULL)
	return 1;

/* Alle Images werden auf NoIcon gesetzt.				*/
ptr = list->first;
for(i = 1; i <= list->anzahl; i++) {
	ptr->nr = -1;
	ptr = ptr->next;
	}

/* Jetzt wird die Datei gelesen und die Images zugewiesen.		*/
while (fread((char *)&new, sizeof(ANLE), 1, fp) == 1) {
	ptr = list->first;
	for(i = 1; i <= list->anzahl; i++) {
		if (strcmp(new.attr, ptr->attr) == 0) ptr->nr = new.nr;
		ptr = ptr->next;
		}
	}

fclose(fp);
return 0;
}


/************************************************************************/
/* config_save								*/
/*									*/
/* Speichert den Inhalt der Konfigurationsliste in eine Datei		*/
/************************************************************************/
int config_save(ANList *list, char *file)
{
ANLEP ptr = list->first;
FILE *fp;

/* Zuerst wird das File geoeffnet					*/
fp = fopen(file, "w");
if (fp == NULL)
	return 1;

while (ptr)
	{
	fwrite((char *)ptr, sizeof(ANLE), 1, fp);
	ptr = ptr->next;
	}

fclose(fp);
return 0;
}


/************************************************************************/
/* attr_refresh 							*/
/*									*/
/* Vergibt die Images fuer eine Attributliste neu			*/
/************************************************************************/
void attr_refresh(AList *list, ANList *anlist)
{
ALEP ptr = list->first;

while (ptr)
	{
	ptr->image = get_image(ptr, anlist);
	ptr = ptr->next;
	}
}


/************************************************************************/
/* image_refresh							*/
/*									*/
/* Vergibt die Images in einem (Teil-)baum neu				*/
/************************************************************************/
void image_refresh(TEP wurzel, ANList *anlist)
{
TEPLEP sohn = wurzel->soehne.first;

attr_refresh(&wurzel->aattr, anlist);
attr_refresh(&wurzel->iattr, anlist);
attr_refresh(&wurzel->dattr, anlist);

while (sohn)
	{
	if (!sohn->symbol->is_terminal)
		image_refresh(sohn->symbol, anlist);

	sohn = sohn->next;
	}
}


/************************************************************************/
/************************************************************************/
/**								       **/
/** Die MAIN-Funktion						       **/
/**								       **/
/************************************************************************/
/************************************************************************/

/************************************************************************/
/* main 								*/
/*									*/
/* Aufruf von Scanner/Parser, Backend					*/
/************************************************************************/
int main(int argc, char *argv[])
{
Tree *wurzel;
int x_max = 0, y_max = 0;
x_list xlist;
ANList anlist;
char file[L_FILENAME];
int arg_file, arg_config;

/* Zuerst wird die Anzahl der Parameter uberprueft		*/
/* Entweder 2 (MUGbrowse file.browse)				*/
/* oder     4 (MUGbrowse file.browse -c file.config		*/
if (argc != 2 && argc != 4)
	usage();

/* Wir muessen die ANList initialisieren			*/
anlist.anzahl = 0;
anlist.first = NULL;

/* Die Eingabe wird geparst					*/
if (argc == 4)				/* Konfigfile angegeben */
	{
	if (strcmp(argv[1], "-c") == 0)
		{
		arg_config = 2;
		arg_file = 3;
		}
	else
		{
		if (strcmp(argv[2], "-c") == 0)
			{
			arg_config = 3;
			arg_file = 1;
			}
		else
			usage();
		}
	}
else
	{
	arg_file = 1;
	}

config_init(&anlist);	/* Zunaechst immer leere Konfiguration, damit	*/
			/* default.config berechnet wird		*/


/* Jetzt wird ueberprueft, ob das browse-file schon die Endung hat	*/
if (strlen(argv[arg_file]) < 7) 	/* Die Endung fehlt sicher!	*/
	sprintf(file, "%s.browse", argv[arg_file]);
else
	if (strcmp(argv[arg_file]+strlen(argv[arg_file])-7, ".browse") == 0)
		strcpy (file, argv[arg_file]);
	else
		sprintf(file, "%s.browse", argv[arg_file]);

/* Nun folgt das Scannen und Parsen des browse-files in 2 Paessen	*/
wurzel = scan_pass1(file, &anlist);
scan_pass2(file, wurzel);

/* Zur schnelleren Ausgabe wird eine Liste aufgebaut, in der alle	*/
/* Elemente (Knoten, Attribute, semantische Aktionen) nach x-Koordi-	*/
/* naten sortiert vorliegen						*/
xlist.first_min = xlist.first_max = NULL;
xlist.anzahl = 0;
build_x_list(wurzel, &xlist, &x_max, &y_max);

/* print_tree(wurzel); */
#ifdef DEBUG
	print_x_list(&xlist);
	printf("%d Elemente, x_max = %d, y_max = %d\n", xlist.anzahl, x_max, y_max);
#endif

/* Speichern der default image configuration in default.config */
printf("Message from MUG Browser: saving default attribute-image configuration ...\n");
config_save(&anlist, "default.config");

/* Laden des image configuration files, falls angegeben. */
if (argc == 4)
	if (config_load(&anlist, argv[arg_config]) != 0)
		printf("Error: Couldn't open configfile %s!\n", argv[arg_config]);


/* Das Frontend ist jetzt fertig und ruft das Backend (die Ausgabe) auf */
/* Erst bei Programmende kommen wir wieder zurueck			*/
printf("Message from MUG Browser: visualizing ...\n");
show_tree(wurzel, x_max, y_max, &anlist, &xlist);
}


