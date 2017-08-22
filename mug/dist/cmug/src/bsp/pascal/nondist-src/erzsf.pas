





function hatberechenbareAttribute (*: boolean; *);
var vok:     VokListe;
    attrL:   AListe;
    hatAttr: boolean;
begin
hatAttr:= (PTab[ aktPNr ].hilfsAttr <> nil);
if not hatAttr
then begin
     vok:= PTab[ aktPNr ].vater;
     if (vok <> nil)
     then begin
          if vok^.konsistent
          then attrL:= NTTab[ vok^.nt ].derAttr
          else attrL:= vok^.spezDerA;
          hatAttr:= (attrL <> nil)
          end;
     if not hatAttr
     then begin
          vok:= PTab[ aktPNr ].soehne;
          while (vok <> nil) do
            begin
            if (vok^.typ = nont)
            then begin
                 if vok^.konsistent
                 then attrL:= NTTab[ vok^.nt ].inhAttr
                 else attrL:= vok^.spezInhA;
                 hatAttr:= (attrL <> nil)
                 end;
            if hatAttr then vok:= nil else vok:= vok^.nxt
            end;
          end;
     end;
hatberechenbareAttribute:= hatAttr
end;   {hatberechenbareAttribute}

procedure semFkteinfuehren;
const plusaktpar = true;
var attrnr, attrnr2, sfnr,
    index, i, x, y,x2,y2,a: integer;
    vok, vok2,v:  VokListe;
    hatergtyp, mehrfach,
    clrscreen, abbrechen,
    ok:   boolean;
    sf:   SemFktListe;
    fpar: TypListe;
    par:  ParListe;
    p:    PListe;
    id:   Ident;
    c:    char;
begin
if hatberechenbareAttribute
then begin
repeat
  repeat
    meldung(15);
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
			meldung(15);
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
      bestimmeTermoderAttr( y, x, vok, attrnr )
    until (attrnr <> 0) or abbrechen;	{abbrechen wird im fadenkreuz besetzt}
    if not abbrechen
    then begin
         istzielpar( vok, attrnr, ok );
         if ok
         then begin
	      meldung(21); wrtIdent( ATab[attrnr].name );
	      gpr_$text(' mit dem Typ ',13,status); wrtIdent( TypTab[ATab[attrnr].typ].name );
	      if schonberechnet( vok, attrnr, sf, par )
	      then begin
	           meldung( 4 );
		   meldung( 6 );
		   antworte(janein,c);
		   clearmeldung;
	           if (c = 'J')
	           then begin
			loescheParVersorgung( sf, par, true );
			if not hatSFerg( sf )
			then begin
			     loescheSemFktgr( sf ); gibfreiSF( aktPNr, sf )
			     end
			end
	           else begin abbrechen:= true; ok:= false end;
	           end;
	      end  {ende von ok}
         else quitmeldung;
         end   {not abbrechen}
    else clearmeldung;
  until ok or abbrechen;   {Hier ist ein korrektes (Hilfs-) Attribut selektiert}
  if not abbrechen 			{oder abbrechen = TRUE}
  then begin  
       repeat 
       ok:=false;
       meldung( 10 ); wrtIdent( TypTab[ ATab[attrnr].typ ].name );
       meldung( 26 );
       ok:= false; CursorPos(y,x);
       initkontext;
       with ViBs[minvibslg]^ do
	 begin
         viline:='Waehlen Sie eine Funktion mit einem Ergebnis vom Typ';
	 insert( TypTab[ ATab[attrnr].typ ].name ,viline,61);
	 end; 
       lkup( y, x, sfktHL, rdorwrt, ok, id, sfnr, clrscreen );
       if ok
       then begin
            fpar:= SFTab[sfnr].erglist;
            hatergtyp:= false; mehrfach:= false;
            while (fpar <> nil) do
	      begin
	      if ( fpar^.typ = ATab[attrnr].typ )
	      then if not hatergtyp
	           then hatergtyp:= true
	           else mehrfach:= true;
	      fpar:= fpar^.nxt
	      end;
            if not hatergtyp then begin ok:= false; meldung( 13 ); quitmeldung; end
            end
       else if (sfnr = IDNT) then ok:= true; 
       clearmeldung;
       until ok or (ord(id[0])=0);
       if not ok
       then (*begin
            meldung( 7 ); meldung( 9 );
            read(c); if (c = '0') then abbrechen:= true;
            end;*)
       clearmeldung
       end
