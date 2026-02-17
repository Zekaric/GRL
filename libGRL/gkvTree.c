/**************************************************************************************************
file:         GkvTree
author:       Robbert de Groot
copyright:    2011, Robbert de Groot

description:
Data structure for a tree representation.
**************************************************************************************************/

/**************************************************************************************************
MIT License

Copyright (c) 2011, Robbert de Groot

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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "pch.h"

/**************************************************************************************************
local:
prototype:
**************************************************************************************************/
static void           _NodeDloc(          GkvTree       * const tree, GkvTreeItem * const value);

static GkvTreeItem *_NodeGetLeftMost(   GkvTreeItem const * const node);
static GkvTreeItem *_NodeGetRightMost(  GkvTreeItem const * const node);

static void           _NodeHeapify(       GkvTree       * const tree, GkvTreeItem * const value);

static void           _NodeRemove(        GkvTree       * const tree, GkvTreeItem * const value);
static void           _NodeRotateUp(      GkvTree       * const tree, GkvTreeItem * const value);

#if defined(_DEBUG)
static void           _Dump(              GkvTreeItem const * const node, Gi4 const level, Gs * const str);
#endif

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gkvTreeAdd
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeAdd(GkvTree * const tree, Gk const * const key, Gv const value)
{
   GkvTreeItem *node,
               *nodeNew = NULL;
   Gcompare     result;

   genter;

   key;

   // Cloc the new node.
   nodeNew = gmemClocType(GkvTreeItem);
   greturnNullIf(!nodeNew);

   nodeNew->heapValue = (GheapN) grandomGetN(NULL);
   nodeNew->owner     = tree;
   gkvSetK(nodeNew->kv, key);
   gkvSetV(nodeNew->kv, value);

   // First node.
   if (!tree->root)
   {
      tree->root = nodeNew;
      greturn tree->root;
   }

   // Add to a mature tree.
   node = tree->root;

   loop
   {
      // What the...
      greturnNullIf(!node);

      result = tree->compareFunc(key, gkvGetK(node->kv));
      if (result == gcompareEQUAL)
      {
         debugHalt("What to do.");
         greturn node;
      }

      if (result == gcompareLESS_THAN)
      {
         if (!node->childLeft)
         {
            nodeNew->parent = node;
            node->childLeft = nodeNew;
            node            = nodeNew;
            break;
         }

         node = node->childLeft;
      }
      else
      {
         if (!node->childRight)
         {
            nodeNew->parent  = node;
            node->childRight = nodeNew;
            node             = nodeNew;
            break;
         }

         node = node->childRight;
      }
   }

   // Move the node to the proper heap level.
   _NodeHeapify(tree, node);

   greturn node;
}

/**************************************************************************************************
func: gkvTreeCloc
**************************************************************************************************/
grlAPI GkvTree *gkvTreeCloc_(Char const * const typeName, GrlCompareFunc const compareFunc)
{
   GkvTree *tree;

   genter;

   greturnNullIf(!compareFunc);

   tree = gmemClocType(GkvTree);
   greturnNullIf(!tree);

   if (!gkvTreeClocContent_(tree, typeName, compareFunc))
   {
      gkvTreeDloc(tree);
      greturn NULL;
   }

   greturn tree;
}

