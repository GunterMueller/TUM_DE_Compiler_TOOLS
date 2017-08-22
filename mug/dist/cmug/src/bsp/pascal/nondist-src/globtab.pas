




procedure hash(* hl: HashListen; var s: Ident; var el: integer; var ex: boolean *);
var relart: lexrel;
    i,r,l1,hllaenge: integer;
    aktname: Ident;
    c: char;
begin
hllaenge:=hashtablaenge(hl);
r:=0;
for i:=1 to ord(s[0]) do r:=(ord(s[i])*31+r) mod hllaenge;
l1:=0;
i:=0;
while i<hllaenge do
  begin
  el:=succ( (r+i) mod hllaenge);
  case hl of
    prodHL: aktname:=PTab[el].name;
    termHL: aktname:=TTab[el].name;
    attrHL: aktname:=ATab[el].name;
    nontHL: aktname:=NTTab[el].name;
    sfktHL: aktname:=SFTab[el].name;
    typeHL: aktname:=TypTab[el].name;
    noList: wrtERR1('hash [1]');
    end;
  if ord(aktname[0])=0 then
    begin
    (* freier Eintrag oder Leiche *)
    if aktname[1]=blk then
      begin (*freier Eintrag*)
      if l1>0 then el:=l1 else { null };
      ex:=false;
      i:=wievielfrei(hl);
      if i<vorwarn then meldeueberlauf (hl,i); 
      i:=hllaenge;
      end
    else
      begin (*Leiche*)
      if l1=0 then l1:=el else { null };
      end;
    end
  else
    begin (* gueltiger Eintrag gefunden *)
    rel (aktname,relart,s);
    if relart=lexgleich then
      begin (* Element gefunden *)
      ex:=true;
      i:=hllaenge;
      end
    else { null } (* Element war nicht das gesuchte *)
    end;
  i:=succ(i);
  end (* while *);
if i=hllaenge then 
  begin
  if l1<>0 then 
    begin
    ex:=false;
    el:=l1;
    end 
  else
    begin
    clearscreen;
    writestring(' Ueberlauf in der Tabelle der ');
    case hl of
      prodHL: gpr_$text('Produktionen',12,status);
      nontHL: gpr_$text('Nonterminale',12,status);
      termHL: gpr_$text('Terminale',9,status);
      attrHL: gpr_$text('Attribute',10,status);
      sfktHL: gpr_$text('Funktionen',11,status);
      typeHL: gpr_$text('Typnamen',8,status);
      end (*case*);
    gpr_$text('!!!',3,status);
    newline;
    newline;
    gpr_$text('Das Programm kann nicht fortgesetzt werden.',43,status); 
    newline;
    gpr_$text('Weitere Massnahmen siehe unter Kapitel "Beschraenkungen" der',60,status);
    newline;
    gpr_$text('Programmdokumentation.',22,status);  
    newline;
    newline;
    writelnstring('Ich warte auf "#".'); 
    keys := ['#',kbd_$pop]; {Create a key set.}
    gpr_$enable_input(gpr_$keystroke, keys, status); 
    keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
    gpr_$enable_input(gpr_$buttons, keys, status); 
    unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
    irrEnde;
    end;
  end;
end (* hash *);



procedure lexeinhaengen(* hl: HashListen; el: integer *);
var hz, az, hznext: integer;
    relart: lexrel;
    elname, hzname: Ident;
begin
az:=0;
case hl of
  prodHL: begin hz:=AG.Prods; PTab[el].nxt:=0 end;
  nontHL: begin hz:=AG.Nonterms; NTTab[el].nxt:=0 end;
  termHL: begin hz:=AG.Terms; TTab[el].nxt:=0 end;
  sfktHL: begin hz:=AG.SemRules; SFTab[el].nxt:=0 end;
  attrHL: begin hz:=AG.Attrs; ATab[el].nxt:=0 end;
  typeHL: begin hz:=AG.Typen; TypTab[el].nxt:=0 end;
  noList: wrtERR1('lexeinf:');
  end (* case *);
while hz<>0 do
  begin
  case hl of
    prodHL: begin elname:=PTab[el].name; hzname:=PTab[hz].name;
 	        hznext:=PTab[hz].nxt end;
    nontHL: begin elname:=NTTab[el].name; hzname:=NTTab[hz].name;
 	        hznext:=NTTab[hz].nxt end;
    termHL: begin elname:=TTab[el].name; hzname:=TTab[hz].name;
 	        hznext:=TTab[hz].nxt end;
    attrHL: begin elname:=ATab[el].name; hzname:=ATab[hz].name;
 	        hznext:=ATab[hz].nxt end;
    sfktHL: begin elname:=SFTab[el].name; hzname:=SFTab[hz].name;
 	        hznext:=SFTab[hz].nxt end;
    typeHL: begin elname:=TypTab[el].name; hzname:=TypTab[hz].name;
                hznext:=TypTab[hz].nxt end;
    end (* case *);
  rel(elname,relart,hzname);
  if relart=lexgroesser then
    begin
    az:=hz;
    hz:=hznext;
    end
  else
    begin
    case hl of
      prodHL: PTab[el].nxt:=hz;
      nontHL: NTTab[el].nxt:=hz;
      termHL: TTab[el].nxt:=hz;
      attrHL: ATab[el].nxt:=hz;
      sfktHL: SFTab[el].nxt:=hz;
      typeHL: TypTab[el].nxt:=hz;
      end (* case *);
    hz:=0;
    end;
  end (*while*);
