





procedure copyALft (* var q,z: AListe *);
var hq,hz,np: AListe;
begin
z:=nil;
hq:=q; hz:=z;
while hq<>nil do
  begin
  beschaffeA(np);
  with np^ do begin attr:=hq^.attr; nxt:=nil end;
  if hz=nil then z:=np else hz^.nxt:=np;
  hz:=np;
  hq:=hq^.nxt;
  end;
end (*copyALft*);


procedure copyHALft (* var q,z: HAListe *);
var hq,hz,np: HAListe;
begin
z:=nil;
hq:=q; hz:=z;
while hq<>nil do
  begin
  beschaffeHA(np);
  with np^ do 
    begin 
    attr:=hq^.attr; 
    vx:=hq^.vx; vy:=hq^.vy;
    X:=hq^.X; Y:=hq^.Y;
    nxt:=nil 
    end;
  if hz=nil then z:=np else hz^.nxt:=np;
  hz:=np;
  hq:=hq^.nxt;
  end;
end (*copyHALft*);


procedure aPzuPL (* pr: integer; var plist: PListe *);
var pl: PListe;
begin
beschaffeP(pl);
pl^.prod:=pr;
pl^.nxt:=plist;
plist:=pl;
end;


procedure sPausPL (* pr: integer; var prodl: PListe *);
var pl, apl: PListe;
    fertig: boolean;
begin
pl:=prodl; apl:=nil; fertig:=false;
while (pl<>nil) and (not fertig) do
  begin
  if pl^.prod=pr then
    begin
    fertig:=true;
    if apl=nil then prodl:=pl^.nxt
	       else apl^.nxt:=pl^.nxt;
    pl^.nxt:=PLL; PLL:=pl;
    end
  else
    begin
    apl:=pl;
    pl:=pl^.nxt;
    end;
  end;
if not fertig then wrtERR1( 'sPausPL');
end (*sPausPL*);


procedure sAausAL (* el: integer; var al: AListe; var pos: integer *); 
var ptr, ptralt: AListe;
begin
if al=nil then pos:=0
else
  begin
  ptralt:=nil;
  ptr:=al; 
  pos:=1;
  while (ptr^.attr<>el) and (ptr^.nxt<>nil) do
    begin
    pos:=succ(pos);
    ptralt:=ptr; 
    ptr:=ptr^.nxt;
    end;
  if ptr^.attr=el then
    begin
    if ptralt=nil then al:=al^.nxt else ptralt^.nxt:=ptr^.nxt;
    ptr^.nxt:=ALL; ALL:=ptr;
    end
  else pos:=0
  end
end (* sAausAL *); 


procedure sHAausHAL(* a: integer; var al: HAListe *);
var ptr,ptralt: HAListe;
begin
if al<>nil then
  begin
  ptralt:=nil;
  ptr:=al;
  while (ptr^.attr<>a) and (ptr^.nxt<>nil) do
    begin
    ptralt:=ptr;
    ptr:=ptr^.nxt;
    end;
  if ptr^.attr=a then
    begin
    if ptralt=nil then al:=al^.nxt else ptralt^.nxt:=ptr^.nxt;
    ptr^.nxt:=HALL; HALL:=ptr;
    end;
  end;
end (*sHAausHAL*);

procedure aAzuAL (* (a: integer; var pos: integer; var al: AListe; var neu: boolean); *);
var cp, ins, np: AListe;
    cpos: integer;
begin
cp:=al; ins:=nil; cpos:=0; neu:=true;
while cp<>nil do
  begin cpos:=succ(cpos);
  if (cp^.attr=a) then
    begin neu:=false; cp:=nil end
  else
    begin
    if (pos=0) or (cpos<pos) then ins:=cp;
    cp:=cp^.nxt;
    end;
  end;
if neu then 
  begin (* element ex. bisher noch nicht *)
  if (pos=0) or (pos=succ(cpos)) then
    begin (* anfuegen ans ende der liste *)
    if pos=0 then pos:=succ(cpos);
    beschaffeA(np);
    with np^ do begin attr:=a; nxt:=nil end;
    if ins=nil then al:=np else ins^.nxt:=np;
    end
  else if pos<=cpos then
    begin (*einfuegen*)
    beschaffeA(np);
    np^.attr:=a;
    if ins=nil then begin np^.nxt:=al; al:=np end
    else begin np^.nxt:=ins^.nxt; ins^.nxt:=np end
    end
  else
    begin
    wrtERR1( 'aAzuAL[1]');
    pos:=-cpos;
    end
  end
