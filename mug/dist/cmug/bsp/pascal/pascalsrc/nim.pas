PROGRAM nim(input,output);

VAR anz,n : integer;

BEGIN
  writeln;
  writeln('Bitte geben Sie die Anfangsmenge ein');
  readln;
  read(anz);
  REPEAT
    REPEAT
      IF anz > 4 THEN 
        n := anz MOD 4 
      ELSE 
        n := anz - 1;
      IF n = 0 THEN
        n := 1;
      anz := anz - n;
      writeln('   ich nehme ',n:1,'Stein(e), es bleiben ',anz:1,' .');
      writeln;
      IF anz <= 1 THEN
        writeln('  ich habe gewonnen.')
      ELSE
       BEGIN
        REPEAT
          writeln('   Ihr Zug:');
          readln;
          read(n);
          IF NOT (n IN [1,2,3]) THEN
            writeln('   ungueltige Anzahl');
        UNTIL n IN [1,2,3];
        anz := anz - n;
        IF anz <= 1 THEN
          writeln('   Sie haben gewonnen');
       END;
    UNTIL anz <= 1;
    writeln(' Revanche, wieviel Steine jetzt ?');
    readln;
    read(anz);
  UNTIL anz = 0;
  writeln;
  writeln;
  writeln(' Spiel beendet');
END.
         
