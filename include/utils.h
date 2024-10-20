#ifndef __UTILS_H__
#define __UTILS_H__

#define SAFEVAL(x, val) if (!x) return val
#define SAFE(x) if (!x) return 0
#define PSAFE(x, y) if (!x) {printf y; return 0;}
#define ESAFE(x, y) if (!x) {perror(y); return 0;}

#endif // __UTILS_H__
