





function testeversion (* eingabedatei: filename): boolean; *);
var idlaenge0, maxanzT0, maxanzNT0, maxanzP0, maxanzSF0, maxanzA0, maxanzTyp0, maxanzASymb0, ID0: integer;
    GIN: text;
      c: char;
begin
open(GIN,eingabedatei);
reset (GIN);
read(GIN,c);
if c = 'I' then begin
                readln(GIN);
                get(GIN)
               end;
get(GIN); get(GIN);
readln(GIN, idlaenge0, maxanzT0, maxanzNT0, maxanzP0, maxanzSF0, ID0, maxanzA0, maxanzTyp0, maxanzASymb0);
testeversion:=	(idlaenge0	= idlaenge)	and
		(maxanzT0	= maxanzT)	and
		(maxanzNT0	= maxanzNT)	and
		(maxanzP0	= maxanzP)	and
		(maxanzSF0	= maxanzSF)	and
		(ID0		= IDNT)		and
		(maxanzA0	= maxanzA)	and
		(maxanzTyp0	= maxanzTyp)	and
		(maxanzASymb0	= maxanzASymb);
close(GIN);
end;

function wievielfrei (* hl: HashListen): integer; *);
var  hllaenge, res, ptr: integer;
begin res:=0;
case hl of
  prodHL: begin hllaenge:=maxanzP end;
  nontHL: begin hllaenge:=maxanzNT end;
  termHL: begin hllaenge:=maxanzT end;
  attrHL: begin hllaenge:=maxanzA end;
  typeHL: begin hllaenge:=maxanzTyp end;
  sfktHL: begin hllaenge:=maxanzSF end;
  end (*case*);
for ptr:=1 to hllaenge do
  begin 
  case hl of
    prodHL: begin 
	    if PTab[ptr].name[0]=chr(0) then res:=succ(res);
	    end;
    nontHL: begin 
	    if NTTab[ptr].name[0]=chr(0) then res:=succ(res);
            end;
    termHL: begin 
	    if TTab[ptr].name[0]=chr(0) then res:=succ(res);
	    end;
    attrHL: begin 
	    if ATab[ptr].name[0]=chr(0) then res:=succ(res);
	    end;
    typeHL: begin 
	    if TypTab[ptr].name[0]=chr(0) then res:=succ(res);
	    end;
    sfktHL: begin 
	    if SFTab[ptr].name[0]=chr(0) then res:=succ(res);
	    end;
    end (*case*);
  end (*for*);
wievielfrei:=res;
end (*wievielfrei*);


procedure testeueberlauf;
var frei: integer;
    hl: HashListen;
begin
for hl:=prodHL to typeHL do
  begin
  frei:=wievielfrei(hl);
  if frei<vorwarn then meldeueberlauf(hl,frei);
  end;
end;


procedure wrtfilename(* fn: filename *);
var i: integer;

  function aktlgfn: integer;
  var i: integer;
  begin i:=lgfilename;
  while (i>1) and (fn[i]=' ') do i:=pred(i);
  if i=1 then if fn[i]=' ' then i:=0;
  aktlgfn:=i;
  end (*aktlgfn*);

begin
for i:=1 to aktlgfn do write(ERRFILE,fn[i]);
end (*wrtfilename*);

procedure wrtERR1(* fn: filename *);
begin
wrtfilename(fn); writeln(ERRFILE); close (ERRFILE)
end;

procedure wrtERR2(* fn, fn2: filename *);
begin
wrtfilename(fn); wrtfilename(fn2); writeln(ERRFILE); close (ERRFILE);
end;

procedure wrtERR3(* fn: filename; en: integer *);
begin
wrtfilename(fn); writeln(ERRFILE,en); close (ERRFILE);
end;

procedure gibCDateiname(* var AGDateiname: filename; var CDateiname: filename *);
var i: integer;
begin
CDateiname:=AGDateiname;
i:=1;
while CDateiname[i]<>' ' do i:=succ(i);
CDateiname[i]:=chr(0);
end;


procedure gibSymbolDateiname(* var AGDateiname: filename; var SDateiname: filename *);
var Symbolextension: string;
    i,j: integer;
begin
Symbolextension:='.symbole';
SDateiname:=AGDateiname;
i:=1;
while SDateiname[i]<>' ' do i:=succ(i);
for j:=0 to 7 do SDateiname[i+j]:=Symbolextension[j];
end;


function isFileDir (* var CDateiname: filename): boolean *);
var testexpr: langstring;
    i,j: integer;
begin
testexpr:='test -d ';
i:=9;
j:=1;
while CDateiname[j]<>chr(0) do
  begin
  testexpr[i]:=CDateiname[j];
  i:=succ(i); j:=succ(j);
  end;
testexpr[i]:=chr(0);
isFileDir:= rufeBS(testexpr)=0;
end;


function schreibenerlaubt (* var CDateiname: filename): boolean *);
var res: boolean;
begin
if wrtFILE(CDateiname)=0 then res:=true
else res:=(attemptwrt(CDateiname)=0);
schreibenerlaubt:=res;
end;


function lesenerlaubt (* var CDateiname: filename): boolean *);
begin
lesenerlaubt:=(rdFILE(CDateiname)=0);
end;


procedure val (*n: integer; var s: Ident*);
var hs: Ident;
    lg,r,i: integer;
begin
lg:=0;
while (n>9) do
  begin
  lg:=succ(lg);
  r:=n mod 10;
  n:=n div 10;
  hs[lg]:=chr(ord('0')+r);
  end;
lg:=succ(lg);
hs[lg]:=chr(ord('0')+n);
for i:=lg downto 1 do s[succ(lg-i)]:=hs[i];
s[0]:=chr(lg);
end;



procedure sucheVl(*pr: integer; vptr: VokListe; var pos: integer *);
var s: VokListe;
    snr: integer;
begin
pos:=-1;
with PTab[pr] do
  begin
  if vater<>nil then if vater=vptr then pos:=0;
  s:=soehne; snr:=0;
  while (s<>nil) and (pos<0) do
    begin
    snr:=succ(snr);
    if s=vptr then pos:=snr else s:=s^.nxt;
    end;
  end;
end (*sucheVl*);


