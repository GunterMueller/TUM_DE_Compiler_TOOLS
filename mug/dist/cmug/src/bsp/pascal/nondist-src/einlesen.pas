







procedure Grammatikeinlesen (* eingabedatei: filename *);
var i,j,akt:         integer;
    c:               char;
    GIN:             text;
    neu,fehler     : boolean;
    direction      : gpr_$direction_t;

procedure Zahleinlesen (var n: integer);
var minus: boolean;
begin
read( GIN, c ); 
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = '-')
then begin minus:= true; read( GIN, c ) end
else minus:= false;
if ('0' <= c) and (c <= '9')
then begin
     n:= ord(c)-ord('0'); read( GIN, c );
     while ('0' <= c) and (c <= '9') do
        begin n:= n*10 + (ord(c)-ord('0')); read( GIN, c ) end;
     if minus then n:= -n
     end
else begin
     n:= ERR ;
     fehler := true
     end
end;  (*Zahleinlesen*)

procedure Realeinlesen (var r: real);
var i: integer;
begin
Zahleinlesen(i);
r:= i/10000
end;   {Realeinlesen}

procedure Identeinlesen (var Id: Ident);
var i:integer;
begin
read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
i:= 0;
if ('@' <= c)
then while (('0' <= c) and (c <= '9')) or
           (('@' <= c) and (c <= 'Z')) or
           (('a' <= c) and (c <= 'z')) do
	   begin
	   if (i < idlaenge) then begin i:= i+1; Id[i]:= c end;
	   read( GIN, c ); 
if ord(c)=32 then read(GIN,c) (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
	   end;
Id[0]:= chr(i)
end;  (*Identeinlesen*)

procedure boollesen (var b: boolean);
begin
read( GIN, c );  
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = 't')
then b:= true
else b:= false;
repeat read( GIN, c ) until (c = ',')
end;  (*boollesen*)

procedure PListeeinlesen (var h: PListe);
var h1,h2: PListe;
begin
read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = '$')
then h:= nil
else begin
     new(h); Zahleinlesen(h^.prod); h1:= h;
     while (c <> ']') do
        begin
        new(h2); Zahleinlesen(h2^.prod); h1^.nxt:= h2; h1:= h1^.nxt
        end;
     h1^.nxt:= nil
     end
end;  (*PListeeinlesen*)

procedure AListeeinlesen (var h: AListe);
var h1,h2: AListe;
begin
read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = '$')
then h:= nil
else begin
     new(h); Zahleinlesen(h^.attr); h1:= h;
     while (c <> ']') do
        begin
        new(h2); Zahleinlesen(h2^.attr); h1^.nxt:= h2; h1:= h1^.nxt
        end;
     h1^.nxt:= nil
     end
end;  (*AListeeinlesen*)

procedure HAListeeinlesen (var h: HAListe);
var h1,h2: HAListe;
begin
read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = '$')
then h:= nil
else begin
     new(h); Realeinlesen(h^.vx); Realeinlesen(h^.vy); Zahleinlesen(h^.attr);
     h1:= h;
     while (c <> ']') do
        begin
        new(h2); Realeinlesen(h2^.vx); Realeinlesen(h2^.vy);
        Zahleinlesen(h2^.attr); h1^.nxt:= h2; h1:= h1^.nxt
        end;
     h1^.nxt:= nil
     end
end;  (*HAListeeinlesen*)

procedure TypListeeinlesen (var h: TypListe);
var h1,h2: TypListe;
begin
read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)
if (c = '$')
then h:= nil
else begin
     new(h); Zahleinlesen(h^.typ); h1:= h;
     while (c <> ']') do
        begin
        new(h2); Zahleinlesen(h2^.typ); h1^.nxt:=h2; h1:=h1^.nxt
        end;
     h1^.nxt:= nil
     end
end;  (*TypListeeinlesen*)

procedure PunktListeeinlesen (var punkte: PunktListe);
var hpunkte: PunktListe;
begin
if (c = '[')
then begin
     new(punkte); hpunkte:= punkte;
     Realeinlesen( punkte^.vx ); Realeinlesen( punkte^.vy );
     while( c <> ']') do
       begin
       new( hpunkte^.nxt ); hpunkte:= hpunkte^.nxt;
       Realeinlesen( hpunkte^.vx ); Realeinlesen( hpunkte^.vy );
       end;
     hpunkte^.nxt := nil;
     read( GIN, c );
