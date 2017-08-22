



                          
var
  connv  : pgm_$connv {##:=
           [stream_$stdin, stream_$stdout,
            stream_$errin, stream_$errout]};
  handle : pgm_$proc; 
  name,  argument : pgm_$arg; 
  argv   : pgm_$argv;


procedure CShell;
var direction: gpr_$direction_t;
begin
zurueck; 
name.chars := '/bin/csh';
    name.len  := 8;
    argument.chars := '-i';
    argument.len  := 2; 
                    
    {load the argument vector w/ addresses}
    argv[0] := ADDR(name);
    argv[1] := ADDR(argument);
pgm_$invoke('/bin/csh',
                8,
                2, argv,       {no arguments}
                4,
                connv,      {std. streams}
                [pgm_$wait],
                handle,
                status) ; 
terminit;
gpr_$inq_text(font_id_orig,direction,status);
gpr_$load_font_file(fontname,fontnamelen,font_id_set1,status);
end (*CShell*);

procedure attributberechnung;
var zeilen, spalten, dienstnr, y, x: integer;
    zuldienstnrn: intset;
    vsf: SemFktListe;
  
  procedure identifiziereSF;
  const plusaktpar=true;
  var sr,sralt: SemFktListe;
      y,x: integer;
  begin
  loeschemenue(Attrberechnung);
  sralt:=nil;
  repeat
    SFanklicken(sr,y,x);
    if sralt<>sr then
      begin
      if sralt<>nil then loeschesignatur(plusaktpar,rbs.uRandvBild-gibazh(IconsUeberText),sralt^.semfkt);
      if sr<>nil then 
        begin
        signatur1(sr);
        sralt:=sr;
        end
      end
  until sr=nil;
  wrtmenue(Attrberechnung);
  end (* identifiziereSF *);

  procedure identifiziereA;
  var y,x,y2,x2,a: integer;
      abbruch: boolean;
      v: VokListe;
  begin
  loeschemenue (Attrberechnung);
  repeat
    meldung(35);
    meldung(44);
    leave_meldung;
    CursorPos(y,x);
    fadenkreuz (y,x,abbruch);
    with rbs do loesche4eck(uRandvBild-gibazh(IconsUeberText)-3,uRandvBild,0,xpixels);
    if not abbruch then
      begin
      bestimmeTermoderAttr(y,x,v,a);
      setCursor(rbs.uRandvBild-gibazh(IconsUeberText),0);
      if a<>0 then
        begin
        gpr_$text(' Identifiziert: Attribut ',25,status);
        wrtIdent(ATab[a].name); gpr_$text(' ',1,status);
        CursorPos(y2,x2);x2:=x2+(27+ord(ATab[a].name[0]))*rbs.zbreite; 
        setCursor(y2,x2+ASymb.breite+rbs.zbreite);
        gpr_$text(': Typ ',6,status); wrtIdent(TypTab[ATab[a].typ].name);
        case ATab[a].art of
  	  inh: gpr_$text(' inherited',10,status);
  	  der: gpr_$text(' derived',8,status);
  	  aux: gpr_$text(' auxiliary',10,status);
  	  end (*case*);
        writeikon(y2,x2,ATab[a].symbol);
        end;
      end;
  until abbruch;
  clearmeldung;
  wrtmenue(Attrberechnung);
  end (*identifiziereA*);

begin (* attributberechnung *)
defmenue(Attrberechnung,zeilen,spalten,zuldienstnrn);
wrtmenue(Attrberechnung);
repeat
  waehledienst(Attrberechnung,dienstnr);
  case dienstnr of
    0: begin
       loeschemenue(Attrberechnung);
       semFkteinfuehren;
       wrtmenue(Attrberechnung);
       end;
    1: identifiziereSF;
    2: begin
       realeKoord(aktPNr);
       zeichneProduktion;
       wrtmenue(Attrberechnung);
       end;
    3: begin (*parameterversorgung*)
       SFanklicken(vsf,y,x);
       if vsf<>nil then
	 begin
	 loeschemenue(Attrberechnung);
	 signatur1(vsf);
	 ParVersorgungaendern(vsf);
         wrtmenue(Attrberechnung);
	 end;
       end;
    4: identifiziereA;
    5: ;
    end (*case*);
until dienstnr=5;
loeschemenue(Attrberechnung);
end (*attributberechnung*);


procedure gestaltung;
var dx, dy, zeilen,spalten,dienstnr: integer;
    zuldienstnrn: intset;
    hattr: HAListe;
    sf: SemFktListe;
    abbruch: boolean;
    c1:char;
