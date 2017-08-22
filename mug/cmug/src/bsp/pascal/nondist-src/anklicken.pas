





procedure fadenkreuz (* var y,x: integer; var abbruch: boolean *);
var c,hy,ly,hx,lx,dummy: char;
begin 
abbruch:=false;
setCursor(y,x);
gpr_$set_cursor_active(true,status);
keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
gpr_$enable_input(gpr_$buttons, keys, status); 
keys := ['0',promptChar,PraefixTab[1]]; {Create a key set.}
gpr_$enable_input(gpr_$keystroke, keys, status);
unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
gpr_$set_cursor_active(false,status); 
x:=ev_pos.x_coord; 
y:=rbs.ypixels-ev_pos.y_coord; 
if (c='0') or (c=kbd_$m1d) then abbruch:=true;
if c=PraefixTab[1] then c:=kbd_$m3d;
ev_char:=c;
end;   {fadenkreuz}

procedure leave_meldung;
 var x,y:integer;
     ende:boolean;
     c:char;
 begin
 ende := FALSE;
 with MFenster do
   setCursor((LOecke_y + RUecke_y) div 2, (RUecke_x + LOecke_x) div 2);
 if Meldungen > 0 then
 begin
 gpr_$set_cursor_active(true,status);
 keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
 gpr_$enable_input(gpr_$buttons, keys, status); 
 keys := [chr(0)..chr(128)]; {Create a key set.}
 gpr_$enable_input(gpr_$keystroke, keys, status);
 gpr_$enable_input(gpr_$locator,keys,status);
 repeat
   unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
   if ev_type = gpr_$locator
    then begin
        gpr_$set_cursor_position(ev_pos, status);
 	x:=ev_pos.x_coord; 
	y:=rbs.ypixels-ev_pos.y_coord; 
        with MFenster do
	  ende := (x > RUecke_x) or (x < LOecke_x) or (y > LOecke_y) or (y < RUecke_y);
        end
     else ende := TRUE;
 until ende;
 gpr_$disable_input(gpr_$locator,status);
 gpr_$set_cursor_active(false,status); 
 clearmeldung;
 end
 end;

procedure bestimmeobloeschen (* y,x: integer; var loeschen: boolean *);
begin
loeschen:= false;
if (y >= rbs.uRandvBild+rbs.vBildHoehe)
then if (y <= rbs.uRandvBild+rbs.vBildHoehe+2*rbs.R1)
     then if (x >= rbs.xpixels-dist(9))
	  then loeschen:= true
end;   {bestimmeobloeschen}

procedure bestimmeHAttr (*y, x: integer; var ha: HAListe; var attrnr: integer*);
var gefunden: boolean;
begin
gefunden:= false;
ha:= PTab[ aktPNr ].hilfsAttr;
while (not gefunden) and (ha <> nil) do
  if (ha^.Y <= y) and (y <= ha^.Y+ASymb.hoehe-1) and
     (ha^.X <= x) and (x <= ha^.X+ASymb.breite-1)
  then gefunden:= true
  else ha:= ha^.nxt;
if gefunden
then attrnr:= ha^.attr
else attrnr:= 0
end;   {bestimmeHAttr}

procedure bestimmeTermoderAttr (* y,x: integer; var vok: VokListe; var attrnr: integer *);
var attr:     AListe;
    hattr:    HAListe;
    moeglich,
    gefunden: boolean;
    i,j:      integer;

begin
gefunden:= false; attrnr:= 0;
vok:= PTab[ aktPNr ].vater;
if (vok = nil) then vok:= PTab[ aktPNr ].soehne;
while (not gefunden) and (vok <> nil) do
  begin
  case vok^.typ of
  term: begin
	if abs(y-vok^.Y) <= rbs.R1
	then if (vok^.X <= x)
	     then if (x <= vok^.X + VBreite(vok) )
		  then gefunden:= true
	end;
  nont: begin
	if abs(y-vok^.Y) <= (ASymb.hoehe div 2)  {falls ASymb.hoehe gerade ist}
	then begin	   {wird ein Pixel ueber dem Ikon auch noch akzeptiert}
	     moeglich:= true;
	     if (x < vok^.X-ASymb.breite)
	     then begin
		  i:= (vok^.X-x-1) div ASymb.breite;
		  attr:= vok^.spezInhA;
		  if (attr = nil) and vok^.konsistent
		  then attr:= NTTab[vok^.nt].inhAttr
		  end
	     else begin
		  i:= vok^.X + dist( ord( NTTab[vok^.nt].name[0] ) + 1 );
		  if (i+ASymb.breite < x)
		  then begin
		       i:= (x-i-1) div ASymb.breite;
		       attr:= vok^.spezDerA;
		       if (attr = nil) and vok^.konsistent
		       then attr:= NTTab[vok^.nt].derAttr
		       end
		  else moeglich:= false
		  end;
	     if moeglich
	     then begin
		  if odd(i)
		  then begin                {i = Position an der das Ikon liegt}
		       i:= (i+1) div 2;
		       j:= 1;
		       while (attr <> nil) and (j < i) do
			 begin j:= j+1; attr:= attr^.nxt end;
		       if (attr <> nil)
		       then begin gefunden:= true; attrnr:= attr^.attr end
		       end
		  {else                   Koordinaten liegen zwischen den Ikons}
		  end
	     end
	end  {nont:}
        end; {case}
  if not gefunden then vok:= vok^.nxt
  end;  {while}
