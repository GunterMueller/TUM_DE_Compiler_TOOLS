#ifndef EXTERN
#define EXTERN        extern
#endif

public void Minimize P_((Automat inautomat,Automat *outautomat));
public void initminimier P_((void));
public  void showPartitions P_((StateSet *MinParts));
public  void statistics P_((Automat automat));

#undef EXTERN
