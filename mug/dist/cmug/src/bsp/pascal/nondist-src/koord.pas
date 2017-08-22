




function VBreite (* vok: VokListe): integer *);
begin
case vok^.typ of
  term: if (TTab[vok^.t].sz1 = ' ')
	then VBreite:= dist( ord( TTab[vok^.t].name[0] )+1 )
	else if (TTab[vok^.t].sz2 = ' ')
	     then VBreite:= dist( 2 )
	     else VBreite:= dist( 3 );
  nont: VBreite:= dist( ord( NTTab[vok^.nt].name[0] )+1 )
  end;
end;   {VBreite}

procedure AttrBreite (* vok: VokListe; var iattr,gesattr: integer *);
var attrl: AListe;
    i:     integer;
begin
case vok^.typ of
  term: begin
	iattr:= 0; gesattr:= 0;
	end;
  nont: begin
	i:= 0;
	attrl:= vok^.spezInhA;
	if vok^.konsistent and (attrl = nil)
	then attrl:= NTTab[vok^.nt].inhAttr;
	while (attrl <> nil) do
	  begin i:= i+1; attrl:= attrl^.nxt end;
	iattr:= i*2*ASymb.breite;
	attrl:= vok^.spezDerA;
	if vok^.konsistent and (attrl = nil)
	then attrl:= NTTab[vok^.nt].derAttr;
	while (attrl <> nil) do
	  begin i:= i+1; attrl:= attrl^.nxt end;
	gesattr:= i*2*ASymb.breite
	end
  end {case}
end;   {AttrBreite}

procedure realeKoord (* n: integer *);   {n ist die Produktionsnummer}
const maxAnzSoehne = 30;
var vok,vorg: VokListe;
    sf: SemFktListe;
    ha: HAListe;
    min: real;
    breite,iattr: array [1..maxAnzSoehne] of integer;
    ges,anz,ue,d,dmin,dvok,dvorg: integer;

  procedure checkVorgaenger (v: VokListe; dv,index: integer);
  var vvorg: VokListe;
      dvv,pos,ue,i: integer;

  begin
  vvorg:= PTab[n].soehne; pos:= d div 2;
  for i:= 1 to index-1 do
    begin
    pos:= pos + d + breite[i];
    vvorg:= vvorg^.nxt
    end;
  dvv:= round( vvorg^.dx*rbs.xpixels );
  ue:= dvv - dv - d + dmin;
  if (ue > 0)
  then begin
       if ( abs(vvorg^.Y-v^.Y) > 2*rbs.R1 )
       then ue:= vvorg^.Y + dmin - v^.Y;
       if (ue > 0)
       then begin
	    dvv:= dvv - ue;
	    vvorg^.dx:= dvv/rbs.xpixels;
	    vvorg^.X:= pos + dvv + iattr[index];
	    if (index > 1) then checkVorgaenger( vvorg, dvv, index-1 )
	    end
       end
  end; {checkVorgaenger}