begin
defmenue(Gestalten,zeilen,spalten,zuldienstnrn);
wrtmenue(Gestalten);
repeat
  waehledienst(Gestalten,dienstnr);
  case dienstnr of
    0: (*sem.Fkt.verschieben*)
       begin
       SFanklicken(sf,dy,dx);
       if sf<>nil
        then begin
              if SFTab[sf^.semfkt].issynfkt
               then begin
	             meldung(58);
		     antworte(janein,c1);
                     if c1='J'
                      then sf^.gedreht:=not sf^.gedreht;
		     clearmeldung;
                    end; 
               if (sf<>nil) then SFpositionieren(sf,dy,dx,false,abbruch);
              end;
       end;
    1: (*auxiliary verschieben*)
       begin
       HAanklicken(hattr,dx,dy);
       if hattr<>nil then HApositionieren(hattr,dy,dx,false,abbruch);
       end;
    2: (*vokabel verschieben*)
       Vokabelverschieben;   
    3: (*linienfuehrung aendern*)
       linienfuehrung;
    4: begin
	if Verbindung=Poly then Verbindung:=Spline else Verbindung:=Poly;
	zeichneProduktion;
       end;
    5: standardpositionierung;
    6: begin
       realeKoord(aktPNr);
       zeichneProduktion;
       end;
    7: begin
       EXTENSIV := not EXTENSIV;
       zeichneProduktion
       end;
    8: ;
    end (*case*);
  if (dienstnr=4) or (dienstnr=7) then loeschemenue(Gestalten);
  if dienstnr in [3,4,6,7] then wrtmenue(Gestalten);
until dienstnr=8;
loeschemenue(Gestalten);
end (*gestaltung*);


function gibAzuVp(* vok: VokListe; pos: integer): integer; *);
var i,lg: integer;
    al: AListe;
begin
if (vok^.typ=term) or (pos=0) then wrtERR1('gibAzuVp[1]')
else
  begin
  with vok^, NTTab[vok^.nt] do
    begin
    if vok^.konsistent then
      begin
      if pos<0 then
	begin
	if spezInhA=nil then al:=inhAttr else al:=spezInhA
	end
      else
	begin
	if spezDerA=nil then al:=derAttr else al:=spezDerA
	end;
      end
    else
      begin
      if pos<0 then al:=spezInhA else al:=spezDerA;
      end;
    lg:=lgAL(al);
    if (lg<abs(pos)) then wrtERR1('gibAzuVp[2]')
    else 
      begin
      for i:=1 to pred(abs(pos)) do al:=al^.nxt;
      gibAzuVp:=al^.attr;
      end;
    end (*with*);
  end;
end; (*gibAzuVp*)


