





procedure beschaffeP(* var index: PListe *);
begin
if PLL = nil
then new(index)
else
  begin
  index:=PLL;
  PLL:=index^.nxt
  end
end;   {beschaffeP}

procedure beschaffeA(* var index: AListe *);
begin
if ALL = nil
then new(index)
else
  begin
  index:=ALL;
  ALL:=index^.nxt
  end
end;   {beschaffeA}

procedure beschaffeHA(* var index: HAListe *);
begin
if HALL = nil
then new(index)
else
  begin
  index:=HALL;
  HALL:=index^.nxt
  end
end;   {beschaffeHA}

procedure beschaffeTyp(* var index: TypListe *);
begin
if TypLL=nil
then new(index)
else
  begin
  index:=TypLL;
  TypLL:=index^.nxt
  end
end;   {beschaffeTyp}

procedure beschaffePar(* var index: ParListe *);
begin
if ParLL = nil
then new(index)
else
  begin
  index:=ParLL;
  ParLL:=index^.nxt
  end
end;   {beschaffePar}

procedure beschaffePunkt(* var index: PunktListe *);
begin
if PunktLL = nil
then new( index )
else begin
     index:= PunktLL;
     PunktLL:= PunktLL^.nxt
     end
end;   {beschaffePunkt}

procedure beschaffeV(* var index: VokListe *);
begin
if VLL = nil
then new(index)
else
  begin
  index:=VLL;
  VLL:=index^.nxt
  end;
index^.unversA := nil
end;   {beschaffeV}

procedure beschaffeSF(* var index: SemFktListe *);
begin
if SFLL = nil
then new(index)
else
  begin
  index:=SFLL;
  SFLL:=index^.nxt
  end
end;   {beschaffeSF}

procedure beschaffevisymbol(* var index: visymbolptr *);
begin
if SymbolLL=nil then new(index) else
  begin
  index:=SymbolLL; 
  SymbolLL:=SymbolLL^.nxt;
  end;
end;

procedure gibfreivibselmt(* n: integer *);
var elem: vibselmtptr;
begin
elem:=ViBs[n];
if elem<>nil then
  begin
  elem^.lastsym:=SymbolLL;
  SymbolLL:=elem^.firstsym;
  elem^.nxt:=ViBsElmtLL;
  ViBsElmtLL:=elem;
  ViBs[n]:=nil;
  end;
end;

procedure beschaffevibselmt(* n: integer *);
var elem: vibselmtptr;
begin
if ViBs[n] <> nil then
  begin   
  gibfreivibselmt(n);
  end;
if ViBsElmtLL=nil then new(elem) else
  begin
  elem:=ViBsElmtLL;
  ViBsElmtLL:=ViBsElmtLL^.nxt;
  end;
with elem^ do
  begin
  hashind:=0; viline:='  '; firstsym:=nil; lastsym:=nil;
  end;
ViBs[n]:=elem;
end;


procedure gibALzurueck(* var al: AListe *);
var ptr: AListe;
begin
if al<>nil then
  begin
  ptr:=al;
  while ptr^.nxt<>nil do ptr:=ptr^.nxt;
  ptr^.nxt:=ALL;
  ALL:=al;
  al:=nil;
  end;
end (*gibALzurueck*);


procedure gibHALzurueck(* var al: HAListe *);
var ptr: HAListe;
begin
if al<>nil then
  begin
  ptr:=al;
  while ptr^.nxt<>nil do ptr:=ptr^.nxt;
  ptr^.nxt:=HALL;
  HALL:=al;
  al:=nil;
  end;
end (*gibALzurueck*);


procedure gibPunktLzurueck(* var al: PunktListe *);
var h: PunktListe;
begin
if al <> nil
then begin
  h:= al;
  while (h^.nxt <> nil) do h:= h^.nxt;
  h^.nxt:= PunktLL;
  PunktLL:= al;
  al:= nil
  end
end;   {gibPunktLzurueck}


procedure gibfreiHA (* var anker: HAListe; elem: HAListe *);
var h: HAListe;			      {Element muss in der Liste von anker sein}
begin
if anker = elem
then anker:= anker^.nxt 		      {Aushaengen aus der Originalliste}
else begin
     h:= anker;
     while (h^.nxt <> elem) do h:= h^.nxt;
     h^.nxt:= elem^.nxt                     {Aushaengen aus der Originalliste}
     end;
elem^.nxt:= HALL; 				        {Einfuegen in Leerliste}
HALL:= elem
end;   {gibfreiHA}



procedure gibfreiV (* n: integer; elem: VokListe *);
var h: VokListe;
begin
if elem^.typ=nont then
  begin
  gibALzurueck(elem^.spezInhA);
  gibALzurueck(elem^.spezDerA);
  gibALzurueck(elem^.unversA);
  sPausPL(n,NTTab[elem^.nt].anwendungen);
  end
else sPausPL(n,TTab[elem^.t].anwendungen);
if (PTab[n].vater = elem)
then PTab[n].vater:= nil
else if (PTab[n].soehne = elem)
     then begin
	  PTab[n].soehne:= PTab[n].soehne^.nxt;   {Aushaengen aus urspr. Liste}
	  if (PTab[n].vater <> nil)
	  then PTab[n].vater^.nxt:= PTab[n].soehne
	  end
     else begin
	  h:= PTab[n].soehne;
	  while (h^.nxt <> elem) do h:= h^.nxt;
	  h^.nxt:= elem^.nxt		           {Aushaengen aus urspr. Liste}
	  end;
elem^.nxt:= VLL; 			     {Vokabel an Leerliste zurueckgeben}
VLL:= elem
end;   {gibfreiV}

procedure gibfreiSF (* n: integer; elem: SemFktListe *);
var parl: ParListe;
    h: SemFktListe;
    i: integer;
begin
for i:= 0 to 1 do 		    {Zurueckgeben der aktuellen Parameterlisten}
  begin
  if (i=0)
  then parl:= elem^.quellpar
  else parl:= elem^.zielpar;
  if (parl <> nil)
  then begin
       while (parl^.nxt <> nil) do parl:= parl^.nxt;
       parl^.nxt:= ParLL;
       if (i=0)
       then ParLL:= elem^.quellpar
       else ParLL:= elem^.zielpar;
       end
  end;
if (PTab[n].semRegeln = elem)
then PTab[n].semRegeln:= PTab[n].semRegeln^.nxt
else begin
     h:= PTab[n].semRegeln;
     while (h^.nxt <> elem) do h:= h^.nxt;
     h^.nxt:= elem^.nxt;
     end;
elem^.nxt:= SFLL;
SFLL:= elem;
if elem^.semfkt<>IDNT then sPausPL(n,SFTab[elem^.semfkt].anwendungen);
end;   {gibfreiSF}
