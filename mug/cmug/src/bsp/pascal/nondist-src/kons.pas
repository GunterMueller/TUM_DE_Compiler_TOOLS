





function isSFversorgt(* sr: SemFktListe): boolean *);
var v: boolean;
    l: ParListe;
begin
v:=true; l:=sr^.quellpar;
while (l <> nil) and v do
  begin
  v:=(l^.vok<>nil) or (l^.attr<>0);
  l:=l^.nxt;
  end;
if v then
  begin
  l:=sr^.zielpar;
  while (l<>nil) and v do
    begin
    v:=(l^.vok<>nil) or (l^.attr<>0);
    l:=l^.nxt;
    end;
  end;
isSFversorgt:=v;
end (*isSFversorgt*);


procedure defunberA (* pr: integer *);
var v: VokListe;
    sr: SemFktListe;
    ap: ParListe;
    pos: integer;
begin
with PTab[pr] do
  begin
  if vater<>nil then
    begin
    expandntv(vater);
    copyALft(vater^.spezDerA,vater^.unversA);
    comprntv(vater);
    end;
  v:=soehne;
  while v<>nil do
    begin
    if v^.typ=nont then
      begin
      expandntv(v);
      copyALft(v^.spezInhA,v^.unversA);
      comprntv(v);
      end;
    v:=v^.nxt;
    end;
  copyHALft(hilfsAttr,unversHAttr);
  sr:=semRegeln;
  while sr<>nil do
    begin
    ap:=sr^.zielpar;
    while ap<>nil do
      begin
      with ap^ do
	begin
	if vok<>nil then
	  begin
	  if attr<>0 then
	    begin
	    sAausAL(attr,vok^.unversA,pos);
	    if pos=0 then wrtERR1('defunberA[1]');
	    end
	  else wrtERR1('defunberA[2]')
	  end
	else
	  begin
	  if attr<>0 then sHAausHAL(attr,unversHAttr)
	  else (*offene Parameterbindung*)
	  end
	end (*with ap*);
      ap:=ap^.nxt;
      end (*while ap*);
    sr:=sr^.nxt;
    end (*while sr*);
  end (*with PTab*);
end (*defunberA*); 


procedure defallunberA;
var pr: integer;
begin
pr:=AG.Prods;
while pr<>0 do  
  begin
  defunberA(pr);
  pr:=PTab[pr].nxt;
  end;
end (*defallunberA*);


function isPkons (* pr: integer): boolean *);
var k: boolean;
    sr: SemFktListe;
    s: VokListe;
begin
defunberA(pr);
with PTab[pr] do
  begin
  k:= vater<>nil;
  if k then k:= unversHAttr=nil;
  if k then k:= vater^.unversA=nil;
  s:=soehne;
  while (s<>nil) and k do
    begin
    k:=s^.unversA=nil;
    s:=s^.nxt;
    end;
  sr:=semRegeln;
  while (sr<>nil) and k do
    begin
    sr^.versorgt:=isSFversorgt(sr);
    k:=sr^.versorgt;
    sr:=sr^.nxt;
    end;
  isPkons:=k;
  end;
end (* isPkons *);


function isNTkons(* nt: integer): boolean *);
var v: boolean;
    vk: AListe;
    pr: integer;
    kind: VokListe;
begin
v:=true;
vk:=inPvorkommen(NTTab[nt].anwendungen);
while (vk<>nil) and v do
  begin
  pr:=vk^.attr;
  vk:=vk^.nxt;
  with PTab[pr] do
    begin
    if vater<>nil then if vater^.nt=nt then v:=vater^.konsistent;
    kind:=soehne;
    while (kind<>nil) and v do
      begin
      if kind^.typ = nont then if kind^.nt=nt then v:=kind^.konsistent;
      kind:=kind^.nxt;
      end;
    end;
  end;
isNTkons:=v;
end (*isNTkons*);