procedure aendereattributierung;
var zeilen, spalten, dienstnr, vpos, apos, anr: integer;
    zuldienstnrn: intset;
    ntv: VokListe;
    kontext: vilinetyp;
    istIdent,clrscreen, gestrichen, aegrafik: boolean;
    aname: Ident;
  
  procedure aeAreihgl;
  var a,y0,y1,y2,vpos,apos,y,x,aposneu: integer;
      ntv: VokListe;

    procedure loescheAsymbol;
    var lg,yu,xp: integer;
    begin
    lg:=dist(succ(ord(NTTab[ntv^.nt].name[0])));
    yu:=ntv^.Y-ASymb.hoehe div 2;
    if apos<0 then xp:=ntv^.X+apos*2*ASymb.breite else xp:=ntv^.X+lg+succ((2*apos-1)*ASymb.breite);
    male4eck(true,yu,yu+ASymb.hoehe-1,xp,xp+ASymb.breite);
    end (*loescheAsymbol*);
    
    
    procedure updateParbindgn(loesch: boolean; ntv: VokListe; al: AListe);
    var l: AListe;
        sr: SemFktListe;
        pl: ParListe;
        b: boolean;
    begin
    if loesch then gpr_$set_draw_value(-2,status);;
    l:=al;
    while l<>nil do
      begin
      sr:=PTab[aktPNr].semRegeln;
      while sr<>nil do
        begin
        pl:=sr^.quellpar;
        for b:=false to true do
          begin
          while pl<>nil do
    	    begin
    	    if pl^.vok=ntv then if pl^.attr=l^.attr then
    	      begin
	      if sr^.semfkt=IDNT then zeichneParVersorgung(sr,sr^.zielpar,true)
	      else if SFTab[sr^.semfkt].issynfkt then zeichneParVersSynfkt(sr,pl,b)
                                         else zeichneParVersorgung(sr,pl,b);
    	      end;
            pl:=pl^.nxt;
    	    end (*while pl*);
          pl:=sr^.zielpar;
          end (*for*);
        sr:=sr^.nxt;
        end (*while sr*);
      l:=l^.nxt;
      end (*while l*);
    if loesch then gpr_$set_draw_value(color_base,status);;
    end (*updateParbindgn*);


    procedure umordnen;
    var absaposneu,pos: integer;
	neu: boolean;
    begin
    if abs(aposneu)>abs(apos) then absaposneu:=pred(abs(aposneu)) else absaposneu:=abs(aposneu);
    if abs(apos)=absaposneu then {null}
    else
      begin
      expandntv(ntv);
      if apos<0 then
	begin
	updateParbindgn(true,ntv,ntv^.spezInhA);
	sAausAL(a,ntv^.spezInhA,pos);
	aAzuAL(a,absaposneu,ntv^.spezInhA,neu);
	updateParbindgn(false,ntv,ntv^.spezInhA);
	end
      else
	begin
	updateParbindgn(true,ntv,ntv^.spezDerA);
	sAausAL(a,ntv^.spezDerA,pos);
	aAzuAL(a,absaposneu,ntv^.spezDerA,neu);
	updateParbindgn(false,ntv,ntv^.spezDerA);
	end;
      comprntv(ntv);
      end;
    end (*umordnen*);

  begin
  with rbs do
    begin
    y0:=uRandvBild-zhoehe;
    y1:=y0-zhoehe-5;
    y2:=y1-zhoehe-5;
    setCursor(y0,0);
    gpr_$text(' Attributreihenfolge eines Nonterminals aendern',47,status);
    linie(y0-3,dist(1),y0-3,dist(47));
    repeat
      loesche4eck(y1,pred(y1+zhoehe),0,xpixels);
      setCursor(y1,0);
      gpr_$text(' Bitte bestimmen Sie das betreffende Nonterminal [Cursor] ',58,status);
      regel(y2,aktPNr);
      Pcontr(y2,aktPNr,'s',vpos);
      if vpos<0 then {null}
      else
	begin
	ntv:=gibVzupos(aktPNr,vpos);
	if ntv^.typ=term then meldefehler(34)
	else
	  begin
	  repeat
	    loesche4eck(y1,pred(y1+zhoehe),0,xpixels);
	    setCursor(y1,0);
	    gpr_$text(' Bitte bestimmen Sie ein an anderer Stelle einzufuegendes Attribut [Cursor]',75,status);
	    NTvContr('s',vpos=0,ntv,apos);
	    if apos=0 then {null}
	    else
	      begin
	      a:=gibAzuVp(ntv,apos);
	      loescheAsymbol;
	      repeat
		loesche4eck(y1,pred(y1+zhoehe),0,xpixels);
		setCursor(y1,0);
		gpr_$text(' Bitte ordnen Sie das Attribut ',31,status); CursorPos(y,x);x:=x+31*rbs.zbreite;
                setCursor(y,x+ASymb.breite);
                gpr_$text(' an neuer Stelle ein',20,status);
		writeikon(y,x,ATab[a].symbol);
		NTvContr('e',vpos=0,ntv,aposneu);
		if (aposneu=0) then meldefehler(7)
		else if (apos*aposneu<0) then meldefehler(36)
		else
		  begin
		  umordnen;
		  zeichneVokabel(ntv);
		  end;
		;
	      until not ((aposneu=0) or (apos*aposneu<0));
	      end;
	    ;
	  until apos=0
	  end
	end
      ;
    until vpos<0;
    end;
  end (*aeAreihgl*);