case hl of
  prodHL: if az=0 then AG.Prods:=el else PTab[az].nxt:=el; 
  nontHL: if az=0 then AG.Nonterms:=el else NTTab[az].nxt:=el; 
  termHL: if az=0 then AG.Terms:=el else TTab[az].nxt:=el; 
  attrHL: if az=0 then AG.Attrs:=el else ATab[az].nxt:=el; 
  sfktHL: if az=0 then AG.SemRules:=el else SFTab[az].nxt:=el; 
  typeHL: if az=0 then AG.Typen:=el else TypTab[az].nxt:=el;
  end (*case*);
end (*lexeinhaengen*);


procedure lexaushaengen (* hl: HashListen; el: integer *);
var hz: integer;
begin
case hl of
  typeHL: if AG.Typen=el then AG.Typen:=TypTab[el].nxt
	  else
	    begin
	    hz:=AG.Typen;
	    while TypTab[hz].nxt<>el do hz:=TypTab[hz].nxt;
	    TypTab[hz].nxt:=TypTab[el].nxt;
	    end;
  prodHL: if AG.Prods=el then AG.Prods:=PTab[el].nxt
	  else
	    begin
	    hz:=AG.Prods;
	    while PTab[hz].nxt<>el do hz:=PTab[hz].nxt;
	    PTab[hz].nxt:=PTab[el].nxt;
	    end;
  nontHL: if AG.Nonterms=el then AG.Nonterms:=NTTab[el].nxt
	  else
	    begin
	    hz:=AG.Nonterms;
	    while NTTab[hz].nxt<>el do hz:=NTTab[hz].nxt;
	    NTTab[hz].nxt:=NTTab[el].nxt;
	    end;
  termHL: if AG.Terms=el then AG.Terms:=TTab[el].nxt
	  else
	    begin
	    hz:=AG.Terms;
	    while TTab[hz].nxt<>el do hz:=TTab[hz].nxt;
	    TTab[hz].nxt:=TTab[el].nxt;
	    end;
  attrHL: if AG.Attrs=el then AG.Attrs:=ATab[el].nxt
	  else
	    begin
	    hz:=AG.Attrs;
	    while ATab[hz].nxt<>el do hz:=ATab[hz].nxt;
	    ATab[hz].nxt:=ATab[el].nxt;
	    end;
  sfktHL: if AG.SemRules=el then AG.SemRules:=SFTab[el].nxt
	  else
	    begin
	    hz:=AG.SemRules;
	    while SFTab[hz].nxt<>el do hz:=SFTab[hz].nxt;
	    SFTab[hz].nxt:=SFTab[el].nxt;
	    end;
  noList: wrtERR1('lexaushaengen:');
  end (*case*);
end (*lexaushaengen*);


procedure initkontext;
var i: integer;
begin
for i:=minvibslg to 0 do beschaffevibselmt(i);
end;


procedure initline;
(* nur fuer vs...-prozeduren! *)
begin
if ViBsLg<maxvibslg then ViBsLg:=succ(ViBsLg);
beschaffevibselmt(ViBsLg);
end (*initline*);


procedure wrtPtoktxt(* pr: integer *);
var pfeil,vn: Ident;
    s: VokListe;
    cp,cpe: integer;
begin
pfeil:=' ->'; pfeil[0]:=chr(2);
initkontext;
with PTab[pr] do
  begin
  with ViBs[minvibslg]^ do
    begin
    viline:=' INFO: Produktion';
    insert(name,viline,19);
    end;
  with ViBs[succ(minvibslg)]^ do
    begin
    if vater<>nil then insert(NTTab[vater^.nt].name,viline,1);
    insert(pfeil,viline,succ(idlaenge));
    s:=soehne; cp:=idlaenge+4;
    while s<>nil do
      begin
      if s^.typ=nont then vn:=NTTab[s^.nt].name else vn:=TTab[s^.nt].name;
      cpe:=pred(cp+ord(vn[0]));
      if cpe<=mvibsbr then
	begin
	insert(vn,viline,cp);
	cp:=cpe+2;
	s:=s^.nxt;
	end
      else
	begin
	viline[mvibsbr]:='!';
	s:=nil;
	end;
      end (*while*);
    end (*with*);
  end (*with*);
end (*wrtPtoktxt*);


