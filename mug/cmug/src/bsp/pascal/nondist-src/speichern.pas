



procedure Grammatikspeichern (* ausgabedatei: filename *);
const  verbrauch = 6;
var i,j:             integer;
    {a,b:              alfa;}
    GOUT:            text;
    SYMBOLE:         file of ASymbDatum;
    SymbolDateiname: filename;
    Symbolextension: packed array [0..7] of char; 
    anzahlzeichen :  integer;
    decoded : cal_$timedate_rec_t; 
    clock : time_$clock_t ;
    fehler:	     boolean;


(*
procedure posZahlspeichern (n: integer);   n=>0 
begin
if n <= 9
then write( GOUT, chr( ord('0')+n ) )
else begin
     posZahlspeichern( n div 10 );
     write( GOUT, chr( ord('0')+(n mod 10) ) )
     end
end;
 *)

procedure Zahlspeichern (n: integer);  (* n=>0 *)
begin
 
 if (anzahlzeichen > 245) then
  begin
    writeln(GOUT) ;
    anzahlzeichen := 0
  end;

 anzahlzeichen := anzahlzeichen + verbrauch ;
 write( GOUT, n:0)

end;

(* procedure Zahlspeichern (n: integer);
begin
if (n < 0)
then begin write( GOUT, '-' ); posZahlspeichern( -n ) end
else posZahlspeichern( n )
end; 
*)
(* Zahlspeichern*) 



procedure Realspeichern (r: real);
var i: integer;
begin
i:= round( r*10000 );
Zahlspeichern(i)
end;   {Realspeichern}

procedure Identspeichern (Id: Ident);
var k: integer;
begin
for k:= 1 to ord( Id[0] ) do write( GOUT, Id[k] )
end; (*Identspeichern*)

procedure PListespeichern (hp: PListe);
var h: PListe;
begin
if hp = nil
then write( GOUT, '$' )
else begin
     write( GOUT, '[' ); h:= hp;
     Zahlspeichern( h^.prod ); h:= h^.nxt;
     while h <> nil do
        begin
        write( GOUT, ',' );
         Zahlspeichern( h^.prod ); h:= h^.nxt
        end;
     write( GOUT, ']' )
     end
end; (*PListespeichern*)

procedure AListespeichern (ha: AListe);
var h: AListe;
begin
if ha = nil
then write( GOUT, '$' )
else begin
     write( GOUT, '[' ); h:= ha;
     Zahlspeichern( h^.attr ); h:= h^.nxt;
     while h <> nil do
        begin
        write( GOUT, ',' );
        Zahlspeichern( h^.attr ); h:= h^.nxt
        end;
     write( GOUT, ']' )
     end
end; (*AListespeichern*)

procedure HAListespeichern (ha: HAListe);
var h: HAListe;
begin
if ha = nil
then write( GOUT, '$' )
else begin
     write( GOUT, '[' ); h:= ha;
     Realspeichern( h^.vx ); write( GOUT, '|' );
     Realspeichern( h^.vy ); write( GOUT, '|' );
     Zahlspeichern( h^.attr ); h:= h^.nxt;
     while h <> nil do
        begin
        write( GOUT, ',' ); Realspeichern( h^.vx );
        write( GOUT, '|' );Realspeichern( h^.vy );
        write( GOUT, '|' );Zahlspeichern( h^.attr ); h:= h^.nxt
        end;
     write( GOUT, ']' )
     end
end; (*HAListespeichern*)

procedure TypListespeichern (ht: TypListe);
var h: TypListe;
begin
if ht = nil
then write( GOUT, '$' )
else begin
     write( GOUT, '[' ); h:= ht;
     Zahlspeichern( h^.typ ); h:= h^.nxt;
     while h <> nil do
        begin
        write( GOUT, ',' ); 
        Zahlspeichern( h^.typ ); h:= h^.nxt
        end;
     write( GOUT, ']' )
     end
end; (*TypListespeichern*)

procedure PunktListespeichern (punkte: PunktListe);
var hpunkte: PunktListe;
begin
if (punkte <> nil)
then begin
     hpunkte:= punkte;
     write( GOUT, '[' );
     repeat
       Realspeichern( hpunkte^.vx ); write( GOUT, '|' );
       Realspeichern( hpunkte^.vy ); hpunkte:= hpunkte^.nxt;
       if (hpunkte = nil)
       then write( GOUT, ']' )
       else write( GOUT, ',' )
     until (hpunkte = nil);
     end
end;   {PunktListespeichern}

