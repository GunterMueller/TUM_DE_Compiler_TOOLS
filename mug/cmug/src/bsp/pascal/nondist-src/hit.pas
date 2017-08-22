




procedure info;
const letztkap = 3;
var c: char;
    kap: integer;
    sw: boolean;

procedure more;
begin 
newline;
gpr_$text('Mit beliebiger Taste gehts weiter !',36,status); {##''}
cread(c);
(*
gpr_$text('MORE: "0" bricht ab, RETURN faehrt fort, "1".."',47,status);
writeint(letztkap);
gpr_$text('" Punkte (1) bis (',18,status);
writeint(letztkap);
gpr_$text(')',1,status);
repeat cread(c) until ord(c) in [ord('0')..(ord('0')+letztkap),13];
if c='0' then       
else if c=chr(13) then 
  begin 
  if kap=letztkap then c:='0' else kap:=succ(kap);
  end
else kap:=ord(c)-ord('0');
*)
clearscreen; setCursor(rbs.yhome,0);
end (*more*);


procedure kurzinfo;
begin
newline;
newline;
newline;
gpr_$text('INFO:',5,status); newline;
gpr_$text('=====',5,status); newline;
newline;
newline;
gpr_$text('Die gesamte Menuesteuerung ist fast ausschliesslich mit der Maus durchfuehrbar.',79,status);newline;
newline;
gpr_$text('Die Maustasten haben dabei folgende Bedeutungen:',48,status);newline;
gpr_$text('------------------------------------------------',48,status);newline;
newline;
gpr_$text('Auswahl von Untermenues: linke Maustaste    = Menue verlassen (nur bedingt moeglich)',84,status);newline;
gpr_$text('                         mittlere Maustaste = Untermenue aufrufen',65,status);newline;
gpr_$text('                         rechte Maustaste   = Ausgabe dieser Infoseite',70,status);newline;
gpr_$text('                         Mausbewegung       = Auswahl eines Untermenues',71,status);newline;
newline;
gpr_$text('Anklicken von Objekten : linke Maustaste    = Anklicken abbrechen',65,status);newline;
gpr_$text('                         mittlere Maustaste = Objekt anklicken und damit auswaehlen',83,status);newline;
gpr_$text('                         rechte Maustaste   = letzte Meldung wiederholen',72,status);newline;
gpr_$text('                         Mausbewegung       = Anfahren von Objekten mit dem Mauszeiger',86,status);newline;
newline;
gpr_$text('Eingabe von Objektnamen: linke Maustaste    = keine Bedeutung',61,status);newline;
gpr_$text('                         mittlere Maustaste = Eingabe uebernehmen',65,status);newline;
gpr_$text('                         rechte Maustaste   = Listenauswahl eines Namens',72,status);newline;
gpr_$text('                         Mausbewegung       = keine Bedeutung',61,status);newline;
newline;
newline;
gpr_$text('Diese Tastenbelegungen sind immer gueltig, sofern fuer spezielle Funktionen keine',81,status);newline;
gpr_$text('anderen Belegungen vereinbart werden.',37,status);newline;
newline;
newline
end;


(*
procedure info0;
begin
newline;
newline;
newline;
gpr_$text('INFO:',5,status); newline;
gpr_$text('=====',5,status); newline;
newline;
gpr_$text('HINWEIS: Diese Information erlaeutert lediglich die verschiedenen Eingabemoeg-',78,status); newline;
gpr_$text('-------- lichkeiten des Benutzers.',34,status); newline; 
gpr_$text('         Ansonsten ziehe man bitte die Dokumentation zu Rate.',61,status); newline;
newline;
gpr_$text('         Dieses Info kann auch aus den meisten Menues durch Eingabe von "?"',75,status); newline;
gpr_$text('         aufgerufen werden, ohne dass auf diese Eingabemoeglichkeit explizit',76,status); newline;
gpr_$text('         hingewiesen wird.',26,status); newline;
newline;
newline;
gpr_$text('ALLGEMEINES: IGEM besitzt zwei verschiedene Eingabemodi:',56,status); newline;
gpr_$text('-----------  1.)  Kommandomodus',31,status); newline;
gpr_$text('                  Zur Selektion muessen die Cursortasten benutzt werden.',72,status); newline;
gpr_$text('                  Die Auswahl erfolgt dann durch das selbstgewaehlte Prompt-',76,status); newline;
gpr_$text('                  Zeichen, Abbruch mit der Taste "0".',53,status); newline;
gpr_$text('             2.)  Selektionsmodus',33,status); newline;
gpr_$text('                  Zur Selektion wird das Fadenkreuz (Maus) benutzt.',67,status); newline;
gpr_$text('                  Die Auswahl erfolgt mit der mittleren, Abbruch mit der linken',79,status); newline;
gpr_$text('                  Maustaste. Auswahl bzw. Abbruch ist auch wie im Kommandomo-',77,status); newline;  
gpr_$text('                  dus moeglich.',31,status); newline;
newline;
gpr_$text('Folgende Eingabemoeglichkeiten werden hier beschrieben:',55,status); newline;
gpr_$text('-------------------------------------------------------',55,status); newline;
newline;
gpr_$text('         (1) Eingabe von Namen,',31,status); newline;
gpr_$text('         (2) Cursorsteuerung,',29,status); newline;
gpr_$text('         (3) Eingabe von "0",',29,status); newline;
{gpr_$text('         (4) Eingabe mittels Fadenkreuzes',41,status); newline;}
newline;
newline;
more;
end;

procedure info1;
var c1: char;
begin
gpr_$text('zu (1): EINGABE VON NAMEN',25,status); newline;
gpr_$text('        -----------------',25,status); newline;
newline;
gpr_$text('Wann immer ein Name vom Benutzer durch das Programm erfragt wird, so kann',73,status); newline;
gpr_$text('dieser zwischen vier Eingabemoeglichkeiten auswaehlen:',54,status); newline;
newline;
gpr_$text('a) Eingabe eines Identifikators (gemaess PASCAL-Syntax)',56,status); newline;
gpr_$text('b) Eingabe von Sonderzeichen',28,status); newline;
gpr_$text('   (a) fuer die sog. "Listenauswahl" (Voreinstellung: "-", "?", "+") und',72,status); newline;
gpr_$text('   (b) zur Bezeichnung der Identitaet einer Funktion (Voreinstellung "="',72,status); newline;
gpr_$text('c) Eingabe eines Praefixes eines PASCAL-Identifikators unmittelbar gefolgt von',78,status); newline;
gpr_$text('   einem der ersten drei der obigen Sonderzeichen,',50,status); newline;
gpr_$text('d) Leere Eingabe.',17,status); newline;
newline;
newline;
gpr_$text('Diese vier unterschiedlichen Eingaben haben folgende Bedeutung:',64,status); newline;
newline;
gpr_$text('zu a): Die Angabe eines Identifikators bezeichnet das gefragte Element wie man',78,status); newline;
gpr_$text('       es erwartet.',19,status); newline;
gpr_$text('zu b): (a) An allen Stellen, an welchen der Benutzer nach einem Namen eines',75,status); newline;
gpr_$text('       Elementes der Grammatik gefragt wird, besteht fuer ihn die Moeglichkeit',78,status); newline;
gpr_$text('       dieses Element aus einer auf dem Bildschirm dargestellt werdenden Liste',78,status); newline;
gpr_$text('       aller infragekommenden Elemente auszuwaehlen. Innerhalb dieser Liste',75,status); newline;
gpr_$text('       findet sich - wenn vom Kontext zulaessig - auch ein Punkt wieder, der',76,status); newline;
gpr_$text('       die Neudefinition eines Elements ermoeglicht. Wuenscht der Benutzer',74,status); newline;
gpr_$text('       diese Auswahlmoeglichkeit, so sollte er eines der drei Sonderzeichen',75,status); newline;
gpr_$text('       eingeben, je nachdem, ob er eine knappe, normale oder ausfuehrliche',74,status); newline;
gpr_$text('       Darstellung der Listen wuenscht. Die Belegung dieser Sonderzeichen ist',77,status); newline;
gpr_$text('       im Menue "Steuerzeichen" veraenderbar.',45,status); newline;
gpr_$text('       (b) Das Sonderzeichen "=" bezeichnet eine Identitaet einer',66,status); newline;
gpr_$text('       Funktion. Es kann an allen Programmstellen eingegeben werden, an',71,status); newline;
gpr_$text('       welchen nach dem Namen einer Funktion in ihrem angewandten ',67,status); newline;
gpr_$text('       Auftreten gefragt ist.',29,status); newline; 
newline;
if rbs.ypixels <> 1023
 then begin
       gpr_$text('Weiter geht''s mit RETURN...',27,status); repeat cread(c1) until c1=chr(13);
       clearscreen;                        
       setCursor(rbs.yhome,0);
      end;
gpr_$text('c) Eingabe eines Praefixes eines PASCAL-Identifikators unmittelbar gefolgt von',78,status); newline;
gpr_$text('   einem der drei obigen Sonderzeichen "-", "?", "+",',53,status); newline;
gpr_$text('d) Leere Eingabe.',17,status); newline;
newline;
newline;
gpr_$text('zu c): Diese Eingabe entspricht im wesentlichen der unter b) beschriebenen.',75,status); newline;
gpr_$text('       Die Angabe eines Praefixes positioniert den auf dem Bildschirm darge-',76,status); newline;
gpr_$text('       stellten Ausschnitt der Liste so, dass ein durch das Praefix bezeich-',76,status); newline;
gpr_$text('       nete Identifikator moeglichst in der Mitte des Ausschnitts sichtbar',74,status); newline;    
gpr_$text('       wird.',11,status); newline;
gpr_$text('zu d): Die leere Eingabe bewirkt den Abbruch der laufenden Aktion.',67,status); newline;
gpr_$text('       (Ist dies ausnahmsweise nicht zugelassen, so erfolgt ein expliziter',74,status); newline;
gpr_$text('       Hinweis auf diesen Umstand.)',35,status); newline;
more;
end; 


procedure info2;
begin
newline; 
newline;
newline;
gpr_$text('zu (2): CURSORSTEUERUNG',23,status); newline;
gpr_$text('        ---------------',23,status); newline;
newline;
gpr_$text('An einigen Programmstellen wird der Benutzer mittels des Hinweises "[CURSOR]"',77,status); newline;
gpr_$text('auf die Moeglichkeit der sog. Cursorsteuerung hingewiesen.',58,status); newline;
newline;
gpr_$text('*** WICHTIG!                                                               ***',78,status); newline;
gpr_$text('*** Diese Cursorsteuerung wird ferner -OHNE BESONDEREN HINWEIS- erwartet,  ***',78,status); newline;
gpr_$text('*** wenn der Benutzer aus Menues auswaehlen soll, deren einzelne Punkte    ***',78,status); newline;
gpr_$text('*** nicht durch Selektoren bezeichnet sind.                                ***',78,status); newline;
newline;
gpr_$text('Der Cursor wird dabei mittels der Tasten "2", "4", "6" und "8" (!) in der',73,status); newline;
gpr_$text('durch das Tastenfeld der Pfeiltasten nahegelegten Richtung bewegt.',66,status); newline;
gpr_$text('Der Cursor kann auch mit den Maustasten bewegt werden :',55,status);newline;
gpr_$text('Linke Taste: links (bzw. oben), rechte Taste rechts (bzw. unten)',64,status); newline;
newline;
gpr_$text('Die Eingabe von "0" (null) bricht die laufende Aktion bzw. Auswahl ab; dies-',76,status); newline;
gpr_$text('bezuegliche Ausnahmen werden explizit angezeigt; s.a. Punkt (3).',64,status); newline;
newline;
gpr_$text('Die Eingabe von "SELECT" (Voreinstellung fuer SELECT ist die Taste <Return>; sie kann',85,status); newline;
gpr_$text('im Menue "Steuerzeichen" geaendert werden) uebernimmt die Cursorposition bzw.',77,status); newline;
gpr_$text('kennzeichnet den durch die augenblickliche Cursorposition ausgezeichneten',73,status); newline;
gpr_$text('Eintrag als vom Benutzer selektiert.',36,status); newline;
gpr_$text('Die Selektion kann zusaetzlich durch die mittlere Maustaste erfolgen.',69,status);newline;
more;
end; 

procedure info3;
begin
newline;
newline;
newline;
gpr_$text('zu (3): EINGABE VON "0" (NULL)',30,status); newline;
gpr_$text('        ----------------------',30,status); newline;
newline;
gpr_$text('Die Kenntnis dieser Eingabemoeglichkeit ist vor allem von Bedeutung, um sich',76,status); newline;
gpr_$text('aus scheinbaren Endlosschleifen zu retten, sowie um (moeglicherweise faelsch-',77,status); newline;
gpr_$text('licherweise) begonnene Aktionen zu unterbrechen und das Begonnene rueckgaengig',78,status); newline;
gpr_$text('zu machen.',10,status); newline;
newline;
gpr_$text('Grundsaetzlich gilt waehrend des gesamten Programmlaufs, dass der Benutzer',74,status); newline;
gpr_$text('- sofern er nach einem Namen gefragt wird- auch den leeren Namen eingeben darf,',79,status); newline;
gpr_$text('in den uebrigen Faellen ist die Eingabe von "0" moeglich. Sie hat eine',70,status); newline;
gpr_$text('aehnliche Funktion wie die leere Eingabe.',41,status); newline;
newline;
gpr_$text('Beide Eingaben bewirken den Abbruch der laufenden Aktion und machen begonnene',77,status); newline;
gpr_$text('Aenderungen an der Datenstruktur wieder rueckgaengig. Oft wird dabei zugleich',77,status); newline;
gpr_$text('ein Untermenue beendet und ins aufrufende Menue zurueckgesprungen.',66,status); newline;
gpr_$text('Insbesondere in den Faellen der "Menueauswahl" fuehrt die Eingabe von "0" in',76,status); newline;
gpr_$text('das aufrufende Menue zurueck.',29,status); newline;
gpr_$text('Ist die Eingabe des leeren Namens bzw. die Eingabe von "0" ausnahmsweise nicht',78,status); newline;
gpr_$text('zulaessig, so wird ein entsprechender Hinweis gemeldet.',55,status); newline;
more;
end; 


procedure info4;
begin
gpr_$text('zu (4): MAUSZEIGER',18,status); newline;
gpr_$text('        ----------',18,status); newline;
newline;
gpr_$text('Auf die Eingabe mittels Mauszeigers wird in jedem Einzelfall explizit hinge-',76,status); newline;
gpr_$text('wiesen. Bewegt wird der Mauszeiger mit der Maus.',48,status); newline;
newline;
gpr_$text('Das Programm beendet das Fadenkreuz (und uebernimmt die dadurch festgelegte',75,status); newline;
gpr_$text('Position, sobald irgendeine "gewoehnliche" Taste gedrueckt wird.',64,status); newline;
gpr_$text('Es gibt jedoch insbesondere zwei Tasten, die man fuer das regulaere Abbrechen',77,status); newline; 
gpr_$text('des Fadenkreuzes NICHT verwenden sollte:',40,status); newline;
gpr_$text('1. Am GSG15-Terminal sollte nicht RETURN verwendet werden, da in diesem Fall',76,status); newline;
gpr_$text('   durch die Hardware bedingt sechs weitere Eingabezeichen erwartet werden.',75,status); newline;
gpr_$text('   Der Rechner scheint in dieser Situation zu "haengen". Das Programm kann',74,status); newline;
gpr_$text('   jedoch nach der Eingabe von sechs beliebigen Zeichen fortgesetzt werden.',75,status); newline;
gpr_$text('2. Die Eingabe von "0" bewirkt das wirkungslose Abbrechen des Fadenkreuzes und',78,status); newline;
gpr_$text('   Rueckkehr in den aufrufenden Programmteil. Siehe auch Punkt (3)!',67,status); newline;
more;
end;
*)
 

begin (*info*)
sw:=aktSeite=0;
Seite1;
clearscreen;
setCursor(rbs.yhome,0);
kap:=0;
kurzinfo;
more;
(*
if c<>'0' then
  begin
  repeat
  case kap of
    1: info1;
    2: info2;
    3: info3;
    {4: info4; }
    end ;
  until c='0';
  end;
*)
if sw then Seite0;
end (*info*);
