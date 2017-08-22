
{ ******************************************************** }
{ Grammatik Grammatikeinleser fuer ReadG                   }
{ fuer CH-2-Grammatiken mit Aktionen                       }
{ letzte Aenderung :  2.3.89                               }
{ erstellt         :  1.3.89                               }
{ ******************************************************** }


{ ========================================================= }
{ Deklaration der Terminalsymbole, entsprechen ReadG.scb    }
{ ========================================================= }
terminals

 1  TERMINALSSY
 2  ACTIONSSY
 3  AXIOMSY
 4  RULESSY
 5  EMPTYSY
 6  IDENTSY
 7  INTSY
 8  ARROWSY
 9  POINTSY
 10 SEMICSY


{ ========================================================= }
{ Aktionen, im Semantikteil ReadGakt.c programmiert         }
{ ========================================================= }
actions

  S_TERMNR    
  S_FIRSTTERM    S_NEWTERM     S_ENDTERMS
  S_ACTIONNR     S_NEWACTION   S_NEXTACTION   S_ENDACTIONS  
  S_AXIOM
  S_LHS          S_SYMBAUS
  S_ENDALT       S_ENDALTLIST    

axiom            grammar

rules

grammar     ->   termpart S_endterms  actionpart S_endactions
                 AXIOMSY IDENTSY S_axiom RULESSY rulelist.

termpart    ->   TERMINALSSY INTSY S_termnr IDENTSY S_firstterm termlist.

termlist    ->   INTSY S_termnr IDENTSY S_newterm termlist; empty.

actionpart  ->   ACTIONSSY actionlist ; empty.

actionlist  ->   INTSY S_actionnr IDENTSY S_newaction;

                 IDENTSY S_nextaction ;

                 INTSY S_actionnr IDENTSY S_newaction actionlist;

                 IDENTSY S_nextaction actionlist.

rulelist    ->   rule ; rule rulelist.

rule        ->   IDENTSY S_lhs ARROWSY altlist POINTSY S_endaltlist.

altlist     ->   alt S_endalt ; alt S_endalt SEMICSY altlist.

alt         ->   rhslist ; EMPTYSY.

rhslist     ->   IDENTSY S_symbaus ; IDENTSY S_symbaus rhslist.