procedure Termspeichern (n: integer);
begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( TTab[n].name ); write( GOUT, ',' );
write( GOUT, TTab[n].sz1, TTab[n].sz2, ',' );
Zahlspeichern( TTab[n].typ ); write( GOUT, ',' );
PListespeichern( TTab[n].anwendungen ); write( GOUT, ',' );
Zahlspeichern( TTab[n].scannerklasse ); write( GOUT, ',' );
Zahlspeichern( TTab[n].nxt ); write( GOUT, ')' )
end; (*Termspeichern*)

procedure Nontermspeichern (n: integer);
begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( NTTab[n].name ); write( GOUT, ',' );
AListespeichern( NTTab[n].inhAttr ); write( GOUT, ',' );
AListespeichern( NTTab[n].derAttr ); write( GOUT, ',' );
PListespeichern( NTTab[n].anwendungen ); write( GOUT, ',' );
Zahlspeichern( NTTab[n].scannerklasse ); write( GOUT, ',' );
Zahlspeichern( NTTab[n].nxt ); write( GOUT, ')' )
end; (*Nontermspeichern*)

procedure Vokabelspeichern (v: VokListe);
begin
if (v^.typ = term)
then begin
     write( GOUT, '(T,' ); Zahlspeichern( v^.t ); write( GOUT, ',' )
     end
else begin
     write( GOUT, '(N,' );
     Zahlspeichern( v^.nt ); write( GOUT, ',' );
     AListespeichern( v^.spezInhA ); write( GOUT, ',' );
     AListespeichern( v^.spezDerA ); write( GOUT, ',' );
     if v^.konsistent
     then write( GOUT, 'true,' )
     else write( GOUT, 'false,' )
     end;
Realspeichern( v^.dx ); write( GOUT, ',' );
Realspeichern( v^.dy ); write( GOUT, ')' )
end; (*Vokabelspeichern*)

procedure Prodspeichern (n: integer);
var hv:  VokListe;
    hsf: SemFktListe;

  procedure sFunktionspeichern (sf: SemFktListe);

    procedure ParListespeichern (pl: ParListe);
    var hp: ParListe;

      function Index (hpl: ParListe): integer;
      var v: VokListe;
          i: integer;
          gefunden: boolean;
      begin
      v:= PTab[n].vater; gefunden:= false;
      if v = nil
      then begin v:= PTab[n].soehne; i:= 2 end
      else i:= 1;
      while v <> nil do
         if v = hpl^.vok
         then begin gefunden:= true; v:= nil end
         else begin v:= v^.nxt; i:= i+1 end;
      if gefunden then Index:= i
                  else begin
		       Index:= ERR;
		       fehler := true
		       end
      end; (*Index*)

    begin
    if pl = nil
    then write( GOUT, '$' )
    else begin
         write( GOUT, '[' ); hp:= pl;
         if hp^.vok = nil then Zahlspeichern( 0 )
                          else Zahlspeichern( Index(hp) );
         write( GOUT, '|' ); Zahlspeichern( hp^.attr );
	 PunktListespeichern( hp^.verb );
         hp:= hp^.nxt;
         while hp <> nil do
            begin
	    write( GOUT, ',' );
            if hp^.vok = nil then Zahlspeichern( 0 )
                             else Zahlspeichern( Index(hp) );
            write( GOUT, '|' ); Zahlspeichern( hp^.attr );
	    PunktListespeichern( hp^.verb );
            hp:= hp^.nxt
            end;
	 write( GOUT, ']' )
         end
    end; (*ParListespeichern*)

  begin
  write( GOUT, '(' );
  Zahlspeichern( sf^.semfkt ); write( GOUT, ',' );
  ParListespeichern( sf^.quellpar ); write( GOUT, ',' );
  ParListespeichern( sf^.zielpar );
  if sf^.versorgt
  then write( GOUT, ',true,' )
  else write( GOUT, ',false,' );
  if sf^.gedreht
  then write( GOUT, 'true,' )
  else write( GOUT, 'false,' );
  Realspeichern( sf^.vx ); write( GOUT, ',' );
  Realspeichern( sf^.vy ); write( GOUT, ')' )
  end; (*sFunktionspeichern*)

begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( PTab[n].name ); write( GOUT, ',' );
hv:= PTab[n].vater;
if hv <> nil then Vokabelspeichern( hv ); writeln( GOUT, ',' ); anzahlzeichen:= 0;
hv:= PTab[n].soehne;
if hv = nil
then write( GOUT, '$,' )
else begin
     write( GOUT, '[' );
     Vokabelspeichern( hv ); hv:= hv^.nxt;
     while hv <> nil do
        begin write( GOUT, ',' ); Vokabelspeichern( hv ); hv:= hv^.nxt ; anzahlzeichen:= 0 end;
     write( GOUT, '],' )
     end;
