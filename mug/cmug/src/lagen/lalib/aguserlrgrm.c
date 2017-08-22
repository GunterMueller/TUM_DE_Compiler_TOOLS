#include <stdio.h>

extern void LAuswerterGen();
extern void EingabeBaumRep();
extern void AusgabeBaumRep();
extern void write_PGint();

#ifdef __STDC__
void AGuser(void)
#else /* ! __STDC__ */
void AGuser()
#endif /* ! __STDC__ */
{
  fprintf(stderr,"Start des L-Auswerters\n");
  LAuswerterGen();
  EingabeBaumRep();
  AusgabeBaumRep();
  write_PGint();
}

