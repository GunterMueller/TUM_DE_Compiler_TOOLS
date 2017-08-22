program einlesen(input,output);





TYPE
  {declare an explicit argument pointer}
  pgm_arg_ptr = ^pgm_$arg;

VAR

  argc         : pinteger;      {argument count}
  arg_vec_addr : pgm_$argv_ptr; {argument vector}

  {declare array to hold arguments}
  arguments    : array [0..127] of pgm_arg_ptr;

procedure Grammatikeinlesen (* eingabedatei: filename *);
var i,j:             integer;
      k:             1..144;
       l:            integer;
    c:               char;
    GIN:             text;
    SYMBOLE:         text;
    SY:              file of ASymbDatum;
    SymbolDateiname: filename; 
    convertdateiname:string;
    Symbolextension: string; 
    convertextension: string;
    neu            : boolean;


procedure redint(var i:integer);
 var s:string;
     k:integer;
     c:char;
 begin            
  readln(SYMBOLE,c);
  i:=ord(c);
  if i=253 then i:=10; 
 end;                        

begin   
{get a pointer to the argument array}
pgm_$get_args (argc,     {number of arguments} 
               arg_vec_addr); {returned pointer} 
if argc<>2 
 then begin
       writeln('Aufruf: conv_ap <Grammatik-Dateiname>');
       writeln('Es wird eine Datei <Grammatik-Dateiname>.symbole erzeugt.');
       writeln('Die Datei <Grammatik-Dateiname>.ascsymb muss im aktuellen Directory stehen !');
       pgm_$exit;
      end;
FOR j := 0 TO (argc - 1) DO 
{typecast the pointer and load into argument array}
arguments[j] := pgm_arg_ptr( arg_vec_addr^[j]);
symbolextension:='.symbole';
convertextension:='.ascsymb'; 
for j:=1 to arguments[1]^.len do 
 begin
  Symboldateiname[j]:=arguments[1]^.chars[j];
  Convertdateiname[j]:=symboldateiname[j]
 end;  
for i:=1 to 8 do begin
                  symboldateiname[j+i]:=symbolextension[i];
                  convertdateiname[j+i]:=convertextension[i]
                 end;
for i:=j+9 to 80 do
 begin
  Symboldateiname[i]:=' ';
  Convertdateiname[i]:=' '
 end;
open( SYMBOLE, convertDateiname );
reset(SYMBOLE);
redint(ASymb.hoehe);
redint(ASymb.breite);
redint(ASymb.upb);
      for l:=0 to ASymb.upb do 
       begin
        ASymb.vorrat[l]:=[];
        redint(i);
        while i<>255
          do begin
              k:=i;
              ASymb.vorrat[l]:=ASymb.vorrat[l]+[k];
              redint(i)
             end;
       end;
for l:=ASymb.upb+1 to maxanzASymb do ASymb.vorrat[l]:=[];
ASymb.gebund:=[];
redint(i);
 while i<>254 do
  begin
   asymb.gebund:=asymb.gebund+[i];
   redint(i)       ;
  end; 
ASymb.vorrat[0]:=[1,
         2,
         3,
         4,
         5,
         6,
         7,
         8,
         9,
        10,
        11,
        12,
        13,
        24,
        25,
        28,
        29,
        30,
        31,
        32,
        36,
        37,
        45,
        48,
        49,
        57,
        60,
        61,
        64,
        65,
        66,
        67,
        68,
        72,
        73,
        75,
        84,
        85,
        87,
        96,
        97,
       100,
       101,
       102,
       103,
       104,
       108,
       109,
       120,
       121,
       126,
       127,
       132,
       133,
       134,
       135,
       136,
       137,
       138,
       139,
       140,
       141,
       142,
       143,
       144 ];

ASymb.R2:= round( sqrt(  ASymb.hoehe*ASymb.hoehe +
			 ASymb.breite*ASymb.breite ) /2 ) + 1;
close(SYMBOLE);
open(SY,symboldateiname);
rewrite(SY);
SY^:=ASymb;
put(SY);
close(SY);
end;  (*Grammatikeinlesen*)
begin

Grammatikeinlesen;
writeln('Symbole konvertiert');
end.