if not gefunden
then bestimmeHAttr( y, x, hattr, attrnr );
end;   {bestimmeTermoderAttr}


procedure istzielpar (*vok: VokListe; attrnr: integer; var ok: boolean *);
begin
if (attrnr <> 0)
then begin
     ok:= true;
     if (vok <> nil)	                                   {Attr von NT}
     then if (vok = PTab[aktPNr].vater)
	  then begin
	       if (ATab[attrnr].art <> der)
	       then begin ok:= false; meldung(1) end
	       end
	  else begin
	       if (ATab[attrnr].art <> inh)
	       then begin ok:= false; meldung(2) end
	       end
     else begin
	  if (ATab[attrnr].art <> aux)
	  then begin ok:= false; meldung(3) end
	  end
     end
else begin
     ok:= false;
     if (vok <> nil) then meldung(5)
     end
end;   {istzielpar}

function schonberechnet (* vok: VokListe; attrnr: integer; var sf: SemFktListe; var par: ParListe): boolean *);
var berechnet: boolean;
begin
sf:= PTab[aktPNr].semRegeln;
berechnet:= false;           	    	    {wird true gesetzt, wenn Attr schon}
while (not berechnet) and (sf <> nil) do        		{berechnet wird}
  begin
  par:= sf^.zielpar;
  while (not berechnet) and (par <> nil) do
    if (par^.vok = vok) and (par^.attr = attrnr)
    then berechnet:= true
    else par:= par^.nxt;
  if not berechnet then sf:= sf^.nxt
  end;
schonberechnet:= berechnet
end;   {schonberechnet}

procedure loescheSemFktgr(* sf: SemFktListe *);
begin
if (sf^.semfkt <> IDNT)
then begin              
     gpr_$set_draw_value(-2,status);
     zeichneSemFkt( sf );  
     if SFTab[sf^.semfkt].issynfkt
      then begin                    
            gpr_$set_draw_value(-2,status);
            sf^.gedreht:=not sf^.gedreht;
            zeichneSemFkt(sf);
            sf^.gedreht:=not sf^.gedreht;
           end; 
     gpr_$set_draw_value(color_base,status);
     loeschewort( sf^.Y-rbs.deltaY-2, sf^.X, ord(SFTab[sf^.semfkt].name[0]));
     end
end;   {loescheSemFktgr}

procedure versorgePar (* var sf: SemFktListe; vok: VokListe; attrnr, index: integer; fpar: TypListe; var gueltig: boolean *);
var apar,
    hpar:    ParListe;
    hsf:     SemFktListe;
    i:       integer;
    c:       char;
    abfrage: boolean;

begin
if (index > 0)				    {index > 0 entspricht Zielparameter}
then istzielpar( vok, attrnr, gueltig )		  	  {dadurch wird gueltig}
else gueltig:= true;					   { richtig vorbesetzt}
if (attrnr <> 0)
then begin				  {d.h. Attr. von NT oder Hilfsattribut}
     if (fpar^.typ <> ATab[attrnr].typ)
     then begin
	  gueltig:= false; meldung(0);
	  wrtIdent( TypTab[ ATab[attrnr].typ ].name )
	  end;
     if (index > 0)			    {index > 0 entspricht Zielparameter}
     then if schonberechnet( vok, attrnr, hsf, apar)
	  then begin
	       meldung(4);
	       if gueltig
	       then begin
		    abfrage:= true;
		    if (sf = hsf)
		    then begin
			 hpar:= sf^.zielpar; i:= 1;
			 while (hpar <> apar) do
			   begin i:= i+1; hpar:= hpar^.nxt end;
			 if (i = index) then abfrage:= false
			 end;
		    if abfrage
		    then begin
	                 meldung(6);
                     keys := ['j','n','J','N']; {Create a key set.}
                     gpr_$enable_input(gpr_$keystroke, keys, status);
                     keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
                     gpr_$enable_input(gpr_$buttons, keys, status); 
                     unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
         			 gpr_$text(c,1,status); newline;
		         if (c = 'j')
		         then begin		      {alte Versorgung loeschen}
			      loescheParVersorgung( hsf, apar, true );
			      loescheParVersorgung( hsf, apar, false);
			      if (sf = hsf)
			      then signatur2( hsf, nil, 0, i )
			      else if not hatSFerg( hsf )
				   then begin
				        loescheSemFktgr( hsf );
					gibfreiSF( aktPNr, hsf )
				        end
		              end
		     	 else gueltig:= false {keine Neuberechng gewuenscht}
			 end
		     end
	       end;  {ende (index>0) und schonberechnet}
     if gueltig
     then begin
	  if (index > 0)
	  then apar:= sf^.zielpar
	  else apar:= sf^.quellpar
	  end   {ende gueltig}
     end   {attrnr <> 0}