if ord(c)=32 then read(GIN,c) (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)  
   end
else punkte:= nil
end;   {PunktListeeinlesen}

procedure Termeinlesen (n: integer);
begin
if (1 <= n) and (n <= maxanzT)
then with TTab[n] do
     begin
     Identeinlesen( name );
     read( GIN, sz1, sz2, c );
     Zahleinlesen( typ );
     PListeeinlesen( anwendungen ); read( GIN, c );  { ',' }
     Zahleinlesen( scannerklasse );
     Zahleinlesen( nxt )
     end
else begin
     while (c <> ')') do begin read( GIN, c ); if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *) end;
     gpr_$text('Ungueltiger Terminalindex: ',26,status);
     writeint(n);
     newline;
     end
end;  (*Termeinlesen*)

procedure Nontermeinlesen (n: integer);
begin
if (1 <= n) and (n <= maxanzNT)
then with NTTab[n] do
     begin
     Identeinlesen( name );
     AListeeinlesen( inhAttr ); read( GIN, c );if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)   { ',' }
     AListeeinlesen( derAttr ); read( GIN, c );if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)   { ',' }
     PListeeinlesen( anwendungen ); read( GIN, c );if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)   { ',' }
     Zahleinlesen( scannerklasse );
     Zahleinlesen( nxt )
     end
else begin
     while (c <> ')') do read( GIN, c );
     gpr_$text('Ungueltiger Nonterminalindex: ',29,status);
     writeint(n);
     newline;
     end
end;  (*Nontermeinlesen*)

procedure Vokabeleinlesen (var h: VokListe);
begin
read( GIN, c ); new(h);  { T oder N }
if (c = 'T')
then begin
     h^.typ:= term; read( GIN, c );if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)   { ',' }
     Zahleinlesen( h^.t )
     end
else begin
     h^.typ:= nont; read( GIN, c );if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf) *)   { ',' }
     Zahleinlesen( h^.nt);
     AListeeinlesen( h^.spezInhA ); read( GIN, c );   { ',' }
     AListeeinlesen( h^.spezDerA ); read( GIN, c );   { ',' }
     h^.unversA := nil;
     boollesen( h^.konsistent )
     end;
Realeinlesen( h^.dx );
Realeinlesen( h^.dy )
end;  (*Vokabeleinlesen*)

procedure Prodeinlesen (n: integer);
var i:   integer;
    hv:  VokListe;
    hsf: SemFktListe;

  procedure sFunktioneinlesen (var sf: SemFktListe);

    procedure ParListeeinlesen (var pl: ParListe);
    var hpl: ParListe;

      function Vokzeiger (k: integer): VokListe;
      var j:  integer;
          hv: VokListe;
      begin
      if (k = 1)
      then Vokzeiger:= PTab[n].vater
      else begin
           hv:= PTab[n].soehne; j:= 2;
           while (j < k) and (hv <> nil) do
              begin hv:= hv^.nxt; j:= j+1 end;
           if (j < k)
           then Vokzeiger:= nil
           else Vokzeiger:= hv
           end
      end;  (*Vokzeiger*)

    begin
    read( GIN, c );
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
    if (c = '$')
    then pl:= nil
    else begin
         new(pl);
         Zahleinlesen(i);
         if (i <= 0)
         then pl^.vok:= nil
         else pl^.vok:= Vokzeiger(i);
         Zahleinlesen(i);
         if (i <= 0) or (maxanzA < i)
         then pl^.attr:= 0
         else pl^.attr:= i;
	 PunktListeeinlesen( pl^.verb );
         hpl:= pl;
         while (c <> ']') do
            begin
            new( hpl^.nxt ); hpl:= hpl^.nxt;
            Zahleinlesen(i);
            if (i <= 0)
            then hpl^.vok:= nil
            else hpl^.vok:= Vokzeiger(i);
            Zahleinlesen(i);
            if (i <= 0) or (maxanzA < i)
            then hpl^.attr:= 0
            else hpl^.attr:= i;
	    PunktListeeinlesen( hpl^.verb )
            end;
         hpl^.nxt := nil
         end
    end;  (*ParListeeinlesen*)

  begin
  new(sf);
  Zahleinlesen( sf^.semfkt );
  ParListeeinlesen( sf^.quellpar ); read( GIN, c );  { ',' }
  ParListeeinlesen( sf^.zielpar );  read( GIN, c );  { ',' }
  boollesen( sf^.versorgt );
  if neu then boollesen( sf^.gedreht) else sf^.gedreht:=false;
  Realeinlesen( sf^.vx );
  Realeinlesen( sf^.vy )
  end;  (*sFunktioneinlesen*)

