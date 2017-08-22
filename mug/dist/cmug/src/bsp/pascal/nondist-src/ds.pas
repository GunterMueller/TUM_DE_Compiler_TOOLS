






procedure loescheParVersorgung (* var sf: SemFktListe; var par: ParListe; zielpar: boolean *);
begin     
gpr_$set_draw_value(-2,status);
if sf^.semfkt <> IDNT
 then 
  if SFTab[sf^.semfkt].issynfkt
   then zeichneParVersSynfkt(sf, par, zielpar )
   else zeichneParVersorgung( sf, par, zielpar )
 else zeichneParVersorgung( sf, par, zielpar );
gpr_$set_draw_value(color_base,status);
entkopple(sf,par);
end;   {loescheParVersorgung}

procedure lspmbdgNTAl(* pr,a: integer; ntv: VokListe *);
var sr,srnext: SemFktListe;
    ap: ParListe;
    b: boolean;
    proc: filename;
begin
proc:='lspmbdgNTAl';
if (pr<=0) or (a<=0) or (ntv=nil) then wrtERR2(proc,'[1]')
else if (ntv^.typ<>nont) or (ATab[a].art=aux) then wrtERR2(proc,'[2]')
else
  begin
  sr:=PTab[pr].semRegeln;
  while sr<>nil do
    begin
    ap:=sr^.quellpar;
    for b:=true downto false do
      begin
      while ap<>nil do
	begin
	if ap^.vok=ntv then if ap^.attr=a then entkopple(sr,ap);
	ap:=ap^.nxt;
	end;
      ap:=sr^.zielpar;
      end (*for*);
    srnext:=sr^.nxt;
    if not hatSFerg(sr) then gibfreiSF(pr,sr);
    sr:=srnext;
    end (*while*);
  end
end (*lspmbdgNTAl*);


procedure lspmbdgVl(* pr: integer; v: VokListe *);
var sr, srnext: SemFktListe;
    pl: ParListe;
    b: boolean;
begin
if (pr<=0) or (v=nil) then wrtERR1('lspmbdgVl')
else
  begin
  sr:=PTab[pr].semRegeln;
  while sr<>nil do
    begin
    pl:=sr^.quellpar;
    for b:=false to true do
      begin
      while pl<>nil do
	begin
	if pl^.vok=v then 
	  begin 
	  if pr=aktPNr then 
            begin
	    if sr^.semfkt = IDNT then loescheParVersorgung(sr,sr^.zielpar,true) 
	    else loescheParVersorgung(sr,pl,b) 
	    end
	  else entkopple(sr,pl);
	  end;
	pl:=pl^.nxt;
	end;
      pl:=sr^.zielpar;
      end (*for*);
    srnext:=sr^.nxt;
    if not hatSFerg(sr) then gibfreiSF(pr,sr);
    sr:=srnext;
    end (*while*);
  end;
end (*lspmbdgVl*);


procedure lspmbdgNTAg(* a: integer; nt: integer *);
var ppr: AListe;
    pr: integer;
    s: VokListe;
begin
if ATab[a].art=aux then wrtERR1('lspmbdgNTAg')
else
  begin
  ppr:=inPvorkommen(NTTab[nt].anwendungen);
  while ppr<>nil do
    begin
    pr:=ppr^.attr;
    ppr:=ppr^.nxt;
    with PTab[pr] do
      begin
      if vater<>nil then if vater^.nt=nt then lspmbdgNTAl(pr,a,vater);
      s:=soehne;
      while s<>nil do
	begin
	if s^.typ=nont then if s^.nt=nt then lspmbdgNTAl(pr,a,s);
	s:=s^.nxt;
	end;
      end;
    end;
  end;
end (*lspmbdgNTAg*);


procedure lspmbdgNTg(* nt: integer *);
var ppr: AListe;
    pr: integer;
    s: VokListe;
begin
ppr:=inPvorkommen(NTTab[nt].anwendungen);
while ppr<>nil do
  begin
  pr:=ppr^.attr;
  ppr:=ppr^.nxt;
  with PTab[pr] do
    begin
    if vater<>nil then if vater^.nt=nt then lspmbdgVl(pr,vater);
    s:=soehne;
    while s<>nil do
      begin
      if s^.typ=nont then if s^.nt=nt then lspmbdgVl(pr,s);
      s:=s^.nxt;
      end (*while*);
    end (*with*);
  end (*while*);
end (*lspmbdgNTg*);


procedure lspmbdgTg(* t: integer *);
var ppr: AListe;
    pr: integer;
    s: VokListe;
begin
ppr:=inPvorkommen(TTab[t].anwendungen);
while ppr<>nil do
  begin
  pr:=ppr^.attr;
  ppr:=ppr^.nxt;
  with PTab[pr] do
    begin
    s:=soehne;
    while s<>nil do
      begin
      if s^.typ=term then if s^.t=t then lspmbdgVl(pr,s);
      s:=s^.nxt;
      end;
    end;
  end;
end (*lspmbdgTg*);


procedure aAzuNTl(* a,pos: integer; var ntv: VokListe; var aegrafik: boolean *);
var apos: integer;
    neu: boolean;
    proc: filename;
begin
apos:=abs(pos); proc:='aAzuNTl';
if (a=0) or (pos=0) or (ntv=nil) then wrtERR2(proc,'[1]')
else if ntv^.typ<>nont then wrtERR2(proc,'[2]')
else
  begin
  expandntv(ntv);
  if ATab[a].art=inh then aAzuAL(a,apos,ntv^.spezInhA,neu) else aAzuAL(a,apos,ntv^.spezDerA,neu);
  if (apos=0) and (not neu) then meldefehler(24);
  aegrafik:= (apos>0) and neu;
  comprntv(ntv);
  end;
end (*aAzuNTl*);


procedure aAzNTg(* a,nt: integer; var pos: integer *);
var neu: boolean;
    pr: integer;
    s: VokListe;
    vk: AListe;


  procedure fAzNT(globneu: boolean; a,pr: integer; var vk: VokListe);
  (* Annahme: 
     Attribut a ist bereits in globaler Attributierung enthalten *)
  var 
      pos: integer;
      neu, spezA: boolean;
  begin (*fAzNT*)
  with ATab[a],NTTab[vk^.nt],vk^ do
    begin
    if globneu then
      begin
      if vk^.konsistent then
        begin
        if ((art=der) and (PTab[pr].vater=vk)) or ((art=inh) and (PTab[pr].vater<>vk)) then PTab[pr].konsistent:=false;
        pos:=0;
        if art=inh then if spezInhA<>nil then aAzuAL(a,pos,spezInhA,neu)
				         else (*skip*)
		   else if spezDerA<>nil then aAzuAL(a,pos,spezDerA,neu)
				         else (*skip*);
        end
      else
        begin
        if art=inh then spezA:=isAelemAL(a,spezInhA) else spezA:=isAelemAL(a,spezDerA);
        if spezA then
	  begin
	  vk^.konsistent:=isgleichattr(inhAttr,spezInhA) and isgleichattr(derAttr,spezDerA);
	  if vk^.konsistent then
	    begin
	    if sameAorder(inhAttr,spezInhA) then gibALzurueck(spezInhA);
	    if sameAorder(derAttr,spezDerA) then gibALzurueck(spezDerA);
	    end;
	  end
        else
	  begin
	  if ((art=der) and (PTab[pr].vater=vk)) or ((art=inh) and (PTab[pr].vater<>vk)) then PTab[pr].konsistent:=false;
	  pos:=0;
	  if art=inh then aAzuAL(a,pos,spezInhA,neu) else aAzuAL(a,pos,spezDerA,neu);
	  end
        end
      end (*if globneu*)
    else
      begin
      if not vk^.konsistent then
        begin
        if art=inh then spezA:=isAelemAL(a,spezInhA) else spezA:=isAelemAL(a,spezDerA);
        if not spezA then
	  begin
	  if ((art=der) and (PTab[pr].vater=vk)) or ((art=inh) and (PTab[pr].vater<>vk)) then PTab[pr].konsistent:=false;
	  pos:=0;
	  if art=inh then aAzuAL(a,pos,spezInhA,neu) else aAzuAL(a,pos,spezDerA,neu);
	  if isgleichattr(inhAttr,spezInhA) and isgleichattr(derAttr,spezDerA) then
	    begin
	    vk^.konsistent:=true;
	    if sameAorderR(a,inhAttr,spezInhA) then gibALzurueck(spezInhA);
	    if sameAorderR(a,derAttr,spezDerA) then gibALzurueck(spezDerA);
	    end;
	  end;
        end;
      end; (*else globneu*)
    end (*with*)
  end (*fAzNT*);

begin (*aAzNTg*)
with ATab[a],NTTab[nt] do
  begin
  if art=inh then aAzuAL(a,pos,inhAttr,neu) else aAzuAL(a,pos,derAttr,neu);
  if pos<1 then if neu then pos:=-1 else pos:=-2 
  else
    begin
    vk:=inPvorkommen(anwendungen);
    while vk<>nil do
      begin
      pr:=vk^.attr; vk:=vk^.nxt;
      with PTab[pr] do
	begin
	if vater<>nil then if vater^.nt=nt then fAzNT(neu,a,pr,vater);
	s:=soehne;
	while s<>nil do
	  begin
	  if s^.typ=nont then if s^.nt=nt then fAzNT(neu,a,pr,s);
	  s:=s^.nxt;
	  end;
	end;
      end;
    end;
  end;
end (*aAzNTg*);


procedure sAausNTl(* pr,a: integer; ntv: VokListe; var aegrafik: boolean *);
var pos: integer;
begin
if (a<=0) or (ntv=nil) then wrtERR1('sAausNTl[1]')
else if (ntv^.typ<>nont) then wrtERR1('sAausNTl[2]')
else
  begin
  expandntv(ntv);
  if ATab[a].art=inh then sAausAL(a,ntv^.spezInhA,pos) else sAausAL(a,ntv^.spezDerA,pos);
  aegrafik:= (pos>0);
  if pos>0 then lspmbdgNTAl(pr,a,ntv);
  comprntv(ntv);
  end;
end (* sAausNTl *);


procedure sAaNTg(* a,nt: integer *);
var warglob: boolean;
    pos,pr: integer;
    vk: AListe;
    s: VokListe;

  procedure sAaNT(warglob: boolean; a: integer; var ntv: VokListe);
  var pos: integer;
      spezA: boolean;
    
  begin 
  with ATab[a],NTTab[ntv^.nt],ntv^ do
    begin
    if warglob then
      begin
      if ntv^.konsistent then
        begin
        if art=inh then if spezInhA<>nil then sAausAL(a,spezInhA,pos) else (*skip*)
		   else if spezDerA<>nil then sAausAL(a,spezDerA,pos) else (*skip*);
        end
      else
        begin
        if art=inh then spezA:=isAelemAL(a,spezInhA) else spezA:=isAelemAL(a,spezDerA);
        if spezA then
	  begin
	  if art=inh then sAausAL(a,spezInhA,pos) else sAausAL(a,spezDerA,pos);
	  end
        else
	  begin
	  ntv^.konsistent:=isgleichattr(inhAttr,spezInhA) and isgleichattr(derAttr,spezDerA);
	  if ntv^.konsistent then
	    begin
	    if sameAorder(inhAttr,spezInhA) then gibALzurueck(spezInhA);
	    if sameAorder(derAttr,spezDerA) then gibALzurueck(spezDerA);
	    end;
	  end;
        end;
      end
    else (* not warglob*)
      begin
      if ntv^.konsistent then (*skip*)
      else
        begin
        if art=inh then spezA:=isAelemAL(a,spezInhA) else spezA:=isAelemAL(a,spezDerA);
        if spezA then
	  begin
	  if art=inh then sAausAL(a,spezInhA,pos) else sAausAL(a,spezDerA,pos);
	  ntv^.konsistent:=isgleichattr(inhAttr,spezInhA) and isgleichattr(derAttr,spezDerA);
	  if ntv^.konsistent then
	    begin
	    if sameAorder(inhAttr,spezInhA) then gibALzurueck(spezInhA);
	    if sameAorder(derAttr,spezDerA) then gibALzurueck(spezDerA);
	    end;
	  end;
        end;
      end;
    end; (*with*)
  end (*sAaNT*);

begin (*sAaNTg*)
with ATab[a],NTTab[nt] do
  begin
  if art=inh then sAausAL(a,inhAttr,pos) else sAausAL(a,derAttr,pos);
  warglob:= pos>0;
  lspmbdgNTAg(a,nt);
  vk:=inPvorkommen(anwendungen);
  while vk<>nil do
    begin
    pr:=vk^.attr;
    vk:=vk^.nxt;
    with PTab[pr] do
      begin
      if vater<>nil then if vater^.nt=nt then sAaNT(warglob,a,vater);
      s:=soehne;
      while s<>nil do
	begin
	if s^.typ=nont then if s^.nt=nt then sAaNT(warglob,a,s);
	s:=s^.nxt;
	end;
      end;
    end; (*while vk*)
  end; (*with*)
