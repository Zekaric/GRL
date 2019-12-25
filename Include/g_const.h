/******************************************************************************
file:       Gconst
author:     Robbert de Groot
copyright:  2000-2012, Robbert de Groot
******************************************************************************/

/*lint -save -e960 -e961 -e9026 */

#if !defined(GCONSTH)
#define      GCONSTH

#if !defined(GRL_DLL)
#  define      grlAPI
#else
#  if defined(GRL_EXPORTS)
#     define   grlAPI __declspec(dllexport)
#  else
#     define   grlAPI __declspec(dllimport)
#  endif
#endif

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
constant:
******************************************************************************/
#if _DEBUG == 1

#define COMPILE_TEST    0

#define CHECK_MEMORY    0

#define GPROFILE_IS_ON  0
#define GTRACE_IS_ON    0

#else

#define COMPILE_TEST    0

#define CHECK_MEMORY    0

#define GPROFILE_IS_ON  0
#define GTRACE_IS_ON    0

#endif


// Windows platform.
#if defined(WIN32)
#define grlWINDOWS      1

// Swapping to change little endian to big endian.
#define grlSWAP_NEEDED  1
#else
// No Swapping.  Architecture is big endian.
#define grlSWAP_NEEDED  0
#endif

#if defined(_WIN64)
#define grl64        1
#else
#define grl32        1
#endif

/******************************************************************************
type:
******************************************************************************/
#if COMPILE_TEST == 1
typedef Gn4                Gid;
#define GidMAX             Gn4MAX

typedef Gi2                Gcount;
#define GcountMAX          Gi2MAX
#define gcountIsGood(C)    (0 <= (C))

typedef Gi2                Gindex;
#define gindexERROR        Gi2MIN
#define GindexMAX          Gi2MAX
#define gindexIsGood(I,C)  (0 <= (I) && (I) < (C))

typedef Gn4                GhashN;
#define GhashNMAX          Gn4MAX

typedef Gn2                GheapN;
#define GheapNMAX          Gn2MAX

typedef Gi2                Goffset;
#define GoffsetMAX         Gi2MAX
#define GoffsetMIN         Gi2MIN

typedef Gi2                Gsize;
#define GsizeMAX           Gi2MAX
#define gsizeIsGood(S)     (0 <= (S))

#else

typedef Gn4                Gid;
#define gidIsEqual(A,B)    ((A) == (B))
#define gidIsGood(I)       (0 < (I))
#define gidIsUndefined(ID) ((ID) == Gn4MAX)
#define gidGetN(ID)        ((Gn4) ID)
#define gidGetFromN(VALUE) ((Gid) VALUE)
#if grlSWAP_NEEDED == 1
#define gidGetC(ID, CHAR4)                \
   (CHAR4[3] = (Char) (((ID) & 0xff000000) >> 24), \
    CHAR4[2] = (Char) (((ID) & 0x00ff0000) >> 16), \
    CHAR4[1] = (Char) (((ID) & 0x0000ff00) >>  8), \
    CHAR4[0] = (Char) (((ID) & 0x000000ff)))
#define gidGetFromC(CHAR4)                \
   ((CHAR4[3] << 24) |                    \
    (CHAR4[2] << 16) |                    \
    (CHAR4[1] <<  8) |                    \
    (CHAR4[0]))
#else
#define gidGetC(ID, CHAR4)                \
   (CHAR4[0] = (Char) (((ID) & 0xff000000) >> 24), \
    CHAR4[1] = (Char) (((ID) & 0x00ff0000) >> 16), \
    CHAR4[2] = (Char) (((ID) & 0x0000ff00) >>  8), \
    CHAR4[3] = (Char) (((ID) & 0x000000ff)))
#define gidGetFromC(VALUE)                \
   ((CHAR4[0] << 24) |                    \
    (CHAR4[1] << 16) |                    \
    (CHAR4[2] <<  8) |                    \
    (CHAR4[3]))
#endif

typedef Gi4                Gcount;
#define GcountMAX          Gi4MAX
#define gcountIsGood(C)    (0 <= (C))

typedef Gi4                Gindex;
#define gindexERROR        Gi4MIN
#define GindexMAX          Gi4MAX
#define gindexIsGood(I,C)  (0 <= (I) && (I) < (C))

typedef Gn4                GhashN;
#define GhashNMAX          Gn4MAX

typedef Gn4                GheapN;
#define GheapNMAX          Gn4MAX

typedef Gi4                Goffset;
#define GoffsetMAX         Gi4MAX
#define GoffsetMIN         Gi4MIN

typedef Gi4                Gsize;
#define GsizeMAX           Gi4MAX
#define gsizeIsGood(S)     (0 <= (S))

#endif


#if defined(grl64)
typedef Gi4                Gih;
typedef Gn4                Gnh;
typedef Gr8                Grp;
#define GnpMAX             UINTPTR_MAX
#define GipMAX             INTPTR_MAX
#else
typedef Gi2                Gih;
typedef Gn2                Gnh;
typedef Gr4                Grp;
#define GnpMAX             UINTPTR_MAX
#define GipMAX             INTPTR_MAX
#endif

#define GiBIT_COUNT        64

#define GnMAX              Gn8MAX
#define GiMAX              Gi8MAX
#define GrMAX              Gr8MAX
#define GrMIN              Gr8MIN

#define Gi1MAX             INT8_MAX
#define Gi1MIN             INT8_MIN
#define Gi2MAX             INT16_MAX
#define Gi2MIN             INT16_MIN
#define Gi4MAX             INT32_MAX
#define Gi4MIN             INT32_MIN
#define Gi8MAX             INT64_MAX
#define Gi8MIN             INT64_MIN

#define Gn1MAX             UINT8_MAX
#define Gn2MAX             UINT16_MAX
#define Gn4MAX             UINT32_MAX
#define Gn8MAX             UINT64_MAX

#define Gr4MAX             FLT_MAX
#define Gr4MIN             FLT_MIN
#define Gr8MAX             DBL_MAX
#define Gr8MIN             DBL_MIN
/*lint -restore */

// Simple hash function for pointers. This assumes pointers are byte alinged to the
// 4 bytes.  This is why we are dividing by 4 to remove the multiple of 4 nature
// of a pointer.
#define gpHash(P) ((GhashN) ((((Gnp) P) / 4) % GhashNMAX))

typedef Gcompare   (*GrlCompareFunc)(        Gp const * const valueA, Gp const * const valueB);
typedef void       (*GrlDestroyFunc)(        Gp       * const value);
typedef void       (*GrlForEachFunc)(        Gp       * const value);
typedef void       (*GrlForEachKeyFunc)(     Gkey const * const key,    Gp       * const value);
typedef Gp        *(*GrlForEachProcessFunc)( Gp       * const value);
typedef void       (*GrlForEachAltFunc)(     Gp       * const value, GrlForEachFunc func);
typedef Gp const  *(*GrlGetFunc)(            Gp const * const mem, Gi4 const index);
typedef GhashN     (*GrlHashFunc)(           Gp const * const value);
typedef void       (*GrlSwapFunc)(           Gp       * const mem, Gi4 const indexA, Gi4 const indexB);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