procedure sucheVg (*vptr: VokListe; var pr: integer; var pos: integer*);
var fertig: boolean;
    anw: PListe;
begin
if vptr^.typ=nont then anw:=NTTab[vptr^.nt].anwendungen else anw:=TTab[vptr^.t].anwendungen;
fertig:=false;
while (anw<>nil) and (not fertig) do
  begin
  pr:=anw^.prod;
  anw:=anw^.nxt;
  sucheVl(pr,vptr,pos);
  fertig:=pos>=0;
  end;
if not fertig then wrtERR1('sucheVg');
end (*sucheVg*);


function gibazh(* za: Zeilenart): integer *);
begin
with rbs, ASymb do case za of
  nurText: gibazh:=zhoehe;
  nurIcons: gibazh:=hoehe;
  IconsMitText: if zhoehe>hoehe then gibazh:=zhoehe else gibazh:=hoehe;
  IconsUeberText: gibazh:=zhoehe+hoehe+5;
  end (*case*);
end (*gibazh*);

function Twirdverwendet (* t: integer): boolean *);
var vork: PListe;
    gefunden: boolean;
    sr: SemFktListe;
    pl: ParListe;
begin
gefunden:=false;
vork:=TTab[t].anwendungen;
while (vork<>nil) and (not gefunden) do
  begin
  with PTab[vork^.prod] do
    begin
    sr:=semRegeln;
    while (sr<>nil) and (not gefunden) do
      begin
      pl:=sr^.quellpar;
      while (pl<>nil) and (not gefunden) do
	begin
	with pl^ do
	  begin
	  if attr=0 then if vok<>nil then if vok^.typ=term then gefunden:=vok^.t=t;
	  end;
	pl:=pl^.nxt;
	end (* while pl*);
      sr:=sr^.nxt;
      end (*while sr*);
    end (*with PTab*);
  vork:=vork^.nxt;
  end (*while vork*);
Twirdverwendet:=gefunden;
end (*Twirdverwendet*);


function hashtablaenge (* hl: HashListen): integer *);
begin
case hl of
  prodHL: hashtablaenge:=maxanzP; 
  termHL: hashtablaenge:=maxanzT; 
  attrHL: hashtablaenge:=maxanzA;
  nontHL: hashtablaenge:=maxanzNT; 
  sfktHL: hashtablaenge:=maxanzSF; 
  typeHL: hashtablaenge:=maxanzTyp; 
  noList: hashtablaenge:=0;
  end (*case*);
end; (*hashtablaenge*)

procedure move_read(* var c: char *);
var OK:boolean;
    xpos,ypos:integer;
begin
xpos := 100;	(* Cursorposition vordefinieren *)
ypos := 100;
SetCursor(rbs.ypixels-ypos,xpos);
keys := [];
gpr_$enable_input(gpr_$locator, keys, status);	(* Mausbewegung abfragen *)
keys := [chr(0)..chr(127),kbd_$cr,kbd_$up_arrow,kbd_$left_arrow,kbd_$right_arrow,kbd_$down_arrow,kbd_$next_win];
gpr_$enable_input(gpr_$keystroke, keys, status);
keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
gpr_$enable_input(gpr_$buttons, keys, status); 
repeat
  begin
  unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
  if ev_type = gpr_$locator
    then begin
	 OK := FALSE;
         if ev_pos.x_coord > xpos + Xsensivity
           then begin OK := TRUE; c := '6' end; 
         if ev_pos.x_coord < xpos - Xsensivity
           then begin OK := TRUE; c := '4' end;
         if ev_pos.y_coord > ypos + Ysensivity
           then begin OK := TRUE; c := '2' end;
         if ev_pos.y_coord < ypos - Ysensivity
           then begin OK := TRUE; c := '8' end;
	 end
     else OK := TRUE;
  end;
until OK;
case c of
 kbd_$cr: c:=trz;
 kbd_$up_arrow: c:='8';
 kbd_$down_arrow: c:= '2';
 kbd_$left_arrow: c:='4';
 kbd_$right_arrow: c:= '6';
 kbd_$next_win: c:= '5'; 
 kbd_$pop:  c:=chr(0);
end;             
if ev_type=gpr_$buttons
 then begin
       case c of
        kbd_$m1d: c:='0';
	kbd_$m2d: c:=trz;
	kbd_$m3d: c:=PraefixTab[1];
       end;
      end;
gpr_$disable_input(gpr_$locator, status);
end (*move_read*);


procedure cread(* var c: char *);
begin
keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
gpr_$enable_input(gpr_$buttons, keys, status); 
keys := [chr(0)..chr(127),kbd_$cr,kbd_$bs,kbd_$next_win,kbd_$char_del]; {Create a key set.}
gpr_$enable_input(gpr_$keystroke, keys, status);
unobscured := gpr_$event_wait(ev_type, c, ev_pos, status); 
if ev_type=gpr_$buttons
 then case c of
        kbd_$m1d: c:='0';
	kbd_$m2d: c:=PromptChar;
        kbd_$m3d: c:=PraefixTab[1];
      end
 else case c of
        kbd_$cr: c:=PromptChar;
        kbd_$bs: c:=chr(127);
        kbd_$next_win: c:= '5'; 
        kbd_$char_del: c:= chr(8); 
        kbd_$pop:  c:=chr(0);
      end;             
end (*cread*);

procedure pread(* var c: char *);
begin
cread(c);
if (c=PromptChar)
 then c:=trz
 else if c=trz
       then begin
             c:=chr(7);
             beep
            end;
end (*pread*);

