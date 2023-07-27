#include "pch.h"

/******************************************************************************
prototype:
******************************************************************************/
static void _ForEachArray( Gv  * const value);
static void _ForEachGc2(Gc2 * const value);

/******************************************************************************
test: libraryStart
******************************************************************************/
TEST(GRL, LibraryStart)
{
  EXPECT_TRUE(grlStart());
  
  grlStop();
}

/******************************************************************************
test: MemRawRoutines
******************************************************************************/
TEST(GRL, MemRawRoutines)
{
   Gn2 *a;

   EXPECT_TRUE(grlStart());

   // test create type.
   a = memCreateType(Gn2);
   EXPECT_TRUE(a != NULL);
   memDestroy(a);

   // test create size.
   a = (Gn2 *) memCreate(20);
   EXPECT_TRUE(a != NULL);
   memDestroy(a);

   grlStop();
}

/******************************************************************************
test: MemLeakControlledRoutines
******************************************************************************/
TEST(GRL, MemLeakControlledRoutines)
{
   Gi   index;
   Gn2 *a,
       *b;

   EXPECT_TRUE(grlStart());

   // creates ///////////////////////////////////////
   // Test the simple create.
   a = (Gn2 *) gmemCreate("Bingo", 20);
   EXPECT_TRUE(a != NULL);
   gmemDestroy(a);

   // Test the simple 1 count type create.
   // a leaks.  OK!
   a = gmemCreateType(Gn2);
   EXPECT_TRUE(a != NULL);

   // Test the 20 count type create.
   a = gmemCreateTypeArray(Gn2, 20);
   EXPECT_TRUE(a != NULL);
   gmemDestroy(a);

   // a leaks.  OK!
   a = gmemCreateTypeArray(Gn2, 20);
   EXPECT_TRUE(a != NULL);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   // clears ////////////////////////////////////////
   // test the byte clear.
   gmemClear(a, 10);
   EXPECT_FALSE(
      a[0] != 0 ||
      a[1] != 0 ||
      a[2] != 0 ||
      a[3] != 0 ||
      a[4] != 0 ||
      a[5] == 0);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   // test the byte clear.
   gmemClearAt(a, 10, 10);
   EXPECT_FALSE(
      a[4]  == 0 ||
      a[5]  != 0 ||
      a[6]  != 0 ||
      a[7]  != 0 ||
      a[8]  != 0 ||
      a[9]  != 0 ||
      a[10] == 0);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   // test the 1 count type clear.
   gmemClearType(a, Gn2);
   EXPECT_FALSE(
      a[0] != 0 ||
      a[1] == 0);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   // test the 1 count type at clear.
   gmemClearTypeAt(a, Gn2, 18 * sizeof(Gn2));
   EXPECT_FALSE(
      a[17] == 0 ||
      a[18] != 0 ||
      a[19] == 0);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   // Clear the entire array.
   gmemClearTypeArray(a, Gn2, 20);
   EXPECT_FALSE(a[0] != 0 || a[19] != 0);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   gmemClearTypeArrayAt(a, Gn2, 5, 5);
   EXPECT_FALSE(
      a[4]  == 0 || 
      a[5]  != 0 ||
      a[6]  != 0 ||
      a[7]  != 0 ||
      a[8]  != 0 ||
      a[9]  != 0 ||
      a[10] == 0);


   // copies ////////////////////////////////////////
   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   gmemCopy(a, 10, 0, 10);
   EXPECT_FALSE(
      a[4] != 5 ||
      a[5] != 1 ||
      a[6] != 2 ||
      a[7] != 3 ||
      a[8] != 4 ||
      a[9] != 5 ||
      a[10] != 11);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }

   gmemCopyTypeArray(a, Gn2, 5, 0, 5);
   EXPECT_FALSE(
      a[4] != 5 ||
      a[5] != 1 ||
      a[6] != 2 ||
      a[7] != 3 ||
      a[8] != 4 ||
      a[9] != 5 ||
      a[10] != 11);

   // b leaks.  OK!
   b = gmemCreateTypeArray(Gn2, 20);
   EXPECT_FALSE(!b);

   // set the buffer.
   for (index = 0; index < 20; index++)
   {
      a[index] = (Gn2) (index + 1);
   }
   gmemClearTypeArray(b, Gn2, 20);

   gmemCopyOver(a, 10, b);
   EXPECT_FALSE(
      b[0] != 1 ||
      b[1] != 2 ||
      b[2] != 3 ||
      b[3] != 4 ||
      b[4] != 5 ||
      b[5] != 0);

   // reset
   gmemClearTypeArray(b, Gn2, 20);

   gmemCopyOverTypeArray(a, Gn2, 5, b);
   EXPECT_FALSE(
      b[0] != 1 ||
      b[1] != 2 ||
      b[2] != 3 ||
      b[3] != 4 ||
      b[4] != 5 ||
      b[5] != 0);

   gmemClearTypeArray(b, Gn2, 20);

   gmemCopyOverTypeArrayAt(a, Gn2, 5, 0, b, 5);
   EXPECT_FALSE(
      b[4]  != 0 ||
      b[5]  != 1 ||
      b[6]  != 2 ||
      b[7]  != 3 ||
      b[8]  != 4 ||
      b[9]  != 5 ||
      b[10] != 0);

   grlStop();
}