procedure evibs2 (* prtikons,istIdent: boolean; hl: HashListen; zugriff: HLZugriff; var c: Ident; var el: integer *);
var nxtline: integer;
    blocked,sw,wechsle,gewaehlt: boolean;
    c1: char;
    relart: lexrel;

  procedure setcur(z: integer);
  begin
  with evibsD do setCursor(e0-z*e9,0);
  end;

  procedure menue;
  begin
  with evibsD do
    setCursor(e8+3*e9+2,0);
  gpr_$text('          EINGABEMOEGLICHKEITEN:',32,status);
  newline;
  gpr_$text(' Cursortasten "auf", "ab" oder Mausbewegung, ',45,status);
  if not istIdent 
  then begin newline; gpr_$text(' 0 oder linke Maustaste: zurueck, ',32,status) end;
  gibPromptChar; gpr_$text('oder mittlere Maustaste: ',25,status);
  case zugriff of
    seeonly: begin
              gpr_$text('zurueck',7,status);
              newline;
             end;
    redonly, rdorwrt: begin
                       gpr_$text('uebernimmt',10,status);
                       newline;
                      end;
    wrtonly: begin
              gpr_$text('generiert',9,status);
              newline;
             end;
    end (*case*);
  end(*menue*);

  procedure display;
  var i: integer;
      akt: visymbolptr;
  begin
  with evibsD do
    begin
    male4eck(true,e8,e7,0,rbs.xpixels);
    for i:=e4 to e5 do
      begin
      with ViBs[i]^ do
        begin setcur(i+e6); gpr_$text(' ',1,status); gpr_$text(viline,80,status);
        if prtikons then
          begin
          akt:=firstsym;
          while akt<>nil do
            begin
	    with evibsD do writeikon(e0-(i+e6)*e9, akt^.spalte,akt^.symbol);
            akt:=akt^.nxt
            end
          end
        end
      end;
    menue;
    end;
  end(*display*);

  procedure vorwaerts(var nxtline: integer; var blockt: boolean);
   var i:integer;
  begin
  with evibsD do
    begin
    if qz>=ViBsLg then blockt:=true
    else
      begin
      if hl=sfktHL then i:=3 else i:=1;
      nxtline:=succ(qz);
      while (nxtline<ViBsLg) and (ViBs[nxtline]^.viline[i]=blk) do nxtline:=succ(nxtline);
      blockt:=ViBs[nxtline]^.viline[i]=blk;
      end
    end;
  end;

  procedure rueckwaerts (var nxtline: integer; var blockt: boolean);
   var i:integer;
  begin
  with evibsD do
    begin
    if qz<=1 then blockt:=true
    else
      begin
      if hl=sfktHL then i:=3 else i:=1;
      nxtline:=pred(qz);
      while (nxtline>1) and (ViBs[nxtline]^.viline[i]=blk) do nxtline:=pred(nxtline);
      blockt:=ViBs[nxtline]^.viline[i]=blk;
      end;
    end;
  end;

  procedure e5e6;
  begin
  with evibsD do
    begin
    e5:=pred(e4+e3); if e5>ViBsLg then e5:=ViBsLg;
    e6:=e1-e4;
    end;
  end;

  procedure pos (var neubild: boolean);
  var i,j,nxtqz: integer;
      s,s1: Ident;
      blocked: boolean;
  begin
  with evibsD do
    begin
    neubild:=false; qz:=0;
    repeat
      vorwaerts (nxtqz,blocked);
      if not blocked then
        begin
        qz:=nxtqz;
        if hl=sfktHL then j:=3 else j:=1;
        for i:=j to idlaenge do s1[i-j+1]:=ViBs[qz]^.viline[i];
        zuw(s1,s);
        rel(s,relart,c);
        blocked:=relart<>lexkleiner;
        end;
      ;
    until blocked;
    vorwaerts(nxtqz,blocked);
    if blocked then nxtqz:=ViBsLg else nxtqz:=pred(nxtqz);
    if (qz<e4) or (nxtqz>e5) then
      begin
      neubild:=true; 
      e4:=qz;
      e5e6;
      display;
      end;
    end;
  end (*pos*);

begin (* evibs *)
sw:=aktSeite=0;
{Seite1;}
with evibsD do
  begin
  e5e6;
  gewaehlt:=false;
  if ord(c[0])<>0 then
    begin pos(wechsle); if not wechsle then if prtreq then display end
  else if prtreq then display;
  if ViBsLg>=maxvibslg then meldefehler(31);
  repeat (* until gewaehlt *)
    setcur(qz+e6); 
    {gpr_$set_cursor_active(true,status);}
    cursoron;
    move_read(c1);
    cursoroff;                          
    {gpr_$set_cursor_active(false,status);}
    if c1 in ['2','4','6','8','0',trz] then 
      begin
        case c1 of
        '2','6':
          begin
	  vorwaerts(nxtline,blocked);
	  if blocked then nxtline:=ViBsLg else
	    begin
	    qz:=nxtline;
	    vorwaerts(nxtline,blocked);
	    if blocked then nxtline:=ViBsLg else nxtline:=pred(nxtline);
	    end;
	  if nxtline>e5 then
	    begin
	    e4:=qz;
	    e5e6;
	    display;
	    end;
          end;
        '8','4': begin
	     rueckwaerts(nxtline,blocked);
	     if blocked then nxtline:=1 else { null };
	     if nxtline >= e4 then qz:=nxtline
	     else
	       begin
	       qz:=qz-e3; if qz<1 then qz:=1;
	       e4:=qz;
	       e5e6;
	       display;
               end;
	     end;
        '0': if not istIdent then begin gewaehlt:=true; el:=ERR end;
        trz:
          begin
	  el:=ViBs[qz]^.hashind;
	  case zugriff of
	    seeonly: begin el:=ERR; gewaehlt:=true end;
	    wrtonly: begin el:=-1; gewaehlt:=true end;
	    redonly: if el>0 then gewaehlt:=true else begin beep; beep end;
	    rdorwrt: if (el=-1) or (el>0) then gewaehlt:=true else begin beep; beep end;
	    end (*case*);
          end;
        end (*case*)
      end
    else if (ord(c1)>=32) and (ord(c1)<=126) then
      begin
      c[0]:=chr(1); c[1]:=c1;
      with rbs do
        begin
        male4eck(true,e8+2*e9,e8+3*e9-1,30*zbreite,xpixels);
        setCursor(e8+2*e9,30*zbreite);
        gpr_$text(' PRAEFIX=',9,status);
        editname(e8+2*e9,41*zbreite,hl,c);
        end;
      pos(wechsle);
      end
    else (*skip*);
  until gewaehlt;
  end;