end; (*sAaNTg*)


procedure aeAart(* a: integer; r: Richtung *);
var nt,pr: integer;
begin
if ATab[a].art<>r then
  begin
  liberA(a);
  if ATab[a].art=aux then
    begin
    pr:=AG.Prods;
    while pr<>0 do
      begin
      sHAausP(a,pr);
      pr:=PTab[pr].nxt;
      end
    end
  else
    begin
    nt:=AG.Nonterms;
    while nt<>0 do
      begin
      sAaNTg(a,nt);
      nt:=NTTab[nt].nxt;
      end;
    end;
  ATab[a].art:=r;
  end;
end (*aeAart*);


procedure sVaP(* pr: integer; v: VokListe *);
begin
if (pr<=0) or (v=nil) then wrtERR1('sVaP')
else
  begin
  lspmbdgVl(pr,v);
  gibfreiV(pr,v);
  end;
end (*sVaP*);


procedure sVausPp(* pr: integer; var pos: integer *);
var s: VokListe;
    i: integer;
begin
with PTab[pr] do
  begin
  if pos=0 then sVaP(pr,vater)
  else
    begin
    if soehne=nil then pos:=-999 (*fehler*)
    else
      begin
      s:=soehne; i:=1;
      while (s^.nxt<>nil) and (i<pos) do
	begin
	i:=succ(i);
	s:=s^.nxt;
	end;
      if i<pos then pos:=-pos (*fehler*)
      else sVaP(pr,s);
      end
    end;
  end;
end (*sVausPp*);


procedure ergPumVp(* pr,v: integer; hl: HashListen; var pos: integer *);
var vok,s,salt: VokListe;
    i: integer;
begin
with PTab[pr] do
  begin
  if pos=0 then
    begin
    if (vater<>nil) or (hl<>nontHL) then pos:=ERR (*fehler*)
    else
      begin
      beschaffeV(vok);
      with vok^ do
	begin
	typ:=nont;
	nxt:=soehne;
	end;
      vater:=vok;
      end
    end
  else
    begin (*pos>0*)
    if pos=1 then
      begin
      beschaffeV(vok);
      if hl=nontHL then
	begin
	vok^.typ:=nont;
	with vok^ do
	  begin
	  nxt:=soehne;
	  if vater<>nil then vater^.nxt:=vok;
	  soehne:=vok;
	  end
	end
      else
	begin
	vok^.typ:=term;
	with vok^ do
	  begin
	  nxt:=soehne;
	  if vater<>nil then vater^.nxt:=vok;
	  soehne:=vok;
	  end;
	end;
      end
    else
      begin (*pos>1*)
      if soehne=nil then pos:=ERR
      else
	begin
	s:=soehne; i:=1; salt:=nil;
	while (s^.nxt<>nil) and (i<pos) do
	  begin
	  i:=succ(i); salt:=s;
	  s:=s^.nxt;
	  end;
	if pos>succ(i) then pos:=-succ(i)
	else
	  begin
	  beschaffeV(vok);
	  if hl=nontHL then vok^.typ:=nont else vok^.typ:=term;
	  if pos>i then 
	    begin
	    s^.nxt:=vok;
	    vok^.nxt:=nil;
	    end
	  else
	    begin
	    vok^.nxt:=s;
	    salt^.nxt:=vok;
	    end;
	  end
	end
      end (*pos>1*)
    end (*pos>0*)
  end (*with*);
if pos>=0 then
  begin
  with vok^ do
    begin
    if hl=nontHL then
      begin
      nt:=v; spezInhA:=nil; spezDerA:=nil; vok^.konsistent:=true;
      Y:= -rbs.R1-1;
      aPzuPL(pr,NTTab[v].anwendungen);
      end
    else
      begin
      t:=v;
      aPzuPL(pr,TTab[v].anwendungen);
      end;
    end (*with*);
  end;
end (*ergPumVp*);


procedure ersVinPp(* pr,v: integer; hl: HashListen; var pos: integer *);
var s: VokListe;
    anzsoehne: integer;
begin
with PTab[pr] do
  begin
  if pos=0 then
    begin
    if vater<>nil then sVausPp(pr,pos);
    ergPumVp(pr,v,hl,pos);
    end
  else
    begin
    s:=soehne; anzsoehne:=0;
    while s<>nil do
      begin
      anzsoehne:=succ(anzsoehne);
      s:=s^.nxt;
      end;
    if pos>anzsoehne then pos:=-pos (*fehler*)
    else
      begin
      sVausPp(pr,pos);
      ergPumVp(pr,v,hl,pos);
      end
    end
  end
end (*ersVinPp*);


procedure loescheSFl(* pr: integer; var sefu: SemFktListe *);
var pl: ParListe;
    isinpar: boolean;
begin
pl:=sefu^.quellpar;
for isinpar:=true downto false do
  begin
  while pl<>nil do
    begin
    entkopple(sefu,pl);
    pl:=pl^.nxt;
    end;
  pl:=sefu^.zielpar;
  end (*for*);
gibfreiSF(pr,sefu);
end;


procedure loescheSFg(*sf: integer*);
var pr: integer;
    ppr: AListe;
    sr, srnext: SemFktListe;
begin
ppr:=inPvorkommen(SFTab[sf].anwendungen);
while ppr<>nil do
  begin
  pr:=ppr^.attr;
  ppr:=ppr^.nxt;
  with PTab[pr] do
    begin
    sr:=semRegeln;
    while sr<>nil do
      begin
      srnext:=sr^.nxt;
      if sr^.semfkt=sf then loescheSFl(pr,sr);
      sr:=srnext;
      end;
    end (*with*);
  end (*while ppr*);
lexaushaengen (sfktHL, sf);
with SFTab[sf] do
  begin
  name[0]:= chr(0);
  name[1]:=trz
  end;
end (*loescheSFg*);


procedure loescheNT(*nt: integer*);
var ppr: AListe;
    pr: integer;
    s, snext: VokListe;
begin
lspmbdgNTg(nt);
ppr:=inPvorkommen(NTTab[nt].anwendungen);
while ppr<>nil do
  begin
  pr:=ppr^.attr;
  ppr:=ppr^.nxt;
  with PTab[pr] do
    begin
    if vater<>nil then if vater^.nt=nt then gibfreiV(pr,vater);
    s:=soehne;
    while s<>nil do
      begin snext:=s^.nxt;
      if s^.typ=nont then if s^.nt=nt then gibfreiV(pr,s);
      s:=snext;
      end (*while*);
    end (*with PTab*);
  end (*while ppr*);
lexaushaengen(nontHL,nt);
with NTTab[nt] do
  begin
  name[1]:=trz;
  name[0]:=chr(0);
  end;
end (*loescheNT*);


procedure loescheT(*t: integer*);
var ppr: AListe;
    pr: integer;
    s, snext: VokListe;
begin
lspmbdgTg(t);
ppr:=inPvorkommen(TTab[t].anwendungen);
while ppr<>nil do
  begin
  pr:=ppr^.attr;
  ppr:=ppr^.nxt;
  with PTab[pr] do
    begin
    s:=soehne;
    while s<>nil do
      begin snext:=s^.nxt;
      if s^.typ=term then if s^.t=t then gibfreiV(pr,s);
      s:=s^.nxt;
      end;
    end (*with*);
  end (*while ppr*);
lexaushaengen(termHL,t);
with TTab[t] do
  begin
  name[0]:=chr(0);
  name[1]:=trz;
  end;
end (*loescheT*);


procedure loescheA(*a: integer*);
var nt: integer;
begin
if ATab[a].art=aux then liberA(a) 
else
  begin
  nt:=AG.Nonterms;
  while nt<>0 do
    begin
    sAaNTg(a,nt);
    nt:=NTTab[nt].nxt;
    end;
  end;
lexaushaengen(attrHL,a);
if ATab[a].symbol <> 0
 then with ASymb do gebund:=gebund-[ATab[a].symbol];
with ATab[a] do
  begin
  name[0]:=chr(0);
  name[1]:=trz;
  end;
end (*loescheA*);


procedure loescheP(*pr: integer*);
var sr,srnext: SemFktListe;
    ap: ParListe;
    i: integer;
    s,snext: VokListe;
begin
with PTab[pr] do
  begin
  sr:=semRegeln;
  while sr<>nil do
    begin
    ap:=sr^.quellpar;
    for i:=0 to 1 do
      begin
      while ap<>nil do
	begin
        entkopple(sr,ap);
        ap:=ap^.nxt;
        end;
      ap:=sr^.zielpar;
      end (*for*);
    srnext:=sr^.nxt;
    gibfreiSF(pr,sr);
    sr:=srnext;
    end (*while sr*);
  gibHALzurueck(hilfsAttr);
  gibHALzurueck(unversHAttr);
  if vater<>nil then gibfreiV(pr,vater);
  s:=soehne;
  while s<>nil do
    begin
    snext:=s^.nxt;
    gibfreiV(pr,s);
    s:=snext;
    end;
  end (*with PTab*);
lexaushaengen(prodHL,pr);
with PTab[pr] do
  begin
  name[1]:=trz;
  name[0]:=chr(0);
  end;
end (*loescheP*);


procedure defptp(* var n: Ident; var nind: integer *);
begin
TypTab[nind].name:=n;
lexeinhaengen(typeHL,nind);
end (*defptp*);



procedure defSF(* sf: integer; var sfname: Ident *);
const linksrand=10;
var md: MaskenDaten;
    y,x,yalt,xalt: integer;
    sw,noparms: boolean;
    antwort:char;

  procedure setcursor1(y,x: integer);
  begin
  setCursor(y,x*rbs.zbreite+linksrand);
  end;

  procedure rdpar(var anker: TypListe; iszielpar:boolean);
  label 125;
  var ende,ex: boolean;
      typindex,fpo: integer;
      tl, tl1: TypListe;
      typid: Ident;
  begin
  ende:=false;
  repeat
    if x>=77 -idlaenge then
      begin
      yalt:=y; y:=y-rbs.zhoehe; xalt:=x; x:=idlaenge+3;
      end;
125:typid[0]:=chr(0);
    editname(y,x*rbs.zbreite+linksrand,typeHL,typid);
    male4eck(true,md.yinput-2*md.azh,md.yinput-rbs.zhoehe-1,md.xinput,rbs.xpixels);
    if isIdent(typid) then
      begin
      fpo:=formpraefixop(typid[ord(typid[0])]);
      if fpo>0 then
	begin
	evibs2(false,false,typeHL,rdorwrt,typid,typindex);
	evibsD.prtreq:=false;
	if typindex<>ERR then
	  begin
	  if typindex=-1 then
	    begin
	    setCursor(md.yinput-2*md.azh,md.xinput);
	    gpr_$text('Wie soll der neue form. Parameter heissen? ',43,status);
	    goto 125;
	    end
	  else
	    begin
	    loeschewort(y,x*rbs.zbreite+linksrand,idlaenge);
	    wrtIdent(typid);
	    end
	  end
	else goto 125;
	end
      else
	begin
	hash(typeHL,typid,typindex,ex);
	if not ex then 
	  begin
	  TypTab[typindex].name:=typid;
	  lexeinhaengen(typeHL,typindex);
	  vsptp(rdorwrt);
	  evibsD.prtreq:=true;
	  end;
        end
      end
    else
      begin
      if ord(typid[0])=0 then ende:=true
      else
	begin
	meldefehler(5);
	loeschewort(y,x*rbs.zbreite,idlaenge);
	goto 125;
	end;
      end;
    if not ende then
      begin
      beschaffeTyp(tl1); tl1^.typ:=typindex; tl1^.nxt:=nil;
      if anker=nil then anker:=tl1 else tl^.nxt:=tl1;
      tl:=tl1; x:=x+ord(typid[0]); gpr_$text(',',1,status); x:=x+2;
      if iszielpar and (SFTab[sf].issynfkt) and (anker <> nil)
       then ende:=true; 
      end;
  until ende;
  end (*rdpar*);

begin (*defSF*)
sw:=aktSeite=0;
Seite1;
with SFTab[sf] do
  begin
  name:=sfname;
  erglist:=nil;
  parlist:=nil;
  anwendungen:=nil;
  end;