else
  begin (*element war bereits vorhanden *)
  if pos=0 then pos:=cpos
  else if pos<>cpos then
    begin
    pos:=-cpos;
    end
  end
end (*aAzuAL*);


function isAelemAL (*a: integer; al: AListe): boolean*);
var v: boolean;
    l: AListe;
begin
v:=false;
l:=al;
while l<>nil do
  begin
  if l^.attr=a then begin v:=true; l:=nil end
  else l:=l^.nxt;
  end;
isAelemAL:=v;
end;


function isHAelemHAL (*a: integer; al: HAListe): boolean*);
var v: boolean;
    l: HAListe;
begin
v:=false;
l:=al;
while l<>nil do
  begin
  if l^.attr=a then begin v:=true; l:=nil end
  else l:=l^.nxt;
  end;
isHAelemHAL:=v;
end;


function isTypelemTL(*tp: integer; tl: TypListe): boolean*);
var l: TypListe;
    iselem: boolean;
begin
l:=tl; iselem:=false;
while l<>nil do
  begin
  iselem:=tl^.typ=tp;
  if iselem then l:=nil else l:=l^.nxt;
  end;
isTypelemTL:=iselem;
end (*isTypelemTL*);


function isgleichattr (*var al1,al2: AListe): boolean*);
var v: boolean;
    l1, l2: AListe;
begin
if (al1=nil) and (al2=nil) then isgleichattr:=true
else if (al1=nil) or (al2=nil) then isgleichattr:=false
else
  begin
  l1:=al1; l2:=al2;
  repeat
    v:=isAelemAL(l1^.attr,al2) and isAelemAL(l2^.attr,al1);
    l1:=l1^.nxt; l2:=l2^.nxt;
  until (not v) or (l1=nil) or (l2=nil);
  if not v then isgleichattr:=false 
  else isgleichattr:=(l1=nil) and (l2=nil)
  end;
end (*isgleichattr*);


function sameAorder(*var al1, al2: AListe): boolean*);
(* al1 und al2 von gleicher laenge! *)
var l1, l2: AListe;
    v: boolean; 
begin
l1:=al1; l2:=al2; v:=true;
while (l1<>nil) and v do
  begin
  v:=l1^.attr=l2^.attr;
  l1:=l1^.nxt; l2:=l2^.nxt;
  end;
sameAorder:=v;
end;

procedure sHAausP (* a,pr: integer *);
begin
sHAausHAL(a,PTab[pr].hilfsAttr);
sHAausHAL(a,PTab[pr].unversHAttr);
end;


function lgtl(*anker: TypListe): integer*);
var cp: TypListe;
    anzel: integer;
begin
cp:=anker; anzel:=0;
while cp<>nil do
  begin
  cp:=cp^.nxt;
  anzel:=succ(anzel);
  end;
lgtl:=anzel;
end (*lgtl*);


function sameAorderR(*a: integer; var al1,al2: AListe): boolean*);
(* al1, al2 muessen von gleicher laenge sein *)
var v: boolean;
    l1,l2: AListe;
begin
l1:=al1; l2:=al2;
v:=true;
while (l1<>nil) and (l2<>nil) and v do
  begin
  if l1^.attr=a then
    begin
    l1:=l1^.nxt;
    if l2^.attr=a then l2:=l2^.nxt
    end
  else if l2^.attr=a then l2:=l2^.nxt
  else
    begin
    v:=l1^.attr=l2^.attr;
    l1:=l1^.nxt; l2:=l2^.nxt
    end;
  end;
sameAorderR:=v;
end (*sameAorderR*);

function lgAL(*var al: AListe): integer*);
var l: AListe;
    lg: integer;
begin
l:=al; lg:=0;
while l<>nil do
  begin
  lg:=succ(lg);
  l:=l^.nxt;
  end;
lgAL:=lg;
end (*lgAL*);


procedure umbAinAListe(* var al: AListe; el1,el2: integer *);
var hz: AListe;
begin
hz:=al;
while hz<>nil do
  begin
  if hz^.attr=el1 then hz^.attr:=el2;
  hz:=hz^.nxt;
  end;
