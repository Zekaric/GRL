/**************************************************************************************************
file:       grob
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:
GRL Repository of Organized Blocks.

These routines will implement a B-Tree using a grob file.  We have just 3 different RUB type blocks
for this file.

The INFO block holds configuation information about the nodes.  Like how many keys per node, and
how large the kes are.  There will only ever be one INFO block and this block will be what is
pointed to by the RUB layer.

The NODE block holds the B-Tree nodes.  Holding n keys, n pointers/rub block offsets to data for
that key, and n+1 pointers to child nodes for the b-tree.

The DATA block holds a copy of the key, the type of data being stored, the raw size of the data,
and the data itself.

Because this is working off RUB it is easy to debug the file in a hex editor to see what is in each
of these 3 types of blocks.

grob File Type is "GROB"

Information Block:  Root index of the grob file.  Only one per file.
   grob Data Type "INFO"
   4 B  - Version number of grob.
   4 B  - Sub format information.  Similar to how GROB is to GRUB.
   4 B  - Count of keys in the key nodes. (KC)
   4 B  - Key Size. (KS)
   8 B  - Index to root key node.

Key Node Block:
   grob Data Type "NODE"
   (KS *       KC) B    - The keys.
   ( 8 * (KC + 1)) B    - The offsets.

Data Block:
   grob Data Type "DATA"
   KS B  - The key.
    4 B  - Type of the data. "INT ", "NAT ", "REAL", "STR ", "PNT "
    4 B  - raw size of data.
    N B  - Data.
**************************************************************************************************/

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
constant:
**************************************************************************************************/
#define GROBHEADER      "GROB"
#define INFOHEADER      "INFO"
#define NODEHEADER      "NODE"
#define DATAHEADER      "DATA"
#define FILEVERSION     1
#define INFOHEADERSIZE  24

/**************************************************************************************************
variable:
**************************************************************************************************/
Gid   _grobId   = {0},
      _infoId   = {0},
      _nodeId   = {0},
      _dataId   = {0};

/**************************************************************************************************
function:
**************************************************************************************************/
static GioRobData   *_DataCloc(        const GioRob * const rob);
static void        _DataDestroy(             GioRobData * const data);
static Gn4         _DataGetHeaderSize( const GioRob * const rob);
static Gb          _DataRead(          const GioRob * const rob,       GioRobData * const data);
static Gb          _DataWrite(         const GioRob * const rob, const GioRobData * const data);

static Gb          _HeaderWrite(       const GioRob * const rob);

static void        _KeyClean(          const GioRob * const rob, Gchar1 * const key);

static void        _NodeCopy(          const GioRob * const rob, const GioRobNode * const a, GioRobNode * const b);
static GioRobNode   *_NodeCloc(        const GioRob * const rob);
static void        _NodeDloc(             GioRobNode * const node);
static Gn4         _NodeGetSize(       const GioRob * const rob);
static Gb          _NodeInsert(        const GioRob * const rob,       GioRobNode * const node,   const Gchar1 * const key, const Gn8 keyIndex);
static Gb          _NodeInsertKey(     const GioRob * const rob,       GioRobNode * const node,   const Gi4 index,        const Gchar1 * const key,            const Gn8 keyIndex);
static Gb          _NodeMerge(         const GioRob * const rob,       GioRobNode * const parent, const Gi4 index,              GioRobNode * const lchild,     const GioRobNode * const rchild);
static Gb          _NodeRead(          const GioRob * const rob,       GioRobNode * const node);
static Gb          _NodeRemove(              GioRob * const rob,       GioRobNode * const node,         Gchar1 * const key, const Gi4 mode,                          Gchar1 * const kswap, Gn8 * const kiswap);
static Gb          _NodeRemoveKey(     const GioRob * const rob,       GioRobNode * const node,   const Gi4 index);
static GioRobData *_NodeSearch(        const GioRob * const rob,       GioRobNode * const node,   const Gchar1 * const key);
static Gi8         _NodeSearchKey(     const GioRob * const rob, const GioRobNode * const node,   const Gchar1 * const key);
static void        _NodeSetKey(        const GioRob * const rob, const GioRobNode * const node,   const Gi4 index,        const Gchar1 * const key,            const Gn8 keyIndex);
static Gb          _NodeSplitChild(    const GioRob * const rob,       GioRobNode * const parent, const Gi4 index,              GioRobNode * const child,       GioRobNode * const child2ndhalf);
static Gb          _NodeWrite(         const GioRob * const rob, const GioRobNode * const node);

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gioRobClose

Close the file and clean up.

param:
rob
   GioRob *
   in
   The file.
**************************************************************************************************/
grlAPI void gioRobClose(GioRob * const rob)
{
   genter;

   // Nothing to do.
   greturnIf(!rob);

   // Flush the data.
   greturnIf(_HeaderWrite(rob));

   // Clean up.
   gioRubClose(rob->rub);

   gmemDloc(rob);

   greturn;
}

