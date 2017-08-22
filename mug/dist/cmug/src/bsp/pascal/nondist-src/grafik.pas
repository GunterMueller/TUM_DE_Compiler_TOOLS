





procedure linie (* y1,x1,y2,x2: integer*);
var x,y:gpr_$coordinate_array_t;
begin                     
 x[1]:=x1;
 x[2]:=x2;
 y[1]:=rbs.ypixels-y1;
 y[2]:=rbs.ypixels-y2;
 gpr_$multiline(x,y,2,status);
end; {linie}

procedure box (* y1,x1,y2,x2: integer *);
begin
 gpr_$draw_box(x1,rbs.ypixels-y1,x2,rbs.ypixels-y2,status);
end; {box}

procedure pfeil (* y1,x1,y2,x2: integer *); {Spitze bei Punkt 2}
const  k   = 6;                {Laenge der Spitze in Pixel}
       pi  = 3.14;
var q,c30,s30: real;
    dx,dy,x3,y3,x4,y4: integer;
    x,y:gpr_$coordinate_array_t;
begin
c30 := cos(pi/6);              {Kosinus des Drehwinkels = 30 Grad}
s30 := sin(pi/6);              {Sinus des Drehwinkels = 30 Grad}
dx := x1 - x2; dy := y1 - y2;
if (dx <> 0) or (dy <> 0)
then begin
     q := k/sqrt( dx*dx + dy*dy );  {Faktor zur Skalierung der Pfeilspitze}
     x3 := round( q*( c30*dx + s30*dy ) ) + x2;
     y3 := round( q*( c30*dy - s30*dx ) ) + y2;
     x4 := round( q*( c30*dx - s30*dy ) ) + x2;
     y4 := round( q*( c30*dy + s30*dx ) ) + y2; 
     x[1]:=x1;
     x[2]:=x2;
     x[3]:=x2;
     x[4]:=x3;
     x[5]:=x2;
     x[6]:=x4;
     y[1]:=rbs.ypixels-y1;
     y[2]:=rbs.ypixels-y2;
     y[3]:=rbs.ypixels-y2;
     y[4]:=rbs.ypixels-y3;
     y[5]:=rbs.ypixels-y2;
     y[6]:=rbs.ypixels-y4;
     gpr_$multiline(x,y,6,status);
     end
end; {pfeil}

procedure spitze (* y1,x1,y2,x2: integer *); {Spitze bei Punkt 2}
const  k   = 6;                {Laenge der Spitze in Pixel}
       pi  = 3.14;
var q,c30,s30: real;
    dx,dy,x3,y3,x4,y4: integer; 
    x,y:gpr_$coordinate_array_t;
begin
c30 := cos(pi/6);              {Kosinus des Drehwinkels = 30 Grad}
s30 := sin(pi/6);              {Sinus des Drehwinkels = 30 Grad}
dx := x1 - x2; dy := y1 - y2;
if (dx <> 0) or (dy <> 0)
then begin
     q := k/sqrt( dx*dx + dy*dy );  {Faktor zur Skalierung der Pfeilspitze}
     x3 := round( q*( c30*dx + s30*dy ) ) + x2;
     y3 := round( q*( c30*dy - s30*dx ) ) + y2;
     x4 := round( q*( c30*dx - s30*dy ) ) + x2;
     y4 := round( q*( c30*dy + s30*dx ) ) + y2;
     x[1]:=x2;
     x[2]:=x3;
     x[3]:=x2;
     x[4]:=x4;
     y[1]:=rbs.ypixels-y2;
     y[2]:=rbs.ypixels-y3;
     y[3]:=rbs.ypixels-y2;
     y[4]:=rbs.ypixels-y4;
     gpr_$multiline(x,y,4,status);
     end
{bei Abstand 0 wird keine Spitze gezeichnet}
end; {spitze}

procedure halbkreis (* ym,xm,r:integer; rechts: boolean *);
var dx,dy,alpha: real;
    x,y: integer;
begin
alpha := 1/r;  dx :=  0;  x := xm;
if rechts
then begin dy :=  r; y := ym + r end
else begin dy := -r; y := ym - r end;
repeat
   begin 
   setCursor(y,x);
   gpr_$line(x,rbs.ypixels-y,status);
   dx := dx + alpha*dy;    {dx und dy haben rechts noch die alten Werte}
   dy := dy - alpha*dx;    {dx hat bereits den neuen Wert,yneu:=yalt-a*xneu}
   x := round(xm + dx);
   y := round(ym + dy);
   end
until x = xm;
end; {halbkreis}

