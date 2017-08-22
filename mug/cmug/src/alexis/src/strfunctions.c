/* const MaxtokLength = 5000; */
/*#define DEBUG*/

#ifdef __STDC__
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#endif

#define MAXTOKLENGTH 5000
#include "strfunctions.h"


#ifdef __STDC__
void STRdelete(struct ActionString *astring, int pos, int len)
#else /* ! __STDC__ */
void STRdelete(astring,pos,len)
struct ActionString *astring;
int pos,len;
#endif /* ! __STDC__ */
{
 int i;
 char *p,*q;
#ifdef DEBUG
   printf("PROCEDURE delete\nEingangsparameter:\nastring: ");
   printacstr(astring);
   printf("pos %d\nlen %d\n\n",pos,len);
#endif
 if (pos>=1 && pos+len-1 <= astring->length)
  {
   p=astring->body+pos-1;
   q=astring->body+pos-1+len;
   for(i= pos+len-1;i<(astring->length);(*p++)=(*q++),i++);
   astring->length-= len;
#ifdef DEBUG
   printf("Ausgangsparameter:\nastring ");
   printacstr(astring);
   printf("\n");
#endif
  }
 else /*DEBUG*/ printf("Error in delete\n");
} 

#ifdef __STDC__
void STRdeletefstr(struct varfilestring *astring, int pos, int len)
#else /* ! __STDC__ */
void STRdeletefstr(astring,pos,len)
struct varfilestring *astring;
int pos,len;
#endif /* ! __STDC__ */
{
  int i;
  char *p,*q;
#ifdef DEBUG
   printf("PROCEDURE deletefstr\nEingangsparameter:\nastring");
   printvfstr(astring);
   printf("pos %d\nlen %d\n\n",pos,len);
#endif
  if (pos>=1 && pos+len-1 <= astring->length)
   {
    p=astring->body+pos-1;
    q=astring->body+pos-1+len;
    for(i= len;--i>=0;(*p++)=(*q++));
    astring->length-= len;
#ifdef DEBUG
   printf("Ausgangsparameter:\nastring ");
   printvfstr(astring);
   printf("\n");
#endif

   }
  else /*DEBUG*/  printf("******** Error in deletefstr\n");
}



#ifdef __STDC__
int STRindexx(struct ActionString *astring, struct varfilestring *search)
#else /* ! __STDC__ */
int STRindexx(astring,search)
struct ActionString *astring;
struct varfilestring *search;
#endif /* ! __STDC__ */
{
 int i,j;
 int found,searchlen;
 char *p;
#ifdef DEBUG
   printf("Function STRindexx\nEingangsparameter:\nastring ");
   printacstr(astring);
   printf("search ");
   printf("alive1\n");
   printvfstr(search);
   printf("alive2\n");
#endif
 if (search->length==0)  return 0 ;
 {
  searchlen=astring->length-search->length+1;
  p=astring->body;
  for(i=1;i<=searchlen;i++,p++)
  {
   found=1;
   for(j=search->length;--j>=0 && found;)
   {
    if (search->body[j] != p[j]) found=0;
   }
   if(found==1) return i;
  }
 }
 return 0;
}


/*******************************************************************/
/*                                                                 */
/*  Prozedur: inttostring             Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: lokale Prozedur                               */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*                                                                 */
/*    Diese Prozedur wandelt den integer32-Wert rein in die zuge-  */
/*    hoerige Dezimaldarstellung um und gibt diese in dem Refe-    */
/*    renzparameter raus wieder zurueck.                           */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*     rein: integer32; Wert, der umgewandelt werden soll.         */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*     raus: string; Umgewandelte Dezimalzahl. Der String mua      */
/*           mindestens soviele Zeichen aufnehmen koennen, wie     */
/*           zur Dezimaldarstellung der Zahl notwendig sind, sonst */
/*           wird ein Laufzeitfehler erzeugt.                      */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*                                                                 */
/*     lauf: integer32; Enthaelt den noch nicht umgewandelten Teil */
/*           von rein in integer32-Format.                         */
/*     ziff: integer32; Enthaelt die momentan umzuwandlende Ziffer */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void STRinttostring(int rein, struct varfilestring *raus)
#else /* ! __STDC__ */
void STRinttostring(rein,raus)
int rein;
struct varfilestring *raus;
#endif /* ! __STDC__ */
{
 int lauf,ziff,len,i;
#ifdef DEBUG
   printf("Function inttostring\nEingangsparameter:\n");
   printf("rein %d\nraus ",rein);
   printvfstr(raus);
#endif
 lauf = rein;
 len = 0;
 do 
 {
  len++;
  ziff= lauf % 10;
  lauf = (lauf-ziff) / 10;
  for(i=len;i>=1;i--)
     raus->body[i] = raus->body[i-1];
  raus->body[0] = (char) (ziff + (int)('0'));
 } while (lauf!=0);
 raus->length = len;
#ifdef DEBUG
   printf("Ausgangsparameter:\nraus ");
   printvfstr(raus);
   printf("\n");
#endif
}
 
