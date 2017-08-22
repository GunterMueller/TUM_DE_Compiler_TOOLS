#ifndef _BIM_UTIL
#define _BIM_UTIL

#include <nodeinfo.h>

extern int  Bim_total_attributes;

/**
 ** Test, ob ein Knoten von einer bestimmten Sorte ist, dabei werden die
 ** Klassenabhaengigkeiten in Betracht gezogen.
 **/

extern int Bim_IsOfSort( MAX_NODE *, char * );

/**
 ** MAX_TREE vollstaendig kopieren
 **/

extern MAX_NODE * Bim_CopyMaxTree( MAX_NODE *, MAX_NODE * );

/**
 ** MAX_TREE freigeben 
 **/

extern void Bim_FreeMaxTree( MAX_NODE * );
 
/**
 ** Alphabetisch sortierte Liste alle Sorten erstellen, Array von Pointern,
 ** abgeschlossen mit einem NULL-Pointer
 **/

extern char ** Bim_ListOfSorts( void );
extern char ** Bim_ListOfAttributes( void );
/**
 ** Obige Liste wieder freigeben
 **/

extern void Bim_FreeListOfSorts( char ** );


#endif