/******************************************************************************
test: Grandom
******************************************************************************/
TEST(GRL, Grandom)
{
   Gn8     init[4] = {0x12345ULL, 0x23456ULL, 0x34567ULL, 0x45678ULL};
   Gcount  length  = 4;
   Grandom r;

   EXPECT_TRUE(grlStart());

   // init the global random number generator.
   grandomCreateContentByArray(NULL, length, init);

   // init the specific random number generator.
   grandomCreateContentByArray(&r,   length, init);

   EXPECT_FALSE(grandomGetN(&r) != 7266447313870364031);
   EXPECT_FALSE(grandomGetN(&r) != 4946485549665804864);
   EXPECT_FALSE(grandomGetN(&r) != 16945909448695747420);
   EXPECT_FALSE(grandomGetN(&r) != 16394063075524226720);
   EXPECT_FALSE(grandomGetN(&r) != 4873882236456199058);

   grlStop();
}

/******************************************************************************
test: GarrayUnsorted
******************************************************************************/
TEST(GRL, GvArrayUnsorted)
{
   Gi       index;
   GvArray *a,
           *adst;
   Gv       vFEEDFACE,
            v42,
            v42neg,
            vNULL,
            vPI,
            vtemp;

   EXPECT_TRUE(grlStart());

   a = gvArrayCreate((GrlCompareFunc) NULL, gbTRUE);
   EXPECT_FALSE(!a);

   gvSetI(&vFEEDFACE, 0xFEEDFACE);
   gvSetI(&v42neg,    -42);
   gvSetI(&v42,        42);
   gvSetP(&vNULL,      NULL);
   gvSetR(&vPI,        gmathPI);

   gvArrayAddAt(   a, 4, &vFEEDFACE);
   gvArrayAddAt(   a, 3, &v42);
   gvArrayAddAt(   a, 2, &v42neg);
   gvArrayAddAt(   a, 1, &vNULL);
   gvArrayAddAt(   a, 0, &vPI);
   gvArrayAddBegin(a,    &vFEEDFACE);
   gvArrayAddBegin(a,    &v42);
   gvArrayAddBegin(a,    &v42neg);
   gvArrayAddBegin(a,    &vNULL);
   gvArrayAddBegin(a,    &vPI);
   gvArrayAddEnd(  a,    &vFEEDFACE);
   gvArrayAddEnd(  a,    &v42);
   gvArrayAddEnd(  a,    &v42neg);
   gvArrayAddEnd(  a,    &vNULL);
   gvArrayAddEnd(  a,    &vPI);

   gvArrayClear(   a, 2, 2);
   gvArrayCopy(    a, 2, 0, 2);

   // adst leaks.  OK!
   adst = gvArrayCreate((GrlCompareFunc) NULL, TRUE);
   gvArrayAddAt(   adst, 4, &vFEEDFACE);
   gvArrayCopyFrom(adst, 0, a, 2, 0);

   gvArrayEraseAt(   a, 1, 3);
   gvArrayEraseBegin(a);
   gvArrayEraseEnd(  a);

   index = gvArrayFind(a, &vFEEDFACE);
   gvArrayForEach(a, (GrlForEachFunc) _ForEachArray);

   vtemp = *gvArrayGetAt(    a, 1);
   vtemp = *gvArrayGetBegin( a);
   index =  gvArrayGetCount( a);
   vtemp = *gvArrayGetEnd(   a);
   index =  gvArrayGetSize(  a);

   gvArraySetCount( a, 15);
   gvArraySwap(     a, 1, 0);

   gvArrayUpdateAt( a, 14, &vFEEDFACE);

   gvArrayFlush(a);

   gvArrayDestroy(a);

   grlStop();
}

