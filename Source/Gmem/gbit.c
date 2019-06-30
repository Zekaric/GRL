/******************************************************************************
file:       gbit
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
Simple set and get bit functions in a bit array.
******************************************************************************/

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

/******************************************************************************
define:
******************************************************************************/
#define Gn4SIZE  32

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: gbitGet

Get a chunk of a int as bits.  bit and count must not overflow the data.
******************************************************************************/
grlAPI Gn4 gbitGet(Gn4 const data, Gindex const bit, Gcount const count)
{
   register Gn4 mask;

   genter;

   debugHaltIf((count < 1) || (31 < count), "Bad count");
   debugHaltIf((bit + count) > 32,          "Bad bit");

   // Create the mask.
   mask = (((Gn4) 1) << (count)) - 1;

   greturn \
      (((mask << bit) // Move the mask over to the right place.
        & data)       // Get the bits at that place.
       >> bit)        // Move those bits down.
      & mask;         // Remove all unecessary bits.
}

/***********************************************************************************
func: gbitSet

Set the bits in the data.  bit and count must not overflow the data.
***********************************************************************************/
grlAPI Gn4 gbitSet(Gn4 const data, Gindex const bit, Gcount const count, Gn4 const value)
{
   register Gn4 mask, mask2;

   genter;

   debugHaltIf((count < 1) || (31 < count), "Bad count");
   debugHaltIf((bit + count) > 32,          "Bad bit");

   // This is the mask to black out the bits in data.
   mask  = ((((Gn4) 1) << (count)) - 1) << bit;

   // mask for the bits of the value to put back in.
   mask2 = (value << bit) & mask;

   // Perform the switch.
   greturn \
      ((~mask) & data)     // AND in the original data to blank out the value.
      | mask2;             // OR in the new data.
}

/*******************************************************************************
func: gbitArrayGet

Works on an array of integers flags.  This will not
handle counts of larger than 32.
*******************************************************************************/
grlAPI Gn4 gbitArrayGet(Gn4 const * const data, Gindex const bit, Gcount const count)
{
   register Gn4 A, B, value;

   genter;

   greturnIf(
         !data       ||
         (count < 1) || (31 < count),
      0);

   // bit and count span over two ints.
   if (((bit + count - 1) / Gn4SIZE) > (bit / Gn4SIZE))
   {
      // Get the bits of the following int.
      A = gbitGet(
         data[(bit + count - 1) / Gn4SIZE],
         0,
         (bit % Gn4SIZE) + count - Gn4SIZE);

      B = gbitGet(
         data[bit / Gn4SIZE],
         bit % Gn4SIZE,
         Gn4SIZE - (bit % Gn4SIZE));

      value = B + (A << (Gn4SIZE - (bit % Gn4SIZE)));
   }
   // One int span is simple.
   else
   {
      value = gbitGet(
         data[bit / Gn4SIZE],
         bit % Gn4SIZE,
         count);
   }

   greturn value;
}

/******************************************************************************
func: gbitArrayGetSize
******************************************************************************/
grlAPI Gsize gbitArrayGetSize(Gcount const count)
{
   genter;
   debugHaltIf(count == 0, "Bad Count");
   greturn (count / 32) + ((count % 32) ? 1 : 0);
}

/*******************************************************************************
 * func: gbitArraySet
 *
 * Works on an array of integer (4 byte) flags.
 ******************************************************************************/
grlAPI Gb gbitArraySet(Gn4 * const data, Gindex const bit, Gcount const count, Gn4 const value)
{
   genter;

   greturnIf(
         !data       ||
         (count < 1) || (31 < count),
      gbFALSE);

   if (((bit + count - 1) / Gn4SIZE) > (bit / Gn4SIZE))
   {
      data[(bit + count - 1) / Gn4SIZE] = (Gn4) gbitSet(
         data[(bit + count - 1) / Gn4SIZE],
         0,
         (bit % Gn4SIZE) + count - Gn4SIZE,
         value >> (Gn4SIZE - (bit % Gn4SIZE)));

      data[bit / Gn4SIZE] = (Gn4) gbitSet(
         data[bit / Gn4SIZE],
         bit % Gn4SIZE,
         (Gn4SIZE - (bit % Gn4SIZE)),
         value & ((((Gn4) 0x1) << (Gn4SIZE - (bit % Gn4SIZE))) - 1));
   }
   else
   {
      data[bit / Gn4SIZE] = (Gn4) gbitSet(
         data[bit / Gn4SIZE],
         bit % Gn4SIZE,
         count,
         value);
   }

   greturn gbTRUE;
}