begin
if (1 <= n) and (n <= maxanzP)
then with PTab[n] do
     begin
     Identeinlesen( name ); read( GIN, c );   { '(' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     if (c <> ',')
     then begin Vokabeleinlesen( vater ); readln( GIN, c ) { , } end
     else begin vater:= nil; readln( GIN ) end;
     read( GIN, c );   { '$ oder [' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     if (c = '$')
     then soehne:= nil
     else begin
	  read( GIN, c );   { '(' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
          Vokabeleinlesen( soehne ); hv:= soehne; read( GIN, c );   { ',' }
          while (c <> ']') do
             begin
             read( GIN, c );   { '(' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
             Vokabeleinlesen( hv^.nxt );  hv:= hv^.nxt;
             read( GIN, c );  { ', oder ]' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
             end;
          hv^.nxt:= nil
          end;
     if vater <> nil then vater^.nxt:= soehne;
     read( GIN, c );   { ',' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     HAListeeinlesen( hilfsAttr ); readln( GIN, c );    { ',' }
     read( GIN, c );   { '$ oder [' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     if (c = '$')
     then semRegeln:= nil
     else begin
	  read( GIN, c );   { '(' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
          sFunktioneinlesen( semRegeln ); hsf:= semRegeln; read( GIN, c ); {,}
          while (c <> ']') do
             begin
             readln( GIN ); read( GIN, c ); { ( }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
             sFunktioneinlesen( hsf^.nxt ); hsf:= hsf^.nxt;
             read( GIN, c );  { ', oder ]' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
             end;
          hsf^.nxt:= nil
          end;
     read( GIN, c );   { ',' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     boollesen( konsistent );
     Zahleinlesen( nxt )
     end  {with und then}
else begin i:= 1;
     while (i <> 0) do
        begin read( GIN, c );
        if (c = '(') then i:= i+1
                     else if (c = ')') then i:= i-1
        end;
     gpr_$text('Ungueltiger Index fuer Produktion: ',35,status);
     writeint(n);
     newline
     end
end;  (*Prodeinlesen*)

procedure SemFkteinlesen (n: integer);
begin
if (1 <= n) and (n <= maxanzSF)
then with SFTab[n] do
     begin
     Identeinlesen( name ); 
     if neu then boollesen( issynfkt ) else issynfkt:=false;
     TypListeeinlesen( parlist ); read( GIN, c );  { ',' } 
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     TypListeeinlesen( erglist ); read( GIN, c );  { ',' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     PListeeinlesen( anwendungen ); read( GIN, c );   { ',' }
if ord(c)=32 then read(GIN,c); (* APOLLO liefert nach 256. Zeichen ein blank (oder lf)J.20.11 *)
     Zahleinlesen( nxt )
     end
else begin
     while (c <> ')') do read( GIN, c );
     gpr_$text('Ungueltiger Index fuer SemFunktion: ',36,status);
     writeint(n);
     newline
     end
end;  (*SemFkteinlesen*)

procedure Attreinlesen (n: integer);
begin
if (1 <= n) and (n <= maxanzA)
then with ATab[n] do
     begin
     Identeinlesen( name );
     Zahleinlesen( typ );
     Zahleinlesen( symbol ); read( GIN, c );
     if (c = 'i')
     then art:= inh
     else if (c = 'd')
          then art:= der
          else art:= aux;
     repeat read( GIN, c ) until (c = ',');
     Zahleinlesen( nxt )
     end
else begin
     while (c <> ')') do read( GIN, c );
     gpr_$text('Ungueltiger Attributindex: ',28,status);
     writeint(n);
     newline
     end
end;  (*Attreinlesen*)

procedure Typnameeinlesen (n: integer);
begin
if (1 <= n) and (n <= maxanzTyp)
then with TypTab[n] do
     begin
     Identeinlesen( name );
     Zahleinlesen( nxt )
     end
else begin
     while (c <> ')') do read( GIN, c );
     gpr_$text('Ungueltiger Typnamenindex: ',28,status);
     writeint(n);
     newline
     end
end;  (*Typnameeinlesen*)

procedure TLeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzT)
       then begin
	    TTab[i].name[0]:= chr(0);
	    TTab[i].name[1]:= '#';
	    end
       end;
end;   {TLeicheneinlesen}

procedure NTLeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzNT)
       then begin
	    NTTab[i].name[0]:= chr(0);
	    NTTab[i].name[1]:= '#';
	    end
       end;
end;   {NTLeicheneinlesen}

procedure PLeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzP)
       then begin
	    PTab[i].name[0]:= chr(0);
	    PTab[i].name[1]:= '#';
	    end
       end;
end;   {PLeicheneinlesen}

procedure SFLeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzSF)
       then begin
	    SFTab[i].name[0]:= chr(0);
	    SFTab[i].name[1]:= '#';
	    end
       end;
end;   {SFLeicheneinlesen}

procedure ALeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzA)
       then begin
	    ATab[i].name[0]:= chr(0);
	    ATab[i].name[1]:= '#';
	    end
       end;
end;   {ALeicheneinlesen}

procedure TypLeicheneinlesen;
begin
read( GIN, c );
if (c <> '$')
then while (c <> ']') do
       begin
       Zahleinlesen(i);
       if (1 <= i) and (i <= maxanzTyp)
       then begin
	    TypTab[i].name[0]:= chr(0);
	    TypTab[i].name[1]:= '#';
	    end
       end;
end;   {TypLeicheneinlesen}


begin
open(GIN, eingabedatei);
reset( GIN );
read(GIN,c);
if c='I' then neu:=true else neu:=false;
fehler := false;
readln(GIN);
repeat read( GIN, c ) until (c = ':');
boollesen( AG.Konsistent );
repeat read( GIN, c ) until (c = ':');
Identeinlesen( AG.PhasenId );
repeat read( GIN, c ) until (c = ':');
Identeinlesen( AG.InGName );
repeat read( GIN, c ) until (c = ':');
Identeinlesen( AG.OutGName ); readln( GIN );
repeat read( GIN, c ) until (c = ':');
Zahleinlesen( AG.Axiom ); readln( GIN );
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.Terms:= 0
else begin
     Zahleinlesen(i); AG.Terms:= i; Termeinlesen(i); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); Termeinlesen(i); read( GIN, c )
        end
     end;
readln( GIN, c );   {','}
TLeicheneinlesen;
readln( GIN, c );   {','}
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.Nonterms:= 0
else begin
     Zahleinlesen(i); AG.Nonterms:= i; Nontermeinlesen(i); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); Nontermeinlesen(i); read( GIN, c )
        end
     end;
readln( GIN, c );   {','}
NTLeicheneinlesen;
readln( GIN, c );   {','}
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.Prods:= 0
else begin
     Zahleinlesen(i); AG.Prods:= i; Prodeinlesen(i); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); Prodeinlesen(i); read( GIN, c )
        end
     end;
readln( GIN, c );   {','}
PLeicheneinlesen;
readln( GIN, c );   {','}
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.SemRules:= 0
else begin
     Zahleinlesen(i); AG.SemRules:= i; SemFkteinlesen(i); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); SemFkteinlesen(i); read( GIN, c )
        end
     end;
readln( GIN, c );   {','}
SFLeicheneinlesen;
readln( GIN, c );   {','}
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.Attrs:= 0
else begin
     Zahleinlesen(i); AG.Attrs:= i; Attreinlesen(i); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); Attreinlesen(i); read( GIN, c );
        end
     end;
readln( GIN, c );   {','}
ALeicheneinlesen;
readln( GIN, c );   {','}
repeat read( GIN, c ) until (c = '[') or (c = '$');
if (c = '$')
then AG.Typen:= 0
else begin
     Zahleinlesen(i); AG.Typen:= i; Typnameeinlesen( i ); read( GIN, c );
     while ( c <> ']') do
        begin
        readln( GIN ); Zahleinlesen(i); Typnameeinlesen( i ); read( GIN, c );
        end
     end;
readln( GIN, c );   {','}
TypLeicheneinlesen;
readln( GIN, c );   {')'}  
close(GIN);
if (eingabedatei <> AGtmp)
 then begin
       newline;
       newline;                                          
       gpr_$text(' Grammatik eingelesen!',22,status);
       newline;
      end;
if fehler then meldefehler(61);
ASymb.gebund := [];
akt := AG.Attrs;
while (akt <> 0) do
begin
  ASymb.gebund := ASymb.gebund + [ATab[akt].symbol];
  akt := ATab[akt].nxt
end
end;  (*Grammatikeinlesen*)