begin
with PTab[aktPNr], rbs do
  begin
  if (vater=nil) and (soehne=nil) then meldefehler(18)
  else
    begin
    defmenue(Attributeaendern,zeilen,spalten,zuldienstnrn);
    repeat
      wrtmenue(Attributeaendern);
      waehledienst(Attributeaendern,dienstnr);
      case dienstnr of
	0: begin
           loeschemenue(Attributeaendern);
	   setCursor(uRandvBild-zhoehe,0);
	   gpr_$text(' ERGAENZE ATTRIBUT (lokal)',26,status);
	   male4eck(false,uRandvBild-zhoehe-3,uRandvBild-zhoehe-2,0,dist(26));
	   waehleAv(uRandvBild-2*zhoehe-5,'e',vpos,apos);
	   if apos<>0 then
	     begin
	     setCursor(uRandvBild-zhoehe,28*zbreite);
	     gpr_$text('Attributname?',13,status);
	     ntv:=gibVzupos(aktPNr,vpos);
	     if apos<0
		then begin
		     kontext:='INFO: Gesucht: Inherited Attribut fuer Nonterminalvorkommen';
		     ATyp_info := inh
		     end
	        else begin
		     kontext:='INFO: Gesucht: Derived Attribut fuer Nonterminalvorkommen';
		     ATyp_info := der
		     end;
             insert(NTTab[ntv^.nt].name,kontext,62);
	     initkontext;
	     ViBs[minvibslg]^.viline:=kontext;
	     istIdent:=false;
	     aname[0]:=chr(0);
	     lkup(uRandvBild-zhoehe,43*zbreite,attrHL,rdorwrt,istIdent,aname,anr,clrscreen);
	     ATyp_info := undef;
	     if istIdent then
	       begin
	       if apos<0 then
		 begin
		 if (ATab[anr].art<>inh) then meldefehler(36)
		 else
		   begin
		   aAzuNTl(anr,abs(apos),ntv,aegrafik);
                   if (not LAZY) and aegrafik then
                     begin
		     realeKoord(aktPNr);
		     zeichneProduktion;
		     end
		   end
		 end
	       else (*apos>0*)
		 begin
		 if (ATab[anr].art<>der) then meldefehler(36)
		 else
		   begin
		   aAzuNTl(anr,apos,ntv,aegrafik);
		   if (not LAZY) and aegrafik then
		     begin
		     realeKoord(aktPNr);
		     zeichneProduktion;
		     end;
		   end;
		 end;
	       end (*istIdent*);
	     end (*apos<>0*);
	   loeschemenue(Prodbearbeiten);
	   end;
	1: begin
	   loeschemenue(Attributeaendern);
	   setCursor(uRandvBild-zhoehe,0);
	   gpr_$text(' STREICHE ATTRIBUT (lokal)',26,status);
	   male4eck(false,uRandvBild-zhoehe-3,uRandvBild-zhoehe-2,0,dist(26));
	   waehleAv(uRandvBild-2*zhoehe-5,'s',vpos,apos);
	   if apos<>0 then
	     begin
	     ntv:=gibVzupos(aktPNr,vpos);
	     sAausNTl(aktPNr,gibAzuVp(ntv,apos),ntv,gestrichen);
	     if gestrichen then
	       begin 
	       if not LAZY then
		 begin
	         realeKoord(aktPNr);
                 zeichneProduktion;
		 end;
	       end;
	     end;
	   loeschemenue(Prodbearbeiten);
	   end;
	2: begin
	   loeschemenue(Attributeaendern);
	   aeAreihgl;
	   loeschemenue(Prodbearbeiten);
	   end;
        3: neuDefHA;
        4: loescheHA;
        5: ;
	end (*case*);
    until dienstnr=5;
    loeschemenue(Attributeaendern);
    end;
  end;
end (*aendereattributierung*);


procedure vokabeleinfuegen;
var j, yname, xname, vind, pos: integer;
    c: char;
    hl: HashListen;
    istIdent, clrscreen: boolean;
    kontext: vilinetyp;
    v: Ident;

  function y (n: integer): integer;
  begin with rbs do
  y:= uRandvBild-succ(n)*(zhoehe+5)
  end;

