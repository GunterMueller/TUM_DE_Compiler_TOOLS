





procedure expandntv (* var ntv: VokListe *);
begin
if ntv=nil then wrtERR1('expandntv[1]')
else if ntv^.typ<>nont then wrtERR1('expandntv[2]')
else
  begin with ntv^,NTTab[ntv^.nt] do
    begin
    if ntv^.konsistent then
      begin
      if spezInhA=nil then copyALft(inhAttr,spezInhA);
      if spezDerA=nil then copyALft(derAttr,spezDerA);
      end;
    end;
  end;
end (*expandntv*);


procedure comprntv (* var ntv: VokListe *);
begin
if ntv=nil then wrtERR1('comprntv[1]')
else if ntv^.typ<>nont then wrtERR1('comprntv[2]')
else
  begin with ntv^, NTTab[ntv^.nt] do
    begin
    if isgleichattr(inhAttr,spezInhA) and isgleichattr(derAttr,spezDerA) then
      begin
      ntv^.konsistent:=true;
      if sameAorder(inhAttr,spezInhA) then gibALzurueck(spezInhA);
      if sameAorder(derAttr,spezDerA) then gibALzurueck(spezDerA);
      end
    else ntv^.konsistent:=false;
    end;
  end;
end (*comprntv*);


function hatAanwdg(*a: integer): boolean*);
var pr: integer;
    hat: boolean;
    aart: Richtung;
    s: VokListe;
begin
hat:=false; 
aart:=ATab[a].art;
pr:=AG.Prods;
while (pr<>0) and (not hat) do
  begin
  with PTab[pr] do
    begin
    if aart=aux then hat:=isHAelemHAL(a,hilfsAttr)
    else
      begin
      if vater<>nil then
	begin
	expandntv(vater);
	if aart=inh then hat:=isAelemAL(a,vater^.spezInhA) else hat:=isAelemAL(a,vater^.spezDerA);
	comprntv(vater);
	end;
      s:=soehne;
      while (s<>nil) and (not hat) do
	begin
	if s^.typ=nont then
	  begin
	  expandntv(s);
	  if aart=inh then hat:=isAelemAL(a,s^.spezInhA) else hat:=isAelemAL(a,s^.spezDerA);
	  comprntv(s);
	  end;
	s:=s^.nxt;
	end (*while*);
      end;
    pr:=nxt;
    end (*with PTab*);
  end (*while pr*);
hatAanwdg:=hat;
end (*hatAanwdg*);


function hatTypanwdg(*tp:integer): boolean*);
var hat: boolean;
    a,sf,t: integer;
begin hat:=false;
a:=AG.Attrs; 
while (a<>0) and (not hat) do
  begin
  hat:=ATab[a].typ=tp;
  a:=ATab[a].nxt;
  end;
sf:=AG.SemRules;
while (sf<>0) and (not hat) do
  begin
  with SFTab[sf] do
    begin
    hat:=isTypelemTL(tp,parlist);
    if (not hat) then hat:=isTypelemTL(tp,erglist);
    sf:=nxt;
    end (*with*);
  end (*while sf*);
t:=AG.Terms;
while (t<>0) and (not hat) do
  begin
  hat:=TTab[t].typ=tp;
  t:=TTab[t].nxt;
  end;
hatTypanwdg:=hat;
end (*hatTypanwdg*);


procedure entkopple (* var sr: SemFktListe; var pl: ParListe *);
begin
with pl^ do
  begin
  attr:=0; vok:=nil; verb:=nil;
  end;
sr^.versorgt:=false;
end; (*entkopple*)

function hatSFerg (* var sr: SemFktListe): boolean *);
var l: ParListe;
    erg: boolean;
begin
if sr=nil then wrtERR1('hatSFerg')
else if sr^.semfkt=IDNT then
  begin
  with sr^ do 
    begin
    if (quellpar=nil) or (zielpar=nil) then 
      begin hatSFerg:=false;
      wrtERR1('hatSFerg')
      end
    else hatSFerg:= ((quellpar^.vok<>nil) or (quellpar^.attr<>0)) 
		and (( zielpar^.vok<>nil) or ( zielpar^.attr<>0));
    end;
  end
