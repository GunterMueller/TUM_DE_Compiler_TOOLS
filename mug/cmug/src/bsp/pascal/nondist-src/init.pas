



                    

                                   
(* FUNCTION zero_fault_handler (IN f_status : pfm_$fault_rec_t): pfm_$fh_func_val_t; EXTERN;  *)


TYPE
  {declare an explicit argument pointer}
  pgm_arg_ptr = ^pgm_$arg;

VAR

  argc         : pinteger;      {argument count}
  arg_vec_addr : pgm_$argv_ptr; {argument vector}

  {declare array to hold arguments}
  arguments    : array [0..127] of pgm_arg_ptr;
  init_bitmap : gpr_$bitmap_desc_t; 
  mode : gpr_$display_mode_t {##:= gpr_$direct};  
  disp_bm_size : gpr_$offset_t;
  {hi_plane_id : gpr_$plane_t := 0; }
  attr_desc: gpr_$attribute_desc_t;
  stream:stream_$id_t;
  maxx,maxy,origx,origy,xborder,yborder:integer;
  padborder : boolean;

procedure writeandleave ( var fn : text; mess : string )  ; {##OPTIONS(NORETURN);}

begin
writeln(fn,mess);
{## irrende()}
end;


procedure AGinit;
var i:  integer;

begin
with AG do       { Initialisierung der Grammatik }
  begin
  PhasenId[0]:= chr(0); InGName[0]:= chr(0); OutGName[0]:= chr(0);
  Axiom:= 0; Terms:= 0; Nonterms:= 0; Prods:= 0; SemRules:=0; Attrs:= 0;
  Typen:=0;
  Konsistent:= false
  end;


for i:= 1 to maxanzA  do
   begin ATab[i].name:= '  '; ATab[i].name[0]:= chr(0) end; 
for i:= 1 to maxanzP  do
   begin PTab[i].name:= '  '; PTab[i].name[0]:= chr(0) end;
for i:= 1 to maxanzT  do
   begin  TTab[i].name:= '  '; TTab[i].name[0]:= chr(0) end;
for i:= 1 to maxanzNT do
   begin NTTab[i].name:= '  '; NTTab[i].name[0]:= chr(0) end;
for i:= 1 to maxanzSF do
   begin SFTab[i].name:= '  '; SFTab[i].name[0]:= chr(0) end;
for i:= 1 to maxanzTyp do
   begin TypTab[i].name:= '  '; TypTab[i].name[0]:=chr(0) end;
             { Ende der Initialisierung der Grammatik }
for i:=minvibslg to maxvibslg do ViBs[i]:=nil;
initfehlerspur;  

end;   {AGinit}

function Symbolinit;
var j:integer;
    Cfn:filename;
    direction: gpr_$direction_t;
begin
    {get a pointer tothe argument array}
    pgm_$get_args (argc,     {number of arguments} 
                   arg_vec_addr); {returned pointer}
    FOR j := 0 TO (argc - 1) DO 

        {typecast the pointer and load into argument array}
        arguments[j] := pgm_arg_ptr( arg_vec_addr^[j]);

    if argc > 1 then begin
 		     for j := 1 to arguments[1]^.len do
			fontname[j] := arguments[1]^.chars[j];
		     for j := arguments[1]^.len+1 to 80 do
			fontname[j] := chr(32);
		     fontnamelen := arguments[1]^.len;
		     end
		else fontname := '  '; 
  gibCDateiname(fontname,Cfn);
  if lesenerlaubt(Cfn) then
     begin
     gpr_$inq_text(font_id_orig,direction,status);
     gpr_$load_font_file (fontname,fontnamelen,font_id_set1,status);
     with ASymb do
       begin
       hoehe:=12; breite:=12;
       upb:=127;
       R2:= round( sqrt(  hoehe*hoehe + breite*breite ) / 2 ) + 1;
       gebund:= [];
       end;
     Symbolinit := TRUE;
     end
  else Symbolinit := FALSE; 
end;   {Symbolinit}


procedure tektronixein;                   
 var unobscured:boolean;
     font_id : integer; {identifier of a text font} 
     path:name_$pname_t;
     p_name_l,unit:integer;
     window:pad_$window_desc_t;                     
     w_size,w_no:integer;
     w_list:pad_$window_list_t;
     
begin 

 window.top := origy;
 window.left := origx;
 window.width := maxx + xborder ;
 window.height := maxy + yborder;   

 p_name_l:=0;
 unit:=1;                      
 disp_bm_size.x_size:=maxx;
 disp_bm_size.y_size:=maxy; 
 pad_$create_window(path , p_name_l , pad_$transcript  ,unit, window, stream , status); 
 if status.all <> status_$ok then error_$print(status);
 pad_$inq_windows(stream,w_list,w_size,w_no,status);  
 if status.all <> status_$ok then error_$print(status);
 pad_$set_auto_close(stream,w_no,true,status);
 if status.all <> status_$ok then error_$print(status); 
 pad_$set_border(stream,w_no,padborder,status);
 if status.all <> status_$ok then error_$print(status); 
 pad_$dm_cmd(stream,'tn',2,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$init(mode,stream,disp_bm_size,hi_plane_id,init_bitmap,status ); 
 if status.all <> status_$ok then error_$print(status);
 gpr_$set_auto_refresh(true,status); 
 if status.all <> status_$ok then error_$print(status);
 unobscured:=gpr_$acquire_display(status); 
 if status.all <> status_$ok then error_$print(status);
 seite0_desc:=init_bitmap;         
 attr_desc:=gpr_$attribute_block(seite0_desc,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$allocate_bitmap(disp_bm_size,hi_plane_id,attr_desc,seite1_desc,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$set_bitmap(seite0_desc,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$load_font_file('f7x13.b',SIZEOF('f7x13.b'),font_id,status);
 if status.all <> status_$ok then error_$print(status);
 gpr_$set_text_font(font_id,status);   
 if status.all <> status_$ok then error_$print(status); 
 gpr_$set_text_value(color_base,status);
 gpr_$set_draw_value(color_base,status);
end;


procedure terminit; 
label 999;
   
var a,b,c,tt,terminal,koordinaten: string;
            j,k:integer;
            id:pfm_$fh_handle_t; 
             maxterm_x, maxterm_y : integer;
             ERRF : text;  {fuer fehler bevor das Programm anlaeuft}

   function getvaluntil(delimiter: char): integer ; {liefert koordinaten aus einem String}

   label 99;
   var res : integer;
   {Achtung k ist globale Varaible} 

   begin

    res := 0;
    getvaluntil := 0 ;  (*Fehlerfall *)
    while (k < 80) do
    begin  
      if (koordinaten[k] = delimiter) then
                   begin 
                     k := k + 1 ;
                     goto 99 
                  end
                                      else
      begin
          res := res * 10 + ( ord( koordinaten[k]) - ord('0'))  ;
          k := k + 1
      end    
    end; 
    writeandleave(ERRF,'Bildschirmkoordinaten (Aufruf) falsch codiert');
    99: getvaluntil := res


    
     end;  {getvaluntil}
  



begin  
   padborder := false; {true}
   xborder   := 0; {5;  falls wegen padborder = true }
   yborder   := 0; {20 ;}  
   open(ERRF,'-STDOUT') ;
   rewrite(ERRF);




           { Feststellen des Terminals }
    {get a pointer tothe argument array}
    pgm_$get_args (argc,     {number of arguments} 
                   arg_vec_addr); {returned pointer} 
    FOR j := 0 TO (argc - 1) DO 

        {typecast the pointer and load into argument array}
        arguments[j] := pgm_arg_ptr( arg_vec_addr^[j]);

(* id:= pfm_$establish_fault_handler (fault_$quit,[],ADDR(zero_fault_handler ),status); 
  ^q zum drucken  war mal                   *)
if argc>2 then begin 
                 for j:=1 to arguments[2]^.len do
                  terminal[j]:=arguments[2]^.chars[j];
                 for j:=arguments[2]^.len+1 to 80 do terminal[j]:=chr(32);
                end                                          
           else terminal:='apollo_15_color';
origx := 0;
origy := 0;

if (terminal='apollo_1280_bw')
 then begin
       maxx:=1280 - xborder;
       maxy:=1024 - yborder ;
       color_nt:=1;
       color_t :=1;
       color_sem:=1;
       color_sy:=1;
       color_id :=1;
       color_icon:=1;
       color_base:=1;
       color_curs:=1;
       hi_plane_id:=0;
      end;

 if (terminal='apollo_15_color') then
     begin
       maxx:=1024  - xborder;
       maxy:=800 - yborder ; 
{1 rot, 0 schwarz, 2 greun 3 blau 4 schwach }
{5 gelb, 6 magenta, 7 schwach, 8 unsichtb, 9 dunkelgruen, 10 unsichtb 11 rot,}
{12 weiss-blau, 13 blau, 14 unsichtbar 15 braun 16 schwarz}

       color_nt:=9;  
       color_t :=15; 
       color_sem:=0; 
       color_sy:=3;
       color_id :=15; 
       color_icon:=1;
       color_base:=255; 
       color_curs:=6;
       hi_plane_id:=3;
    end; 



if (argc >3)
then begin 
     for j:=1 to arguments[3]^.len do
        koordinaten[j]:=arguments[3]^.chars[j];
        for j:=arguments[3]^.len+1 to 80 do koordinaten[j]:=chr(32);
        k :=2;
        if (koordinaten[2] <> ']') then {explizite groesse}
          begin
            maxterm_x := maxx;
            maxterm_y := maxy;
            origx := getvaluntil(',');
            origy := getvaluntil('x');
            maxx  := getvaluntil(',');
            maxy  := getvaluntil(']');
            if ((maxx + origx ) > maxterm_x ) then
                     begin
               writeandleave(ERRF,'Bildschrim zu klein : x-Koordinate');
               goto 999
                     end ;
            if ((maxy + origy ) > maxterm_y ) then
                     begin           
               writeandleave(ERRF,'Bildschrim zu klein : y-Koordinate');
               goto 999
                     end

          end
     end ; 
           
if (argc > 4)
then begin 
     for j:=1 to arguments[4]^.len do
       voreinstellung[j]:=arguments[4]^.chars[j];
     for j:=arguments[4]^.len+1 to 80 do voreinstellung[j]:=chr(32);
     ueberspringe := true;
     end
else Voreinstellung:= 'Grammatik';


        
   { Initialisierung des Terminals und der globalen Variablen bzw. Strings }
tektronixein;  {name isr historische Remineszenz, hat ncihts mehr mit tektronix zu tun }
     with rbs do
       begin
       ypixels:=maxy-1; xpixels:=maxx-1;
       zhoehe:=18; zbreite:=9;
       yhome:=maxy-zhoehe; R1:=15;
       vBildHoehe:=maxy-300;
       uRandvBild:=145;
       deltaY:=7; deltaX:=5;
       end;                                                                    
     with rbs, MeldFenst, MFenster do
       begin
       window_size.x_size  := rbs.zbreite*61 + 16;
       window_size.y_size  := rbs.zhoehe*5 + 16;
       window_base.x_coord := (xpixels - window_size.x_size) div 2;
       window_base.y_coord := (ypixels - window_size.y_size) div 2;
       LOecke_x := window_base.x_coord;
       LOecke_y := ypixels - window_base.y_coord;
       RUecke_x := LOecke_x + window_size.x_size - 11;
       RUecke_y := LOecke_y - window_size.y_size + 11;
       end;
     
{ Ende der Initialisierung der globalen Variablen bzw. Strings }

ALL:= nil; PLL:= nil; VLL:= nil; SFLL:= nil; ParLL:= nil; TypLL:= nil; HALL:= nil; SymbolLL:=nil; ViBsElmtLL:=nil; PunktLL:= nil;





vt100 := false;
AGtmp:='AG.tmp.$$$'; 
Verbindung:= Poly;
ATyp_info := undef;
Meldungen:= 0;
Bildnummer:=0;
aktSeite:= 0;
LAZY:=false;
EXTENSIV := true;
PraefixTab[0]:= chr(0);
PraefixTab[1]:= '-';
PraefixTab[2]:= '?';
PraefixTab[3]:= '+';
PromptChar:= chr(13);
IDchar:= '='; 
999:
end;   {terminit}

procedure zurueck;
begin   
 gpr_$terminate( false, status );  {Terminate the graphics session.} 
 if status.all <> status_$ok then error_$print(status);
 stream_$close(stream,status);
 if status.all <> status_$ok then error_$print(status);
end;   {zurueck}