begin
min:= rbs.R1/rbs.vBildHoehe;
vok:= PTab[n].vater;
if (vok <> nil)
then begin
     AttrBreite( vok, anz, ges );
     ges:= ges + VBreite( vok ) + 1;
     d:= (rbs.xpixels-ges) div 2;
     dvok:= round( vok^.dx*rbs.xpixels );
     if (ges > rbs.xpixels+1)
     then begin			{Vater zu breit}
	  ue:= d + anz + dvok;
	  if (ue < 0)
	  then begin vok^.dx:= vok^.dx - ue/rbs.xpixels; dvok:= dvok - ue end
	  else begin
	       ue:= d + (ges - anz - VBreite( vok ) - 1) - dvok;
	       if (ue < 0)
	       then begin vok^.dx:= vok^.dx + ue/rbs.xpixels; dvok:= dvok+ue end
	       end;
	  meldung( 11 ); quitmeldung;
	  end
     else begin
	  if (abs(dvok) > d)
	  then begin			{Vater zu weit verschoben}
	       if (dvok < 0)
	       then dvok:= -d
	       else dvok:= d;
	       vok^.dx:= dvok/rbs.xpixels
	       end
	  end;
     vok^.X:= d + dvok + anz;
     if (vok^.dy <> 0)
     then begin
	  if (vok^.dy < -0.4 + min)
	  then vok^.dy:= -0.4 + min
	  else if (vok^.dy > 0.1 - min)
	       then vok^.dy:= 0.1 - min
          end;
     vok^.Y:= rbs.uRandvBild + round( rbs.vBildHoehe*(0.9+vok^.dy) );
     end;
{Ab hier Berechnung der Soehne}
vok:= PTab[n].soehne;
if (vok <> nil)
then begin
     dmin:= 10  ;{ ASymb.breite div 2;	legt den Mindestabstand zwischen Vokabeln fest}
     ges:= 0; anz:= 0;
     repeat
     anz:= anz+1;
     AttrBreite( vok, iattr[anz], breite[anz] );
     breite[anz]:= (breite[anz] + VBreite( vok ) + 1);   
     ges:= ges + breite[anz];
     if (vok^.dy <> 0)
     then begin
	  if (vok^.dy < -0.2 + min)
	  then vok^.dy:= -0.2 + min
	  else if (vok^.dy > 0.3 - min)
	       then vok^.dy:= 0.3 - min
	  end;
     vok^.Y:= rbs.uRandvBild + round( (0.2+vok^.dy) * rbs.vBildHoehe );
     vok:= vok^.nxt
     until (vok = nil);
     vok:= PTab[n].soehne;
     if ((ges + anz*dmin) <= (rbs.xpixels+1))
     then begin   {genuegend Platz fuer Vokabeln vorhanden}
	  d:= (rbs.xpixels + 1 - ges) div anz;
	  anz:= 1;
	  dvok:= round( vok^.dx * rbs.xpixels );
	  if (dvok < -(d div 2))
	  then begin
	       dvok:= -(d div 2);
	       vok^.dx:= dvok/rbs.xpixels
	       end;
	  vok^.X:= (d div 2) + dvok + iattr[1];
	  ges:= (d div 2) + breite[1] + d;
	  vorg:= vok; vok:= vok^.nxt;
	  while (vok <> nil) do
	    begin
	    anz:= anz+1; dvorg:= dvok;
	    dvok:= round( vok^.dx * rbs.xpixels );
	    ue:= dvorg - dvok -d  + dmin;{ eventuelle Ueberlappung in X-Richtung}
	    if (ue > 0)  
	    then begin
		 if (abs(vorg^.Y-vok^.Y) <= 2*rbs.R1)
		 then begin 		      {ueberlappt in X- und Y-Richtung}
		      if (dvok < 0)
		      then begin
			   if (dvorg < 0)
			   then dvok:= dmin - d + dvorg
			   else begin
				if (dvorg < ue)
				then begin dvorg:= 0; dvok:= dmin - d end
				else if (-dvok < ue)
				     then begin
					  dvok:= 0; dvorg:= d - dmin
					  end
	  			     else begin
					  dvok:= dvok + ((ue+1) div 2);
					  dvorg:= dvorg - ((ue+1) div 2)
					  end;
				vorg^.dx:= dvorg/rbs.xpixels;
				vorg^.X:=ges-d-breite[anz-1]+iattr[anz-1]+dvorg;
				if (anz > 2) then
				checkVorgaenger( vorg, dvorg, anz-2 )
				end;
			   vok^.dx:= dvok/rbs.xpixels
			   end
		      else begin
			   dvorg:= d - dmin + dvok;
			   vorg^.dx:= dvorg/rbs.xpixels;
			   vorg^.X:= ges-d-breite[anz-1] + iattr[anz-1] + dvorg;
			   if (anz > 2) then
			   checkVorgaenger( vorg, dvorg, anz-2 )
			   end;
		      end {Ueberlappung in X- und Y-Richtung}
		 else begin {ueberlappt nur in X-Richtung}
		      ue:= vorg^.X + dmin - (ges + dvok + iattr[anz]);
		      if (ue > 0)
		      then begin   {die richtige Reihenfolge der Vokabeln waere}
			   if (dvok < 0)     {optisch nicht mehr gewaehrleistet}
			   then begin
				if (dvorg < 0)
				then dvok:= dvok + ue
				else begin
				     if (dvorg < ue)
				     then begin
					  dvok:= dvok + ue - dvorg;
					  dvorg:= 0
					  end
				     else if (-dvok < ue)
					  then begin
					       dvorg:= dvorg - ue - dvok;
					       dvok:= 0
					       end
					  else begin
					       dvorg:= dvorg - ((ue+1) div 2);
					       dvok:= dvok + ((ue+1) div 2)
					       end;
				     vorg^.dx:= dvorg/rbs.xpixels;
				     vorg^.X:= ges - d - breite[anz-1]
						       + iattr[anz-1] + dvorg;
				     if (anz > 2) then
				     checkVorgaenger( vorg, dvorg, anz-2 )
				     end;
				vok^.dx:= dvok/rbs.xpixels;
				end
			   else begin
				dvorg:= dvorg - ue;
				vorg^.dx:= dvorg/rbs.xpixels;
				vorg^.X:=ges-d-breite[anz-1]+iattr[anz-1]+dvorg;
				if (anz > 2) then
				checkVorgaenger( vorg, dvorg, anz-2 )
				end
			   end
		      end {Ueberlappung nur in X-Richtung}
		 end; {Ueberlappung ueberhaupt}
	    vok^.X:= ges + dvok + iattr[anz];
	    ges:= ges + d + breite[anz];
	    vorg:= vok; vok:= vok^.nxt
	    end; {while}     {nach while-Schleife zeigt vorg auf letzte Vokabel}
	  if (dvok > (d div 2))
	  then begin 	     {letzte Vokabel ist zu weit nach rechts verschoben}
	       dvok:= d div 2;
	       vorg^.dx:= dvok/rbs.xpixels;
	       vorg^.X:= ges - d - breite[anz] + iattr[anz] + dvok;
	       if (anz > 1) then checkVorgaenger( vorg, dvok, anz-1 )
	       end
	  end     {Platz reicht aus}
     else begin	  {Gesamtplatzbedarf ist zu gross}
	  d:= (rbs.xpixels + 1 - ges) div (anz - 1);
	  ges:= 0; anz:= 0;
	  repeat   {da Platzbedarf zu gross muss es mindestens einen Sohn geben}
	    anz:= anz+1;
	    vok^.X:= ges + iattr[anz];
	    if (vok^.X < 0)
	    then vok^.X:= 0
	    else if (vok^.X+VBreite(vok) > rbs.xpixels)        

		 then vok^.X:= rbs.xpixels - VBreite(vok);
	    if odd(anz)
	    then begin
		 if (vok^.dy < -0.25+min)
		 then vok^.dy:= -0.25+min;
		 vok^.Y:= rbs.uRandvBild + round((0.25+vok^.dy)*rbs.vBildHoehe)
		 end
	    else begin
		 if (vok^.dy < -0.15+min)
		 then vok^.dy:= -0.15+min;
	         vok^.Y:= rbs.uRandvBild + round((0.15+vok^.dy)*rbs.vBildHoehe)
		 end;
	    ges:= ges + d + breite[anz];
	    vok:= vok^.nxt
	  until (vok = nil);
	  meldung( 12 ); quitmeldung; 
	  end
     end;  {es gibt Soehne, d.h. PTab[n].soehne <> nil}