else begin  {attrnr = 0}
     if (vok <> nil)
     then begin			               	       {Objekt ist ein Terminal}
	  if (index < 0)			     {entspricht Quellparameter}
	  then begin
	       if (vok^.typ <> term)
	       then begin
		    wrtERR1('Vokabel muesste Terminal sein (versorgePar)');
		    gueltig:= false
		    end
	       else begin 
		    if not Twirdverwendet( vok^.t )
		    then TTab[vok^.t].typ:= fpar^.typ
		    else begin
     		         if (fpar^.typ <> TTab[vok^.t].typ)
		         then begin
			      meldung( 36 );
			      wrtIdent( TypTab[ TTab[vok^.t].typ ].name );
			      gpr_$text(' verwendet!',11,status); meldung( 37 );
                  keys := ['j','n','J','N']; {Create a key set.}
                  gpr_$enable_input(gpr_$keystroke, keys, status); 
                  keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
                  keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
                  gpr_$enable_input(gpr_$buttons, keys, status); gpr_$enable_input(gpr_$buttons, keys, status); 
                  unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
			      gpr_$text(c,1,status);
			      if (c = 'n')
			      then gueltig:= false
			      else begin
				   lspmbdgTg( vok^.t );
		    		   TTab[vok^.t].typ:= fpar^.typ
				   end
			      end
		         end
		    end
	       end;
	  if gueltig then apar:= sf^.quellpar
	  end
     else gueltig:= false			     {war kein gueltiges Objekt}
     end;   {attrnr = 0}
if gueltig
then begin
     for i:= 1 to abs(index)-1 do apar:= apar^.nxt;
     if (apar^.vok <> nil) or (apar^.attr <> 0)
     then begin  
          gpr_$set_draw_value(-2,status);
          if sf^.semfkt <> IDNT
           then 
             if SFTab[sf^.semfkt].issynfkt
              then zeichneParVersSynfkt(sf, apar, (index>0))
	      else zeichneParVersorgung( sf, apar, (index>0) )
	   else zeichneParVersorgung( sf, apar, (index>0) ); 
       gpr_$set_draw_value(color_base,status);
	  end;
     apar^.vok:= vok; apar^.attr:= attrnr;     	 {eigentliches besetzen}
                       			       {der aktuellen Parameter}
     aenderelinienfuehrung(sf,apar,(index>0),true);
     if sf^.semfkt<> IDNT
      then
        if SFTab[sf^.semfkt].issynfkt
         then zeichneParVersSynfkt(sf, apar, (index>0)) 
         else zeichneParVersorgung( sf, apar, (index>0) )
      else zeichneParVersorgung( sf, apar, (index>0) );
     signatur2( sf, vok, attrnr, index )
     end
else begin
     meldung(7); meldung(8);
     pread(c); if (c = '0') then gueltig:= true;
     end;
clearmeldung;
end;   {versorgePar}


procedure ParVersorgungaendern (* var sf: SemFktListe *);  {sf darf nicht nil}
const plusaktpar = true;				     {oder ID sein}
var vok: VokListe;
    fpar: TypListe;
    apar: ParListe; 
    v : VokListe;
    dummy,attrnr,
    index,x,y,x2,y2,a:    integer;
    loeschen,
    ok,abbrechen: boolean;