lexeinhaengen(sfktHL,sf);
defmaske(sfktHL,0,md);
initevibsD(3,md.ystern-14*md.azh,md.azh);
clearscreen;
evibsD.prtreq:=true;
SFmaske(true,md,sfname);
vsptp(rdorwrt);
meldung(59);
antworte(semsyn,antwort);
SFTab[sf].issynfkt := (antwort = 'Y');
clearmeldung;
setCursor(md.yinput,md.xinput);
gpr_$text('Bitte Typnamen der form. Eing.-Parameter angeben.',49,status);
newline;
gpr_$text('  (Trennzeichen= RETURN, Abbruch= leere Eingabe)',48,status);
y:=md.ystern-6*md.azh; x:=0; yalt:=y; xalt:=idlaenge+5;
setcursor1(y,x); wrtIdent(sfname); gpr_$text(':',1,status);
x:=idlaenge+2; setcursor1(y,x); gpr_$text('(',1,status); x:=succ(x);
rdpar(SFTab[sf].parlist,false);
if x=idlaenge+3 then begin y:=yalt; x:=xalt end;
x:=x-2; loeschewort(y,x*rbs.zbreite+linksrand,2);
gpr_$text('):',2,status); x:=x+3;
loescheeingabefeld(md);
gpr_$text('Bitte Typnamen der form. Ausgabeparameter angeben.',50,status);
repeat
  rdpar(SFTab[sf].erglist,true); noparms:=SFTab[sf].erglist=nil;
  if noparms then meldefehler(42);
until not noparms;
if sw then Seite0;
end (*defSF*);


procedure waehledienst1(anzd,ypos:integer; md:MaskenDaten; var dienst:integer);
var x0,dx,y: integer;
    c: char;
begin 
loescheeingabefeld(md);
gpr_$text('Bitte waehlen Sie [Cursor] ',27,status);
dienst:=1;
repeat
  if (anzd=2) or (anzd=4)
  then begin if (dienst mod 2)=0
             then x0:=rbs.xpixels div 2 + 1
             else x0:=md.rand + 1;
             dx:=(rbs.xpixels-2*md.rand) div 2;
             if dienst>2
             then y:=ypos-md.azh-7
             else y:=ypos-1;
       end
  else begin dx:=(rbs.xpixels div 3)-md.rand+1;
             if (dienst mod 3)=0
             then x0:=(rbs.xpixels div 3)*2+2
             else if (dienst=2) or (dienst=5)
                  then begin
                    x0:=rbs.xpixels div 3+1;
                    dx:=dx+md.rand end
                  else begin
                    x0:=md.rand+1;
                    dx:=dx-1 end; 
             if dienst>3
             then y:=ypos-md.azh-7
             else y:=ypos-1;
       end;
  invertBild(x0,y,dx-1,md.azh+5);
  repeat move_read(c) until c in ['0','2','4','6','8',trz]; 
  invertBild(x0,y,dx-1,md.azh+5);
  case c of
    '0': dienst:=0;
    '2': if anzd>3 
         then if dienst <= (anzd div 2) 
              then dienst := dienst + (anzd div 2);
    '8': if anzd>3
         then if dienst > (anzd div 2)
              then dienst := dienst - (anzd div 2);
    '4': if dienst>1 then dienst:=pred(dienst);
    '6': if dienst<anzd then dienst:=succ(dienst);
    trz: ; 
    otherwise;
    end (*case*);
  ;
until (c='0') or (c=trz);
end (*waehledienst1*);




procedure aeP(* pr: integer *);
var md: MaskenDaten;
    y0,dienst,pos,i: integer;
    geladen,listreq: HashListen;
    NTneudefs,Tneudefs: AListe;
    vokfrage,neuelmtfrage: array [HashListen] of array [1..48] of char;
    modus: char;
    sw: boolean;

  procedure umbenennen;
  label 108;
  var pr2name: Ident;
      y,x,fpo,pr2: integer;
      ex: boolean;

    procedure Pumbenennen;
    var nt,t,sf: integer;
        vk: PListe;
    begin
    PTab[pr2]:=PTab[pr];
    PTab[pr2].name:=pr2name;
    lexaushaengen(prodHL,pr);
    lexeinhaengen(prodHL,pr2);
    PTab[pr].name[0]:=chr(0);
    nt:=AG.Nonterms;
    while nt<>0 do
      begin
      vk:=NTTab[nt].anwendungen;
      while vk<>nil do
        begin
        if vk^.prod=pr then vk^.prod:=pr2;
        vk:=vk^.nxt;
        end;
      nt:=NTTab[nt].nxt;
      end;
    t:=AG.Terms;
    while t<>0 do
      begin
      vk:=TTab[t].anwendungen;
      while vk<>nil do
        begin
        if vk^.prod=pr then vk^.prod:=pr2;
        vk:=vk^.nxt;
        end;
      t:=TTab[t].nxt;
      end;
    sf:=AG.SemRules;
    while sf<>0 do
      begin
      vk:=SFTab[sf].anwendungen;
      while vk<>nil do
        begin
        if vk^.prod=pr then vk^.prod:=pr2;
        vk:=vk^.nxt;
        end;
      sf:=SFTab[sf].nxt;
      end;
    end (*Pumbenennen*);

  begin (*umbenennen*)
  pr2name[0]:=chr(0);
  loescheeingabefeld(md);
  gpr_$text('Produktion umbenennen in [Name]? ',34,status); CursorPos(y,x);x:=x+34*rbs.zbreite;
  108:
  editname(y,x,prodHL,pr2name);
  if isIdent(pr2name) then
    begin
    fpo:=formpraefixop(pr2name[ord(pr2name[0])]);
    if fpo>0 then
      begin
      vspp(wrtonly);
      evibs2(false,false,prodHL,wrtonly,pr2name,pr2);
      if pr2=ERR then { null }
      else if pr2=-1 then
	begin
	loescheeingabefeld(md);
	gpr_$text('NEUER Name der Produktion? ',27,status); CursorPos(y,x); x:=x+27*rbs.zbreite;
	goto 108;
	end
      else wrtERR1('aeP:umbenennen')
      end
    else
      begin
      hash(prodHL,pr2name,pr2,ex);
      if ex then meldefehler(13) else Pumbenennen;
      end
    end
   else if ord(pr2name[0])<>0 
         then begin
               meldefehler(1);
               goto 108;
              end;
  end (*umbenennen*);

  procedure ergVdef;
  var vnm: Ident;
      ptr: AListe;
  begin
  vnm[0]:=chr(0);
  ptr:=Tneudefs;
  while ptr<>nil do 
    begin
    defT(ptr^.attr,vnm);
    ptr:=ptr^.nxt;
    end;
  ptr:=NTneudefs;
  while ptr<>nil do
    begin
    defNT(ptr^.attr,vnm);
    ptr:=ptr^.nxt;
    end;
  gibALzurueck(Tneudefs);
  gibALzurueck(NTneudefs);
  end (*ergVdef*);

  procedure liesV;
  label 109,119;
  var y,x,fpo,vind,pos: integer;
      vnm: Ident;
      ex: boolean;
      antwort:char;

    procedure halbdef(voktyp: HashListen; var vnm: Ident; vind: integer);
    var cP: PListe;
        pos: integer;
        neu: boolean;
    begin
    beschaffeP(cP);
    cP^.prod:=pr;
    cP^.nxt:=nil;
    pos:=0;
    if voktyp=nontHL then
      begin
      with NTTab[vind] do
        begin
        name:=vnm;
        inhAttr:=nil;
        derAttr:=nil;
        aAzuAL(vind,pos,NTneudefs,neu);
        anwendungen:=cP;
        scannerklasse:=0;
        end;
      end
    else
      begin
      with TTab[vind] do
        begin
        name:=vnm;
        typ:=0; (* !!! *)
        sz1:=blk;
        sz2:=blk;
        scannerklasse:=0;
        anwendungen:=cP;
        end;
      aAzuAL(vind,pos,Tneudefs,neu);
      end;
    lexeinhaengen(voktyp,vind);
    end (*halbdef*);

  begin (*liesV*)
  119:
  loescheeingabefeld(md);
  gpr_$text(vokfrage[listreq],48,status);
  109:
  CursorPos(y,x); x:=x+48*rbs.zbreite;
   setCursor(y,x);
  vnm[0]:=chr(0);
  editname(y,x,listreq,vnm);
  if isIdent(vnm) then
    begin
    fpo:=formpraefixop(vnm[ord(vnm[0])]);
    if fpo>0 then
      begin
      if geladen<>listreq then
	begin
	if listreq=nontHL then vspnt(rdorwrt,fpo) else vspt(rdorwrt);
	geladen:=listreq;
	evibsD.prtreq:=true;
	end;
      evibs2(fpo>=2,false,listreq,rdorwrt,vnm,vind);
      evibsD.prtreq:=false;
      if vind=ERR then { null }
      else
	begin
	if vind<>-1 then { null }
	else
	  begin
	  loescheeingabefeld(md);
	  gpr_$text(neuelmtfrage[listreq],48,status);
      setCursor(md.yinput,49*rbs.zbreite);
	  goto 109;
	  end;
	end;
      end
    else
      begin
      hash(listreq,vnm,vind,ex);
      if ex
       then { null }
       else begin
                 meldung(46);
                 antworte(janein,antwort);
                 clearmeldung;
                 if antwort in ['N','A']
                  then goto 119
                  else halbdef(listreq,vnm,vind);
                end;
      end
    end
  else
    begin
    if ord(vnm[0]) = 0 then { null } else meldefehler(5);
    vind:=ERR;
    end;
  if vind=ERR then { null }
  else
    begin
    loescheeingabefeld(md);
    gpr_$text('Bitte Position markieren [Cursor] ',34,status);
    Pcontr2(y0,pr,modus,pos);
    if pos<0 then { null }
    else
      begin
      if (pos=0) and (listreq=termHL) then meldefehler(33)
      else
	begin
        if (dienst=1) or (dienst=2) then ergPumVp(pr,vind,listreq,pos) else ersVinPp(pr,vind,listreq,pos);
	end;
      end
    end
  end (*liesV*);

begin (*aeP*)
sw:=aktSeite=0;
Seite1;
defmaske(prodHL,1,md);
y0:=md.ystern-6*md.azh;
initevibsD(3,md.zstern-3,md.azh);
clearscreen;
geladen:=noList;
dienst:=0;
Pmaske(false,md,PTab[pr].name);
NTneudefs:=nil;
Tneudefs:=nil;
vokfrage[nontHL]:='Name des einzufuegd./ersetzenden Nonterminals? ';
vokfrage[termHL]:='Name des einzufuegd./ersetzenden Terminals? ';
neuelmtfrage[nontHL]:='Name des neuen Nonterminals? ';
neuelmtfrage[termHL]:='Name des neuen Terminals? ';
repeat
  regel(y0,pr);
  waehledienst1(6,md.ystern-11*md.azh-11,md,dienst);
  case dienst of
    0: ;
    1: begin
       modus:='e';
       listreq:=nontHL;
       liesV;
       end;
    2: begin
       modus:='e';
       listreq:=termHL;
       liesV;
       end;
    3: umbenennen;
    4: if (PTab[pr].vater=nil) and (PTab[pr].soehne=nil) then meldefehler(35)
       else
	 begin
	 modus:='s';
	 listreq:=nontHL;
	 liesV;
	 end;
    5: if PTab[pr].soehne=nil then meldefehler(43) 
       else
	 begin
	 modus:='s';
	 listreq:=termHL;
	 liesV;
	 end;
    6: if (PTab[pr].vater=nil) and (PTab[pr].soehne=nil) then meldefehler(35)
       else
         begin
	 Pcontr2(y0,pr,'s',pos);
	 if pos>=0 then sVausPp(pr,pos)
	 end;
    end (*case*);
  ;
until (dienst=0) or (dienst=3);
ergVdef;
if sw then Seite0;
end; (*aeP*)


