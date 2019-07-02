/******************************************************************************
file:       g_List
author:     Robbert de Groot
copyright:  2002-2011, Robbert de Groot

description:
Base for double linked list.
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

#if !defined(G_LISTH)
#define      G_LISTH

/******************************************************************************
type:
******************************************************************************/
typedef struct G_ListItem G_ListItem;
struct G_ListItem
{
   G_ListItem        *next,
                     *prev;
};

typedef struct G_List G_List;
struct G_List
{
   GCONTAINER_VAR

   GrlCompareFunc     compareFunc;
   Gb                 isSorted;
   G_ListItem        *head,
                     *tail;
};

/******************************************************************************
prototype:
******************************************************************************/
//lint -save -e960 -e961 -e9023 -e9024 -e9026
#define g_ListCreate(             TYPE, TYPE_SUB, OPTIONAL_COMPARE_FUNC) ((G_List *) gleakCreate((Gp *) g_ListCreate_(             gsizeof(TYPE_SUB), #TYPE, #TYPE_SUB, (OPTIONAL_COMPARE_FUNC)), gsizeof(G_List)))
#define g_ListCreateContent(LIST, TYPE, TYPE_SUB, OPTIONAL_COMPARE_FUNC)                                g_ListCreateContent_(LIST, gsizeof(TYPE_SUB), #TYPE, #TYPE_SUB, (OPTIONAL_COMPARE_FUNC))
//lint -restore

grlAPI G_ListItem *g_ListAdd(             G_List       * const list, Gp const * const value);
grlAPI G_ListItem *g_ListAddBegin(        G_List       * const list, Gp const * const value);
grlAPI G_ListItem *g_ListAddEnd(          G_List       * const list, Gp const * const value);

grlAPI G_List     *g_ListCreate_(                                    Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GrlCompareFunc const compareFunc);
grlAPI Gb          g_ListCreateContent_(  G_List       * const list, Gsize const typeSize, Char const * const typeName, Char const * const typeNameSub, GrlCompareFunc const compareFunc);

grlAPI void        g_ListDestroy(         G_List       * const list);
grlAPI void        g_ListDestroyContent(  G_List       * const list);

grlAPI Gb          g_ListErase(           G_List       * const list, Gp const * const value);
grlAPI Gb          g_ListEraseBegin(      G_List       * const list);
grlAPI Gb          g_ListEraseEnd(        G_List       * const list);

grlAPI G_ListItem *g_ListFind(            G_List const * const list, Gp const * const value);
grlAPI void        g_ListFlush(           G_List       * const list);
grlAPI Gb          g_ListForEach(         G_List const * const list, GrlForEachFunc const func);

grlAPI G_ListItem *g_ListGetBegin(        G_List const * const list);
grlAPI Gcount      g_ListGetCount(        G_List const * const list);
grlAPI G_ListItem *g_ListGetEnd(          G_List const * const list);

// G_ListItem functions
grlAPI G_ListItem *g_ListItemAdd(         G_List       * const list, G_ListItem * const litem, Gp const * const value);

grlAPI G_ListItem *g_ListItemErase(       G_List       * const list, G_ListItem * const litem);

grlAPI Gp         *g_ListItemGet(         G_ListItem const * const litem);
grlAPI G_ListItem *g_ListItemGetNext(     G_ListItem const * const litem);
grlAPI G_ListItem *g_ListItemGetPrev(     G_ListItem const * const litem);

grlAPI void        g_ListItemUpdate(      G_List       * const list, G_ListItem * const litem, Gp const * const value);

// Locally called for any g_List* routines an not to be used elsewhere.
       void        g_ListAddBegin_Add(    G_List       * const list, G_ListItem * const litem);
       void        g_ListAddEnd_Add(      G_List       * const list, G_ListItem * const litem);
       
       void        g_ListItemAdd_Add(     G_List       * const list, G_ListItem * const litem, G_ListItem * const nitem);
       G_ListItem *g_ListItem_Create(     G_List const * const list);

#endif
