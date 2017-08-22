#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN void Compress P_((Automat CoAutomat2,ClassDescr CoClasses2,KomprUebergang CoKomp2));

EXTERN void Classify P_((Automat ClAutomat,ClassDescr ClErgPtr));

#undef EXTERN
