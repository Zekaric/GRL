/**************************************************************************************************
file:       gvDataData
author:     Robbert de Groot
copyright:  2002, Robbert de Groot

description:
A data type that holds all types of data.

What's the difference between this and Gv?
Gv is more internal.  This type is intended to be cloc'd all the time.  So you will be dealing with
a pointer to this type always while Gv you will be dealing with it raw.  This type also includes
the type being stored.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2002, Robbert de Groot

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**************************************************************************************************/

#pragma once

/*************************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*************************************************************************************************/

/**************************************************************************************************
const:
**************************************************************************************************/
#define gvDataTYPE_I "GvData:I"
#define gvDataTYPE_N "GvData:N"
#define gvDataTYPE_P "GvData:P"
#define gvDataTYPE_R "GvData:R"
#define gvDataTYPE_V "GvData"

// type defined in gconst.h

/**************************************************************************************************
prototype:
**************************************************************************************************/
#define gvDataCloc()    (GvData *) gleakCloc((Gp *) gcDataCloc_(), gsizeof(GvData))

grlAPI Gcompare    gpCompare(           Gp     const * const valueA, Gp     const * const valueB);

// gvData is a simple light data holder.  Use carfully.
grlAPI Gcompare    gvDataCompareI(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareN(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareP(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareR(      GvData const * const valueA, GvData const * const valueB);

grlAPI GvData     *gvDataCloc_(         void);
grlAPI Gb          gvDataClocContent(   GvData       * const v);

grlAPI void        gvDataDloc(          GvData       * const v);
grlAPI void        gvDataDlocContent(   GvData       * const v);

grlAPI GvData      gvDataFromI(         Gi             const value);
grlAPI GvData      gvDataFromN(         Gn             const value);
grlAPI GvData      gvDataFromP(         Gp           * const value);
grlAPI GvData      gvDataFromR(         Gr             const value);
grlAPI GvData      gvDataFromS(         Gs           * const value);

grlAPI Gi          gvDataGetI(          GvData const * const v);
grlAPI Gn          gvDataGetN(          GvData const * const v);
grlAPI Gp         *gvDataGetP(          GvData const * const v);
grlAPI Gr          gvDataGetR(          GvData const * const v);
grlAPI Gs         *gvDataGetS(          GvData const * const v);

grlAPI GhashN      gvDataHash(          GvData const * const value);
grlAPI GhashN      gvDataHashS(         GvData const * const value);

grlAPI Gb          gvDataSetI(          GvData       * const v, Gi   const value);
grlAPI Gb          gvDataSetN(          GvData       * const v, Gn   const value);
grlAPI Gb          gvDataSetP(          GvData       * const v, Gp * const value);
grlAPI Gb          gvDataSetR(          GvData       * const v, Gr   const value);
grlAPI Gb          gvDataSetS(          GvData       * const v, Gs * const value);

/*************************************************************************************************/
#ifdef __cplusplus
}
#endif
/*************************************************************************************************/
