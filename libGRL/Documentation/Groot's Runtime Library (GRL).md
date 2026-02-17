# libGRL

## Overview

libGRL (Groot's Runtime Library) is a C library that provides cross platform utilities, data 
containers, etc.  It started life when a similar library what I was using at work stoppeb being
developed and supported by the company that created it.  The company being Visix and their library
was called Galaxy.  Galaxy was a great library.  It was better and further along than QT when the
decision was made to used it.  However the company made a poor business decision and felt that it
was no longer viable to continue operations.  Galaxy was sold to a Brazilian company called 
Ambiencia who flat out said they would not take in all the existing Galaxy customers and if the
existing customers wanted to use their 'Galaxy' library they would have to pay a brand new license 
for it.  This rubbed a lot of long term customers the wrong way because Visix basically just 
released a new version of their library before they stopped shop.  Practically everyone who used
Galaxy either moved to something else.  We managed to legally get the source code and continue with
it until we could move to a different ecosystem.  So libGRL was born to be that alternative.  But
my company decided they would go in a totally different direction so libGRL was never used or 
really considered.  But I kept developing it on my own time because I still like C and all the 
features that Galaxy had.  However this is in now way a 1-1 replacement for Galaxy and it never
used any of the Galaxy code.  

Lately though, as 1 developer, doing all the things I'd like to put into libGRL for multiple 
platforms is a bit much so I'm leveraging libSDL v3 to help out with some of the cross platform 
code.

## Memory Managment (Gmem, Gleak, Gtemp)

libGRL wraps the standard C malloc/calloc and free routines.  I have found over the years that 
tired programmers have made unintended mistakes with these routined which causes memory leaks, 
badly sized memory buffers, etc.  So the routines provided are meant to be safer and easier to use.

Also, all the memory routines in libGRL, at least in DEBUG builds, are tracked.  What I mean here 
is that, if you allocated memory and never freed it, then at program exit, a leak report is made
showing where the memory was allocated so that you can have an easier time finding and fixing the
leaks you made.  

There is also a temporary memory tracking that may make some coding simpler so that any temporary
allocations made in a function are freed when the function exists.  Similar to how C++ can auto
clean up object when the program goes out of scope.

## Data Containers

Data containers is a big issue with C.  The standard library does not come with any.  C++ has STL
at least.  So libGRL is attempting to provide a similar set.  At least the most common ones.

### Dynamic Array (Gv\*Array)

A dynamic array/buffer that can grow as needed.  Similar to a C++ std::vector.

### Keyed Dynamic Array (GkvArray)

A dynamic array that holds key/value pairs.  If you keep it sorted, then lookups are log2(n) 
because of binary search.

### Linked List (GvList)

A double linked list.  Similar to C++ std::list.

### Keyed Linked List (GkvList)

A double linked list that holds key/value pairs.  

### Hash Table (GvHash)

A hash table that grows.  The main hash table is an array of linked lists.  So if two items hash 
to the same index, then they are added to the linked list at that hash index.  This is fast.  It 
will only become slow if your hash doesn't distribute the data well or if you didn't side the hash
table big enough so that the linked lists become long.  Depending on your data, this will always be
faster than a linked list for larger data sets and generally outperform trees.

### Keyed Hash Table (GkvHash)

A hash table that grows that holds key/value pairs.

### Semi-balanced Binary Tree (GvTree)

A semi-balanced binary tree.  How it achieves balance is by mixing it with a heap.  Look up Treep
for how this works.  It is not fully balanced but it is improbable that it will become, basically,
a linked list.  So better than a naive binary tree, less overhead than a red-black tree, 123 tree, 
B-tree (balanced tree with n keys per node.).

### Keyed Semi-balanced Binary Tree (GkvTree)

A semi-balanced binary tree that holds key/value pairs.

## Dynamic Strings (Gs)

Dynamic strings that grow and shrink as needed.  Similar to C++ std::string.  These strings are 
always in UTF32.  I know, that is memory wasteful but in general, UTF32 is the easiest to work 
with.  There are conversion functions to make UTF8 and UTF16 buffers.  But these strings are far
better and safer to work with than the C string functions.  Anyone who are using C string functions
now a days should really have a good reason for doing so.  Otherwise, people should be using a 
dynamic string solution of some kind.  Maybe not this one but something.

# Library

## Data Types

### Gcompare

```
typedef enum
{
   gcompareLESS_THAN    = -1,
   gcompareEQUAL        =  0,
   gcompareGREATER_THAN =  1,
   gcompareUNKNOWN      =  2
} Gcompare;
```

Used in return for compare functions.

### Char

Typedefed char.

### CharW

Typedefed wchar_t.

### Gb

A boolean type.

### Gbit

A type for bit fields.

### Gchar[|1|2]

An character type of UTF32, Utf8/ASCII (1 byte), or Utf16/wchar_t (2 bytes).

### Gcount

An integer type that is best size for the platform to be used for count.  Currently 32 bits.

### Gi[|1|2|4|8]

An integer type of largest size, 1 byte, 2 bytes, 4 bytes, or 8 bytes.

### Gindex

An integer type that is best size for the platform to be used for index iterators.  Currently 32 
bits.

### Gn[|1|2|4|8]

An natrual type (unsigned integer) of largest size, 1 byte, 2 bytes, 4 bytes, or 8 bytes.

### Goffset

An integer type that is best size for the platform to be used for offsets.  Currently 32 bits.

### Gr[|4|8]

An real type (float/double) of largest size, 4 bytes (float), or 8 bytes (double).

### Gsize

An integer type that is best size for the platform to be used for sizes.  Currently 32 bits.

### Gs

A dynamic string type of UTF32 characters.  Strings are just like standard C string in that they
are terminated by a null character.  Gs is a thin wrapper around Gv4Array.  The wrapper takes care
of the null termination character.

#### Function (Gv4Array wrapper)

##### gsAdd\*

```
Gb gsAddAt(   Gs * const a, Gindex const index, Gchar const value);
Gb gsAddBegin(Gs * const a,                     Gchar const value);
Gb gsAddEnd(  Gs * const a,                     Gchar const value);
```

*gsAddAt* will add a character at a given index in the string.

*gsAddBegin* will add a character at the beginning of the string.

*gsAddEnd* will add a character at the end of the string.

##### gsCloc, gsClocContent

```
Gs *gsCloc(void)
Gb  gsClocContent(Gs * const a);
```

Create a new string or intialize a new string variable.

##### gsCopy\*

```
Gb gsCopy(    Gs * const a, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
Gb gsCopyFrom(Gs * const aDst, Gindex const indexDst, Gs const * const aSrc, Gcount const count, Gindex const indexSrc);
```

*gsCopy* safely copies one part of the string to another part of the same string.

*gsCopyFrom* copies a subset from one string to another string.

##### gsDloc, gsDlocContent

```
void gsDloc(         Gs * const a);
void gsDlocContent(  Gs * const a);
void gsDlocContainer(Gv const * const v)
```

*gsDloc* deallocates a string.

*gsDlocContent* deallocates a string variable contents.

*gsDlocContainer* deallocates a string from a Gv data container.

##### gsErase\*

```
Gb gsEraseAt(   Gs * const a, Gcount const count, Gindex const index);
Gb gsEraseBegin(Gs * const a, Gcount const count);
Gb gsEraseEnd(  Gs * const a, Gcount const count);
```

*gsEraseAt* erases *count* characters at the given index.

*gsEraseBegin* erases *count* characters from the beginning of the string.

*gsEraseEnd* erases *count* characters from the end of the string.

##### gsGetFlush

```
void gsFlush(Gs * const a);
```

Flushes the string to an empty string.

##### gsFroEach\*

```
Gb gsForEach(    Gs const * const a, GrlForEachFunc const func);
Gb gsForEachDown(Gs const * const a, GrlForEachFunc const func);
```

Iterates over each character in the string calling a given function.  *gsForEachDown* does the 
operation in reverse.

##### gsGet\*

```
Gchar const *gsGet(Gs const * const a);
```

Gets a pointer to the internal UTF32 character buffer.

##### gsGet\*

```
Gchar gsGetAt(   Gs const * const a, Gindex const index);
Gchar gsGetBegin(Gs const * const a);
Gchar gsGetEnd(  Gs const * const a);
```

*gsGetAt* will get a character at a given index in the string.

*gsGetBegin* will get a character at the beginning of the string.

*gsGetEnd* will get a character at the end of the string.

##### gsGetCount

```
Gcount gsGetCount(Gs const * const a);
```

Gets the count of characters in the string (not including the null termination character).

##### gsSetCount

```
Gcount gsSetCount(Gs * const a, Gcount const value);
```

Sets the count of characters in the string.  If the count is larger, then the string grows and 
inserts null characters for the new characters.  If the count is smaller, then the string is
truncated.

##### gsSwap

```
Gb gsSwap(Gs * const a, Gindex const indexA, Gindex const indexB);
```

Swaps the characters at two given indicies.

##### gsUpdateAt

```
Gb gsUpdateAt(Gs * const a, Gindex const index, Gchar const value);
```

Updates a character at a given index to a new value.

#### Function (Utility)

##### gsAppend\*

```
Gs *gsAppend(          Gs * const str, Gs const * const value);
Gs *gsAppendA(         Gs * const str, Char const * const value);
Gs *gsAppendGchar1(    Gs * const str, Gchar1 const * const value);
Gs *gsAppendGchar2(    Gs * const str, Gchar1 const * const value);
Gs *gsAppendI(         Gs * const str, Gi const i);
Gs *gsAppendLetter(    Gs * const str, Gchar const c);
Gs *gsAppendN(         Gs * const str, Gn const n);
Gs *gsAppendR(         Gs * const str, Gr const r);
Gs *gsAppendSub(       Gs * const str, Gs const * const value, Gindex const start, Gindex const end);
Gs *gsAppendParams(    Gs * const str, ...);
```

*gsAppend* will append a gs string to a gs string.

*gsAppendA* will append an ASCII string to a gs string.

*gsAppendGchar1* and *gsAppendGchar2* will append a UTF8 or UTF16/wchar_t string to a gs string.

*gsAppendI* will append an integer value to a gs string.

*gsAppendLetter* will append a single UTF32 character to a gs string.

*gsAppendN* will append a natural value to a gs string.

*gsAppendR* will append a real value to a gs string.

*gsAppendSub* will append a substring from another gs string to a gs string.

*gsAppendParams* will append a variable list of Gs strings to a gs string.

##### gsAppendFormatted

```
Gs *gsAppendFormatted(Gs * const str, GsParamType formatType, ...);
```

This function is a bit like printf but in a way simpler.  

The full call parameters are:

```
gsAppendFormatted(
   Gs * const str, 
   GsParamType formatType, [Format string],
   {GsParamType, [Key], GsParamType, [Value],}*
   gsParamTypeNONE);
```

*str* is the string being appended to.

*formatType* and the value that follows is the format string.  This format string will have encoded
into it variables to be replaced.

The next and subsequent 4 paramters is the key value.  *GsParamType* dictates what the next 
parameter is.  Even the format string has a *GsParamType* field.  So we have a *GsParamType* and 
Key value, followed by a *GsParamType* and Value value.  We can have any number of these key value
pairs.

The list is terminated by a *GsParamType* of *gsParamTypeNONE*.

What happens is that this function will find all instances of a key in the format string and 
replace that key with the associated value.  

Example:
```
result = gsAppendFormatted(
   str,
   gsParamTypeA, "Hello, {name}.  You have {count} new messages.",
   gsParamTypeA, "{name}",  gsParamTypeA, "GRL",
   gsParamTypeA, "{count}", gsParamTypeI, 5,
   gsParamTypeNONE);
```

This will append the string "Hello, GRL.  You have 5 new messages." to the string *str*.

###### GsParamType

```
   gsParamTypeNONE,

   gsParamTypeA      = 0x00000001,
   gsParamTypeS      = 0x00000002,
   gsParamTypeS_DLOC = 0x10000002,
   gsParamTypeI      = 0x00000003,
   gsParamTypeN      = 0x00000004,
```

Parameters for the gsAppendFormatted function can only be one of the above types.

*gsParamTypeNONE* is only ever used to terminate the parameter list.

*gsParamTypeA* is an C/ASCII string (Char const \*).

*gsParamTypeS* and *gsParamTypeS_DLOC* is a Gs string (Gs const \*).  The *_DLOC* option will tell
gsAppendFormatted to perform a gsDloc on the passed in string once done.  This is useful for 
cleaning up.  You can pass in a newly created Gs string and clean it up automatically.

*gsParamTypeI* is an integer (Gi).  *gsParamTypeN* is a natural (Gn).  Reals are not handled here
because often you may need more formatting with them.

##### gsCloc\*

```
#define gsClocA(S)       
#define gsClocGchar1(S)   
#define gsClocGchar2(S)   
#define gsClocJoin(A,S)  
#define gsClocSplit(S,L) 
```

*...A*, *...Gchar1*, and *...Gchar2* will create an ASCII, Utf8, and Utf16 string from a Gs.

*...Join* will create 

##### gsClocFrom\*

```
#define gsClocFrom(S)                   
#define gsClocFromA(A)                  
#define gsClocFromGchar1(S)              
#define gsClocFromGchar2(S)              
#define gsClocFromI(I)                  
#define gsClocFromN(N)                  
#define gsClocFromR(R)                  
#define gsClocFromFormatted(PTYPE, ...) 
#define gsClocFromParam(...)            
#define gsClocFromSub(S, START, END)    
```

Create Gs string from various inputs.

*...Gchar1* and *...Gchar2* will create a Gs from a UTF8 and UTF16 string.

*...A* will create a Gs from an ASCII string.

*...I*, *...N*, *...R* will create a Gs from an integer, natural, or real value.

*...Formatted* will create a Gs from a formatted string.  See gsAppendFormatted for details.

*...Param* will create a Gs from a variable list of Gs strings.  See gsAppendParams for details.

*...Sub* will create a Gs from a substring of another Gs string.

##### gsClocJoin

```
#define gsClocJoin(GsArray, GsSeparator)  
```

Creates a Gs by taking a GvArray of Gs strings and separating each item with the separator 
string.

Example:
```
Array:      ["The", "quick", "brown", "fox"]
Separator:  "---"

Result:     "The---quick---brown---fox"
```

##### gsClocSplit

```
#define gsClocSplit(GsSting, Letter) 
```

Creates a GvArray of Gs strings by taking a Gs string and breaking it apart at each instance of 
the given letter in the string.

Example:
```
String: "The quick brown fox"
Letter: ' '

Result: ["The", "quick", "brown", "fox"]
```

##### gsCompare\*

```
Gcompare gsCompare(             Gs const * const as, Gs   const * const bs);
Gcompare gsCompareA(            Gs const * const as, Char const * const bs);
Gcompare gsCompareContainer(    Gv const * const av, Gv   const * const bv);
Gcompare gsCompareBase(         Gs const * const as, Gs   const * const bs);
Gcompare gsCompareBaseContainer(Gv const * const av, Gv   const * const bv);
Gcompare gsCompareBaseCount(    Gs const * const as, Gs   const * const bs, Gcount const count);
Gcompare gsCompareCount(        Gs const * const as, Gs   const * const bs, Gcount const count);
```

Compare functions for Gs strings.

*...Container* is for use with the data containers.

*...Base...* is case insensitive comparison.

*...Count* limits the comparison to the first *count* characters.

##### gsEraseSub

```
Gb gsEraseSub(Gs * const a, Gindex const start, Gindex const end);
```

Erases a substring from the string from *start* to *end* indicies.

##### gsFindAndReplace

```
Gs *gsFindAndReplace(Gs * const str, Gs const * const find, Gs const * const replace, Gcount * const count);
```

Finds all instances of the string find with the string in replace.  Returns the number of times the
operation was performed in *count*.

##### gsFind\*

```
Gindex gsFindFirstNotOf(    Gs const * const str, Gindex const position, Gs   const * const letters);
Gindex gsFindFirstNotOfChar(Gs const * const str, Gindex const position, Gchar const letter);
Gindex gsFindFirstOf(       Gs const * const str, Gindex const position, Gs   const * const letters);
Gindex gsFindFirstOfChar(   Gs const * const str, Gindex const position, Gchar const letter);
Gindex gsFindLastNotOf(     Gs const * const str, Gindex const position, Gs   const * const letters);
Gindex gsFindLastNotOfChar( Gs const * const str, Gindex const position, Gchar const letter);
Gindex gsFindLastOf(        Gs const * const str, Gindex const position, Gs   const * const letters);
Gindex gsFindLastOfChar(    Gs const * const str, Gindex const position, Gchar const letter);
Gindex gsFindSub(           Gs const * const str, Gindex const position, Gs   const * const substr);
```

Find the index of the string for the whatever we are trying to find.

Return will be GindexERROR if not found.

*...Char* restricts to finding a single character.  The non char version will find any character 
in the string of characters you passed in.

*gsFindSub* finds the location of a smaller *substr* in the larger string.  

##### gsGet\*

```
Gi gsGetI(   Gs const * const str);
Gn gsGetN(   Gs const * const str);
Gn gsGetNHex(Gs const * const str);
Gr gsGetR(   Gs const * const str);
```

*...I*, *...N*, *...NHex*, and *...R* gets an integer, a natural, a natural from a hex 
representation, and a real from the string.

##### gsGetWhiteSpace

```
Gs const *gsGetWhitespace(void);
```

Gets all the whitespace characters.  Convenience function since this string has been created 
already internally.  Do not gsDloc() this string or modify it.

##### gsHash\*

```
GhashN gsHash(         Gs const * const str);
GhashN gsHashContainer(Gv const * const str);
```

Create a hash of the string.

##### gsInsert\*

```
Gs *gsInsert(Gs * const dst, Gindex const position, Gs const * const src);
```

Inserts a string inside another string.

##### gsIsBlank

```
Gb gsIsBlank(Gs const * const str);
```

Returns true if the string is NULL, empty, or is all whitespace.

##### gsIsEqual\*

```
#define gsIsEqual(         A, B)       
#define gsIsEqualA(        A, B)       
#define gsIsEqualCount(    A, B, COUNT)
#define gsIsEqualBase(     A, B)       
#define gsIsEqualBaseCount(A, B, COUNT)
```

Returns true if the two strings are equal.

*...Base* is case insensitive.

*...Count* limits the comparison to the first *count* characters.

##### gsIsEmpty

```
Gb gsIsEmpty(Gs const * const str);
```

Returns true if the string is NULL or empty.

##### gsIsMultiline

```
Gb gsIsMultiline(Gs const * const str);
```

Returns true if the string has at least one \n inside.

##### gsReverse

```
Gs *gsReverse(Gs * const str);
```

Reverses the string.

##### gsPat\*

```
Gs *gsPadHead(Gs * const str, Gcount const length, Gchar const letter);
Gs *gsPadTail(Gs * const str, Gindex const length, Gchar const letter);
```

Adds multiple of the same character to the beginning or end of the string.

##### gsSet\*

```
#define gsSet(            S, VALS)                  (gsFlush(S), gsAppend(          S, VALS))
#define gsSetI(           S, VALI)                  (gsFlush(S), gsAppendI(         S, VALI))
#define gsSetN(           S, VALN)                  (gsFlush(S), gsAppendN(         S, VALN))
#define gsSetR(           S, VALR)                  (gsFlush(S), gsAppendR(         S, VALR))
#define gsSetParams(      S, ...)                   (gsFlush(S), gsAppendParams(    S, __VA_ARGS__))
#define gsSetSub(         S, VALS, START, END)      (gsFlush(S), gsAppendSub(       S, VALS, START, END))
```

Replaces the entire string with something else.

*gsSet* replaces the string with another string.

*...I*, *...N*, and *...R* reaplaces the string with a string of the provided integer, natural, or 
real.

*gsSetParams* will replace the string with the collection of strings.  See gsAppendParams.

*gsSetSub* will replace the string with a substring of another string.


##### gsStrip\*

```
Gs *gsStrip(        Gs * const str, GsStripMethod const type);
Gs *gsStripCompress(Gs * const str);
```

Strip whitespace and escapes from the string dictated by the GsStringMethod

###### GsStripMethod

```
typedef enum
{
   gsStripMethodNONE                      = 0x00000000,

   gsStripMethodESCAPE_CHAR               = 0x00000001,
   gsStripMethodESCAPE_CHAR_ALL           = 0x00000002,

   gsStripMethodWHITE_SPACE               = 0x00000010,
   gsStripMethodWHITE_SPACE_ALL           = 0x00000020,

   gsStripMethodWHITE_SPACE_LEADING       = 0x10000000,
   gsStripMethodWHITE_SPACE_TRAILING      = 0x20000000
} GsStripMethod;
```

*...ESCAPE_CHAR* will remove the escape character '\' from the string.

*...WHITE_SPACE* will remove the internal white spaces from th string.

*...WHITE_SPACE_LEADING* will remove all leading white space.

*...WHITE_SPACE_TRAILING* will remove all trailing white space.

*...ALL* will remove all even within string enclosed in quotes inside the string.

### Gv, Gv8

A Gv/Gv8 is 8 Bytes / 64 bits in size.  This is a union of native types, a boolean (b), 
an integer (i), a natural (n, aka unsigned integer), a real (r, aka double), a string (s), and a 
pointer (p) value.  

Gv8 is the same structure since in a 64 bit machine this is the native pointer size.

```
typedef union
{
   Gn1                      byte[8]; // assuming pointer size is 8 bytes.
   Gi                       b;
   Gi                       i;
   Gn                       n;
   Gr                       r;
   Gs                      *s;        // assuming pointer size is 8 bytes.
   Gp                      *p;        // assuming pointer size is 8 bytes.
} Gv;

typedef Gv Gv8;
```

##### gsTo\*Case

```
Gs *gsToLowerCase(Gs * const str);
Gs *gsToUpperCase(Gs * const str);
```

This just converts the first 128 code points to upper case or lower case.  This is not full UNICODE
aware.

##### gsTrim\*

```
Gs *gsTrim(     Gs * const str, Gs const * const letters);
Gs *gsTrimLeft( Gs * const str, Gs const * const letters);
Gs *gsTrimRight(Gs * const str, Gs const * const letters);
```

This trims the leading or trailing characters that are found in the provide letters.  Not 
restricted to just whitespace.

#### Function

##### gvCompare\*

```
Gcompare gvCompare[I|N|R|S](Gv[|8] const * const a, Gv[|8] const * const b);
```

Compares two Gv[|8] values. 

Returns a Gcompare value.

##### gvFrom\*

```
Gv gvFromIndex(Gindex const value);
Gv gvFromP(    Gp     const value);
```

Converts a more native type to a Gv.

Returns a Gv value.

##### gvGet\*

```
#define gvGet[B|I|N|P|R|S](V)
#define gvpGet[B|I|N|P|R|S](POINTER_TO_V)
```

Get a native type from a Gv structure.

##### gvSet\*

```
#define gvSet[B|I|N|P|R|S](V, VALUE)
#define gvpSet[B|I|N|P|R|S](POINTER_TO_V, VALUE)
```

Set a Gv structure from a native type.

### Gv1

A Gv1 is 1 byte / 8 bits in size.

```
typedef union
{
   Gn1                      byte[1];
   Gi1                      b;
   Gi1                      i;
   Gn1                      n;
} Gv1;
```

#### Function

##### gv1Compare\*

```
Gcompare gv1Compare[I|N](Gv1 const * const a, Gv1 const * const b);
```

Compares two Gv1 values. 

Returns a Gcompare value.

##### gv1From\*

```
Gv gv1FromChar(Char const value);
```

Converts a more native type to a Gv1.

Returns a Gv1 value.

##### gv1Get\*

```
#define gv1Get[B|I|N](V)
#define gv1pGet[B|I|N](POINTER_TO_V)
```

Get a native type from a Gv1 structure.

##### gv1Set\*

```
#define gv1Set[B|I|N](V, VALUE)
#define gv1pSet[B|I|N](POINTER_TO_V, VALUE)
```

Set a Gv1 structure from a native type.

### Gv2

A Gv2 is 2 bytes / 16 bits in size.

```
typedef union
{
   Gn1                      byte[2];
   Gi2                      b;
   Gi2                      i;
   Gn2                      n;
} Gv2;
```

#### Function

##### gv2Compare\*

```
Gcompare gv2Compare[I|N](Gv2 const * const a, Gv2 const * const b);
```

Compares two Gv2 values. 

Returns a Gcompare value.

##### gv2Get\*

```
#define gv2Get[B|I|N](V)
#define gv2pGet[B|I|N](POINTER_TO_V)
```

Get a native type from a Gv2 structure.

##### gv1Set\*

```
#define gv2Set[B|I|N](V, VALUE)
#define gv2pSet[B|I|N](POINTER_TO_V, VALUE)
```

Set a Gv2 structure from a native type.

### Gv4

A Gv4 is 4 bytes / 32 bits in size.

```
typedef union
{
   Gn1                      byte[4];
   Gi4                      b;
   Gi4                      i;
   Gn4                      n;
   Gr4                      r;
   Gchar                    c;
} Gv4;
```

#### Function

##### gv4Compare\*

```
Gcompare gv4Compare[I|N|R](Gv4 const * const a, Gv4 const * const b);
```

Compares two Gv4 values. 

Returns a Gcompare value.

##### gv4From\*

```
Gv gv4FromGchar( Gchar  const value);
Gv gv4FromGindex(Gindex const value);
```

Converts a more native type to a Gv4.

Returns a Gv4 value.

##### gv4Get\*

```
#define gv4Get[B|I|N|R](V)
#define gv4pGet[B|I|N|R](POINTER_TO_V)
```

Get a native type from a Gv4 structure.

##### gv4Set\*

```
#define gv4Set[B|I|N|R](V, VALUE)
#define gv4pSet[B|I|N|R](POINTER_TO_V, VALUE)
```

Set a Gv4 structure from a native type.

## Data Containers

### GTYPE_VAR

```
#if _DEBUG
#define GTYPE_VAR                   Char typeName[16];
#else 
#define GTYPE_VAR
#endif
```

Each data type that is more than a trivial native type, has a type name for debugging purposes.  
This name is limited to 16 UTF8 bytes.  On windows, you sometimes get a leak report from the run-
time libraries and this leak report often shows the first 16 bytes of the memory block that was
leaked.  Hopefully this typeName will show up in that report and hopefully helps you figure out
what leaked.  However gmemLeak should also be reporting the same leak so this may be redundant.

#### Function

##### GTYPE_GET

```
#define GTYPE_GET(VAR)
```

Gets the typeName.

##### GTYPE_SET

```
#define GTYPE_SET(VAR, TYPE)
```

Sets the typeName.

### GCONTAINER_VAR

```
#define GCONTAINER_VAR                       \
   GTYPE_VAR                                 \
   Gcount                   count
```

Each data container has a count of the number of items in the container.

### Dynamic Array Functions (Gv\*Array)

GvArray, Gv1Array, Gv2Array, Gv4Array all have the same functions that work the same way.  The only
difference is that the Gv type that they work with.

```
typedef struct Gv[|1|2|4]Array
{
   GCONTAINER_VAR;

   Gcount                   countTotal;
   Gbit                     isVectorSizing   : 1,
                            isSorted         : 1;
   GrlCompareFunc           compareFunc;
   Gv[|1|2|4]              *p;
} GvArray;
```

*countTotal* is the total size of the buffer allocated for the array.  This can be larger than the
actual count of items in the array.

*isVectorSizing* indicates if the array should grow/shrink by 1.5x or by the actual amount being 
asked to grow.

*isSorted* indicates if the array is sorted.  This is just a flag.  If the programmer inserts 
something manually then this flag is turned off as it is assumed that the sortedness is broken.

*compareFunc* is a pointer to a function for comparing two values.  Required for sorted arrays.

*p* is the pointer to the actual buffer of Gv[|1|2|4] values.

#### Functions

##### gv\*ArrayAdd\*

```
Gb gv[|1|2|4]ArrayAdd(     Gv[|1|2|4]Array * const array,                     Gv[|1|2|4] const value);
Gb gv[|1|2|4]ArrayAddAt(   Gv[|1|2|4]Array * const array, Gindex const index, Gv[|1|2|4] const value);
Gb gv[|1|2|4]ArrayAddBegin(Gv[|1|2|4]Array * const array,                     Gv[|1|2|4] const value);
Gb gv[|1|2|4]ArrayAddEnd(  Gv[|1|2|4]Array * const array,                     Gv[|1|2|4] const value);
```

*\*ArrayAdd* Adds a value to the array and maintains sortedness.  Can only be used if the array was 
created with a compare function.

*\*ArrayAddAt* Adds a value at the given index.  Sets the isSorted flag to false.  If you add to 
an index that will cause a 'gap' between the current end of the array and the new index, then 
0 values will be added to fill in the gap.  You can do this or call gvArraySetCount to perform the
same operation.

*\*ArrayAddBegin* Adds a value at the beginning of the array.  Sets the isSorted flag to false.

*\*ArrayAddEnd* Adds a value at the end of the array.  Sets the isSorted flag to false.

##### gv\*ArrayClear

```
Gb gv[|1|2|4]ArrayClear(Gv[|1|2|4]Array * const array, Gcount const count, Gindex const index);
```

Sets *count* values in the array at *index* to 0.

##### gv\*ArrayCloc, gv\*ArrayClocContent

```
Gv[|1|2|4]Array *gv[|1|2|4]ArrayCloc(                                      [TYPE], GrlCompareFunc compareFunc, Gb const isVectorSizing)
Gb               gv[|1|2|4]ArrayClocContent(Gv[|1|2|4]Array * const array, [TYPE], GrlCompareFunc compareFunc, Gb const isVectorSizing)
```

*\*ArrayCloc* allocates a dynamic array. 

*\*ArrayClocContent* allocates a dynamic array contents given a pointer to a dynamic array 
structure.  I.E. used when the array may only exist temporarily in one function.  You would create 
a GvArray variable and pass it's pointer to this ClocContent function to initialize it.

##### gv\*ArrayCopy\*

```
Gb gv[|1|2|4]ArrayCopy(    Gv[|1|2|4]Array * const array, Gcount const count, Gindex const indexSrc, Gindex const indexDst);
Gb gv[|1|2|4]ArrayCopyFrom(Gv[|1|2|4]Array * const aDst, Gindex const indexDst, GvArray const * const aSrc, Gcount const count, Gindex const indexSrc);
```

*\*ArrayCopy* safely copies one part of the array to another part of the same array.

*\*ArrayCopyFrom* copies a subset from one array to another array.

##### gv\*ArrayDloc\*

```
void gv[|1|2|4]ArrayDloc(       Gv[|1|2|4]Array * const array);
void gv[|1|2|4]ArrayDlocContent(Gv[|1|2|4]Array * const array);
```

*\*ArrayCloc* deallocates a dynamic array. 

*\*ArrayClocContent* deallocates a dynamic array contents given a pointer to a dynamic array 
structure.  

##### gv\*ArrayErase\*

```
Gb gv[|1|2|4]ArrayErase(     Gv[|1|2|4]Array * const array, Gv[|1|2|4] const value);
Gb gv[|1|2|4]ArrayEraseAt(   Gv[|1|2|4]Array * const array, Gcount const count, Gindex const index);
Gb gv[|1|2|4]ArrayEraseBegin(Gv[|1|2|4]Array * const array, Gcount const count);
Gb gv[|1|2|4]ArrayEraseEnd(  Gv[|1|2|4]Array * const array, Gcount const count);
```

*\*ArrayErase* erases the first occurrence of the given value from the array.  Array doesn't need
to be sorted.

*\*ArrayEraseAt* erases *count* values at the given index.

*\*ArrayEraseBegin* erases *count* values from the beginning of the array.

*\*ArrayEraseEnd* erases *count* values from the end of the array.

##### gv\*ArrayFind

```
Gindex gv[|1|2|4]ArrayFind(Gv[|1|2|4]Array * const array, Gv[|1|2|4] const value);
```

Finds a value in the array.  The array does not need to be sorted.  The function will
do a linear search if the array is not sorted otherwise it will do a binary search.

Return the index of the item.  GindexERROR if not found.

##### gv\*ArrayFlush

```
void gv[|1|2|4]ArrayFlush(Gv[|1|2|4]Array * const array);
```

Flushes all the values in the array and returns the count to 0.

##### gv\*ArrayForEach\*

```
void gv[|1|2|4]ArrayForEach(    Gv[|1|2|4]Array * const array, GrlForEachFunc const func);
void gv[|1|2|4]ArrayForEachDown(Gv[|1|2|4]Array * const array, GrlForEachFunc const func);
```

Calls the given function for each item in the array.  *ForEachDown* does the process in reverse 
order making it possible to delete items while iterating.

##### gv\*ArrayGet\*

```
Gv[|1|2|4] const   *gv[|1|2|4]ArrayGet(     Gv[|1|2|4]Array  const * const array);
Gv[|1|2|4]          gv[|1|2|4]ArrayGetAt(   Gv[|1|2|4]Array  const * const array, Gindex const index);
Gv[|1|2|4]          gv[|1|2|4]ArrayGetBegin(Gv[|1|2|4]Array  const * const array);
Gv[|1|2|4]          gv[|1|2|4]ArrayGetEnd(  Gv[|1|2|4]Array  const * const array);
```

*ArrayGet* gets a pointer to the internal buffer of the array.

*ArrayGetAt* gets the value at the given index.

*ArrayGetBegin* gets the value at the beginning of the array.

*ArrayGetEnd* gets the value at the end of the array.


##### gv\*ArrayGetCount

```
Gcount gv[|1|2|4]ArrayGetCount(Gv[|1|2|4]Array const * const array);
```

Get the count of items in the array.

##### gv\*ArraySetCount

```
Gcount gv[|1|2|4]ArraySetCount(Gv[|1|2|4]Array const * const array, Gcount const value);
```

Set the count of items in the array.  If the count is larger then the array grows and inserts 0s
for the new items.  If the count is smaller then the array truncates and the values that are pruned
are lost.  If items in the array are allocated then the programmer must deallocate them before this
call.

##### gv\*ArraySort

```
Gcount gv[|1|2|4]ArraySort(Gv[|1|2|4]Array const * const array);
```

Sort the array.  Must provide a compare function when creating the array.

##### gv\*ArraySwap

```
Gb gv[|1|2|4]ArraySwap(Gv[|1|2|4]Array * const array, Gindex const indexA, Gindex const indexB);
```

Swaps the values at two given indicies.

##### gv\*ArrayUpdateAt\*

```
Gb gv[|1|2|4]ArrayUpdateAt(Gv[|1|2|4]Array * const array, Gindex const index, Gv[|1|2|4] const value);
```

Update a value in the array at a given index.  Sets the isSorted flag to false.