begin
x:= rbs.xpixels-dist(9);
y:=  rbs.uRandvBild+rbs.vBildHoehe-10;
box( y, x, y+2*rbs.R1, rbs.xpixels );
setCursor( y+rbs.R1-rbs.deltaY, x+rbs.deltaX );
gpr_$text('Loeschen',8,status);
repeat
  meldung( 20 );
  meldung( 7 );
  y:= rbs.uRandvBild - gibazh(IconsUeberText);
  waehleformPar( plusaktpar, y, sf^.semfkt, 's', false, dummy, index, fpar );
  clearmeldung;
  if (index <> 0)
  then begin
       x:= rbs.xpixels div 2;
       y:= rbs.uRandvBild + (rbs.vBildHoehe div 2);
       repeat
         if (index < 0)
         then meldung(19)
         else meldung(15);
         meldung(44);
         meldung(45);
	 leave_meldung;
	 CursorPos(y,x); 
         repeat
	   fadenkreuz(y,x,abbrechen);
       if ev_char=kbd_$m3d
        then begin                                 
              repeat
              with rbs do loesche4eck(uRandvBild-2*gibazh(IconsUeberText)-3,uRandvBild-gibazh(IconsUeberText)-5,0,xpixels);
                 bestimmeTermoderAttr(y,x,v,a);
                 setCursor(rbs.uRandvBild-2*gibazh(IconsUeberText),0);
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
                   end 
		 else begin
		      if (index < 0) then meldung(19)
				     else meldung(15);
	 	      meldung(44);
		      meldung(45);
		      leave_meldung;
		      CursorPos(y,x)
		      end;
                setCursor(y,x);
                fadenkreuz(y,x,abbrechen);
               until (ev_char<>kbd_$m3d);
               with rbs do loesche4eck(uRandvBild-2*gibazh(IconsUeberText)-3,uRandvBild-gibazh(IconsUeberText)-5,0,xpixels);
               end;
	   bestimmeTermoderAttr( y, x, vok, attrnr );
	   bestimmeobloeschen( y, x, loeschen );
         until (vok <> nil) or (attrnr <> 0) or loeschen or abbrechen;
	 if not abbrechen
	 then if loeschen
	      then begin
     	    	   ok:= true;
     	    	   if (index>0)
     	    	   then apar:= sf^.zielpar
     	    	   else apar:= sf^.quellpar;
     	    	   for dummy:= 1 to abs(index)-1 do apar:= apar^.nxt;
     	    	   loescheParVersorgung( sf, apar, index>0 );
		   if (index > 0)
		   then if not hatSFerg( sf )
			then begin
			     dummy:= rbs.uRandvBild - gibazh(IconsUeberText);
			     sfparmkd( plusaktpar, dummy, sf^.semfkt,
			     	       lgtl(SFTab[sf^.semfkt].erglist), y, x );
			     male4eck(true,y-3,rbs.uRandvBild-5,0,rbs.xpixels);
			     loescheSemFktgr( sf ); gibfreiSF( aktPNr, sf );
			     index:= 0; sf:= nil
			     end
			else signatur2( sf, nil, 0, index )
		   else signatur2( sf, nil, 0, index )
     	    	   end
	      else versorgePar( sf, vok, attrnr, index, fpar, ok )
       until ok or abbrechen;
       clearmeldung
       end
until (index = 0);
if (sf <> nil) then sf^.versorgt:= isSFversorgt( sf );
male4eck( true, rbs.uRandvBild+rbs.vBildHoehe-10,
		rbs.uRandvBild+rbs.vBildHoehe+2*rbs.R1,
	        rbs.xpixels-dist(9), rbs.xpixels );
end;   {ParVersorgungaendern}

procedure HAanklicken (* var ha: HAListe; var dy,dx: integer *);
var x,y,attrnr: integer;
    abbrechen: boolean;
begin
ha:= PTab[ aktPNr ].hilfsAttr;
if (ha <> nil)
then begin
     meldung(16);
     meldung(44);
     leave_meldung;
     CursorPos(y,x);
     repeat
       fadenkreuz(y,x,abbrechen);
       if ev_char = kbd_$m3d
	then begin
	     meldung(16);
	     meldung(44);
	     leave_meldung;
     	     CursorPos(y,x);
	     attrnr := 0
	     end
        else bestimmeHAttr(y,x,ha,attrnr);
     until (attrnr <> 0) or abbrechen;
     if abbrechen
     then begin dx:= 0; dy:= 0; ha:= nil end
     else begin dx:= ha^.X - x; dy:= ha^.Y - y end;
     clearmeldung;
     end
else meldung( 39 )
end;   {HAanklicken}

procedure HApositionieren (* ha: HAListe; dy,dx: integer; neu: boolean; var abbrechen: boolean *);
var y,x:      integer;
    symbol:   ASymbTyp;
    onscreen: boolean;

  procedure zeichneHAParVerbindungen;
  var sf:  SemFktListe;
      par: ParListe;
  begin
  sf:= PTab[ aktPNr ].semRegeln;
  while (sf <> nil) do
    begin
    par:= sf^.zielpar;
    while (par <> nil) do
      begin
      if (par^.attr = ha^.attr) 
      then begin 
            if sf^.semfkt <> IDNT
             then
              if SFTab[sf^.semfkt].issynfkt
               then zeichneParVersSynfkt(sf,par,true)
               else zeichneParVersorgung( sf, par, true )
             else zeichneParVersorgung( sf, par, true ); par:= nil end
      else par:= par^.nxt
      end;
    par:= sf^.quellpar;
    while (par <> nil) do
      begin
      if (par^.attr = ha^.attr) 
      then if (sf^.semfkt = IDNT)
           then zeichneParVersorgung( sf, sf^.zielpar, true )
           else if sf^.semfkt <> IDNT
                 then if SFTab[sf^.semfkt].issynfkt
                       then zeichneParVersSynfkt(sf,par,false)
                       else zeichneParVersorgung(sf,par,false) 
                 else zeichneParVersorgung( sf, par, false );
      par:= par^.nxt
      end;
    sf:= sf^.nxt;
    end;   {while sf<>nil}
  end;   {zeichneHAParVerbindungen}

