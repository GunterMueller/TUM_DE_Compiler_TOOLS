#ifndef EXTERN
#define EXTERN        extern
#endif

EXTERN void Push P_((Automat PuAutomat));

EXTERN void PushEvent P_((Event PeEvent));

EXTERN void PushSet P_((EventSet PsSet));

EXTERN void AGenSet P_((EventSet PsSet,Automat *outautomat));

EXTERN void PushTStar P_((void));

EXTERN void AGenTStar P_((Automat *outautomat));

EXTERN void PushStr P_((EventString PsString));

EXTERN void AGenStr P_((EventString PsString,Automat *outautomat));

EXTERN void Twist P_((void));

EXTERN Automat Top P_((void));

EXTERN Automat Pop P_((void));

EXTERN void DisposeAutomaton P_((Automat DaAutomat));

EXTERN void Concat P_((Automat inautomat1,Automat inautomat2,Automat *outautomat));

EXTERN void Alternative P_((Automat inautomat1,Automat inautomat2,Automat *outautomat));

EXTERN void Star P_((Automat inautomat,Automat *outautomat));

EXTERN void Plus P_((Automat inautomat,Automat *outautomat));

EXTERN void Option P_((Automat inautomat,Automat *outautomat));

EXTERN void Myhill P_((Automat inautomat,Automat *outautomat));

EXTERN void DefineAction  P_((Action DaAction,Automat inautomat,Automat *outautomat));

EXTERN void Negate P_((Automat inautomat,Automat *outautomat));

EXTERN void Allbut P_((Automat inautomat,Automat *outautomat));

EXTERN void initautstack P_((void));

EXTERN void CopyAutomat P_((Automat inautomat,Automat *outautomat));

EXTERN void Multiply P_((Automat *inautomat,int n,int m));

#undef EXTERN