procedure antworte(* qt:fragetyp; var antw:char *);
 type text21 = packed array[1..21] of char;
 var alternative: array [0..2] of text21;                           
     zeichen: array [0..2] of char;
     c:char;
     wahl,i,xpos,ypos,dx,len: integer;
     danz: 0..2;

    function low2upp(c:char) : char;
     begin
     if (c >= 'a') and (c <= 'z')
       then low2upp := chr( ord(c) - ord('a') + ord('A') )
       else low2upp := c;
     end;

 begin (* antworte *)
 ypos := MFenster.LOecke_y - (1+Meldungen)*rbs.zhoehe - 5;
 xpos := MFenster.LOecke_x + 20;
 Meldungen := Meldungen + 1;
 case qt of
 janein: begin
	 alternative[0] := '      Ja      ';
	 zeichen[0] := 'J';
	 alternative[1] := '     Nein     ';
	 zeichen[1] := 'N';
	 alternative[2] := '   Abbruch    ';
	 zeichen[2] := 'A';
	 danz := 2;
	 end;
 semide: begin
	 alternative[0] := '  Identitaet  ';
	 zeichen[0] := 'I';
	 alternative[1] := '   Funktion   ';
	 zeichen[1] := 'S';
	 alternative[2] := '    Abbruch   ';
	 zeichen[2] := 'A';
	 danz := 2;
	 end;
 semsyn: begin
	 alternative[0] := '     semantisch      ';
	 zeichen[0] := 'S';
	 alternative[1] := '     syntaktisch     ';
	 zeichen[1] := 'Y';
	 danz := 1;
	 end;
 obenunten: 
	 begin
         alternative[0] := '         oben        ';
	 zeichen[0] := 'O';
	 alternative[1] := '        unten        ';
	 zeichen[1] := 'U';
	 danz := 1;
	 end;
 inhder: begin
	 alternative[0] := '  inherited   ';
	 zeichen[0] := 'I';
	 alternative[1] := '   derived    ';
	 zeichen[1] := 'D';
	 alternative[2] := '   Abbruch    ';
	 zeichen[2] := '0';
	 danz := 2;
	 end;
 auinde: begin
	 alternative[0] := '  inherited   ';
	 zeichen[0] := 'I';
 	 alternative[1] := '  auxiliary   ';
	 zeichen[1] := 'A';
	 alternative[2] := '   derived    ';
  	 zeichen[2] := 'D';
	 danz := 2;
	 end;
 end; (* case *)
 len := (4-danz)*7;
 dx := rbs.zbreite*len + 4;
 for i:=0 to danz do
 begin
  setCursor(ypos,xpos+i*(dx+15));
  gpr_$text(alternative[i],len,status);
  box(ypos-6,xpos+i*(dx+15)-2,ypos+rbs.zhoehe-2,xpos+dx+i*(dx+15));
 end;
 wahl := 0;
 repeat
  begin
  invertBild(xpos+wahl*(dx+15)-1,ypos-6,dx+1,rbs.zhoehe+3);
  move_read(c);
  invertBild(xpos+wahl*(dx+15)-1,ypos-6,dx+1,rbs.zhoehe+3);
  case c of
   trz: antw := zeichen[wahl];
   '4': if wahl > 0 then wahl := pred(wahl);
   '6': if wahl < danz then wahl := succ(wahl);
   otherwise for i := 0 to danz do
                if low2upp(c) = zeichen[i] then begin
						antw := zeichen[i];
						c := trz;
						end;
  end; (* case *)
 end; (* repeat *)
 until (c = trz); 
 end; (* antworte *)

procedure newline;
 var x,y:integer;
 begin
  CursorPos(y,x);
  SetCursor(y-rbs.zhoehe,0);
 end;
  
procedure writestring(* s:string *);
 var i:integer;
begin
 i:=0;
 while s[i]<>' ' do i:=i+1;
 gpr_$text(s,i,status)
end;

procedure writelnstring(* s:string *);
 begin
  writestring(s);
  newline;
 end;
                 
procedure cursoron;
 var x,y,i:integer;
     
 begin 
  cursorpos(y,x);
  old_cursor_x:=x;
  y:=rbs.ypixels-y;
  old_cursor_y:=y;
  {for i:=0 to hi_plane_id do} gpr_$set_raster_op(0,6,status);
  for i:=-1 to 13
   do begin
       gpr_$move(x-1,y-i,status);
       gpr_$line(x+7,y-i,status);
      end;
  {male4eck(false,y+12,y,x-1,x+7);}
  {for i:=0 to hi_plane_id do} gpr_$set_raster_op(0,3,status);
  setCursor(rbs.ypixels-y,x)  
 end;

procedure cursoroff;
 var i:integer;
 begin
  {for i:=0 to hi_plane_id do} gpr_$set_raster_op(0,6,status);
  for i:=-1 to 13
   do begin
       gpr_$move(old_cursor_x-1,old_cursor_y-i,status);
       gpr_$line(old_cursor_x+7,old_cursor_y-i,status);
      end;
  {male4eck(true,old_cursor_y+12,old_cursor_y,old_cursor_x,old_cursor_x+6);}                
  {for i:=0 to hi_plane_id do} gpr_$set_raster_op(0,3,status);
  setcursor(rbs.ypixels-old_cursor_y,old_cursor_x)
 end;

procedure beep;
 var time:time_$clock_t; 
 begin
  time.high16:= 0;
  time.low32:= 25000;
  tone_$time(time); 
 end;
   
procedure clearscreen;
 var rectangle:gpr_$window_t;
 begin
  rectangle.window_base.x_coord:=0;
  rectangle.window_base.y_coord:=0;
  rectangle.window_size.x_size:=rbs.xpixels+1;
  rectangle.window_size.y_size:=rbs.ypixels+1;
  gpr_$set_fill_value(-2,status);
  gpr_$rectangle(rectangle,status);
  gpr_$set_fill_value(color_base,status);
 end;

procedure wrtIdent(* var s: Ident *);
var i: integer; 
    txt:gpr_$string_t;
begin
for i:=1 to ord(s[0]) do txt[i]:=s[i];
gpr_$text(txt,ord(s[0]),status)
end;   {wrtIdent}
                            
procedure writeint(* n: integer *);
 var i,j,coun:integer; 
             c:char;
             s:string;
 begin
  j:=n;
  if n<0 then n:= -n;
  coun:= 0;
  i:=1;
  repeat
   s[i]:= chr(n mod 10 + ord('0'));
   i:=i+1;
   coun:=coun + 1;
   n:=n div 10;
  until n <= 0;
   if (j < 0)
    then begin
          s[i]:='-';
          coun:=coun +1; 
          i:=i+1;
         end;
   s[i]:=' ';
   i:=1; 
   j:=coun;
   while i < coun
    do begin
         c:= s[i];
         s[i]:= s[coun];
         s[coun]:= c;
         i:=i+i;
         coun:=coun-1; 
        end;
   gpr_$text(s,j,status)
 end;