/******************************************************************************
test: GarraySorted
******************************************************************************/
TEST(GRL, GvArraySorted)
{
   Gi       index;
   GvArray *a;
   Gv       v;

   EXPECT_TRUE(grlStart());

   a = gvArrayCreate((GrlCompareFunc) gvCompareN, TRUE);
   EXPECT_FALSE(!a);

   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));
   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));
   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));
   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));
   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));
   gvArrayAdd(a, gvSetN(&v, grandomGetN(NULL)));

   gvArrayEraseBegin(a);
   gvArrayEraseEnd(  a);

   index = gvArrayFind(a, gvSetN(&v, 12));
   EXPECT_FALSE(index != -1);

   gvArrayDestroy(a);

   grlStop();
}

/******************************************************************************
test: Gs
******************************************************************************/
TEST(GRL, Gs)
{
   Gs        *s,
              sc;
   Gc2 const *cstr;
   Gc2        c;
   Gi         i;

   EXPECT_TRUE(grlStart());

   s = gsCreate();
   EXPECT_TRUE( s != NULL);
   EXPECT_FALSE(!gsCreateContent(&sc));

   gsSetCount(&sc, 10);
   gsForEach( &sc, (GrlForEachFunc) _ForEachGc2);

   gsAddAt(   s, 5, L'A');
   gsForEach( s, (GrlForEachFunc) _ForEachGc2);

   gsAddBegin(s, L'Z');
   gsAddEnd(  s, L'Z');

   gsClear(   s, 1, 0);
   gsCopy(    s, 1, 5, 0);
   gsCopyFrom(&sc, 0, s, gsGetCount(s), 0); 

   gsUpdateAt(s, 2, L'B');

   gsEraseAt(   s, 1, 6);
   gsEraseBegin(&sc);
   gsEraseEnd(  &sc);

   EXPECT_FALSE(gsFind(s, L'B') == GindexERROR);
   EXPECT_FALSE(gsFind(s, L'S') != GindexERROR);
   gsFlush(&sc);

   cstr =  gsGet(     s);
   c    = *gsGetAt(   s, 2);
   c    = *gsGetBegin(s);
   i    =  gsGetCount(s);
   c    = *gsGetEnd(  s);
   i    =  gsGetSize( s);

   gsSort(s);
   gsSwap(s, 0, 5);

   gsDestroy(s);
   gsDestroyContent(&sc);

   grlStop();
}

/******************************************************************************
test: GsArray
******************************************************************************/
TEST(GRL, GsArray)
{
   GsArray *sa;
   Gs      *s;

   EXPECT_TRUE(grlStart());

   sa = gsArrayCreate((GrlCompareFunc) gsCompare, gbFALSE);

   gsArrayAdd(     sa,    gsCreateRandom());
   gsArrayAddAt(   sa, 5, gsCreateRandom());
   gsArrayAddBegin(sa,    gsCreateRandom());
   gsArrayAddEnd(  sa,    gsCreateRandom());

   s = gsArrayGetAt(   sa, 1);
   s = gsArrayGetBegin(sa);
   s = gsArrayGetEnd(  sa);

   gsArrayForEach(sa, (GrlForEachFunc) gsDestroyFunc);
   gsArrayDestroy(sa);

   grlStop();
}

/******************************************************************************
test: GlistUnsorted
******************************************************************************/
TEST(GRL, GvListUnsorted)
{
   GvList     *list;
   GvListItem *item;
   Gv          vB000B000,
               v42,
               v42neg,
               vPointer,
               vPI,
               v;
   Gi          i;

   EXPECT_TRUE(grlStart());

   gvSetN(&vB000B000, 0xB000B000);
   gvSetN(&v42,       42);
   gvSetI(&v42neg,   -42);
   gvSetP(&vPointer, (Gp *) (Gnp) 0x1);
   gvSetR(&vPI,       gmathPI);

   list = gvListCreate((GrlCompareFunc) NULL);
   EXPECT_TRUE(list != NULL);

   item = gvListAddBegin( list, &vB000B000);
   item = gvListAddBegin( list, &v42neg);
   item = gvListAddBegin( list, &v42);
   item = gvListAddBegin( list, &vPointer);
   item = gvListAddBegin( list, &vPI);
   item = gvListAddEnd(   list, &vB000B000);
   item = gvListAddEnd(   list, &v42neg);
   item = gvListAddEnd(   list, &v42);
   item = gvListAddEnd(   list, &vPointer);
   item = gvListAddEnd(   list, &vPI);

   gvListEraseBegin(list);
   gvListEraseEnd(  list);

   item = gvListFind(list, &vB000B000);
   item = gvListFind(list, &v42neg);
   item = gvListFind(list, &v42);
   item = gvListFind(list, &vPointer);
   item = gvListFind(list, &vPI);
   item = gvListFind(list, gvSetI(&v, 5));

   item = gvListGetBegin(list);
   i    = gvListGetCount(list);
   item = gvListGetEnd(  list);

   gvListFlush(list);

   item = gvListAddBegin(list, &vB000B000);
   item = gvListAddBegin(list, &v42neg);
   item = gvListAddBegin(list, &v42);
   item = gvListAddBegin(list, &vPointer);
   item = gvListAddBegin(list, &vPI);

   gvListDestroy(list);

   grlStop();
}

