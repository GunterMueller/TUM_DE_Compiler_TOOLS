#ifndef MEMDEBUG

#define MEMAlloc(n)  	malloc(n)
#define MEMFree(p)  	free(p)

#else

extern char *MEMAlloc(/* int n */);
extern void MEMFree(/* char *p */);

#endif
