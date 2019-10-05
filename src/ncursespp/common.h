#ifndef NPP_COMMON_H_
#define NPP_COMMON_H_

#include <stdio.h>
#include <vector>
#include <string>

#define NPP_FATAL(...)            \
do {                              \
  fprintf(stderr, __VA_ARGS__);   \
  exit(1);                        \
} while(0);

#ifdef NPP_DEBUG
// glog style checks
#define DCHECK(cond)                      \
do {                                      \
  if(!(cond)) {                           \
    NPP_FATAL("%s:%d:\n  '%s' failed!\n", \
              __FILE__, __LINE__, #cond); \
  }                                       \
} while(0);
#else
#define DCHECK(cond) void(0);
#endif

#define DCHECK_OP(lhs, op, rhs) DCHECK((lhs) op (rhs))
#define DCHECK_EQ(lhs, rhs) DCHECK_OP(lhs, ==, rhs)
#define DCHECK_NE(lhs, rhs) DCHECK_OP(lhs, !=, rhs)
#define DCHECK_LT(lhs, rhs) DCHECK_OP(lhs, <, rhs)
#define DCHECK_GT(lhs, rhs) DCHECK_OP(lhs, >, rhs)
#define DCHECK_LE(lhs, rhs) DCHECK_OP(lhs, <=, rhs)
#define DCHECK_GE(lhs, rhs) DCHECK_OP(lhs, >=, rhs)

namespace npp {


}

#endif