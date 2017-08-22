#include "scan.h"
#include "global.h"


typedef int BOOL;
typedef struct AutomatenDescr *AUTOMAT;
typedef int INT;
typedef struct ClassDs CLASSDESC;
typedef struct KomprUeg KOMPRUEB;
typedef struct _partype { int par[10]; } PARTYPE;
typedef struct EvSet CHARSET;
typedef Quellort QUELLORT;

typedef struct {
          int semval;
          Quellort ort;  } FORMPAR,IDENT,INSTRUCTSY,INTEGERSY,PROGSTRINGSY,
                                      REGOP,SPECIALSY,STRINGSY;

typedef struct {
         BOOL bool;
         CLASSDESC classdesc;
         KOMPRUEB komprueb; } BOCLKO;
typedef struct {
         AUTOMAT automat;
         BOOL bool; } AUTBOOL;
typedef struct {
         BOOL bool;
         PARTYPE partype; } BOOLPAR;
typedef struct {
         INT i1;
         QUELLORT ort;
                       } INTORT;
typedef struct {
         CHARSET ch;
         BOOL bool; } CHARBOOL;

