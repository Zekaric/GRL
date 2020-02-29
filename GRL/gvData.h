/******************************************************************************
file:       gvDataData
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
A data type that holds all types of data.  
******************************************************************************/

/******************************************************************************
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
******************************************************************************/

#if !defined(GVDATAH)
#define      GVDATAH

/******************************************************************************
const:
******************************************************************************/
#define gvDataTYPE_I "GvData:I"
#define gvDataTYPE_N "GvData:N"
#define gvDataTYPE_P "GvData:P"
#define gvDataTYPE_R "GvData:R"
#define gvDataTYPE_V "GvData"

// type defined in gconst.h

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9026
grlAPI Gcompare    gpCompare(           Gp     const * const valueA, Gp const * const valueB);

// gvData is a simple light data holder.  Use carfully.
grlAPI Gcompare    gvDataCompareI(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareN(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareP(      GvData const * const valueA, GvData const * const valueB);
grlAPI Gcompare    gvDataCompareR(      GvData const * const valueA, GvData const * const valueB);

grlAPI GvData     *gvDataCreate(        void);
grlAPI Gb          gvDataCreateContent( GvData       * const v);

grlAPI void        gvDataDestroy(       GvData       * const v);
grlAPI void        gvDataDestroyContent(GvData       * const v);

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

//lint -restore

/******************************************************************************
GvData containers.
******************************************************************************/

#endif
