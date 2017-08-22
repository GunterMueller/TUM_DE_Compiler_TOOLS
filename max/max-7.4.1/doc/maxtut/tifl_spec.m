////////////////////////////////////////////////////////////////
//   Abstract Syntax of FLIRT
/////////////////////////////////


Program      (  Exp  )
Exp          =  LetExp  |  Int  |  Bool  |  CondExp  |  FctAppl  |  UsedId
LetExp       (  FctDeclList  Exp  )
FctDeclList  *  FctDecl
FctDecl      (  Type  DeclId  ParDeclList  Body  )
Type         =  Boolean  |  Integer
Boolean      ()
Integer      ()
ParDeclList  *  ParDecl
ParDecl      (  Type  DeclId  )
Body         =  Exp  |  PredeclBody
PredeclBody  () 
CondExp      (  Exp  Exp  Exp  )
FctAppl      (  UsedId  ExpList  )
ExpList      *  Exp
UsedId       (  Ident  LineNo  )
DeclId       (  Ident  LineNo  )


Decl         =  FctDecl |  ParDecl
Scope        =  FctDecl |  LetExp
LineNo       =  Int


/////////////////////////////////////////////////////////////
//   some sorts for the evaluator
/////////////////////////////////
Env          *  Pair
Pair         (  ParDecl@  Value  )
Value        =  Bool | Int



//////////////////////////////
//  Funktionsdeklarationen  
//  (Bodies in mfl.c)
//////////////////////////////

FCT itos( Int ) String

FCT and( Bool, Bool ) Bool
FCT or( Bool, Bool ) Bool
FCT not( Bool ) Bool

FCT add( Int, Int ) Int
FCT sub( Int, Int ) Int
FCT mul( Int, Int ) Int

FCT lt( Int, Int ) Bool
FCT le( Int, Int ) Bool
FCT equ( Int, Int ) Bool


