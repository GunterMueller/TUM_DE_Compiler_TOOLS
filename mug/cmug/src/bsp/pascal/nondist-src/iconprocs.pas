





procedure syminvibs(* zeile,spalte,nr: integer *);
var symbolelmt: visymbolptr;
begin
beschaffevisymbol(symbolelmt);
with ViBs[zeile]^ do
  begin
  if lastsym=nil then firstsym:=symbolelmt else lastsym^.nxt:=symbolelmt;
  lastsym:=symbolelmt;
  symbolelmt^.spalte:=spalte;
  symbolelmt^.symbol:=nr;
  symbolelmt^.nxt:=nil;
  end
end;                   

procedure writesymbnr(s:integer);
 var flag:boolean;
 begin 
  flag:=false;
  if (s div 100) = 0 then begin gpr_$text(' ',1,status); flag:=true end
                     else begin
                           gpr_$text(chr(s div 100 + 48),1,status);
                           s:=s mod 100
                          end;
  if ((s div 10) = 0) and flag then gpr_$text(' ',1,status) 
                    else begin
                          gpr_$text(chr(s div 10 +48),1,status);
                          s:=s mod 10
                         end;
  gpr_$text(chr(s+48),1,status);
 end;

procedure writeikon(* y1,x1: integer; var sym: ASymbTyp *);
begin 
  gpr_$set_text_value(color_icon,status);
  gpr_$set_text_font(font_id_set1,status);
  setCursor(y1,x1);
  gpr_$text(chr(sym+64),1,status);
  gpr_$set_text_font(font_id_orig,status);
  gpr_$set_text_value(color_base,status);
end; (*writeikon*) 

procedure loescheteil(y,a:integer);
 var i:integer;
 begin
   for i:=1 to a do
    begin
     loeschewort(y,0,90);
     y:=y-rbs.zhoehe
    end
 end; 

procedure symbolwahl(* var atrb: Ident; var g: integer *);
const oRand=4;
var b,h,h1,h2,g1,yalt,yneu,index,minbreite,i: integer;
    fehler,clearscr,sw,IstName,ende: boolean;
    antwort:char;
    id:Ident;


procedure lkup1( y,x: integer; hl: HashListen; zugriff: HLZugriff; var istIdent: boolean; var s: Ident; var el: integer; var clrscreen: boolean);
var lg,fn,praefixop: integer;
    lapsus,id,fehler,ex: boolean;

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

begin (*lkup1*)
clrscreen:=false;
if g1=0 then s[0]:=chr(0);
repeat
  lapsus:=false;
  repeat
    editname(y,x,hl,s);
    id:=isIdent(s); 
    fehler:=istIdent and (not id);
    if fehler then meldefehler(1);
  until not fehler;
  
  if id then
    begin
    lg:=ord(s[0]);
    praefixop:=formpraefixop(s[lg]);
    if praefixop>0 then
      begin
      s[0]:=chr(pred(lg)); (* s jetzt evtl. leer *)
      listenwahl(hl,istIdent,zugriff,praefixop,s,el);
      clrscreen:=true;
      end
    else
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
        rdorwrt: if not ex then calldef(s,el); 
       end (* case *)
      end; (* else *)
    end (* if *)
  else 
    begin
    if ord(s[0])<>0 
       then if (hl=sfktHL) and (ord(s[0])=1) and (s[1]=IDchar) 
               then el:=IDNT
	       else meldefehler(30);
    end;
until not lapsus; 
istIdent:=isIdent(s);
end (*lkup*);


procedure updatesymbnr(nr:integer; bind:boolean);
  var i,h,b:integer;
 begin
  if nr <> 0 
  then
  with rbs,ASymb do
   begin
    h:=ypixels-oRand*zhoehe-zhoehe-hoehe;
    b:=3*zbreite;
    for i:=1 to nr-1
    do begin
        if b<minbreite then b:=b+4*zbreite
          else begin
                b:=3*zbreite;
                h:=h-2*zhoehe-hoehe
               end
        end; (* for *)
    loeschewort(h-zhoehe,b-2*zbreite,3);
    setCursor(h-zhoehe,b-2*zbreite); 
    if bind then gpr_$text('  *',3,status) else writesymbnr(nr)
   end; (* with *)
 end; (* updatesymbnr *)

procedure getnewATTR;
 var i:integer;
 begin
  gpr_$text(' Name : ',8,status);
  i:=AG.Attrs;
  g1:=0;
  while (i>0) do
   if ATab[i].symbol <> 0
     then i := ATab[i].nxt
     else begin
          g1:=i;
          i:=0;
          end;
   IstName:=false;
   if g1 <> 0
     then begin
            IstName:=false;
            index:=g1;
            id:=ATab[index].name;
          end; 
   lkup1(h,8*rbs.zbreite,attrHL,redonly,IstName,id,index,clearscr);
   if (g1<>0) and (ord(id[0]) = 0) and IstName 
      then id:=ATab[g1].name;
   if not IstName and clearscr
     then begin
            index:=0;
            symbolwahl(id,index);
            ende:=true;
          end
     else 
         if IstName
          then begin
                if clearscr 
                 then begin
                        symbolwahl(id,index);
                        ende:=true
                      end
                 else begin  
                       with ASymb do 
                        if ATab[index].symbol <> 0
                         then gebund:=gebund-[ATab[index].symbol];
                        g1:=ATab[index].symbol;
                        (*updatesymbnr(g1,false)*)
                      end; (* else *)
               end (* then *)
           else ende:=true;
 end; (* getnewATTR *)


