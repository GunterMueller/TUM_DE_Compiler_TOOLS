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
var i,j,k:           integer;
    c:               char;
    GIN:             text;
    SYMBOLE:         text;
    SY:              file of ASymbDatum;
    SymbolDateiname,ConvertDateiname: filename;
    Symbolextension,Convertextension: string;
    neu            : boolean;


begin   
{get a pointer to the argument array}
pgm_$get_args (argc,     {number of arguments} 
               arg_vec_addr); {returned pointer} 
if argc<>2 
 then begin
       writeln('Aufruf: conv_vax <Grammatik-Dateiname>');
       writeln('Es wird eine Datei <Grammatik-Dateiname>.ascsymb erzeugt.');
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
 
open(SY,SymbolDateiname);
reset(SY);
ASymb:=SY^;
close(SY);
open( SYMBOLE, ConvertDateiname );
rewrite(SYMBOLE);
writeln(SYMBOLE,chr(ASymb.hoehe));
writeln(SYMBOLE,chr(ASymb.breite));
writeln(SYMBOLE,chr(ASymb.upb));
if ASymb.upb>255 then k:=255 else k:=ASymb.upb;
for i:=0 to k
 do begin
     for j:=1 to 144
      do if j in ASymb.vorrat[i] 
       then if j=10 
             then writeln(SYMBOLE,chr(253))
             else writeln(SYMBOLE,chr(j));
     writeln(SYMBOLE,chr(255));
    end;                                      
for i:=1 to ASymb.upb
 do if i in ASymb.gebund
     then if i=10
           then writeln(SYMBOLE,chr(253))
           else writeln(SYMBOLE,chr(i));
writeln(SYMBOLE,chr(254));
close(SYMBOLE); 
end;  (*Grammatikeinlesen*)
begin
Grammatikeinlesen;
writeln('Symbole konvertiert !');
end.

