#pragma once
#include "defines.h"


#define _FORCE_INLINE_ __attribute__((__always_inline__)) __inline__
#define  FORCE_INLINE  __attribute__((always_inline)) inline


#ifndef M_PI
  #define M_PI 3.14159265358979323846f
#endif


#define WITHIN(N,L,H)       ((N) >= (L) && (N) <= (H))
#define NUMERIC(a)          WITHIN(a, '0', '9')
#define NUMERIC_SIGNED(a)   (NUMERIC(a) || (a) == '-' || (a) == '+')
#define DECIMAL(a)          (NUMERIC(a) || a == '.')
#define DECIMAL_SIGNED(a)   (DECIMAL(a) || (a) == '-' || (a) == '+')

// AVR compatibility
#define strtof strtod


#define SEC_TO_MS(N) uint32_t((N)*1000UL)
#define MMM_TO_MMS(MM_M) float(float(MM_M) / 60.0f)


//i have absolute no idea what those are doing...
#define TERN(O,A,B)         _TERN(_ENA_1(O),B,A)    // OPTION converted to '0' or '1'
#define TERN0(O,A)          _TERN(_ENA_1(O),0,A)    // OPTION converted to A or '0'
#define TERN1(O,A)          _TERN(_ENA_1(O),1,A)    // OPTION converted to A or '1'
#define TERN_(O,A)          _TERN(_ENA_1(O),,A)     // OPTION converted to A or '<nul>'
#define _TERN(E,V...)       __TERN(_CAT(T_,E),V)    // Prepend 'T_' to get 'T_0' or 'T_1'
#define __TERN(T,V...)      ___TERN(_CAT(_NO,T),V)  // Prepend '_NO' to get '_NOT_0' or '_NOT_1'
#define ___TERN(P,V...)     THIRD(P,V)              // If first argument has a comma, A. Else B.
#define _ENA_1(O)           _ISENA(CAT(_IS,CAT(ENA_, O)))
#define _ISENA(V...)        IS_PROBE(V)
#define IS_PROBE(V...) SECOND(V, 0)     // Get the second item passed, or 0
#define _CAT(a,V...) a##V
#define CAT(a,V...) _CAT(a,V)


#define ISEOL(C)            ((C) == '\n' || (C) == '\r')


#define FIRST(a,...)     a
#define SECOND(a,b,...)  b
#define THIRD(a,b,c,...) c


#define TBI(N,B) (N ^= _BV(B))
#define _BV32(b) (1UL << (b))
#define TEST32(n,b) !!((n)&_BV32(b))
#define SBI32(n,b) (n |= _BV32(b))
#define CBI32(n,b) (n &= ~_BV32(b))
#define TBI32(N,B) (N ^= _BV32(B))


#define COUNT(a)            (sizeof(a)/sizeof(*a))


#define RAD2DEG(r) ((r)*180.0f/float(M_PI))
#define DEG2RAD(d) ((d)*float(M_PI)/180.0f)