procedure zeichneVokabel (* vok: VokListe *);
var y,x,laenge: integer;
    symbol:     ASymbTyp;
    h:	        AListe;
    color:gpr_$pixel_value_t;

begin    
gpr_$inq_draw_value(color,status);
setCursor( vok^.Y-rbs.deltaY, vok^.X+rbs.deltaX );
case vok^.typ of
  term: begin 
        if color <> -2 
         then begin
               gpr_$set_draw_value(color_t,status);
               gpr_$set_text_value(color_t,status); 
              end;
	    with TTab[vok^.t] do
	  begin
	  if (sz1 = ' ')
	  then begin
	       laenge:= dist( ord( name[0] ) + 1 );
	       wrtIdent( name )
	       end
	  else begin
	       gpr_$text(sz1,1,status);
	       if (sz2 = ' ')
	       then laenge:= dist(2)
	       else begin laenge:= dist(3); gpr_$text(sz2,1,status) end
	       end
	  end
	end;
  nont: begin
         if color <>-2 
          then begin  
                gpr_$set_draw_value(color_nt,status);
                gpr_$set_text_value(color_nt,status);
               end;
	laenge:= dist ( ord( NTTab[vok^.nt].name[0] ) + 1 );
	wrtIdent( NTTab[vok^.nt].name )
	end
end;   {case}
with rbs,vok^ do
  box( Y+R1, X, Y-R1, X+laenge );