HAListespeichern( PTab[n].hilfsAttr ); writeln( GOUT, ',' ); anzahlzeichen:= 0;
hsf:= PTab[n].semRegeln;
if hsf = nil
then write( GOUT, '$' )
else begin
     write( GOUT, '[' );
     sFunktionspeichern( hsf ); hsf:= hsf^.nxt;
     while hsf <> nil do
        begin
        writeln( GOUT, ',' ); anzahlzeichen:= 0; sFunktionspeichern( hsf ); hsf:= hsf^.nxt
        end;
     write( GOUT, ']' )
     end;
if PTab[n].konsistent
then write( GOUT, ',true,' )
else write( GOUT, ',false,' );
Zahlspeichern( PTab[n].nxt ); write( GOUT, ')' )
end; (*Prodspeichern*)

procedure SemFktspeichern (n: integer);
begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( SFTab[n].name ); write( GOUT, ',' );
if SFTab[n].issynfkt
 then write( GOUT, 'true,' )
 else write( GOUT, 'false,' );
TypListespeichern( SFTab[n].parlist ); write( GOUT, ',' );
TypListespeichern( SFTab[n].erglist ); write( GOUT, ',' );
PListespeichern( SFTab[n].anwendungen ); write( GOUT, ',' );
Zahlspeichern( SFTab[n].nxt ); write( GOUT, ')' )
end; (*SemFktspeichern*)

procedure Attrspeichern (n: integer);
begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( ATab[n].name ); write( GOUT, ',' );
Zahlspeichern( ATab[n].typ ); write( GOUT, ',' );
Zahlspeichern( ATab[n].symbol );
case ATab[n].art of
   inh: write( GOUT, ',inh,' );
   der: write( GOUT, ',der,' );
   aux: write( GOUT, ',aux,' )
end;
Zahlspeichern( ATab[n].nxt ); write( GOUT, ')' )
end; (*Attrspeichern*)

procedure Typnamespeichern (n: integer);
begin
Zahlspeichern( n ); write( GOUT, '(' );
Identspeichern( TypTab[n].name ); write( GOUT, ',' );
Zahlspeichern( TypTab[n].nxt ); write( GOUT, ')' )
end; (*Typnamespeichern*)

