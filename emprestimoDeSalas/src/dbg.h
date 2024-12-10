#ifndef DBG_H
#define DBG_H

//#define DBG 0

#if DBG == 1
#warning DBG MODE ON

#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);
#define dbgi(x) printf("%s = %d\n", #x, x);
#endif

#endif