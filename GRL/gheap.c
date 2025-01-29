/**************************************************************************************************
file:       gheap
author:     Robbert de Groot
copyright:  2002-2009, Robbert de Groot

description:
heap sort routines.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/*******************************************************************************************************
 * FUNC:msHeapify, msHeapBuild, msHeapSort
 *
 * Routines for a heap sort.
 ******************************************************************************************************/
#if 0 // Current not used.
#define Parent(i) ( (i) >> 1)
#endif

//lint -save -e961 -e9026
#define Left(i)   ( (i) << 1)
#define Right(i)  (((i) << 1) + 1)
//lint -restore

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gheapBuild

Build the heap.
**************************************************************************************************/
grlAPI void gheapBuild(Gheap * const data)
{
   Gindex a;

   genter;

   for (a = (data->count >> 1); a > 0; a--)
   {
      gheapHeapify(data, data->count, a);
   }

   greturn;
}

/**************************************************************************************************
func: gheapHeapify

Heapify function.
**************************************************************************************************/
grlAPI void gheapHeapify(Gheap * const data, Gcount const arraySize, Gindex const nodeIndex)
{
   Gindex    lIndex,
             rIndex,
             bigIndex;
   Gp const *nodeP,
            *lP,
            *rP,
            *bigP;

   genter;

   lIndex = Left( nodeIndex);
   rIndex = Right(nodeIndex);

   nodeP = data->getFunc(data->mem, nodeIndex - 1);
   lP    = data->getFunc(data->mem, lIndex    - 1);
   rP    = data->getFunc(data->mem, rIndex    - 1);

   if (lIndex                       <= arraySize &&
       data->compareFunc(nodeP, lP) == gcompareLESS_THAN) //lint !e960 !e9007
   {
      bigIndex = lIndex;
      bigP     = lP;
   }
   else
   {
      bigIndex = nodeIndex;
      bigP     = nodeP;
   }

   if (rIndex                      <= arraySize &&
       data->compareFunc(bigP, rP) == gcompareLESS_THAN) //lint !e960 !e9007
   {
      bigIndex = rIndex;
   }

   if (bigIndex != nodeIndex)
   {
      // Swap first and last.
      data->swapFunc(data->mem, nodeIndex - 1, bigIndex - 1);

      gheapHeapify(data, arraySize, bigIndex);
   }
   greturn;
}

/**************************************************************************************************
func: gheapSetData

Initialize a Gheap structure.
**************************************************************************************************/
grlAPI Gheap gheapSetData(Gcount const count, Gp * const mem, GrlGetFunc const getF,
   GrlSwapFunc const swapF, GrlCompareFunc const compareFunc)
{
   Gheap data;

   genter;

   data.count       = count;
   data.mem         = mem;
   data.getFunc     = getF;
   data.swapFunc    = swapF;
   data.compareFunc = compareFunc;

   greturn data;
}

/**************************************************************************************************
func: gheapSort

Sort the data as a heap.
**************************************************************************************************/
grlAPI Gb gheapSort(Gheap * const data)
{
   Gindex a,
          arraySize;

   genter;

   gheapBuild(data);

   arraySize = data->count;

   for (a = data->count; a > 1; a--)
   {
      // Swap first and last.
      data->swapFunc(data->mem, 0, arraySize - 1);

      arraySize--;

      gheapHeapify(data, arraySize, 1);
   }

   greturn gbTRUE;
}