procedure aeNT (* nt: integer *);
label 122,123;
var l1,l2,l,y,x,fpo,nt2,dienst: integer;
    ntname,nt2name: Ident;
    md: MaskenDaten;
    c: char;
    sw,ex,b: boolean;

  procedure NTumbenennen;
  var vork: AListe;
      aktprod: integer;
      daddy,hisson: VokListe;
  begin
  NTTab[nt2]:=NTTab[nt];
  NTTab[nt2].name:=nt2name; 
  lexaushaengen(nontHL,nt);
  lexeinhaengen(nontHL,nt2);
  NTTab[nt].name[0]:=chr(0);
  vork:=inPvorkommen(NTTab[nt].anwendungen);
  while vork<>nil do
    begin
    aktprod:=vork^.attr;
    vork:=vork^.nxt;
    daddy:=PTab[aktprod].vater;
    hisson:=PTab[aktprod].soehne;
    if daddy <> nil then
      begin
      if daddy^.nt=nt then daddy^.nt:=nt2;
      end;
    while hisson <> nil do
      begin
      if hisson^.typ = nont then
        begin if hisson^.nt=nt then hisson^.nt:=nt2 end;
      hisson:=hisson^.nxt;
      end
    end
  end (* umbenennen *);

  procedure aeNTaeA;
  var c: char;
  
    procedure NTcrtl(modus: char; art: Richtung; var pos: integer);
    var xstart,lg: array[Richtung] of integer;
        ystart,lastpos: integer;
        c: char;
        aart: Richtung;
    begin
    loescheeingabefeld(md);
    if modus='e'
    then gpr_$text('Bitte Einfuegeposition markieren [Cursor] ',42,status)
    else if modus='u'
          then begin
                gpr_$text('Bitte das umzuordnende Attribut markieren [Cursor]',50,status);
                modus := 's'
               end
          else gpr_$text('Bitte das zu streichende Attribut markieren [Cursor]',52,status);
    with NTTab[nt], evibsD, rbs do
      begin
      lg[inh]:=lgAL(inhAttr);
      lg[der]:=lgAL(derAttr);
      ystart:=md.ystern-6*md.azh;
      xstart[inh]:=md.rand+3; xstart[der]:=xpixels div 2 +3;
      if modus='e' then 
        begin
        ystart:=ystart+md.azh div 2;
        lastpos:=succ(lg[art]);
        pos:=lastpos;
        repeat
          setCursor(ystart-pos*md.azh,xstart[art]);
          cursoron;
          repeat move_read(c) until c in ['0','2','4','6','8',trz];
          cursoroff;
          case c of
    	'0': pos:=0;
    	'2': pos:=succ(pos mod lastpos);
    	'4': pos:=1;
    	'6': pos:=lastpos;
    	'8': if pos>1 then pos:=pred(pos) else pos:=lastpos;
    	trz: if art=inh then pos:=-pos;  
        otherwise;
    	end (*case*);
          ;
        until (c='0') or (c=trz);
        end
      else
        begin
        if (lg[inh]=0) and (lg[der]=0) then pos:=0
        else
          begin
          if lg[inh]>0 then 
    	    begin
    	    pos:=lg[inh]; aart:=inh 
    	    end
          else
    	    begin
    	    pos:=lg[der]; aart:=der;
    	    end;
          repeat
	    setCursor(ystart-pos*md.azh,xstart[aart]);
	    cursoron;
    	    repeat move_read(c) until c in ['0','2','4','6','8',trz];
	    cursoroff;
    	    case c of
              '0': pos:=0;
    	      '2': pos:=succ(pos mod lg[aart]);
    	      '4': begin
    	           if lg[inh]>0 then
    		     begin
    		     aart:=inh;
    		     if pos>lg[inh] then pos:=lg[inh];
    		     end
    	           end;
    	      '6': begin
    	           if lg[der]>0 then
    		     begin
    		     aart:=der;
    		     if pos>lg[der] then pos:=lg[der];
    		     end;
    	           end;
    	      '8': if pos>1 then pos:=pred(pos) else pos:=lg[aart];
    	      trz: if aart=inh then pos:=-pos; 
               otherwise;
    	      end (*case*);
    	    ;
          until (c='0') or (c=trz);
          end;
        end;
      end;
    end (*NTcrtl*);
  
    procedure bedAeinf(a,pos: integer);
    var apos,l: integer;
    begin
    if ATab[a].art=inh then l:=lgAL(NTTab[nt].inhAttr) else l:=lgAL(NTTab[nt].derAttr);
    apos:=abs(pos);
    aAzNTg(a,nt,apos);
    if apos<0 then meldefehler(24)
    else
      begin
      if l>= md.zstern then neuaufteilg(false,l+2,md);
      wrthalbattribg(nt,true,ATab[a].art,md); 
      end;
    end (*bedAeinf*);
    
    
    procedure bedAstreichen(var pos: integer);
    var l: AListe;
	a,i, pmb, gef: integer;
    begin
    if pos<>0 then
      begin
      if pos<0 then l:=NTTab[nt].inhAttr else l:=NTTab[nt].derAttr;
      for i:=1 to pred(abs(pos)) do l:=l^.nxt;
      a:=l^.attr;
      isAaktParNT(a,nt,pmb,gef);
      if globaendern(pmb,gef) then
	begin
        sAaNTg(a,nt);
        wrthalbattribg(nt,true,ATab[a].art,md)
	end;
      end;
    end;
    
    
    procedure usrAstreichen;
    var pos: integer;
    begin
    NTcrtl('s',inh,pos); (*2. Parameter beliebig*)
    bedAstreichen(pos);
    end;
     
procedure gesamtattributg;
  var ex,abbruch: boolean;
      fpo,y,x,nt2,l1,l2,l: integer;
      nt2name: Ident;
  
    procedure abbrechen;
    var c: char;
    begin
    with evibsD,rbs do
      begin
      loescheeingabefeld(md);
      gpr_$text('Wollen Sie die Aenderung beenden? [j n]   ',43,status); 
      repeat pread(c) until c in ['j','n','J','N'];
      gpr_$text(c,1,status);
      abbruch := (c='j') or (c = 'J');
      end;
    end; (*abbrechen*)
  
  begin (*gesamtattributg*)
  with rbs do
    begin
    repeat
      abbruch:=true;
      loescheeingabefeld(md);
      wrtIdent(ntname);gpr_$text(' wird attributiert wie Nonterminal? ',36,status);
      CursorPos(y,x); x:=x+(37+ord(ntname[0]))*rbs.zbreite;
      nt2name[0]:=chr(0);
      editname(y,x,nontHL,nt2name);
      if not isIdent(nt2name) then
        begin
        if ord(nt2name[0])<>0 then meldefehler(5);
        abbrechen;
        end
      else
        begin fpo:= formpraefixop(nt2name[ord(nt2name[0])]);
        if fpo>0 then
	  begin
	  vspnt(redonly,fpo); evibsD.prtreq:=true;
	  evibs2(fpo>=2,false,nontHL,redonly,nt2name,nt2);
	  evibsD.prtreq:=false;
	  if nt2=ERR then abbrechen
	  else
	    begin
	    copyALft(NTTab[nt2].inhAttr,NTTab[nt].inhAttr);
	    copyALft(NTTab[nt2].derAttr,NTTab[nt].derAttr);
	    l1:=lgAL(NTTab[nt].inhAttr);
	    l2:=lgAL(NTTab[nt].derAttr);
	    if l1>l2 then l:=l1 else l:=l2;
	    if l>md.zstern then
	      begin
	      clearscreen;
              neuaufteilg(true,l+2,md);
	      NTmaske(true,md,ntname);
	      end;
	    wrthalbattribg(nt,false,inh,md);
	    wrthalbattribg(nt,false,der,md);
	    end
	  end
        else
	  begin (*kein praefix, aber name*)
	  hash(nontHL,nt2name,nt2,ex);
	  if ex then
	    begin
	    copyALft(NTTab[nt2].inhAttr,NTTab[nt].inhAttr);
	    copyALft(NTTab[nt2].derAttr,NTTab[nt].derAttr); 
        l1:=lgAL(NTTab[nt].inhAttr);
	    l2:=lgAL(NTTab[nt].derAttr);
	    if l1>l2 then l:=l1 else l:=l2;
	    if l>md.zstern then
	      begin
	      clearscreen;
              neuaufteilg(true,l+2,md);
	      NTmaske(true,md,ntname);
	      end;
	    wrthalbattribg(nt,false,inh,md);
	    wrthalbattribg(nt,false,der,md);
	    end
	  else
	    begin
	    meldefehler(11);
	    abbrechen;
	    end;
	  end;
        end;
      ;
    until abbruch;
    end;
  end (*gesamtattributierung*);

    
    procedure usrAeinf;
    label 126, 9999;
    var fpo,y,x,a,pos: integer;
        aname: Ident;
        ex: boolean;
        c: char;
    begin
    with evibsD, rbs do
      begin
      loescheeingabefeld(md); 
      if (NTTab[nt].inhAttr=nil) and  (NTTab[nt].derAttr=nil)
      then begin 
            gpr_$text('Wollen Sie die Attribute eines anderen Nonterminals uebernehmen [j n]? ',71,status);
            repeat pread(c) until c in ['j','n','J','N'];
            if c in ['j','J'] then 
                  begin
                  gesamtattributg ;
                  goto 9999
                  end
            else loescheeingabefeld(md);
        end;
      gpr_$text('Name des einzufuegenden Attributs? ',35,status); CursorPos(y,x);x:=x+35*rbs.zbreite;
    126:
      aname[0]:=chr(0);
      editname(y,x,attrHL,aname);
      if not isIdent(aname) then
        begin
        if ord(aname[0])<>0 then 
          begin
          meldefehler(5);
          goto 126;
          end
        end 
      else 
        begin (*name*)
        fpo:= formpraefixop(aname[ord(aname[0])]);
        if fpo>0 then
          begin (*praefix*)
          evibs2(fpo>=2,false,attrHL,rdorwrt,aname,a);
          prtreq:=false;
          if a<>ERR then
    	    begin
    	    if a=-1 then
    	      begin
	      loescheeingabefeld(md);
    	      gpr_$text('Wie soll das neue Attribut heissen? ',36,status);
    	      CursorPos(y,x); x:=x+36*rbs.zbreite;
    	      goto 126
    	      end 
    	    else
    	      begin
    	      NTcrtl('e',ATab[a].art,pos);
    	      bedAeinf(a,pos);
    	      end
    	    end
          end
        else
          begin (* kein Praefix*)
          hash(attrHL,aname,a,ex);
          if ex then
    	    begin
    	    NTcrtl('e',ATab[a].art,pos);
    	    bedAeinf(a,pos);
    	    end
          else
    	    begin
	    loescheeingabefeld(md);
	    meldung(61);
	    antworte(inhder,c);
    	    clearmeldung;
    	    if c<>'0' then
    	      begin
    	      with ATab[a] do
    	        begin
    	        name:=aname;
    	        typ:=0;
    	        symbol:=0;
    	        if c='I' then art:=inh else art:=der;
    	        end;
    	      lexeinhaengen(attrHL,a);
    	      NTcrtl('e',ATab[a].art,pos);
    	      bedAeinf(a,pos);
    	      end
    	    end
          end (*kein praefix*)
        end (*name*)              
      end; (*with*)
   9999: end (*usrAeinf*);

    procedure aeAreihgg;
    var apos,a,y,x,aposneu: integer;
        prz: AListe;
        s: VokListe;

      function gibA: integer;
      var l: AListe;
	  i: integer;
      begin
      if apos<0 then l:=NTTab[nt].inhAttr else l:=NTTab[nt].derAttr;
      for i:=1 to pred(abs(apos)) do l:=l^.nxt;
      gibA:=l^.attr;
      end (*gibA*);

      procedure loescheA;
      var x1,x2,y: integer;
      begin
      if ATab[a].art=inh then
	begin
	x1:=md.rand+1; x2:=rbs.xpixels div 2 - 1
	end
      else
	begin
	x1:=rbs.xpixels div 2 +1; x2:=rbs.xpixels -md.rand-1
	end;
      y:=md.ystern-(6+abs(apos))*md.azh;
      male4eck(true,y,pred(y+md.azh),x1,x2);
      end (*loescheA*);

    procedure umordnen;
    var absaposneu,pos: integer;
	neu: boolean;
    begin
    if abs(aposneu)>abs(apos) then absaposneu:=pred(abs(aposneu)) else absaposneu:=abs(aposneu);
    if abs(apos)=absaposneu then { null }
    else
      begin
      if apos<0 then
	begin
	sAausAL(a,NTTab[nt].inhAttr,pos);
	aAzuAL(a,absaposneu,NTTab[nt].inhAttr,neu);
	end
      else
	begin
	sAausAL(a,NTTab[nt].derAttr,pos);
	aAzuAL(a,absaposneu,NTTab[nt].derAttr,neu);
	end;
      end;
    end (*umordnen*);

    begin (*aeAreihgg*);
    repeat
      loescheeingabefeld(md);
      NTcrtl('u',inh,apos);
      if apos=0 then { null }
      else
        begin
        a:=gibA;
        loescheA;
        loescheeingabefeld(md);
        gpr_$text('Bitte ordnen Sie Attribut ',26,status); CursorPos(y,x);x:=x+26*rbs.zbreite;
        setCursor(y,x+ASymb.breite);
        gpr_$text(' an neuer Stelle ein.',21,status);
        writeikon(y,x,ATab[a].symbol);
        repeat
	  NTcrtl('e',ATab[a].art,aposneu);
	  if aposneu=0 then meldefehler(7) else umordnen;
	  wrthalbattribg(nt,true,ATab[a].art,md);
        until apos<>0;
        end;
      ;
    until apos=0;
    prz:=inPvorkommen(NTTab[nt].anwendungen);
    while prz<>nil do
      begin
      with PTab[prz^.attr] do
	begin
	if vater<>nil then if vater^.nt=nt then if vater^.konsistent then
	  begin
	  expandntv(vater);
	  comprntv(vater);
	  end;
	s:=soehne;
	while s<>nil do
	  begin
	  if s^.typ=nont  then if s^.nt=nt then if s^.konsistent then
	    begin
	    expandntv(s);
	    comprntv(s);
	    end;
	  s:=s^.nxt;
	  end;
	end;
      prz:=prz^.nxt;
      end;
    end (*aeAreihgg*);
  
  
  begin (*aeNTaeA*)
  with rbs do
    begin
    vspa(rdorwrt,3);
    evibsD.prtreq:=true;
    repeat
      loescheeingabefeld(md);
      NTmaske1(md);
      waehledienst1(3,md.ystern-(md.zstern+8)*md.azh-11,md,dienst);
      loesche4eck(md.ystern-(md.zstern+7)*md.azh-6,md.ystern-(md.zstern+8)*md.azh-12,0,rbs.xpixels);
      case dienst of
        0: ;
        1: usrAeinf;
        2: usrAstreichen;
        3: aeAreihgg;
        otherwise;
      end; 
    until dienst=0;
    end;
  ergAtypen;
  end (*aeNTaeA*);