end;


procedure umbHAinHAListe(* var al: HAListe; el1,el2: integer *);
var hz: HAListe;
begin
hz:=al;
while hz<>nil do
  begin
  if hz^.attr=el1 then hz^.attr:=el2;
  hz:=hz^.nxt;
  end;
end;


procedure umbAinParListe (* var pl: ParListe; el1,el2: integer *);
var hz: ParListe;
begin
hz:=pl;
while hz<>nil do
  begin
  if hz^.attr=el1 then hz^.attr:=el2;
  hz:=hz^.nxt;
  end;
end;


function totgeweiht (*sr: SemFktListe; ap: ParListe): boolean*);
var pl: ParListe;
    res: boolean;
begin
res:=true;
with sr^ do
  begin
  pl:=zielpar;
  while pl<>nil do
    begin
    if pl=ap then pl:=pl^.nxt
    else if (pl^.vok=nil) and (pl^.attr=0) then pl:=pl^.nxt
    else 
      begin
      res:=false;
      pl:=nil;
      end
    end
  end;
totgeweiht:=res;
end (*totgeweiht*);


procedure hatparambindung (* sf, ppos: integer; var pmb: integer; var gef: integer *);
var ppr: AListe;
    i,pr: integer;
    sr: SemFktListe;
    pl: ParListe;
begin
pmb:=0; gef:=0;
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
      if sr^.semfkt=sf then
	begin
	if ppos<0 then pl:=sr^.quellpar else pl:=sr^.zielpar;
	for i:=1 to pred(abs(ppos)) do pl:=pl^.nxt;
	if (pl^.attr<>0) or (pl^.vok<>nil) then 
	  begin
	  pmb:=succ(pmb);
	  if ppos>0 then if totgeweiht(sr,pl) then gef:=succ(gef);
	  end
	end;
      sr:=sr^.nxt;
      end;
    end (*with*);
  end (*while ppr*);
end (*hatparambindung*);


procedure isAaktParl(* a,pr,nt: integer; var pmb: integer; var gef: integer *);
var sr: SemFktListe;
    pl: ParListe;
  
  function betroffen: boolean;
  begin
  with pl^ do
    begin
    if attr<>a then betroffen:=false
    else
      begin
      if nt=0 then betroffen:=true
      else
	begin
	if vok<>nil then if vok^.typ=nont then betroffen:=vok^.nt=nt
					  else betroffen:=false
		    else betroffen:=false
	end
      end
    end
  end (*betroffen*);

begin (*isAaktParl*)
pmb:=0; gef:=0;
sr:=PTab[pr].semRegeln;
while sr<>nil do
  begin
  pl:=sr^.quellpar;
  while pl<>nil do
    begin
    if betroffen then pmb:=succ(pmb);
    pl:=pl^.nxt;
    end;
  pl:=sr^.zielpar;
  while pl<>nil do
    begin
    if betroffen then
      begin
      pmb:=succ(pmb);
      if sr^.semfkt<>IDNT then if totgeweiht(sr,pl) then gef:=succ(gef);
      end;
    pl:=pl^.nxt;
    end;
  sr:=sr^.nxt;
  end;
end (*isAaktParl*);


procedure isAaktParg(* a: integer; var pmb: integer; var gef: integer *);
const NTbeliebig=0;
var pr: integer;
    lpmb, lgef: integer;
begin
pmb:=0; gef:=0;
pr:=AG.Prods;
while pr<>0 do
  begin
  isAaktParl(a,pr,NTbeliebig,lpmb,lgef);
  pmb:=pmb+lpmb; gef:=gef+lgef;
  pr:=PTab[pr].nxt;
  end;
end (*isAaktPar *);


procedure isAaktParNT(* a,nt: integer; var pmb: integer; var gef: integer *);
var lpmb, lgef: integer;
    vk: AListe;
begin
pmb:=0; gef:=0;
vk:=inPvorkommen(NTTab[nt].anwendungen);
while vk<>nil do
  begin
  isAaktParl(a,vk^.attr,nt,lpmb,lgef);
  pmb:=pmb+lpmb; gef:=gef+lgef;
  vk:=vk^.nxt;
  end;
end;