procedure checkPs;
var pr: integer;
begin
pr:=AG.Prods;
while pr<>0 do
  begin
  PTab[pr].konsistent:=isPkons(pr);
  pr:=PTab[pr].nxt;
  end;
end (*checkPs*);


function sindPkons (*: boolean *);
var pr: integer;
    k: boolean;
begin
pr:=AG.Prods; k:=true;
while (pr<>0) and k do
  begin
  k:=isPkons(pr);
  pr:=PTab[pr].nxt;
  end;
sindPkons:=k;
end; (*sindPkons*)


function sindNTkons (*: boolean *);
var istkons: boolean;
    nt: integer;
begin
nt:=AG.Nonterms; istkons:=true;
while (nt<>0) and istkons do
  begin
  istkons:=isNTkons(nt);
  nt:=NTTab[nt].nxt;
  end;
sindNTkons:=istkons;
end; (*sindNTkons*)


function isAGkons (*: boolean *);
var k: boolean;
begin
with AG do
  begin
  k:=(ord(InGName[0])<>0) and (ord(OutGName[0])<>0) and (ord(PhasenId[0])<>0);
  if k then k:=Axiom>0;
  if k then k:=sindPkons;
  if k then k:=sindNTkons;
  end;
isAGkons:=k;
end (*isAGkons*);


procedure vsNTinkons (* n: integer *);
var keine, vtxt,stxt,spos: Ident;
    anwtxt,ktxt: vilinetyp;
    s: VokListe;
    pr,sohnnr: integer;
    sw: boolean;

  procedure wrtattrs (al: AListe);
  var ca: AListe;
      inherited,derived: Ident;
  begin
  inherited:=' inherited'; inherited[0]:=chr(9);
  derived:=' derived'; derived[0]:=chr(7);
  ca:=al;
  while ca<>nil do
    begin
    initline;
    with ATab[ca^.attr],ViBs[ViBsLg]^ do
      begin
      insert(name,viline,5);
      viline[idlaenge+5]:=':';
      insert(TypTab[typ].name,viline,idlaenge+7);
      if art=inh then insert(inherited,viline,2*idlaenge+9)
      else insert(derived,viline,2*idlaenge+9);
      end;
    ca:=ca^.nxt;
    end;
  end (*wrtattr*);

begin (*vsNTinkons*)
sw:=aktSeite=0;
Seite1;
vtxt:=' (Vater)'; vtxt[0]:=chr(7);
stxt:=' (  . Sohn)'; stxt[0]:=chr(10);
anwtxt:='in den Anwendungen:';
ktxt:='konsistent zur globalen Attributierung';
initkontext;
with ViBs[minvibslg]^ do
  begin
  viline:='Attributierung des Nonterminals';
  insert(NTTab[n].name,viline,33);
  catenate(viline,anwtxt);
  end;
ViBsLg:=0;
initline;
with ViBs[ViBsLg]^ do
  begin
  viline:='(globale Attributierung:)';
  hashind:=99;
  end;
  if NTTab[n].inhAttr = nil
   then begin
         initline;
         keine:=' Inher. :keine';
         keine[0]:=chr(14);
         insert(keine,ViBs[ViBsLg]^.viline,5)
        end;
wrtattrs(NTTab[n].inhAttr);
  if NTTab[n].derAttr = nil
   then begin
         initline;
         keine:=' Derived:keine';
         keine[0]:=chr(14);
         insert(keine,ViBs[ViBsLg]^.viline,5)
        end;
