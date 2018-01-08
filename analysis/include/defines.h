#ifndef DEFINES_H
#define DEFINES_H

#define BPIX1P(EXPAND)     \
   EXPAND(1)               \
   EXPAND(2)               \
   EXPAND(3)               \
   EXPAND(4)               \

#define FPIX1P(EXPAND)     \
   EXPAND(5)               \
   EXPAND(6)               \
   EXPAND(7)               \

#define BTRKLT2P(EXPAND)      \
   EXPAND(1, 2)               \
   EXPAND(1, 3)               \
   EXPAND(1, 4)               \
   EXPAND(2, 3)               \
   EXPAND(2, 4)               \
   EXPAND(3, 4)               \

#define FTRKLT2P(EXPAND)      \
   EXPAND(1, 5)               \
   EXPAND(1, 6)               \
   EXPAND(1, 7)               \

#define BTRKLT3P(p, EXPAND)   \
   EXPAND(p, 1, 2)            \
   EXPAND(p, 1, 3)            \
   EXPAND(p, 1, 4)            \
   EXPAND(p, 2, 3)            \
   EXPAND(p, 2, 4)            \
   EXPAND(p, 3, 4)            \

#define FTRKLT3P(p, EXPAND)   \
   EXPAND(p, 1, 5)            \
   EXPAND(p, 1, 6)            \
   EXPAND(p, 1, 7)            \

#endif  /* DEFINES_H */