begin (*vokabeleinfuegen*)
with rbs do
  begin
  repeat
    male4eck(false,y(0)+zhoehe+3,y(0)+zhoehe+3,0,xpixels);
    linie(y(0)-10,zbreite,y(0)-10,xpixels);
    setCursor(y(0),0);
    gpr_$text(' VOKABEL EINFUEGEN',18,status);
    setCursor(y(2),0);
    gpr_$text(' Bitte waehlen Sie Vokabeltyp bzw. Eingabeende [Cursor]',55,status);
    setCursor(y(3),2*zbreite); gpr_$text('Typ = Nonterminal',17,status);
    setCursor(y(3),24*zbreite); gpr_$text('Typ = Terminal',14,status);
    setCursor(y(3),46*zbreite); gpr_$text('Einfuegen abbrechen',19,status);
    j:=1;
    repeat
      invertBild((1+(j-1)*22)*zbreite,y(3)-4,21*zbreite,zhoehe);
      move_read(c);                        
      invertBild((1+(j-1)*22)*zbreite,y(3)-4,21*zbreite,zhoehe);
        case c of
         '4': if j > 1 then j := pred(j);
	 '6': if j < 3 then j := succ(j);
	 '0': j := 3;
	end
    until (c=trz) or (c='0');
    if j=1 then hl:=nontHL 
    else if j=2 then hl:=termHL
    else hl:=noList;
    if hl<>noList then
      begin
      loesche4eck(y(3)-3,y(0)-4,0,xpixels);
      loesche4eck(y(0),y(0)+zhoehe,0,xpixels); setCursor(y(0),0);
      if hl=nontHL then gpr_$text(' NONTERMINAL',12,status) else gpr_$text(' TERMINAL',9,status);
      gpr_$text(' EINFUEGEN  mit Namen ',22,status);
      CursorPos(yname,xname);
      xname:=xname+35*rbs.zbreite;
      istIdent:=false;
      wrtPtoktxt(aktPNr);
      kontext:=': Vokabel einfuegen';
      catenate (ViBs[minvibslg]^.viline,kontext);
      lkup(yname,xname,hl,rdorwrt,istIdent,v,vind,clrscreen);
      if istIdent then
	begin
	setCursor(y(1),0);
	gpr_$text(' Bitte Einfuegeposition markieren [CURSOR]',42,status);
	regel(y(2),aktPNr);
	Pcontr(y(2),aktPNr,'e',pos);
	if pos>=0 then
	  begin
	  if (pos=0) and (hl=termHL) then meldefehler(33)
          else
	    begin
	    ergPumVp(aktPNr,vind,hl,pos);
	    if not LAZY then
	      begin
	      realeKoord(aktPNr);
	      zeichneProduktion;
	      end;
	    end;
	  end (*pos>=0*);
	end (*istIdent*);
      end (*hl<>noList*);
    with rbs do male4eck(true,0,uRandvBild,0,xpixels);
  until j=3;
  end (*with*);
end (*vokabeleinfuegen*);


procedure vokabelloeschen;
const zabst=10;
var y0,y1,y2,pos: integer;
begin
with PTab[aktPNr], rbs do
  begin
  if (soehne=nil) and (vater=nil) then begin beep;beep end
  else
    begin
    y0:=uRandvBild-zabst-zhoehe;
    male4eck(false,uRandvBild-zabst,uRandvBild-zabst+3,0,xpixels);
    linie(y0-10,0,y0-10,xpixels);
    setCursor(y0,0); gpr_$text(' VOKABEL LOESCHEN',17,status);
    y1:=y0-zhoehe-2*zabst;
    setCursor(y1,0);
    gpr_$text(' Bitte Position bestimmen [CURSOR]',34,status);
    y2:=y1-zhoehe-zabst;
    regel(y2,aktPNr);
    Pcontr(y2,aktPNr,'s',pos);
    if pos>=0 then
      begin
      sVausPp(aktPNr,pos);
      if not LAZY then
	begin
        realeKoord(aktPNr);
	zeichneProduktion;
	end;
      end;
    end;
  end; (*with*)
male4eck(true,0,rbs.uRandvBild,0,rbs.xpixels);
end (*vokabelloeschen*);


procedure vokabelersetzen;
var j, yname, xname, vind, pos: integer;
    c: char;
    hl: HashListen;
    vokart,v: Ident;
    istIdent, clrscreen: boolean;
    kontext: vilinetyp;

  function y (n: integer): integer;
  begin with rbs do
  y:= uRandvBild-succ(n)*(zhoehe+5)
  end;