begin (*aeNT*)
sw:=aktSeite=0;
Seite1;
if nt>maxanzNT
 then begin
       nt:=nt-maxanzNT;
       b:=true
      end
 else b:=false;
l1:=lgAL(NTTab[nt].inhAttr); l2:=lgAL(NTTab[nt].derAttr);
ntname:=NTTab[nt].name;
if l1>l2 then l:=l1 else l:=l2;
defmaske(nontHL,l+2,md);
initevibsD(3,md.ystern-(md.zstern+8)*md.azh-1,md.azh);
clearscreen;
evibsD.prtreq:=true;
NTmaske(false,md,ntname);
wrthalbattribg(nt,false,inh,md); 
wrthalbattribg(nt,false,der,md);
123:
setCursor(md.yinput,md.xinput);
loescheeingabefeld(md);
if b
  then aeNTaeA
  else begin
    with md,rbs do begin
      linie(ystern-(zstern+7)*azh-6,rand,ystern-(zstern+7)*azh-6,xpixels-rand);
      linie(ystern-(zstern+8)*azh-12,rand,ystern-(zstern+8)*azh-12,xpixels-rand);
      linie(ystern-(zstern+7)*azh-6,rand,ystern-(zstern+8)*azh-12,rand);
      linie(ystern-(zstern+7)*azh-6,xpixels div 2,ystern-(zstern+8)*azh-12,xpixels div 2);
      linie(ystern-(zstern+7)*azh-6,xpixels-rand,ystern-(zstern+8)*azh-12,xpixels-rand);
      setCursor(ystern-(zstern+8)*azh-8,rand+zbreite);
      gpr_$text('NONTERMINAL UMBENENNEN',22,status);
      setCursor(ystern-(zstern+8)*azh-8,xpixels div 2 + zbreite);
      gpr_$text('ATTRIBUTIERUNG AENDERN',22,status);
    end (* with *);
    waehledienst1(2,md.ystern-(md.zstern+8)*md.azh-11,md,dienst);
    loesche4eck(md.ystern-(md.zstern+8)*md.azh-12,md.ystern-(md.zstern+7)*md.azh-6,0,rbs.xpixels); 
    if dienst<>0 then
  begin
  if dienst=1 then
    begin
122:
    loescheeingabefeld(md);
    gpr_$text('Wie soll das Nonterminal jetzt heissen? ',34,status); CursorPos(y,x);x:=x+34*rbs.zbreite;
    nt2name[0]:=chr(0);
    editname(y,x,nontHL,nt2name);
    if isIdent(nt2name) then
      begin
      fpo:=formpraefixop(nt2name[ord(nt2name[0])]);
      if fpo>0 then
	begin
	vspnt(wrtonly,fpo);
	evibs2(fpo>2,false,nontHL,wrtonly,nt2name,nt2);
	if nt2 = -1 then goto 122 else goto 123;
	end
      else
	begin
	hash(nontHL,nt2name,nt2,ex);
	if ex then
	  begin
	  meldefehler(16);
	  goto 123;
	  end 
	else NTumbenennen
	end
      end
    else
      begin
      meldefehler(5);
      goto 123;
      end
    end
  else aeNTaeA
  end;
 end;
if sw then Seite0;
end (*aeNT*);



procedure defNT(* var ntname: Ident; nt: integer *);
var c: char;
    md: MaskenDaten;
    sw: boolean;

  procedure behandleAeingabe(a: integer);
  var y0, lastpos: integer;
      b: boolean;
      x: array [Richtung] of integer;
  begin
  with md, rbs, evibsD, ATab[a] do
    begin
    x[inh]:=rand+zbreite; 
    x[der]:=xpixels div 2 + x[inh];
    if art=inh then b:=isAelemAL(a,NTTab[nt].inhAttr) else b:=isAelemAL(a,NTTab[nt].derAttr);
    if b then meldefehler(24)
    else if art=aux then meldefehler(4) 
    else
      begin
      lastpos:=0;
      aAzNTg(a,nt,lastpos);
      if lastpos>zstern then neuaufteilg(true,lastpos+2,md);
      y0:=ystern-(lastpos+6)*azh;
      setCursor(y0,x[art]+2*zbreite); wrtIdent(name); 
      if typ>0 then 
        begin
        gpr_$text(':',1,status);
        writeikon(y0,x[art],symbol);
        setCursor(y0,x[art]+(idlaenge+4)*zbreite); wrtIdent(TypTab[typ].name)
        end
      end
    end
  end (*behandleAeingabe*);

  procedure eattributg;
  label 127; 
  var abbruch,ex: boolean;
      a, fpo: integer;
      aname: Ident;
      aart: Richtung;
      c: char;
  begin
  with evibsD, rbs do
    begin
    vspa(rdorwrt,3);
    prtreq:=true;
    repeat (*bis benutzer abbricht*)
      repeat (*bis aufgrund abbruchwunsch vermutet*)
        abbruch:=false;
	loescheeingabefeld(md);
        gpr_$text('Attributname/leere Eingabe',26,status); 
        aname[0]:=chr(0);
        editname(md.yinput, md.xinput+29*zbreite,attrHL,aname);
  127:  if not isIdent(aname) then
	  begin
	  abbruch:=true;
	  if ord(aname[0])<>0 then meldefehler(5)
	  end
        else
	  begin (* name nicht leer *)
	  fpo:= formpraefixop(aname[ord(aname[0])]);
	  if fpo>0 then
	    begin (*Eingabe mit Praefix*)
	    evibs2(fpo>=2,false,attrHL,rdorwrt,aname,a);
	    prtreq:=false;
	    if a=ERR then abbruch:=true
	    else
	      begin (*neudef. attr oder exd. attr*)
	      if a=-1 then
	        begin (*neudef. aus liste*)
		loescheeingabefeld(md);
	        gpr_$text('Wie heisst das neue Attribut? ',30,status);
		aname[0]:=chr(0);
	        editname(md.yinput,md.xinput+32*zbreite,attrHL,aname);
	        goto 127;
	        end (* neudef. in liste*)
	      else behandleAeingabe(a);
	      end (*Neudef. attr oder exd. attr*)
	    end (*Eingabe mit Praefixop*)
	  else
	    begin (*Eingabe eines Namens ohne Praefixop*)
	    hash(attrHL,aname,a,ex);
	    if not ex then
	      begin (*A ex. nicht bisher*)
	      loescheeingabefeld(md);
              antworte(inhder,c);
              if c='0' then a:=0
	      else
		begin
	        if c='I' then aart:=inh else aart:=der;
	        with ATab[a] do
	          begin
	          name:=aname;
	          typ:=0;
	          symbol:=0;
	          art:=aart;
	          end;
	        lexeinhaengen(attrHL,a);
		end;
	      end (*A ex bisher nicht*);
	    if a<>0 then behandleAeingabe(a);
	    end (*Eingabe Namen ohne Praefix*)
	  end (*name nicht leer*)
        ;
      until abbruch;
      loescheeingabefeld(md);
      gpr_$text('Wollen Sie die Definition beenden? [j n] ',41,status);
      keys :=['j','n','J','N'] ; {Create a key set.}
      gpr_$enable_input(gpr_$keystroke, keys, status); 
      keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
      gpr_$enable_input(gpr_$buttons, keys, status); 
      unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
      gpr_$text(c,1,status);
    until c='j';
    end
  end (*eattributg*);

  procedure gesamtattributg;
  var ex,abbruch: boolean;
      fpo,y,x,nt2,l1,l2,l: integer;
      nt2name: Ident;
  
    procedure abbrechen;
    var c: char;
    begin
    with evibsD,rbs do
      begin
      loescheeingabefeld(md);
      gpr_$text('Wollen Sie die Definition beenden? [j n]   ',43,status); 
      keys :=['j','n','J','N'] ; {Create a key set.}
      gpr_$enable_input(gpr_$keystroke, keys, status);
      keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
      gpr_$enable_input(gpr_$buttons, keys, status); 
      unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
      gpr_$text(c,1,status);
      abbruch:=c='j';
      end;
    end; (*abbrechen*)
  
  begin (*gesamtattributg*)
  with rbs do
    begin
    repeat
      abbruch:=true;
      loescheeingabefeld(md);
      wrtIdent(ntname);gpr_$text(' wird attributiert wie Nonterminal? ',36,status);
      CursorPos(y,x); x:=x+(37+ord(ntname[0]))*rbs.zbreite;
      nt2name[0]:=chr(0);
      editname(y,x,nontHL,nt2name);
      if not isIdent(nt2name) then
        begin
        if ord(nt2name[0])<>0 then meldefehler(5);
        abbrechen;
        end
      else
        begin fpo:= formpraefixop(nt2name[ord(nt2name[0])]);
        if fpo>0 then
	  begin
	  vspnt(redonly,fpo); evibsD.prtreq:=true;
	  evibs2(fpo>=2,false,nontHL,redonly,nt2name,nt2);
	  evibsD.prtreq:=false;
	  if nt2=ERR then abbrechen
	  else
	    begin
	    copyALft(NTTab[nt2].inhAttr,NTTab[nt].inhAttr);
	    copyALft(NTTab[nt2].derAttr,NTTab[nt].derAttr);
	    l1:=lgAL(NTTab[nt].inhAttr);
	    l2:=lgAL(NTTab[nt].derAttr);
	    if l1>l2 then l:=l1 else l:=l2;
	    if l>md.zstern then
	      begin
	      clearscreen;
              neuaufteilg(true,l+2,md);
	      NTmaske(true,md,ntname);
	      end;
	    wrthalbattribg(nt,false,inh,md);
	    wrthalbattribg(nt,false,der,md);
	    end
	  end
        else
	  begin (*kein praefix, aber name*)
	  hash(nontHL,nt2name,nt2,ex);
	  if ex then
	    begin
	    copyALft(NTTab[nt2].inhAttr,NTTab[nt].inhAttr);
	    copyALft(NTTab[nt2].derAttr,NTTab[nt].derAttr);
	    end
	  else
	    begin
	    meldefehler(11);
	    abbrechen;
	    end;
	  end;
        end;
      ;
    until abbruch;
    end;
  end (*gesamtattributierung*);

begin (*defNT*)
sw:=aktSeite=0;
Seite1;
if ord(ntname[0])=0 then { null } 
else
  begin
  with NTTab[nt] do
    begin
    name:=ntname;
    inhAttr:=nil;
    derAttr:=nil;
    anwendungen:=nil;
    scannerklasse:=0;
    end;
  lexeinhaengen(nontHL,nt);
  end;
with NTTab[nt],rbs do
  begin
  defmaske(nontHL,0,md);
  initevibsD(3,md.ystern-(md.zstern+8)*md.azh,md.azh);
  clearscreen;
  evibsD.prtreq:=true;
  NTmaske(true,md,NTTab[nt].name);
  if (AG.Nonterms=nt) and (NTTab[nt].nxt=0) then c:='n'
  else 
    begin setCursor(md.yinput,md.xinput);
    gpr_$text('Wollen Sie gleich Attribute zuordnen [j n] ?',44,status); 
    keys :=['j','n','J','N'] ; {Create a key set.}
    gpr_$enable_input(gpr_$keystroke, keys, status);
    keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
    keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
    gpr_$enable_input(gpr_$buttons, keys, status); gpr_$enable_input(gpr_$buttons, keys, status); 
    unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
    if c='j' then
     begin
      loescheeingabefeld(md);
      gpr_$text('Wollen Sie die Attribute eines anderen Nonterminals uebernehmen [j n]?',71,status);
      keys :=['j','n','J','N'] ; {Create a key set.}
      gpr_$enable_input(gpr_$keystroke, keys, status);
      keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
      gpr_$enable_input(gpr_$buttons, keys, status); 
      unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
     end
     else c:='z'; 
    end;
  if c<>'z' then begin
  if c='j' then gesamtattributg else eattributg;
  ergAtypen;
  if c='j' then aeNT(nt+maxanzNT);
  end;
 end;