until ok or abbrechen;
if not abbrechen
then begin
     if (sfnr <> IDNT)
     then begin
     	  beschaffeSF( sf );
     	  beschaffeP( p ); p^.prod:= aktPNr;            {Festhalten}
     	  p^.nxt:= SFTab[ sfnr ].anwendungen;           {der neuen}
          SFTab[ sfnr ].anwendungen:= p;          {Anwendungsstelle}
          y:= rbs.uRandvBild-gibazh(IconsUeberText);
      	  signatur( plusaktpar, y, sfnr );
     	  sf^.semfkt:= sfnr;
     	  sf^.quellpar:= nil;
     	  sf^.zielpar:= nil;
     	  sf^.versorgt:= false;
     	  sf^.nxt:= PTab[ aktPNr ].semRegeln;
     	  PTab[ aktPNr ].semRegeln:= sf;
     	  fpar:= SFTab[ sfnr ].parlist;
     	  while (fpar <> nil) do
       	    begin
       	    beschaffePar( par );
            par^.vok:= nil;
            par^.attr:= 0;
            par^.verb:= nil;
            par^.nxt:= sf^.quellpar;
            sf^.quellpar:= par;
            fpar:= fpar^.nxt
            end;
          fpar:= SFTab[ sfnr ].erglist;
          while (fpar <> nil) do
            begin
            beschaffePar( par );
            par^.vok:= nil;
            par^.attr:= 0;
            par^.verb:= nil;
            par^.nxt:= sf^.zielpar;
            sf^.zielpar:= par;
            fpar:= fpar^.nxt
            end;
          if mehrfach
          then begin
	       meldung(22); wrtIdent( TypTab[ ATab[ attrnr ].typ ].name );
	       repeat
	       waehleformPar( plusaktpar, y, sfnr, 's', true, ATab[attrnr].typ, index, fpar )
	       until (index <> 0);
	       clearmeldung;
	       end
          else begin
               fpar:= SFTab[ sfnr ].erglist; index:= 1;
	       while (fpar^.typ <> ATab[ attrnr ].typ) do
	         begin fpar:= fpar^.nxt; index:= index+1 end
               end;
          signatur2( sf, vok, attrnr, index );
	  if sf^.semfkt <> IDNT
	   then if SFTab[sf^.semfkt].issynfkt
		 then begin
		      meldung(60);
		      antworte(obenunten,c);
		      if c='A' then abbrechen := true
			       else sf^.gedreht := c='O';
		      clearmeldung;
		      end;
          SFpositionieren( sf, 0, -(dist(ord(SFTab[sf^.semfkt].name[0]))div 2),
	                   true, abbrechen );
          if abbrechen
	  then begin
	       loeschesignatur( true, y, sf^.semfkt );
	       gibfreiSF( aktPNr, sf );
	       clearmeldung
	       end
          else begin
               par:= sf^.zielpar;
               for i:= 1 to index-1 do par:= par^.nxt;
               par^.vok:= vok;
               par^.attr:= attrnr;
               par^.verb:= nil;
               sf^.versorgt:= isSFversorgt(sf);
	       aenderelinienfuehrung( sf, par, true, false );
               if sf^.semfkt <> IDNT
                then 
                 if SFTab[sf^.semfkt].issynfkt
                  then zeichneParVersSynfkt(sf,par,true)
	          else zeichneParVersorgung( sf, par, true )
	        else zeichneParVersorgung( sf, par, true );
               ParVersorgungaendern( sf )
	       end
          end
     else begin
          repeat
            meldung(27);
            meldung(45);
	    leave_meldung;
	    CursorPos(y,x);
            repeat
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
			meldung(27);
			meldung(45);
			leave_meldung;
			CursorPos(y,x)
			end;
                setCursor(y,x);
                fadenkreuz(y,x,abbrechen);
               until (ev_char<>kbd_$m3d);
               with rbs do loesche4eck(uRandvBild-2*gibazh(IconsUeberText)-3,uRandvBild-gibazh(IconsUeberText)-5,0,xpixels);
               end;
                bestimmeTermoderAttr( y, x, vok2, attrnr2 )
              until (attrnr2 <> 0) or (vok2 <> nil) or abbrechen
            until (attrnr <> attrnr2) or (vok <> vok2) or abbrechen;
	    if not abbrechen
	    then begin
	         if (attrnr2 <> 0)
                 then begin
		      if (ATab[attrnr].typ = ATab[attrnr2].typ)
		      then ok:= true
		      else begin
		           ok:= false; meldung(0);
		           wrtIdent( TypTab[ ATab[attrnr2].typ ].name );
		           end
		      end
	         else begin
		      if (vok2^.typ = nont)
		      then wrtERR1('SemFkteinfuehren: Vokabel muesste Terminal sein (erzeuge ID)')
		      else begin
	                   ok:= true;
		           if not Twirdverwendet( vok2^.t )
		           then TTab[vok2^.t].typ:= ATab[attrnr].typ
		           else begin
     		                if (ATab[attrnr].typ <> TTab[vok2^.t].typ)
		                then begin
			             meldung( 36 );
			             wrtIdent(TypTab[ TTab[vok2^.t].typ ].name);
			             gpr_$text(' verwendet!',11,status); meldung( 37 );
                         keys := ['j','J','n','N']; {Create a key set.}
                         gpr_$enable_input(gpr_$keystroke, keys, status);
                         keys := [kbd_$m1d,kbd_$m2d,kbd_$m3d]; {Create a key set.}
                         gpr_$enable_input(gpr_$buttons, keys, status); 
                         unobscured := gpr_$event_wait(ev_type, c, ev_pos, status);  
			             gpr_$text(c,1,status);
			             if (c = 'n')
			             then ok:= false
			             else begin
				          lspmbdgTg( vok2^.t );
		    		          TTab[vok2^.t].typ:= ATab[attrnr].typ 
				          end
			             end
		                end
		           end
		      end;
	         if not ok
	         then begin
		      meldung(7); meldung(9);
		      pread(c); if (c = '0') then abbrechen:= true
		      end
		 end;   {ende von nicht abbrechen}
	    clearmeldung
	  until ok or abbrechen;
	  if not abbrechen
	  then begin
       	       beschaffeSF( sf );
       	       sf^.semfkt:= IDNT;
       	       beschaffePar( sf^.zielpar );
	       sf^.zielpar^.vok:=  vok;
	       sf^.zielpar^.attr:= attrnr;
	       sf^.zielpar^.verb:= nil;
	       sf^.zielpar^.nxt:= nil;
       	       beschaffePar( sf^.quellpar );
	       sf^.quellpar^.vok:=  vok2;
	       sf^.quellpar^.attr:= attrnr2;
	       sf^.quellpar^.verb:= nil;
	       sf^.quellpar^.nxt:= nil;
       	       sf^.versorgt:= true;
	       sf^.X:= 0; sf^.vx:= 0;
	       sf^.Y:= 0; sf^.vy:= 0;
       	       sf^.nxt:= PTab[ aktPNr ].semRegeln;
       	       PTab[ aktPNr ].semRegeln:= sf;
	       aenderelinienfuehrung( sf, sf^.zielpar, true, false );
               if sf^.semfkt <> IDNT
                then
                  if SFTab[sf^.semfkt].issynfkt
                   then zeichneParVersSynfkt(sf,sf^.zielpar,true)
	           else zeichneParVersorgung( sf, sf^.zielpar, true )
	        else zeichneParVersorgung( sf, sf^.zielpar, true )
	       end
	  end
     end  {nicht abbrechen}
end   {es sind berechenbare Attribute vorhanden}
else meldung( 42 )
end;   {semFkteinfuehren}