STRUC  mfl  [ Program ]{

FCT id( Node I ) Ident : term( son( 1, I ) )
FCT ln( Node N ) String : itos( term( son( -1, N ) ) )

ATT encl_scope( Node N ) Scope@ :
   IF  is[ N, _FctDecl@ ]            : N
   |   is[ N, _LetExp@ ]             : N 
   ELSE                     encl_scope( fath( N ) )

FCT first_decl( Scope@ S ) Decl@:
   IF  LetExp@<<FCTD,*>,_> S     :   FCTD
   |   FctDecl@<_,_,<PARD,*>,_> S:   PARD
   ELSE nil()

FCT lookup_list( Ident ID, Decl@ D ) DeclId@ :
   IF  ID = id( son(2,D) )  :  son(2,D)   ELSE  lookup_list( ID, rbroth(D) )

FCT lookup( Ident ID, Scope@ S ) DeclId@ :
   LET  DID == lookup_list(ID,first_decl(S)) :
   IF   DID # nil() :  DID  ELSE  lookup( ID, encl_scope(fath(S)) )

ATT decl( UsedId@ UID ) DeclId@ :
   lookup( id(UID), encl_scope(UID) )

ATT type( Exp@ E ) Type :
   IF LetExp@<_,EX> E   :  type( EX )
   |  Int@ E            :  Integer()
   |  Bool@ E   	:  Boolean()
   |  CondExp@<_,E2,_> E:  type( E2 ) 
   |  FctAppl@<UID,_> E :  type( UID ) 
   |  UsedId@ E         :  term( son( 1, fath(decl(E)) ) )
   ELSE nil()


PRD par_type_check[ ParDecl@ P, Exp@ E ]:
   term(son(1,P)) = type(E)
 && { rbroth(P) # nil()  ->  par_type_check[ rbroth(P), rbroth(E) ] }
   

////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//
//     Kontextbedingungen
//     (in einem Block!!!!)
//
//////////////////////////////////////////////////////////////////

//
//  beide Zweige von if ... then ... else ... fi m"ussen den gleichen
//  Typ haben
//

CND CondExp@<_,E1,E2>               : type(E1) = type(E2)
| `"### : then/else expr's must be of same type\n"'

//
//  die Bedingung in if ... muss vom Typ Boolean sein
//

CND CondExp@<E1,*>                  : is[type(E1),_Boolean] 
| `"### : conditional expr must be of type Boolean\n"'

//  die formalen Parameter einer Fkts.deklaration m"ussen paarweise verschieden 
//  sein
//

CND ParDeclList@<*,<_,ID1>,*,<_,ID2>,*>  : id(ID1) # id(ID2)
| `"### LINE(S) " ln(ID1) "/" ln(ID2) ": parameter \"" idtos(id(ID1)) "\" doubly declared\n"'

//  die Fkts.deklarationen in einer DeclList m"ussen paarweise verschieden sein
//

CND FctDeclList@<*,<ID1,*>,*,<ID2,*>,*>   : id(ID1) # id(ID2)
| `"### LINE(S) " ln(ID1) "/" ln(ID2) ": function \"" idtos(id(ID1)) "\" doubly declared\n"'

//  angewandt auftretende Bezeichner m"ussen deklariert sein
//

CND UsedId@ UID                   : decl(UID) # nil()
| `"### LINE " ln(UID) ": identifier \"" idtos(id(UID)) "\" not declared\n"'

//  Anzahl formale Par muss gleich Anzahl akt. Par sein
//

CND FctAppl@<UID,EL>                   : numsons(EL) = numsons( son( 2, fath( decl( UID ) ) ) )
| `"### LINE " ln(UID) ": incorrect number of parameters in call of function "idtos(id(UID))"\n"'

//  Typen von formalen und entspr. aktuellen Par m"ussen "ubereinstimmen
//

CND FctAppl@<UID,<E,*>>      :  par_type_check[ son(1,son(3,fath(decl(UID)))), E ]
| `"### LINE " ln(UID) ": type mismatch in call of function "idtos(id(UID))"\n"'

//  Typ aus der Deklaration einer Fkt. und Typ der Exp m"ussen "ubereinstimmen
//  "Uberpr"ufung nicht f"ur vordef. Fkt.en
//

CND FctDecl@<T,DID,_,B>                :
 !is[ B , _PredeclBody@] -> term( T ) = type( B )
| `"### LINE " ln(DID) ": declaration of "idtos(id(DID))" does not match function result\n"'

//  falls Fkts.bezeichner ohne Klammern auftritt
//

CND UsedId@ UID                        :
   rbroth(UID) = nil() -> !is[ fath( decl ( UID ) ), _FctDecl@ ]
| `"### LINE " ln(UID) ": incorrect call of "idtos(id(UID))" \n"'


///////////////////////////////////////////////////////////////////////////
//
//  eval and related functions
//
///////////////////////////////////////////////////////////////////////////
                         

FCT  env_lookup( ParDecl@ PN, Env E ) Value:
   IF  subterm(1,subterm(1,E)) = PN  :  subterm(2,subterm(1,E))
                                  ELSE  env_lookup( PN, back(E) )

FCT  enter_pars( ParDecl@ PN, Exp@ EN, Env E, Env EVALENV ) Env:
   LET  V == eval( EN, EVALENV )   :
   IF   rbroth(PN) = nil()   :	appfront( Pair(PN,V), E )
   ELSE   enter_pars( rbroth(PN), rbroth(EN), appfront( Pair(PN,V), E ), EVALENV )


FCT  eval_predecl( Ident ID, Exp@ EN, Env E ) Value :
   IF  idtos(ID) = "or"      :   or( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "and"     :   and( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "not"     :   not( eval(EN,E) )
    |  idtos(ID) = "add"     :   add( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "sub"     :   sub( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "mul"     :   mul( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "lt"      :   lt( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "le"      :   le( eval(EN,E), eval(rbroth(EN),E) )
    |  idtos(ID) = "equ"     :   equ( eval(EN,E), eval(rbroth(EN),E) )
   ELSE  nil()

FCT  eval ( Exp@ X, Env E ) Value:
   IF  LetExp@<_,BD>        X:  eval( BD, E )
    |  Int@                 X:  term(X)
    |  Bool@                X:  term(X)
    |  CondExp@<E1,E2,E3>   X:  IF eval(E1,E) = true() : eval(E2,E)  ELSE  eval(E3,E) 
    |  UsedId@              X:  env_lookup( fath(decl(X)), E )
    |  FctAppl@<UID,<>>     X:  eval( son(4, UID.decl.fath ), E )
    |  FctAppl@<UID,<E1,*>> X:  LET  FCTDCL ==  UID.decl.fath  :
	IF  FctDecl@<_,<IDN,_>,_,PredeclBody@> FCTDCL:  eval_predecl( term(IDN), E1, E )
	ELSE   eval( son(4,FCTDCL), enter_pars(son(1,son(2,FCTDCL)),E1,E,E)  )
   ELSE nil()

}