procedure Aufforderung;
 begin
  with rbs, ASymb do
   begin
    h:=h-3*zhoehe;
    setCursor(h,0); 
    gpr_$text(' Bitte durch Angabe einer Nummer dem Attribut ',46,status);
    wrtIdent(id); newline;
    gpr_$text(' ein Symbol zuordnen ! ',23,status);
    newline;
    h:=h-3*zhoehe;
    setCursor(h,0);  
    gpr_$text(' gewaehlt fuer Attribut ',24,status); 
    wrtIdent(id); gpr_$text(' Symbol Nr. ',12,status); 
    CursorPos(h,b); b:=b+(36+ord(id[0]))*rbs.zbreite;
   end; (* with *)
 end; (* Aufforderung *)

begin  (*Symbolwahl*)
 if g<>0 
   then begin 
          index:=g;
          id:=atrb;
          g1:=ATab[index].symbol;
          if ATab[index].symbol <> 0
           then ASymb.gebund:=ASymb.gebund-[ATab[index].symbol];
        end;
 sw:=aktSeite=0;
 clearscr:=false;
 {Seite1;}
 clearscreen;
 h:=rbs.ypixels-oRand*rbs.zhoehe;
 setCursor(h,0);  
 gpr_$text(' Dienst: Attribut Symbol zuordnen',33,status); 
 newline;
 male4eck(false,h-3,h-5,rbs.zbreite,dist(33));
 h1:=h;
 ende:=false;
 h:=h-3*rbs.zhoehe;
 if g=0 
   then begin
          loescheteil(h,1); 
          setCursor(h,0);
          getnewATTR;
          if ende then IstName:=false;
          setCursor(h,0);
          loescheteil(h,1)
        end
   else IstName:=true;
 if IstName
   then begin
          h:=h1;
          with rbs, ASymb do
           begin
            if upb<=0 
              then meldefehler(29)
              else
              begin
                h:=h-zhoehe-hoehe; 
                b:=3*zbreite;
                minbreite:=xpixels-7*rbs.zbreite;
                for i:=1 to upb do
                 begin
	           writeikon(h,b,i);
	           setCursor(h-zhoehe,b-2*zbreite); 
                   if not (i in gebund) then writesymbnr(i) else gpr_$text('  *',3,status);
	           if b<minbreite
                     then b:=b+4*zbreite
	             else
	              begin
	                b:=3*zbreite;
	                h:=h-zhoehe-hoehe-zhoehe;
	              end;
	         end; (* for *)
                h1:=h;
                Aufforderung; 
              end; (* else *)
              repeat (* 1 *)
               repeat (* 2 *) 
                begin
                loeschewort(h,b,20);
                g1:=readnat4(h,b);
                fehler:=g1>upb;
                if not fehler then fehler:=g1 in gebund;
                if fehler 
                 then meldefehler(3) 
                 else begin
                      gebund:=gebund+[g1];
                      ATab[index].symbol:=g1;
                      updatesymbnr(g1,true)
                      end 
                 end;
              until not fehler; (* repeat 2 *)
              h2:=h;
              repeat (* 3 *)
                h:=h-3*zhoehe;     {war 6}
                setCursor(h,0);
                i:=AG.Attrs;
                while (i>0) do
                 if ATab[i].symbol <> 0
                  then i:=ATab[i].nxt
                  else begin
                        i:=-1;
                        antwort:='j'
                       end;
                if i<> -1
                 then begin
                       gpr_$text(' Weiteres Symbol zuordnen ?  (j/n) ',35,status);
                       keys := ['j','n','J','N']; {Create a key set.}
                       gpr_$enable_input(gpr_$keystroke, keys, status);
                       keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
                       gpr_$enable_input(gpr_$buttons, keys, status); 
                       unobscured := gpr_$event_wait(ev_type, antwort, ev_pos, status); 
                      end;
                if (antwort='j') or (antwort='J')
                  then begin
                      h:=h-3*zhoehe;
                      loeschewort(h,0,79);
                      setCursor(h,0);
                      getnewATTR;
                      updatesymbnr(g1,false);
                      if ende then IstName:=true;
                  end
                  else begin
                      IstName:=true;
                      ende:=true
                  end;
                  if not ende then loescheteil(h,1);
                  h:=h2;
              until IstName; (* repeat 3 *)
              if ende
                then clearscreen
                else begin 
                    loescheteil(h1-3*zhoehe,10);
                    h:=h1;
                    Aufforderung;
               end; (* else *)
            until ende; (* repeat 1 *) 
           end; (* with *)
        end; (* then *)
 if sw then {Seite0;}
 end (*symbolwahl*);
 