if el>0 then
  begin
  case hl of
    prodHL: c:=PTab[el].name;
    nontHL: c:=NTTab[el].name;
    termHL: c:=TTab[el].name;
    typeHL: c:=TypTab[el].name;
    attrHL: c:=ATab[el].name;
    sfktHL: c:=SFTab[el].name;
    end (*case*);
  end
else (* c wie vom benutzer eingegeben *);
if sw then Seite0;
end (*evibs2*);


procedure evibs (* istIdent: boolean; hl: HashListen; zugriff: HLZugriff; var c: Ident; var el: integer *);
var i: integer;
    akt: visymbolptr;
    sw: boolean;
begin
sw:=aktSeite=0;
{Seite1;}
clearscreen;;  
if (hl=nontHL) or (hl=attrHL) then evibsD.e9:=gibazh(IconsMitText) else evibsD.e9:=rbs.zhoehe;
evibsD.prtreq:=true;
initevibsD(3,rbs.ypixels+(minvibslg-4)*evibsD.e9-3,evibsD.e9);
for i:=minvibslg to 0 do with ViBs[i]^ do
  begin
  setCursor(succ(rbs.ypixels)-(4+minvibslg-i)*evibsD.e9,0); gpr_$text(' ',1,status);
  gpr_$text(viline,80,status);
  akt:=firstsym;
  while akt<>nil do
    begin
    with rbs do writeikon(succ(ypixels)-(4+minvibslg-i)*evibsD.e9, akt^.spalte, akt^.symbol);
    akt:=akt^.nxt;
    end;
  end (*for*);
evibs2(true,istIdent,hl,zugriff,c,el);
if sw then Seite0;
end (*evibs*);


procedure vsptp(* zugriff: HLZugriff *);
var i,akttn: integer;
begin
for i:=1 to ViBsLg do gibfreivibselmt(i);
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(*** VEREINBARTE TYPNAMEN (ANFANG) ***)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,
  rdorwrt: begin
	   initline;
	   with ViBs[ViBsLg]^ do
	     begin
	     viline:='* Neuen Typnamen vereinbaren *';
	     hashind:=-1;
	     end;
	   end;
  end (*case*);
akttn:=AG.Typen;
while akttn<>0 do
  begin
  initline;
  with ViBs[ViBsLg]^ do
    begin
    hashind:=akttn;
    insert(TypTab[akttn].name,viline,1);
    end (*with*);
  akttn:=TypTab[akttn].nxt;
  end (*while*);
initline;
ViBs[ViBsLg]^.viline:='{*** TYPNAMEN {ENDE} ***}';
end (*vsptp*);


procedure vspsf(* zugriff: HLZugriff *);
var akt: integer;
    ti: TypListe;
    rbr: integer;
    l: integer;
    kennzeichen:Ident;

begin 
for l:=1 to ViBsLg do gibfreivibselmt(l);
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(************ TABELLE DER FUNKTIONEN (ANFANG) ************)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,rdorwrt:
           begin 
	   initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='* Neue Funktion vereinbaren *';
             hashind:=-1;
             end;
	   initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='# Attribut durchreichen #';
             hashind:=IDNT;
             end
           end;
  end (*case*);