sf:= PTab[n].semRegeln;
while (sf <> nil) do
  begin
  if (sf^.semfkt <> IDNT)
  then begin
       d:= round( sf^.vx * rbs.xpixels );
       if (d < rbs.R1)
       then begin d:= rbs.R1; sf^.vx:= d/rbs.xpixels end
       else begin
            ges:= dist( ord( SFTab[sf^.semfkt].name[0] ) ) + rbs.R1;
            if (d+ges > rbs.xpixels)
            then begin d:= rbs.xpixels-ges; sf^.vx:= d/rbs.xpixels end
            end;
       sf^.X:= d;
       d:= round( sf^.vy * rbs.vBildHoehe );
       if (d < rbs.R1)
       then begin d:= rbs.R1; sf^.vy:= d/rbs.vBildHoehe end
       else if (d > rbs.vBildHoehe-rbs.R1)
            then begin d:= rbs.vBildHoehe-rbs.R1; sf^.vy:= d/rbs.vBildHoehe end;
       sf^.Y:= rbs.uRandvBild + d;
       end;
  sf:= sf^.nxt
  end;
ha:= PTab[n].hilfsAttr;
while (ha <> nil) do
  begin
  d:= round( ha^.vx * rbs.xpixels );
  if (d < 0)
  then begin d:= 0; ha^.vx:= 0 end
  else if (d > rbs.xpixels-ASymb.breite)
       then begin d:= rbs.xpixels-ASymb.breite; ha^.vx:= d/rbs.xpixels end;
  ha^.X:= d;
  d:= round( ha^.vy * rbs.vBildHoehe );
  if (d < 0)
  then begin d:= 0; ha^.vy:= 0 end
  else if (d > rbs.vBildHoehe-ASymb.hoehe)
       then begin d:= rbs.vBildHoehe-ASymb.hoehe; ha^.vy:= d/rbs.vBildHoehe end;
  ha^.Y:= rbs.uRandvBild + d;
  ha:= ha^.nxt
  end;
end; {realeKoord}

