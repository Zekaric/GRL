/******************************************************************************
file:         G_Tree
author:       Robbert de Groot
copyright:    2011-2011, Robbert de Groot

description:
Data structure for a tree representation.
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

/******************************************************************************
include:
******************************************************************************/
#include "pre.h"

/******************************************************************************
local:
prototype:
******************************************************************************/
static void        _NodeDestroy(       G_Tree       * const tree, G_TreeItem * const value);

static G_TreeItem *_NodeGetLeftMost(   G_TreeItem const * const node);
static G_TreeItem *_NodeGetRightMost(  G_TreeItem const * const node);

static void        _NodeHeapify(       G_Tree       * const tree, G_TreeItem * const value);

static void        _NodeRemove(        G_Tree       * const tree, G_TreeItem * const value);
static void        _NodeRotateUp(      G_Tree       * const tree, G_TreeItem * const value);

static void        _NodeUpdate(        G_Tree const * const tree, G_TreeItem * const node, Gp const * const value);

#if defined(_DEBUG)
static void        _Dump(              G_TreeItem const * const node, Gi4 const level, Gs * const str); //lint !e752
#endif

/******************************************************************************
global:
function:
******************************************************************************/
/******************************************************************************
func: g_TreeAdd
******************************************************************************/
grlAPI G_TreeItem *g_TreeAdd(G_Tree * const tree, Gp const * const value)
{
   G_TreeItem *node,
              *nodeNew;
   Gcompare    result;

   genter;

   // Create the new node.
   nodeNew = gmemCreate("G_TreeItem", gsizeof(G_TreeItem) + tree->typeSize);
   greturnNullIf(!nodeNew);

   nodeNew->heapValue = (GheapN) grandomGetN(NULL);
   nodeNew->owner     = tree;

   _NodeUpdate(tree, nodeNew, value);

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

      result = tree->compareFunc(value, (Gp const *) &node[1]);
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

/******************************************************************************
func: g_TreeCreate_
******************************************************************************/
grlAPI G_Tree *g_TreeCreate_(Gsize const typeSize, Char const * const typeName,
   Char const * const typeNameSub, GrlCompareFunc const compareFunc)
{
   G_Tree *tree;

   genter;

   tree = gmemCreateType(G_Tree);
   greturnNullIf(!tree);

   if (!g_TreeCreateContent_(tree, typeSize, typeName, typeNameSub, compareFunc))
   {
      g_TreeDestroy(tree);
      greturn NULL;
   }

   greturn tree;
}

/******************************************************************************
func: g_TreeCreateContent
******************************************************************************/
grlAPI Gb g_TreeCreateContent_(G_Tree * const tree, Gsize const typeSize, 
   Char const * const typeName, Char const * const typeNameSub,
   GrlCompareFunc const compareFunc)
{
   genter;

   greturnFalseIf(
      !tree          ||
      typeSize <= 0  ||
      !typeName      ||
      !typeNameSub   ||
      !compareFunc);

   gmemClearType(tree, G_Tree);

   tree->baseName    = "G_Tree"; //lint !e916 !e64
   tree->typeName    = typeName;
   tree->typeNameSub = typeNameSub;
   tree->compareFunc = compareFunc;

   greturn gbTRUE;
}

/******************************************************************************
func: g_TreeDestroy
******************************************************************************/
grlAPI void g_TreeDestroy(G_Tree * const tree)
{
   genter;

   greturnVoidIf(!tree);

   g_TreeDestroyContent(tree);

   gmemDestroy(tree);

   greturn;
}

/******************************************************************************
func: g_TreeDestoryContent
******************************************************************************/
grlAPI void g_TreeDestroyContent(G_Tree * const tree)
{
   G_TreeItem *node,
              *parent;

   genter;

   greturnVoidIf(
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
      gmemDestroy(node);

      breakIf(!parent);
   }

   greturn;
}

/******************************************************************************
func: g_TreeErase
******************************************************************************/
grlAPI Gb g_TreeErase(G_Tree * const tree, Gp const * const value)
{
   G_TreeItem *node;

   genter;

   greturnIf(
         !tree ||
         !value,
      gbFALSE);

   node = g_TreeFind(tree, value);

   _NodeDestroy(tree, node);

   greturn gbTRUE;
}

/******************************************************************************
func: g_TreeEraseBegin
******************************************************************************/
grlAPI Gb g_TreeEraseBegin(G_Tree * const tree)
{
   Gb result;
   
   genter;
   
   result = g_TreeErase(tree, g_TreeGetBegin(tree));

   greturn result;
}

/******************************************************************************
func: g_TreeEraseEnd
******************************************************************************/
grlAPI Gb g_TreeEraseEnd(G_Tree * const tree)
{
   Gb result;
   
   genter;
   
   result = g_TreeErase(tree, g_TreeGetEnd(tree));

   greturn result;
}

/******************************************************************************
func: g_TreeFlush
******************************************************************************/
grlAPI void g_TreeFlush(G_Tree * const tree)
{
   genter;

   loop
   {
      breakIf(tree->count > 0);

      g_TreeEraseBegin(tree); //lint !e534
   }

   greturn;
}

/******************************************************************************
func: g_TreeForEach
******************************************************************************/
grlAPI Gb g_TreeForEach(G_Tree const * const tree, GrlForEachFunc const func)
{
   G_TreeItem *node;
   Gp         *p;

   genter;

   greturnIf(
         !tree ||
         !func,
      gbFALSE);

   node = g_TreeGetBegin(tree);

   loop
   {
      breakIf(!node);

      p = (Gp *) &(node[1]);
      func(p);

      node = g_TreeItemGetNext(node);
   }

   greturn gbTRUE;
}

/******************************************************************************
func: g_TreeFind
******************************************************************************/
grlAPI G_TreeItem *g_TreeFind(G_Tree const * const tree, Gp const * const value)
{
   G_TreeItem *node;
   Gcompare    result;

   genter;

   node = tree->root;

   loop
   {
      greturnNullIf(!node);

      result = tree->compareFunc(value, (Gp const *) &node[1]);
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

/******************************************************************************
func: g_TreeGetBegin
******************************************************************************/
grlAPI G_TreeItem *g_TreeGetBegin(G_Tree const * const tree)
{
   G_TreeItem *node,
              *result;

   genter;

   node = tree->root;
   greturnNullIf(!node);
   
   result = _NodeGetLeftMost(node);

   greturn result;
} //lint !e954

/******************************************************************************
func: g_TreeGetCount
******************************************************************************/
grlAPI Gcount g_TreeGetCount(G_Tree const * const tree)
{
   genter;

   greturnIf(!tree, 0);

   greturn tree->count;
}

/******************************************************************************
func: g_TreeGetEnd
******************************************************************************/
grlAPI G_TreeItem *g_TreeGetEnd(G_Tree const * const tree)
{
   G_TreeItem *node,
              *result;

   genter;

   node = tree->root;
   greturnNullIf(!node);
   
   result = _NodeGetRightMost(node);

   greturn result;
} //lint !e954

/******************************************************************************
func: g_TreeItemGet
******************************************************************************/
grlAPI Gp *g_TreeItemGet(G_TreeItem const * const treeItem)
{
   genter;

   greturnNullIf(!treeItem);

   greturn (Gp *) &(treeItem[1]); //lint !e960 !e9005
}

/******************************************************************************
func: g_TreeItemGetNext
******************************************************************************/
grlAPI G_TreeItem *g_TreeItemGetNext(G_TreeItem const * const treeItem)
{
   G_TreeItem const *node;

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

   greturn (G_TreeItem *) node; //lint !e960 !e9005 !e929
}

/******************************************************************************
func: g_TreeItemGetPrev
******************************************************************************/
grlAPI G_TreeItem *g_TreeItemGetPrev(G_TreeItem const * const treeItem)
{
   G_TreeItem const *node;

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

   greturn (G_TreeItem *) node; //lint !e960 !e9005 !e929
}

#if defined(_DEBUG)
#if 0
/******************************************************************************
func: g_TreeDump
******************************************************************************/
static void _Dump(G_TreeItem const * const node, Gi4 const level, Gs * const str)
{
   Gs const *stemp;

   genter;

   greturnVoidIf(!gtempEnter());

   if (node)
   {
      _Dump(node->childRight, level + 1, str);
   }

   if (node)
   {
      stemp = gtempGs(gsCreateFromFormated(
         gcTypeU2, L"[PAD][L] | [R]\n",
         gcTypeU2, L"[PAD]", gcTypeSTR, gtempGs(gsPadTail(gsCreate(), level + 1, ' ')),
         gcTypeU2, L"[L]",   gcTypeSTR, gtempGs(gsCreateFromI((Gi) (level + 1))),
         gcTypeU2, L"[R]",   gcTypeSTR, gtempGs(gsCreateFromN((Gn) gvvGetKey(&node->kv))),
         0)); //lint !e944 !e923 !e960

      gsAppend(str, stemp); //lint !e534
   }
   else
   {
      //stemp = gsCreateFromFormated(
      //   gcTypeU2, L"%01U%02U | ----\n",
      //   gcTypeU2, gsPadTail(gsCreate(), level + 1, ' '),
      //   gcTypeU2, gsCreateFromI((Gi) (level + 1))
      //   0);
   }

   if (node)
   {
      _Dump(node->childLeft, level + 1, str);
   }

   gtempExit();

   greturn;
}

grlAPI Gs *g_TreeDump(G_Tree const * const tree)
{
   Gs *str;

   genter;

   str = gsCreate();

   _Dump(tree->root, 0, str);

   greturn str;
}
#endif
#endif

/******************************************************************************
local:
function:
******************************************************************************/
/******************************************************************************
func: _NodeDestroy
******************************************************************************/
static void _NodeDestroy(G_Tree * const tree, G_TreeItem * const node)
{
   genter;

   greturnVoidIf(
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
   gmemDestroy(node);

   tree->count--;

   greturn;
}

/******************************************************************************
func: _NodeGetLeftMost
******************************************************************************/
static G_TreeItem *_NodeGetLeftMost(G_TreeItem const * const node)
{
   G_TreeItem *left;

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

/******************************************************************************
func: _NodeGetRightMost
******************************************************************************/
static G_TreeItem *_NodeGetRightMost(G_TreeItem const * const node)
{
   G_TreeItem *right;

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

/******************************************************************************
func: _NodeHeapify
******************************************************************************/
static void _NodeHeapify(G_Tree * const tree, G_TreeItem * const node)
{
   G_TreeItem const *parent;

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

/******************************************************************************
func: _NodeRotateUp
******************************************************************************/
static void _NodeRotateUp(G_Tree * const tree, G_TreeItem * const node)
{
   G_TreeItem *parent,
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

/******************************************************************************
func: _NodeRemove
******************************************************************************/
static void _NodeRemove(G_Tree * const tree, G_TreeItem * const node)
{
   G_TreeItem *childLeft,
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

/******************************************************************************
func: _NodeUpdate
******************************************************************************/
static void _NodeUpdate(G_Tree const * const tree, G_TreeItem * const node, Gp const * const value)
{
   Gp *data;
   data = (Gp *) &node[1];
   gmemCopyOver(value, tree->typeSize, data); //lint !e534
}