procedure TLeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzT do
  if (TTab[i].name[0] = chr(0)) and (TTab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then writeln( GOUT, '],') else writeln( GOUT, '$,' ); anzahlzeichen:= 0;
end;   {TLeichenspeichern}

procedure NTLeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzNT do
  if (NTTab[i].name[0] = chr(0)) and (NTTab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then writeln( GOUT, '],') else writeln( GOUT, '$,' ); anzahlzeichen:= 0
end;   {NTLeichenspeichern}

procedure PLeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzP do
  if (PTab[i].name[0] = chr(0)) and (PTab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then writeln( GOUT, '],') else writeln( GOUT, '$,' ); anzahlzeichen:= 0
end;   {PLeichenspeichern}

procedure SFLeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzSF do
  if (SFTab[i].name[0] = chr(0)) and (SFTab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then writeln( GOUT, '],') else writeln( GOUT, '$,' ); anzahlzeichen:= 0
end;   {SFLeichenspeichern}

procedure ALeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzA do
  if (ATab[i].name[0] = chr(0)) and (ATab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then writeln( GOUT, '],') else writeln( GOUT, '$,' ) ;  anzahlzeichen:= 0
end;   {ALeichenspeichern}

procedure TypLeichenspeichern;
var leichen: boolean;
begin
leichen:= false;
for i:= 1 to maxanzTyp do
  if (TypTab[i].name[0] = chr(0)) and (TypTab[i].name[1] <> ' ')
  then if leichen
       then begin write( GOUT, ',' ); Zahlspeichern(i) end
       else begin write( GOUT, '[' ); Zahlspeichern(i); leichen:= true end;
if leichen then write( GOUT, ']') else write( GOUT, '$' )
end;   {TypLeichenspeichern}


begin 
anzahlzeichen := 0;
fehler := false;
open( GOUT, ausgabedatei );
rewrite( GOUT );
cal_$get_local_time(clock);
cal_$decode_time(clock,decoded);
writeln( GOUT, 'IGEM Version 2.3  Internform erzeugt am ',decoded.day:2,'.',decoded.month:2,'   ',decoded.year:4,
          ' um ',decoded.hour:2,'Uhr ',decoded.minute:2);                                               
writeln( GOUT, 'DIM', idlaenge, maxanzT, maxanzNT, maxanzP, maxanzSF,
         IDNT, maxanzA, maxanzTyp, maxanzASymb);
write( GOUT, 'GRAMMATIK(konsistent:' );
if AG.Konsistent then write( GOUT, 'true' ) else write( GOUT, 'false' );
write( GOUT, ',Phasenid:' ); Identspeichern( AG.PhasenId );
write( GOUT, ',InGName:' );  Identspeichern( AG.InGName );
write( GOUT, ',OutGName:' ); Identspeichern( AG.OutGName ); writeln( GOUT,',');
write( GOUT,  'Axiom:' );    Zahlspeichern( AG.Axiom ); writeln( GOUT, ',' );
write( GOUT,  'TERMS' );    i:= AG.Terms;
if i = 0
then writeln( GOUT, '$,' )
else begin
     write( GOUT, '[' ); Termspeichern( i ); i:= TTab[i].nxt;
     while i <> 0 do
        begin writeln( GOUT, ',' ); anzahlzeichen:= 0; Termspeichern( i ); i:= TTab[i].nxt end;
     writeln( GOUT, '],' ); anzahlzeichen:= 0
     end;
TLeichenspeichern;
write( GOUT, 'NONTERMS' ); i:= AG.Nonterms;
if i = 0
then begin writeln( GOUT, '$,' ); anzahlzeichen:= 0 end
else begin
     write( GOUT, '[' ); Nontermspeichern( i ); i:= NTTab[i].nxt;
     while i <> 0 do
       begin writeln( GOUT, ',' );  anzahlzeichen:= 0;Nontermspeichern( i ); i:= NTTab[i].nxt end;
     writeln( GOUT, '],' ) ; anzahlzeichen:= 0;
     end;
NTLeichenspeichern;
write( GOUT, 'PRODS' ); i:= AG.Prods;
if i = 0
then begin writeln( GOUT, '$,' ); anzahlzeichen:= 0 end
else begin
     write( GOUT, '[' ); Prodspeichern( i ); i:= PTab[i].nxt;
     while i <> 0 do
        begin writeln( GOUT, ',' ); anzahlzeichen:= 0; Prodspeichern( i ); i:= PTab[i].nxt end;
     writeln( GOUT, '],' ); anzahlzeichen:= 0
     end;
PLeichenspeichern;
write( GOUT, 'SEMFKTS' ); i:= AG.SemRules;
if i = 0
then begin writeln( GOUT, '$,' ); anzahlzeichen:= 0 end
else begin
     write( GOUT, '[' ); SemFktspeichern( i ); i:= SFTab[i].nxt;
     while i <> 0 do
        begin writeln( GOUT, ',' );  anzahlzeichen:= 0;SemFktspeichern( i ); i:= SFTab[i].nxt end;
     writeln( GOUT, '],' ); anzahlzeichen:= 0
     end;
SFLeichenspeichern;
write( GOUT, 'ATTRS' ); i:= AG.Attrs;
if i = 0
then begin writeln( GOUT, '$,' ); anzahlzeichen:= 0 end
else begin
     write( GOUT, '[' ); Attrspeichern( i ); i:= ATab[i].nxt;
     while i <> 0 do
        begin writeln( GOUT, ',' ); anzahlzeichen:= 0; Attrspeichern( i ); i:= ATab[i].nxt end;
     writeln( GOUT, '],' ) ; anzahlzeichen:= 0
     end;
ALeichenspeichern;
write( GOUT, 'TYPNAMEN' ); i:= AG.Typen;
if i = 0
then begin writeln( GOUT, '$,' ); anzahlzeichen:= 0 end
else begin
     write( GOUT, '[' ); Typnamespeichern( i ); i:= TypTab[i].nxt;
     while i <> 0 do
        begin writeln( GOUT, ',' ); anzahlzeichen:= 0; Typnamespeichern(i); i:= TypTab[i].nxt end;
     writeln( GOUT, '],' ) ; anzahlzeichen:= 0
     end;
TypLeichenspeichern;
writeln( GOUT, ')' );
writeln(GOUT, '(* === Aktuelle Dimensionierungsgrenzen === *)');
writeln(GOUT, 'idlaenge_    = ', idlaenge,';');
writeln(GOUT, 'maxanzT_     = ', maxanzT,';'); 
writeln(GOUT, 'maxanzNT_    = ', maxanzNT,';');
writeln(GOUT, 'maxanzP_     = ', maxanzP,';');
writeln(GOUT, 'maxanzSF_    = ', maxanzSF,';');
writeln(GOUT, 'ID_          = ', IDNT,';');
writeln(GOUT, 'maxanzA_     = ', maxanzA,';');
writeln(GOUT, 'maxanzTyp_   = ', maxanzTyp,';'); 
writeln(GOUT, 'maxanzASymb_ = ', maxanzASymb,';'); 
close(GOUT);
if (ausgabedatei <> AGtmp)
 then begin
      gpr_$text(' Grammatik gespeichert!',23,status);
      newline;
      end;
if fehler then meldefehler(62);
end; (*Grammatikspeichern*)
