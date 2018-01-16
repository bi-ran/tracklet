#if defined INCLUDE_VZ_BINS || defined INCLUDE_VZ_RANGE || defined INCLUDE_VZ_N
#ifndef DECLARED_VZ_N
#define DECLARED_VZ_N
   const int nvz = 30;
#endif  /* DECLARED_VZ_N */
#if defined INCLUDE_VZ_BINS || defined INCLUDE_VZ_RANGE
#ifndef DECLARED_VZ_RANGE
#define DECLARED_VZ_RANGE
   const float vzmin = -15;
   const float vzmax = 15;
#endif  /* DECLARED_VZ_RANGE */
#if defined INCLUDE_VZ_BINS
#ifndef DECLARED_VZ_BINS
#define DECLARED_VZ_BINS
   float vzb[nvz + 1];
   for (int i=0; i<=nvz; i++)
      vzb[i] = i * (vzmax - vzmin) / nvz + vzmin;
#endif  /* DECLARED_VZ_BINS */
#endif  /* defined INCLUDE_VZ_BINS */
#endif  /* defined INCLUDE_VZ_BINS || defined INCLUDE_VZ_RANGE */
#endif  /* defined INCLUDE_VZ_BINS || defined INCLUDE_VZ_RANGE || defined INCLUDE_VZ_N */

#if defined INCLUDE_ETA_BINS || defined INCLUDE_ETA_RANGE || defined INCLUDE_ETA_N
#ifndef DECLARED_ETA_N
#define DECLARED_ETA_N
   const int neta = 36;
#endif  /* DECLARED_ETA_N */
#if defined INCLUDE_ETA_BINS || defined INCLUDE_ETA_RANGE
#ifndef DECLARED_ETA_RANGE
#define DECLARED_ETA_RANGE
   const float etamin = -3.6;
   const float etamax = 3.6;
#endif  /* DECLARED_ETA_RANGE */
#if defined INCLUDE_ETA_BINS
#ifndef DECLARED_ETA_BINS
#define DECLARED_ETA_BINS
   float etab[neta + 1];
   for (int i=0; i<=neta; i++)
      etab[i] = i * (etamax - etamin) / neta + etamin;
#endif  /* DECLARED_ETA_BINS */
#endif  /* defined INCLUDE_ETA_BINS */
#endif  /* defined INCLUDE_ETA_BINS || defined INCLUDE_ETA_RANGE */
#endif  /* defined INCLUDE_ETA_BINS || defined INCLUDE_ETA_RANGE || defined INCLUDE_ETA_N */

#if defined INCLUDE_MULT_BINS || defined INCLUDE_MULT_N
#ifndef DECLARED_MULT_N
#define DECLARED_MULT_N
   const int nmult = 15;
#endif  /* DECLARED_MULT_N */
#if defined INCLUDE_MULT_BINS
#ifndef DECLARED_MULT_BINS
#define DECLARED_MULT_BINS
   float multb[nmult + 1] = {
          0,   20,   50,  100,  200,
        320,  540,  800, 1200, 1750,
       2400, 3200, 4200, 5400, 7000,
      12800
   };
#endif  /* DECLARED_MULT_BINS */
#endif  /* defined (INCLUDE_MULT_BINS) */
#endif  /* defined (INCLUDE_MULT_BINS) || defined (INCLUDE_MULT_N) */