begin
if (ha <> nil)
then begin
     meldung(17);
     meldung(44);
     leave_meldung;
     CursorPos(y,x);
     onscreen:= false;
     repeat
       fadenkreuz(y,x,abbrechen);
       if ev_char = kbd_$m3d
	then begin
	     meldung(17);
	     meldung(44);
	     leave_meldung;
	     CursorPos(y,x)
	     end
        else if (x+dx >= 0)
	       then if (y+dy > rbs.uRandvBild)
	       then if (x+dx <= rbs.xpixels - ASymb.breite)
	       then if (y+dy <= rbs.uRandvBild + rbs.vBildHoehe - ASymb.hoehe)
	       then onscreen:= true
     until onscreen or abbrechen;
     if not abbrechen
     then begin
	  if not neu
	  then begin 
           gpr_$set_draw_value(-2,status);
	       zeichneHAParVerbindungen;
	       male4eck( true, ha^.Y, ha^.Y+ASymb.hoehe, ha^.X, ha^.X+ASymb.breite ); 
           gpr_$set_draw_value(color_base,status);
	       {LOESCHENAUS wird schon in male4eck gesetzt}
	       end;   {not neu}
     	  ha^.X:= x+dx;
     	  ha^.Y:= y+dy;
     	  ha^.vx:= (x+dx)/rbs.xpixels;
     	  ha^.vy:= (y+dy - rbs.uRandvBild)/rbs.vBildHoehe;
	  symbol:=  ATab[ha^.attr].symbol;
	  writeikon( ha^.Y, ha^.X, symbol );
	  if not neu then zeichneHAParVerbindungen
	  end   {nicht abbrechen}
     end   {ha <> nil}
end;   {HApositionieren}

procedure SFpositionieren(* sf: SemFktListe; dy, dx: integer; neu: boolean; var abbrechen: boolean *);
var y,x:      integer;
    onscreen: boolean;
begin
if (sf <> nil)
then if (sf^.semfkt <> IDNT)
then begin
     meldung(14);
     meldung(44);
     leave_meldung;
     CursorPos(y,x);
     onscreen:= false;
     repeat
       setCursor(y,x);
       fadenkreuz(y,x,abbrechen);
       if ev_char = kbd_$m3d
	then begin
	     meldung(14);
	     meldung(44);
	     leave_meldung;
	     CursorPos(y,x)
	     end
        else if (x+dx >= rbs.R1) then
	       if (y+dy > rbs.uRandvBild+rbs.R1) then
	       if (y+dy <= rbs.uRandvBild+rbs.vBildHoehe-rbs.R1) then
	       if (x+dx+dist( ord( SFTab[sf^.semfkt].name[0] ) )+rbs.R1 
	            <= rbs.xpixels) then onscreen:= true;
     until onscreen or abbrechen;
     if not abbrechen
     then begin
          if not neu then loescheSemFktgr( sf );
          sf^.X:= x+dx;
          sf^.Y:= y+dy;
          sf^.vx:= sf^.X/rbs.xpixels;
          sf^.vy:= (sf^.Y-rbs.uRandvBild)/rbs.vBildHoehe;
	  zeichneSemFkt( sf )
	  end
     end
end;   {SFpositionieren}

procedure SFanklicken (* var sf: SemFktListe; var dy, dx: integer *);
var y,x,hx:      integer;
    abbrechen,
    gefunden: boolean;
begin
sf:= PTab[ aktPNr ].semRegeln;
if (sf <> nil)
then begin
     gefunden:= false;
     while (sf <> nil) and not gefunden do     {stellt fest, ob ueberhaupt eine}
       if (sf^.semfkt <> IDNT)		    {sem Funktion ausser der Identitaet}
       then gefunden:= true		         {vorhanden ist, da sonst keine}
       else sf:= sf^.nxt;		  		      {Auswahl moeglich}
     if gefunden
     then begin
          meldung(18);
          meldung(44);
	  leave_meldung;
	  CursorPos(y,x);
          gefunden:= false;
          repeat
            setCursor(y,x);
            fadenkreuz(y,x,abbrechen);
	    if ev_char = kbd_$m3d
	     then begin
		  meldung(18);
		  meldung(44);
		  leave_meldung;
		  CursorPos(y,x)
		  end
	    else if not abbrechen
	     then begin
                  while (sf <> nil) and not gefunden do
	           begin
	           if (sf^.semfkt <> IDNT)
	           then begin
	                if (abs(y-sf^.Y) <= rbs.R1)
	                then begin
	                     if (x < sf^.X)
	                     then begin
		                  if (x >= sf^.X-rbs.R1)
		                  then if (round(sqrt((x-sf^.X)*(x-sf^.X) +
					        (y-sf^.Y)*(y-sf^.Y))) <= rbs.R1)
			               then gefunden:= true
		                  end     {Koord liegen im linken Halbkreis}
	                     else begin
		                  hx:= sf^.X + dist(ord(SFTab[sf^.semfkt].name[0]));
		                  if (x <= hx)
		                  then gefunden:= true {Koord liegen imRechteck}
		                  else if (x <= hx+rbs.R1)
			     	       then if (round( sqrt( (x-hx)*(x-hx) +
						(y-sf^.Y)*(y-sf^.Y))) <= rbs.R1)
			                    then gefunden:= true
		                  end  	    {Koord liegen im rechten Halbkreis}
	                     end
		        end;
	           if not gefunden then sf:= sf^.nxt
	           end;   {while}
                 if not gefunden then sf:= PTab[ aktPNr ].semRegeln;
		 end   {kein Abbruch}
	    else sf:= nil
          until gefunden or abbrechen;
	  if abbrechen
	  then begin dx:= 0; dy:= 0 end
	  else begin dx:= sf^.X-x; dy:= sf^.Y-y; end;
	  end   {es gibt sem.Fkt. ausser ID}
     else meldung( 40 )
     end   {es sind sem.Fkt. vorhanden}