akt:=AG.SemRules;
while akt<>0 do
  begin
  initline;
  ViBs[ViBsLg]^.hashind:=akt;
  kennzeichen[0]:=chr(2);
  kennzeichen[2]:=' ';
  if SFTab[akt].issynfkt
   then kennzeichen[1]:='y'
   else kennzeichen[1]:=' ';
  insert(kennzeichen,ViBs[ViBsLg]^.viline,1); 
  insert(SFTab[akt].name,ViBs[ViBsLg]^.viline,3);
  ViBs[ViBsLg]^.viline[succ(idlaenge+5)]:='(';
  rbr:=mvibsbr-succ(idlaenge+5);
  ti:=SFTab[akt].parlist;
  while ti<>nil do
    begin
    l:=succ(ord(TypTab[ti^.typ].name[0]));
    if rbr-l>0
    then
      begin
      insert(TypTab[ti^.typ].name,ViBs[ViBsLg]^.viline,succ(mvibsbr-rbr));
      rbr:=rbr-l;
      ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=',';
      end
    else
      begin
      initline;
      rbr:=mvibsbr-succ(idlaenge);
      insert(TypTab[ti^.typ].name,ViBs[ViBsLg]^.viline,succ(mvibsbr-rbr));
      rbr:=rbr-l;
      ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=','
      end;
    ti:=ti^.nxt;
    end (*while*);
  if ViBs[ViBsLg]^.viline[mvibsbr-rbr]='(' 
  then ViBs[ViBsLg]^.viline[succ(mvibsbr-rbr)]:=')'
  else ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=')';
  initline;
  ViBs[ViBsLg]^.viline[idlaenge]:=':'; ViBs[ViBsLg]^.viline[succ(idlaenge)]:='(';
  rbr:=mvibsbr-succ(idlaenge);
  ti:=SFTab[akt].erglist;
  while ti<>nil do
    begin
    l:=succ(ord(TypTab[ti^.typ].name[0]));
    if rbr-l>0
    then
      begin
      insert(TypTab[ti^.typ].name,ViBs[ViBsLg]^.viline,succ(mvibsbr-rbr));
      rbr:=rbr-l;
      ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=',';
      end
    else
      begin
      initline;
      rbr:=mvibsbr-succ(idlaenge);
      insert(TypTab[ti^.typ].name,ViBs[ViBsLg]^.viline,succ(mvibsbr-rbr));
      rbr:=rbr-l;
      ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=','
      end;
    ti:=ti^.nxt;
    end (*while*);
  if ViBs[ViBsLg]^.viline[mvibsbr-rbr]='(' 
  then ViBs[ViBsLg]^.viline[succ(mvibsbr-rbr)]:=')'
  else ViBs[ViBsLg]^.viline[mvibsbr-rbr]:=')';
  akt:=SFTab[akt].nxt
  end (*while akt*);
initline;
ViBs[ViBsLg]^.viline:='{************ TABELLE DER FUNKTIONEN  (ENDE)  ************}';
end (*vspsf*);


procedure vspnt(* zugriff: HLZugriff; praefixop: integer *);
type attrtyp = (inherited, derived);
var at: attrtyp;
    sinh, sder: Ident;
    satt,snoatt: vilinetyp;
    aktnt: integer;
    i,akta: integer;
    nextat: AListe;

begin (*vspnt*)
for i:=1 to ViBsLg do gibfreivibselmt(i);
sinh:=' inherited'; sinh[0]:=chr(10);
sder:=' derived';   sder[0]:=chr(8);
satt:=' (global) attributiert wie folgt:';
snoatt:=' (Nonterminal bisher ohne globale Attribute)';
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(***************** TABELLE DER NONTERMINALS (ANFANG) ******************)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,rdorwrt:
           begin 
	   initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='* Neues Nonterminal vereinbaren *';
             hashind:=-1;
             end
           end;
  end (*case*);
aktnt:=AG.Nonterms;
while aktnt <> 0 do
  begin
  initline;
  with ViBs[ViBsLg]^ do
    begin
    hashind:=aktnt;
    insert(NTTab[aktnt].name,viline,1);
    if praefixop>=2 then
      begin
      if (NTTab[aktnt].inhAttr=nil) and (NTTab[aktnt].derAttr=nil) then catenate(viline,snoatt) else catenate(viline,satt);
      end;
    end;
  if praefixop>=2 then
    begin
    for at:=inherited to derived do 
      begin
      if at=inherited then nextat:=NTTab[aktnt].inhAttr else nextat:=NTTab[aktnt].derAttr;
      while nextat <> nil do
        begin
        akta:=nextat^.attr;
        initline;
        if praefixop>=3 then syminvibs(ViBsLg,15*rbs.zbreite,ATab[akta].symbol);
        insert(ATab[akta].name,ViBs[ViBsLg]^.viline,20);
        ViBs[ViBsLg]^.viline[idlaenge+21]:=':';
        insert(TypTab[ATab[akta].typ].name,ViBs[ViBsLg]^.viline,idlaenge+23);
        if at = inherited
        then insert(sinh,ViBs[ViBsLg]^.viline,2*idlaenge+25)
        else insert(sder,ViBs[ViBsLg]^.viline,2*idlaenge+25);
        nextat:=nextat^.nxt;
        end; (*while*)
      end; (*for*);
    end; (*if*)
  initline;
  aktnt := NTTab[aktnt].nxt;
  end;
initline;
ViBs[ViBsLg]^.viline:='{****************** TABELLE DER NONTERMINALS (ENDE) *******************}';
end (* vspnt *);


procedure vspt(* zugriff: HLZugriff *);
var i,akt: integer;
begin
for i:=1 to ViBsLg do gibfreivibselmt(i);
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(******************* TABELLE DER TERMINALS (ANFANG) *******************)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,rdorwrt:
           begin 
	   initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='* Neues Terminal vereinbaren *';
             hashind:=-1;
             end
           end;
  end (*case*);