if sw then Seite0;
end (*defNT*);


procedure defP(* pr: integer; var prn: Ident *);
const rRand=79;
var md: MaskenDaten;
    NTneudefs,Tneudefs: AListe;
    sw: boolean;
    dienst: integer;

  procedure halbdef(voktyp: HashListen; var vnm: Ident; vind: integer);
  var cP: PListe;
      pos: integer;
      neu: boolean;
  begin
  beschaffeP(cP);
  cP^.prod:=pr;
  cP^.nxt:=nil;
  pos:=0;
  if voktyp=nontHL then
    begin
    with NTTab[vind] do
      begin
      name:=vnm;
      inhAttr:=nil;
      derAttr:=nil;
      anwendungen:=nil;
      scannerklasse:=0;
      end;
    aAzuAL(vind,pos,NTneudefs,neu);
    end
  else
    begin
    with TTab[vind] do
      begin
      name:=vnm;
      typ:=0;
      sz1:=blk;
      sz2:=blk;
      scannerklasse:=0;
      anwendungen:=nil;
      end;
    aAzuAL(vind,pos,Tneudefs,neu);
    end;
  lexeinhaengen(voktyp,vind);
  end (*halbdef*);

  procedure ergVdef;
  var vnm: Ident;
      ptr: AListe;
  begin
  ptr:=Tneudefs;
  while ptr<>nil do 
    begin vnm[0]:=chr(0);
    defT(ptr^.attr,vnm);
    ptr:=ptr^.nxt;
    end;
  ptr:=NTneudefs;
  while ptr<>nil do
    begin
    vnm[0]:=chr(0);
    defNT(ptr^.attr,vnm);
    ptr:=ptr^.nxt;
    end;
  gibALzurueck(Tneudefs);
  gibALzurueck(NTneudefs);
  end (*ergVdef*);

  procedure leseVn;
  label 112,333; 
  var pos,y0,y,x,fpo,vind,dienst: integer;
      geladen,listreq: HashListen;
      c,antwort: char;
      vnm: Ident;
      ex: boolean;
  begin
  pos:=0;
  geladen:=noList;
  y0:=md.ystern-6*md.azh;
  Tneudefs:=nil;
  NTneudefs:=nil;
  repeat 
    333:
    if pos=0 then dienst:=1
    else
      begin
      loescheeingabefeld(md);
      with md,rbs do begin
        loesche4eck(ystern-10*azh-6,0,0,xpixels);
        linie(ystern-10*azh-6,rand,ystern-10*azh-6,xpixels-rand);
        linie(ystern-11*azh-12,rand,ystern-11*azh-12,xpixels-rand);
        linie(ystern-10*azh-6,rand,ystern-11*azh-12,rand);
        linie(ystern-10*azh-6,xpixels div 2,ystern-11*azh-12,xpixels div 2);
        linie(ystern-10*azh-6,xpixels-rand,ystern-11*azh-12,xpixels-rand);
        setCursor(ystern-11*azh-8,rand+zbreite);
        gpr_$text('naechster Sohn ist NONTERMINAL',30,status);
        setCursor(ystern-11*azh-8,xpixels div 2 + zbreite);
        gpr_$text('naechster Sohn ist TERMINAL',27,status);
      end (* with *);
      waehledienst1(2,md.ystern-11*md.azh-11,md,dienst);
      loesche4eck(md.ystern-10*md.azh-6,md.ystern-11*md.azh-12,0,rbs.xpixels); 
      end;
      if dienst=0 then { null } else
      begin
      loescheeingabefeld(md);
      gpr_$text('Name des ',9,status);
      if pos=0 then gpr_$text('Vaters? ',8,status) 
      else
        begin
        if dienst=1 then gpr_$text('nonterminalen ',14,status) else gpr_$text('terminalen ',11,status);
        gpr_$text('Sohnes? ',8,status);
        end;
      CursorPos(y,x); x:=x+31*rbs.zbreite;
      if dienst=1 then listreq:=nontHL else listreq:=termHL;
      112:
      vnm[0]:=chr(0);
      editname(y,x,listreq,vnm);
      if isIdent(vnm) then
        begin
        fpo:=formpraefixop(vnm[ord(vnm[0])]);
        if fpo>0 then
          begin
          if listreq=geladen then { null }      
          else
            begin
            if listreq=nontHL then vspnt(rdorwrt,fpo) else vspt(rdorwrt);
            geladen:=listreq;
            evibsD.prtreq:=true;
            end;
          evibs2(fpo>=2,false,listreq,rdorwrt,vnm,vind);
          evibsD.prtreq:=false;
          if vind=ERR then { null }
          else
            begin
            if vind=-1 then
              begin
              loescheeingabefeld(md);
              if dienst=1 then gpr_$text('Wie soll das neue Nonterminal heissen? ',40,status)
                          else gpr_$text('Wie soll das neue Terminal heissen? ',37,status);
              CursorPos(y,x); x:=x+40*rbs.zbreite;
              goto 112;
              end
            else { null }
            end
          end
        else
          begin
          if dienst=1 then hash(nontHL,vnm,vind,ex) else hash(termHL,vnm,vind,ex);
          if ex 
           then { null }
           else begin
                 meldung(46);
		 antworte(janein,antwort);
                 clearmeldung;
                 if antwort in ['A','N']
                  then goto 333
                  else halbdef(listreq,vnm,vind);
                end;
          end;
        end
      else
        begin
        if ord(vnm[0])=0 then
          begin
          if pos=0 then pos:=1 else meldefehler(1)
          end
        else meldefehler(5);
        vind:=ERR;
        end;
      if vind=ERR then { null }
      else
        begin
        regelkoord(y0,pr,pos,y,x);
	if x+ord(vnm[0])>=rRand-2 then
	  begin
	  y:=y-rbs.zhoehe;
	  x:=idlaenge+4;
	  end;
        setCursor(y,x*rbs.zbreite); wrtIdent(vnm);
        ergPumVp(pr,vind,listreq,pos);
        pos:=succ(pos);
        end;
      end;
  until dienst=0;
  ergVdef;
  end (*leseVn*);


begin  (*defP*)
sw:=aktSeite=0;
Seite1;
with PTab[pr] do
  begin
  name:=prn;
  vater:=nil;
  soehne:=nil;
  hilfsAttr:=nil;
  unversHAttr:=nil;
  semRegeln:=nil;
  end;
lexeinhaengen(prodHL,pr);
defmaske(prodHL,0,md);
initevibsD(3,md.ystern-10*md.azh-11,md.azh);
clearscreen;
Pmaske(true,md,prn);
leseVn;
if sw then Seite0;
end (*defP*);


procedure FPeinf(* sf,pos: integer; var fp: TypListe *);
var i: integer;
    hz: TypListe;
begin with SFTab[sf] do
  begin
  if pos= -1 then
    begin
    fp^.nxt:=parlist;
    parlist:=fp;
    end
  else if pos=1 then
    begin
    fp^.nxt:=erglist;
    erglist:=fp;
    end
  else
    begin
    if pos<0 then hz:=parlist else hz:=erglist;
    for i:=1 to abs(pos)-2 do hz:=hz^.nxt;
    fp^.nxt:=hz^.nxt;
    hz^.nxt:=fp;
    end;
  end (*with*);
end (*FPeinf*);


procedure aktpareinf(* parms: boolean; ind, pos: integer *);
var 
    i: integer;
    vk: AListe;
    ap, l2: ParListe;
    sr: SemFktListe;
begin
with SFTab[ind] do
  begin
  vk:=inPvorkommen(anwendungen);
  while vk <> nil do
    begin
    sr:=PTab[vk^.attr].semRegeln;
    vk:=vk^.nxt;
    while sr <> nil do
      begin
      if sr^.semfkt=ind then
        begin
        beschaffePar(ap);
        with ap^ do
          begin
          vok:=nil;
          attr:=0;
          verb:=nil;
          nxt:=nil;
          end;
        with sr^ do
          begin
          versorgt:=false;
          if pos=1 then
            begin
            if parms then
              begin
              ap^.nxt:=quellpar;
              quellpar:=ap;
              end
            else
              begin
              ap^.nxt:=zielpar;
              zielpar:=ap;
              end; 
            end
          else
            begin
            if parms then l2:=quellpar else l2:=zielpar;
            for i:=1 to pos-2 do l2:=l2^.nxt;
            ap^.nxt:=l2^.nxt;
            l2^.nxt:=ap;
            end;
          end (*with sr*);
        end (*if sr^.name*);
      sr:=sr^.nxt; 
      end (*while sr*);
    end (*while vk*); 
  end (*with SFTab*);
end (*aktpareinf*);
 

procedure pstreichen(* parms: boolean; ind,pos: integer *);
var hz,l: TypListe; 
    i: integer; 
    vk: AListe;
    sr: SemFktListe;
    hz2,l2: ParListe;
begin
with SFTab[ind] do
  begin
  if pos<1 then wrtERR1('pstreichen:')
  else if pos=1 then
    begin
    if parms then
      begin
      hz:=parlist;
      parlist:=hz^.nxt;
      end
    else
      begin
      hz:=erglist;
      erglist:=hz^.nxt;
      end
    end
  else
    begin
    if parms then l:=parlist else l:=erglist;
    for i:=1 to pos-2 do l:=l^.nxt; 
    hz:=l^.nxt;
    l^.nxt:=hz^.nxt;
    end;
  hz^.nxt:=TypLL; TypLL:=hz;

  vk:=inPvorkommen(anwendungen);
  while vk <> nil do
    begin
    sr:=PTab[vk^.attr].semRegeln;
    vk:=vk^.nxt;
    while sr <> nil do
      begin
      if sr^.semfkt=ind then
        begin
        with sr^ do
          begin
          if pos=1 then
            begin
            if parms then
              begin
              hz2:=quellpar;
              quellpar:=hz2^.nxt;
              end
            else
              begin
              hz2:=zielpar;
              zielpar:=hz2^.nxt;
              end
            end
          else
            begin
            if parms then l2:=quellpar else l2:=zielpar; 
            for i:=1 to pos-2 do l2:=l2^.nxt;
            hz2:=l2^.nxt; 
            l2^.nxt:=hz2^.nxt;
            end;
	  hz2^.nxt:=ParLL; ParLL:=hz2;
          end (*with sr*);
        sr^.versorgt:=isSFversorgt(sr);
        end (*if*);
      sr:=sr^.nxt;
      end (*while sr*);
    end (*while vk*);
  end (*with SFTab*);
end (*pstreichen*);


procedure aeT (* t: integer *);
var md: MaskenDaten;
    c: char;
    sw: boolean;
    dienst:integer;
  
  procedure umbenennen;
  label 113;
  var y,x,fpo,t2: integer;
      t2name: Ident;
      ex: boolean;

    procedure Tumbenennen;
    var vork: AListe;
        aktprod: integer;
        hisson: VokListe;
    begin
    TTab[t2]:=TTab[t];
    TTab[t2].name:=t2name;
    lexaushaengen(termHL,t);
    lexeinhaengen(termHL,t2);
    TTab[t].name[0]:=chr(0);
    vork:=inPvorkommen(TTab[t].anwendungen);
    while vork<>nil do
      begin
      aktprod:=vork^.attr;
      vork:=vork^.nxt;
      hisson:=PTab[aktprod].soehne;
      while hisson <> nil do
        begin
        if hisson^.typ = term then 
          begin if hisson^.t=t then hisson^.t:=t2 end;
        hisson:=hisson^.nxt;
        end
      end
    end (* Tumbenennen *);
  
  begin (*umbenennen*)
  loescheeingabefeld(md);
  gpr_$text('Terminal umbenennen in? [Name] ',31,status); CursorPos(y,x);x:=x+31*rbs.zbreite;
  113:
  t2name[0]:=chr(0);
  editname(y,x,termHL,t2name);
  if isIdent(t2name) then
    begin
    fpo:=formpraefixop(t2name[ord(t2name[0])]);
    if fpo>0 then
      begin
      vspt(wrtonly);
      evibs2(false,false,termHL,wrtonly,t2name,t2);
      if t2=ERR then { null }
      else
	begin
	if t2=-1 then
	  begin
	  loescheeingabefeld(md);
	  gpr_$text('Bitte NEUEN Terminalnamen angeben ',34,status); CursorPos(y,x); x:=x+34*rbs.zbreite;
	  goto 113;
	  end
	else { null };
	end
      end
    else
      begin
      hash(termHL,t2name,t2,ex);
      if ex then meldefehler(14) else Tumbenennen;
      end
    end
  else
    begin
    if ord(t2name[0])<>0 then meldefehler(5) else { null };
    end
  end (*umbenennen*);

