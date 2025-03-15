/**************************************************************************************************
file:       gmatrix3
author:     Robbert de Groot
copyright:  2001-2009, Robbert de Groot

description:
Functions for 4x4 matrices.
**************************************************************************************************/

/**************************************************************************************************
BSD 2-Clause License

Copyright (c) !!!!YEAR!!!!, Robbert de Groot
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

/**************************************************************************************************
include:
**************************************************************************************************/
#include "precompiled.h"

/**************************************************************************************************
global:
function:
**************************************************************************************************/
/**************************************************************************************************
func: gmatrix3Clean

Make sure small values are 0.
**************************************************************************************************/
grlAPI void gmatrix3Clean(Gmatrix3 const * const mi, Gmatrix3 * const mo)
{
   Gi4 a;

   genter;

   forCount(a, 16)
   {
      if (fabs(mi->value[a]) < gmathDOUBLE_TOLERANCE)
      {
         mo->value[a] = 0.;
      }
      else
      {
         mo->value[a] = mi->value[a];
      }
   }
   greturn;
}

/**************************************************************************************************
func: gmatrix3Copy
**************************************************************************************************/
grlAPI void gmatrix3Copy(Gmatrix3 const * const src, Gmatrix3 * const dst)
{
   genter;
   gmemCopyOverTypeArray(dst, Gr, 16, src);//lint !e960 !e9005 !e534
   greturn;
}

/**************************************************************************************************
func: gmatrix3Minus
**************************************************************************************************/
grlAPI void gmatrix3Minus(Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m)
{
   Gi4 a;

   genter;

   forCount(a, 16)
   {
      m->value[a] = m1->value[a] - m2->value[a];
   }
   greturn;
}

/**************************************************************************************************
func: gmatrix3Negate
**************************************************************************************************/
grlAPI void gmatrix3Negate(Gmatrix3 const * const m1, Gmatrix3 * const m)
{
   Gi4 a;

   genter;

   forCount(a, 16)
   {
      m->value[a] = -m1->value[a];
   }
   greturn;
}

/**************************************************************************************************
func: gmatrix3Plus
**************************************************************************************************/
grlAPI void gmatrix3Plus(Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m)
{
   Gi4 a;

   genter;

   forCount(a, 16)
   {
      m->value[a] = m1->value[a] + m2->value[a];
   }
   greturn;
}

/**************************************************************************************************
func: gmatrix3Product
**************************************************************************************************/
grlAPI void gmatrix3Product(Gmatrix3 const * const m1, Gmatrix3 const * const m2, Gmatrix3 * const m)
{
   Gmatrix3 mat;
   Gi4      a;

   genter;

   mat.value[0]  = m1->value[0] *m2->value[0] + m1->value[1] *m2->value[4] + m1->value[2] *m2->value[8]  + m1->value[3]*m2->value[12];
   mat.value[1]  = m1->value[0] *m2->value[1] + m1->value[1] *m2->value[5] + m1->value[2] *m2->value[9]  + m1->value[3]*m2->value[13];
   mat.value[2]  = m1->value[0] *m2->value[2] + m1->value[1] *m2->value[6] + m1->value[2] *m2->value[10] + m1->value[3]*m2->value[14];
   mat.value[3]  = m1->value[0] *m2->value[3] + m1->value[1] *m2->value[7] + m1->value[2] *m2->value[11] + m1->value[3]*m2->value[15];

   mat.value[4]  = m1->value[4] *m2->value[0] + m1->value[5] *m2->value[4] + m1->value[6] *m2->value[8]  + m1->value[7]*m2->value[12];
   mat.value[5]  = m1->value[4] *m2->value[1] + m1->value[5] *m2->value[5] + m1->value[6] *m2->value[9]  + m1->value[7]*m2->value[13];
   mat.value[6]  = m1->value[4] *m2->value[2] + m1->value[5] *m2->value[6] + m1->value[6] *m2->value[10] + m1->value[7]*m2->value[14];
   mat.value[7]  = m1->value[4] *m2->value[3] + m1->value[5] *m2->value[7] + m1->value[6] *m2->value[11] + m1->value[7]*m2->value[15];

   mat.value[8]  = m1->value[8] *m2->value[0] + m1->value[9] *m2->value[4] + m1->value[10]*m2->value[8]  + m1->value[11]*m2->value[12];
   mat.value[9]  = m1->value[8] *m2->value[1] + m1->value[9] *m2->value[5] + m1->value[10]*m2->value[9]  + m1->value[11]*m2->value[13];
   mat.value[10] = m1->value[8] *m2->value[2] + m1->value[9] *m2->value[6] + m1->value[10]*m2->value[10] + m1->value[11]*m2->value[14];
   mat.value[11] = m1->value[8] *m2->value[3] + m1->value[9] *m2->value[7] + m1->value[10]*m2->value[11] + m1->value[11]*m2->value[15];

   mat.value[12] = m1->value[12]*m2->value[0] + m1->value[13]*m2->value[4] + m1->value[14]*m2->value[8]  + m1->value[15]*m2->value[12];
   mat.value[13] = m1->value[12]*m2->value[1] + m1->value[13]*m2->value[5] + m1->value[14]*m2->value[9]  + m1->value[15]*m2->value[13];
   mat.value[14] = m1->value[12]*m2->value[2] + m1->value[13]*m2->value[6] + m1->value[14]*m2->value[10] + m1->value[15]*m2->value[14];
   mat.value[15] = m1->value[12]*m2->value[3] + m1->value[13]*m2->value[7] + m1->value[14]*m2->value[11] + m1->value[15]*m2->value[15];

   forCount(a, 16)
   {
      m->value[a] = mat.value[a];
   }
   greturn;
}