else
  begin
  l:=sr^.zielpar;
  erg:=false;
  while l<>nil do
    begin 
    with l^ do
      begin
      erg:=(attr<>0) or (vok<>nil);
      if erg then l:=nil else l:=l^.nxt;
      end
    end;
  hatSFerg:=erg;
  end;
end;


procedure liberA (* el: integer *);
var pr,i: integer;
    sr, s: SemFktListe;
    l: ParListe;
begin
pr:=AG.Prods;
while pr<>0 do
  begin
  sr:=PTab[pr].semRegeln;
  while sr<>nil do
    begin
    s:=sr^.nxt;
    l:=sr^.quellpar;
    for i:=1 to 2 do
      begin
      while l<>nil do
	begin
	if l^.attr=el then entkopple(sr,l);
	l:=l^.nxt;
        end;
      l:=sr^.zielpar;
      end (*for*);
    if not hatSFerg(sr) then gibfreiSF(pr,sr);
    sr:=s;
    end(*while*);
  pr:=PTab[pr].nxt;
  end (*while pr*);
end (*liberA*);


function gibVzupos(* pr,pos: integer: VokListe *);
var s: VokListe;
    snr: integer;
begin
with PTab[pr] do
  begin
  if pos=0 then
    begin
    if vater<>nil then gibVzupos:=vater else wrtERR1('gibVzupos [1]')
    end
  else
    begin
    s:=soehne;
    if s=nil then snr:=0 else snr:=1;
    while (s<>nil) and (snr<pos) do
      begin
      s:=s^.nxt;
      snr:=succ(snr);
      end;
    if s=nil then wrtERR1('gibVzupos [2]') else gibVzupos:=s
    end;
  end (*with*);
end (*gibVzupos*);
 
   
procedure listenwahl(*hl:HashListen; var istIdent: boolean; zugriff: HLZugriff; praefixop: integer; var s: Ident; var el: integer *);
var elalt,llg: integer;
    salt: Ident;
    seitenwechsel: boolean;

  procedure calldef(var s: Ident; var el: integer);
  var fpo: integer;
      ende,ex: boolean;
  begin
  s[0]:=chr(0);
  repeat
    with evibsD do loeschewort(e8+2*e9,0,79);
    gpr_$text('Wie soll das neue Element heissen?',34,status);
    with evibsD do editname(e8+2*e9,37*rbs.zbreite,hl,s);
    if isIdent(s) then
      begin fpo:=formpraefixop(s[ord(s[0])]);
      if fpo>0 then
	begin
	with evibsD do loeschewort(e8+2*e9,0,79);
	gpr_$text('===EINGABEMOEGLICHKEITEN:',25,status);
        listenwahl(hl,istIdent,seeonly,fpo,s,el);
	ende:=false;
	end
      else
	begin
	hash(hl,s,el,ex);
	if ex then 
	  begin
	  meldefehler(2);
	  ende:=false;
	  end
	else
	  begin
          case hl of
            prodHL: defP(el,s);
            nontHL: defNT(el,s);
            attrHL: defA(el,s);
            sfktHL: defSF(el,s);
            termHL: defT(el,s);
            typeHL: defptp(s,el);
            end (* case *);
          ende:=true;
	  end
	end
      end
    else
      begin
      if ord(s[0])<>0 then
	begin
	meldefehler(5);
	ende:=false;
	end
      else if istIdent then
	begin
	meldefehler(7);
	ende:=false;
	end
      else ende:=true;
      end;
  until ende;
  istIdent:=isIdent(s);
  with evibsD do loeschewort(e8+2*e9,0,79);
  gpr_$text('===EINGABEMOEGLICHKEITEN:',25,status);
  end (*calldef*);


  procedure callname(var s: Ident);
  begin
    case hl of
    prodHL: s:=PTab[el].name;
    nontHL: s:=NTTab[el].name;
    termHL: s:=TTab[el].name;
    sfktHL: s:=SFTab[el].name;
    attrHL: s:=ATab[el].name;
    typeHL: s:=TypTab[el].name;
    noList: ;
    end (*case*);
  end;

