




 {##
procedure flush_keybuffer; 
 extern;

procedure read2(var c:char);
  extern;
    }
procedure meldung (* fnr: integer *);
 var x,y:integer;
begin
if Meldungen = 0 then openMeldefenster;
with MFenster do
  setCursor( LOecke_y-(1+Meldungen)*rbs.zhoehe-2, LOecke_x + 7 );
case fnr of
 0: gpr_$text('falscher Typ ',13,status);
 1: gpr_$text('Beim Vater duerfen nur "derived" Attribute berechnet werden.',60,status);
 2: gpr_$text('Beim Sohn duerfen nur "inherited" Attr. berechnet werden.',57,status);
 3: gpr_$text('Dieses Attribut hat nicht die Richtung "auxiliary".',51,status);
 4: gpr_$text('Dieses Attribut wird bereits berechnet!',39,status);
 5: gpr_$text('Terminals duerfen nur Quellparameter sein',41,status);
 6: gpr_$text('Soll alte Berechnung durch neue ersetzt werden?',47,status);
 7: gpr_$text('Tippen Sie linke Maustaste oder "0" um abzubrechen',50,status);
 8: gpr_$text('oder ein beliebiges anderes Zeichen um fortzusetzen.  ',54,status);
 9: gpr_$text('oder ein anderes Zeichen um ein anderes Attr. auszuwaehlen.',59,status);
10: gpr_$text('Waehle eine Funktion mit einem Ergebnis vom Typ ',48,status);
11: gpr_$text('Zu viele Attr. beim Vater! Es werden nicht alle angezeigt.',58,status);
12: gpr_$text('Platzbedarf fuer Soehne zu gross! Ueberlappungen moeglich.',58,status);
13: gpr_$text('Diese Funktion hat kein Ergebnis des geforderten Typ`s.',55,status);
14: gpr_$text('Bestimmen Sie mit dem Mauszeiger die Position der Funktion!',59,status);
15: gpr_$text('Selektieren Sie das zu berechnende Attribut mit der Maus!',57,status);
16: gpr_$text('Selektieren Sie mit dem Mauszeiger ein Hilfsattribut!',53,status);
17: gpr_$text('Bestimmen Sie mit der Maus die Position des Hilfsattributs!',59,status);
18: gpr_$text('Selektieren Sie mit dem Mauszeiger eine Funktion!',49,status);
19: gpr_$text('Selektieren Sie mit der Maus ein Attribut oder ein Terminal!',60,status);
20: gpr_$text('Waehlen Sie einen formalen Parameter aus!',41,status);
21: gpr_$text('Gewaehlt wurde das Attribut ',28,status);
22: gpr_$text('Waehlen Sie einen Ergebnisparameter vom Typ ',44,status);
23: begin
     gpr_$text('Waehlen Sie ein Hilfsattribut aus!  Name: ',42,status);
     cursorPos(y,x);
     setCursor(y,x+43*rbs.zbreite);
    end;
24: gpr_$text('Dieses Hilfsattribut existiert bereits in dieser Produktion!',60,status);
25: gpr_$text('oder ein anderes Zeichen um ein neues Hilfsattribut zu def.!',60,status);
26: begin
     gpr_$text('Name: ',6,status);
     cursorPos(y,x);
     setCursor(y,x+6*rbs.zbreite)
    end;
27: gpr_$text('Selektieren Sie das durchzureichende Attribut!',46,status);
28: gpr_$text('Selektieren Sie die zu verschiebende Vokabel mit der Maus!',58,status);
29: gpr_$text('Bestimmen Sie mit der Maus die neue Position der Vokabel!',57,status);
30: gpr_$text('Markieren Sie Zwischenpunkte in Richtung Quelle -> Ziel! ',57,status);
31: gpr_$text('Waehlen Sie, ob Sie die Linienfuehrung',38,status);
32: gpr_$text('einer Identitaet oder einer Funktion aendern wollen!',52,status);
33: gpr_$text('Selektieren Sie ein von einer Identitaet versorgtes Attr.!',58,status);
34: gpr_$text('Diese Produktion enthaelt keine Identitaeten!',45,status);
35: gpr_$text('Selektieren Sie das betreffende Attribut bzw. Hilfsattribut.',60,status);
36: gpr_$text('Dieses Terminal wird bereits mit dem Typ ',41,status);
37: gpr_$text('Typ aendern ? (alte Verbindungen werden geloescht!!)',52,status);
38: gpr_$text('Diese Produktion enthaelt keine Funktionen!',43,status);
39: gpr_$text('Diese Produktion enthaelt keine Hilfsattribute!',47,status);
40: gpr_$text('Diese Produktion enthaelt nur Identitaeten!',43,status);
41: gpr_$text('Diese Produktion ist noch leer; sie enthaelt keine Vokabeln!',60,status);
42: gpr_$text('Diese Produktion enthaelt keine berechenbaren Attribute!',56,status);
43: gpr_$text('Produktion gespeichert!',23,status);
44: gpr_$text('Mittlere Maustaste waehlt aus, linke Maustaste beendet.',56,status);
45: begin
    gpr_$text('Rechte Maustaste oder ',22,status);
    gpr_$text(PraefixTab[1],1,status);
    gpr_$text(' idenfiziert Attribut',21,status);
    end;
46: gpr_$text('Element mit diesem Namen existiert nicht ! Neudefinition ? ',59,status); 
47: gpr_$text('Die Produktion wird nicht abgespeichert.',40,status);
48: gpr_$text('   Sind Sie sich dessen bewusst ?',33,status);
49: gpr_$text('Die Grammatik wird nicht abgespeichert.',39,status);
50: gpr_$text('Die Ausfuehrung der gewuenschten Aktion wuerde',46,status);
51: gpr_$text('Parameterbindungen aufloesen',28,status);
52: gpr_$text('und Funktionsvorkommen wegwerfen.',33,status);
53: gpr_$text('Wollen Sie dennoch aendern ?',28,status);
54: gpr_$text('WARNUNG: Produktion nicht leer!',31,status);
55: gpr_$text('W A R N U N G : ',16,status);
56: gpr_$text('besitzt Vorkommen, die alle vernichtet wuerden.',47,status);
57: gpr_$text('Wollen Sie dennoch loeschen ?',29,status);
58: gpr_$text('Soll die synt. Funktion gedreht werden ?',40,status);
59: gpr_$text('Waehlen Sie die Art der neuen Funktion:',39,status);
60: gpr_$text('Wo sollen die Eingabeparameter stehen ?',39,status);
61: gpr_$text('Waehlen Sie die Richtung des Attributs:',39,status);
end;
Meldungen:= Meldungen + 1
end; {meldung}


procedure meldefehler(* fnr: integer *);
type alfa1= packed array[1..34] of char;
     alfa2= packed array[1..27] of char;
     alfa3= packed array[1..36] of char;
     alfa4= packed array[1..49] of char;

var c: char;
    h1,h2: integer;
    noname: alfa1;
    empty: alfa2;
    redef: alfa3;
    nopasname: alfa4;
    s: Ident;

  procedure h2aendern (fehlerzeilen: integer);
  begin
  h2:= h1-fehlerzeilen*rbs.zhoehe;
  end;

  procedure nextline;
  begin
   setCursor(h2,MFenster.LOecke_x + 7);
  end;

