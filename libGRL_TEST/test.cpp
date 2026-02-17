#include "pch.h"
#include "grl.h"
#include "assert.h"

static bool _Gv1ArrayCompare( Gv1Array * const a, const char * const str);
static void _Gv1ForEach(      Gp * const value);
static void _Gv1ForEachDown(  Gp * const value);
static bool _GsCompare(       Gs * const a, const char * const str);
static void _GsForEach(       Gp * const value);
static void _GsForEachDown(   Gp * const value);

TEST(libGRL, LibraryInitialization)
{
  EXPECT_TRUE(grlStart());

  gleakReport();

  grlStop();
}

TEST(libGRL, Gv1Array)
{
   EXPECT_TRUE(grlStart());

   Gv1Array *a = nullptr;

   a = gv1ArrayCloc("Gv1Array", nullptr, gbTRUE);
   EXPECT_TRUE(a                   != nullptr);
   EXPECT_TRUE(gv1ArrayGetCount(a) == 0);

   // Because we did not provide a compare function, this call should fail.
   EXPECT_TRUE(!gv1ArrayAdd(a, gv1FromChar('a')));

   // Add some elements to the array.
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('d')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('e')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('f')));
   EXPECT_TRUE(gv1ArrayGetCount(a) == 3);
   EXPECT_TRUE(_Gv1ArrayCompare(a, "def"));

   EXPECT_TRUE(gv1ArrayAddBegin(a, gv1FromChar('c')));
   EXPECT_TRUE(gv1ArrayAddBegin(a, gv1FromChar('a')));
   EXPECT_TRUE(gv1ArrayGetCount(a) == 5);
   EXPECT_TRUE(_Gv1ArrayCompare(a, "acdef"));

   EXPECT_TRUE(gv1ArrayAddAt(a, 0, gv1FromChar('_')));
   EXPECT_TRUE(gv1ArrayAddAt(a, 2, gv1FromChar('b')));
   EXPECT_TRUE(gv1ArrayAddAt(a, 7, gv1FromChar('g')));
   EXPECT_TRUE(gv1ArrayGetCount(a) == 8);
   EXPECT_TRUE(_Gv1ArrayCompare(a, "_abcdefg"));

   EXPECT_TRUE(gv1ArrayClear(a, 2, 3));
   EXPECT_TRUE(gv1ArrayGetAt(a, 2).i == 'b');
   EXPECT_TRUE(gv1ArrayGetAt(a, 3).i == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 4).i == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 5).i == 'e');

   EXPECT_TRUE(gv1ArrayCopy(a, 2, 5, 3));
   EXPECT_TRUE(gv1ArrayGetAt(a, 2).i == 'b');
   EXPECT_TRUE(gv1ArrayGetAt(a, 3).i == 'e');
   EXPECT_TRUE(gv1ArrayGetAt(a, 4).i == 'f');
   EXPECT_TRUE(gv1ArrayGetAt(a, 5).i == 'e');

   // Should be adding 0s between g and z.
   EXPECT_TRUE(gv1ArrayAddAt(a, 20, gv1FromChar('z')));
   EXPECT_TRUE(gv1ArrayGetCount(a) == 21);
   EXPECT_TRUE(gv1ArrayGetAt(a, 0).i  == '_');
   EXPECT_TRUE(gv1ArrayGetAt(a, 1).i  == 'a');
   EXPECT_TRUE(gv1ArrayGetAt(a, 7).i  == 'g');
   EXPECT_TRUE(gv1ArrayGetAt(a, 8).i  == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 19).i == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 20).i == 'z');

   EXPECT_TRUE(gv1ArrayEraseAt(a, 10, 8));
   EXPECT_TRUE(gv1ArrayGetAt(a, 7).i  == 'g');
   EXPECT_TRUE(gv1ArrayGetAt(a, 8).i  == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 9).i  == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 10).i == 'z');

   EXPECT_TRUE(!gv1ArrayErase(a, gv1FromChar('f')));

   EXPECT_TRUE(gv1ArrayEraseBegin(a, 2));
   EXPECT_TRUE(gv1ArrayGetBegin(a).i == 'b');
   EXPECT_TRUE(gv1ArrayEraseEnd(a, 2));
   EXPECT_TRUE(gv1ArrayGetCount(a) == 8);
   EXPECT_TRUE(gv1ArrayGetEnd(a).i == 0);

   EXPECT_TRUE(gv1ArrayFind(a, gv1FromChar('g')) == GindexERROR);

   gv1ArrayFlush(a);
   EXPECT_TRUE(gv1ArrayGetCount(a) == 0);

   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('a')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('b')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('c')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('d')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('e')));
   EXPECT_TRUE(gv1ArrayAddEnd(a, gv1FromChar('f')));

   EXPECT_TRUE(gv1ArrayForEach(a, _Gv1ForEach));
   EXPECT_TRUE(gv1ArrayForEachDown(a, _Gv1ForEachDown));

   EXPECT_TRUE(gv1ArraySetCount(a, 12));
   EXPECT_TRUE(gv1ArraySwap(a, 2, 10));
   EXPECT_TRUE(gv1ArrayGetAt(a, 2).i  == 0);
   EXPECT_TRUE(gv1ArrayGetAt(a, 10).i == 'c');

   EXPECT_TRUE(gv1ArrayUpdateAt(a, 2, gv1FromChar('z')));
   EXPECT_TRUE(gv1ArrayGetAt(a, 2).i  == 'z');

   gv1ArrayDloc(a);

   grlStop();
}