akt:=AG.Terms;
while akt <> 0 do
  begin
  initline;
  with ViBs[ViBsLg]^ do
    begin
    hashind:=akt;
    insert(TTab[akt].name,ViBs[ViBsLg]^.viline,1);
    if TTab[akt].typ > 0 then
      begin
      viline[succ(idlaenge)]:=':';
      insert(TypTab[TTab[akt].typ].name,ViBs[ViBsLg]^.viline,idlaenge+3);
      end;
    viline[2*idlaenge+5]:=TTab[akt].sz1;
    viline[2*idlaenge+6]:=TTab[akt].sz2;
    end;
  akt:=TTab[akt].nxt;
  end;
initline;
ViBs[ViBsLg]^.viline:='{******************** TABELLE DER TERMINALS (ENDE) ********************}';
end; (* vspt *)


procedure vspa(* zugriff: HLZugriff; praefixop: integer *);
var i,akt: integer;
    saux,sinh,sder: Ident;

begin (*vspa*)
saux:=' auxiliary'; saux[0]:=chr(9);
sinh:=' inherited'; sinh[0]:=chr(9);
sder:=' derived'; sder[0]:=chr(7);

for i:=1 to ViBsLg do gibfreivibselmt(i);
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(******************* TABELLE DER ATTRIBUTE (ANFANG) *******************)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,rdorwrt:
           begin 
           initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='* Neues Attribut vereinbaren *';
             hashind:=-1;
             end
           end;
  end (*case*);
akt:=AG.Attrs;
while akt<>0 do
  begin
  initline;
  with ViBs[ViBsLg]^ do
    begin
    hashind:=akt;
    insert(ATab[akt].name,ViBs[ViBsLg]^.viline,1);
    syminvibs(ViBsLg,pred(idlaenge)*rbs.zbreite,ATab[akt].symbol);
    viline[idlaenge+4]:=':';
    insert(TypTab[ATab[akt].typ].name,ViBs[ViBsLg]^.viline,idlaenge+6);
    with ATab[akt] do
      case art of
      aux: insert(saux,ViBs[ViBsLg]^.viline,2*idlaenge+8);
      inh: insert(sinh,ViBs[ViBsLg]^.viline,2*idlaenge+8);
      der: insert(sder,ViBs[ViBsLg]^.viline,2*idlaenge+8);
      end (*case*);
    end;
  akt:=ATab[akt].nxt;
  end;
initline;
ViBs[ViBsLg]^.viline:='{******************* TABELLE DER ATTRIBUTE (ENDE) *********************}';
end;


procedure vspp(* zugriff: HLZugriff *);
var i,spanf, deltax1, rdabst, x: integer;
    aktpp: integer;
    pvater, psoehne: VokListe;

begin
for i:=1 to ViBsLg do gibfreivibselmt(i);
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(***************** TABELLE DER PRODUKTIONEN (ANFANG) ******************)';
case zugriff of
  seeonly: ;
  redonly: ;
  wrtonly,rdorwrt:
           begin 
	   initline;
           with ViBs[ViBsLg]^ do
             begin
             viline:='* Neue Produktion vereinbaren *';
             hashind:=-1;
             end
           end;
  end (*case*);
aktpp:=AG.Prods;
while aktpp<>0 do
  begin
  initline;
  with ViBs[ViBsLg]^ do
    begin
    hashind:=aktpp;
    insert(PTab[aktpp].name,ViBs[ViBsLg]^.viline,1);
    viline[ord(succ(ord(PTab[aktpp].name[0])))]:=':';
    end;
  initline;
  pvater:=PTab[aktpp].vater;
  if pvater<>nil then
    insert(NTTab[pvater^.nt].name,ViBs[ViBsLg]^.viline,3);
  with ViBs[ViBsLg]^ do
    begin
    viline[idlaenge+4]:='-';
    viline[idlaenge+5]:='>';
    end
  ;
  with rbs do
    begin
    spanf:=(7+idlaenge);
    deltax1:=succ(idlaenge);
    rdabst:=xpixels div zbreite-deltax1-1;
    end;
  x:=spanf;
  psoehne:=PTab[aktpp].soehne;
  while psoehne <> nil do
    begin
    if psoehne^.typ = term 
    then insert(TTab[psoehne^.t].name,ViBs[ViBsLg]^.viline,x)
    else insert(NTTab[psoehne^.nt].name,ViBs[ViBsLg]^.viline,x);
    x:=x+deltax1;
    if x>= rdabst then
      begin
      x:=spanf;
      initline;
      end;
    psoehne:=psoehne^.nxt;
    end;
  initline;
  aktpp:=PTab[aktpp].nxt;
  end;
initline;
ViBs[ViBsLg]^.viline:='{****************** TABELLE DER PRODUKTIONEN (ENDE) *******************}';
end; (*vspp*)


