/******************************************************************************
file:       gsUtil
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
Some simple and convenient string file load routines.
******************************************************************************/

#if !defined(GSTRUTILH)
#define      GSTRUTILH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9022 -e9023 -e9024 -e9026
#define gsClocLoad(PATH)                   ((Gs *)        gleakCloc(gsClocLoad_(PATH),                  gsizeof(Gs)))
#define gsClocInput()                      ((Gs *)        gleakCloc(gsClocInput_(),                     gsizeof(Gs)))
#define gsArrayClocLoad(PATH)              ((GsArray *)   gleakCloc(gsArrayClocLoad_(PATH),             gsizeof(GsArray)))
#define gsHashKeyClocLoad(HASHSIZE, PATH)  ((GsHashKey *) gleakCloc(gsHashKeyClocLoad_(HASHSIZE, PATH), gsizeof(GsHashKey)))
//lint -restore

grlAPI Gs         *gsClocLoad_(         Gpath const * const path);
grlAPI Gs         *gsClocInput_(        void);
grlAPI GsArray    *gsArrayClocLoad_(    Gpath const * const path);

grlAPI GsHashKey  *gsHashKeyClocLoad_(  GhashSize const hashSize, Gpath const * const path);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