else meldung( 38 )
end;   {SFanklicken}

procedure neuDefHA;
var ha: 	HAListe;
    y,x,attrnr: integer;
    ok,abbruch: boolean;
    id:		Ident;
    c:		char;
begin
repeat
  meldung(23);
  ok:= false; c:= ' ';
  CursorPos(y,x);
  initkontext;
  ViBs[minvibslg]^.viline:= 'Waehlen Sie ein Attribut vom Typ auxiliary aus!';
  ATyp_info := aux;		(* Neues Attribut als Hilfsattribut kennzeichnen *)
  lkup( y, x, attrHL, rdorwrt, ok, id, attrnr, abbruch );
  ATyp_info := undef;
  if ok					{abbruch ist hier nur dummy}
  then begin
       if (ATab[attrnr].art <> aux)
       then begin ok:= false; meldung(3) end
       else begin
	    ha:= PTab[ aktPNr ].hilfsAttr;   	      {Test ob schon vorhanden}
	    while (ha <> nil) do
	      if (ha^.attr = attrnr)
	      then begin ok:= false; ha:= nil; meldung(24) end
	      else ha:= ha^.nxt;
	    end
       end;
  if not ok
  then begin meldung(7); meldung(25); pread(c) end;
  clearmeldung
until ok or (c = '0');
if ok
then begin
     beschaffeHA( ha );			      {beschaffen eines Hilfsattributes}
     ha^.attr:= attrnr;
     HApositionieren(ha, -(ASymb.hoehe div 2), -(ASymb.breite div 2), true, abbruch );
     if abbruch
     then begin
          ha^.nxt:= HALL; HALL:= ha          {Positionierung wurde abgebrochen}
          end				               {neues Element freigeben}
     else begin
          ha^.nxt:= PTab[ aktPNr ].hilfsAttr;     {einhaengen in die Liste der}
          PTab[ aktPNr ].hilfsAttr:= ha;	   		{Hilfsattribute}
	  end
     end
end;   {neuDefHA}

procedure loescheHA;
var sf,hsf:    SemFktListe;
    ha:        HAListe;
    par:       ParListe;
    dx,dy:     integer;
    loeschen:  boolean;
begin
HAanklicken( ha, dy, dx );
if (ha <> nil)
then begin
     sf:= PTab[ aktPNr ].semRegeln;
     while (sf <> nil) do
       begin
       loeschen:= false;
       par:= sf^.zielpar;
       while (par <> nil) do
	 begin
	 if (par^.attr = ha^.attr)
	 then begin
	      loescheParVersorgung( sf, par, true );
	      if not hatSFerg( sf ) then loeschen:= true;
	      par:= nil
	      end
	 else par:= par^.nxt
	 end;
       if not loeschen
       then begin
            par:= sf^.quellpar;
            while (par <> nil) do
	      begin
	      if (par^.attr = ha^.attr)
	      then begin
		   if (sf^.semfkt = IDNT) 
		   then begin
			loeschen:= true;
			loescheParVersorgung( sf, sf^.zielpar, true );
			end
		   else loescheParVersorgung( sf, par, false );
		   end;
	      par:= par^.nxt
	      end
	    end;
       if loeschen
       then begin
	    hsf:= sf^.nxt; loescheSemFktgr( sf );
	    gibfreiSF( aktPNr, sf ); sf:= hsf
	    end
       else sf:= sf^.nxt
       end;
     male4eck( true, ha^.Y, ha^.Y+ASymb.hoehe, ha^.X, ha^.X+ASymb.breite );
     gibfreiHA( PTab[aktPNr].hilfsAttr, ha )
     end
end;   {loescheHA}

procedure Vokabelverschieben;
var vok,hv:    VokListe;
    x,y,dx,dy: integer;
    gefunden,ok,
    abbrechen: boolean;
