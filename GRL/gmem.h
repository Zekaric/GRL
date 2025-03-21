/**************************************************************************************************
file:         Gmem
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
Data structure for a memory handling.

Not thread safe functions:  Critical sections left to the user.
   gmemClear()
   gmemCopy()
   gmemGetAt()
   gmemGetCount()
   gmemGetSize()
   gmemIsStarted()
   gmemStart()
   gmemStop()

Thread safe functions:
   gmemClocType()
   gmemClocTypeArray()
   gmemDloc()
   gmemSet()

These functions lock because they play around with a memory pool behind the
scenes and this pool needs to be thread safe.  Normal malloc and free is
also thread safe and so is locking as well.  With our pooling though I'm
hoping that the added expense of locking will still be less than calling
malloc and free directly because malloc and free often make a kernel call which
can be very slow.

gmemCloc() has a type string included as one of the parameters.  This is so
that when you go to debug and are looking at a buffer you may have some idea
what is contained in that buffer by following the string pointer.
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) 2000, Robbert de Groot
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**************************************************************************************************/

#if !defined(Gmem_HEADER)
#define      Gmem_HEADER

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
const:
**************************************************************************************************/
// For data compression functions (zlib and lz4 wrappers)
typedef enum
{
   gmemCompressLevelLOW_FASTEST,
   gmemCompressLevelLOW_FASTER,
   gmemCompressLevelLOW_FAST,
   gmemCompressLevelLOW_MAX,
   gmemCompressLevelDEFAULT,
   gmemCompressLevelHIGH_MIN,
   gmemCompressLevelHIGH_DEFAULT,
   gmemCompressLevelHIGH_OPTIMUM,
   gmemCompressLevelHIGH_MAX
} GmemCompressLevel;

/**************************************************************************************************
prototype:
**************************************************************************************************/
//lint -save -e960 -e961 -e9026 -e9022 -e9024
// Raw mem functions
// Not leak tracked.
// I prefer using calloc even if it might be slower than malloc as it zeroes
// the memory.  The overhead so far has not caused me grief.
#define memoryCloc(            BYTECOUNT)                                      calloc((size_t) 1, (size_t) (BYTECOUNT))
#define memoryClocType(        TYPE)                                  (TYPE *) memoryCloc(gsizeof(TYPE))
#define memoryClocTypeArray(   TYPE, COUNT)                           (TYPE *) memoryCloc(gsizeof(TYPE) * (COUNT))
#define memoryDloc(            P)                                              free((Gp *) (P))

// Gmem functions.
// Leak tracked.
// Zeroed memory on creation.
// Type string point included in the allocated memory.

// Clear* functions.
// Type  - provide a type to define the size of the element(s) to clear.
// Array - indicates we are clearing a buffer of N types.
// At    - indicates we are dealing with an array of types adn we are clearing some location inside.
#define gmemClear(               P, BYTECOUNT)                                   gmemClearAt(   (P),     (BYTECOUNT),               0)
#define gmemClearType(           P, TYPE)                                        gmemClearAt(   (P),     gsizeof(TYPE),             0)
#define gmemClearTypeAt(         P, TYPE, INDEX)                                 gmemClearAt(   (P),     gsizeof(TYPE),             gsizeof(TYPE) * (INDEX))
#define gmemClearTypeArray(      P, TYPE, COUNT)                                 gmemClearAt(   (P),     gsizeof(TYPE) * (COUNT),   0)
#define gmemClearTypeArrayAt(    P, TYPE, COUNT, INDEX)                          gmemClearAt(   (P),     gsizeof(TYPE) * (COUNT),   gsizeof(TYPE) * (INDEX))

// Copying data from withing the same array/buffer of type.
#define gmemCopyTypeArray(       P, TYPE, COUNT, INDEX_SRC,    INDEX_DST)        gmemCopy(      (P),     gsizeof(TYPE) * (COUNT),   gsizeof(TYPE) * (INDEX_SRC),  gsizeof(TYPE) * (INDEX_DST))

// Copying data from one array over to some other array of a given type.
#define gmemCopyOver(            P, BYTECOUNT,            PSRC)             gmemCopyOverAt((Gp *) (P),  (BYTECOUNT),             (Gi) 0,                    (Gp *) (PSRC), 0)
#define gmemCopyOverType(        P, TYPE,                 PSRC)             gmemCopyOverAt((Gp *) (P),  gsizeof(TYPE),           (Gi) 0,                    (Gp *) (PSRC), 0)
#define gmemCopyOverTypeArray(   P, TYPE, COUNT,          PSRC)             gmemCopyOverAt((Gp *) (P),  gsizeof(TYPE) * (COUNT), (Gi) 0,                    (Gp *) (PSRC), 0)
#define gmemCopyOverTypeArrayAt( P, TYPE, COUNT, INDEX_P, PSRC, INDEX_SRC)  gmemCopyOverAt((Gp *) (P),  gsizeof(TYPE) * (COUNT), gsizeof(TYPE) * (INDEX_P), (Gp *) (PSRC), gsizeof(TYPE) * (INDEX_SRC))

// Create a dynamic memory buffer on the heap.
// Type  - provide a type to define the size of the element(s) to create.
// Array - indicates we are creating a buffer of N types.
#define gmemCloc(              TYPE_CHAR,  BYTECOUNT)                            gleakCloc((Gp *) gmemCloc_((Char *) (TYPE_CHAR),    (BYTECOUNT)),                   (BYTECOUNT))
#define gmemClocType(          TYPE)                                    (TYPE *) gleakCloc((Gp *) gmemCloc_((Char *) #TYPE,          gsizeof(TYPE)),           gsizeof(TYPE))
#define gmemClocTypeArray(     TYPE,       COUNT)                       (TYPE *) gleakCloc((Gp *) gmemCloc_((Char *) #TYPE " ARRAY", gsizeof(TYPE) * (COUNT)), gsizeof(TYPE) * (COUNT))

// Low level memory comparison.
#define gmemIsEqual(             PA, PB, COUNT)                                  (memcmp((PA), (PB), (size_t) (COUNT))  == 0)
#define gmemIsEqualType(         PA, PB, TYPE)                                   (memcmp((PA), (PB), sizeof(TYPE))      == 0)

// Setting a buffer to a specific byte value.
#define gmemSet(                 P,    BYTECOUNT, BYTEVALUE)                     memset((P), (BYTEVALUE), (size_t) (BYTECOUNT))
//lint -restore

// Actual functions that couldn't be made into macroes.
grlAPI void  gmemClearAt(     Gp         * const p, Gcount const byteCount, Gindex const byteIndex);
grlAPI Gb    gmemCopy(        Gp         * const p, Gcount const byteCount, Gindex const byteIndex,                        Gindex const byteIndexSrc);
grlAPI Gb    gmemCopyOverAt(  Gp         * const p, Gcount const byteCount, Gindex const byteIndex, Gp const * const pSrc, Gindex const byteIndexSrc);
grlAPI Gp   *gmemCloc_(       Char const * const type, Gcount const byteCount);

grlAPI void  gmemDloc(        Gp        * const p);

grlAPI void  gmemFlushPools(  void);

grlAPI void  gmemSetDefaced(  Gp        * const p,    Gcount const byteCount);
// gmemStart and Stop are called by grlStart and Stop.
       Gb    gmemStart(       void);
       void  gmemStop(        void);

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