TEST(libGRL, Gtemp)
{
   EXPECT_TRUE(grlStart());

   GtempScope  *tempScope;

   tempScope = gtempEnter();
   EXPECT_TRUE(tempScope != nullptr);

   gtemp(  tempScope, gmemCloc("DATA", 4), gmemDloc);
   gtempGs(tempScope, gsClocFromA("STR DATA"));

   gtempExit(tempScope);

   grlStop();
}
TEST(libGRL, Gs)
{
   EXPECT_TRUE(grlStart());

   Gs *a = nullptr;
   Gs *b = nullptr;

   a = gsCloc();
   EXPECT_TRUE(a             != nullptr);
   EXPECT_TRUE(gsGetCount(a) == 0);

   // Add some elements to the array.
   EXPECT_TRUE(gsAddEnd(a, 'd'));
   EXPECT_TRUE(gsAddEnd(a, 'e'));
   EXPECT_TRUE(gsAddEnd(a, 'f'));
   EXPECT_TRUE(gsGetCount(a) == 3);
   EXPECT_TRUE(_GsCompare(a, "def"));

   EXPECT_TRUE(gsAddBegin(a, 'c'));
   EXPECT_TRUE(gsAddBegin(a, 'a'));
   EXPECT_TRUE(gsGetCount(a) == 5);
   EXPECT_TRUE(_GsCompare(a, "acdef"));

   EXPECT_TRUE(gsAddAt(a, 0, '_'));
   EXPECT_TRUE(gsAddAt(a, 2, 'b'));
   EXPECT_TRUE(gsAddAt(a, 7, 'g'));
   EXPECT_TRUE(gsGetCount(a) == 8);
   EXPECT_TRUE(_GsCompare(a, "_abcdefg"));

   EXPECT_TRUE(gsCopy(a, 2, 5, 3));
   EXPECT_TRUE(gsGetAt(a, 2) == 'b');
   EXPECT_TRUE(gsGetAt(a, 3) == 'e');
   EXPECT_TRUE(gsGetAt(a, 4) == 'f');
   EXPECT_TRUE(gsGetAt(a, 5) == 'e');

   // Should be adding 0s between g and z.
   EXPECT_TRUE(gsAddAt(a, 20, 'z'));
   EXPECT_TRUE(gsGetCount(a) == 21);
   EXPECT_TRUE(gsGetAt(a, 0)  == '_');
   EXPECT_TRUE(gsGetAt(a, 1)  == 'a');
   EXPECT_TRUE(gsGetAt(a, 7)  == 'g');
   EXPECT_TRUE(gsGetAt(a, 8)  == 0);
   EXPECT_TRUE(gsGetAt(a, 19) == 0);
   EXPECT_TRUE(gsGetAt(a, 20) == 'z');

   EXPECT_TRUE(gsEraseAt(a, 10, 8));
   EXPECT_TRUE(gsGetAt(a, 7)  == 'g');
   EXPECT_TRUE(gsGetAt(a, 8)  == 0);
   EXPECT_TRUE(gsGetAt(a, 9)  == 0);
   EXPECT_TRUE(gsGetAt(a, 10) == 'z');

   EXPECT_TRUE(gsEraseBegin(a, 2));
   EXPECT_TRUE(gsGetBegin(a) == 'b');
   EXPECT_TRUE(gsEraseEnd(a, 2));
   EXPECT_TRUE(gsGetCount(a) == 8);
   EXPECT_TRUE(gsGetEnd(a) == 0);

   gsFlush(a);
   EXPECT_TRUE(gsGetCount(a) == 0);

   EXPECT_TRUE(gsAddEnd(a, 'a'));
   EXPECT_TRUE(gsAddEnd(a, 'b'));
   EXPECT_TRUE(gsAddEnd(a, 'c'));
   EXPECT_TRUE(gsAddEnd(a, 'd'));
   EXPECT_TRUE(gsAddEnd(a, 'e'));
   EXPECT_TRUE(gsAddEnd(a, 'f'));

   EXPECT_TRUE(gsForEach(    a, _GsForEach));
   EXPECT_TRUE(gsForEachDown(a, _GsForEachDown));

   EXPECT_TRUE(gsSetCount(a, 12));
   EXPECT_TRUE(gsSwap(a, 2, 10));
   EXPECT_TRUE(gsGetAt(a, 2)  == 0);
   EXPECT_TRUE(gsGetAt(a, 10) == 'c');

   EXPECT_TRUE(gsUpdateAt(a, 2, 'z'));
   EXPECT_TRUE(gsGetAt(a, 2)  == 'z');

   gsDloc(a);

   b = gsClocFromA("test");
   EXPECT_TRUE(_GsCompare(b, "test"));

   a = gsClocFrom(b);
   EXPECT_TRUE(_GsCompare(a, "test"));

   gsAppend(a, b);
   EXPECT_TRUE(_GsCompare(a, "testtest"));

   gsAppendA(a, "TEST");
   EXPECT_TRUE(_GsCompare(a, "testtestTEST"));

   gsAppendLetter(a, '!');
   EXPECT_TRUE(_GsCompare(a, "testtestTEST!"));

   gsAppendI(a, -123);
   EXPECT_TRUE(_GsCompare(a, "testtestTEST!-123"));

   gsAppendSub(a, b, 1, 3);
   EXPECT_TRUE(_GsCompare(a, "testtestTEST!-123es"));

   gsAppendN(a, 456);
   EXPECT_TRUE(_GsCompare(a, "testtestTEST!-123es456"));

   gsAppendR(a, -3.1415);
   EXPECT_TRUE(_GsCompare(a, "testtestTEST!-123es456-3.1415"));

   gsDloc(b);
   gsFlush(a);

   gsAppendFormatted(
      a,
      gsParamTypeA,      "This is a test %P1% and %P11% %P1% %% %PI% %PN% %PR%.",
      gsParamTypeA,      "%P1%",              gsParamTypeA,      "GRL!",
      gsParamTypeA,      "%P11%",             gsParamTypeA,      "DUDE!",
      gsParamTypeA,      "%PI%",              gsParamTypeI,      (Gi) -123,
      gsParamTypeA,      "%PN%",              gsParamTypeN,      (Gn) 4567,
      gsParamTypeA,      "%PR%",              gsParamTypeR,      (Gr) GrPI,
      gsParamTypeS_DLOC, gsClocFromA("%PS%"), gsParamTypeS_DLOC, gsClocFromA("DOESN'T EXIST"),
      gsParamTypeNONE);
   EXPECT_TRUE(_GsCompare(a, "This is a test GRL! and DUDE! GRL! %% -123 4567 3.14159265358979."));

   gsDloc(a);

   grlStop();
}

