/**************************************************************************************************
file:         G_Container
author:       Robbert de Groot
copyright:    2011-2012, Robbert de Groot

description:
The base for a dynamic arrrays.
**************************************************************************************************/

/**************************************************************************************************
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
**************************************************************************************************/

#if !defined(G_CONTAINERH)
#define      G_CONTAINERH

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/**************************************************************************************************
type:
**************************************************************************************************/
// This type is for debugging pursposes.  So you can cast any of the containers to this
// to see what the container actually is.
#define GCONTAINER_VAR                       \
   GTYPE_VAR;                                \
   Gb                       isPointerType;   \
   Gsize                    typeSize;        \
   Gcount                   count

typedef struct
{
   GCONTAINER_VAR;
} G_Container;

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/

#endif
