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

/******************************************************************************
type:
******************************************************************************/


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