if (vok^.typ = nont)
then begin
     y:= vok^.Y - (ASymb.hoehe div 2);
     h:= vok^.spezInhA;
     if vok^.konsistent and (h = nil)
     then h:= NTTab[vok^.nt].inhAttr;
     x:= vok^.X;
     while (h <> nil) do
	begin                       		    {Hierdurch wird der Abstand}
	x:= x - 2*ASymb.breite;   			   {der Ikon's bestimmt}
	if (x < 0)
	then h:= nil
	else begin
	     symbol:=  ATab[ h^.attr ].symbol ;
	     writeikon( y, x, symbol ); 
	     h:= h^.nxt
	     end
	end;
     h:= vok^.spezDerA;
     if vok^.konsistent and (h = nil)
     then h:= NTTab[vok^.nt].derAttr;
     x:= vok^.X + laenge - ASymb.breite + 1;
     while (h <> nil) do
	begin
	x:= x + 2*ASymb.breite;
	if ((x + ASymb.breite - 1) > rbs.xpixels)
	then h:= nil
	else begin
	     symbol:=  ATab[ h^.attr ].symbol ;
	     writeikon( y, x, symbol ); 
	     h:= h^.nxt
	     end
	end
     end; {if nont then}
 if color<>-2 then gpr_$set_draw_value(color_base,status);
 if color<>-2 then gpr_$set_text_value(color_base,status);
end; {zeichneVokabel}

procedure polygon (* var y1,x1,y2,x2: integer; r1,r2:integer; var pl: PunktListe *);
var hy,ly,hx,lx: char;
    abstand:     real;
    x,y:         integer;
    issynt:      boolean; 
begin
if r2=-1 then begin
               r2:=0;
               issynt:=true;
              end
         else issynt:=false; 
x:= round(pl^.vx * rbs.xpixels);
y:= round(pl^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
abstand:= sqrt( (x1-x)*(x1-x) + (y1-y)*(y1-y) );
if (abstand <> 0)
then begin
     x1:= x1 + round( r1/abstand*(x-x1) );
     y1:= y1 + round( r1/abstand*(y-y1) );
     end;   
setCursor(y1,x1);
gpr_$line(x1,rbs.ypixels-y1,status);
{tekadr(y1,x1,hy,ly,hx,lx);
write(chr(29),hy,ly,hx,lx);
tekadr(y,x,hy,ly,hx,lx);}
{setCursor(y,x);}
gpr_$line(x,rbs.ypixels-y,status);
{write(hy,ly,hx,lx);}
pl:= pl^.nxt;
while (pl <> nil) do
  begin
  x:= round(pl^.vx * rbs.xpixels);
  y:= round(pl^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
  {setCursor(y,x);}
  gpr_$line(x,rbs.ypixels-y,status);
  {tekadr(y,x,hy,ly,hx,lx);
  write(hy,ly,hx,lx); }
  pl:= pl^.nxt
  end;
abstand:= sqrt( (x2-x)*(x2-x) + (y2-y)*(y2-y) );
if (abstand <> 0)
then begin
     if not issynt 
      then begin
            x2:= x2 + round( r2/abstand*(x-x2) );
            y2:= y2 + round( r2/abstand*(y-y2) );
           end;   
     {setCursor(y2,x2);}
     gpr_$line(x2,rbs.ypixels-y2,status);
     {tekadr(y2,x2,hy,ly,hx,lx);
     write(hy,ly,hx,lx,chr(31));}
     if not issynt then spitze(y,x,y2,x2)
     end
else ;
end;   {polygon}


procedure spl(* y1,x1,r1,yn,xn,rn: integer; pktl: PunktListe *);
const maxanzpunkte = 31;
var abstand: real;
    i,n,j: integer;
    ix,iy,sx,sy: array [1..maxanzpunkte] of integer;
    pl: PunktListe;
    issynt: boolean;
  
  procedure copy;
  begin
  i:=succ(i);
  ix[i]:=ix[j]; iy[i]:=iy[j];
  j:=succ(j);
  end (*copy*);

begin (*spl*)
if rn=-1 then begin
               rn:=0;
               issynt:=true
              end
         else issynt:=false;
ix[1] := x1;
iy[1] := y1;
i:=1; pl:=pktl;
while pl<>nil do
  begin
  i:=succ(i); 
  with rbs, pl^ do
    begin
    ix[i]:=trunc(vx*xpixels); iy[i]:=trunc(vy*vBildHoehe+uRandvBild); 
    end;
  pl:=pl^.nxt;
  end; 
n := succ(i);
abstand := sqrt( (xn-ix[n-1])*(xn-ix[n-1]) + (yn-iy[n-1])*(yn-iy[n-1]) );
ix[n] := xn - round( (rn+6)/abstand*(xn-ix[n-1]) );
iy[n] := yn - round( (rn+6)/abstand*(yn-iy[n-1]) );
n := n + 1;
ix[n] := xn - round( rn/abstand*(xn-ix[n-2]) );
iy[n] := yn - round( rn/abstand*(yn-iy[n-2]) );
abstand := sqrt( (x1-ix[2])*(x1-ix[2]) + (y1-iy[2])*(y1-iy[2]) );
ix[1] := x1 - round( r1/abstand*(x1-ix[2]) );
iy[1] := y1 - round( r1/abstand*(y1-iy[2]) );
i:=1; j:=2;
while j<=n do
  begin
  if ix[i]<>ix[j] then copy else if iy[i]<>iy[j] then copy else j:=succ(j);
  end;
n := i;
if n = 3 then
  if not issynt then pfeil (iy[1], ix[1], iy[n], ix[n])
                else linie (iy[1], ix[1], yn, xn)
else 
  begin
  spitze(iy[n-1], ix[n-1], iy[n], ix[n]);
  setCursor(iy[1],ix[1]);
  for i := 2 to n do      (* Punktliste ohne ersten Punkt kopieren *)
    begin
    sx[i-1] := ix[i];
    sy[i-1] := rbs.ypixels - iy[i]
    end;
  gpr_$spline_cubic_p(sx,sy,n-1,status);
  end
end (*spl*);


procedure zeichneParVersSynfkt (* sf: SemFktListe; apar: ParListe; zielpar: boolean *);
 var laenge,z,xkoord,ykoord,i,abstand: integer;
    gedr: boolean;
      par:ParListe;          
      color:gpr_$pixel_value_t;

procedure zP (x,y:integer);
var x1,y1,x2,y2,r1,r2,xr,yr: integer;
    punkte:	   PunktListe;
    abstand:       real;
    versorgt,
    gefunden:      boolean; 


  procedure parkoord (var y,x,r: integer; par: ParListe);
  var i,dx,dy: integer;
      al:      AListe;
      hal:     HAListe;
      zweiRefPkte: boolean;
  begin
  gefunden:= false; versorgt:= true;
  if (par^.attr <> 0)
  then begin   {Attr oder HAttr}
       r:= ASymb.R2;
       if (par^.vok <> nil)
       then begin   {Attr von NT}
	    if (par^.vok^.typ <> nont)
	    then wrtERR1('Vokabel muesste NT sein')
	    else  begin
	 	  i:= 0;
	  	  case ATab[par^.attr].art of
	    	   inh: begin
		        al:= par^.vok^.spezInhA;
		        if (al = nil) and par^.vok^.konsistent
		        then al:= NTTab[par^.vok^.nt].inhAttr;
		        while not gefunden and (al <> nil) do
		          begin
		   	  i:= i+1;
		   	  if (al^.attr = par^.attr)
		   	  then gefunden:= true
		   	  else al:= al^.nxt
		   	  end;
		        x:= par^.vok^.X - 2*i*ASymb.breite + (ASymb.breite div 2);
		        end;
	    	   der: begin
		        al:= par^.vok^.spezDerA;
		        if (al = nil) and par^.vok^.konsistent
		        then al:= NTTab[par^.vok^.nt].derAttr;
		        while not gefunden and (al <> nil) do
		   	  begin
		   	  i:= i+1;
		   	  if (al^.attr = par^.attr)
		   	  then gefunden:= true
		   	  else al:= al^.nxt
		          end;
		        x:= par^.vok^.X + dist(ord(NTTab[par^.vok^.nt].name[0])+1)+1
				     + 2*i*ASymb.breite - (ASymb.breite div 2);
		        end;
	     	   aux: wrtERR1('Attribut darf nicht vom Typ auxiliary sein')
	  	  end;   {case}
	          y:= par^.vok^.Y
	          end
	    end
       else begin   {Hilfsattribut}
	    hal:= PTab[ aktPNr ].hilfsAttr;
	    while not gefunden and (hal <> nil) do
	      if (hal^.attr = par^.attr)
	      then gefunden:= true
	      else hal:= hal^.nxt;
	    if gefunden
	    then begin
	         x:= hal^.X + (ASymb.breite div 2);
	         y:= hal^.Y + (ASymb.hoehe div 2);
	         end
	    end;
       if not gefunden then wrtERR1('Attribut nicht gefunden!')
       end
  else begin  {attrnr = 0}
       if (par^.vok <> nil)
       then begin   	{Terminal}
	    if (par^.vok^.typ <> term)
	    then wrtERR1('Vokabel muesste Terminal sein  ')
	    else begin
	         gefunden:= true; r:= 0;	       
		 zweiRefPkte:= false;
		 if (punkte <> nil)
		 then begin
		      xr:= round(punkte^.vx * rbs.xpixels);
		      yr:= round(punkte^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
		      end
		 else if (sf^.semfkt = IDNT)
		      then begin xr:= x1; yr:= y1 end
		      else begin xr:= sf^.X; yr:= sf^.Y; zweiRefPkte:= true end;
		 {falls semFkt links vom Terminal liegt muss zweiter}
		 {Referenzpunkt beruecksichtigt werden}
		 i:= VBreite( par^.vok );
	         x:= par^.vok^.X; dx:= x - xr;
	         y:= par^.vok^.Y; dy:= y - yr;
		 if (dy+rbs.R1 < 0)
		 then begin			{RefPkt oberhalb des Terminals}
		      y:= y + rbs.R1;
		      if (dx > -dy - rbs.R1)
		      then begin 	     {RefPkt unterhalb linker Diagonale}
			   if zweiRefPkte
			   then begin
			       dx:= dx - dist(ord( SFTab[sf^.semfkt].name[0] ));
			       if (dx <= -dy - rbs.R1) then x:= x + (i div 2);
				end          {RefPkt oberhalb linker Diagonale}
			   end
		      else if (-dx -i > -dy - rbs.R1)
			   then x:= x + i  {RefPkt unterhalb rechter Diagonale}
			   else x:= x + (i div 2);  {RefPkt zwischen den Diag.}
		      end
		 else if (dy - rbs.R1 > 0)
		 then begin	     		{RefPkt unterhalb des Terminals}
		      y:= y - rbs.R1;
		      if (dx > dy - rbs.R1)
		      then begin	    {RefPkt oberhalb linker Diagonale}
			   if zweiRefPkte
			   then begin
			       dx:= dx - dist(ord( SFTab[sf^.semfkt].name[0] ));
			       if (dx <= dy - rbs.R1) then x:= x + (i div 2);
				end          {RefPkt unterhalb linker Diagonale}
			   end
		      else if (-dx -i > dy - rbs.R1)
			   then x:= x + i   {RefPkt oberhalb rechter Diagonale}
			   else x:= x + (i div 2);  {RefPkt zwischen den Diag.}
		      end
		 else if (dx < 0) then x:= x + i; {RefPkt liegt rechts vom Term}
				  {else         RefPkt liegt links vom Terminal}
	         end
	    end
       else versorgt:= false   {aktueller Parameter ist nicht versorgt}
       end;
  end;  {parkoord}

begin  
punkte:= apar^.verb;
if (sf^.semfkt = IDNT)
then begin
     parkoord( y1, x1, r1, sf^.zielpar );
     (*if gefunden then parkoord( y2, x2, r2, sf^.quellpar )*)
     end
else begin
     parkoord( y1, x1, r1, apar );
     if gefunden
     then begin
	  if (punkte = nil)
	  then begin xr:= x1; yr:= y1 end
	  else begin
	       if not zielpar
	       then while (punkte^.nxt <> nil) do punkte:= punkte^.nxt;
	       {falls kein Zielparameter, dann ist der letzte Zwischenpunkt}
	       {der Referenzpunkt}
	       xr:= round(punkte^.vx * rbs.xpixels);
	       yr:= round(punkte^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
	       end;
	  (*r2:= rbs.R1; y2:= sf^.Y;
          if (xr < sf^.X)
     	  then x2:= sf^.X		    
     	  else begin
	       x2:= sf^.X + dist( ord( SFTab[sf^.semfkt].name[0] ) );
	       if (xr < x2)
	       then begin              	   
		    x2:= xr; r2:= 0;
		    if (yr > y2)
		    then y2:= y2 + rbs.R1
		    else y2:= y2 - rbs.R1
		    end
	       end*)
	  end
     end;
if gefunden
then begin
     x2:=x; y2:=y; 
     punkte:= apar^.verb;
     if (punkte = nil)
     then begin
	  abstand:= sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
          if (abstand <> 0)
          then begin
		y1:= y1+ round( r1/abstand*(y2-y1) );
	        x1:= x1 + round( r1/abstand*(x2-x1) ); 
	       if zielpar
                then pfeil( y2, x2, y1, x1)
	        else linie( y1, x1, y2, x2);
               end
	  end
     else if (Verbindung = Poly)
	  then if zielpar
	       then polygon( y2, x2, y1, x1, 0 , r1, punkte )
	       else polygon( y1, x1, y2, x2, r1, -1, punkte )
	  else if zielpar
	       then spl( y2, x2, 0, y1, x1, r1, punkte )
	       else spl( y1, x1, r1, y2, x2, -1, punkte )
     end
else if (sf^.semfkt = IDNT)
     then begin
          gibfreiSF( aktPNr, sf ); wrtERR1('Identitaet geloescht')
	  end
     else if versorgt
          then begin
               wrtERR3('Parameterversorgung geloescht!  AttrNr:',apar^.attr);
               apar^.vok:= nil;
               apar^.attr:= 0;
               apar^.verb:= nil;
               end
end;   {zP}
  begin 
       gpr_$inq_draw_value(color,status);
       if color<>-2 then gpr_$set_draw_value(color_sy,status);
       par:=apar;
       gedr:= sf^.gedreht;
       with rbs,sf^ do
         begin
                apar:=quellpar;
                i:=0;
                while apar<>nil do
                  begin
                   i:=i+1;
                   apar:=apar^.nxt
                  end; 
                if i > ord(SFTab[semfkt].name[0])
                 then begin
                      laenge:=dist(i);
                      end
                 else begin
                       laenge:= dist (ord( SFTab[semfkt].name[0] ) );
                      end; 
                if i<>0 
                 then begin
                       while (laenge mod dist(i)) <> 0 do
                        begin
                         laenge:=laenge+1;
                        end;
                      end;
                if i<>0 
                 then begin
                       abstand:=laenge div dist(i);
                       abstand:=dist(abstand); 
                      end; 
         end; {with}
         apar:=par;
         par:=sf^.quellpar; 
         if not zielpar
          then begin 
             xkoord:=sf^.X+(abstand div 2);
             if gedr then ykoord:=sf^.Y+rbs.R1+10 else ykoord:=sf^.Y-rbs.R1-10;
             while par <> apar do
              begin
               par:=par^.nxt;
               xkoord:=xkoord+abstand
              end
            end
          else begin
                if gedr then ykoord:=sf^.Y-rbs.R1-10 else ykoord:=sf^.Y+rbs.R1+10;
                xkoord:=sf^.X+laenge div 2
               end;
        zP(xkoord,ykoord);                             
if color<>-2 then gpr_$set_draw_value(color_base,status);
if color<>-2 then gpr_$set_text_value(color_base,status);
end; {zeichneParVersSynfkt}


procedure zeichneParVersorgung (* sf: SemFktListe; apar: ParListe; zielpar: boolean *);
var x1,y1,x2,y2,r1,r2,xr,yr: integer;
    punkte:	   PunktListe;
    abstand:       real;
    versorgt,
    gefunden:      boolean;
    zeichne :   boolean;
    color:gpr_$pixel_value_t;

  procedure parkoord (var y,x,r: integer; par: ParListe);
  var i,dx,dy: integer;
      al:      AListe;
      hal:     HAListe;
      zweiRefPkte: boolean;
  begin
  gefunden:= false; versorgt:= true;
  if (par^.attr <> 0)
  then begin   {Attr oder HAttr}
       r:= ASymb.R2;
       if (par^.vok <> nil)
       then begin   {Attr von NT}
	    if (par^.vok^.typ <> nont)
	    then wrtERR1('Vokabel muesste NT sein')
	    else  begin
	 	  i:= 0;
	  	  case ATab[par^.attr].art of
	    	   inh: begin
		        al:= par^.vok^.spezInhA;
		        if (al = nil) and par^.vok^.konsistent
		        then al:= NTTab[par^.vok^.nt].inhAttr;
		        while not gefunden and (al <> nil) do
		          begin
		   	  i:= i+1;
		   	  if (al^.attr = par^.attr)
		   	  then gefunden:= true
		   	  else al:= al^.nxt
		   	  end;
		        x:= par^.vok^.X - 2*i*ASymb.breite + (ASymb.breite div 2);
		        end;
	    	   der: begin
		        al:= par^.vok^.spezDerA;
		        if (al = nil) and par^.vok^.konsistent
		        then al:= NTTab[par^.vok^.nt].derAttr;
		        while not gefunden and (al <> nil) do
		   	  begin
		   	  i:= i+1;
		   	  if (al^.attr = par^.attr)
		   	  then gefunden:= true
		   	  else al:= al^.nxt
		          end;
		        x:= par^.vok^.X + dist(ord(NTTab[par^.vok^.nt].name[0])+1)+1
				     + 2*i*ASymb.breite - (ASymb.breite div 2);
		        end;
	     	   aux: wrtERR1('Attribut darf nicht vom Typ auxiliary sein')
	  	  end;   {case}
	          y:= par^.vok^.Y
	          end
	    end
       else begin   {Hilfsattribut}
	    hal:= PTab[ aktPNr ].hilfsAttr;
	    while not gefunden and (hal <> nil) do
	      if (hal^.attr = par^.attr)
	      then gefunden:= true
	      else hal:= hal^.nxt;
	    if gefunden
	    then begin
	         x:= hal^.X + (ASymb.breite div 2);
	         y:= hal^.Y + (ASymb.hoehe div 2);
	         end
	    end;
       if not gefunden then wrtERR1('Attribut nicht gefunden!')
       end
  else begin  {attrnr = 0}
       if (par^.vok <> nil)
       then begin   	{Terminal}
	    if (par^.vok^.typ <> term)
	    then wrtERR1('Vokabel muesste Terminal sein  ')
	    else begin
	         gefunden:= true; r:= 0;	       
		 zweiRefPkte:= false;
		 if (punkte <> nil)
		 then begin
		      xr:= round(punkte^.vx * rbs.xpixels);
		      yr:= round(punkte^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
		      end
		 else if (sf^.semfkt = IDNT)
		      then begin xr:= x1; yr:= y1 end
		      else begin xr:= sf^.X; yr:= sf^.Y; zweiRefPkte:= true end;
		 {falls semFkt links vom Terminal liegt muss zweiter}
		 {Referenzpunkt beruecksichtigt werden}
		 i:= VBreite( par^.vok );
	         x:= par^.vok^.X; dx:= x - xr;
	         y:= par^.vok^.Y; dy:= y - yr;
		 if (dy+rbs.R1 < 0)
		 then begin			{RefPkt oberhalb des Terminals}
		      y:= y + rbs.R1;
		      if (dx > -dy - rbs.R1)
		      then begin 	     {RefPkt unterhalb linker Diagonale}
			   if zweiRefPkte
			   then begin
			       dx:= dx - dist(ord( SFTab[sf^.semfkt].name[0] ));
			       if (dx <= -dy - rbs.R1) then x:= x + (i div 2);
				end          {RefPkt oberhalb linker Diagonale}
			   end
		      else if (-dx -i > -dy - rbs.R1)
			   then x:= x + i  {RefPkt unterhalb rechter Diagonale}
			   else x:= x + (i div 2);  {RefPkt zwischen den Diag.}
		      end
		 else if (dy - rbs.R1 > 0)
		 then begin	     		{RefPkt unterhalb des Terminals}
		      y:= y - rbs.R1;
		      if (dx > dy - rbs.R1)
		      then begin	    {RefPkt oberhalb linker Diagonale}
			   if zweiRefPkte
			   then begin
			       dx:= dx - dist(ord( SFTab[sf^.semfkt].name[0] ));
			       if (dx <= dy - rbs.R1) then x:= x + (i div 2);
				end          {RefPkt unterhalb linker Diagonale}
			   end
		      else if (-dx -i > dy - rbs.R1)
			   then x:= x + i   {RefPkt oberhalb rechter Diagonale}
			   else x:= x + (i div 2);  {RefPkt zwischen den Diag.}
		      end
		 else if (dx < 0) then x:= x + i; {RefPkt liegt rechts vom Term}
				  {else         RefPkt liegt links vom Terminal}
	         end
	    end
       else versorgt:= false   {aktueller Parameter ist nicht versorgt}
       end;
  end;  {parkoord}

begin
zeichne := true;
punkte:= apar^.verb;
gpr_$inq_draw_value(color,status);                      
if color<>-2 then gpr_$set_draw_value(color_sem,status);
if (sf^.semfkt = IDNT)
then 
      if EXTENSIV
      then begin 
           if color<>-2 then gpr_$set_draw_value(color_id,status);
           if color<>-2 then gpr_$set_text_value(color_id,status);
           parkoord( y1, x1, r1, sf^.zielpar );
           if gefunden then parkoord( y2, x2, r2, sf^.quellpar )
           end 
      else      
           zeichne := false

else begin
     parkoord( y1, x1, r1, apar );
     if gefunden
     then begin
	  if (punkte = nil)
	  then begin xr:= x1; yr:= y1 end
	  else begin
	       if not zielpar
	       then while (punkte^.nxt <> nil) do punkte:= punkte^.nxt;
	       {falls kein Zielparameter, dann ist der letzte Zwischenpunkt}
	       {der Referenzpunkt}
	       xr:= round(punkte^.vx * rbs.xpixels);
	       yr:= round(punkte^.vy * rbs.vBildHoehe) + rbs.uRandvBild;
	       end;
	  r2:= rbs.R1; y2:= sf^.Y;
          if (xr < sf^.X)
     	  then x2:= sf^.X		     {Attr liegt links von sem Funktion}
     	  else begin
	       x2:= sf^.X + dist( ord( SFTab[sf^.semfkt].name[0] ) );
	       if (xr < x2)
	       then begin              	   {Attr liegt ueber oder unter sem Fkt}
		    x2:= xr; r2:= 0;
		    if (yr > y2)
		    then y2:= y2 + rbs.R1
		    else y2:= y2 - rbs.R1
		    end
 	       {else 			     Attr liegt rechts von sem Funktion}
	       end
	  end
     end;
if gefunden 
then
  if zeichne
     then
  begin
     punkte:= apar^.verb;
     if (punkte = nil)
     then begin
	  abstand:= sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
          if (abstand <> 0)
          then begin
	       if zielpar
	       then pfeil( y2 - round( r2/abstand*(y2-y1) ),
	                   x2 - round( r2/abstand*(x2-x1) ),
		           y1 + round( r1/abstand*(y2-y1) ),
	                   x1 + round( r1/abstand*(x2-x1) )  )
	       else pfeil( y1 + round( r1/abstand*(y2-y1) ),
	                   x1 + round( r1/abstand*(x2-x1) ),
		           y2 - round( r2/abstand*(y2-y1) ),
	                   x2 - round( r2/abstand*(x2-x1) )  )
                end
	        end
     else if (Verbindung = Poly)
	  then if zielpar
	       then polygon( y2, x2, y1, x1, r2, r1, punkte )
	       else polygon( y1, x1, y2, x2, r1, r2, punkte )
	  else if zielpar
	       then spl( y2, x2, r2, y1, x1, r1, punkte )
	       else spl( y1, x1, r1, y2, x2, r2, punkte )
  end {zeichne}
else if (sf^.semfkt = IDNT)
     then begin
          gibfreiSF( aktPNr, sf ); wrtERR1('Identitaet geloescht')
	  end
     else if versorgt
          then begin
               wrtERR3('Parameterversorgung geloescht!  AttrNr:',apar^.attr);
               apar^.vok:= nil;
               apar^.attr:= 0;
               apar^.verb:= nil;
               end;
if color<>-2 then gpr_$set_draw_value(color_base,status);
if color<>-2 then gpr_$set_text_value(color_base,status);
end;   {zeichneParVersorgung}                           



procedure zeichneSemFkt (* sf: SemFktListe *);
var laenge,z,xkoord,ykoord,i,angleich,abstand,dst: integer;
    apar:     ParListe;
    issyn,gedr: boolean; 
      color:gpr_$pixel_value_t;

begin                          
gpr_$inq_draw_value(color,status);
if (sf^.semfkt = IDNT)
then zeichneParVersorgung( sf, sf^.zielpar, true )
else begin
     issyn:=SFTab[sf^.semfkt].issynfkt;
     gedr:= sf^.gedreht;
     with rbs,sf^ do
       begin
       if issyn
        then begin
              apar:=quellpar;
              i:=0;
              while apar<>nil do
                begin
                 i:=i+1;
                 apar:=apar^.nxt
                end; 
              if i > ord(SFTab[semfkt].name[0])
               then begin
                    laenge:=dist(i);
                    angleich:=dist(i-ord(SFTab[semfkt].name[0]))
                    end
               else begin
                     angleich:=0;
                     laenge:= dist (ord( SFTab[semfkt].name[0] ) );
                    end; 
              if i<>0 
               then begin
                     while (laenge mod dist(i)) <> 0 do
                      begin
                       laenge:=laenge+1;
                       angleich:=angleich+1
                      end;
                    end;
             end
         else laenge:=dist(ord(SFTab[semfkt].name[0])); 
       if issyn
        then begin  
               if color<>-2 
                then begin
                      gpr_$set_draw_value(color_sy,status);
                      gpr_$set_text_value(color_sy,status)
                     end;
             end
        else begin 
               if color<>-2
                then begin
                      gpr_$set_draw_value(color_sem,status);
                      gpr_$set_text_value(color_sem,status);
                     end;
             end;
       linie( Y+R1, X, Y+R1, X+laenge );
       linie( Y-R1, X+laenge, Y-R1, X);
       if issyn
        then begin 
              linie( Y+R1, X+laenge, Y, X+laenge+R1 );
              linie( Y-R1, X+laenge, Y, X+laenge+R1 ); 
              linie( Y+R1, X, Y, X-R1 );
              linie( Y-R1, X, Y, X-R1 ); 
              if gedr
               then begin
                      ykoord:=Y-R1;
                      dst:=-1;
                    end
               else begin
                      ykoord:=Y+R1;
                      dst:=1;
                    end;
              linie( ykoord, X+laenge div 2, ykoord+10*dst, X+laenge div 2);
              if i<>0 
               then begin
                     if gedr then ykoord:=Y+R1 else ykoord:=Y-R1;
                     abstand:=laenge div dist(i);
                     abstand:=dist(abstand); 
                     linie(ykoord, X+(abstand div 2), ykoord-10*dst, X+(abstand div 2));
                     xkoord:=X+(abstand div 2)+abstand;
                     for z:=2 to i do
                       begin
                        linie( ykoord, xkoord, ykoord-10*dst,xkoord);
                        xkoord:=xkoord+abstand
                       end;
                    end;                             
              
             end
        else begin 
              halbkreis( Y, X+laenge, R1, true );
              halbkreis( Y, X, R1, false );
              angleich:=0
             end;
       setCursor( Y-deltaY, X+angleich div 2 );
       wrtIdent( SFTab[semfkt].name );
       end; {with}
     for i:= 0 to 1 do
       begin
       if (i = 0)
       then begin 
             apar:= sf^.quellpar;
            end
       else begin
             apar:= sf^.zielpar;
            end;
       while (apar <> nil) do
         begin
          if issyn
           then begin
                 zeichneParVersSynfkt(sf,apar,(i<>0));
                end
           else zeichneParVersorgung( sf, apar, (i<>0) );
         apar:= apar^.nxt
         end;
       end {for}
     end; {else}  
 if color<>-2 then gpr_$set_draw_value(color_base,status);
 if color<>-2 then gpr_$set_text_value(color_base,status);
end; {zeichneSemFkt}

procedure zeichneProduktion;
var vok:    VokListe;
    sf:     SemFktListe;
    ha:     HAListe;
    symbol: ASymbTyp;
begin
clearscreen;
setCursor( rbs.uRandvBild+rbs.vBildHoehe+1, 0 );
gpr_$text(' Produktion:  ',14,status); wrtIdent( PTab[ aktPNr ].name );
vok:= PTab[ aktPNr ].vater;
if (vok <> nil) then zeichneVokabel( vok );
vok:= PTab[ aktPNr ].soehne;
while (vok <> nil) do
  begin zeichneVokabel( vok ); vok:= vok^.nxt end;
ha:= PTab[ aktPNr ].hilfsAttr;
while (ha <> nil) do
  begin
  symbol:= ATab[ ha^.attr ].symbol ;
  writeikon( ha^.Y, ha^.X, symbol );
  ha:= ha^.nxt
  end;
sf:= PTab[ aktPNr ].semRegeln;
while (sf<> nil) do
  begin zeichneSemFkt( sf ); sf:= sf^.nxt end;
end;   {zeichneProduktion}