begin (*vokabelersetzen*)
with PTab[aktPNr], rbs do
  begin
  if (vater=nil) and (soehne=nil) then begin beep; beep end
  else
    begin
    repeat
      male4eck(false,y(0)+zhoehe+3,y(0)+zhoehe+3,0,xpixels);
      linie(y(0)-10,zbreite,y(0)-10,xpixels);
      setCursor(y(0),0);
      gpr_$text(' VOKABEL ERSETZEN',17,status);
      setCursor(y(2),0);
      gpr_$text(' Typ der ERSETZENDEN Vokabel bzw. Eingabeende?',46,status); 
      setCursor(y(2)-rbs.zhoehe,0);
      gpr_$text(' [2 4=Cursor,',13,status); gibPromptChar; gpr_$text('uebernimmt]',11,status);
      setCursor(y(4),2*zbreite); gpr_$text('Typ = Nonterminal',17,status);
      setCursor(y(4),24*zbreite); gpr_$text('Typ = Terminal',14,status);
      setCursor(y(4),46*zbreite); gpr_$text('Ersetzen abbrechen',18,status);
      j:=1;
      repeat
        invertBild((1+(j-1)*22)*zbreite,y(4)-4,21*zbreite,zhoehe);
        move_read(c);                 
        invertBild((1+(j-1)*22)*zbreite,y(4)-4,21*zbreite,zhoehe);
        case c of
         '4': if j > 1 then j := pred(j);
	 '6': if j < 3 then j := succ(j);
	 '0': j := 3;
	end
      until ((c=trz) or (c='0'));
      if j=1 then hl:=nontHL else if j=2 then hl:=termHL else hl:=noList;
      if hl<>noList then
	begin dekodhl(hl,vokart);
	male4eck(true,0,y(1),0,xpixels); 
	setCursor(y(0),19*zbreite);
	gpr_$text('durch ',6,status); wrtIdent(vokart);
    gpr_$text(' mit Namen ',11,status);
	CursorPos(yname, xname); 
    xname:=xname+(17+ord(vokart[0]))*rbs.zbreite;
	istIdent:=false;
	wrtPtoktxt(aktPNr);
	kontext:=': Vokabel ersetzen';
	catenate(ViBs[minvibslg]^.viline,kontext);
	lkup(yname,xname,hl,rdorwrt,istIdent,v,vind,clrscreen);
	if istIdent then
	  begin
	  setCursor(y(1),0);
	  gpr_$text(' Bitte Position markieren [CURSOR]',34,status);
	  regel(y(2),aktPNr);
	  Pcontr(y(2),aktPNr,'s',pos);
	  if pos>=0 then
	    begin
	    if (pos=0) and (hl=termHL) then meldefehler(33)
	    else
	      begin
	      ersVinPp(aktPNr,vind,hl,pos);
	      if not LAZY then
		begin
	        realeKoord(aktPNr);
	        zeichneProduktion;
		end;
	      end;
	    end (*pos>=0*);
	  end (*istIdent**);
	end (*if hl<>noList*);
      ;
    until j=3;
    end;
  end;
with rbs do male4eck(true,0,uRandvBild,0,xpixels);
end (*vokabelersetzen*);


procedure produktionbearbeiten (* pr: integer *);
var zeilen,spalten,prnr,dienstnr: integer;
    zuldienstnrn: intset;
    prn: Ident;
    c1: char;
begin
aktPNr:=pr;
{Seite0;}
clearscreen;
Grammatikspeichern(AGtmp);
realeKoord(aktPNr);
zeichneProduktion;
dienstnr:=0;
defmenue(Prodbearbeiten,zeilen,spalten,zuldienstnrn);
wrtmenue(Prodbearbeiten);
repeat
  waehledienst(Prodbearbeiten,dienstnr);
  if dienstnr in [0,1,3,4,7,9,10] then loeschemenue(Prodbearbeiten);
  case dienstnr of
    0: attributberechnung;
    1: gestaltung;
    2: begin (*Pspeichern*)
       Grammatikspeichern(AGtmp); 
       meldung( 43 )
       end;
    3: aendereattributierung;
    4: vokabeleinfuegen;
    5: (* produktion speichern & verlassen *);
    6: begin
       realeKoord(aktPNr);
       zeichneProduktion;
       end;
    7: vokabelloeschen;
    8: begin
       meldung(47);
       meldung(48);
       antworte(janein,c1);
       clearmeldung;
       if c1='J' then
	 begin
         AGinit;
         Grammatikeinlesen(AGtmp);
	 end
       else dienstnr:=2;
       end;
    9: begin
	EXTENSIV := not EXTENSIV;
	zeichneProduktion
       end;
   10: vokabelersetzen;
   11: begin
       Seite1;
       vsPinkons(aktPNr);
       prn[0]:=chr(0);
       evibs(false,noList,seeonly,prn,prnr);
       Seite0;
       end;
    end (*case*);
  if dienstnr in [0,1,3,4,6,7,9,10] then wrtmenue(Prodbearbeiten);
until (dienstnr=5) or (dienstnr=8);
aktPNr:= 0;
end; (*produktionbearbeiten*)