/**************************************************************************************************
func: gioRobCreateData

Create a data item in the rob.

param:
rob
   GioRob *
   in
   The file.

key, dataType, size
   char *, char *, Gn4
   in, in, in
   The key, type and size of the data.

return:
GioRobData *
**************************************************************************************************/
grlAPI GioRobData *gioRobClocData_(GioRob * const rob, const Gchar1 * const key, Gid const dataType, const Gn4 size)
{
   GioRubData *dtemp;
   GioRobData *data;
   GioRobNode *node;

   genter;

   // Nothing to do.
   greturnValIf(
         !rob      ||
         !key      ||
         !gidIsGood(dataType),
      NULL);

   node = NULL;

   // Check to see if the data already exists.  If it does.  BAD!
   data = gioRobGetData(rob, key);
   stopIf(data);

   // Create the data block.
   dtemp = gioRubClocData(rob->rub, _dataId, size + _DataGetHeaderSize(rob));

   data           = gleakCloc(_DataCloc(rob), gsizeof(GioRobData));
   data->index    = gioRubDataGetIndex(dtemp);
   data->size     = size;
   data->dataType = dataType;
   strncpy_s((char *) data->key, (size_t) rob->keySize, (char *) key, (size_t) rob->keySize);

   stopIf(!_DataWrite(rob, data));

   gioRubDataDloc(dtemp);


   // Insert into the tree.
   node = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
   stopIf(!node);

   node->index = rob->rootNodeIndex;

   stopIf(!_NodeRead(rob, node));

   // Empty Tree.
   if      (node->keyCount == 0)
   {
      stopIf(!_NodeInsertKey(rob, node, 0, key, data->index));

      stopIf(!_NodeWrite(rob, node));

      // Clean up.
      _NodeDloc(node);
   }
   // Root node not full.
   else if (node->keyCount != rob->keyCount)
   {
      stopIf(!_NodeInsert(rob, node, key, data->index));

      // Clean up.
      _NodeDloc(node);
   }
   else
   {
      GioRobNode *root;
      GioRobNode *node2ndhalf;

      // Create new root.
      root              = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
      stopIf(!root);

      dtemp             = gioRubClocData(rob->rub, _nodeId, _NodeGetSize(rob));
      stopIf(!dtemp);

      root->index       = gioRubDataGetIndex(dtemp);
      root->nodeList[0] = node->index;
      gioRubDataDloc(dtemp);

      // Split child.
      node2ndhalf = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
      stopIf(!node2ndhalf);

      stopIf(!_NodeSplitChild(rob, root, 0, node, node2ndhalf));

      // Clean up.
      _NodeDloc(node);
      _NodeDloc(node2ndhalf);


      // Update the header.
      rob->rootNodeIndex = root->index;
      stopIf(!_HeaderWrite(rob));


      // Insert the new key.
      stopIf(!_NodeInsert(rob, root, data->key, data->index));


      // Clean up.
      _NodeDloc(root);
   }

   greturn data;

STOP:
   _NodeDloc(node);
   greturnValIf(!gioRobDataDloc(data), NULL);

   greturn NULL;
}