procedure hlaendern (* hl: HashListen *);
const oRand=4;
var praefixop,y0,ya,yg,yl,ys,anker,el,
    yname,xantw,xname,xantw2,xname2,xantw3,x,y: integer;
    c: char;
    s: Ident;
    geloescht, clrscreen,istIdent: boolean;
    kontext, kontext1: vilinetyp;
    sw: boolean;
    dienst,maxdienst:integer;


  procedure uebersicht;
  var istIdent: boolean;
  begin
  s[0]:=chr(0);
  istIdent:=false;
  kontext1:='(Uebersicht)';
  catenate(ViBs[minvibslg]^.viline,kontext1);
  listenwahl(hl,istIdent,seeonly,praefixop,s,el);
  end;

  procedure bsmask;
  var s: Ident;
  begin
  clearscreen;
  dekodhl(hl,s);
  setCursor(y0,0);
  gpr_$text(kontext,80,status);
  newline;
  setCursor(ya,0); 
  if typeHL=hl
   then gpr_$text('   Typnamen umbenennen',22,status)
   else gpr_$text('   aendert',10,status);
  setCursor(yg,0);
  gpr_$text('   generiert',12,status);
  newline;
  setCursor(yl,0);
  gpr_$text('   loescht',10,status); 
  newline;
  case hl of
    prodHL,termHL,sfktHL,typeHL:
     begin
      gpr_$text('   Uebersicht',14,status); 
      newline;
     end;
    attrHL:
      begin
      gpr_$text('   ordnet Symbol zu',19,status);
      newline;
      gpr_$text('   Uebersicht',14,status); 
      newline;
      end;
    nontHL:
      begin
      gpr_$text('   Uebersicht ohne Attribute',28,status);
      newline;
      gpr_$text('   Uebersicht mit  Attribute',28,status);
      newline;
      end;
    end (*case*);
  gpr_$text('   Zurueck',10,status);
  end;

  function vorsaetzlich: boolean;
  var c: char;
      hlname: Ident;
  begin
  dekodhl(hl,hlname);
  beep; beep;
  if hl=prodHL
   then meldung(54)
   else 
    begin
    meldung(55);
    wrtIdent(hlname);
    gpr_$text(blk,1,status);
    wrtIdent(s);
    meldung(56); 
    end;
 meldung(57);
 antworte(janein,c);
 vorsaetzlich:= c='J';
 clearmeldung;
end (*vorsaetzlich*);


  procedure aeTyp(tind: integer);
  var t2ind: integer;
      istIdent,clscreen: boolean;
      t2: Ident;
  
    procedure Typumbenennen;
    var fenster: integer;
        fenster2: TypListe;
        i: integer;
    begin
    lexaushaengen(typeHL,tind);
    TypTab[tind].name[0]:=chr(0);
    fenster:=AG.Terms;
    while fenster<>0 do
      begin
      if TTab[fenster].typ=tind then TTab[fenster].typ:=t2ind;
      fenster:=TTab[fenster].nxt;
      end;
    fenster:=AG.Attrs;
    while fenster<>0 do
      begin
      if ATab[fenster].typ=tind then ATab[fenster].typ:=t2ind;
      fenster:=ATab[fenster].nxt;
      end;
    fenster:=AG.SemRules;
    while fenster<>0 do
      begin
      fenster2:=SFTab[fenster].parlist;
      for i:=0 to 1 do
        begin
        while fenster2<>nil do
	  begin
	  if fenster2^.typ=tind then fenster2^.typ:=t2ind;
	  fenster2:=fenster2^.nxt;
	  end;
        fenster2:=SFTab[fenster].erglist;
        end (*for*);
      fenster:=SFTab[fenster].nxt;
      end (*while*);
    end (*Typumbenennen*);

  begin (*aeTyp*)
  initkontext;
  with ViBs[minvibslg]^ do
    begin
    viline:='INFO: Aendere Typname';
    insert(TypTab[tind].name,viline,24);
    end;
  if clrscreen then
    begin
    bsmask;
    setCursor(ya,xantw2); wrtIdent(s);
    setCursor(ya,xname2); gpr_$text('->',2,status);
    end
  else loeschewort(yname,0,70);
  setCursor(yname,0); gpr_$text(' Bitte neuen Typnamen angeben',29,status); 
  setCursor(yname,30*rbs.zbreite);
  istIdent:=false;
  lkup(ya,xantw3,typeHL,rdorwrt,istIdent,t2,t2ind,clscreen);
  if istIdent then if tind<>t2ind then Typumbenennen;
  end; (*aeTyp*)
  
begin (* hlaendern*)
sw:=aktSeite=0;
Seite1;
with rbs do
  begin
  y0:=ypixels-oRand*zhoehe;
  ya:=y0-2*zhoehe;
  yg:=y0-3*zhoehe;
  yl:=y0-4*zhoehe;
  ys:=y0-5*zhoehe;
  yname:=y0-8*zhoehe;
  xname:=18*zbreite;
  xantw:=xname+6*zbreite;
  xantw2:=37*zbreite;
  xname2:=xantw2+(succ(idlaenge)*zbreite);
  xantw3:=xname2+3*zbreite;
  end;
case hl of
 prodHL,termHL,sfktHL,typeHL : maxdienst := 4;
 attrHL,nontHL : maxdienst := 5;
