
#ifdef DEBUG
#define		_BEGIN_		_FORMOUT_("{") 
#define		_END_		_FORMOUT_("}")
#define		_RETURN_	_FORMOUT_(">>>")
#define		_INIT_		_FORMOUT_("INIT")
#define		_EXIT_		_FORMOUT_("EXIT")

#define		_FORMOUT_(s)	printf("%16.16s:%4d %8s ----------------------------------\n",__FILE__,__LINE__,s);

#define		_TRA_	printf("                      ");printf(
#define		_TRE_	);fflush(stdout);
#else
#define		_BEGIN_	 
#define		_END_	
#define		_RETURN_
#define		_INIT_	
#define		_EXIT_	

#define		_FORMOUT_(s)	printf("%16.16s:%4d %8s ----------------------------------\n",__FILE__,__LINE__,s);

#define		_TRA_  (
#define		_TRE_	); 
#endif

