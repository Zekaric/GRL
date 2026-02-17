/**************************************************************************************************
file:         GvTree
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
static void        _NodeDloc(          GvTree       * const tree, GvTreeItem * const value);

static GvTreeItem *_NodeGetLeftMost(   GvTreeItem const * const node);
static GvTreeItem *_NodeGetRightMost(  GvTreeItem const * const node);

static void        _NodeHeapify(       GvTree       * const tree, GvTreeItem * const value);

static void        _NodeRemove(        GvTree       * const tree, GvTreeItem * const value);
static void        _NodeRotateUp(      GvTree       * const tree, GvTreeItem * const value);

#if defined(_DEBUG)
static void        _Dump(              GvTreeItem const * const node, Gi4 const level, Gs * const str);
#endif

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gvTreeAdd
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeAdd(GvTree * const tree, Gv const value)
{
   GvTreeItem *node,
              *nodeNew = NULL;
   Gcompare    result;

   genter;

   // Cloc the new node.
   nodeNew = gmemClocType(GvTreeItem);
   greturnNullIf(!nodeNew);

   nodeNew->heapValue = (GheapN) grandomGetN(NULL);
   nodeNew->owner     = tree;

   nodeNew->v = value;

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

      result = tree->compareFunc(&value, &node->v);
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
func: gvTreeCloc
**************************************************************************************************/
grlAPI GvTree *gvTreeCloc_(Char const * const typeName, GrlCompareFunc const compareFunc)
{
   GvTree *tree;

   genter;

   greturnFalseIf(!compareFunc);

   tree = gmemClocType(GvTree);
   greturnNullIf(!tree);

   if (!gvTreeClocContent_(tree, typeName, compareFunc))
   {
      gvTreeDloc(tree);
      greturn NULL;
   }

   greturn tree;
}

/**************************************************************************************************
func: gvTreeClocContent
**************************************************************************************************/
grlAPI Gb gvTreeClocContent_(GvTree * const tree, Char const * const typeName,
   GrlCompareFunc const compareFunc)
{
   genter;

   greturnFalseIf(
      !tree ||
      !compareFunc);

   gmemClearType(tree, GvTree);

   typeName;
   GTYPE_SET(tree, typeName);

   tree->compareFunc = compareFunc;

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvTreeDloc
**************************************************************************************************/
grlAPI void gvTreeDloc(GvTree * const tree)
{
   genter;

   greturnIf(!tree);

   gvTreeDlocContent(tree);

   gmemDloc(tree);

   greturn;
}

/**************************************************************************************************
func: gvTreeDestoryContent
**************************************************************************************************/
grlAPI void gvTreeDlocContent(GvTree * const tree)
{
   GvTreeItem *node,
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
func: gvTreeErase
**************************************************************************************************/
grlAPI Gb gvTreeErase(GvTree * const tree, Gv const value)
{
   GvTreeItem *node;

   genter;

   greturnFalseIf(!tree);

   node = gvTreeFind(tree, value);
   greturnFalseIf(!node);

   _NodeDloc(tree, node);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvTreeEraseBegin
**************************************************************************************************/
grlAPI Gb gvTreeEraseBegin(GvTree * const tree)
{
   GvTreeItem *node;

   genter;

   greturnFalseIf(!tree);

   node = gvTreeGetBegin(tree);
   greturnFalseIf(!node);

   _NodeDloc(tree, node);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvTreeEraseEnd
**************************************************************************************************/
grlAPI Gb gvTreeEraseEnd(GvTree * const tree)
{
   GvTreeItem *node;

   genter;

   greturnFalseIf(!tree);

   node = gvTreeGetEnd(tree);
   greturnFalseIf(!node);

   _NodeDloc(tree, node);

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvTreeFlush
**************************************************************************************************/
grlAPI void gvTreeFlush(GvTree * const tree)
{
   genter;

   loop
   {
      breakIf(tree->count > 0);

      gvTreeEraseBegin(tree);
   }

   greturn;
}

/**************************************************************************************************
func: gvTreeForEach
**************************************************************************************************/
grlAPI Gb gvTreeForEach(GvTree const * const tree, GrlForEachFunc const func)
{
   GvTreeItem *node;
   Gp         *p;

   genter;

   greturnFalseIf(
      !tree ||
      !func);

   node = gvTreeGetBegin(tree);

   loop
   {
      breakIf(!node);

      p = (Gp *) &(node[1]);
      func(p);

      node = gvTreeItemGetNext(node);
   }

   greturn gbTRUE;
}

/**************************************************************************************************
func: gvTreeFind
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeFind(GvTree const * const tree, Gv const value)
{
   GvTreeItem *node;
   Gcompare    result;

   genter;

   node = tree->root;

   loop
   {
      greturnNullIf(!node);

      result = tree->compareFunc(&value, &node->v);
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
func: gvTreeGetBegin
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeGetBegin(GvTree const * const tree)
{
   GvTreeItem *node,
              *result;

   genter;

   node = tree->root;
   greturnNullIf(!node);

   result = _NodeGetLeftMost(node);

   greturn result;
}

/**************************************************************************************************
func: gvTreeGetCount
**************************************************************************************************/
grlAPI Gcount gvTreeGetCount(GvTree const * const tree)
{
   genter;

   greturn0If(!tree);

   greturn tree->count;
}

/**************************************************************************************************
func: gvTreeGetEnd
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeGetEnd(GvTree const * const tree)
{
   GvTreeItem *node;

   genter;

   node = tree->root;
   greturnNullIf(!node);

   greturn _NodeGetRightMost(node);
}

/**************************************************************************************************
func: gvTreeItemGet
**************************************************************************************************/
grlAPI Gv gvTreeItemGet(GvTreeItem const * const treeItem)
{
   Gv zero = { 0 };

   genter;

   greturnValIf(!treeItem, zero);

   greturn treeItem->v;
}

/**************************************************************************************************
func: gvTreeItemGetNext
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeItemGetNext(GvTreeItem const * const treeItem)
{
   GvTreeItem const *node;

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

   greturn (GvTreeItem *) node;
}

/**************************************************************************************************
func: gvTreeItemGetPrev
**************************************************************************************************/
grlAPI GvTreeItem *gvTreeItemGetPrev(GvTreeItem const * const treeItem)
{
   GvTreeItem const *node;

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

   greturn (GvTreeItem *) node;
}

#if defined(_DEBUG)
/**************************************************************************************************
func: gvTreeDump
**************************************************************************************************/
static void _Dump(GvTreeItem const * const node, Gi4 const level, Gs * const str)
{
   Gs *stemp;

   genter;

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
         gsParamTypeA, "[R]",   gsParamTypeS_DLOC, gsClocFromN(gvGetN(node->v)),
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

grlAPI Gs *gvTreeDump(GvTree const * const tree)
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
static void _NodeDloc(GvTree * const tree, GvTreeItem * const node)
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
static GvTreeItem *_NodeGetLeftMost(GvTreeItem const * const node)
{
   GvTreeItem *left;

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
static GvTreeItem *_NodeGetRightMost(GvTreeItem const * const node)
{
   GvTreeItem *right;

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
static void _NodeHeapify(GvTree * const tree, GvTreeItem * const node)
{
   GvTreeItem const *parent;

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
static void _NodeRotateUp(GvTree * const tree, GvTreeItem * const node)
{
   GvTreeItem *parent,
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
static void _NodeRemove(GvTree * const tree, GvTreeItem * const node)
{
   GvTreeItem *childLeft,
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
