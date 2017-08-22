LEXMAKROS
   Eoln            = chr(10);        { Zeilenwechsel }
   Tab             = chr(9);         { Tabulatoren }
   Comment         = '{' not(.'}'.)* '}' |
                     '(*' allbut('*)') '*)';
   Ws              = (' ' | Eoln | Tab | Comment)+;
   UpCaseLetter    = (.'A'..'I','J'..'R','S'..'Z'.);
   LowCaseLetter   = (.'a'..'i','j'..'r','s'..'z'.);
   Letter          = UpCaseLetter | LowCaseLetter;
   Digit           = (.'0'..'9'.);

   IntNumber       = Digit+;
   String          = ( ('''' (allbut('''') | '''''') '''') | '#' Digit#1,3 )+;
   Ident           = (letter | '_') (letter | digit | '_' )* ;

MAKROEND
 
ACTIONMAKROS
   Code(%1,%2)        prog   MACRetCC(TOKEN,%1,%2);   progend
   RetId(%1)          prog   MACRetId(TOKEN,%1);      progend
   RetInt(%1)         prog   MACRetInt(TOKEN,%1);     progend
   RetStr(%1)         prog   MACRetString(TOKEN,%1);  progend
MAKROEND

ScanInit
prog
  printf("ALEXIS: Scanner                 (c) TU Muenchen  2. Juli 1991\n");
progend


ScanEnd
prog
  MACRetCC(TOKEN,0,0);
progend