function dist(* i: integer ): integer *);
begin
dist:= i*rbs.zbreite;
end;   {dist}

procedure tekadr(* y,x: integer; var hy,ly,hx,lx: char *);
begin
hy:=chr((y div 32) + 32);
ly:=chr((y mod 32) + 96);
hx:=chr((x div 32) + 32);
lx:=chr((x mod 32) + 64);         
end;   {tekadr}

procedure setCursor(* z,s: integer *);
var position:gpr_$position_t;
begin                       
 position.x_coord:=s;
 position.y_coord:=rbs.ypixels-z;
 gpr_$set_cursor_position(position,status);
 gpr_$move(s,rbs.ypixels-z,status)
end;   {setCursor}

procedure CursorPos (* var y,x: integer *);
var cursor_pat: gpr_$bitmap_desc_t;
    cursor_raster_op: gpr_$raster_op_array_t;
    active:boolean;
    position,origin: gpr_$position_t;
begin
 gpr_$inq_cursor(cursor_pat,cursor_raster_op,active,position,origin,status);
 x:=position.x_coord;
 y:=rbs.ypixels-position.y_coord;
end;   {CursorPos}

procedure male4eck(* loesch: boolean; ya,ye,xa,xe: integer *);
var rectangle: gpr_$window_t;
    x,y:integer;
begin 
ya:=rbs.ypixels-ya;
ye:=rbs.ypixels-ye;
if ye<ya then begin y:=ye; ye:=ya; ya:=y end; 
if xe<xa then begin x:=xe; xe:=xa; xa:=x end; 

 rectangle.window_base.x_coord:=xa;
 rectangle.window_base.y_coord:=ya;
 rectangle.window_size.x_size:= xe-xa+1;
 rectangle.window_size.y_size:= ye-ya+1;
 if loesch
  then gpr_$set_fill_value(-2,status);
 gpr_$rectangle(rectangle,status);
 if loesch
  then gpr_$set_fill_value(color_base,status);

end; (*male4eck*)


procedure loesche4eck(* yu,yo,xl,xr: integer *);
begin
male4eck(true,yu,yo,xl,xr);
end;


procedure backspace (* y,x,laenge: integer *); 
   var i:integer;
begin
{if (laenge >= 0)
then begin    
     male4eck( true, y-1, y+12, x+dist(laenge), x+dist(laenge)+9 );
     setCursor( y, x+dist(laenge) )
     end  }
 setCursor(y,x+dist(laenge));
 gpr_$text(' ',1,status);
 setCursor(y,x+dist(laenge));
end;   {backspace}


procedure gibPromptChar;
 var txt: gpr_$string_t;
begin
 
if PromptChar=chr(13)
 then gpr_$text(' <RETURN> ',10,status)
 else begin
       txt[1]:=blk;
       txt[2]:=PromptChar;
       txt[3]:=blk;
       gpr_$text(txt,3,status)
      end;
end;


procedure clearmeldung;
begin
 if (Meldungen > 0) then
   gpr_$write_pixels(popupspeicher, MeldFenst, status);
 Meldungen := 0
end;

procedure openMeldefenster;
begin
  gpr_$read_pixels(MeldFenst,popupspeicher,status);
  with MFenster do
  begin
   male4eck(false, RUecke_y-10,LOecke_y-10,LOecke_x+10,RUecke_x+10);
   male4eck( true, RUecke_y, LOecke_y, LOecke_x, RUecke_x );
   box(LOecke_y, LOecke_x, RUecke_y, RUecke_x);
   box(LOecke_y - 3, LOecke_x + 3, RUecke_y + 3, RUecke_x - 3);
  end;
end;   {openMeldefenster}