/**************************************************************************************************
func: gioRobDlocData

Destroy the data and remove from the tree.

param:
rob
   GioRob *
   in
   The file.

return:
Gi4
**************************************************************************************************/
grlAPI Gb gioRobDlocData(GioRob * const rob, GioRobData * const data)
{
   GioRobNode *node;
   GioRubData *rubData;

   genter;

   // Nothing to do.
   greturnValIf(
         !rob ||
         !data,
      gbFALSE);

   // Remove from the tree.
   node = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
   node->index = rob->rootNodeIndex;
   greturnValIf(!_NodeRead(rob, node), gbFALSE);

   greturnValIf(!_NodeRemove(rob, node, data->key, 0, NULL, NULL), gbFALSE);

   _NodeDloc(node);

   // Remove the data from the file.
   rubData = gioRubGetData(rob->rub, data->index);
   greturnValIf(!gioRubDlocData(rob->rub, rubData), gbFALSE);

   greturnValIf(!gioRobDataDloc(data), gbFALSE);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRobFlush

Update the file.

param:
rob
   GioRob *
   in
   The file.
**************************************************************************************************/
grlAPI void gioRobFlush(const GioRob * const rob)
{
   genter;

   // Nothing to do.
   greturnIf(!rob);

   greturnIf(_HeaderWrite(rob));

   greturn;
}

/**************************************************************************************************
func: gioRobGetData

Search the rob.

param:
rob
   GioRob *
   in
   The file.

key
   char *
   in
   The key.

return:
GioRobData *
**************************************************************************************************/
grlAPI GioRobData *gioRobGetData(const GioRob * const rob, const Gchar1 * const key)
{
   GioRobNode *node;
   GioRobData *data;

   genter;

   data = NULL;
   node = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

   node->index = rob->rootNodeIndex;

   if (!_NodeRead(rob, node))
   {
      data = _NodeSearch(rob, node, key);
   }
   _NodeDloc(node);

   greturn data;
}

/**************************************************************************************************
func: gioRobGetKeyCount

Get the key count per node

param:
rob
   GioRob *
   in
   The file.

return:
Gn4
**************************************************************************************************/
grlAPI Gn4 gioRobGetKeyCount(const GioRob * const rob)
{
   genter;

   greturnValIf(!rob, 0);

   greturn rob->keyCount;
}

/**************************************************************************************************
func: gioRobGetKeySize

Get the size of each key.

param:
rob
   GioRob *
   in
   The file.

return:
Gn4
**************************************************************************************************/
grlAPI Gn4 gioRobGetKeySize(const GioRob * const rob)
{
   genter;

   // Nothing to do.
   if (!rob)
   {
      greturn 0;
   }

   greturn rob->keySize;
}

/**************************************************************************************************
func: gioRobGetType

Get the type of the file.

param:
rob
   GioRob *
   in
   The file.

return:
char *
**************************************************************************************************/
grlAPI Gid gioRobGetType(const GioRob * const rob)
{
   genter;

   greturnValIf(!rob, GidNONE);

   greturn rob->fileType;
}

/**************************************************************************************************
func: gioRobGetVersion

Get the version of the rob.

param:
rob
   GioRob *
   in
   The file.

return:
Gn4
**************************************************************************************************/
grlAPI Gn4 gioRobGetVersion(const GioRob * const rob)
{
   genter;

   // Nothing to do.
   if (!rob)
   {
      greturn 0;
   }

   greturn rob->version;
}

/**************************************************************************************************
func: gioRobLockOn

Lock the file so that the data item can be read.

param:
rob
   GioRob *
   in
   The file.

return:
Gfile *
**************************************************************************************************/
grlAPI Gfile *gioRobLockOn(const GioRob * const rob, const GioRobData * const data)
{
   Gfile    *file;
   GioRubData *dtemp;

   genter;

   if (!rob ||
       !data)
   {
      greturn NULL;
   }

   dtemp = gioRubGetData(rob->rub, data->index);
   file  = gioRubLockOn(rob->rub, dtemp);

   if (gfileSetPosition(file, gpositionCURRENT, (Goffset) _DataGetHeaderSize(rob)) !=
         gfileSetPositionSUCCESS)
   {
      debugHalt("gfileSetPosition failed");
   }

   gioRubDataDloc(dtemp);

   greturn file;
}

/**************************************************************************************************
func: gioRobLockOff

Unlock the file.

param:
rob
   GioRob *
   in
   The file.
**************************************************************************************************/
grlAPI Gb gioRobLockOff(GioRob * const rob)
{
   genter;

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);
   rob->isLocked = gbFALSE;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRobOpen

Open the rob file.

param:
filename
   Gs *
   in
   the filename.

mode
   GrobOpen
   in
   The mode in which to open the file.

filetype, keyCount, keySize
   char *, Gn4, Gn4
   in, in, in
   ONLY REQUIRED WHEN MODE IS grobOpenREAD_WRITE_NEW.  Specifies the
   type of the file, the number of keys per Btree node, and the size
   of the key in bytes.

return:
GioRob *
**************************************************************************************************/
grlAPI GioRob *gioRobOpen_(const Gpath * const path, const GfileOpenMode mode,
   Gid const fileType, const Gn4 keyCount, const Gn4 keySize)
{
   Gfile      *file;
   GioRob     *rob;
   GioRubData *data;
   GioRobNode *node;

   genter;

   file = NULL;
   data = NULL;

   rob = gmemClocType(GioRob);
   greturnNullIf(!rob);

   loopOnce
   {
      // Creating a new file.
      if (mode == gfileOpenModeREAD_WRITE_NEW)
      {
         breakIf(!gidIsGood(fileType));

         rob->rub = gioRubOpen(path, mode, _grobId, FILEVERSION); //lint !e930
         breakIf(!rob->rub);

         rob->fileType = fileType;
         rob->keyCount = gMAX(3, keyCount);
         rob->keySize  = gMAX(4, keySize);
         rob->version  = FILEVERSION;

         data = gioRubClocData(rob->rub, _infoId, INFOHEADERSIZE);
         breakIf(!gioRubSetRootIndex(rob->rub, gioRubDataGetIndex(data)));
         gioRubDataDloc(data);

         node               = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
         data               = gioRubClocData(rob->rub, _nodeId, _NodeGetSize(rob));
         rob->rootNodeIndex = gioRubDataGetIndex(data);
         node->index        = gioRubDataGetIndex(data);
         gioRubDataDloc(data);

         breakIf(!_NodeWrite(rob, node));
         _NodeDloc(node);

         breakIf(!_HeaderWrite(rob));

         greturn rob;
      }


      // Opening an existing file.
      rob->rub = gioRubOpen(path, mode, _grobId, FILEVERSION); //lint !e930

      // Not a rub file.
      breakIf(!rob->rub);

      // A rob file.
      breakIf(gidIsEqual(_grobId, gioRubGetType(rob->rub)));

      data = gioRubGetData(rob->rub, gioRubGetRootIndex(rob->rub));

      // Something wrong.  Root block isn't a rob info block.
      breakIf(gidIsEqual(_infoId, gioRubDataGetType(data)));

      file = gioRubLockOn(rob->rub, data);

      // Get the version of the rob.
      breakIf(!gfileGet4(file, 1, (Gp *) &(rob->version)));
      breakIf(!gfileGet( file, 4,        &(rob->fileType)));
      breakIf(!gfileGet4(file, 1, (Gp *) &(rob->keyCount)));
      breakIf(!gfileGet4(file, 1, (Gp *) &(rob->keySize)));
      breakIf(!gfileGet8(file, 1, (Gp *) &(rob->rootNodeIndex)));

      breakIf(!gioRubLockOff(rob->rub));

      greturn rob;
   }

   // Clean up on failed open.
   gioRubDataDloc(data);
   gioRubClose(rob->rub);
   gmemDloc(rob);

   greturn NULL;
}

/**************************************************************************************************
func: gioRobStart
**************************************************************************************************/
Gb gioRobStart(void)
{
   genter;

   gmemCopyOverTypeArray(GROBHEADER, Gchar1, 4, &_grobId);
   gmemCopyOverTypeArray(INFOHEADER, Gchar1, 4, &_infoId);
   gmemCopyOverTypeArray(NODEHEADER, Gchar1, 4, &_nodeId);
   gmemCopyOverTypeArray(DATAHEADER, Gchar1, 4, &_dataId);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRobStop
**************************************************************************************************/
void gioRobStop(void)
{
   // Nothing
}

/**************************************************************************************************
data routines
**************************************************************************************************/
/**************************************************************************************************
func: gioRobDataDloc

Clean up the data pointer.

param:
data
   GioRobData *
   in
   The data.
**************************************************************************************************/
grlAPI Gb gioRobDataDloc(GioRobData * const data)
{
   genter;

   greturnValIf(!data, gbTRUE);

   gmemDloc(data->key);
   gmemDloc(data);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gioRobDataGetKey

Get the key of the data.

param:
data
   GioRobData *
   in
   The data.

return:
char *
**************************************************************************************************/
grlAPI const Gchar1 *gioRobDataGetKey(const GioRobData * const data)
{
   genter;

   if (!data)
   {
      greturn NULL;
   }
   greturn data->key;
}

/**************************************************************************************************
func: gioRobDataGetSize

Get the raw size of the data.

param:
data
   GioRobData *
   in
   The data.

return:
Gn4
**************************************************************************************************/
grlAPI Gn4 gioRobDataGetSize(const GioRobData * const data)
{
   genter;

   if (!data)
   {
      greturn 0;
   }
   greturn data->size;
}

/**************************************************************************************************
func: gioRobDataGetType

Get the type of the data stored here.

param:
data
   GioRobData *
   in
   The data.

return:
char *
**************************************************************************************************/
grlAPI Gid gioRobDataGetType(const GioRobData * const data)
{
   genter;

   greturnValIf(!data, GidNONE);

   greturn data->dataType;
}

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _DataCloc

Create a data pointer.

param:
rob
   GioRob *
   in
   the file.

return:
GioRobData *
**************************************************************************************************/
static GioRobData *_DataCloc(const GioRob * const rob)
{
   GioRobData *data;

   genter;

   data = gmemClocType(GioRobData);
   greturnNullIf(!data);

   data->key = gmemClocTypeArray(Gchar1, rob->keySize);
   if (!data->key)
   {
      gmemDloc(data);
      greturn NULL;
   }

   greturn data;
}

/**************************************************************************************************
func: _DataDestroy

Clean up.

param:
data
   GioRobData *
   in
   the data
**************************************************************************************************/
static void _DataDestroy(GioRobData * const data)
{
   genter;

   gmemDloc(data->key);
   gmemDloc(data);
   greturn;
}

/**************************************************************************************************
func: _DataGetHeaderSize

Get the header size for a data item.

param:
rob
   GioRob *
   in
   The file.

return:
Gn4
**************************************************************************************************/
static Gn4 _DataGetHeaderSize(const GioRob * const rob)
{
   genter;

   greturn rob->keySize + 8;
}

/**************************************************************************************************
func: _DataRead

Read in the data header.

param:
rob
   GioRob *
   in
   the file

data
   GioRobData *
   in
   the data.

return:
Gi4
**************************************************************************************************/
static Gb _DataRead(const GioRob * const rob, GioRobData * const data)
{
   GioRubData *dtemp;
   Gfile    *file;

   genter;

   dtemp = gioRubGetData(rob->rub, data->index);
   file  = gioRubLockOn(rob->rub, dtemp);

   greturnValIf(!gfileGet( file, rob->keySize, data->key),      gbFALSE);
   greturnValIf(!gfileGet( file, 4,           &data->dataType), gbFALSE);
   greturnValIf(!gfileGet4(file, 1, (Gp *) &(data->size)),      gbFALSE);

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);
   gioRubDataDloc(dtemp);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _DataWrite

Write out the data header.

param:
rob
   GioRob *
   in
   the file

data
   GioRobData *
   in
   the data.

return:
Gi4
**************************************************************************************************/
static Gb _DataWrite(const GioRob * const rob, const GioRobData * const data)
{
   GioRubData *dtemp;
   Gfile    *file;

   genter;

   dtemp = gioRubGetData(rob->rub, data->index);
   file  = gioRubLockOn(rob->rub, dtemp);

   greturnValIf(!gfileSet( file, rob->keySize, data->key,      NULL), gbFALSE);
   greturnValIf(!gfileSet( file, 4,           &data->dataType, NULL), gbFALSE);
   greturnValIf(!gfileSet4(file, 1,   (Gp *) &(data->size)),          gbFALSE);

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);
   gioRubDataDloc(dtemp);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _HeaderWrite

Write the rob header.

param:
rob
   GioRob *
   in
   The file.

return:
Gi4
**************************************************************************************************/
static Gb _HeaderWrite(const GioRob * const rob)
{
   Gfile    *file;
   GioRubData *data;

   genter;

   // Get the info block.
   data = gioRubGetData(rob->rub, gioRubGetRootIndex(rob->rub));

   // Lock the file.
   file = gioRubLockOn(rob->rub, data);
   greturnValIf(!file, gbFALSE);

   // Get the version of the rob.
   greturnValIf(!gfileSet4(file, 1, (Gp *) &(rob->version)),         gbFALSE);
   greturnValIf(!gfileSet( file, 4,        &(rob->fileType), NULL),  gbFALSE);
   greturnValIf(!gfileSet4(file, 1, (Gp *) &(rob->keyCount)),        gbFALSE);
   greturnValIf(!gfileSet4(file, 1, (Gp *) &(rob->keySize)),         gbFALSE);
   greturnValIf(!gfileSet8(file, 1, (Gp *) &(rob->rootNodeIndex)),   gbFALSE);

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);

   gioRubDataDloc(data);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _KeyClean

Clean the garbage from the nodes.
**************************************************************************************************/
static void _KeyClean(const GioRob * const rob, Gchar1 * const key)
{
   Gi4 a;

   genter;

   // Find the null terminator.
   forCount(a, (Gi4) rob->keySize)
   {
      breakIf(key[a] == (Gchar1) '\0');
   }

   // Null out the rest.
   a++;
   if (a < (Gi4) rob->keySize)
   {
      gmemClear(&(key[a]), rob->keySize - a);//lint !e737
   }
   greturn;
}

/**************************************************************************************************
func: _NodeCopy

Copy the node content.

param:
rob
   GioRob *
   in
   The file.

a, b
   GioRobNode *, GioRobNode *
   in, in/out
   the nodes.
**************************************************************************************************/
static void _NodeCopy(const GioRob * const rob, const GioRobNode * const a, GioRobNode * const b)
{
   genter;

   b->index    = a->index;
   b->keyCount = a->keyCount;

   gmemCopyOverTypeArray(a->indexList, Gn8, rob->keyCount,           b->indexList);
   gmemCopyOver(         a->keyList,   rob->keySize * rob->keyCount, b->keyList);//lint !e647
   gmemCopyOverTypeArray(a->nodeList,  Gn8, rob->keyCount + 1,       b->nodeList);//lint !e776

   greturn;
}

/**************************************************************************************************
func: _NodeCloc

Create a node

param:
rob
   GioRob *
   in
   the file.

return:
GioRobNode *
**************************************************************************************************/
static GioRobNode *_NodeCloc(const GioRob * const rob)
{
   GioRobNode *node;

   genter;

   node = gmemClocType(GioRobNode);
   greturnNullIf(!node);

   node->keyList   = gmemClocTypeArray(Gchar1,  rob->keySize * rob->keyCount);//lint !e647
   node->indexList = gmemClocTypeArray(Gn8,   rob->keyCount);
   node->nodeList  = gmemClocTypeArray(Gn8,   rob->keyCount + 1);//lint !e776

   if (!node->keyList   ||
       !node->indexList ||
       !node->nodeList)
   {
      gmemDloc(node->keyList);
      gmemDloc(node->indexList);
      gmemDloc(node->nodeList);
      gmemDloc(node);
      greturn NULL;
   }

   node->keyCount = 0;

   greturn node;
}

/**************************************************************************************************
func: _NodeDloc

Destroy the node.

param:
node
   GioRobNode *
   in
   The node.
**************************************************************************************************/
static void _NodeDloc(GioRobNode * const node)
{
   genter;

   greturnIf(!node);

   gmemDloc(node->nodeList);
   gmemDloc(node->indexList);
   gmemDloc(node->keyList);
   gmemDloc(node);
   greturn;
}

/**************************************************************************************************
func: _NodeGetSize

Get the data size of a node.

param:
rob
   GioRob *
   in
   The file.

return:
Gn4
**************************************************************************************************/
static Gn4 _NodeGetSize(const GioRob * const rob)
{
   genter;

   greturn
      // key count.
      4 +
      // key and indecies.
      (rob->keyCount * (rob->keySize + 8)) +
      // node indecies.
      ((rob->keyCount + 1) * 8);
}

/**************************************************************************************************
func: _NodeInsert

Insert the key into the tree.

param:
rob
   GioRob *
   in
   the file.

node
   GioRobNode *
   in
   The node.

key, index
   char *, Gn8
   in, in
   The information for the key.

return:
Gi4
**************************************************************************************************/
static Gb _NodeInsert(const GioRob * const rob, GioRobNode * const node, const Gchar1 * const key, const Gn8 keyIndex)
{
   Gi8          index;
   GioRobNode  *ntemp,
               *ntemp2ndhalf;

   genter;

   ntemp        = (GioRobNode *) gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
   ntemp2ndhalf = (GioRobNode *) gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

   loop
   {
      // Find the location of the new key.
      index = _NodeSearchKey(rob, node, key);

      /* Shouldn't happen because caller already checked.
      ** here for sanity.*/
      breakIf(0 <= index && index < rob->keyCount);

      // Get the index.
      index = -(index + 1);

      // Leaf node.
      breakIf(node->nodeList[0] == 0);

      // Internal node.
      ntemp->index = node->nodeList[index];
      greturnValIf(!_NodeRead(rob, ntemp), gbFALSE);

      if (ntemp->keyCount == rob->keyCount)
      {
         greturnValIf(!_NodeSplitChild(rob, node, (Gi4) index, ntemp, ntemp2ndhalf), gbFALSE);

         // After the split we need to see which sub child we need to go down.
         if (charCompare(
               (size_t) rob->keySize,
               (char *) key,
               (char *) &(node->keyList[index * rob->keySize])) < 0)
         {
            _NodeCopy(rob, ntemp, node);
         }
         else
         {
            _NodeCopy(rob, ntemp2ndhalf, node);
         }
      }
      else
      {
         _NodeCopy(rob, ntemp, node);
      }
   }

   // Clean up.
   _NodeDloc(ntemp);
   _NodeDloc(ntemp2ndhalf);

   // Insert into the node.
   greturnValIf(!_NodeInsertKey(rob, node, (Gi4) index, key, keyIndex), gbFALSE);

   greturnValIf(!_NodeWrite(rob, node), gbFALSE);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeInsertKey

Insert a key into a node.

param:
rob
   GioRob *
   in
   the file.

node
   GioRobNode *
   in
   The node.

index
   Gi4
   in
   the position to put the key in.

key, keyIndex
   char *, Gn8
   in, in
   The information for the key.

return:
Gi4
**************************************************************************************************/
static Gb _NodeInsertKey(const GioRob * const rob, GioRobNode * const node, const Gi4 index, const Gchar1 * const key, const Gn8 keyIndex)
{
   genter;

   // Make a space.
   gmemCopyOver(
      &(node->keyList[rob->keySize *  index     ]),
      rob->keySize * ((rob->keyCount - index) - 1),
      &(node->keyList[rob->keySize * (index + 1)]));//lint !e647 !e737 !e679
   gmemCopyOverTypeArray(
      &(node->indexList[index]),
      Gn8,
      rob->keyCount - index - 1,
      &(node->indexList[index + 1]));//lint !e737 !e679
   gmemCopyOverTypeArray(
      &(node->nodeList[ index]),
      Gn8,
      rob->keyCount - index,
      &(node->nodeList[ index + 1]));//lint !e737 !e679

   // Bring up the key from the child.
   node->keyCount = node->keyCount + 1;
   _NodeSetKey(rob, node, index, key, keyIndex);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeMerge

Merge the parent key with it's two children.

param:
rob
   GioRob *
   in
   the file.

parent
   GioRobNode *
   in
   The node.

index
   Gi4
   in
   the position to put the key in.

lchild, rchild
   GioRobNode *, GioRobNode *
   in, in
   The node.

return:
Gi4
**************************************************************************************************/
static Gb _NodeMerge(const GioRob * const rob, GioRobNode * const parent, const Gi4 index, GioRobNode * const lchild, const GioRobNode * const rchild)
{
   genter;

   // Copy the parent key down to the lchild.
   gmemCopyOver(
      &(parent->keyList[rob->keySize * index           ]),
      rob->keySize,
      &(lchild->keyList[rob->keySize * lchild->keyCount]));//lint !e679 !e737 !e679
   lchild->indexList[lchild->keyCount] = parent->indexList[index];
   lchild->keyCount = lchild->keyCount + 1;

   // Remove the key from the parent.
   greturnValIf(!_NodeRemoveKey(rob, parent, index), gbFALSE);

   // Copy the keys from the right child over to the left child.
   gmemCopyOver(
      &(rchild->keyList[rob->keySize * 0               ]),
      rob->keySize * rchild->keyCount,
      &(lchild->keyList[rob->keySize * lchild->keyCount]));//lint !e647 !e835 !e679 !e941
   gmemCopyOverTypeArray(
      &(rchild->indexList[0               ]),
      Gn8,
      rchild->keyCount,
      &(lchild->indexList[lchild->keyCount]));
   gmemCopyOverTypeArray(
      &(rchild->nodeList[0               ]),
      Gn8,
      rchild->keyCount + 1,
      &(lchild->nodeList[lchild->keyCount]));//lint !e776

   lchild->keyCount += rchild->keyCount;

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeRead

Read in the node.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

return:
Gi4
**************************************************************************************************/
static Gb _NodeRead(const GioRob * const rob, GioRobNode * const node)
{
   Gfile    *file;
   GioRubData *data;

   genter;

   data = gioRubGetData(rob->rub, node->index);
   file = gioRubLockOn(rob->rub, data);

   greturnValIf(!gfileGet4(file, 1,                     (Gp *) &(node->keyCount)), gbFALSE);
   greturnValIf(!gfileGet( file, (rob->keyCount * rob->keySize), node->keyList),   gbFALSE); //lint !e647
   greturnValIf(!gfileGet8(file, rob->keyCount,        (Gp *)   node->indexList), gbFALSE);
   greturnValIf(!gfileGet8(file, (rob->keyCount + 1),   (Gp *)   node->nodeList),  gbFALSE);

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);
   gioRubDataDloc(data);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeRemove

Remove a node from the tree.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

key
   char *
   in
   the key.

mode, kswap, kiswap
   Gi4, char *, Gn8 *
   in, in/out, in/out
   The mode.
    0 = Normal, match on key value.
   -1 = Remove and swap successor.
    1 = Remove and swap predecessor.

return:
Gi4
**************************************************************************************************/
static Gb _NodeRemove(GioRob * const rob, GioRobNode * const node, Gchar1 * const key, const Gi4 mode, Gchar1 * const kswap, Gn8 * const kiswap)
{
   Gi8 index;

   genter;

   loop
   {
      index = 0;

      // Find the index of the key to remove.
      if      (mode == 0)
      {
         index = _NodeSearchKey(rob, node, key);
      }
      else if (mode == -1)
      {
         if (!node->nodeList[0])
         {
            index = 0;
         }
         else
         {
            index = -1;
         }
      }
      else if (mode == 1)
      {
         if (!node->nodeList[0])
         {
            index = node->keyCount - 1;
         }
         else
         {
            index = -((Gi4) node->keyCount + 1);//lint !e776
         }
      }

      // From Introductions to Algorithms (Cormen, Leiserson & Rivest), chapter 19.3
      // CASE 1: key is in leaf node, remove key from leaf node.
      if (!node->nodeList[0])
      {
         // Remove the key.
         if (0 <= index && index < node->keyCount)
         {
            // We need to swap values.
            if (mode != 0)
            {
               gmemCopyOver(
                  &(node->keyList[rob->keySize * index]),
                  rob->keySize,
                  kswap);
               *kiswap = node->indexList[index];
            }

            // Remove the key.
            greturnFalseIf(!_NodeRemoveKey(rob, node, (Gi4) index));
            greturnFalseIf(!_NodeWrite(rob, node));
            greturn gbTRUE;
         }
         else
         {
            // Should never happen but the key doesn't exist.
            greturn gbFALSE;
         }
      }

      // CASE 2: Key is in an internal node.
      if (0 <= index && index < node->keyCount)
      {
         GioRobNode *lchild,
                  *rchild;

         lchild = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));
         rchild = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

         lchild->index = node->nodeList[index];
         rchild->index = node->nodeList[index + 1];

         greturnFalseIf(!_NodeRead(rob, lchild));
         greturnFalseIf(!_NodeRead(rob, rchild));

         // CASE 2c: both children have a small enough number of keys that a merge of nodes is
         // possible.
         if (lchild->keyCount + rchild->keyCount < rob->keyCount)
         {
            GioRubData *data;

            greturnFalseIf(!_NodeMerge(rob, node, (Gi4) index, lchild, rchild));

            // Root node is empty.  Pop it off.
            if (node->index    == rob->rootNodeIndex &&
                node->keyCount == 0)
            {
               rob->rootNodeIndex = lchild->index;

               data = gioRubGetData(rob->rub, node->index);
               greturnFalseIf(!gioRubDlocData(rob->rub, data));

               greturnFalseIf(!_HeaderWrite(rob));
            }
            // Root node still has data.
            else
            {
               greturnFalseIf(!_NodeWrite(rob, node));
            }
            greturnFalseIf(!_NodeWrite(rob, lchild));

            data = gioRubGetData(rob->rub, rchild->index);
            greturnFalseIf(!gioRubDlocData(rob->rub, data));

            _NodeDloc(rchild);

            // Continue with the removal of the key.
            _NodeCopy(rob, lchild, node);
            _NodeDloc(lchild);
         }
         // CASE 2a: Get predecessor and swap the keys.
         else if (lchild->keyCount >= rchild->keyCount)
         {
            _NodeDloc(rchild);
            greturnFalseIf(
               !_NodeRemove(
                  rob,
                  lchild,
                  key,
                  1,
                  &(node->keyList[rob->keySize * index]),
                  &(node->indexList[index])));

            greturnFalseIf(!_NodeWrite(rob, node));
            _NodeDloc(lchild);
            greturn gbTRUE;
         }
         // Case 2b: Get the successor and swap the keys.
         else
         {
            _NodeDloc(lchild);
            greturnFalseIf(
               !_NodeRemove(
                  rob,
                  rchild,
                  key,
                  -1,
                  &(node->keyList[rob->keySize * index]),
                  &(node->indexList[index])));

            greturnFalseIf(!_NodeWrite(rob, node));
            _NodeDloc(rchild);
            greturn gbTRUE;
         }
      }

      // CASE 3: Key is in a sub tree of the current node.
      else
      {
         GioRobNode *child,
                  *lsib,
                  *rsib;

         lsib  = NULL;
         rsib  = NULL;
         index = -(index + 1);

         child = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

         child->index = node->nodeList[index];
         greturnFalseIf(!_NodeRead(rob, child));

         if (child->keyCount < (rob->keyCount + 1) / 2)
         {
            // Get the left sibling.
            if (index > 0)
            {
               lsib = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

               lsib->index = node->nodeList[index - 1];
               greturnFalseIf(!_NodeRead(rob, lsib));

               // CASE 3a: Left sibling has keys to share.
               if (lsib->keyCount >= (rob->keyCount + 1) / 2)
               {
                  // Copy the parent key down to the child.
                  greturnFalseIf(
                     !_NodeInsertKey(
                        rob,
                        child,
                        0,
                        &(node->keyList[rob->keySize * (index - 1)]),
                        node->indexList[index - 1]));
                  child->nodeList[0] = lsib->nodeList[lsib->keyCount];

                  // Move the sibling key to the parent.
                  gmemCopyOver(
                     &(lsib->keyList[rob->keySize * (lsib->keyCount - 1)]),
                     rob->keySize,
                     &(node->keyList[rob->keySize * (index - 1)]));//lint !e679
                  node->indexList[index - 1] = lsib->indexList[lsib->keyCount - 1];

                  // yank the sibling key.
                  greturnFalseIf(!_NodeRemoveKey(rob, lsib, (Gi4) (lsib->keyCount - 1)));

                  greturnFalseIf(!_NodeWrite(rob, node));
                  greturnFalseIf(!_NodeWrite(rob, child));
                  greturnFalseIf(!_NodeWrite(rob, lsib));

                  _NodeCopy(rob, child, node);

                  _NodeDloc(child);
                  _NodeDloc(lsib);
                  continue;
               }
            }

            // Didn't find anything on the left side.  Try the right.
            if (index < node->keyCount)
            {
               rsib  = gleakCloc(_NodeCloc(rob), gsizeof(GioRobNode));

               rsib->index = node->nodeList[index + 1];
               greturnFalseIf(!_NodeRead(rob, rsib));

               // CASE 3a: right sibling has keys to share.
               if (rsib->keyCount >= (rob->keyCount + 1) / 2)
               {
                  if (lsib)
                  {
                     _NodeDloc(lsib);
                  }

                  // Copy the parent key down to the child.
                  greturnFalseIf(
                     !_NodeInsertKey(
                        rob,
                        child,
                        (Gi4) child->keyCount,
                        &(node->keyList[rob->keySize * index]),
                        node->indexList[index]));
                  child->nodeList[child->keyCount] = rsib->nodeList[0];

                  // Move the sibling key to the parent.
                  gmemCopyOver(
                     &(rsib->keyList[rob->keySize * 0]),
                     rob->keySize,
                     &(node->keyList[rob->keySize * index]));//lint !e835 !e941
                  node->indexList[index] = rsib->indexList[0];

                  // yank the sibling key.
                  /* needed because _NodeRemoveKey doesn't overwrite
                  ** the index'th node pointer.*/
                  rsib->nodeList[0] = rsib->nodeList[1];
                  greturnFalseIf(!_NodeRemoveKey(rob, rsib, 0));

                  greturnFalseIf(!_NodeWrite(rob, node));
                  greturnFalseIf(!_NodeWrite(rob, child));
                  greturnFalseIf(!_NodeWrite(rob, rsib));

                  _NodeCopy(rob, child, node);

                  _NodeDloc(child);
                  _NodeDloc(rsib);
                  continue;
               }
            }

            // CASE 3b: Neither fit the profile.  Merge with the left or right sibling.
            if (lsib)
            {
               GioRubData *data;

               if (rsib)
               {
                  _NodeDloc(rsib);
               }

               greturnValIf(!_NodeMerge(rob, node, (Gi4) index - 1, lsib, child), gbFALSE);

               // Root node is empty.  Pop it off.
               if (node->index    == rob->rootNodeIndex &&
                   node->keyCount == 0)
               {
                  rob->rootNodeIndex = lsib->index;

                  data = gioRubGetData(rob->rub, node->index);
                  greturnValIf(!gioRubDlocData(rob->rub, data), gbFALSE);

                  greturnValIf(!_HeaderWrite(rob), gbFALSE);
               }
               // Root node still has data.
               else
               {
                  greturnValIf(!_NodeWrite(rob, node), gbFALSE);
               }

               greturnValIf(!_NodeWrite(rob, lsib), gbFALSE);

               data = gioRubGetData(rob->rub, child->index);
               greturnValIf(!gioRubDlocData(rob->rub, data), gbFALSE);

               _NodeDloc(child);

               // Continue with the removal of the key.
               _NodeCopy(rob, lsib, node);
               _NodeDloc(lsib);
            }
            else if (rsib)
            {
               GioRubData *data;

               greturnValIf(!_NodeMerge(rob, node, (Gi4) index, child, rsib), gbFALSE);

               // Root node is empty.  Pop it off.
               if (node->index    == rob->rootNodeIndex &&
                   node->keyCount == 0)
               {
                  rob->rootNodeIndex = child->index;

                  data = gioRubGetData(rob->rub, node->index);
                  greturnValIf(!gioRubDlocData(rob->rub, data), gbFALSE);

                  greturnValIf(!_HeaderWrite(rob), gbFALSE);
               }
               // Root node still has data.
               else
               {
                  greturnValIf(!_NodeWrite(rob, node), gbFALSE);
               }
               greturnValIf(!_NodeWrite(rob, child), gbFALSE);

               data = gioRubGetData(rob->rub, rsib->index);
               greturnValIf(!gioRubDlocData(rob->rub, data), gbFALSE);

               _NodeDloc(rsib);

               // Continue with the removal of the key.
               _NodeCopy(rob, child, node);
               _NodeDloc(child);
            }
            else
            {
               debugHalt("Both LSIB and RSIB are NULL!?!");
               greturn gbFALSE;
            }
         }
         // Continue with the new node.
         else
         {
            _NodeCopy(rob, child, node);
            _NodeDloc(child);
         }
      }
   }
}

/**************************************************************************************************
func: _NodeRemoveKey

Remove a key from a node.  Node pointers favour the left child and
the right is lost.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

index
   Gi4
   in
   the key to remove.

return:
Gi4
**************************************************************************************************/
static Gb _NodeRemoveKey(const GioRob * const rob, GioRobNode * const node, const Gi4 index)
{
   genter;

   gmemCopyOver(
      &(node->keyList[rob->keySize * (index + 1)]),
      rob->keySize * (rob->keyCount - (index - 1)),
      &(node->keyList[rob->keySize * index]));//lint !e647 !e737 !e679
   gmemCopyOverTypeArray(
      &(node->indexList[index + 1]),
      Gn8,
      rob->keyCount - (index - 1),
      &(node->indexList[index]));//lint !e737 !e679
   gmemCopyOverTypeArray(
      &(node->nodeList[index + 2]),
      Gn8,
      rob->keyCount - (index - 1),
      &(node->nodeList[index + 1]));//lint !e737 !e679

   // Null out the last item.
   if (node->keyCount == rob->keyCount)
   {
      gmemClear(
         &(node->keyList[rob->keySize * (rob->keyCount - 1)]),
         rob->keySize);//lint !e679
      node->indexList[rob->keyCount - 1] = 0;
      node->nodeList[rob->keyCount]      = 0;
   }

   node->keyCount = node->keyCount - 1;

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeSearch

Search the tree.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode *
   in
   The current node.

key
   char *
   in
   The key to find.

return:
GioRobData *
**************************************************************************************************/
static GioRobData *_NodeSearch(const GioRob * const rob, GioRobNode * const node, const Gchar1 * const key)
{
   Gi8          index;
   Gi8          blockIndex;
   GioRobData  *data;

   genter;

   loop
   {
      // Search the node for the key.
      index = _NodeSearchKey(rob, node, key);

      // Found the key.
      if (0 <= index && index < rob->keyCount)
      {
         blockIndex = node->indexList[index];
         break;
      }

      // Sub node search if there are any more subnodes to search.
      if (index < 0 &&
          node->nodeList[0])
      {
         index    = -(index + 1);
         node->index = node->nodeList[index];
         greturnValIf(!_NodeRead(rob, node), NULL);
      }
      // No match at all.
      else
      {
         greturn NULL;
      }
   }

   // Found the index to the data.
   data = gleakCloc(_DataCloc(rob), gsizeof(GioRobData));
   greturnValIf(!data, NULL);

   // Get the data.
   data->index = blockIndex;
   if (!_DataRead(rob, data))
   {
      _DataDestroy(data);
      greturn NULL;
   }

   greturn data;
}

/**************************************************************************************************
func: _NodeSearchKey

Find the index in the node that best places the key.

param:


return:
Gi8
   >=0    - One of the keys matches directly.
   <0     - ABS(value) - 1 is one of the indices to a sub node.
   Gi8MAX - No sub nodes, no keys, nothing applicable.
**************************************************************************************************/
static Gi8 _NodeSearchKey(const GioRob * const rob, const GioRobNode * const node, const Gchar1 * const key)
{
   Gi4    min,
          max,
          mid,
          value;

   genter;

   // Nothing to search.
   if      (node->keyCount == 0)
   {
      greturn Gi8MAX;
   }

   // One key.
   else if (node->keyCount == 1)
   {
      // Compare the keys.
      value = charCompare((size_t) rob->keySize, (char *) key, (char *) node->keyList);

      // Found the match.
      if (value == 0)
      {
         greturn 0;
      }
      else
      {
         // Get the appropriate node.
         if (value < 0)
         {
            greturn -1;
         }
         else
         {
            greturn -2;
         }
      }
   }

   // More than one key.
   else
   {
      // Binary search the nodes for the key.
      min  = 0;
      max  = node->keyCount - 1;
      mid  = (min + max) / 2;

      loop
      {
         // Compare the keys.
         value = charCompare(
            (size_t) rob->keySize,
            (char *) key,
            (char *) &(node->keyList[mid * rob->keySize]));

         // Keys are equal.
         if (value == 0)
         {
            greturn mid;
         }

         // We've hit a the closest match.
         if (min == max)
         {
            // Get the appropriate sub node.
            if (value < 0)
            {
               greturn -(min + 1);//lint !e776
            }
            else
            {
               greturn -(min + 2);//lint !e776
            }
         }

         // Less than.
         if (value < 0)
         {
            max = gMAX(min, mid - 1);
         }
         else
         {
            min = gMIN(max, mid + 1);
         }

         // Get new mid.
         mid = (min + max) / 2;
      }
   }
}

/**************************************************************************************************
func: _NodeSetKey

Set the key value in the node.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

index
   Gi4
   in
   the child node to split.

key, keyIndex
   char *, Gn8
   in, in
   The key information.
**************************************************************************************************/
static void _NodeSetKey(const GioRob * const rob, const GioRobNode * const node, const Gi4 index, const Gchar1 * const key, const Gn8 keyIndex)
{
   genter;

   gmemCopyOver(
      key,
      rob->keySize,
      &(node->keyList[rob->keySize * index]));//lint !e679 !e737
   node->indexList[index] = keyIndex;

   _KeyClean(rob, &(node->keyList[rob->keySize * index]));//lint !e679 !e737
   greturn;
}

/**************************************************************************************************
func: _NodeSplitChild

Split a child node.

    X   To        X
    |            / \
    Y           Z   Y

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

index
   Gi4
   in
   the child node to split.

return:
Gi4
**************************************************************************************************/
static Gb _NodeSplitChild(const GioRob * const rob, GioRobNode * const parent, const Gi4 index, GioRobNode * const child, GioRobNode * const child2ndhalf)
{
   GioRobNode *node;
   GioRubData *data;

   genter;

   // Create a new z node .
   data = gioRubClocData(rob->rub, _nodeId, _NodeGetSize(rob));
   node = child2ndhalf;
   node->index = gioRubDataGetIndex(data);
   gioRubDataDloc(data);

   /* The odd math is for odd key counts.
   ** 5 => node->keyCount = 2
   ** 4 => node->keyCount = 1 */
   child->keyCount = ((child->keyCount + 1) / 2) - 1;
   /* We add 1 to key count for the odd values.
   ** 5 => child->keyCount = 2
   ** 4 => child->keyCount = 2 (leaves one key that moves up to the parent.)*/
   node->keyCount = rob->keyCount - (child->keyCount - 1);

   // Copy the keys from child over to child2ndhalf.
   gmemCopyOver(
      &(child->keyList[rob->keySize * (child->keyCount + 1)]),
      rob->keySize * node->keyCount,
      node->keyList);//lint !e647 !e679
   gmemCopyOverTypeArray(
      &(child->indexList[child->keyCount + 1]),
      Gn8,
      node->keyCount,
      node->indexList);//lint !e679
   gmemCopyOverTypeArray(
      &(child->nodeList[child->keyCount + 1]),
      Gn8,
      node->keyCount + 1,
      node->nodeList);//lint !e776 !e679

   // Adjust the parent to include the new child.
   greturnValIf(
         !_NodeInsertKey(
            rob,
            parent,
            index,
            &(child->keyList[rob->keySize * child->keyCount]),
            child->indexList[child->keyCount]),
      gbFALSE);//lint !e679

   parent->nodeList[index + 1] = node->index;//lint !e679

   // Shift the child values.
   // zero out the unused stuff.
   gmemClear(
      &(child->keyList[rob->keySize * child->keyCount]),
      rob->keySize * (rob->keyCount - child->keyCount));//lint !e679
   gmemClearTypeArray(
      &(child->indexList[child->keyCount]),
      Gn8,
      rob->keyCount - child->keyCount);
   gmemClearTypeArray(
      &(child->nodeList[child->keyCount + 1]),
      Gn8,
      rob->keyCount - child->keyCount);//lint !e679

   // Ordered to hopefully reduce the chance of knobbling the file too badly.
   greturnValIf(!_NodeWrite(rob, node),   gbFALSE);
   greturnValIf(!_NodeWrite(rob, parent), gbFALSE);
   greturnValIf(!_NodeWrite(rob, child),  gbFALSE);

   greturn gbTRUE;
}

/**************************************************************************************************
func: _NodeWrite

Write out the node.

param:
rob
   GioRob *
   in
   The file.

node
   GioRobNode
   in
   The node.

return:
Gi4
**************************************************************************************************/
static Gb _NodeWrite(const GioRob * const rob, const GioRobNode * const node)
{
   Gfile    *file;
   GioRubData *data;

   genter;

   data = gioRubGetData(rob->rub, node->index);
   file = gioRubLockOn(rob->rub, data);

   greturnValIf(!gfileSet4(file, 1,                     (Gp *) &(node->keyCount)),     gbFALSE); //lint !e960 !e9005
   greturnValIf(!gfileSet( file, (rob->keyCount * rob->keySize), node->keyList, NULL), gbFALSE); //lint !e647
   greturnValIf(!gfileSet8(file, rob->keyCount,        (Gp *)   node->indexList),     gbFALSE);
   greturnValIf(!gfileSet8(file, (rob->keyCount + 1),   (Gp *)   node->nodeList),      gbFALSE); //lint !e776

   greturnValIf(!gioRubLockOff(rob->rub), gbFALSE);
   gioRubDataDloc(data);

   greturn gbTRUE;
}