wrtattrs(NTTab[n].derAttr);
initline;
pr:=AG.Prods;
while pr<>0 do
  begin
  with PTab[pr] do
    begin
    if vater<>nil then if vater^.nt=n then
      begin
      initline;
      ViBs[ViBsLg]^.hashind:=100*pr;
      insert(name,ViBs[ViBsLg]^.viline,1);
      insert(vtxt,ViBs[ViBsLg]^.viline,idlaenge+2);
      if vater^.konsistent then catenate(ViBs[ViBsLg]^.viline,ktxt)
      else
	begin
	wrtattrs(vater^.spezInhA);
        if vater^.spezInhA = nil
         then begin
               initline;
               keine:=' Inher. :keine';
               keine[0]:=chr(14);
               insert(keine,ViBs[ViBsLg]^.viline,5)
              end;
        wrtattrs(vater^.spezDerA);
        if vater^.spezDerA = nil
         then begin
               initline;
               keine:=' Derived:keine';
               keine[0]:=chr(14);
               insert(keine,ViBs[ViBsLg]^.viline,5)
              end;
	end;
      initline;
      end;
    s:=soehne; sohnnr:=0;
    while s<>nil do
      begin
      sohnnr:=succ(sohnnr);
      if s^.typ=nont then if s^.nt=n then
	begin
	val(sohnnr,spos);
	if ord(spos[0])=1 then
	  begin
	  stxt[2]:=blk;
	  stxt[3]:=spos[1]
	  end
	else
	  begin
	  stxt[2]:=spos[1];
	  stxt[3]:=spos[2];
	  end;
	initline;
	insert(name,ViBs[ViBsLg]^.viline,1);
	insert(stxt,ViBs[ViBsLg]^.viline,idlaenge+2);
        if s^.konsistent then catenate(ViBs[ViBsLg]^.viline,ktxt)
	else
	  begin
        if s^.spezInhA = nil
         then begin
               initline;
               keine:=' Inher. :keine';
               keine[0]:=chr(14);
               insert(keine,ViBs[ViBsLg]^.viline,5)
              end;
	  wrtattrs(s^.spezInhA);
        if s^.spezDerA = nil
         then begin
               initline;
               keine:=' Derived:keine';
               keine[0]:=chr(14);
               insert(keine,ViBs[ViBsLg]^.viline,5)
              end;
	  wrtattrs(s^.spezDerA);
	  end;
	ViBs[ViBsLg]^.hashind:=100*pr+sohnnr;
	initline;
	end;
      s:=s^.nxt;
      end (*while*);
    end (*with PTab*);
  pr:=PTab[pr].nxt;
  end (*while pr*);
if sw then Seite0;
end (*vsNTinkons*);


procedure vsPinkons(* pr: integer *);
var ha: HAListe;
    Afehl,Sfehl,sw: boolean;
    Afehlzeile,sohnnr,Sfehlzeile,cp: integer;
    uva: AListe;
    s: VokListe;
    stxt,vtxt,spos: Ident;
    sr: SemFktListe;
    apl: ParListe;
    fpl: TypListe;