begin
hv:= PTab[ aktPNr ].vater;
if (hv = nil) then hv:= PTab[ aktPNr ].soehne;
if (hv <> nil)
then begin
     meldung(28);
     meldung(44);
     leave_meldung;
     CursorPos(y,x);
     gefunden:= false;
     repeat
       vok:= hv; 
       fadenkreuz(y,x,abbrechen);
       if ev_char = kbd_$m3d
	then begin
	     meldung(28);
	     meldung(44);
	     leave_meldung;
	     CursorPos(y,x)
	     end
       else if not abbrechen
        then while (vok <> nil) and not gefunden do
	      begin
	      if (abs(vok^.Y-y) <= 2*rbs.R1)
	      then if (vok^.X <= x)
	           then if (x <= vok^.X + VBreite(vok))
		        then gefunden:= true;
	      if not gefunden then vok:= vok^.nxt
	      end
     until gefunden or abbrechen;
     if not abbrechen
     then begin
	  dx:= vok^.X-x; dy:= vok^.Y-y;
	  meldung( 29 );
          meldung(44);
	  leave_meldung;
	  CursorPos(y,x);
	  repeat
	    fadenkreuz(y,x,abbrechen);
	    if ev_char = kbd_$m3d
		then begin
		     meldung(29);
		     meldung(44);
		     leave_meldung;
		     CursorPos(y,x)
		     end
	    else if not abbrechen
	     then begin
		 ok:= false;
		 if (vok = PTab[ aktPNr ].vater)
		 then begin
		      if (rbs.uRandvBild+rbs.vBildHoehe-rbs.R1 >= y+dy)
		      then if (y+dy >= rbs.uRandvBild+0.5*rbs.vBildHoehe+rbs.R1)
		           then if (0 <= x+dx)
			        then if (x+dx+VBreite(vok) < rbs.xpixels)
				     then ok:= true
		      end
		 else begin
		      if (rbs.uRandvBild+rbs.R1 < y+dy)
		      then if (y+dy <= rbs.uRandvBild+0.5*rbs.vBildHoehe-rbs.R1)
		           then if (0 <= x+dx)
			        then if (x+dx+VBreite(vok) < rbs.xpixels)
				     then ok:= true
		      end
	         end
	  until ok or abbrechen;
	  if not abbrechen
	  then begin
	       vok^.dx:= vok^.dx + (x+dx-vok^.X)/rbs.xpixels;
	       vok^.dy:= vok^.dy + (y+dy-vok^.Y)/rbs.vBildHoehe;
	       if not LAZY
	       then begin
    	    realeKoord( aktPNr );          
		    zeichneProduktion;
		    wrtmenue( Gestalten );
		    end
	       end
	  end
     end
else meldung( 41 )
end;   {Vokabelverschieben}

procedure standardpositionierung;
var vok: VokListe;
begin
vok:= PTab[ aktPNr ].vater;
if (vok = nil) then vok:= PTab[ aktPNr ].soehne;
while (vok <> nil) do
  begin vok^.dx:= 0; vok^.dy:= 0; vok:= vok^.nxt end;
if not LAZY
then begin
     realeKoord( aktPNr );
     zeichneProduktion;
     wrtmenue( Gestalten )
     end
end;   {standardpositionierung}

procedure markiere (* y, x: integer *);
begin
linie( y-1, x-2, y-1, x+2 );
linie( y+1, x-2, y+1, x+2 );
linie( y-2, x-1, y+2, x-1 );
linie( y-2, x+1, y+2, x+1 );
end;   {markiere}

procedure liesPunkte(* var pl: PunktListe *);
var hpl:       PunktListe;
    i,x,y,
    xalt,yalt: integer;
    ok,
    abbrechen: boolean;
begin
i:= 0;
leave_meldung;
CursorPos(y,x);
repeat
  repeat
    ok:= false;
    setCursor(y,x);
    fadenkreuz(y,x,abbrechen);
    if (not abbrechen) and (ev_char <> kbd_$m3d) 
    then begin
         if (x > 1) and (x < rbs.xpixels-1)
         and (y > rbs.uRandvBild) and (y < rbs.uRandvBild+rbs.vBildHoehe)
         then if (i > 0)
	      then ok:= ( sqr(xalt-x)+sqr(yalt-y) > 20 )
	      else ok:= true
	 end;
  until ok or abbrechen;
  if ok
  then begin
       xalt:= x; yalt:= y; i:= i+1;
       if (i = 1)
       then begin beschaffePunkt(pl); hpl:= pl end
       else begin beschaffePunkt(hpl^.nxt); hpl:= hpl^.nxt end;
       hpl^.vx:= x/rbs.xpixels;
       hpl^.vy:= (y-rbs.uRandvBild)/rbs.vBildHoehe;
       markiere(y,x);
       end;
until abbrechen or (i = 28);
if (i = 0) then pl:= nil else hpl^.nxt:= nil
end;   {liesPunkte}

procedure aenderelinienfuehrung (* sf: SemFktListe; par: ParListe; zielpar, altloeschen: boolean *);
var hpunkte, punkte: PunktListe;
    x,y: integer;