procedure ebene2;
var c,c1: char;
    istIdent,clrscreen: boolean;
    prn: Ident;
    pr,xpb,ypb: integer;
    CAG,CS,SDateiname: filename;
    dienst: integer;

  procedure bsmask;
  var i: integer;
  begin
  clearscreen;
  if ueberspringe then begin 
    setCursor(rbs.yhome-3*rbs.zhoehe,0);
    gpr_$text(' Eingelesen wurde ',18,status);
    gpr_$text(Voreinstellung,60,status);
    ueberspringe := false;
  end;
  setCursor(rbs.yhome-6*rbs.zhoehe,0);
  gpr_$text(' Bitte waehlen Sie:',19,status); 
  setCursor(rbs.yhome-7*rbs.zhoehe,0);
  gpr_$text(' ==================',19,status);
  setCursor(rbs.yhome-9*rbs.zhoehe,0);;
  gpr_$text('       bearbeite Produktion   ',30,status);
  CursorPos(ypb,xpb);
  xpb:=xpb+35*rbs.zbreite;
  setCursor(rbs.yhome-10*rbs.zhoehe,0);
  gpr_$text('       Attribute',16,status); 
  setCursor(rbs.yhome-11*rbs.zhoehe,0);
  gpr_$text('       Nonterminale',19,status);
  setCursor(rbs.yhome-12*rbs.zhoehe,0);
  gpr_$text('       Produktionen',19,status);
  setCursor(rbs.yhome-13*rbs.zhoehe,0);
  gpr_$text('       semantische/syntaktische Funktionen',42,status);
  setCursor(rbs.yhome-14*rbs.zhoehe,0);
  gpr_$text('       Terminale',16,status);
  setCursor(rbs.yhome-15*rbs.zhoehe,0);
  gpr_$text('       Typnamen',15,status);
  setCursor(rbs.yhome-16*rbs.zhoehe,0);
  gpr_$text('       Grammatik konservieren',29,status);
  setCursor(rbs.yhome-17*rbs.zhoehe,0);
  gpr_$text('       Grammatik speichern & verlassen',38,status);
  setCursor(rbs.yhome-18*rbs.zhoehe,0);
  gpr_$text('       Grammatik unveraendert verlassen',39,status);
  setCursor(rbs.yhome-19*rbs.zhoehe,0);
  gpr_$text('       Konsistenzpruefung',25,status);
  setCursor(rbs.yhome-20*rbs.zhoehe,0);
  gpr_$text('       Steuerzeichen',20,status);
  setCursor(rbs.yhome-21*rbs.zhoehe,0);
  gpr_$text('       Information',11,status);      
  setCursor(rbs.yhome-22*rbs.zhoehe,0);
  gpr_$text('       C-Shell rufen',20,status);
  end (*bsmask*);

begin (*ebene2*)
bsmask;
dienst := 0;
repeat
 repeat
  invertBild(rbs.zbreite*6,rbs.yhome-(9+dienst)*rbs.zhoehe-4,rbs.zbreite*37,rbs.zhoehe);
  move_read(c);
  invertBild(rbs.zbreite*6,rbs.yhome-(9+dienst)*rbs.zhoehe-4,rbs.zbreite*37,rbs.zhoehe);
  case c of
    '8': if dienst > 0 then dienst := pred(dienst);
    '2': if dienst < 13 then dienst := succ(dienst);
  end;
 until (c = trz);
  case dienst of
    1 : hlaendern(attrHL);
    0 : begin
	 setCursor(ypb,xpb); gpr_$text('Name?',5,status);
	 initkontext;
	 ViBs[minvibslg]^.viline:='Bitte waehlen Sie die zu bearbeitende Produktion';
	 istIdent:=false;
	 lkup(ypb,xpb+6*rbs.zbreite,prodHL,rdorwrt,istIdent,prn,pr,clrscreen);
         if istIdent then produktionbearbeiten(pr);
     bsmask;
	 end;
    8,7: 
	 begin
	 setCursor(rbs.yhome-26*rbs.zhoehe,0);
	 gpr_$text(' Bitte geben Sie den Dateinamen der zu sichernden Grammatik an.',63,status);; 
     setCursor(rbs.yhome-27*rbs.zhoehe,0);
	 gpr_$text(' Hinweis: Leere Eingabe uebernimmt folgende Voreinstellung:',59,status); 
     setCursor(rbs.yhome-28*rbs.zhoehe,0); 
     gpr_$text(blk,1,status);
	 gpr_$text(Voreinstellung,60,status);
     setCursor(rbs.yhome-29*rbs.zhoehe,0);
	 liesDateiname(Voreinstellung, AGDateiname);
	 gibSymbolDateiname(AGDateiname,SDateiname);
	 gibCDateiname(AGDateiname,CAG);
	 gibCDateiname(SDateiname,CS);
         if isFileDir(CAG) or isFileDir(CS) then 
	   begin
           meldefehler(55);
	   dienst := 7;
	   end
	 else if schreibenerlaubt(CAG) and schreibenerlaubt(CS) then Grammatikspeichern(AGDateiname)
	 else
	   begin dienst := 7;
	   meldefehler(52);
	   end; 
     bsmask;
	 end;
     2 : hlaendern(nontHL);
     3 : hlaendern(prodHL);
     4 : hlaendern(sfktHL);
     5 : hlaendern(termHL);
     6 : hlaendern(typeHL);
     9 : begin
	 meldung(49);
	 meldung(48);
         antworte(janein,c1);
	 clearmeldung;
         if (c1='N') or (c1='A') then dienst := 0;
         bsmask;
	 end;
     10: begin
          vsAGkons;
         end;
     11: begin
          aePraefixTab;
         end;
     12: info;
     13: begin
          CShell;
          bsmask
         end;    
    otherwise ;
    end (*case*);
  ;