begin
sw:=aktSeite=0;
Seite1;
stxt:=' des   . Sohnes'; stxt[0]:=chr(14);
vtxt:=' des Vaters'; vtxt[0]:=chr(10);
defunberA(pr);
ViBsLg:=0;
initkontext;
with PTab[pr] do
  begin
  if vater=nil then
    begin
    initline;
    ViBs[ViBsLg]^.viline:='a) Produktion hat keine linke Seite (Vater fehlt)';
    initline;
    end;
  if unversHAttr<>nil then
    begin
    initline;
    ViBs[ViBsLg]^.viline:='b) Folgende Auxiliaries sind unversorgt:';
    ha:=unversHAttr;
    while ha<>nil do
      begin
      initline;
      insert(ATab[ha^.attr].name,ViBs[ViBsLg]^.viline,6);
      ha:=ha^.nxt;
      end;
    initline;
    end;
  initline; Afehl:=false; Afehlzeile:=ViBsLg;
  if vater<>nil then
    begin
    uva:=vater^.unversA;
    while (uva<>nil) do
      begin
      Afehl:=true;
      initline;
      with ViBs[ViBsLg]^ do
	begin
	syminvibs(ViBsLg,rbs.zbreite,ATab[uva^.attr].symbol);
	insert(ATab[uva^.attr].name,viline,3);
	insert(vtxt,viline,idlaenge+4);
	insert(NTTab[vater^.nt].name,viline,idlaenge+19);
	end;
      uva:=uva^.nxt;
      end;
    end;
  s:=soehne; sohnnr:=0;
  while s<>nil do
    begin
    sohnnr:=succ(sohnnr);
    if s^.typ=nont then
      begin
      uva:=s^.unversA;
      while uva<>nil do
	begin
	Afehl:=true;
	initline;
	with ViBs[ViBsLg]^ do
	  begin
	  syminvibs(ViBsLg,rbs.zbreite,ATab[uva^.attr].symbol);
	  insert(ATab[uva^.attr].name,viline,3);
	  insert(stxt,viline,idlaenge+4);
	  val(sohnnr,spos);
	  insert(spos,viline,10-ord(spos[0])+idlaenge);
	  insert(NTTab[s^.nt].name,viline,idlaenge+19);
	  end;
	uva:=uva^.nxt;
	end (*while*);
      end;
    s:=s^.nxt;
    end (*while*);
  if Afehl then
    begin
    ViBs[Afehlzeile]^.viline:='c) Folgende Nonterminal-Attribute sind unversorgt:';
    initline;
    end;
  initline; Sfehl:=false; Sfehlzeile:=ViBsLg;
  sr:=semRegeln;
  while sr<>nil do
    begin
    if sr^.semfkt=IDNT then {null}
    else
      begin
      if not isSFversorgt(sr) then
        begin
        with sr^,SFTab[sr^.semfkt] do
  	  begin
  	  initline;
  	  insert(name,ViBs[ViBsLg]^.viline,2);
  	  ViBs[ViBsLg]^.viline[idlaenge+3]:='(';
  	  cp:=idlaenge+4;
  	  initline;
  	  apl:=quellpar;
  	  fpl:=parlist;
  	  while (apl<>nil) and (fpl<>nil) do
  	    begin
  	    if cp>=mvibsbr-ord(TypTab[fpl^.typ].name[0])-1 then
  	      begin
  	      cp:=idlaenge+4;
  	      initline; initline;
  	      end;
  	    insert(TypTab[fpl^.typ].name,ViBs[pred(ViBsLg)]^.viline,cp);
  	    if (apl^.attr=0) and (apl^.vok=nil) then
  	      begin
  	      Sfehl:=true;
  	      ViBs[ViBsLg]^.viline[cp]:='^';
  	      end;
  	    cp:=succ(cp+ord(TypTab[fpl^.typ].name[0]));
  	    apl:=apl^.nxt;
  	    fpl:=fpl^.nxt;
  	    end;
  	  if (apl<>nil) or (fpl<>nil) then wrtERR1('vsPinkons[1]');
  	  ViBs[pred(ViBsLg)]^.viline[pred(cp)]:=')';
  	  if cp>=mvibsbr-idlaenge-5 then
  	    begin
  	    cp:=idlaenge+3;
  	    initline; initline;
  	    end;
  	  ViBs[pred(ViBsLg)]^.viline[cp]:=':';
          cp:=succ(cp);
  	  apl:=zielpar;
  	  fpl:=erglist;
  	  while (apl<>nil) and (fpl<>nil) do
  	    begin
  	    if cp>=mvibsbr-ord(TypTab[fpl^.typ].name[0])-1 then
  	      begin
  	      cp:=idlaenge+4;
  	      initline; initline;
  	      end;
  	    insert(TypTab[fpl^.typ].name,ViBs[pred(ViBsLg)]^.viline,cp);
  	    if (apl^.attr=0) and (apl^.vok=nil) then
  	      begin
  	      Sfehl:=true; 
  	      ViBs[ViBsLg]^.viline[cp]:='^';
  	      end;
  	    cp:=succ(cp+ord(TypTab[fpl^.typ].name[0]));
  	    apl:=apl^.nxt;
  	    fpl:=fpl^.nxt;
  	    end;
  	  if (apl<>nil) or (fpl<>nil) then wrtERR1('vsPinkons [2]');
  	  end (*with*);
        end (*if not*);
      end;
    sr:=sr^.nxt;
    end (*while sr*);
  if Sfehl then
    begin
    ViBs[Sfehlzeile]^.viline:='d) Folgenden formalen Parametern sind keine aktuellen zugeordnet:';
    initline;
    end;
  if (vater=nil) or (unversHAttr<>nil) or Afehl or Sfehl then
    begin
    ViBs[minvibslg]^.viline:='ES BESTEHEN FOLGENDE INKONSISTENZEN IN PRODUKTION';
    insert(PTab[pr].name,ViBs[minvibslg]^.viline,51);
    end
  else
    begin
    ViBs[minvibslg]^.viline:='ES BESTEHEN KEINE INKONSISTENZEN IN PRODUKTION';
    insert(PTab[pr].name,ViBs[minvibslg]^.viline,48);
    end;
  end (*with PTab*);