begin
if (par^.vok <> nil) or (par^.attr <> 0)
then begin
     hpunkte:= par^.verb;
     while (hpunkte <> nil) do
       begin
       x:= round( hpunkte^.vx * rbs.xpixels );
       y:= round( hpunkte^.vy * rbs.vBildHoehe ) + rbs.uRandvBild;
       markiere( y, x ); hpunkte:= hpunkte^.nxt
       end;
     meldung( 30 );
     meldung( 44 );
     liesPunkte( punkte );
     clearmeldung;
     gpr_$set_draw_value(-2,status);
     if altloeschen
     then begin
          if sf^.semfkt <> IDNT
           then
            if SFTab[sf^.semfkt].issynfkt
             then zeichneParVersSynfkt(sf,par,zielpar)
     	     else zeichneParVersorgung( sf, par, zielpar )
     	   else zeichneParVersorgung( sf, par, zielpar );
     	  hpunkte:= par^.verb;
     	  while (hpunkte <> nil) do
       	    begin
            x:= round( hpunkte^.vx * rbs.xpixels );
            y:= round( hpunkte^.vy * rbs.vBildHoehe ) + rbs.uRandvBild;
            markiere( y, x ); hpunkte:= hpunkte^.nxt
            end;
	  end;
     hpunkte:= punkte;
     while (hpunkte <> nil) do
       begin
       x:= round( hpunkte^.vx * rbs.xpixels );
       y:= round( hpunkte^.vy * rbs.vBildHoehe ) + rbs.uRandvBild;
       markiere( y, x ); hpunkte:= hpunkte^.nxt
       end;  
     gpr_$set_draw_value(color_base,status);
     gibPunktLzurueck( par^.verb );
     par^.verb:= punkte;
     if sf^.semfkt <> IDNT
      then 
       if SFTab[sf^.semfkt].issynfkt
         then zeichneParVersSynfkt(sf,par,zielpar)
         else zeichneParVersorgung( sf, par, zielpar )
      else zeichneParVersorgung( sf, par, zielpar );
     end   {Parameter war versorgt}
end;   {aenderelinienfuehrung}

procedure bestimmeID (* var sf: SemFktListe *);
var x,y,attrnr: integer;
    abbrechen,
    gefunden:   boolean;
    vok:        VokListe;
    hsf:        SemFktListe;
begin
hsf:= PTab[ aktPNr ].semRegeln; gefunden:= false;
while (hsf <> nil) and not gefunden do
  if (hsf^.semfkt = IDNT)
  then gefunden:= true
  else hsf:= hsf^.nxt;
if gefunden
then begin
     gefunden:= false;
     meldung( 33 );
     leave_meldung;
     CursorPos(y,x);
     repeat
       setCursor(y,x);
       fadenkreuz(y,x,abbrechen);
       if ev_char = kbd_$m3d
	then begin
	     meldung(33);
	     leave_meldung;
	     CursorPos(y,x)
	     end
       else if not abbrechen
        then begin
	    bestimmeTermoderAttr( y, x, vok, attrnr );
	    if (attrnr <> 0)
	    then begin
		 sf:= hsf;
		 while (sf <> nil) and not gefunden do
		   begin
		   if (sf^.semfkt = IDNT)
		   then if (sf^.zielpar^.vok = vok) and
			   (sf^.zielpar^.attr = attrnr) then gefunden:= true;
		   if not gefunden then sf:= sf^.nxt
		   end
		 end
	    end
       else sf:= nil
     until gefunden or abbrechen;
     end
else begin meldung( 34 ); sf:= nil end
end;   {bestimmeID}

procedure linienfuehrung;
const plusaktpar=true;
var x,y,
    index:  integer;
    fpar:   TypListe;
    par:    ParListe;
    sf:     SemFktListe;
    c:      char;
begin
meldung( 31 ); meldung( 32 ); 
antworte(semide,c);
clearmeldung;
if (c = 'S')
then begin
     SFanklicken( sf, y, x );
     if (sf<>nil)
     then begin
	  loeschemenue( Gestalten );
          signatur1( sf );
          repeat
            meldung(20);
	    meldung(7);
            waehleformPar( plusaktpar, rbs.uRandvBild-gibazh(IconsUeberText), 
                           sf^.semfkt, 's', false, x, index, fpar );
            clearmeldung;
            if (index <> 0)
            then begin
                 if (index > 0) then par:= sf^.zielpar else par:= sf^.quellpar;
                 for x:= 1 to abs(index)-1 do par:= par^.nxt;
                 aenderelinienfuehrung( sf, par, (index>0), true )
		 end
          until (index = 0);
          wrtmenue( Gestalten );
	  end
     end
else if (c = 'I') then
     begin
     bestimmeID( sf );
     if (sf <> nil) then aenderelinienfuehrung( sf, sf^.zielpar, true, true )
     end
end;   {linienfuehrung}