/**************************************************************************************************
func: gmatrix3ProductGvec3
**************************************************************************************************/
grlAPI void gmatrix3ProductGvec3(Gmatrix3 const * const m, Gvec3 const * const in,
   Gvec3 * const out)
{
   Gr tx,ty,tz;

   genter;

   tx = m->value[0] * in->a  +  m->value[1] * in->b  +  m->value[2]  * in->c  +  m->value[3];
   ty = m->value[4] * in->a  +  m->value[5] * in->b  +  m->value[6]  * in->c  +  m->value[7];
   tz = m->value[8] * in->a  +  m->value[9] * in->b  +  m->value[10] * in->c  +  m->value[11];

   out->a = tx;
   out->b = ty;
   out->c = tz;
   greturn;
}

/**************************************************************************************************
func: gmatrix3ProductGvec3List
**************************************************************************************************/
grlAPI void gmatrix3ProductGvec3List(Gmatrix3 const * const m, Gcount const pcount,
   Gvec3 const * const in, Gvec3 * const out)
{
   Gindex index;

   genter;

   forCount(index, pcount)
   {
      gmatrix3ProductGvec3(m, &(in[index]), &(out[index]));
   }

   greturn;
}

/**************************************************************************************************
func: gmatrix3SetFromUnitVectorsLocalToWorld
**************************************************************************************************/
grlAPI void gmatrix3SetFromUnitVectorsLocalToWorld(Gmatrix3 * const m,
   Gvec3 const * const x, Gvec3 const * const y, Gvec3 const * const z)
{
   genter;

   m->value[0]  = x->a;
   m->value[1]  = y->a;
   m->value[2]  = z->a;
   m->value[3]  = 0;

   m->value[4]  = x->b;
   m->value[5]  = y->b;
   m->value[6]  = z->b;
   m->value[7]  = 0;

   m->value[8]  = x->c;
   m->value[9]  = y->c;
   m->value[10] = z->c;
   m->value[11] = 0;

   m->value[12] = 0;
   m->value[13] = 0;
   m->value[14] = 0;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3SetFromUnitVectorsWorldToLocal

Create a change basis matrix based on three new direction vectors.
This will take poGis in world coordinates to the new coordinate
system.
**************************************************************************************************/
grlAPI void gmatrix3SetFromUnitVectorsWorldToLocal(Gmatrix3 * const m,
   Gvec3 const * const x, Gvec3 const * const y, Gvec3 const * const z)
{
   genter;

   m->value[0]  = x->a;
   m->value[1]  = x->b;
   m->value[2]  = x->c;
   m->value[3]  = 0;

   m->value[4]  = y->a;
   m->value[5]  = y->b;
   m->value[6]  = y->c;
   m->value[7]  = 0;

   m->value[8]  = z->a;
   m->value[9]  = z->b;
   m->value[10] = z->c;
   m->value[11] = 0;

   m->value[12] = 0;
   m->value[13] = 0;
   m->value[14] = 0;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3SetIdentity
**************************************************************************************************/
grlAPI void gmatrix3SetIdentity(Gmatrix3 * const m)
{
   genter;

   gmemClearType(m, Gmatrix3);

   m->value[0]  = 1;
   m->value[5]  = 1;
   m->value[10] = 1;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3SetRotation
**************************************************************************************************/
grlAPI void gmatrix3SetRotation(Gmatrix3 * const m, GmathAxis const axis, Gr const angle)
{
   genter;

   if (axis == gmathAxisX)
   {
      m->value[0]  = 1;
      m->value[1]  = 0;
      m->value[2]  = 0;

      m->value[4]  = 0;
      m->value[5]  = cos(angle);
      m->value[6]  = -sin(angle);

      m->value[8]  = 0;
      m->value[9]  = sin(angle);
      m->value[10] = cos(angle);
   }
   else if (axis == gmathAxisY)
   {
      m->value[0]  = cos(angle);
      m->value[1]  = 0;
      m->value[2]  = sin(angle);

      m->value[4]  = 0;
      m->value[5]  = 1;
      m->value[6]  = 0;

      m->value[8]  = -sin(angle);
      m->value[9]  = 0;
      m->value[10] = cos(angle);
   }
   else
   {
      m->value[0]  = cos(angle);
      m->value[1]  = -sin(angle);
      m->value[2]  = 0;

      m->value[4]  = sin(angle);
      m->value[5]  = cos(angle);
      m->value[6]  = 0;

      m->value[8]  = 0;
      m->value[9]  = 0;
      m->value[10] = 1;
   }

   m->value[3]  = 0;
   m->value[7]  = 0;
   m->value[11] = 0;
   m->value[12] = 0;
   m->value[13] = 0;
   m->value[14] = 0;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3SetScale
**************************************************************************************************/
grlAPI void gmatrix3SetScale(Gmatrix3 * const m, Gr const x, Gr const y, Gr const z)
{
   genter;

   m->value[0]  = x;
   m->value[1]  = 0;
   m->value[2]  = 0;
   m->value[3]  = 0;

   m->value[4]  = 0;
   m->value[5]  = y;
   m->value[6]  = 0;
   m->value[7]  = 0;

   m->value[8]  = 0;
   m->value[9]  = 0;
   m->value[10] = z;
   m->value[11] = 0;

   m->value[12] = 0;
   m->value[13] = 0;
   m->value[14] = 0;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3SetTranslation
**************************************************************************************************/
grlAPI void gmatrix3SetTranslation(Gmatrix3 * const m, Gr const x, Gr const y, Gr const z)
{
   genter;

   m->value[0]  = 1;
   m->value[1]  = 0;
   m->value[2]  = 0;
   m->value[3]  = x;

   m->value[4]  = 0;
   m->value[5]  = 1;
   m->value[6]  = 0;
   m->value[7]  = y;

   m->value[8]  = 0;
   m->value[9]  = 0;
   m->value[10] = 1;
   m->value[11] = z;

   m->value[12] = 0;
   m->value[13] = 0;
   m->value[14] = 0;
   m->value[15] = 1;
   greturn;
}

/**************************************************************************************************
func: gmatrix3Transpose
**************************************************************************************************/
grlAPI void gmatrix3Transpose(Gmatrix3 const * const in, Gmatrix3 * const out)
{
   Gmatrix3 temp;
   Gi4      a;

   genter;

   temp.value[0]  = in->value[0];  temp.value[1]  = in->value[4];  temp.value[2]  = in->value[8];   temp.value[3]  = in->value[12];
   temp.value[4]  = in->value[1];  temp.value[5]  = in->value[5];  temp.value[6]  = in->value[9];   temp.value[7]  = in->value[13];
   temp.value[8]  = in->value[2];  temp.value[9]  = in->value[6];  temp.value[10] = in->value[10];  temp.value[11] = in->value[14];
   temp.value[12] = in->value[3];  temp.value[13] = in->value[7];  temp.value[14] = in->value[11];  temp.value[15] = in->value[15];

   forCount(a, 16)
   {
      out->value[a] = temp.value[a];
   }
   greturn;
}


#if 0 // NEED TO CONVERT

/*******************************************************************************************************
 * func: mgMatrixDeterminant
 *
 * Finds the determinant of a NxN matrix.
 ******************************************************************************************************/
grlAPI Gmatrix3 mgMatrixDeterminant(Gr *M, Gi4 N)
{
   Gr *TM,
       Result      = 0;
   Gi4 a,
       b,
       c,
       d;

   genter;

   // 1x1 Matrix would yeild -M[0]
   if (N == 1)
   {
      greturn -M[0];
   }

   // Temporary Matrix to hold the sub matrix.
   TM = (Gr *) MSAlloc(gsizeof(Gr)*(N-1)*(N-1));
   if (TM == NULL)
   {
      greturn 0;
   }

   // Use the formula Sum(i=1,N){(-1)^i+1 * a(1,i) * det(A(1,i))}
   forCount(a, N)
   {
      if (M[a] == 0)
      {
         continue;
      }

      c = 0;
      forCount(b, N)
      {
         if (b != a)
         {
            for (d = 1; d < N; d++)
            {
               TM[c + (d-1)*(N-1)] = M[b + d*N];
            }
            c++;
         }
      }

      switch (a % 2)
      {
      case 0:
         Result += M[a] * mgMatrixDeterminant(TM, N-1);
         break;

      case 1:
         Result -= M[a] * mgMatrixDeterminant(TM, N-1);
      }
   }

   // Free up the temporary matrix
   MSFree(TM);

   greturn Result;
   greturn;
}


/*******************************************************************************************************
 * func: mgMatrixInverse
 *
 * Inverse the matrix. OutM * M = I
 * Returns: gbTRUE  - Matrix is inversed.
 *          gbFALSE - Could not inverse matrix.
 ******************************************************************************************************/
grlAPI void mgMatrixRowExchange(Gr *M, Gi4 N, Gi4 I, Gi4 J)
{
   Gr  Temp;
   Gi4 a;

   genter;

   forCount(a, N)
   {
         Temp           = M[a + (I)*(N)];
         M[a + (I)*(N)] = M[a + (J)*(N)];
         M[a + (J)*(N)] = Temp;
   }
   greturn;
}

grlAPI void mgMatrixRowScale(Gr *M, Gi4 N, Gi4 I, Gr S)
{
   Gi4 a;

   genter;

   forCount(a, N)
   {
      M[a + (I)*(N)] *= (S);
   }
   greturn;
}

grlAPI void mgMatrixRowScaleAndAdd(Gr *M, Gi4 N, Gi4 I, Gr S, Gi4 J)
{
   Gi4 a;

   genter;

   forCount(a, N)
   {
      M[a + (J)*(N)] += (S) * M[a + (I)*(N)];
   }
   greturn;
}

grlAPI Gb mgMatrixInvert(Gr *M, Gi4 N, Gr *OutM)
{
   Gr *IM,
      *JM;
   Gi4 a,
       b;
   Gr  DoubleTemp;

   genter;

   // if the determinant is non zero then there exists an inverse.
   if (mgMatrixDeterminant(M, N) == 0)
   {
      greturn gbFALSE;
   }

   // allocate temporary matrices
   IM = (Gr *) MSAlloc(gsizeof(Gr)*N*N);
   JM = (Gr *) MSAlloc(gsizeof(Gr)*N*N);
   if (IM == NULL || JM == NULL)
   {
      if (IM)
      {
         MSFree(IM);
      }
      if (JM)
      {
         MSFree(JM);
      }
      greturn gbFALSE;
   }

   // Initialize the buffers
   vmemCopy(M, IM, gsizeof(Gr)*N*N);
   forCount(a, N*N)
   {
      JM[a] = 0;
   }
   forCount(a, N)
   {
      JM[a + a*N] = 1;
   }

   // Invert the matrix using Gaussian elimination
   forCount(a, N)
   {
      // Find non zero element
      for (b = a; b < N; b++)
      {
         breakIf(fabs(IM[a + b*N]) >= 0.00001);
      }
      mgMatrixRowExchange(IM, N, a, b);
      mgMatrixRowExchange(JM, N, a, b);

      // Scale Row so that it's 0 ... 0 1 x ... x
      DoubleTemp = 1/IM[a + a*N];
      mgMatrixRowScale(IM, N, a, DoubleTemp);
      mgMatrixRowScale(JM, N, a, DoubleTemp);

      IM[a + a*N] = 1; // Avoid any precision errors

      // Make all other rows zero
      forCount(b, N)
      {
         if (b != a)
         {
            DoubleTemp = -IM[a + b*N];
            mgMatrixRowScaleAndAdd(IM, N, a, DoubleTemp, b);
            mgMatrixRowScaleAndAdd(JM, N, a, DoubleTemp, b);

            IM[a + b*N] = 0; // Avoid any precision errors
         }
      }
   }

   vmemCopy(JM, OutM, gsizeof(Gr)*N*N);

   MSFree(IM);
   MSFree(JM);

   greturn gbTRUE;
}
#endif