begin (* listenwahl *)
seitenwechsel:=aktSeite=0;
Seite1;
llg:=hashtablaenge(hl);
salt:=s; elalt:=el;
case hl of
  prodHL: vspp(zugriff);
  nontHL: vspnt(zugriff,praefixop);
  attrHL: vspa(zugriff,praefixop);
  sfktHL: vspsf(zugriff); 
  termHL: vspt(zugriff); 
  typeHL: vsptp(zugriff);
  end (*case*);
evibs(istIdent,hl,zugriff,s,el);
if (not istIdent) and (el=ERR) then s[0]:=chr(0) 
else
  begin
  case zugriff of
    seeonly: begin s:=salt; el:=elalt end;
    redonly: if (el>0) and (el<=llg) then callname(s)
             else wrtERR1('listenwahl: [1]');
    wrtonly: if el=-1 then calldef(s,el)
             else wrtERR1('listenwahl: [2]');
    rdorwrt: if el <> IDNT then
	     if el=-1 then calldef(s,el)
             else if (el>0) and (el<=llg) then callname(s)
             else wrtERR1('listenwahl: [3]');
    end (*case*);
  end;
if seitenwechsel then Seite0;
end (*listenwahl*);


procedure lkup(* y,x: integer; hl: HashListen; zugriff: zugriffstyp; var istIdent: boolean; var s: Ident; var el: integer; var clrscreen: boolean *);
var lg,fn,praefixop: integer;
    weiter,lapsus,id,fehler,ex: boolean;
                      c:char;

  procedure calldef(var s: Ident; var el: integer);
  begin
  case hl of
    prodHL: defP(el,s);
    termHL: defT(el,s);
    attrHL: defA(el,s);
    nontHL: defNT(el,s);
    sfktHL: defSF(el,s);
    typeHL: defptp(s,el);
    end (*case*);
  clrscreen:=true;
  end (*calldef*);

begin (*lkup*)
clrscreen:=false;
weiter := TRUE;
s[0]:=chr(0);
repeat
  lapsus:=false;
  repeat
    editname(y,x,hl,s);
    id:=isIdent(s); 
    fehler:=(istIdent or (ord(s[0])<>0)) and (not id) and (s[1]<>IDchar);
    if fehler then meldefehler(1);
  until not fehler;
  
  if id then
    begin
    lg:=ord(s[0]); praefixop:=formpraefixop(s[lg]);
    if praefixop>0 then
      begin
      s[0]:=chr(pred(lg)); (* s jetzt evtl. leer *)
      listenwahl(hl,istIdent,zugriff,praefixop,s,el);
      if (el = IDNT) then weiter := FALSE;
      clrscreen:=true;
      end
    else if weiter then
      begin (* auswahl aus den hashtabellen nicht via bildschirm *)
            (* s wohldefiniert, nicht leer *)
      hash(hl,s,el,ex); 
      fn:=8+ord(hl); if hl=typeHL then fn:=44;
      case zugriff of 
        seeonly: (* skip *);
        redonly: if not ex then
                   begin
                   meldefehler(fn); lapsus:=true;
                   end;
        wrtonly: if ex then
                   begin
                   meldefehler(fn+5); lapsus:=true;
                   end
                 else calldef(s,el);
        rdorwrt: if not ex 
                  then begin
			clearmeldung;
                        meldung( 46 );
			antworte(janein,c);
                        clearmeldung;
                        if c = 'J'
                         then calldef(s,el)
                         else s[0]:=chr(0);
                      end;
        end (* case *)
      end;
    end
  else 
    begin
    if ord(s[0])<>0 then if (hl=sfktHL) and (ord(s[0])=1) and (s[1]=IDchar) then el:=IDNT
		   else meldefehler(30);
    end;
until not lapsus; 
istIdent:=isIdent(s);
end (*lkup*);