/*******************************************************************/
/*                                                                 */
/*  Prozedur: SSubString              Version: 20/05/91            */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung: Globale Funktion                              */
/*                                                                 */
/*  Funktionsbeschreibung: Diese Prozedur liefert einen Ausschnitt */
/*      aus dem Uebergebenen String, der an der Position Offset    */
/*      beginnt und die Laenge count hat. Im Gegensatz zu der      */
/*      Funktion SubStr des Compilers laesst diese Funktion auch   */
/*      zu,dass offset + count > Length(instring) ist.             */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*      instring: string(maxstring): String,aus dem der Ausschnitt */
/*         extrahiert werden soll.                                 */
/*      offset: integer32; Position, an der das Ergenis beginnen soll*/
/*      count: integer32; Laenge des Stringteils, das extrahiert wer-*/
/*         den soll. Ist offset + count > Length(instring),so wird */
/*         inString ab offset bis zum Ende zurueckgegeben.         */
/*                                                                 */
/*  Ausgabeparameter:                                              */
/*      Funktionsergebnis: Teil von instring, beginnend ab offset  */
/*         mit der Laenge count bzw. dem Rest des Strings          */
/*                                                                 */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Lokale Variablen:                                              */
/*      lang : integer32; Enthaelt die effektive Laenge des zu extra-*/
/*         hierenden Strings, also entweder count oder             */
/*         Length(instring) - offset +1                            */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
void STRssubstring(struct ActionString *ergebnis,
                   struct ActionString *instring,
                   int offset,
                   int count)
#else /* ! __STDC__ */
void STRssubstring(ergebnis,instring,offset,count)
struct ActionString *ergebnis,*instring;
int offset,count;
#endif /* ! __STDC__ */
{
 char *p,*q;
 int lang,i;
#ifdef DEBUG
   printf("Function STRssubstring\nEingangsparameter:\ninstring ");
   printacstr(instring);
   printf("offset %d\ncount %d\nErgebnis ",offset,count);
#endif
 if (offset+count-1 > instring->length)
    lang=instring->length-offset+1;
 else lang= count;
 p=ergebnis->body;
 q=instring->body+offset-1;
 for(i=0;i++<lang;(*p++)=(*q++));
 ergebnis->length=lang;
#ifdef DEBUG
   printacstr(ergebnis);
   printf("\n");
#endif
}
   

/*******************************************************************/
/*                                                                 */
/*  Prozedur: StrInsert               Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Fuegt InsString an der Stelle pos in InString ein              */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  pos                       integer32                            */
/*  InsString                 String                               */
/*  Transientparameter:                                            */
/*  InString                  ActionString                         */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  front                     ActionString                         */
/*  rest                      ActionString                         */
/*******************************************************************/

#ifdef __STDC__
void STRstrinsert(struct ActionString *InString,
                  int pos,
                  struct varfilestring *InsString)
#else /* ! __STDC__ */
void STRstrinsert(InString,pos,InsString)
struct ActionString *InString;
int pos;
struct varfilestring *InsString;
#endif /* ! __STDC__ */
{
 char *p,*q;
 int i;
#ifdef DEBUG
   printf("PROCEDURE strinsert\nEingangsparameter:\nInString ");
   printacstr(InString);
   printf("pos %d\nInsString ",pos);
   printvfstr(InsString);
#endif
 p=InString->body+pos;
 q=InsString->body;

for(i=InString->length;--i>=pos;InString->body[i+InsString->length]=InString->body[i]);
 for(i=0;i<InsString->length;(*p++)=(*q++),i++);
 InString->length=InString->length+InsString->length;
#ifdef DEBUG
   printf("Ausgangsparameter:\nInString ");
   printacstr(InString);
   printf("\n");
#endif
} 