end;
kontext:='Dienst';
dekodhl(hl,s);
insert(s,kontext,8);
repeat
  initkontext;
  catenate(ViBs[minvibslg]^.viline,kontext);
  bsmask;
  dienst := 0;
  repeat
   invertBild(2*rbs.zbreite,ya-dienst*rbs.zhoehe-4,27*rbs.zbreite,rbs.zhoehe);
   move_read(c);
   invertBild(2*rbs.zbreite,ya-dienst*rbs.zhoehe-4,27*rbs.zbreite,rbs.zhoehe);
   case c of
    '8' : if dienst > 0 then dienst := pred(dienst);
    '2' : if dienst < maxdienst then dienst := succ(dienst);
   end;
   if (c = PraefixTab[1]) then dienst := -1;
  until (c = trz) or (c = '0') or (c = PraefixTab[1]);
  if (c = '0') then dienst := maxdienst;
  case hl of
    prodHL: anker:=AG.Prods;
    termHL: anker:=AG.Terms;
    attrHL: anker:=AG.Attrs;
    nontHL: anker:=AG.Nonterms;
    sfktHL: anker:=AG.SemRules;
    typeHL: anker:=AG.Typen;
    noList: wrtERR1('hlaendern:');
    end (*case*);
  case dienst of
    0 : if anker=0 then 
	   begin if hl=typeHL then meldefehler(57) else meldefehler(18+ord(hl))
	   end
         else
           begin
	   if hl=typeHL then
	     begin
	     setCursor(ya,xname2); gpr_$text('->',2,status);
	     setCursor(yname,0); gpr_$text(' Bitte bisherigen Typnamen angeben',34,status);
	     xantw:=xantw2;
	     end
	   else
	     begin
	     setCursor(ya,xname); gpr_$text('Name:',5,status);
         setCursor(ya,xname+6*rbs.zbreite);
	     end;
           kontext1:='aendern:';
	       catenate(ViBs[minvibslg]^.viline,kontext1);
           istIdent:=false;
           lkup(ya,xantw,hl,redonly,istIdent,s,el,clrscreen);
	   if istIdent then
	     begin
             case hl of
               prodHL: aeP(el);
               termHL: aeT(el);
               nontHL: aeNT(el);
               sfktHL: aeSF(el);
               attrHL: aeA(el);
               typeHL: aeTyp(el);
               end (*case*);
	     end;
           end;
     1 : begin                                            
         setCursor(yg,xname); gpr_$text('Name:',5,status); 
         setCursor(yg,xname+6*rbs.zbreite);
         istIdent:=false;
	     kontext1:='generieren:';
	     catenate(ViBs[minvibslg]^.viline,kontext1);
         lkup(yg,xantw,hl,wrtonly,istIdent,s,el,clrscreen);
         end;
     2 : if anker=0 then meldefehler(18+ord(hl))
         else
           begin
           setCursor(yl,xname); gpr_$text('Name?',5,status);
           setCursor(yg,xname+6*rbs.zbreite);
           istIdent:=false;
	   kontext1:='loeschen:';
	   catenate(ViBs[minvibslg]^.viline,kontext1);
           lkup(yl,xantw,hl,redonly,istIdent,s,el,clrscreen);
	   if istIdent then
	     begin
             geloescht:=true;
	     case hl of
	       sfktHL: begin
		       if SFTab[el].anwendungen=nil then loescheSFg(el)
		       else if vorsaetzlich then loescheSFg(el)
		       else geloescht:=false;
		       end;
	       nontHL: begin
		       if NTTab[el].anwendungen=nil then loescheNT(el)
		       else if vorsaetzlich then loescheNT(el)
		       else geloescht:=false;
		       end;
	       termHL: begin
		       if TTab[el].anwendungen=nil then loescheT(el)
		       else if vorsaetzlich then loescheT(el)
		       else geloescht:=false;
		       end;
	       prodHL: begin
		       if (PTab[el].vater=nil) and (PTab[el].soehne=nil) then loescheP(el)
		       else if vorsaetzlich then loescheP(el)
		       else geloescht:=false;
		       end;
	       attrHL: begin
		       if not hatAanwdg(el) then loescheA(el)
		       else if vorsaetzlich then loescheA(el)
		       else geloescht:=false;
		       end;
	       typeHL: begin
		       if not hatTypanwdg(el) then
			 begin
			 lexaushaengen(typeHL,el);
			 with TypTab[el] do
			   begin
			   name[0]:=chr(0);
			   name[1]:=trz;
			   end;
			 end
		       else meldefehler(40);
                       end;
	       end (*case*);
	     if not geloescht then meldefehler(39)
	     end
	   else meldefehler(39);
           end;
     3 : begin 
	 if hl in [prodHL,sfktHL,termHL,typeHL] then begin praefixop:=1; uebersicht end;
	 if (hl=attrHL) then begin
                	     el:=0; 
                	     symbolwahl(s,el);
              		     end;
         if (hl=nontHL) then begin praefixop:=1; uebersicht end;
	 end;
     4 : begin
	 if (hl=attrHL) then begin praefixop:=2; uebersicht end;
         if (hl=nontHL) then begin praefixop:=3; uebersicht end;
	 end;
     5 : ;
    -1 : info; 
     otherwise;
    end (*case*);
  ;
until dienst = maxdienst;
if sw then Seite0;
end (*hlaendern*);