begin (*aeT*)
sw:=aktSeite=0;
Seite1;
defmaske(termHL,0,md);
initevibsD(3,md.yinput-rbs.zhoehe,md.azh);
clearscreen;
evibsD.prtreq:=true;
Tmaske(false,md,TTab[t].name);
setCursor(md.ystern-6*md.azh+2,19*rbs.zbreite);
with TTab[t] do begin gpr_$text(sz1,1,status); gpr_$text(sz2,1,status) end;
  loescheeingabefeld(md);
  gpr_$text('Bitte waehlen Sie [Cursor]',26,status);
  with md,rbs do begin
    linie(yinput-6,rand,yinput-6,xpixels-rand);   
    linie(yinput-12-azh,rand,yinput-12-azh,xpixels-rand);
    linie(yinput-azh-12,rand,yinput-6,rand);
    linie(yinput-azh-12,xpixels div 2,yinput-6,xpixels div 2);
    linie(yinput-azh-12,xpixels-rand,yinput-6,xpixels-rand);
    setCursor(yinput-8-azh,rand+zbreite);
    gpr_$text('NAME AENDERN',12,status);
    setCursor(yinput-8-azh,xpixels div 2 + zbreite);
    gpr_$text('KURZDARSTELLUNG AENDERN',23,status);
  end (* with *);
  waehledienst1(2,md.yinput-11-md.azh,md,dienst);
  loesche4eck(md.yinput-12-md.azh,md.yinput-6,0,rbs.xpixels);
  case dienst of 
    0: ;
    1: begin
       loescheeingabefeld(md);
       gpr_$text('Bitte geben Sie die neue Darstellung an ',40,status);
       loeschewort(md.ystern-6*md.azh,19*rbs.zbreite,2);
       readTersatz(md.ystern-6*md.azh,19*rbs.zbreite,t);
       end;
    2: umbenennen;
    otherwise;
    end (*case*);
if sw then Seite0;
end (*aeT*);


procedure defT(* t: integer; var tname: Ident *);
var md: MaskenDaten;
    sw: boolean;
begin
sw:=aktSeite=0;
Seite1;
if ord(tname[0])=0 then { null } 
else
  begin
  with TTab[t] do
    begin
    name:=tname;
    typ:=0;
    scannerklasse:=0;
    anwendungen:=nil;
    end;
  lexeinhaengen(termHL,t);
  end;
defmaske(termHL,0,md);
initevibsD(3,md.yinput-rbs.zhoehe,md.azh);
clearscreen;
evibsD.prtreq:=true;
Tmaske(true,md,TTab[t].name);
readTersatz(md.ystern-6*md.azh+2,20*rbs.zbreite,t);
if sw then Seite0;
end (*defT*);



procedure FPumbenennen(* parms: boolean; ind, pos: integer; typnm: integer *);
var l: TypListe;
    vk: AListe;
    i: integer;
    sr,srnext: SemFktListe;
    l2: ParListe;
begin
with SFTab[ind] do
  begin
  if parms then l:=parlist else l:=erglist;
  for i:=1 to pred(pos) do l:=l^.nxt;
  l^.typ:=typnm;
  vk:=inPvorkommen(anwendungen);
  end;
while vk<>nil do
  begin
  sr:=PTab[vk^.attr].semRegeln;
  while sr<>nil do
    begin srnext:=sr^.nxt;
    if sr^.semfkt=ind then
      begin
      with sr^ do if parms then l2:=quellpar else l2:=zielpar;
      for i:=1 to pred(pos) do l2:=l2^.nxt;
      entkopple(sr,l2);
      if not hatSFerg(sr) then gibfreiSF(vk^.attr,sr);
      end;
    sr:=srnext;
    end (*while sr*);
  vk:=vk^.nxt;
  end; (*while vk*)
end (*FPumbenennen*);



procedure aeSF(* sf: integer *);
const plusaktpar=false;
var sfname: Ident;
    md: MaskenDaten;
    ysfname,dienst,i: integer;
    sw: boolean;

  procedure einfuegen;
  label 120;
  var pos,y,x,fpo,tind: integer;
      tnm: Ident;
      fp: TypListe;
      ex: boolean;
  begin
  loescheeingabefeld(md);
  gpr_$text('Position des neuen formalen Parameters [Cursor]',47,status);
  contr(ysfname,sf,'e',pos);
  if pos<>0 then
    begin
    loescheeingabefeld(md);
    gpr_$text('Typname des einzufuegenden Parameters? ',39,status); CursorPos(y,x);x:=x+39*rbs.zbreite;
  120:
    tnm[0]:=chr(0);
    editname(y,x,typeHL,tnm);
    if isIdent(tnm) then
      begin
      fpo:=formpraefixop(tnm[ord(tnm[0])]);
      if fpo>0 then
	begin
	evibs2(false,false,typeHL,rdorwrt,tnm,tind);
	evibsD.prtreq:=false;
	if tind=ERR then { null } else
	  begin
	  if tind=-1 then
	    begin
	    loescheeingabefeld(md);
	    gpr_$text('Bitte NEUEN Typnamen angeben fuer formalen Parameter ',60,status);
	    CursorPos(y,x);
        x:=x+60*rbs.zbreite;
	    goto 120;
	    end
	  else { null };
	  beschaffeTyp(fp);
	  FPeinf(sf,pos,fp); fp^.typ:=tind;
	  aktpareinf(pos<0,sf,abs(pos));
	  end
	end
      else
	begin
	hash(typeHL,tnm,tind,ex);
	if ex then { null }
	else
	  begin
	  TypTab[tind].name:=tnm;
	  lexeinhaengen(typeHL,tind);
	  vsptp(rdorwrt);
	  evibsD.prtreq:=true;
	  end;
	beschaffeTyp(fp);
	FPeinf(sf,pos,fp);
	fp^.typ:=tind;
	aktpareinf(pos<0,sf,abs(pos));
	end
      end
    else
      begin
      if ord(tnm[0])<>0 then meldefehler(5) else { null };
      end;
    end
  end (*einfuegen*);

  procedure streichen;
  var pos,pmb,gef: integer;
  begin
  loescheeingabefeld(md);
  gpr_$text('Position des zu streichenden Parameters? [Cursor] ',50,status);
  contr(ysfname,sf,'s',pos);
  if pos<>0 then
    begin
    if (pos=1) and (lgtl(SFTab[sf].erglist)<=1) then meldefehler(27)
    else 
      begin
      hatparambindung(sf,pos,pmb,gef);
      if globaendern(pmb,gef) then pstreichen(pos<0,sf,abs(pos));
      end;
    end;
  end (*streichen*);

  procedure aetypname;
  label 119;
  var pos,y,x,fpo,tind,pmb,gef: integer;
      tnm: Ident;
      ex: boolean;
  begin
  loescheeingabefeld(md);
  gpr_$text('Bitte markieren Sie den zu aendernden Parameter [Cursor]',56,status);
  contr(ysfname,sf,'s',pos);
  if pos<>0 then
    begin
    hatparambindung(sf,pos,pmb,gef);
    if globaendern(pmb,gef) then
      begin
      loescheeingabefeld(md);
      gpr_$text('Neuer Typname? ',15,status); CursorPos(y,x);x:=x+15*rbs.zbreite;
      119:
      tnm[0]:=chr(0);
      editname(y,x,typeHL,tnm);
      if isIdent(tnm) then
        begin
        fpo:=formpraefixop(tnm[ord(tnm[0])]);
        if fpo>0 then
          begin
          evibs2(false,false,typeHL,rdorwrt,tnm,tind);
          evibsD.prtreq:=false;
          if tind=ERR then { null }
          else
	    begin
	    if tind=-1 then 
	      begin
	      loescheeingabefeld(md);
	      gpr_$text('Bitte NEUEN Typnamen angeben',28,status);
	      goto 119;
	      end
	    else FPumbenennen(pos<0,sf,abs(pos),tind);
	    end
          end
        else
          begin
          hash(typeHL,tnm,tind,ex);
          if ex then { null }
          else
	    begin
	    TypTab[tind].name:=tnm;
	    lexeinhaengen(typeHL,tind);
	    vsptp(rdorwrt);
	    evibsD.prtreq:=true;
	    end;
          FPumbenennen(pos<0,sf,abs(pos),tind);
          end
        end
      else
        begin
        if ord(tnm[0])<>0 then meldefehler(5) else { null }
        end
      end
    end;
  end (*aetypname*);

  procedure umbenennen;
  label 118;
  var y,x,fpo,sf2: integer;
      sf2name: Ident;
      ex: boolean;
  
    procedure SFumbenennen;
    var vk: AListe;
        sr: SemFktListe;
    begin
    SFTab[sf2]:=SFTab[sf];
    SFTab[sf2].name:=sf2name;
    lexaushaengen(sfktHL,sf);
    lexeinhaengen(sfktHL,sf2);
    SFTab[sf].name[0]:=chr(0);
    vk:=inPvorkommen(SFTab[sf].anwendungen);
    while vk <> nil do
      begin
      sr:=PTab[vk^.attr].semRegeln;
      vk:=vk^.nxt;
      while sr <> nil do
        begin
        if sr^.semfkt=sf then sr^.semfkt:=sf2;
        sr:=sr^.nxt;
        end; 
      end;
    end (*SFumbenennen*);

  begin (*umbenennen*)
  118:
  loescheeingabefeld(md);
  gpr_$text('Welchen NEUEN Namen soll die Funktion tragen? ',46,status); CursorPos(y,x); x:=x+46*rbs.zbreite;
  sf2name[0]:=chr(0);
  editname(y,x,sfktHL,sf2name);
  if isIdent(sf2name) then
    begin
    fpo:=formpraefixop(sf2name[ord(sf2name[0])]);
    if fpo>0 then
      begin
      vspsf(wrtonly);
      evibsD.prtreq:=true;
      evibs2(false,false,sfktHL,wrtonly,sf2name,sf2);
      if sf2=ERR then { null } else goto 118;
      end
    else
      begin
      hash(sfktHL,sf2name,sf2,ex);
      if ex then meldefehler(17) else SFumbenennen;
      end
    end
  else
    begin
    if ord(sfname[0]) <> 0 then meldefehler(5) else { null };
    end
  end (*umbenennen*);

begin (*aeSF*)
sw:=aktSeite=0;
Seite1;
sfname:=SFTab[sf].name;
defmaske(sfktHL,0,md);
initevibsD(3,md.ystern-14*md.azh-3,md.azh);
ysfname:=md.ystern-6*md.azh;
clearscreen;
evibsD.prtreq:=true;
SFmaske(false,md,sfname);
vsptp(rdorwrt);
dienst:=1;
repeat
  loeschesignatur(plusaktpar,ysfname,sf);
  signatur(plusaktpar,ysfname,sf);
  loescheeingabefeld(md);
  gpr_$text('Bitte waehlen Sie! [Cursor]',28,status);
  with md,rbs do begin 
    for i:=1 to 3 do
      linie(ystern-(10+i)*azh-i*6,rand,ystern-(10+i)*azh-i*6,xpixels-rand);
    linie(ystern-11*azh-6,rand,ystern-13*azh-18,rand);
    linie(ystern-11*azh-6,xpixels div 2,ystern-13*azh-18,xpixels div 2);
    linie(ystern-11*azh-6,xpixels-rand,ystern-13*azh-18,xpixels-rand);
    setCursor(ystern-12*azh-8,rand+zbreite);
    gpr_$text('FORM. PARAMETER EINFUEGEN',25,status);
    setCursor(ystern-12*azh-8,xpixels div 2 + zbreite);
    gpr_$text('TYPNAMEN AENDERN',16,status);
    setCursor(ystern-13*azh-14,rand+zbreite);
    gpr_$text('FORM. PARAMETER STREICHEN',25,status);
    setCursor(ystern-13*azh-14,xpixels div 2 + zbreite);
    gpr_$text('FUNKTION UMBENENNEN',19,status);
  end (* with *);
  waehledienst1(4,md.ystern-12*md.azh-11,md,dienst);
  loesche4eck(md.ystern-13*md.azh-18,md.ystern-11*md.azh-6,0,rbs.xpixels);
  case dienst of
    0: ;
    1: einfuegen;
    2: aetypname;
    3: streichen;
    4: umbenennen;
    end (*case*);