/*******************************************************************/
/*                                                                 */
/*  Prozedur: StrContains             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Funktion                                     */
/*                                                                 */
/*  Funktionsbeschreibung: Prueft ob ein String search in Instring */
/*  enthalten ist und liefert in position die Position zurueck.    */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InString                  Actionstring                         */
/*  search                    String                               */
/*  Ausgabeparameter:                                              */
/*  StrContains               boolean                              */
/*  Transientparameter                                             */
/*  position                  integer32                            */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*******************************************************************/

#ifdef __STDC__
int STRstrcontains(struct ActionString *InString,
                   struct varfilestring *search,
                   int *position)
#else /* ! __STDC__ */
int STRstrcontains(InString,search,position)
struct ActionString *InString;
struct varfilestring *search;
int *position;
#endif /* ! __STDC__ */
{ 
#ifdef DEBUG
   printf("FUNCTION strcontains\nEingangsparameter:\nInString ");
   printacstr(InString);
   printf("search ");
   printvfstr(search);
   printf("position %d\nErgebnis ",*position);
#endif
 *position = STRindexx(InString,search);
#ifdef DEBUG
  printf("%d\n\n",*position);
#endif
 return(*position);
}


/*******************************************************************/
/*                                                                 */
/*  Prozedur: RepInString             Version:  20/05/91           */
/*                                                                 */
/*******************************************************************/
/*                                                                 */
/*  Klassifizierung:  Prozedur                                     */
/*                                                                 */
/*  Funktionsbeschreibung:                                         */
/*  Ersetzt im Progstring den StellungsParameter %<Instead> durch  */
/*  den String Instring                                            */
/*-----------------------------------------------------------------*/
/*                                                                 */
/*  Eingabeparameter:                                              */
/*  InString                  String                               */
/*  Seiteneffekte:                                                 */
/*                                                                 */
/*  Lokale Variablen:                                              */
/*  progstring                ActionString                         */
/*  toreplace                 String                               */
/*  place                     integer32                            */
/*******************************************************************/

#ifdef __STDC__
void STRrepinstring(struct varfilestring *InString,
                    int instead,
                    struct ActionString *progstring)
#else /* ! __STDC__ */
void STRrepinstring(InString,instead,progstring)
struct varfilestring *InString;
int instead;
struct ActionString *progstring;
#endif /* ! __STDC__ */
{
 struct varfilestring toreplace;
 int place;

#ifdef DEBUG
   printf("PROCEDURE repinstring\nEingangsparameter:\nInString ");
   printvfstr(InString);
   printf("instead %d\nprogstring ",instead);
   printacstr(progstring);
#endif
 toreplace.body[0]='%';
 toreplace.body[1]= (char) ( (int) '0' + instead);
 toreplace.length=2;
 while (STRstrcontains(progstring,&toreplace,&place))
 {
#ifdef DEBUG
  printf("===> Makro gefunden an Stelle %d\n\n\n",STRstrcontains(progstring,&toreplace,&place));
#endif
  STRdelete(progstring,place,2);
#ifdef DEBUG
  printf("===> String nach STRdelete ");
  printacstr(progstring);
#endif
  STRstrinsert(progstring,place-1,InString);
#ifdef DEBUG
  printf("===> String nach STRstrinsert ");
  printacstr(progstring);
#endif
 }
#ifdef DEBUG
   printf("Ausgangsparameter:\nprogstring ");
   printacstr(progstring);
   printf("\n");
#endif
}
 

#ifdef __STDC__
void printacstr(struct ActionString *string)
{
#else /* ! __STDC__ */
 printacstr(string)
 struct ActionString *string;
 {
#endif /* ! __STDC__ */
  int i;
  printf("Laenge %d\n",string->length);
  for (i=0;i<string->length;printf("%c",string->body[i++]));
  printf("\n");
  printf("String ausgegeben\n");
 }
#ifdef __STDC__
void printvfstr(struct varfilestring *string)
{
#else /* ! __STDC__ */
 printvfstr(string)
 struct varfilestring *string;
 {
#endif /* ! __STDC__ */
  int i;
  for (i=0;i<string->length;printf("%c",string->body[i++]));
  printf("\n");
 }
