#ifndef DBG_H
#define DBG_H

#define DBG 1

#if DBG == 1
#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);
#define dbgi(x) printf("%s = %d\n", #x, x);
#endif

#endif