until (dienst=0) or (dienst=4);
if sw then Seite0;
end (*aeSF*);



procedure aeA(* a: integer *);
var md: MaskenDaten;
    c,r: char;
    neuart: Richtung;
    sw: boolean;
    pmb,gef,dienst,i: integer;

  procedure umbenennen; 
  label 115;
  var 
      y,x,fpo,a2: integer;
      a2name: Ident;
      ex: boolean;

    procedure Aumbenennen;
    var nt, pr: integer;
        vl: VokListe;
        sr: SemFktListe;
    begin
    ATab[a2]:=ATab[a];
    ATab[a2].name:=a2name;
    lexaushaengen(attrHL,a);
    lexeinhaengen(attrHL,a2);
    ATab[a].name[0]:=chr(0);
    nt:=AG.Nonterms;
    while nt<>0 do
      begin
      umbAinAListe(NTTab[nt].inhAttr,a,a2);
      umbAinAListe(NTTab[nt].derAttr,a,a2);
      nt:=NTTab[nt].nxt;
      end;
    pr:=AG.Prods;
    while pr<>0 do
      begin
      vl:=PTab[pr].vater;
      if vl<>nil then
        begin
        umbAinAListe(vl^.spezInhA,a,a2);
        umbAinAListe(vl^.spezDerA,a,a2);
        end;
      vl:=PTab[pr].soehne;
      while vl<>nil do
        begin
        if vl^.typ=nont then
  	begin
  	umbAinAListe(vl^.spezInhA,a,a2);
  	umbAinAListe(vl^.spezDerA,a,a2);
  	end;
        vl:=vl^.nxt;
        end;
      umbHAinHAListe(PTab[pr].hilfsAttr,a,a2);
      sr:=PTab[pr].semRegeln;
      while sr<>nil do
        begin
        umbAinParListe(sr^.quellpar,a,a2);
        umbAinParListe(sr^.zielpar,a,a2);
        sr:=sr^.nxt;
        end;
      pr:=PTab[pr].nxt;
      end;
    end (*Aumbenennen*);
  
  begin (*umbenennen*)
  loescheeingabefeld(md);
  gpr_$text('Attribut umbenennen in? [Name] ',31,status); CursorPos(y,x); x:=x+31*rbs.zbreite;
  115:
  a2name[0]:=chr(0);
  editname(y,x,attrHL,a2name);
  if isIdent(a2name) then
    begin fpo:=formpraefixop(a2name[ord(a2name[0])]);
    if fpo>0 then 
      begin
      vspa(wrtonly,3);
      evibsD.prtreq:=true;
      evibs2(false,false,attrHL,wrtonly,a2name,a2);
      if a2=ERR then { null }
      else
	begin
	if a2=-1 then
	  begin
	  loescheeingabefeld(md);
	  gpr_$text('Bitte NEUEN Attributnamen angeben ',34,status); CursorPos(y,x);x:=x+34*rbs.zbreite;
	  goto 115;
	  end
	else { null };
	end
      end
    else
      begin
      hash(attrHL,a2name,a2,ex);
      if ex then meldefehler(15) else Aumbenennen;
      end
    end
  else
    begin
    if ord(a2name[0])=0 then { null } else meldefehler(5);
    end
  end (*umbenennen*);

  procedure aetyp;
  label 114;
  var y,x,fpo,tind,gef,pmb: integer;
      tnm: Ident;
      ex: boolean;
  begin
  isAaktParg(a,pmb,gef);
  if globaendern(pmb,gef) then
    begin
    loescheeingabefeld(md);
    gpr_$text('Name des neuen Typs?                                               ',67,status); CursorPos(y,x);x:=x+21*rbs.zbreite;
    114:
    tnm[0]:=chr(0);
    editname(y,x,typeHL,tnm);
    if isIdent(tnm) then
      begin
      fpo:=formpraefixop(tnm[ord(tnm[0])]);
      if fpo>0 then
        begin
        vsptp(rdorwrt);
        evibs2(false,false,typeHL,rdorwrt,tnm,tind);
        if tind=ERR then { null } 
        else
	  begin
	  if tind=-1 then
	    begin
	    loescheeingabefeld(md);
	    gpr_$text('Wie soll der neue Typname heissen?                                 ',67,status); CursorPos(y,x);x:=x+35*rbs.zbreite;
	    goto 114;
	    end
	  else { null };
	  end
        end
      else
        begin
        hash(typeHL,tnm,tind,ex);
        if ex then { null }
        else 
	  begin
	  TypTab[tind].name:=tnm;
	  lexeinhaengen(typeHL,tind);
	  end
        end
      end
    else
      begin
      if ord(tnm[0])<>0 then meldefehler(5) else { null };
      tind:=ERR;
      end;
    if tind<>ERR then if ATab[a].typ<>tind then
      begin
      loeschewort(md.ystern-8*md.azh-4,12*rbs.zbreite,idlaenge);
      liberA(a);
      ATab[a].typ:=tind;   
      setCursor(md.ystern-8*md.azh-4,12*rbs.zbreite);
      wrtIdent(TypTab[tind].name);
      end
    end;
  end (*aetyp*);
               
begin (*aeA*)
sw:=aktSeite=0;
Seite1;
defmaske(attrHL,1,md);
initevibsD(3,md.yinput-rbs.zhoehe,md.azh);
clearscreen;
evibsD.prtreq:=true;
Amaske(false,md,ATab[a].name);
writeikon(md.ystern-6*md.azh-4,12*rbs.zbreite,ATab[a].symbol);
setCursor(md.ystern-7*md.azh-4,12*rbs.zbreite);
case ATab[a].art of
  inh: gpr_$text('inherited',9,status);
  aux: gpr_$text('auxiliary',9,status);
  der: gpr_$text('derived',7,status);
  end (*case*);
setCursor(md.ystern-8*md.azh-4,12*rbs.zbreite);
wrtIdent(TypTab[ATab[a].typ].name);
repeat
  loescheeingabefeld(md); 
  gpr_$text('Bitte waehlen Sie! [Cursor]',28,status); 
  with md,rbs do begin
    for i:=1 to 2 do
      linie(ystern-(9+i)*azh-i*6-1,rand,ystern-(9+i)*azh-1-i*6,xpixels-rand);
    linie(ystern-10*azh-7,rand,ystern-11*azh-13,rand);
    linie(ystern-10*azh-7,xpixels div 3,ystern-11*azh-13,xpixels div 3);
    linie(ystern-10*azh-7,2*xpixels div 3,ystern-11*azh-13,2*xpixels div 3);
    linie(ystern-10*azh-7,xpixels-rand,ystern-11*azh-13,xpixels-rand);
    setCursor(ystern-11*azh-9,rand+zbreite);
    gpr_$text('ATTRIBUT UMBENENNEN',19,status);
    setCursor(ystern-11*azh-9,xpixels div 3 + zbreite);
    gpr_$text('TYP AENDERN',11,status);
    setCursor(ystern-11*azh-9,2*xpixels div 3 + zbreite); 
    gpr_$text('RICHTUNG AENDERN',16,status);
  end (* with *);
  waehledienst1(3,md.ystern-11*md.azh-12,md,dienst);
  loesche4eck(md.ystern-11*md.azh-13,md.ystern-10*md.azh-7,0,rbs.xpixels);
  case dienst of
    0:;
    1: umbenennen;
    2: aetyp;
    3: begin
	isAaktParg(a,pmb,gef);
	if globaendern(pmb,gef) then
	 begin
	 meldung(61);
	 antworte(auinde,r);
	 clearmeldung;
	 loeschewort(md.ystern-7*md.azh-4,12*rbs.zbreite,10);
         setCursor(md.ystern-7*md.azh-4,12*rbs.zbreite);
	 case r of
	   'A': begin gpr_$text('auxiliary',9,status); neuart:=aux end;
	   'I': begin gpr_$text('inherited',9,status); neuart:=inh end;
	   'D': begin gpr_$text('derived',7,status); neuart:=der end;
           otherwise;
	 end (*case*);
	 if ATab[a].art<>neuart then aeAart(a,neuart);
	 end;
        end;
    otherwise;
  end (*case*);
  ;
until (dienst=0) or (dienst=1);
if sw then Seite0;
end (*aeA*);


procedure ergAtyp(* a: integer *);
label 112;
var md: MaskenDaten;
    y,x,fpo,tind: integer;
    tnm: Ident;
    ex: boolean;
begin
defmaske(attrHL,0,md);
initevibsD(3,md.yinput-rbs.zhoehe,md.azh);
clearscreen;
evibsD.prtreq:=true;
Amaske(true,md,ATab[a].name);
setCursor(md.ystern-6*md.azh,12*rbs.zbreite);
case ATab[a].art of
  inh: gpr_$text('inherited',9,status);
  der: gpr_$text('derived',7,status);
  aux: gpr_$text('auxiliary',9,status);
  end (*case*);
loescheeingabefeld(md);
gpr_$text('Typ des Attributes? [Name] ',27,status); CursorPos(y,x);x:=x+27*rbs.zbreite;
112:
tnm[0]:=chr(0);
liesIdent(y,x,typeHL,tnm);
fpo:=formpraefixop(tnm[ord(tnm[0])]);
if fpo>0 then
  begin
  vsptp(rdorwrt);
  evibs2(false,true,typeHL,rdorwrt,tnm,tind);
  if tind=-1 then
    begin
    loescheeingabefeld(md);
    gpr_$text('Wie soll der neue Typ heissen? ',31,status); CursorPos(y,x);x:=x+31*rbs.zbreite;
    goto 112;
    end
  else { null };
  end
else
  begin
  hash(typeHL,tnm,tind,ex);
  if ex then { null }
  else
    begin
    TypTab[tind].name:=tnm;
    lexeinhaengen(typeHL,tind);
    end
  end;
ATab[a].typ:=tind;
(*symbolwahl(ATab[a].name,ATab[a].symbol);*)
end (*ergAtyp*);


procedure ergAtypen;
var a: integer;
begin
a:=AG.Attrs;
while a<>0 do
  begin
  if ATab[a].typ=0 then ergAtyp(a);
  a:=ATab[a].nxt;
  end;
end (*ergAtypen*);



procedure defA(* a: integer; var aname: Ident*);
label 116;
var md: MaskenDaten;
    c: char;
    y,x,fpo,tind: integer;
    tnm: Ident;
    sw,ex: boolean;
begin
sw:=aktSeite=0;
Seite1;
with ATab[a] do
  begin
  name:=aname;
  typ:=0;
  symbol:=0;
  end;
lexeinhaengen(attrHL,a);
defmaske(attrHL,0,md);
initevibsD(3,md.yinput-rbs.zhoehe,md.azh);
clearscreen;
evibsD.prtreq:=true;
Amaske(true,md,aname);
case ATyp_info of
undef : antworte(auinde,c);
aux :   c := 'A';
inh :   c := 'I';
der :   c := 'D'
end; (* case *)
setCursor(md.ystern-6*md.azh,12*rbs.zbreite);
case c of
  'A': begin ATab[a].art:=aux; gpr_$text('auxiliary',9,status) end;
  'I': begin ATab[a].art:=inh; gpr_$text('inherited',9,status); end;
  'D': begin ATab[a].art:=der; gpr_$text('derived',7,status) end; 
   otherwise;
  end (*case*);
loescheeingabefeld(md);
gpr_$text('Typ des Attributes? [Name] ',27,status); CursorPos(y,x);x:=x+27*rbs.zbreite;
116:
tnm[0]:=chr(0);
liesIdent(y,x,typeHL,tnm);
fpo:=formpraefixop(tnm[ord(tnm[0])]);
if fpo>0 then
  begin
  vsptp(rdorwrt);
  evibs2(false,true,typeHL,rdorwrt,tnm,tind);
  if tind=-1 then
    begin
    loescheeingabefeld(md);
    gpr_$text('Wie soll der neue Typ heissen? ',31,status); CursorPos(y,x);x:=x+31*rbs.zbreite;
    goto 116;
    end
  else { null };
  end
else
  begin
  hash(typeHL,tnm,tind,ex);
  if ex then { null }
  else
    begin
    TypTab[tind].name:=tnm;
    lexeinhaengen(typeHL,tind);
    end
  end;
ATab[a].typ:=tind;
ATab[a].symbol:=0;
loescheeingabefeld(md);
gpr_$text('Symbolzuordnung im Attributmenue.    Weiter mit "',49,status);
gibpromptchar;
gpr_$text('"',1,status);           
repeat cread(c) until c=promptchar;
if sw then Seite0;
end (*defA*);