if sw then Seite0;
end (*vsPinkons*);


procedure vsallNTinkons;
var nt: integer;
    sw: boolean;
begin
sw:=aktSeite=0;
Seite1;
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(* ZUSAMMENSTELLUNG ALLER INKONSISTENT ATTRIBUTIERTEN NONTERMINALS *)';
nt:=AG.Nonterms;
while nt<>0 do
  begin
  if not isNTkons(nt) then
    begin
    initline;
    with ViBs[ViBsLg]^ do
      begin
      insert(NTTab[nt].name,viline,1);
      hashind:=nt;
      end;
    end;
  nt:=NTTab[nt].nxt;
  end (*while*);
initline;
ViBs[ViBsLg]^.viline:='(******************** ENDE DER ZUSAMMENSTELLUNG *********************)';
initkontext;
ViBs[minvibslg]^.viline:='GENAUERE KONSISTENZINFORMATION DURCH SELEKTION DES ENTSPRECH. NONTERMINALS';
if sw then Seite0;
end (*vsallNTinkons*);


procedure vsallPinkons;
var pr: integer;
    vfehl,Afehl,Sfehl,sw: boolean;
    s: VokListe;
    sr: SemFktListe;
    meldung,vtxt,Atxt,Stxt: vilinetyp;
begin
sw:=aktSeite=0;
Seite1;
vtxt:='Vater fehlt,';
Atxt:='unvers. Attribute,';
Stxt:='unvers. form. Param.';
defallunberA;
ViBsLg:=0;
initline;
ViBs[ViBsLg]^.viline:='(**** Vollstaendige Uebersicht aller inkonsistenten Produktionen ****)';
pr:=AG.Prods;
while pr<>0 do
  begin
  if not isPkons(pr) then
    begin
    with PTab[pr] do
      begin
      vfehl:=vater=nil;
      Afehl:=unversHAttr<>nil;
      if not vfehl then if not Afehl then Afehl:=vater^.unversA<>nil;
      s:=soehne;
      while (s<>nil) and (not Afehl) do
	begin
	Afehl:=s^.unversA<>nil;
	s:=s^.nxt;
	end;
      Sfehl:=false;
      sr:=semRegeln;
      while (sr<>nil) and (not Sfehl) do
	begin
	sr^.versorgt:=isSFversorgt(sr);
	Sfehl:=not sr^.versorgt;
	sr:=sr^.nxt;
	end;
      meldung:='  ';
      insert(name,meldung,1);
      meldung[idlaenge+1]:=':';
      if vfehl then catenate(meldung,vtxt);
      if Afehl then catenate(meldung,Atxt);
      if Sfehl then catenate(meldung,Stxt);
      initline;
      with ViBs[ViBsLg]^ do
	begin
	viline:=meldung; hashind:=pr
	end;
      end (*with*);
    end;
  pr:=PTab[pr].nxt;
  end (*while*);