// Compare the contents of the Gv1Array to the given string.
static bool _Gv1ArrayCompare(Gv1Array * const a, const char * const str)
{
   Gindex     index;
   Gv1 const *buffer;

   if (gv1ArrayGetCount(a) != (Gcount) strlen(str))
   {
      return false;
   }

   buffer = gv1ArrayGet(a);
   forCount (index, gv1ArrayGetCount(a))
   {
      if (buffer[index].i != str[index])
      {
         return false;
      }
   }

   return true;
}

static void _Gv1ForEach(Gp * const value)
{
   static Gindex index = 0;
   Char const   *array = (Char const *) "abcdef";
   Gv1          *v     = (Gv1 *) value;

   assert(v->i == array[index++]);
}

static void _Gv1ForEachDown(Gp * const value)
{
   static Gindex index = 0;
   Char const   *array = (Char const *) "fedcba";
   Gv1          *v     = (Gv1 *) value;

   assert(v->i == array[index++]);
}

// Compare the contents of the Gv1Array to the given string.
static bool _GsCompare(Gs * const a, char const * const str)
{
   Gindex     index;
   Gchar const *buffer;

   if (gsGetCount(a) != (Gcount) strlen(str))
   {
      return false;
   }

   buffer = gsGet(a);
   forCount (index, gsGetCount(a))
   {
      if (buffer[index] != (Gchar) str[index])
      {
         return false;
      }
   }

   return true;
}

static void _GsForEach(Gp * const value)
{
   static Gindex index = 0;
   Char const   *array = (Char const *) "abcdef";
   Gchar        *v     = (Gchar      *) value;

   assert(*v == (Gchar) array[index++]);
}

static void _GsForEachDown(Gp * const value)
{
   static Gindex index = 0;
   Char const   *array = (Char const *) "fedcba";
   Gchar        *v     = (Gchar      *) value;

   assert(*v == (Gchar) array[index++]);
}
