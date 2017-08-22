#define MAXMEM 1000

static struct { char *adr;
                int len;
              } Liste[MAXMEM];

static void check()
  {
  int i;
  char *a;
  int l;

  for(i=0;i<MAXMEM;i++)
    {
    if(Liste[i].len!=0)
      {
      a=Liste[i].adr;
      l=Liste[i].len;
      if( *(int*)a!=0x31415926 ||
          *(int*)(a+l-4)!=0x87654321 )
        {
        printf("ERROR #MEM# --003\n");
        printf("Eintrag %d:  Adr: %08x  Len: %d\n",i,a,l);
        exit(-1);
        }
      }
    }
  }

static void add(a,l)
char *a;
int l;
  {
  int i;
  int f;

  f=-1;

  for(i=0;i<MAXMEM;i++)
    {
    if(Liste[i].len==0) f=i;
    if( Liste[i].adr<=a && 
        a<Liste[i].adr+Liste[i].len )
      { printf("ERROR #MEM# --000\n");
        exit(-1);
      }
    }
  if(f==-1)
    {
    printf("ERROR #MEM# --001\n");
    exit(-1);
    }
  Liste[f].adr=a;
  Liste[f].len=l;  
  }

static void sub(a)
char *a;
  {
  int i,f;

  f=-1;

  for(i=0;i<MAXMEM;i++)
    {
    if(Liste[i].adr==a)
      {
      f=i;
      }
    }
  if(f==-1)
    {
    printf("ERROR #MEM# --002\n");
    exit(-1);
    }
  Liste[f].adr=0;
  Liste[f].len=0;
  }

char *MEMAlloc(n)
int n;
  {
  char *p;
  int l;
  l=((n+7)|3)+1;
  p=(char *)malloc(l);
  *(int*)p=0x31415926;
  *(int*)(p+l-4)=0x87654321;
  add(p,l);
  check();
  printf("malloc(%d)=0x%08x\n",n,p);
  return p+4;
  }

void MEMFree(p)
char *p;
  {
  check();
  sub(p-4);
  free(p-4);
  printf("Free 0x%08x\n",p);
  }