/**************************************************************************************************
func: gkvTreeClocContent
**************************************************************************************************/
grlAPI Gb gkvTreeClocContent_(GkvTree * const tree, Char const * const typeName,
   GrlCompareFunc const compareFunc)
{
   genter;

   greturnFalseIf(
      !tree ||
      !compareFunc);

   gmemClearType(tree, GkvTree);

   typeName;
   GTYPE_SET(tree, typeName);

   tree->compareFunc   = compareFunc;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvTreeDloc
**************************************************************************************************/
grlAPI void gkvTreeDloc(GkvTree * const tree)
{
   genter;

   greturnIf(!tree);

   gkvTreeDlocContent(tree);

   gmemDloc(tree);

   greturn;
}

/**************************************************************************************************
func: gkvTreeDestoryContent
**************************************************************************************************/
grlAPI void gkvTreeDlocContent(GkvTree * const tree)
{
   GkvTreeItem *node,
                 *parent;

   genter;

   greturnIf(
      !tree ||
      !tree->root);

   parent = tree->root;

   loop
   {
      // Find a leaf.
      loop
      {
         // Find Min
         if (parent->childLeft)
         {
            parent = parent->childLeft;
            continue;
         }

         // Find Right
         if (parent->childRight)
         {
            parent = parent->childRight;
            continue;
         }

         // Found a leaf.
         break;
      }

      // Delete leaf
      node   = parent;
      parent = node->parent;

      if (parent->childLeft == node)
      {
         parent->childLeft = NULL;
      }
      else
      {
         parent->childRight = NULL;
      }

      // destroy the node.
      gmemDloc(node);

      breakIf(!parent);
   }

   greturn;
}

/**************************************************************************************************
func: gkvTreeErase
**************************************************************************************************/
grlAPI Gb gkvTreeErase(GkvTree * const tree, Gk const * const key)
{
   GkvTreeItem *node;

   genter;

   greturnFalseIf(
      !tree ||
      !key);

   node = gkvTreeFind(tree, key);

   _NodeDloc(tree, node);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvTreeEraseBegin
**************************************************************************************************/
grlAPI Gb gkvTreeEraseBegin(GkvTree * const tree)
{
   Gb result;

   genter;

   result = gkvTreeErase(tree, gkvTreeGetBegin(tree));

   greturn result;
}

/**************************************************************************************************
func: gkvTreeEraseEnd
**************************************************************************************************/
grlAPI Gb gkvTreeEraseEnd(GkvTree * const tree)
{
   Gb result;

   genter;

   result = gkvTreeErase(tree, gkvTreeGetEnd(tree));

   greturn result;
}

/**************************************************************************************************
func: gkvTreeFlush
**************************************************************************************************/
grlAPI void gkvTreeFlush(GkvTree * const tree)
{
   genter;

   loop
   {
      breakIf(tree->count > 0);

      gkvTreeEraseBegin(tree);
   }

   greturn;
}

/**************************************************************************************************
func: gkvTreeForEach
**************************************************************************************************/
grlAPI Gb gkvTreeForEach(GkvTree const * const tree, GrlForEachKeyFunc const func)
{
   GkvTreeItem *node;

   genter;

   greturnFalseIf(
      !tree ||
      !func);

   node = gkvTreeGetBegin(tree);

   loop
   {
      breakIf(!node);

      func(gkvGetK(node->kv), &gkvGetV(node->kv));

      node = gkvTreeItemGetNext(node);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gkvTreeFind
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeFind(GkvTree const * const tree, Gk const * const key)
{
   GkvTreeItem *node;
   Gcompare     result;

   genter;

   node = tree->root;

   loop
   {
      greturnNullIf(!node);

      result = tree->compareFunc(key, gkvGetK(node->kv));
      breakIf(result == gcompareEQUAL);

      if (result == gcompareLESS_THAN)
      {
         node = node->childLeft;
      }
      else
      {
         node = node->childRight;
      }
   }

   greturn node;
}

/**************************************************************************************************
func: gkvTreeGetBegin
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeGetBegin(GkvTree const * const tree)
{
   GkvTreeItem *node;

   genter;

   node = tree->root;
   greturnNullIf(!node);

   greturn _NodeGetLeftMost(node);
}

/**************************************************************************************************
func: gkvTreeGetCount
**************************************************************************************************/
grlAPI Gcount gkvTreeGetCount(GkvTree const * const tree)
{
   genter;

   greturn0If(!tree);

   greturn tree->count;
}

/**************************************************************************************************
func: gkvTreeGetEnd
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeGetEnd(GkvTree const * const tree)
{
   GkvTreeItem *node;

   genter;

   node = tree->root;
   greturnNullIf(!node);

   greturn _NodeGetRightMost(node);
}

/**************************************************************************************************
func: gkvTreeItemGet
**************************************************************************************************/
grlAPI Gv gkvTreeItemGet(GkvTreeItem const * const treeItem)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(!treeItem, zero);

   greturn gkvGetV(treeItem->kv);
}

/**************************************************************************************************
func: gkvTreeItemGetKey
**************************************************************************************************/
grlAPI Gk const *gkvTreeItemGetKey(GkvTreeItem const * const treeItem)
{
   genter;

   greturnNullIf(!treeItem);

   greturn gkvGetK(treeItem->kv);
}

/**************************************************************************************************
func: gkvTreeItemGetNext
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeItemGetNext(GkvTreeItem const * const treeItem)
{
   GkvTreeItem const *node;

   genter;

   greturnNullIf(!treeItem);

   // find the left most child of the right substree.
   node = _NodeGetLeftMost(treeItem->childRight);
   if (!node)
   {
      node = treeItem;

      // Nothing on the right.
      // crawl up the tree.
      loop
      {
         if (!node->parent)
         {
            // node is root and is last item.
            node = NULL;
            break;
         }

         // current node is left child of parent,
         // parent is the next value.
         if (node->parent->childLeft == node)
         {
            node = node->parent;
            break;
         }

         node = node->parent;
      }
   }

   greturn (GkvTreeItem *) node;
}

/**************************************************************************************************
func: gkvTreeItemGetPrev
**************************************************************************************************/
grlAPI GkvTreeItem *gkvTreeItemGetPrev(GkvTreeItem const * const treeItem)
{
   GkvTreeItem const *node;

   genter;

   greturnNullIf(!treeItem);

   // find the right most child of the left subtree.
   node = _NodeGetRightMost(treeItem->childLeft);
   if (!node)
   {
      node = treeItem;

      // Nothing on the left.
      // craw up the tree.
      loop
      {
         if (!node->parent)
         {
            // node is root and is first item.
            node = NULL;
            break;
         }

         // current node is right child of parent,
         // parent is the previous value.
         if (node->parent->childRight == node)
         {
            node = node->parent;
            break;
         }

         node = node->parent;
      }
   }

   greturn (GkvTreeItem *) node;
}

/**************************************************************************************************
func: gkvTreeItemUpdate
**************************************************************************************************/
grlAPI Gb gkvTreeItemUpdate(GkvTreeItem * const treeItem, Gv const value)
{
   genter;

   greturnFalseIf(!treeItem);

   gkvSetV(treeItem->kv, value);

   greturn gbTRUE;
}

#if defined(_DEBUG)
/**************************************************************************************************
func: gkvTreeDump
**************************************************************************************************/
static void _Dump(GkvTreeItem const * const node, Gi4 const level, Gs * const str)
{
   Gs *stemp;

   genter;

   greturnIf(!gtempEnter());

   if (node)
   {
      _Dump(node->childRight, level + 1, str);
   }

   if (node)
   {
      stemp = gsClocFromFormatted(
         gsParamTypeA, "[PAD][L] | [R]\n",
         gsParamTypeA, "[PAD]", gsParamTypeS_DLOC, gsPadTail(gsCloc(), level + 1, ' '),
         gsParamTypeA, "[L]",   gsParamTypeS_DLOC, gsClocFromI((Gi) (level + 1)),
         gsParamTypeA, "[R]",   gsParamTypeS_DLOC, gsClocFromN(gvGetN(gkvGetV(node->kv))),
         gsParamTypeNONE);

      gsAppend(str, stemp);

      gsDloc(stemp);
   }
   else
   {
      stemp = gsClocFromFormatted(
         gsParamTypeA, "[PAD][L] | ----\n",
         gsParamTypeA, "[PAD]", gsParamTypeS_DLOC, gsPadTail(gsCloc(), level + 1, ' '),
         gsParamTypeA, "[L]",   gsParamTypeS_DLOC, gsClocFromI((Gi) (level + 1)),
         gsParamTypeNONE);
   }

   if (node)
   {
      _Dump(node->childLeft, level + 1, str);
   }

   greturn;
}

grlAPI Gs *gkvTreeDump(GkvTree const * const tree)
{
   Gs *str;

   genter;

   str = gsCloc();

   _Dump(tree->root, 0, str);

   greturn str;
}
#endif

/**************************************************************************************************
local:
function:
**************************************************************************************************/
/**************************************************************************************************
func: _NodeDloc
**************************************************************************************************/
static void _NodeDloc(GkvTree * const tree, GkvTreeItem * const node)
{
   genter;

   greturnIf(
      !tree ||
      !node);

   loop
   {
      // Break when node is at the leaf
      breakIf(
         node->childLeft  == NULL &&
         node->childRight == NULL);

      // Percolate the node down the tree.
      _NodeRemove(tree, node);
   }

   // Now we can remove the node.
   gmemDloc(node);

   tree->count--;

   greturn;
}

/**************************************************************************************************
func: _NodeGetLeftMost
**************************************************************************************************/
static GkvTreeItem *_NodeGetLeftMost(GkvTreeItem const * const node)
{
   GkvTreeItem *left;

   genter;

   left = node->childLeft;
   greturnNullIf(!left);

   loop
   {
      breakIf(left->childLeft == NULL);
      left = left->childLeft;
   }

   greturn left;
}

/**************************************************************************************************
func: _NodeGetRightMost
**************************************************************************************************/
static GkvTreeItem *_NodeGetRightMost(GkvTreeItem const * const node)
{
   GkvTreeItem *right;

   genter;

   right = node->childRight;
   greturnNullIf(!right);

   loop
   {
      breakIf(right->childRight == NULL);
      right = right->childRight;
   }

   greturn right;
}

/**************************************************************************************************
func: _NodeHeapify
**************************************************************************************************/
static void _NodeHeapify(GkvTree * const tree, GkvTreeItem * const node)
{
   GkvTreeItem const *parent;

   genter;

   loop
   {
      parent = node->parent;
      breakIf(!parent);

      breakIf(node->heapValue > parent->heapValue)

      // Time to rotate the tree.
      _NodeRotateUp(tree, node);
   }

   greturn;
}

/**************************************************************************************************
func: _NodeRotateUp
**************************************************************************************************/
static void _NodeRotateUp(GkvTree * const tree, GkvTreeItem * const node)
{
   GkvTreeItem *parent,
             *child;

   genter;

   parent = node->parent;

   //          parent             node
   //            /\                /\        //
   //        node  ...   =>       .  parent
   //         /\                       /\    //
   //        .  child             child  .
   //
   // Links that change...
   // 1 parent->parent     = node
   // 2 parent->childLeft  = child
   // 3 node->parent       = parent->parent
   // 4 node->childRight   = parent
   // 5 child->parent      = parent
   if (parent->childLeft == node)
   {
      // set the child.
      child             = node->childRight;

      // Rotate
      node->parent      = parent->parent;
      node->childRight  = parent;

      parent->childLeft = child;
      parent->parent    = node;

      child->parent     = parent;
   }
   //          parent                   node
   //            /\                      /\   //
   //           .  node  ...   =>  parent  .
   //               /\               /\       //
   //          child  .             .  child
   else
   {
      // set the child
      child = node->childLeft;

      node->parent       = parent->parent;
      node->childLeft    = parent;

      parent->childRight = child;
      parent->parent     = node;

      child->parent      = parent;
   }

   // Fix the parent's left, right
   if (node->parent)
   {
      if (node->parent->childRight == parent)
      {
         node->parent->childRight = node;
      }
      else
      {
         node->parent->childLeft = node;
      }
   }
   else
   {
      tree->root = node;
   }

   greturn;
}

/**************************************************************************************************
func: _NodeRemove
**************************************************************************************************/
static void _NodeRemove(GkvTree * const tree, GkvTreeItem * const node)
{
   GkvTreeItem *childLeft,
              *childRight,
              *swapNode,
              *parentTemp,
              *leftTemp,
              *rightTemp;

   genter;

   childLeft  = node->childLeft;
   childRight = node->childRight;

   if (!childLeft &&
       !childRight)
   {
      // Nothing to do.
      greturn;
   }

   if (childLeft &&
       !childRight)
   {
      // child left takes the nodes place.
      childLeft->parent = node->parent;
      if (node->parent == NULL)
      {
         tree->root = childLeft;
      }
      else
      {
         if (node->parent->childLeft == node)
         {
            node->parent->childLeft = childLeft;
         }
         else
         {
            node->parent->childRight = childLeft;
         }
      }

      node->parent     = NULL;
      node->childLeft  = NULL;
      node->childRight = NULL;
      greturn;
   }

   if (!childLeft &&
       childRight)
   {
      // child right take the node's place.
      childRight->parent = node->parent;
      if (node->parent == NULL)
      {
         tree->root = childRight;
      }
      else
      {
         if (node->parent->childLeft == node)
         {
            node->parent->childLeft = childRight;
         }
         else
         {
            node->parent->childRight = childRight;
         }
      }

      node->parent     = NULL;
      node->childLeft  = NULL;
      node->childRight = NULL;
      greturn;
   }

   // Get the previous child in the left subtree.
   swapNode = _NodeGetRightMost(childLeft);

   // Swap positions.
   parentTemp = node->parent;
   leftTemp   = node->childLeft;
   rightTemp  = node->childRight;

   // change the node.
   node->parent     = swapNode->parent;
   node->childLeft  = swapNode->childLeft;
   node->childRight = swapNode->childRight;
   // change all the items that point to node.
   if (parentTemp == NULL)
   {
      tree->root = swapNode;
   }
   else
   {
      if (parentTemp->childLeft == node)
      {
         parentTemp->childLeft = swapNode;
      }
      else
      {
         parentTemp->childRight = swapNode;
      }
   }
   leftTemp->parent  = swapNode;
   rightTemp->parent = swapNode;

   // Change the swapNode
   swapNode->parent     = parentTemp;
   swapNode->childLeft  = leftTemp;
   swapNode->childRight = rightTemp;
   // Change the items that point to sname node
   if (node->parent->childLeft == swapNode)
   {
      node->parent->childLeft = node;
   }
   else
   {
      node->parent->childRight = node;
   }
   if (node->childLeft)
   {
      node->childLeft->parent  = node;
   }
   if (node->childRight)
   {
      node->childRight->parent = node;
   }

   // swap heap values.
   swapNode->heapValue = node->heapValue;

   greturn;
}