initline;
ViBs[ViBsLg]^.viline:='(********************* ENDE DER UEBERSICHT **************************)';
initkontext;
ViBs[minvibslg]^.viline:='GENAUERE KONSISTENZINFORMATION DURCH SELEKTION DER ENTSPRECH. PRODUKTION';
if sw then Seite0;
end (*vsallPinkons*);


procedure vsAGkons;
const oRand=7;
var NTkons, Pkons, AGkons, istIdent, clrscreen, sw: boolean;
    c: char;
    dienst, maxdienst, xpos, prnr, ntnr, zeile, index: integer;
    ax, prn, ntn, s: Ident;

  procedure wrtnm (var s: Ident);
  begin
  if ord(s[0])<>0 then wrtIdent(s) else gpr_$text('<bisher undefiniert>',20,status);
  end;

  function yy(n: integer): integer;
  begin
  with rbs do yy:=yhome-(oRand+n)*zhoehe;
  end;

  procedure bsmask;
  begin
  with rbs do
    begin
    clearscreen;
    setCursor(yy(0),0);
    gpr_$text(' Konsistenz (& Vollstaendigkeits) -Checkliste der Grammatik:',60,status);
    male4eck(false,yy(0)-3,yy(0)-5,0,xpixels);
    setCursor(yy(2),0);
    gpr_$text(' a) Phasen_id',13,status); setCursor(yy(2),xpos); wrtnm(AG.PhasenId);
    setCursor(yy(3),0);
    gpr_$text(' b) ein_gram_id',15,status); setCursor(yy(3),xpos); wrtnm(AG.InGName);
    setCursor(yy(4),0);
    gpr_$text(' c) aus_gram_id',15,status); setCursor(yy(4),xpos); wrtnm(AG.OutGName);
    setCursor(yy(5),0);
    gpr_$text(' d) Axiom',9,status); setCursor(yy(5),xpos);
    if AG.Axiom<=0 then gpr_$text('<bisher undefiniert>',20,status) else wrtIdent(NTTab[AG.Axiom].name);
    setCursor(yy(6),0); gpr_$text(' e) Produktionen:',16,status);
    setCursor(yy(6),xpos);
    if not Pkons then gpr_$text('nicht ',6,status);
    gpr_$text('konsistent!',11,status);
    setCursor(yy(7),0); gpr_$text(' f) Nonterminals:',17,status);
    setCursor(yy(7),xpos);
    if NTkons then gpr_$text('konsistent ',11,status) else gpr_$text('inkonsistent ',13,status);
    gpr_$text('attributiert!',13,status);
    setCursor(yy(9),0);
    gpr_$text(' Grammatikstatus:',17,status);
    setCursor(yy(9),xpos);
    if AG.Konsistent then gpr_$text('i.O.',4,status) else gpr_$text('unvollstaendig bzw. inkonsistent',32,status);
    male4eck(false,yy(10)+6,yy(10)+5,0,xpixels);
    setCursor(yy(12),0);
    gpr_$text(' Auswahlmoeglichkeiten:',23,status); 
    newline;
    newline;
    gpr_$text('    PhasenId aendern',20,status);
    newline;
    gpr_$text('    InGName aendern',19,status);
    newline;
    gpr_$text('    OutGName aendern',20,status);
    newline;
    gpr_$text('    Axiom aendern',17,status);
    newline;
    if not Pkons
      then begin
	   gpr_$text('    Info ueber inkons. Produktionen',35,status);
	   newline
	   end;
    if not NTkons
      then begin
	   gpr_$text('    Info ueber inkons. attribut. Nonterminals',45,status);
	   newline
	   end;
    gpr_$text('    Zurueck',11,status);
    newline;
    end;
  end (*bsmask*);