/******************************************************************************
test: GlistSorted
******************************************************************************/
TEST(GRL, GvlistSorted)
{
   GvList     *list;
   GvListItem *item;
   Gv          v;

   EXPECT_TRUE(grlStart());

   list = gvListCreate((GrlCompareFunc) gvCompareN);
   EXPECT_TRUE(list != NULL);

   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));
   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));
   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));
   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));
   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));
   item = gvListAdd(list, gvSetN(&v, grandomGetN(NULL)));

   item = gvListFind(list, gvSetN(&v, 42));
   EXPECT_FALSE(item != NULL);

   item = gvListFind(list, gvSetN(&v, gvGetN(gvListItemGet(gvListGetEnd(list)))));
   EXPECT_FALSE(item == NULL);

   gvListDestroy(list);

   grlStop();
}

/******************************************************************************
test: GvHash
******************************************************************************/
TEST(GRL, GvHash)
{
   GvHash *hash;
   Gn      n;
   Gv      v,
           v42,
           v42neg,
           vPointer,
           vPI,
          *pv;

   EXPECT_TRUE(grlStart());

   hash = gvHashCreate((GrlCompareFunc) gvCompareN, (GrlHashFunc) gvHash, ghashSize10);
   EXPECT_TRUE(hash != NULL);

   n = grandomGetN(NULL);
   gvHashAdd(hash, gvSetN(&v, n));
   n = grandomGetN(NULL);

   gvHashAdd(hash, gvSetI(&v42neg,   -42));
   gvHashAdd(hash, gvSetN(&v42,       42));
   gvHashAdd(hash, gvSetP(&vPointer, (Gp *) (Gnp) 0x1));
   gvHashAdd(hash, gvSetR(&vPI,      gmathPI));

   EXPECT_FALSE(gvHashErase(hash, gvSetI(&v, -45)));
   EXPECT_TRUE( gvHashErase(hash, gvSetI(&v, -42)));

   pv = gvHashFind(hash, gvSetR(&v, gmathPI));
   EXPECT_FALSE(pv == NULL);
   
   gvHashFlush(hash);
   
   gvHashDestroy(hash);

   grlStop();
}

/******************************************************************************
test: GsHash
******************************************************************************/
TEST(GRL, GsHash)
{
   GsHash *hash;
   Gs     *s1,
          *s2,
          *s3,
          *s4,
          *s5,
          *s5b;

   EXPECT_TRUE(grlStart());

   hash = gsHashCreate((GrlCompareFunc) gsCompare, (GrlHashFunc) gsHash, ghashSize10);
   EXPECT_TRUE(hash != NULL);

   s1  = gsCreateFromA("1");
   s2  = gsCreateFromA("22");
   s3  = gsCreateFromA("333");
   s4  = gsCreateFromA("4444");
   s5  = gsCreateFromA("55555");
   s5b = gsCreateFromA("55555");

   gsHashAdd(hash, s1);
   gsHashAdd(hash, s2);
   gsHashAdd(hash, s3);
   gsHashAdd(hash, s4);
   gsHashAdd(hash, s5);
   EXPECT_FALSE(gsHashAdd(hash, s5b) != gbFALSE);

   EXPECT_FALSE(gsHashFind(hash, s5b) != s5);

   gsHashDestroy(hash);

   grlStop();
}

/******************************************************************************
func: _ForEachArray
******************************************************************************/
static void _ForEachArray(Gv * const value)
{
   gvSetN(value, gvGetN(value) + 1);
}

/******************************************************************************
func: _ForEachArray
******************************************************************************/
static void _ForEachGc2(Gc2 * const value)
{
   if (*value == 0)
   {
      *value = L'A' + grandomGetN(NULL) % 26;
   }
}