begin
nopasname:='Identifikator muss der PASCAL-Syntax genuegen!';
noname:=' mit diesem Namen existiert nicht!';
empty :=' Es existiert noch kein(e) ';
redef :=' mit diesem Namen existiert bereits!';
openMeldefenster;
h1:=MFenster.LOecke_y-(1+Meldungen)*rbs.zhoehe-2;
h2aendern(1);
setCursor (h1,MFenster.LOecke_x + 7);
case fnr of
  1: gpr_$text(nopasname,46,status);
  2: begin
     gpr_$text('Identifikator existiert bereits unter diesem Namen',50,status);
     nextline;
     gpr_$text('            Bitte anderen Namen waehlen!',40,status);
     h2aendern(2);
     end;
  3: gpr_$text('Ungueltige Nummer!',18,status);
  4: gpr_$text('Auxiliaries hier unzulaessig',28,status);
  5: begin
     with rbs do
       begin
       h2aendern(2);
       setCursor(h1,MFenster.LOecke_x + 7);
       gpr_$text('SYNTAX: <evtl. leeres Praefix eines PASCAL-Id`s><AuswahlOp>',60,status);
       nextline;
       gpr_$text('        <AuswahlOp>::="',23,status);
       gpr_$text(PraefixTab[1],1,status);
       gpr_$text('"|"',3,status);
       gpr_$text(PraefixTab[2],1,status);
       gpr_$text('"|"',3,status);
       gpr_$text(PraefixTab[3],1,status);
       gpr_$text('"|<leere Eingabe>',17,status);
       end;
     end;
  6: begin
     gpr_$text('Max. Laenge von Namen: ',23,status);
     writeint(idlaenge);
     gpr_$text(' Zeichen',8,status); 
     end;
  7: gpr_$text('Leere Eingabe bzw. Abbruch der Eingabe nicht erlaubt',52,status);
  8: begin dekodhl(prodHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  9: begin dekodhl(termHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  10: begin dekodhl(attrHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  11: begin dekodhl(nontHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  12: begin dekodhl(sfktHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  13: begin dekodhl(prodHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  14: begin dekodhl(termHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  15: begin dekodhl(attrHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  16: begin dekodhl(nontHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  17: begin dekodhl(sfktHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  18: begin gpr_$text(empty,27,status); dekodhl(prodHL,s); wrtIdent(s) end;
  19: begin gpr_$text(empty,27,status); dekodhl(termHL,s); wrtIdent(s) end;
  20: begin gpr_$text(empty,27,status); dekodhl(attrHL,s); wrtIdent(s) end;
  21: begin gpr_$text(empty,27,status); dekodhl(nontHL,s); wrtIdent(s) end;
  22: begin gpr_$text(empty,27,status); dekodhl(sfktHL,s); wrtIdent(s) end;
  23: gpr_$text('Praefixoperator hier nicht zulaessig!',37,status);
  24: gpr_$text('Attribut bereits an anderer Position in der Attributierung',58,status);
  25: begin h2aendern(2);
      gpr_$text('Attribute duerfen hoechstens an das Ende der bisherigen ',56,status); 
      nextline;
      gpr_$text('Attributierung angehaengt werden!',33,status);
      end;
  26: gpr_$text('Bitte zuerst mittels "B" aktuelles Nonterminal bestimmen',56,status);
  27: gpr_$text('Letzter Ergebnisparameter darf nicht gestrichen werden!',55,status);
  28: ;
  29: begin
      gpr_$text('Der Vorrat an Attributsymbolen ist erschoepft!',46,status);
      nextline;
      gpr_$text('          Bitte zunaechst neue Symbole generieren.',50,status);
      h2aendern(2);
      end;
  30: begin
      gpr_$text(nopasname,46,status); 
      nextline;
      gpr_$text('(Eingabe bleibt [ebenso wie leere Eingabe] ohne Wirkung!)',57,status);
      h2aendern(2);
      end;
  31: begin
      gpr_$text('Ueberlauf im "virtuellen Bildschirm" !',38,status);
      nextline;
      gpr_$text(' Bitte diesbezueglich Programmdokumentation beachten!',53,status);
      h2aendern(2);
      end;
  32: begin
      gpr_$text('PhasenId, InGName, OutGName duerfen hoechstens vier Zeichen',59,status);
      nextline;
      gpr_$text('             lang sein!',23,status);
      h2aendern(2);
      end;
  33: gpr_$text('Vater der Produktion muss vom Typ Nonterminal sein.',51,status);
  34: gpr_$text('Vokabel muss Nonterminal sein.',30,status);
  35: gpr_$text('Die Produktion ist leer. Es gibt nichts zu streichen.',53,status);
  36: begin
      gpr_$text('Auf der linken Seite des Nonterminale sollten die inherited,',60,status);
      nextline;
      gpr_$text('auf der rechten Seite die derived Attribute stehen.',51,status);
      h2aendern(2);
      end; 
  37: ;
  38: gpr_$text('Es gibt bereits einen Typ mit diesem Namen.',43,status);
  39: gpr_$text('Das Element wurde nicht geloescht und nicht veraednert.',55,status);
  40: gpr_$text('Typname wird verwendet, darf nicht geloescht werden.',52,status);
  41: gpr_$text('Attribut ist bereits in der Attributierung vorhanden.',53,status);
  42: gpr_$text('Sem. Funktionen muessen mind. ein Ergebnis abliefern.',53,status);
  43: gpr_$text('Die Produktion besitzt keine Terminale.',39,status);
  44: begin dekodhl(typeHL,s); wrtIdent(s); gpr_$text(noname,34,status) end;
  49: begin dekodhl(typeHL,s); wrtIdent(s); gpr_$text(redef,36,status) end;
  50: gpr_$text('Zahl darf den Wert 9999 nicht uebersteigen.',43,status);
  51: gpr_$text('Kein Lesezugriff auf diese Datei !',34,status);
  52: begin
      gpr_$text('Kein Schreibzugriff auf diese Datei oder keine',46,status); 
      nextline;
      gpr_$text('Schreibberechtigung im angesprochenen Directory!',48,status);
      nextline;
      gpr_$text('Bitte anderen Dateinamen waehlen!',27,status);
      h2aendern(3);
      end;
  53: begin
      gpr_$text('Die Datei AG\[tmp\] sollte bei Programmstart im aktuellen',57,status);
      nextline;
      gpr_$text('Directory nicht existieren. Bitte loeschen oder umbenennen!',59,status);
      h2aendern(2);
      end;
  54: begin 
      gpr_$text('Die Datei AG.tmp.$$$ laesst sich im aktuellen',45,status);
      nextline;
      gpr_$text('Directory nicht schreiben!',20,status);
      nextline;
      gpr_$text('Bitte schreibenden Zugriff auf diese Datei ermoeglichen.',56,status);
      h2aendern(3);
      end;
  55: gpr_$text('Der angegebene Name bezeichnet ein Directory, keine Datei!',58,status);
  56: gpr_$text('Es darf kein Directory mit Namen AG.tmp.$$$ existieren !',56,status);
  57: begin gpr_$text(empty,27,status); dekodhl(typeHL,s); wrtIdent(s) end;
  58: begin
      gpr_$text('Bitte Schreibzugriff fuer Datei "fehlerspur" ermoeglichen',57,status); 
      nextline;
      gpr_$text('und Programm neu starten.',19,status);
      h2aendern(2);
      end;
  59: begin
      gpr_$text('Die Grammatik kann nicht eingelesen werden. Sie muss',52,status);
      nextline;
      gpr_$text('erst durch das Programm "resize" transformiert werden.',54,status);
      h2aendern(2);
      end;
  60: gpr_$text('Die Attributsymboldatei kann nicht eingelesen werden.',53,status);
  61: gpr_$text('WARNUNG: Syntax-Fehler in der Spezifikation !',45,status);
  62: gpr_$text('WARNUNG: ERROR-Element in der Internform gefunden !',51,status);
  end (*case*);
nextline;
gpr_$text('   Mit beliebiger Taste gehts weiter...',40,status); {## ''}
cread (c);
Meldungen := 1;
clearmeldung;
end; (* meldefehler *)


procedure meldeueberlauf(* hl: HashListen; frei: integer*);
var h1,h2: integer;
    c: char;
begin
h1:=rbs.yhome-Meldungen*rbs.zhoehe; setCursor(h1,0);
if frei<warn then gpr_$text(' WARNUNG',8,status) else gpr_$text(' Vorwarnung',11,status);
gpr_$text(': Hashtabelle der ',18,status);
case hl of
  prodHL: gpr_$text('Produktionen',12,status);
  nontHL: gpr_$text('Nonterminale',12,status);
  termHL: gpr_$text('Terminale',9,status);
  attrHL: gpr_$text('Attribute',9,status);
  typeHL: gpr_$text('Typnamen',8,status);
  sfktHL: gpr_$text('Funktionen',10,status);
  end (*case*);
if frei>=warn then gpr_$text(' nahezu',7,status);
gpr_$text(' voll.',6,status);
newline;
if frei >= warn then h2:=h1-2*rbs.zhoehe
else
  begin
  gpr_$text(' Bitte die laufende Aktion abschliessen, Grammatik speichern, Massnahmen gem.',77,status);
  newline;
  gpr_$text(' Punkt "Beschraenkungen" d. Dokumentation ergreifen.',52,status);
  h2:=h1-3*rbs.zhoehe;
  end;
gpr_$text(' Mit # gehts weiter...',13,status); {##''}
repeat cread(c) until c='#';
loesche4eck(h2,h1,0,rbs.xpixels);
end (*meldeueberlauf*);


function globaendern(* pmb,gef: integer): boolean *);
var c: char;
begin
if (pmb=0) and (gef=0) then globaendern:=true
else
  begin
  meldung(50);
  meldung(51);
  if gef>0
   then meldung(52);
  meldung(53);
  antworte(janein,c);
  globaendern:= c='J';
  clearmeldung;
  end;
end;


procedure editname(* y,x: integer; hl: HashListen; var s: Ident *);
var gross,EOL: boolean;
    i,zsa: integer;
    zulchs: set of char;
    c: char; 
    a,b:integer;

  function cw(c: char): char;
  begin
  if hl=noList then cw:=c
  else
  if gross then if (c>='a') and (c<='z') then cw:=chr(ord(c)+zsa) else cw:=c
           else if (c>='A') and (c<='Z') then cw:=chr(ord(c)-zsa) else cw:=c
  end;

begin (*editname*)
zsa := ord('A')-ord('a');
gross:=hl in [prodHL,termHL,attrHL];
zulchs:=['a'..'z','A'..'Z','0'..'9'];
if hl<>noList then zulchs:=zulchs+[PraefixTab[1],PraefixTab[2],PraefixTab[3]];
if hl=sfktHL then zulchs:=zulchs+[IDchar];
if (ord(s[0])<=0) or (ord(s[0])>idlaenge) then s[0]:=chr(0);
for i:=1 to ord(s[0]) do s[i]:=cw(s[i]);
for i:=succ(ord(s[0])) to idlaenge do s[i]:=blk;
loeschewort(y,x,succ(ord(s[0])));
wrtIdent(s);
EOL:=false;
setCursor(y,x+ord(s[0])*rbs.zbreite);
repeat (*until eoln*)  
 cursoron;
 cread(c);                           
 cursoroff;
 if (c=chr(13)) 
  then begin
        EOL:=true;
       end 
  else
    begin 
    if (c = PraefixTab[1]) then EOL := true;
    if ord(c)=127 then
      begin
      if ord(s[0])<>0 then
        begin with rbs do
          begin
          s[ord(s[0])]:=blk;
	  s[0]:=chr(pred(ord(s[0])));
          backspace(y,x,ord(s[0]));
	  end
        end
      end
    else if c in zulchs then
      begin
      if ord(s[0])=0 then
        begin
        s[0]:=chr(1); s[1]:=cw(c);
      	setCursor(y,x); 
        gpr_$text(s[1],1,status);
        setCursor(y,x+rbs.zbreite);
        end
      else if (formpraefixop(s[ord(s[0])])<>0) or (s[ord(s[0])]=IDchar) then
        begin with rbs do
          begin
          meldefehler(5);
          setCursor(y,x+dist(ord(s[0])));
          end
        end
      else if ord(s[0])=idlaenge then
        begin with rbs do
          begin
          meldefehler(6);
          setCursor(y,x+dist(ord(s[0])));
          end
        end
      else
        begin
	s[0]:=chr(succ(ord(s[0])));
	s[ord(s[0])]:=cw(c);
        gpr_$text(cw(c),1,status);
        cursorpos(a,b);
        setCursor(a,b+rbs.zbreite);
        end
      end
    else (* c not in zulchs *) beep;
    end;
  ;                  
until EOL;
end (* editname *);

function readnat4 (* y,x: integer: integer *);
var s: Ident; 
    lg,res,i: integer; 
    fehler: boolean;
begin 
repeat fehler:=false;
  s[0]:=chr(0);
  editname(y,x,noList,s);
  lg:=ord(s[0]);
  for i:=1 to lg do fehler:=fehler or  not (s[i] in ['0'..'9']);
  if fehler then 
    begin
    meldefehler(3);
    loeschewort(y,x,4);
    end
  else
    begin
    if lg>4 then
      begin
      meldefehler(3);
      loeschewort(y,x,4);
      fehler:=true;
      end
    else
      begin
      res:=0;
      for i:=1 to lg do res:=10*res+ord(s[i])-ord('0');
      readnat4:=res;
      end;
    end;
until not fehler;
end;


procedure readTersatz(* y,x,t: integer *);
var EOL: boolean;
    lg,a,b: integer;
    c: char;
    s: array[0..3] of char;
begin
for lg:=0 to 3 do s[lg]:=blk;
loeschewort(y,x,2);
EOL:=false; lg:=0;
repeat    
  {gpr_$set_cursor_active(true,status);}
  cursoron;
  cread(c);
  cursoroff;                           
  {gpr_$set_cursor_active(false,status);}
  if c=chr(13) then 
    begin
    EOL:=true; 
    end
  else
    begin
    if ord(c)=127 then
      begin
      if lg>0 then
	begin
	with rbs do
	  begin
	  s[lg]:=blk;
	  lg:=pred(lg);
	  backspace(y,x,lg);
	  end
	end
      end
    else
      begin
      if lg>=2 then begin beep; beep; end
      else
	begin
	lg:=succ(lg);
	if c<blk then c:=blk;
	s[lg]:=c;
	gpr_$text(c,1,status);
    cursorPos(a,b);
    setCursor(a,b+rbs.zbreite);
	end
      end
    end
  ;
until EOL;
with TTab[t] do
  begin
  sz1:=s[1];
  sz2:=s[2];
  if lg=2 then if (sz1=blk) then if (sz2<>blk) then 
    begin sz1:=sz2; sz2:=blk
    end;
  end;
end (*readTersatz*);


procedure sfparmkd(* plusaktpar: boolean; y0,sf,pp: integer; var y1,xalt: integer *);
label 1;
const llrand=1;
var azhoehe,lrand, rrand, i, iparms, oparms, x1: integer;
    error: boolean;
    pl: TypListe;
    proc: filename;

  procedure zaehlefort(nml, szl: integer);
  var deltax1: integer;
  begin
  if plusaktpar and (nml>0) and (nml<3) then deltax1:=3 else deltax1:=nml;
  deltax1:=deltax1+szl;
  if x1+deltax1>rrand then
    begin
    x1:=succ(lrand); y1:=y1-azhoehe;
    end;
  xalt:=x1;
  x1:=x1+deltax1;
  end;

begin (*sfparmkd*)
if plusaktpar then azhoehe:=gibazh(IconsUeberText) else azhoehe:=gibazh(nurText);
proc:='sfparmkd ';
(* folgende zeile muss mit der entsprechend gekennzeichneten in procedure
   signatur uebereinstimmen *)
lrand:=succ(idlaenge)+llrand; rrand:=77; x1:=lrand; xalt:=x1; y1:=y0;

with SFTab[sf] do
  begin
  iparms:=lgtl(parlist); oparms:=lgtl(erglist);
  if pp<0 then error:=(-pp<1) or (-pp>iparms)
	  else error:=(pp<1) or (pp>oparms);
  if error then wrtERR2(proc,'[1]')
  else
    begin
    if parlist=nil then (*skip*)
    else
      begin x1:=succ(x1); xalt:=x1; i:=1; pl:=parlist;
      while i<iparms do
	begin zaehlefort(ord(TypTab[pl^.typ].name[0]),2);
	if i=-pp then goto 1
	else
	  begin
	  i:=succ(i); pl:=pl^.nxt;
	  end;
	end;
      zaehlefort(ord(TypTab[pl^.typ].name[0]),1);
      if -pp=iparms then goto 1;
      end;
    zaehlefort(0,2);
    if erglist=nil then wrtERR2(proc,'[2]')
    else
      begin
      i:=1; pl:=erglist;
      while i<oparms do
	begin zaehlefort(ord(TypTab[pl^.typ].name[0]),2);
	if i=pp then goto 1
	else
	  begin
	  i:=succ(i); pl:=pl^.nxt;
	  end
	end;
      zaehlefort(ord(TypTab[pl^.typ].name[0]),1);
      end;
    1:  
    end;
  end
end (*sfparmkd*);


procedure loeschesignatur (* plusaktpar: boolean; y0: integer; sf: integer *);
var azhoehe,y,x: integer;
begin
if plusaktpar then azhoehe:=gibazh(IconsUeberText) else azhoehe:=gibazh(nurText);
sfparmkd(plusaktpar,y0,sf,lgtl(SFTab[sf].erglist),y,x);
loesche4eck(y-3,y0+azhoehe-1,0,rbs.xpixels);
end (*loeschesignatur*);


procedure signatur(* plusaktpar: boolean; y0,sf: integer *);
const llrand=1;
var dummy: Ident;
    azhoehe,lrand,x1,iparms,oparms,i,y1,rrand: integer;
    pl: TypListe;

  procedure schreibe(var nm: Ident; szlg: integer; sz1,sz2: char);
  var lg: integer;
      expands: Ident;
  begin
  expands:=nm;
  lg:=ord(expands[0]);
  if (lg<3) and plusaktpar then
    begin
    case lg of
      0: ;
      1: begin
	 expands[1]:=blk; expands[2]:=nm[1]; expands[3]:=blk; expands[0]:=chr(3);
	 end;
      2: begin
	 expands[3]:=blk; expands[0]:=chr(3);
	 end;
      end (*case*);
    lg:=ord(expands[0]);
    end;
  lg:=lg+szlg;
  if x1+lg>rrand then
    begin
    x1:=succ(lrand); y1:=y1-azhoehe;
    end;
  setCursor(y1,x1*rbs.zbreite); wrtIdent(expands);
  if szlg=1 then gpr_$text(sz1,1,status)
  else if szlg=2 then begin gpr_$text(sz1,1,status); gpr_$text(sz2,1,status)  end
  else wrtERR1('signatur:schreibe');
  x1:=x1+lg;
  end (*schreibe*);

begin (*signatur*)
if plusaktpar then azhoehe:=gibazh(IconsUeberText) else azhoehe:=gibazh(nurText);
dummy[0]:=chr(0);
(* die folgende zeile muss mit der entsprechend gekennzeichneten zeile in
   procedure sfparmkd uebereinstimmen: *)
lrand:=succ(idlaenge)+llrand; x1:=lrand; rrand:=77; y1:=y0;

with SFTab[sf] do
  begin
  iparms:=lgtl(parlist); oparms:=lgtl(erglist);
  setCursor(y0,llrand*rbs.zbreite); wrtIdent(name);
  if parlist<>nil then
    begin
    setCursor(y1,x1*rbs.zbreite); gpr_$text('(',1,status); x1:=succ(x1);
    pl:=parlist;
    for i:=1 to pred(iparms) do
      begin
      schreibe(TypTab[pl^.typ].name,2,',',blk);
      pl:=pl^.nxt;
      end;
    schreibe(TypTab[pl^.typ].name,1,')',blk);
    end;
  schreibe(dummy,2,':',blk);
  if oparms=0 then wrtERR1('signatur')
  else
    begin
    pl:=erglist;
    for i:=1 to pred(oparms) do
      begin
      schreibe(TypTab[pl^.typ].name,2,',',blk);
      pl:=pl^.nxt;
      end;
    schreibe(TypTab[pl^.typ].name,1,';',blk);
    end;
  end (*with*);
end (*signatur*);


procedure signatur1(* svk: SemFktListe *);
const plusaktpar=true;
var y0,vz,i,pm,x1,y1,pr,pos: integer;
    apl: ParListe;
    fpl: TypListe;
begin
y0:=rbs.uRandvBild-gibazh(IconsUeberText);
with svk^,SFTab[svk^.semfkt] do
  begin
  signatur(plusaktpar,y0,semfkt);
  vz:=-1; fpl:=parlist; apl:=quellpar;
  for i:=0 to 1 do
    begin
    for pm:=1 to lgtl(fpl) do
      begin
      sfparmkd(plusaktpar,y0,semfkt,vz*pm,y1,x1);
      y1:=y1+rbs.zhoehe; x1:=(x1+(ord(TypTab[fpl^.typ].name[0]) div 2))*rbs.zbreite;
      if apl^.vok=nil then
	begin
        if apl^.attr=0 then (* unversorgt, skip*)
	else writeikon(y1,x1,ATab[apl^.attr].symbol);
	end
      else
	begin
	sucheVg(apl^.vok,pr,pos);
	if apl^.attr=0 then 
	  begin (*terminal*)
	  setCursor(y1,x1); writeint(pos);
	  end
	else
	  begin (* NT-Attr*)
	  setCursor(y1,x1-rbs.zbreite); writeint(pos); gpr_$text(':',1,status);
	  writeikon(y1,x1+rbs.zbreite,ATab[apl^.attr].symbol);
	  end;
	end;
      fpl:=fpl^.nxt; apl:=apl^.nxt;
      end (*for pm*);
    vz:=1; fpl:=erglist; apl:=zielpar;
    end (*for i*);
  end (*with*);
end (*signatur1*);


procedure signatur2(* sfv: SemFktListe; vok: VokListe; attr, parpos: integer *);
const plusaktpar=true;
var fpl: TypListe;
    y0, pr, pos, i, y, x: integer;
begin
y0:=rbs.uRandvBild-gibazh(IconsUeberText);
if parpos>0 
then fpl:= SFTab[sfv^.semfkt].erglist 
else fpl:= SFTab[sfv^.semfkt].parlist;
for i:= 1 to abs(parpos)-1 do fpl:= fpl^.nxt;
sfparmkd( plusaktpar, y0, sfv^.semfkt, parpos, y, x );
y:=y+rbs.zhoehe;
x:=(x+(ord(TypTab[fpl^.typ].name[0]) div 2))*rbs.zbreite;
male4eck(true,y,y+gibazh(IconsMitText)+4,x-rbs.zbreite,x+rbs.zbreite+ASymb.breite);
if vok=nil
then begin
     if attr=0 then (* null *) else writeikon(y,x,ATab[attr].symbol);
     end
else begin
     sucheVg( vok, pr, pos );
     if attr=0
     then begin setCursor(y,x); writeint(pos) end
     else begin
          setCursor(y,x-rbs.zbreite); writeint(pos); gpr_$text(':',1,status);
          writeikon(y,x+rbs.zbreite,ATab[attr].symbol)
          end
     end;
end (*signatur2*);


procedure liesIdent(* y,x: integer; hl: HashListen; var s: Ident *);
var okay: boolean;
begin
repeat
  editname(y,x,hl,s); 
  okay:=isIdent(s); 
  if not okay then meldefehler(1);
until okay;
end;


procedure blinkkoord (* v: VokListe; var yo,yu,xl,xm,xr: integer *);
var lg: integer;
begin
with v^ do
  begin
  if typ=term then
    begin
    with TTab[t] do
      begin
      if sz1=' ' then lg:=dist(ord(name[0])+1)
      else
	begin
	if sz2=' ' then lg:=dist(2) else lg:=dist(3)
	end
      end;
    end
  else lg:=dist(ord(NTTab[nt].name[0])+1);
  end (*with*);
with rbs, v^ do
  begin
  yo:=Y+R1; yu:=Y-R1;
  xl:=X; xr:=X+lg; xm:=(xl+xr) div 2;
  end;
end; (*blinkkoord*)


procedure blinkersatz (* vaterpos, ein: boolean *);
var y,x,delta: integer;
begin
if not LAZY then
  begin
  with PTab[aktPNr], rbs do
    begin
    if vaterpos then
      begin
      if vater<>nil then wrtERR1('blinkersatz[1]')
      else y:=uRandvBild+((9*vBildHoehe) div 10);
      end
    else
      begin
      if soehne<>nil then wrtERR1('blinkersatz[2]')
      else y:=uRandvBild+((2*vBildHoehe) div 10);
      end;
    delta:=3*zbreite; x:=xpixels div 2;
    male4eck(not ein, y+R1-2, y+R1, x-delta, x+delta);
    male4eck(not ein, y-R1, y-R1+2, x-delta, x+delta);
    male4eck(not ein, y-R1, y+R1, x-delta, x-delta+2);
    male4eck(not ein, y-R1, y+R1, x+delta-2, x+delta);
    end
  end
end (*blinkersatz*);


procedure blinke (* pr: integer; pos: integer; ein: boolean *);
var yo,yu,xl,xm,xr: integer;
begin
if not LAZY then
  begin
  blinkkoord(gibVzupos(pr,pos),yo,yu,xl,xm,xr);
  invertBild(xl+1,yu,xr-xl-1,yo-yu-1);
  end;
end (*blinke*);


procedure blinkelinks(* pr,pos: integer; ein:boolean *);
var yo,yu,xl,xr,xm: integer;
begin
if not LAZY then
  begin
  blinkkoord(gibVzupos(pr,pos),yo,yu,xl,xm,xr);
  invertBild(xl+1,yu,xm-xl,yo-yu-1);
  end;
end;


procedure blinkerechts(* pr,pos: integer; ein: boolean *);
var yo,yu,xl,xr,xm: integer;
begin
if not LAZY then
  begin
  blinkkoord(gibVzupos(pr,pos),yo,yu,xl,xm,xr);
  invertBild(xm,yu,xr-xm,yo-yu-1);
  end;
end;


procedure regelkoord(* y0,pr,pos: integer; var y,x: integer *);
const rRand=79;
      lRand=1;
var p,anzsoehne,cp,snr,lg,cpalt: integer;
    s: VokListe;
begin
with PTab[pr],rbs do
  begin
  if pos=0 then   
    begin
    y:=y0; x:=lRand;
    end
  else
    begin
    s:=soehne; anzsoehne:=0; y:=y0; cp:=idlaenge+lRand+3; x:=cp;
    while s<>nil do
      begin
      anzsoehne:=succ(anzsoehne);
      s:=s^.nxt;
      end;
    if pos>succ(anzsoehne) then wrtERR1('regelkoord')
    else
      begin
      if pos>anzsoehne then p:=anzsoehne else p:=pos;
      s:=soehne; snr:=0;
      while s<>nil do
	begin
	snr:=succ(snr);
	if s^.typ=nont then lg:=ord(NTTab[s^.nt].name[0]) else lg:=ord(TTab[s^.nt].name[0]);
	if cp+lg>=rRand-2 then
	  begin
	  cp:=idlaenge+lRand+3;
	  y:=y-zhoehe;
	  end;
	cpalt:=cp;
	cp:=cp+lg+2;
	if snr=p then
	  begin
	  if pos>anzsoehne then x:=cp else x:=cpalt;
	  s:=nil;
	  end
        else s:=s^.nxt;
	end (*while*);
      end;
    end;
  end;
end (*regelkoord*);


procedure regel (* y0,pr: integer *);
const rRand=79;
      lRand=1;
      rand=5; (*sollte mit "rand" aus Prozedur defmaske uebereinstimmen*)
var anzsoehne,y,x,cp,lg: integer;
    s: VokListe;
    nm: Ident;
begin
with PTab[pr],rbs do
  begin
  s:=soehne; anzsoehne:=0;
  while s<>nil do
    begin
    s:=s^.nxt; anzsoehne:=succ(anzsoehne);
    end;
  regelkoord(y0,pr,anzsoehne,y,x);
  loesche4eck(y-rbs.zhoehe,pred(y0+zhoehe),succ(rand),rbs.xpixels-succ(rand));
  if vater<>nil then 
    begin
    setCursor(y0,lRand*rbs.zbreite); wrtIdent(NTTab[vater^.nt].name);
    end;
  setCursor(y0,(idlaenge+lRand)*zbreite); gpr_$text('->',2,status);
  y:=y0; cp:=idlaenge+lRand+3;
  s:=soehne;
  while s<>nil do
    begin
    if s^.typ=nont then nm:=NTTab[s^.nt].name else nm:=TTab[s^.t].name;
    lg:=ord(nm[0]);
    if cp+lg>=rRand-2 then
      begin
      cp:=idlaenge+lRand+3;
      y:=y-zhoehe;
      end;
    setCursor(y,cp*zbreite); wrtIdent(nm);
    cp:=cp+lg+2;
    s:=s^.nxt;
    end;
  end;
end (*regel*);


procedure Pcontr (* y0,pr: integer; modus: char; var pos: integer *);
var s: VokListe;
    anzsoehne,uindexgr,oindexgr,y,x,yh,xh: integer;
    c: char;
begin
if (modus<>'e') and (modus<>'s') then wrtERR1('Pcontr [1]')
else if (modus='s') and (PTab[pr].vater=nil) and (PTab[pr].soehne=nil) then
  begin
  meldefehler(35);
  pos:=-1;
  end
else
  begin
  with PTab[pr] do
    begin
    s:=soehne; anzsoehne:=0;
    while s<>nil do
      begin
      anzsoehne:=succ(anzsoehne);
      s:=s^.nxt;
      end;
    if ((modus='e') and (vater=nil)) or ((modus='s') and (vater<>nil)) then uindexgr:=0 else uindexgr:=1;
    if modus='e' then oindexgr:=succ(anzsoehne) else oindexgr:=anzsoehne;
    pos:=uindexgr;
    repeat
      if modus='s' then 
	begin
	blinke(pr,pos,true);
	regelkoord(y0,pr,pos,y,x);
	if pos = 0 then xh := x + idlaenge
	           else regelkoord(y0,pr,succ(pos),yh,xh)
	end
      else
	begin
	if pos=0 then 
          begin
	  if vater=nil then blinkersatz(true,true) else blinke(pr,pos,true)
	  end
	else if pos=1 then 
	  begin
	  if soehne=nil then blinkersatz(false,true) else blinkelinks(pr,pos,true)
	  end
	else if pos>anzsoehne then blinkerechts(pr,anzsoehne,true)
	else
	  begin
	  blinkerechts(pr,pred(pos),true);
	  blinkelinks(pr,pos,true);
	  end;
	regelkoord(y0,pr,pos,y,x);
	x := x - 1;
	xh := x + 2
	end;    
      invertBild(x*rbs.zbreite-4,y-4,(xh-x-1)*rbs.zbreite,rbs.zhoehe);
      repeat move_read(c) until c in ['0','2','4','6','8',trz];
      invertBild(x*rbs.zbreite-4,y-4,(xh-x-1)*rbs.zbreite,rbs.zhoehe);
      if modus='s' then blinke(pr,pos,false)
      else
	begin
	if pos=0 then 
	  begin
	  if vater=nil then blinkersatz(true,false) else blinke(pr,pos,false)
	  end
	else if pos=1 then 
	  begin
	  if soehne=nil then blinkersatz(false,false) else blinkelinks(pr,pos,false)
	  end
	else if pos>anzsoehne then blinkerechts(pr,anzsoehne,false)
	else
	  begin
	  blinkerechts(pr,pred(pos),false);
	  blinkelinks(pr,pos,false);
	  end;
	end;
      case c of
	'0': pos:= -1; (*undo*)
	'4': if pos>uindexgr then pos:=pred(pos) else pos:=oindexgr;
	'6': if pos<oindexgr then pos:=succ(pos) else pos:=uindexgr;
	'2': pos:=uindexgr;
	'8': pos:=oindexgr;
	trz: ;
	end (*case*);
      ;
    until (c='0') or (c=trz);
    end (*with*);
  end;
end (*Pcontr*);


procedure Pcontr2 (* y0,pr: integer; modus: char; var pos: integer *);
var s: VokListe;
    anzsoehne,uindexgr,oindexgr,y,x: integer;
    c: char;
begin
if (modus<>'e') and (modus<>'s') then wrtERR1('Pcontr2 [1]')
else if (modus='s') and (PTab[pr].vater=nil) and (PTab[pr].soehne=nil) then
  begin
  meldefehler(35);
  pos:=-1;
  end
else
  begin
  with PTab[pr] do
    begin
    s:=soehne; anzsoehne:=0;
    while s<>nil do
      begin
      anzsoehne:=succ(anzsoehne);
      s:=s^.nxt;
      end;
    if ((modus='e') and (vater=nil)) or ((modus='s') and (vater<>nil)) then uindexgr:=0 else uindexgr:=1;
    if modus='e' then oindexgr:=succ(anzsoehne) else oindexgr:=anzsoehne;
    pos:=uindexgr;
    repeat
      regelkoord(y0,pr,pos,y,x);
      if modus='s' then setCursor(y,x*rbs.zbreite) else setCursor(y,pred(x)*rbs.zbreite); 
      {gpr_$set_cursor_active(true,status);}
      cursoron;
      repeat move_read(c) until c in ['0','2','4','6','8',trz]; 
      {gpr_$set_cursor_active(false,status);}
      cursoroff;
      case c of
	'0': pos:= -1; (*undo*)
	'4': if pos>uindexgr then pos:=pred(pos) else pos:=oindexgr;
	'6': if pos<oindexgr then pos:=succ(pos) else pos:=uindexgr;
	'2': pos:=uindexgr;
	'8': pos:=oindexgr;
	trz: ;
	end (*case*);
      ;
    until (c='0') or (c=trz);
    end (*with*);
  end;
end (*Pcontr2*);


procedure NTvContr(* modus: char; istvater: boolean; ntv: VokListe; var Apos: integer *);
var anzia, anzda, index, lg, cx, cy, vpos: integer;
    c: char;

  function pos(index: integer): integer;
  begin
  if index<=anzia then pos:=index-succ(anzia) else pos:=index-anzia;
  end;

  function xp(p: integer): integer;
  begin
  if p<0 then xp:=ntv^.X+p*2*ASymb.breite else xp:=ntv^.X+lg-ASymb.breite+1+2*p*ASymb.breite;
  end;

begin
with ntv^, rbs do
  begin
  if (modus<>'e') and (modus<>'s') then wrtERR1('NTvContr[0]')
  else if typ=term then wrtERR1('NTvContr[1]')
  else
    begin
    if konsistent then
      begin
      anzia:=lgAL(NTTab[nt].inhAttr); 
      anzda:=lgAL(NTTab[nt].derAttr);
      end
    else
      begin
      anzia:=lgAL(spezInhA);
      anzda:=lgAL(spezDerA);
      end;
    if modus='e' then
      begin
      anzia:=succ(anzia);
      anzda:=succ(anzda);
      end;
    if (anzia<=0) and (anzda<=0) then wrtERR1('NTvContr[2]')
    else
      begin sucheVl(aktPNr,ntv,vpos); if not LAZY then blinke(aktPNr,vpos,true);
      lg:=dist(succ(ord(NTTab[nt].name[0])));
      if istvater then cy:=ntv^.Y+(ASymb.hoehe div 2)+5 else cy:=ntv^.Y-(ASymb.hoehe div 2)-zhoehe-5;
      if anzda>0 then index:=succ(anzia) else index:=anzia;
      repeat
	cx:=xp(pos(index));
	if modus='e' then
	  begin
	  if pos(index)>0 then cx:=cx-zbreite else cx:=cx+zbreite;
	  end;
	if (cx>=0) and ((cx+ASymb.breite-1)<=xpixels) then setCursor(cy,cx)
	else wrtERR1('NTvContr[3]');  
    {gpr_$set_cursor_active(true,status);}
    cursoron;
	repeat move_read(c) until c in ['0','4','6',trz]; 
    {gpr_$set_cursor_active(false,status);}
    cursoroff;
	case c of
	  '0': Apos:=0;
	  '4': if index>1 then index:=index-1 else index:=anzia+anzda;
	  '6': index:=succ(index mod (anzia+anzda));
	  trz: Apos:=pos(index);
	  end (*case*);
      until (c='0') or (c=trz);
      if not LAZY then blinke(aktPNr,vpos,false);
      end
    end;
  end;
end; (*NTvContr*)


procedure waehleAv(* y0: integer; modus: char; var vpos,apos: integer *);
label 128;
var ntv: VokListe;

  procedure zeigeglobA (nt: integer);
  const uRand=20; (*sicherheitsabstand vom unteren bildrand*)
  var abst,b,o1,o2: integer;
      al: AListe;
  begin
  b:=ord(NTTab[nt].name[0])+10; if odd(b) then b:=succ(b);
  b:=b div 2;
  o1:=(40-b)*rbs.zbreite - ASymb.breite;
  o2:=(40+b)*rbs.zbreite;
  abst:=round(1.5*ASymb.breite);
  with NTTab[nt] do
    begin 
    if (inhAttr=nil) and (derAttr=nil) then
      begin setCursor(uRand,0);
      gpr_$text(' Nonterminal ',14,status); wrtIdent(name); gpr_$text(' bisher ohne globale Attribute!',31,status);
      end
    else
      begin setCursor(uRand,(41-b)*rbs.zbreite);
      wrtIdent(NTTab[nt].name); gpr_$text(' (glob.)',8,status);
      al:=inhAttr;
      while al<>nil do
	begin
	writeikon(uRand,o1,ATab[al^.attr].symbol);
	al:=al^.nxt;
	o1:=o1-abst;
	end;
      al:=derAttr;
      while al<>nil do
	begin
	writeikon(uRand,o2,ATab[al^.attr].symbol);
	al:=al^.nxt;
	o2:=o2+abst;
	end;
      end;
    end;
  end (*zeigeglobA*);

begin
128:
with rbs do
  begin
  male4eck(true,0,y0+zhoehe,0,xpixels);
  setCursor(y0,0);
  gpr_$text(' Bestimmen Sie bitte das Nonterminal, dessen Attributierung zu aendern ist',74,status);
  regel(y0-zhoehe,aktPNr);
  Pcontr(y0-zhoehe,aktPNr,'s',vpos);
  if vpos<0 then apos:=0
  else 
    begin ntv:=gibVzupos(aktPNr,vpos);
    if ntv^.typ=term then
      begin
      meldefehler(34);
      vpos:=-1; apos:=0;
      end
    else
      begin
      male4eck(true,0,y0+zhoehe,0,xpixels);
      setCursor(y0,0);
      if modus='s' then gpr_$text(' Bestimmen Sie bitte das zu streichende Attribut',48,status)
      else gpr_$text(' Bestimmen Sie bitte die Position, auf welcher Attribut zu ergaenzen ist',72,status);
      zeigeglobA(ntv^.nt);
      NTvContr(modus,vpos=0,ntv,apos);
      if apos=0 then goto 128
      end
    end;
  end
end (*waehleAv*);

procedure waehleformPar (* plusaktpar: boolean; y0,sf: integer; modus: char; typcheck: boolean; typname: integer; var pos: integer; var fp: TypListe *);

var azhoehe,lasty,dummx,k,iparms, oparms, i, index, x, y, hx, hy, len: integer;
    typex, ende, synt: boolean;
    c: char;
    proc: filename;
    pl: TypListe;

  function p(index: integer): integer;
  begin
  if index<=iparms then p:= -index else p:=index-iparms;
  end;

  function passttyp(pos: integer): boolean;
  var pl: TypListe;
      i: integer;
  begin
  if pos<0 then pl:=SFTab[sf].parlist else pl:=SFTab[sf].erglist;
  for i:=1 to pred(abs(pos)) do pl:=pl^.nxt;
  passttyp:= typname=pl^.typ;
  end (*passttyp*);

  procedure cursorweiter(i: integer);
  var ende: boolean;
  begin
  if typcheck then
    begin
    repeat
      if index<=iparms then index:=succ(iparms);
      ende:=passttyp(p(index));
      if not ende then index:=index+i;
    until ende;
    end;
  end (*cursorweiter*);

begin (*waehleformPar*)
proc:='waehleformPar';
synt:=SFTab[sf].issynfkt and (modus = 'e');
if (modus<>'e') and (modus<>'s') then wrtERR2(proc,'[1]')
else if (modus='e') and typcheck then wrtERR2(proc,'[3]')
else
  begin
  if plusaktpar then azhoehe:=gibazh(IconsUeberText) else azhoehe:=gibazh(nurText);
  with SFTab[sf] do
    begin
    iparms:=lgtl(parlist); oparms:=lgtl(erglist);
    if modus='s' then
      begin
      if oparms=0 then wrtERR2(proc,'[3]')
      else
	begin
	sfparmkd(plusaktpar,y0,sf,oparms,lasty,dummx);
	gpr_$set_draw_value(-2,status);
        for k:=0 to (lasty-y0) div azhoehe do linie(y0-k*azhoehe-3,0,y0-k*azhoehe-3,rbs.xpixels);  
	gpr_$set_draw_value(color_base,status);
	if typcheck then
	  begin
	  typex:=false;
	  pl:=parlist;
	  for i:=0 to 1 do
	    begin
	    while (pl<>nil) and (not typex) do
	      begin
	      typex:= pl^.typ=typname;
	      pl:=pl^.nxt;
	      end;
	    pl:=erglist;
	    end (*for*);
	  end (*if typcheck*)
	else typex:=true;
	end
      end (*if modus='s'*)
    else
      begin
      iparms:=iparms+1;
      oparms:=oparms+1;
      typex:=true;
      end;
    if typex then
      begin
      index:=pos;
      if (index<1) or (index>(iparms+oparms)) then index:=succ(iparms);
      if synt then index:=1;
      cursorweiter(1);
      pos:=p(index);
      sfparmkd(plusaktpar,y0,sf,pos,y,x); if modus='e' then x:=x-1;
      repeat
	if pos<0 then fp:=parlist else fp:=erglist;
	for i:=1 to pred(abs(pos)) do fp:=fp^.nxt;
	if modus = 'e' then len := rbs.zbreite
		       else len := dist(ord(TypTab[fp^.typ].name[0]));
        hx:=x*rbs.zbreite; hy:=y-3; 
	invertBild(hx,hy,len,rbs.zhoehe);
	repeat move_read (c) until c in ['0','2','4','5','6','8',trz];
	invertBild(hx,hy,len,rbs.zhoehe);
	case c of
	  '0': begin 
	       sfparmkd(plusaktpar,y0,sf,lgtl(erglist),y,x);
	       with rbs do male4eck(true,y-3,y0+zhoehe+ASymb.hoehe,0,xpixels);
               pos:=0; fp:=nil 
               end;
	  '2': begin
	       index:=1; cursorweiter(1);
	       end;
	  '4': begin
	       if index>1
                then index:=index-1
                else if synt then index:=iparms 
                             else index:=iparms+oparms;
	       cursorweiter(-1);
	       end;
	  '5': begin
                if synt then (*index:=(iparms div 2)*)
                else index:=succ(iparms); cursorweiter(1);
	       end;
	  '6': begin
                if synt
                 then index:=succ(index mod iparms) 
                 else index:=succ(index mod (iparms+oparms));
	       cursorweiter(1);
	       end;
	  '8': begin
               if synt 
                then index:=iparms 
	        else index:=iparms+oparms;
	       cursorweiter(-1);
	       end;
	  trz: begin
	       pos:=p(index);
	       if modus='s' then
		 begin
		 if pos<0 then fp:=parlist else fp:=erglist;
		 for i:=1 to pred(abs(pos)) do fp:=fp^.nxt;
                 hx:=x*rbs.zbreite; hy:=y-3; 
		 linie(hy,hx,hy,hx+dist(ord(TypTab[fp^.typ].name[0])));
		 end
	       else fp:=nil;
	       end;
       otherwise ;
	  end; (*case*) 
	ende:=(c='0') or (c=trz);
	if not ende then
	  begin
	  pos:=p(index);
	  if modus='e' then
	    begin
	    if (iparms=1) and (pos=-1) then
	      begin
	      y:=y0; x:=idlaenge;
	      end
	    else if pos= -iparms then
	      begin
	      sfparmkd(plusaktpar,y0,sf,-iparms+1,y,x);
	      pl:=parlist;
	      for i:=1 to iparms-2 do pl:=pl^.nxt;
	      x:=x+ord(TypTab[pl^.typ].name[0]);
	      end 
	    else if pos=oparms then
	      begin
	      sfparmkd(plusaktpar,y0,sf,oparms-1,y,x);
	      pl:=erglist;
	      for i:=1 to oparms-2 do pl:=pl^.nxt;
	      x:=x+ord(TypTab[pl^.typ].name[0]);
	      end
	    else
	      begin
	      sfparmkd(plusaktpar,y0,sf,pos,y,x);
	      x:=x-1;
	      end;
	    end
	  else sfparmkd(plusaktpar,y0,sf,pos,y,x);
	  end;
	;
      until ende;
      end (*typex*) 
    else
      begin (*geforderter typ ex. nicht*)
      pos:=0;
      fp:=nil;
      end;
    end (*with*);
  end (*else*);
end (*waehleformPar*);


procedure contr (* y0,sf: integer; modus: char; var pos: integer *);
const plusaktpar=false;
var dummyptr: TypListe;
begin
waehleformPar(plusaktpar,y0,sf,modus,false,0,pos,dummyptr);
end;

procedure defmaske(* hl: HashListen; l: integer; var md: MaskenDaten *);
begin with md do
  begin
  rand:=5;
  xinput:=rand;
  ystern:=succ(rbs.ypixels)-7;
  case hl of
    prodHL: 
      begin
      azh:=rbs.zhoehe;
      yinput:=ystern-10*azh-2;
      if l=0 then zstern:=ystern-10*azh-8 else zstern:=ystern-12*azh-22;
      end;
    nontHL:
      begin
      if ASymb.hoehe>rbs.zhoehe then azh:=ASymb.hoehe else azh:=rbs.zhoehe;
      if l<=0 then zstern:= 6 else zstern:=l; 
      yinput:=ystern-(zstern+7)*azh-2;
      end;
    sfktHL:
      begin
      azh:=rbs.zhoehe;
      zstern:=0;
      yinput:=ystern-11*azh+1;
      end;
    attrHL:
      begin
      azh:=rbs.zhoehe;
      if l=0 then yinput:=ystern-8*azh-2 else yinput:=ystern-10*azh+1;
      end;
    termHL: 
      begin
      azh:=rbs.zhoehe;
      yinput:=ystern-8*azh+3;
      end;
    typeHL: wrtERR1('defmaske');
    end (*case*);
  end;
end; (*defmaske*)


procedure Pmaske(* neudef: boolean; var md: MaskenDaten; var pname: Ident *);
var x2,x3,y1,y2,y3,y4,dx,dy,y,x: integer;
begin
with md,rbs do
  begin
  y1:=ystern-3*azh-3;
  y2:=ystern-4*azh-6;
  y3:=ystern-9*azh-3;
  y4:=ystern-10*azh-6;
  x2:=xpixels-rand;
  x3:=rand+zbreite;
  linie(y1,rand,y1,x2);
  linie(y2,rand,y2,x2);
  linie(y3,rand,y3,x2);
  linie(y3,rand,y1,rand);
  linie(y3,x2,y1,x2);
  setCursor(y2+4,x3);
  if neudef then gpr_$text('DEFINITION',10,status) else gpr_$text('AENDERUNG',9,status);
  gpr_$text(' DER PRODUKTION ',16,status); wrtIdent(pname);
  if neudef then 
    begin
    setCursor(ystern-6*azh,rand+idlaenge*zbreite); gpr_$text('->',2,status);
    end
  else
    begin
    dx:=(xpixels -2*rand) div 3;
    dy:=azh+6;
    linie(ystern-12*azh-18,x2,ystern-10*azh-6,x2);
    linie(ystern-10*azh-6,rand,ystern-10*azh-6,xpixels-rand);
    linie(ystern-11*azh-12,rand,ystern-11*azh-12,xpixels-rand);
    linie(ystern-12*azh-18,rand,ystern-12*azh-18,xpixels-rand);
    linie(ystern-10*azh-6,rand,ystern-12*azh-18,rand);
    linie(ystern-10*azh-6,xpixels div 3,ystern-12*azh-18,xpixels div 3);
    linie(ystern-10*azh-6,2*xpixels div 3,ystern-12*azh-18,2*xpixels div 3);
    linie(ystern-10*azh-6,xpixels-rand,ystern-12*azh-18,xpixels-rand);
    y:=ystern-11*azh-7;
    x:=rand+zbreite;
    setCursor(y,x); gpr_$text('NONTERMINAL EINFUEGEN',21,status);
    setCursor(y,x+dx); gpr_$text('TERMINAL EINFUEGEN',18,status);
    setCursor(y,x+2*dx); gpr_$text('PRODUKTION UMBENENNEN',21,status);
    y:=y-dy;   
    setCursor(y,x); gpr_$text('VOK. DURCH NONTERM. ERS.',24,status);
    setCursor(y,x+dx); gpr_$text('VOK. DURCH TERMINAL ERS.',24,status);
    setCursor(y,x+2*dx); gpr_$text('VOKABEL STREICHEN',17,status);
    end
  end
end (*Pmaske*);


procedure SFmaske (* neudef: boolean; var SFmd: MaskenDaten; var sfname: Ident *);
begin
with SFmd, rbs do
  begin
  linie(ystern-3*azh-3,rand,ystern-3*azh-3,xpixels-rand);
  linie(ystern-4*azh-9,rand,ystern-4*azh-9,xpixels-rand);
  linie(ystern-9*azh-3,rand,ystern-9*azh-3,xpixels-rand);
  linie(ystern-9*azh-3,rand,ystern-3*azh-3,rand);
  linie(ystern-9*azh-3,xpixels-rand,ystern-3*azh-3,xpixels-rand);
  setCursor(ystern-4*azh-5,rand+zbreite);
  if neudef then gpr_$text('NEUDEFINITION',13,status) else gpr_$text('AENDERN',7,status);
  gpr_$text(' der Funktion ',14,status); wrtIdent(sfname);
  end;
end (*SFmaske*);


procedure Amaske(* neudef: boolean; var md: MaskenDaten; var aname: Ident *);
var y1,y2,y3,y4: integer;
begin
with md,rbs do
  begin
  y1:=ystern-3*azh-3;
  y2:=ystern-4*azh-6;
  if neudef then
    begin
    y3:=ystern-7*azh-3;
    y4:=ystern-8*azh-6;
    end
  else
    begin
    y3:=ystern-8*azh-9;
    y4:=ystern-10*azh-3;
    end;
  linie(y1,rand,y1,xpixels-rand);
  linie(y2,rand,y2,xpixels-rand);
  linie(y3,rand,y3,xpixels-rand);
  linie(y3,rand,y1,rand);
  linie(y3,xpixels-rand,y1,xpixels-rand);
  if neudef then
    begin
    setCursor(y2+4,rand+zbreite);
    gpr_$text('DEFINTION DES ATTRIBUTES ',25,status); wrtIdent(aname);
    setCursor(ystern-6*azh+1,rand+zbreite);
    gpr_$text('Richtung:',9,status);
    setCursor(ystern-7*azh+1,rand+zbreite);
    gpr_$text('Typ:',4,status);
    end
  else begin
    setCursor(y2+4,rand+zbreite);
    gpr_$Text('AENDERN DES ATTRIBUTES ',23,status); wrtIdent(aname);
    setCursor(ystern-6*azh-4,rand+zbreite);
    gpr_$text('Symbol:',7,status);
    setCursor(ystern-7*azh-4,rand+zbreite);
    gpr_$text('Richtung:',9,status);
    setCursor(ystern-8*azh-4,rand+zbreite);
    gpr_$text('Typ:',4,status);
    end
  end
end (*Amaske*);


procedure Tmaske(* neudef: boolean; var md: MaskenDaten; var tname: Ident *);
var y1,y2,y3,y4,x2,x3: integer;
begin
with md,rbs do
  begin
  y1:=ystern-3*azh-3;
  y2:=ystern-4*azh-6;
  y3:=ystern-6*azh-3;
  y4:=yinput-3;
  x2:=xpixels-rand;
  x3:=rand+zbreite;
  linie(y1,rand,y1,x2);
  linie(y2,rand,y2,x2);
  linie(y3,rand,y3,x2);
  linie(y3,rand,y1,rand);
  linie(y3,x2,y1,x2);
  setCursor(y2+4,x3);
  if neudef then gpr_$text('DEFINITION',10,status) else gpr_$text('AENDERN',7,status);
  gpr_$text(' DES TERMINALS ',15,status); wrtIdent(tname);
  setCursor(ystern-6*azh+2,x3); gpr_$text('Kurzdarstellung: ',17,status);
 end
end (*Tmaske*);


procedure wrthalbattribg(* nt: integer; loeschen: boolean; aart: Richtung; var maskenD: MaskenDaten *);
var l: AListe;
    x1,x2,ystart: integer;
begin
with evibsD, maskenD, rbs do
  begin
  if aart=inh then 
    begin
    x1:=rand+1; x2:=xpixels div 2 -1;
    l:=NTTab[nt].inhAttr;
    end
  else
    begin
    x1:=xpixels div 2 +1; x2:=xpixels-rand-1;
    l:=NTTab[nt].derAttr;
    end;
  if loeschen then male4eck(true,ystern-(zstern+6)*azh,ystern-6*azh,x1,x2);
  ystart:=ystern-7*azh;
  while l<>nil do
    begin
    with l^ do
      begin
      setCursor(ystart,x1+4*zbreite); wrtIdent(ATab[attr].name); 
      if ATab[attr].typ>0 then
	begin
        gpr_$text(':',1,status);
        writeikon(ystart,x1+2*zbreite,ATab[attr].symbol);
        setCursor(ystart,x1+(idlaenge+6)*zbreite); wrtIdent(TypTab[ATab[attr].typ].name);
	end;
      ystart:=ystart-azh;
      end;
    l:=l^.nxt;
    end;
  end;
end (*wrthalbattribtg*);

procedure NTmaske(*neudef: boolean; var NTmd: MaskenDaten; var ntname: Ident*);
var dx,dy,x,y,i:integer;
begin
with evibsD, NTmd, rbs do begin
  linie(ystern-(zstern+6)*azh-3,xpixels div 2, ystern-4*azh-6,xpixels div 2);
  linie(ystern-(zstern+6)*azh-3,rand,ystern-3*azh-3,rand);
  linie(ystern-(zstern+6)*azh-3,xpixels-rand,ystern-3*azh-3,xpixels-rand);
  linie(ystern-3*azh-3,rand,ystern-3*azh-3,xpixels-rand);
  linie(ystern-4*azh-6,rand,ystern-4*azh-6,xpixels-rand);
  linie(ystern-5*azh-9,rand,ystern-5*azh-9,xpixels-rand);
  linie(ystern-(zstern+6)*azh-3,rand,ystern-(zstern+6)*azh-3,xpixels-rand);
  setCursor(ystern-4*azh-2,rand+20);
  if neudef then gpr_$text(' DEFINITION',11,status) else gpr_$text (' AENDERUNG',10,status);
  gpr_$text(' DER GLOBALEN ATTRIBUTIERUNG von Nonterminal ',45,status); wrtIdent(ntname);
  setCursor(ystern-5*azh-5,10*zbreite); gpr_$text('Inherited Attribute:',20,status);
  setCursor(ystern-5*azh-5,xpixels div 2 + 10*zbreite); gpr_$text('Derived Attribute:',18,status);
end (* with *)
end (*NTmaske*);

procedure NTmaske1(* NM1:MaskenDaten *);
var y:integer;
begin
  with NM1,rbs do begin
    y:=ystern-(zstern+7)*azh-6;   
    linie(y,rand,y,xpixels-rand);
    linie(y-azh-6,rand,y-azh-6,xpixels-rand);
    linie(y,rand,y-azh-6,rand);
    linie(y,xpixels div 3,y-azh-6,xpixels div 3); 
    linie(y,2*xpixels div 3,y-azh-6,2*xpixels div 3);
    linie(y,xpixels-rand,y-azh-6,xpixels-rand);
    setCursor(y-azh+1,rand+zbreite);
    gpr_$text('ATTRIBUT ERGAENZEN',18,status);
    setCursor(y-azh+1,xpixels div 3 + zbreite);
    gpr_$text('ATTRIBUT STREICHEN',18,status);
    setCursor(y-azh+1,2*xpixels div 3 + zbreite); 
    gpr_$text('ATTRIBUT-REIHUNG AENDERN',24,status);
  end
end;

procedure liesDateiname (* var default,Dateiname: filename *);
var y,x,laenge,a,b: integer;
    ende:       boolean;
    c:          char;

begin
CursorPos(y,x);
gpr_$text(' ',1,status);
setCursor(y,x+rbs.zbreite);
Dateiname:= '  ';
ende:= false; laenge:= 0;
repeat    
 {gpr_$set_cursor_active(true,status);}
  cursoron;
  cread(c);                          
 {gpr_$set_cursor_active(false,status);}
  cursoroff;
  if c=chr(13) 
  then begin
       ende:= true;
       if (laenge = 0)
       then begin Dateiname:= default; gpr_$text( Dateiname ,60,status) end
       else default:= Dateiname; 
       cursorPos(a,b); SetCursor(a+rbs.zhoehe,0);
       end
  else begin
       if (' ' < c) then
         begin
         if (ord(c) = 127)
	 then begin
              if (laenge > 0)
              then begin
                   Dateiname[ laenge ]:= ' '; laenge:= laenge-1;
	 	   backspace( y, x, laenge+1 );
		   end
	      end
         else if (laenge < 70)
	      then begin
	 	   laenge:= laenge+1;
           cursorPos(a,b);
           gpr_$text(c,1,status);
		   Dateiname[laenge]:= c;
           setcursor(a,b+rbs.zbreite);
		   end
         end
       end
until ende
end;   {liesDateiname}


function recover (*: boolean *);
var CAG,CS,SDateiname: filename;
    c: char;
begin    
gibSymbolDateiname(AGtmp,SDateiname);
gibCDateiname(AGtmp,CAG);
gibCDateiname(SDateiname,CS);
if (exFILE(CAG)=0) and (exFILE(CS)=0) then
  begin
  if (wrtFILE(CAG)=0) and (wrtFILE(CS)=0) then
    begin
    clearscreen; 
    setCursor(rbs.ypixels-2*rbs.zhoehe,0);
    gpr_$text(' Es wurden die Dateien AG.tmp.$$$ und AG.tmp.symbole.$$$ gefunden.',66,status);
    newline;
    gpr_$text(' Soll auf sie wieder aufgesetzt werden [j/n]? ',46,status);
    keys := ['j','n']; {Create a key set.}
    gpr_$enable_input(gpr_$keystroke, keys, status);
    keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
    gpr_$enable_input(gpr_$buttons, keys, status); 
    unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
    recover:= c='j';
    end
  else
    begin
    meldefehler(54);
    zurueck;
    irrEnde;
    end
  end
else
  begin
  if (exFILE(CAG)=0) or (exFILE(CS)=0) then
    begin
    meldefehler(53);
    zurueck;
    irrEnde;
    end
  else recover:=false;
  end
end (*recover*);


procedure initfehlerspur;
var fn, Cfn: filename;
begin 
fn:='fehlerspur';
gibCDateiname(fn,Cfn);
if schreibenerlaubt(Cfn)
 then begin
        open(ERRFILE,fn) ;
        rewrite(ERRFILE)
      end
else 
  begin
  meldefehler(58);
  irrEnde;
  end;
end (*initfehlerspur*);