begin (*vsAGkons*)
sw:=aktSeite=0;
Seite1;
xpos:=20*rbs.zbreite;
checkPs;
Pkons:=sindPkons;
NTkons:=sindNTkons;
AG.Konsistent:=isAGkons;
clearscreen;
bsmask;
maxdienst := 4;
if not Pkons then maxdienst := maxdienst + 1;
if not NTkons then maxdienst := maxdienst + 1;
dienst := 0;
repeat
  setCursor(yy(20),0);                   
  repeat
   invertBild(3*rbs.zbreite,yy(14)-rbs.zhoehe*dienst-4,42*rbs.zbreite,rbs.zhoehe);
   move_read(c);
   invertBild(3*rbs.zbreite,yy(14)-rbs.zhoehe*dienst-4,42*rbs.zbreite,rbs.zhoehe);
   case c of
    '8': if dienst > 0 then dienst := pred(dienst);
    '2': if dienst < maxdienst then dienst := succ(dienst);
   end; (* case *)
   if c = '0' then dienst := -1;
  until (c = trz) or (c = '0');
  case dienst of
    0,1,2:
      begin
      zeile:= dienst+2;
      male4eck(true,pred(yy(pred(zeile))),yy(zeile),xpos,rbs.xpixels);
      s[0]:=chr(0);
      editname(yy(zeile),xpos,noList,s);
      if isIdent(s) then
	begin
	if ord(s[0])>4 then meldefehler(32)
	else
	  begin
	  case dienst of
	    0: AG.PhasenId:=s;
	    1: AG.InGName:=s;
	    2: AG.OutGName:=s;
	    end (*case*);
	  AGkons:=isAGkons;
	  if AGkons<>AG.Konsistent then
	    begin
	    AG.Konsistent:=AGkons;
	    male4eck(true,yy(9),pred(yy(8)),xpos,rbs.xpixels);
	    setCursor(yy(9),xpos);
	    if AG.Konsistent then gpr_$text('i.O.',4,status)
	    else gpr_$text('inkonsistent/unvollstaendig',27,status);
	    end;
	  end (*else*);
	end (*if isIdent*)
      else
	begin
	if ord(s[0])<>0 then meldefehler(1)
	end;
      male4eck(true,pred(yy(pred(zeile))),yy(zeile),xpos,rbs.xpixels);
      setCursor(yy(zeile),xpos);
      case dienst of
	0: wrtnm(AG.PhasenId);
	1: wrtnm(AG.InGName);
	2: wrtnm(AG.OutGName);
	end (*case*);
      end;
    3:
      begin
      male4eck(true,pred(yy(4)),yy(5),xpos,rbs.xpixels);
      istIdent:=false;
      lkup(yy(5),xpos,nontHL,rdorwrt,istIdent,ax,index,clrscreen);
      if istIdent then
	begin
	AG.Axiom:=index;
	AG.Konsistent:=isAGkons;
	end
      else
	begin
	if ord(ax[0])<>0 then meldefehler(1);
	end;
      bsmask;
      end;
    4,5:
      begin
      if (not Pkons) and (dienst = 4) then
	begin
	vsallPinkons;
	istIdent:=false; prn[0]:=chr(0);
	evibs(istIdent,prodHL,redonly,prn,prnr);
	if prnr>0 then 
	  begin
	  vsPinkons(prnr);
	  istIdent:=false; prn[0]:=chr(0);
	  evibs(istIdent,noList,seeonly,prn,prnr);
	  end;
	end
      else if (not NTkons and Pkons and (dienst = 4)) or (not Ntkons and not Pkons and (dienst = 5)) then
	begin
	vsallNTinkons;
	istIdent:=false; ntn[0]:=chr(0);
	evibs(istIdent,nontHL,redonly,ntn,ntnr);
	if ntnr>0 then
	  begin
	  vsNTinkons(ntnr);
	  istIdent:=false; ntn[0]:=chr(0);
	  evibs(istIdent,prodHL,seeonly,ntn,ntnr);
	  end;
	end
      else dienst := -1;
      bsmask;
      end;
    6: dienst := -1;
    otherwise;
    end (*case*);
  ;
until (dienst = -1);
if sw then Seite0;
end (*vsAGkons*);