until (dienst = 9) or (dienst = 8);
end (*ebene2*);


procedure einstieg;
const oRand=4;
var c: char;
    CAG: filename;
    dienst: integer;
    
  function yy(n: integer): integer;
  begin
  with rbs do yy:=ypixels-(n+oRand)*zhoehe;
  end;

  procedure bsmask;
  begin
  clearscreen;
  setCursor(yy(0),0);
  gpr_$text(' Bitte waehlen Sie:',20,status);
  setCursor(yy(0)-rbs.zhoehe,0);
  gpr_$text(' ==================',19,status);           
  setCursor(yy(0)-3*rbs.zhoehe,0);
  gpr_$text('       Information',18,status);
  setCursor(yy(0)-4*rbs.zhoehe,0);
  gpr_$text('       erzeuge Grammatik neu',28,status);
  setCursor(yy(0)-5*rbs.zhoehe,0);
  gpr_$text('       lade bereits existierende Grammatik',42,status);
  setCursor(yy(0)-6*rbs.zhoehe,0);
  gpr_$text('       beende Programmlauf',26,status);
  setCursor(yy(0)-7*rbs.zhoehe,0);
  gpr_$text('       C-Shell',14,status);
  end;

begin (*einstieg*)
if not Symbolinit 
  then meldefehler(60)
  else begin
aktPNr:= 0;
if recover then
  begin
  AGinit;
  Grammatikeinlesen(AGtmp);
  ebene2;
  end
else
  begin
  if ueberspringe then
   begin 
   AGDateiname := Voreinstellung;
   gibCDateiname(AGDateiname,CAG);
   if isFileDir(CAG) then meldefehler(55)
   else if lesenerlaubt(CAG) then
     begin
     if testeversion(AGDateiname) then
       begin
       AGinit;
       Grammatikeinlesen(AGDateiname);
       testeueberlauf;
       ebene2;
       end
     else meldefehler(59)
     end
   else meldefehler(51)
   end; 
  bsmask;
  dienst := 0;
  repeat
    repeat
     invertBild(6*rbs.zbreite,yy(0)-(dienst+3)*rbs.zhoehe-4,37*rbs.zbreite,rbs.zhoehe);
     move_read(c);
     invertBild(6*rbs.zbreite,yy(0)-(dienst+3)*rbs.zhoehe-4,37*rbs.zbreite,rbs.zhoehe);
     case c of
     '8' : if dienst > 0 then dienst := pred(dienst);
     '2' : if dienst < 4 then dienst := succ(dienst)
     end
    until (c = trz);
    case dienst of
       2 : begin
  	   AGinit;
  	   setCursor(yy(8),0);
       gpr_$text(' Bitte geben Sie den Dateinamen der einzulesenden Grammatik an.',63,status);
       setCursor(yy(8)-rbs.zhoehe,0);
  	   gpr_$text(' Hinweis: Leere Eingabe uebernimmt folgende Voreinstellung:',59,status);
       setCursor(yy(8)-2*rbs.zhoehe,0);
       gpr_$text(blk,1,status);
  	   gpr_$text(Voreinstellung,60,status);
       setCursor(yy(8)-3*rbs.zhoehe,0);
  	   liesDateiname(Voreinstellung,AGDateiname);
  	   gibCDateiname(AGDateiname,CAG);
           if isFileDir(CAG) then meldefehler(55)
  	   else if lesenerlaubt(CAG) then 
  	     begin
             if testeversion (AGDateiname) then
	       begin
  	       Grammatikeinlesen(AGDateiname);
               testeueberlauf;
               ebene2;
  	       end
	     else meldefehler(59)
	     end
  	   else meldefehler(51);
       bsmask;
  	   end;
       3 : ;
       1 : begin
           AGinit;
  	   ebene2;
       bsmask;
  	   end;
       0 : info;
       4 : begin
            CShell;
            bsmask
          end;  
       otherwise;
      end; (*case*)
    ;
  until dienst = 3;
  end
end
end (*einstieg*);