procedure quitmeldung;
var c: char;
begin
if (Meldungen > 0)
then begin
     with MFenster do
       setCursor( LOecke_y - (1+Meldungen)*rbs.zhoehe-2, LOecke_x + 7);
     gpr_$text('    Mit beliebiger Taste gehts weiter !',40,status); {##'}
     Meldungen:= Meldungen+1;
     cread(c);
     clearmeldung
     end
end;   {quitmeldung}


procedure Seite0; 
  var window:gpr_$window_t;
     origin:gpr_$position_t;
begin
if aktseite<>0 then begin
aktSeite:= 0;
clearmeldung;
clearscreen;
window.window_base.x_coord:=0;
window.window_base.y_coord:=0;
window.window_size.x_size:=rbs.xpixels+1;
window.window_size.y_size:=rbs.ypixels+1;
origin.x_coord:=0;
origin.y_coord:=0;
gpr_$pixel_blt(seite1_desc,window,origin,status);
if status.all <> status_$ok then error_$print(status);
gpr_$set_bitmap(seite1_desc,status);
if status.all <> status_$ok then error_$print(status);
clearscreen;
gpr_$set_bitmap(seite0_desc,status);  
if status.all <> status_$ok then error_$print(status);
end;
end;   {Seite0}


procedure Seite1; 
 var window:gpr_$window_t;
     origin:gpr_$position_t;
begin  
if aktseite<>1
 then begin
aktSeite:= 1; 
clearmeldung;
window.window_base.x_coord:=0;
window.window_base.y_coord:=0;
window.window_size.x_size:=rbs.xpixels+1;
window.window_size.y_size:=rbs.ypixels+1;
origin.x_coord:=0;
origin.y_coord:=0;
gpr_$set_bitmap(seite1_desc,status);
if status.all <> status_$ok then error_$print(status);
gpr_$pixel_blt(seite0_desc,window,origin,status);
if status.all <> status_$ok then error_$print(status);
gpr_$set_bitmap(seite0_desc,status); 
if status.all <> status_$ok then error_$print(status);
clearscreen;
 end;
end;   {Seite1}
                                    

procedure screen2disk(* f:string *);
 var window:gpr_$window_t;
     origin:gpr_$position_t;  
     size:gpr_$offset_t;
     group_header:gpr_$bmf_group_header_array_t;
     attributes:gpr_$attribute_desc_t;
     desc,current_desc:gpr_$bitmap_desc_t;
     created:boolean; 
     version:gpr_$version_t;
     i,groups:integer;  


begin
 window.window_base.x_coord:=0;
 window.window_base.y_coord:=0;
 window.window_size.x_size:=rbs.xpixels;
 window.window_size.y_size:=rbs.ypixels;
 origin.x_coord:=0;
 origin.y_coord:=0; 
 group_header[0].n_sects:=1;
 group_header[0].pixel_size:=1;
 group_header[0].allocated_size:=1;
 group_header[0].bytes_per_line:=0;
 group_header[0].bytes_per_sect:=0; 
 attributes:=gpr_$attribute_block(seite0_desc,status);
 if status.all <> status_$ok then error_$print(status);
 size.x_size:=rbs.xpixels+1;
 size.y_size:=rbs.ypixels+1; 
 i:=1;  
 groups:=1;
 while f[i] <> ' ' do i:=i+1;
 gpr_$open_bitmap_file(gpr_$update,f,i-1,version,size,groups,group_header,attributes,desc,created,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$inq_bitmap(current_desc,status);
 if status.all <> status_$ok then error_$print(status); 
 gpr_$set_bitmap(desc,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$pixel_blt(current_desc,window,origin,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$set_bitmap(current_desc,status);
 if status.all <> status_$ok then error_$print(status);
end;

function formpraefixop(* c: char): integer *);
begin
if c=PraefixTab[1] then formpraefixop:=1
else if c=PraefixTab[2] then formpraefixop:=2
else if c=PraefixTab[3] then formpraefixop:=3
else formpraefixop:=0;
end;

procedure dekodhl(* hl: HashListen; var s: Ident *);
begin
  case hl of
  noList: s[0]:=chr(0);
  prodHL: begin s:=' Produktion'; s[0]:=chr(10) end;
  termHL: begin s:=' Terminal'; s[0]:=chr(8) end;
  nontHL: begin s:=' Nonterminal'; s[0]:=chr(11) end;
  attrHL: begin s:=' Attribut'; s[0]:=chr(8) end;
  sfktHL: begin s:=' Funktion'; s[0]:=chr(12) end;
  typeHL: begin s:=' Typname'; s[0]:=chr(7) end;
  end (* case *)
end (* dekodhl *);


procedure zuw(* var s1: Ident; var s2: Ident *);
var i: integer;
begin
i:=1;
while (i<idlaenge) and (s1[i]<>blk) do i:=succ(i);
if s1[i]<>blk then s2[0]:=chr(idlaenge) else s2[0]:=chr(pred(i));
for i:=1 to ord(s2[0]) do s2[i]:=s1[i];
end; (*zuw*)


procedure rel(* s1: Ident; var op: lexrel; s2: Ident *);
type entscheidg = (unklar,kleiner,groesser);
var i,m,w: integer;
    entscheid: entscheidg;
begin
if ord(s1[0])=ord(s2[0])        
then begin w:=0; m:=ord(s1[0]) end
else if ord(s1[0])>ord(s2[0]) 
then begin w:=1; m:=ord(s2[0]) end
else begin w:=2; m:=ord(s1[0]) end;
i:=1; entscheid:=unklar;
while (i<=m) and (entscheid=unklar) do
  if s1[i]<s2[i] then entscheid:=kleiner
  else if s1[i]>s2[i] then entscheid:=groesser
  else i:=succ(i);
if entscheid = kleiner then op:=lexkleiner
else if entscheid=groesser then op:=lexgroesser
else if w=0 then op:=lexgleich
else if w=1 then op:=lexgroesser
else op:=lexkleiner
end (*rel*);


function yvonzeile(* n,azhoehe: integer): integer *);
begin
yvonzeile:=rbs.yhome-n*azhoehe;
end;


function isIdent(* var s: Ident): boolean *);
begin
if ord(s[0]) = 0
then isIdent:=false
else if (s[1] in ['a'..'z','A'..'Z']) or (formpraefixop(s[1])>0) then isIdent:=true
else isIdent:=false
end;


procedure loeschewort(* y,x,lg: integer *);
 var i:integer;
begin
if lg>0
then male4eck( true, y-2, y+16, x, x+pred(dist(lg)));
setCursor(y,x);
end;


procedure aePraefixTab;
const zwr = 10;
      hzwr= 5;  (* 2*hzwr = zwr ! *)
      lRand=7;
var stz0,stz: intset;
    i,j: integer;
    c: char;
    y1,y2,y3,y4,y10,v20,v2,v4,v5,v50,v6,v7,v8,v80,v9,v90,xst: integer;
    hx,hy: integer;
    y: array[5..9] of integer;
    u: array[0..4] of integer;
    sw: boolean; 
    txt: gpr_$string_t;

  procedure bsmask;
  var i: integer;
    
    procedure setcursor1(y,x: integer);
    begin
    setCursor(y,(lRand+x)*rbs.zbreite);
    end;

  begin (*bsmask*)
  with rbs do
    begin
    clearscreen;
    linie(v20,u[0],v20,u[4]);
    linie(v2,u[0],v2,u[3]);
    linie(v4,u[0],v4,u[4]);
    linie(v50,u[0],v50,u[4]);
    linie(v5,u[0],v5,u[4]);
    linie(v6,u[0],v6,u[4]);
    linie(v7,u[0],v7,u[4]);
    for i:=1 to 3 do linie(v7,u[i],v50,u[i]);
    linie(v7,u[0],v20,u[0]);
    linie(v4,u[1],v2,u[1]);
    linie(v4,u[2],v2,u[2]);
    linie(v4,u[3],v20,u[3]);
    linie(v7,u[4],v20,u[4]);
    linie(v80,u[0],v80,u[4]);
    linie(v8,u[0],v8,u[4]);
    linie(v90,u[0],v90,u[4]);
    linie(v9,u[0],v9,u[4]);
    linie(v8,u[0],v80,u[0]);
    linie(v8,u[3],v80,u[3]);
    linie(v8,u[4],v80,u[4]);
    linie(v9,u[0],v90,u[0]);
    linie(v9,u[3],v90,u[3]);
    linie(v9,u[4],v90,u[4]);
    setCursor(y1,0);
    gpr_$text(' Dienst: Aendere Steuerzeichen',30,status);
    male4eck(false,y1-4,y1-3,zbreite,dist(30));
    setcursor1(y2,3); gpr_$text('Art der Darst. der Identifikatortabellen',40,status);
    setcursor1(y3,22);gpr_$text('mit',3,status);
    setcursor1(y3,38);gpr_$text('mit',3,status);
    setcursor1(y4,2); gpr_$text('Bezeichnung',11,status);
    setcursor1(y4,17); gpr_$text('Attributnamen',13,status);
    setcursor1(y4,33); gpr_$text('Attributicons',13,status);
    setcursor1(y4,49); gpr_$text('Steuerzeichen',13,status);
    setcursor1(y[5],4);gpr_$text('"knapp"',7,status);
    setcursor1(y[5],22);gpr_$text('nein',4,status);
    setcursor1(y[5],38);gpr_$text('nein',4,status);
    setcursor1(y[6],4); gpr_$text('"mittel"',8,status);
    setcursor1(y[6],23);gpr_$text('ja',2,status);
    setcursor1(y[6],38);gpr_$text('nein',4,status);
    setcursor1(y[7],3); gpr_$text('"extensiv"',10,status);
    setcursor1(y[7],23);gpr_$text('ja',2,status);
    setcursor1(y[7],39); gpr_$text('ja',2,status);
    setcursor1(y[8],2); gpr_$text('Bezeichner fuer Identitaet der Funktionen',41,status);
    setcursor1(y[9],2); gpr_$text('"SELECT"',8,status);
    setCursor(y10,0);
    gpr_$text(' Moegliche Eingaben sind',24,status); 
    setCursor(y10-rbs.zhoehe,0);
    gpr_$text('    2 8 = Cursor vertikal',25,status);  
    setCursor(y10-2*rbs.zhoehe,0);
    gpr_$text('      0 = Zurueck',17,status);
    setCursor(y10-3*rbs.zhoehe,0);
    gpr_$text('      v = Voreinstellung uebernehmen',36,status);  
    setCursor(y10-4*rbs.zhoehe,0);
    gpr_$text(' und folgende Sonderzeichen fuer Belegung der Steuerzeichen:',60,status);
    hy:=y10-6*rbs.zhoehe; hx:=0;
    end (*with rbs*);
  end (*bsmask*);

begin (*aePraefixTab*)
sw:=aktSeite=0;
Seite1;
stz0:=[33..47,58..64,91..96,123..126];
with rbs do
  begin
  y1:=yhome-zhoehe;
  y2:=y1-3*zhoehe;
  y3:=y2-zhoehe-zwr;
  y4:=y3-zhoehe;
  y[5]:=y4-zhoehe-2*zwr;
  y[6]:=y[5]-zhoehe-zwr;
  y[7]:=y[6]-zhoehe-zwr;
  y[8]:=y[7]-2*zhoehe-zwr;
  y[9]:=y[8]-2*zhoehe-zwr;
  y10:=y[9]-3*zhoehe-zwr;

  v20:=y2+zhoehe+hzwr;
  v2:=y2-hzwr;
  v4:=y4-hzwr;
  v50:=y[5]+zhoehe+hzwr;
  v5:=y[5]-hzwr;
  v6:=y[6]-hzwr;
  v7:=y[7]-hzwr;
  v80:=y[8]+zhoehe+hzwr;
  v8:=y[8]-hzwr;
  v90:=y[9]+zhoehe+hzwr;
  v9:=y[9]-hzwr;

  u[0]:=(lRand*zbreite)-hzwr;
  for i:=1 to 4 do u[i]:=u[0]+i*16*zbreite;
  xst:=u[3]+zbreite;
  end;
bsmask;
j:=5; c:=blk;
repeat             
  
  if (c<>'2') and (c<>'8') then
  for i:=5 to 9 do
    begin
    loeschewort(y[i],xst,10);
    setCursor(y[i],xst+3*rbs.zbreite); 
    if i<=7 then begin
                  txt[1]:=PraefixTab[i-4];
                  gpr_$text(txt,1,status);
                 end
    else if i=8 then begin
                      txt[1]:=IDchar;
                      gpr_$text(txt,1,status)
                     end
    else 
      begin setCursor(y[i],xst+rbs.zbreite);
      gibPromptChar;
      end;
    end;
  stz:=stz0-[ord(PraefixTab[1])]-[ord(PraefixTab[2])]-[ord(PraefixTab[3])]-[ord(IDchar)]-[ord(PromptChar)];
  loeschewort(hy,0,79);
  for i:=33 to 126 do if i in stz
   then begin
    gpr_$text(blk,1,status);
    gpr_$text(chr(i),1,status);
   end;
  if j=9 then gpr_$text(' <RETURN>',9,status);
  invertBild(xst,y[j]-3,14*rbs.zbreite,rbs.zhoehe);
  move_read(c);     
  invertBild(xst,y[j]-3,14*rbs.zbreite,rbs.zhoehe);
  if ord(c) in stz then 
    begin if j<=7 then PraefixTab[j-4]:=c
	  else if j=8 then IDchar:=c
	  else PromptChar:=c;
    end
  else (* ord(c) not in stz *)
    begin
    if (j=9) and (c=chr(13)) then PromptChar:=c
    else if (c='2') then
      begin
      if j<9 then j:=succ(j) else j:=5;
      end
    else if (c='8') then
      begin
      if j>5 then j:=pred(j) else j:=9;
      end
    else if c='v' then
      begin
      PraefixTab[1]:='-'; PraefixTab[2]:='?'; PraefixTab[3]:='+';
      IDchar:='=';
      PromptChar:='.';
      end
    else if (c='0') or (c='4') or (c='6') then (*skip*)
    else beep;
    end;
until c='0';
if sw then Seite0;                    

end (*aePraefixTab*);

procedure catenate (* var v1, v2: vilinetyp *);
var i,ls: integer;
begin
ls:=mvibsbr;
while (ls>1) and (v1[ls]=blk) do ls:=pred(ls);
if ls=1 then if v1[ls]=blk then ls:=-1;
ls:=ls+2;
for i:=ls to mvibsbr do v1[i]:=v2[succ(i-ls)];
end (*catenate*);

procedure insert(* a: Ident; var b: vilinetyp; sp: integer *);
var i,mist : integer;
begin 
mist := ord(a[0]);
for i:=1 to ord(a[0]) do b[pred(i+sp)]:=a[i];
end; (*insert*)

procedure initevibsD(* yu,yo,deltay: integer *);
begin
with evibsD do
  begin
  if yu<yo then begin e7:=yo; e8:=yu end
	   else begin e7:=yu; e8:=yo end;
  e9:=deltay;
  e3:=(succ(e7-e8)) div deltay -3; (* -3 fuer ViBs-Menue! *)
  if e3<=0 then wrtERR1('initevibs');
  e1:=0;
  e0:=succ(e7)-deltay;
  e4:=1;
  qz:=1;
  end;
end (*initevibs*);


procedure neuaufteilg(* defd: boolean; zsternneu: integer; var md: MaskenDaten *);
var yu,yo: integer;
    dummyid: Ident;
begin
dummyid[0]:=chr(0);
with evibsD do
  begin
  if zsternneu>md.zstern then
    begin
    yu:=md.ystern-(zsternneu+8)*md.azh; 
    yo:=md.ystern-(md.zstern+6)*md.azh-3
    end
  else
    begin
    yu:=md.ystern-(md.zstern+8)*md.azh; 
    yo:=md.ystern-(zsternneu+6)*md.azh-3
    end;
  male4eck(true,yu,yo,0,rbs.xpixels);
  md.zstern:=zsternneu;
  md.yinput:=md.ystern-(zsternneu+7)*md.azh-3;
  NTmaske(defd,md,dummyid);
  prtreq:=true;
  initevibsD(3,md.ystern-(md.zstern+8)*md.azh-1,md.azh);
  end;
end (*neuaufteilg*);


procedure loescheeingabefeld(* var md: MaskenDaten *);
begin
with md do
  begin
  loesche4eck(yinput-3,pred(yinput+azh)-1,xinput,rbs.xpixels);
  setCursor(yinput,xinput);
  end
end;



procedure defmenue(* m: menuekenng; var zeilen, spalten: integer; var zuldienstnrn: intset *);
begin
case m of
  Prodbearbeiten:
    begin
    zeilen:=4; spalten:=3; zuldienstnrn:=[0..11]; 
    end;
  Attrberechnung:
    begin
    zeilen:=2; spalten:=3; zuldienstnrn:=[0..5];
    end;
  Gestalten:
    begin
    zeilen:=3; spalten:=3; zuldienstnrn:=[0..8];
    end;
  Attributeaendern:
    begin
    zeilen:=2; spalten:=3; zuldienstnrn:=[0..5];
    end;
  end (*case*);
end;


procedure loeschemenue(* m: menuekenng *);
const zabst=10;
var zeilen, spalten: integer;
    zuldienstnrn: intset;
begin
defmenue(m,zeilen,spalten,zuldienstnrn);
with rbs do
  begin
  male4eck(true,0,uRandvBild,0,xpixels)
  {else male4eck(true,uRandvBild-zabst-zeilen*(zhoehe+zabst),uRandvBild,0,xpixels);}
  end;
end (*loeschemenue*);


procedure wrtleeresmenue (* m: menuekenng *);
const zabst=10;
      rand=10;
var i,j,zeilen,spalten: integer;
    zuldienstnrn: intset;

  function y(i: integer): integer;
  begin
  with rbs do y:=uRandvBild-zabst-i*(zhoehe+zabst);
  end;

  function x(j: integer): integer;
  begin
  with rbs do x:=((xpixels-rand-rand) div spalten)*j+rand;
  end;

begin 
defmenue(m,zeilen,spalten,zuldienstnrn);
for i:=0 to zeilen do male4eck(false,y(i),y(i),x(0),x(spalten));
for j:=0 to spalten do male4eck(false,y(zeilen),y(0),x(j),x(j));
end;
 
(*
FUNCTION zero_fault_handler (IN f_status : pfm_$fault_rec_t ): pfm_$fh_func_val_t;
 var bildname:string;
     nummer:integer;
begin 
  bildname:='bild';
  bildnummer:=bildnummer+1;
  if bildnummer=1000 then bildnummer:=0;
  nummer:=bildnummer;
  bildname[5]:=chr(nummer div 100+48);  
  nummer:=nummer mod 100;
  bildname[6]:=chr(nummer div 10+48);
  nummer:=nummer mod 10;
  bildname[7]:=chr(nummer+48);
  screen2disk(bildname);
  zero_fault_handler:=pfm_$return_to_faulting_code;
 end; *)

procedure invertBild(* x1,y1,xs,ys:integer *);
var rectangle: gpr_$window_t;
    x,y:integer;
begin 
y1:=rbs.ypixels-y1;
rectangle.window_base.x_coord:=x1;
rectangle.window_base.y_coord:=y1-ys;
rectangle.window_size.x_size:= xs;
rectangle.window_size.y_size:= ys;
gpr_$raster_op_prim_set([gpr_$rop_fill],status);
gpr_$set_raster_op(0,6,status);
gpr_$rectangle(rectangle,status);
gpr_$raster_op_prim_set([gpr_$rop_fill,gpr_$rop_line,gpr_$rop_blt],status);
gpr_$set_raster_op(0,3,status);
end;

procedure waehledienst(* m: menuekenng; var dienstnr: integer *);
const zabst=10;
      rand=10;
var c: char;
    anzelem,zeilen,spalten,nummer,xx,yy,xsize,ysize: integer;
    zuldienstnrn: intset;       
    bildname:string;

  function y(i: integer): integer;
  begin
  with rbs do y:=uRandvBild-zabst-i*(zhoehe+zabst);
  end;

  function x(j: integer): integer;
  begin
  with rbs do x:=((xpixels-rand-rand) div spalten)*j+rand;
  end;

begin (* waehledienst *)
defmenue(m,zeilen,spalten,zuldienstnrn);
anzelem:=zeilen*spalten;
bildname:='bild';
if (dienstnr<0) or (dienstnr>=anzelem) then dienstnr:=0;
repeat
   xx := x(dienstnr mod spalten);
   yy := y(succ(dienstnr div spalten));
   xsize := x(1)-x(0)-1;
   ysize := y(1)-y(2)-1;
  invertBild( xx+1, yy, xsize, ysize);
  repeat move_read(c) until c in ['0','2','4','6','8',trz,'?',PraefixTab[1]];
  invertBild( xx+1, yy, xsize, ysize);
  clearmeldung;
  case c of
    '?','-': info; 
    '2': if (dienstnr+spalten) < anzelem then dienstnr := dienstnr+spalten;
    '4': if dienstnr mod spalten > 0 then dienstnr:=pred(dienstnr);
    '6': if dienstnr mod spalten < spalten-1 then dienstnr:=succ(dienstnr);
    '8': if dienstnr>=spalten then dienstnr:=dienstnr-spalten;
    trz: if not (dienstnr in zuldienstnrn) then beep;
    '0': begin
           if m=Attrberechnung then
             begin
             dienstnr:=5;
             c:=trz
             end;
           if m= Gestalten then
             begin
             dienstnr:=8;
             c:=trz
             end;
           if m=Attributeaendern then
             begin
             dienstnr:=5;
             c:=trz
             end;
         end;
     otherwise;
    end (*case*);
until (c=trz) and (dienstnr in zuldienstnrn);
end (*waehledienstPb*);


procedure wrtmenue(* m: menuekenng *);
const zabst=10;
      rand=10;
var zeilen, spalten: integer;
    zuldienstnrn: intset;

  function y(i: integer): integer;
  begin
  with rbs do y:=uRandvBild-zabst-i*(zhoehe+zabst);
  end;

  function x(j: integer): integer;
  begin
  with rbs do x:=((xpixels-rand-rand) div spalten)*j+rand;
  end;

  procedure setcursor1(i,j: integer);
  begin
  setCursor(y(j)+(zabst div 2), x(i)+(rbs.zbreite div 2)); 
  end;

begin 
gpr_$set_draw_value(color_base,status);
gpr_$set_text_value(color_base,status);
defmenue(m,zeilen,spalten,zuldienstnrn);
wrtleeresmenue (m);
case m of
  Prodbearbeiten:
    begin
    setcursor1(0,1); gpr_$text(' ATTRIBUTBERECHNUNG',19,status);
    setcursor1(0,2); gpr_$text(' ATTRIBUTIERUNG AENDERN',23,status);
    setcursor1(0,3); gpr_$text(' PRODUKTION ZEICHNEN',20,status);
    setcursor1(0,4); gpr_$text(' IDENTITAETEN ',14,status);
	    	     if not EXTENSIV then gpr_$text('AUSBLENDEN',10,status)
		     	  	     else gpr_$text('ANZEIGEN',8,status);
    setcursor1(1,1); gpr_$text(' GESTALTUNG',11,status);
    setcursor1(1,2); gpr_$text(' VOKABEL EINFUEGEN',18,status);
    setcursor1(1,3); gpr_$text(' VOKABEL LOESCHEN',17,status);
    setcursor1(1,4); gpr_$text(' VOKABEL ERSETZEN',17,status);
    setcursor1(2,1); gpr_$text(' PRODUKTION SPEICHERN',21,status);
    setcursor1(2,2); gpr_$text(' P. SPEICHERN & VERL.',21,status);
    setcursor1(2,3); gpr_$text(' P. UNVERAENDERT VERL.',22,status);
    setcursor1(2,4); gpr_$text(' PRODUKTIONSKONSISTENZ',22,status);
    end;
  Attrberechnung:
    begin
    setcursor1(0,1); gpr_$text(' ATTRIBUT BERECHNEN',19,status);
    setcursor1(1,1); gpr_$text(' IDENTIFIZIERE FUNKTION',23,status);
    setcursor1(2,1); gpr_$text(' PRODUKTION ZEICHNEN',20,status);
    setcursor1(0,2); gpr_$text(' PARAMETERVERSG. AENDERN',24,status);
    setcursor1(1,2); gpr_$text(' IDENTIFIZIERE ATTRIBUT',23,status);
    setcursor1(2,2); gpr_$text(' ZURUECK',8,status);
    end;
  Gestalten:
    begin
    setcursor1(0,1); gpr_$text(' FUNKTION VERSCHIEBEN',21,status);
    setcursor1(1,1); gpr_$text(' HILFSATTRIBUT VERSCHIEBEN',26,status);
    setcursor1(2,1); gpr_$text(' VOKABEL VERSCHIEBEN',20,status);
    setcursor1(0,2); gpr_$text(' LINIENFUEHRUNG AENDERN',23,status);
    setcursor1(1,2); gpr_$text(' LINIENART AENDERN: ',19,status);
    if Verbindung=Poly then gpr_$text('SPLINE',6,status) else gpr_$text('POLYGON',7,status);
    setcursor1(2,2); gpr_$text(' STANDARDPOSITIONIERUNG',23,status);
    setcursor1(0,3); gpr_$text(' PRODUKTION ZEICHNEN',20,status);
    setcursor1(1,3); gpr_$text(' IDENTITAETEN ',14,status);
	    	     if not EXTENSIV then gpr_$text('ANZEIGEN',8,status)
				     else gpr_$text('AUSBLENDEN',10,status);
    setcursor1(2,3); gpr_$text(' ZURUECK',8,status);
    end;
  Attributeaendern:
    begin
    setcursor1(0,1); gpr_$text(' ATTRIBUT ERGAENZEN',19,status);
    setcursor1(1,1); gpr_$text(' ATTRIBUT STREICHEN',19,status);
    setcursor1(2,1); gpr_$text(' ATTRIBUTREIHUNG AENDERN',24,status);
    setcursor1(0,2); gpr_$text(' HILFSATTRIBUT EINFUEHREN',25,status);
    setcursor1(1,2); gpr_$text(' HILFSATTRIBUT STREICHEN',24,status);
    setcursor1(2,2); gpr_$text(' ZURUECK',8,status);
    end;
  end (*case*);
end (*wrtmenue*);


function inPvorkommen (* PL:PListe): AListe *);
var res: AListe;
    vk: PListe;
    pos: integer;
    neu: boolean;
begin
res:=nil;
vk:=PL;
while vk<>nil do
  begin
  pos:=0;
  aAzuAL(vk^.prod,pos,res,neu);
  vk:=vk^.nxt;
  end;
inPvorkommen:=res;
end;
