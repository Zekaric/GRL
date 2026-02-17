/*
   A C-program for MT19937-64 (2004/9/29 version).
   Coded by Takuji Nishimura and Makoto Matsumoto.

   This is a 64-bit version of Mersenne Twister pseudorandom number
   generator.

   Before using, initialize the state by using init_genrand64(seed)
   or init_by_array64(init_key, key_length).

   Copyright (C) 2004, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   References:
   T. Nishimura, ``Tables of 64-bit Mersenne Twisters''
     ACM Transactions on Modeling and
     Computer Simulation 10. (2000) 348--357.
   M. Matsumoto and T. Nishimura,
     ``Mersenne Twister: a 623-dimensionally equidistributed
       uniform pseudorandom number generator''
     ACM Transactions on Modeling and
     Computer Simulation 8. (Jan. 1998) 3--30.

   Any feedback is very welcome.
   http://www.math.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove spaces)
*/

#include "pch.h"

#define grandomMM       156
#define grandomMATRIX   0xB5026F5AA96619E9ULL
/* Most significant 33 bits */
#define grandomUM       0xFFFFFFFF80000000ULL
/* Least significant 31 bits */
#define grandomLM       0x7FFFFFFFULL

// Not my code.
static Grandom _r;

/* initializes mt[NN] with a seed */
void grandomClocContent(Grandom * const r, Gn8 const seed)
{
   Grandom *rtemp;

   genter;

   rtemp = r;
   if (!rtemp)
   {
      rtemp = &_r;
   }

   if (rtemp->isInit == gbTRUE)
   {
      greturn;
   }

   rtemp->mt[0] = seed;
   for (rtemp->mti = 1; rtemp->mti < NN; rtemp->mti++)
   {
      rtemp->mt[rtemp->mti] =
         (6364136223846793005ULL *
            (rtemp->mt[rtemp->mti - 1] ^ (rtemp->mt[rtemp->mti - 1] >> 62)) +
          rtemp->mti);
   }
   rtemp->isInit = gbTRUE;

   greturn;
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void grandomClocContentByArray(Grandom * const r, Gcount const keyCount, Gn8 const * const keyList)
{
   Gn8       i,
             k;
   Gi4       j;
   Grandom  *rtemp;

   genter;

   rtemp = r;
   if (!rtemp)
   {
      rtemp = &_r;
   }

   grandomClocContent(rtemp, 19650218ULL);

   i = 1;
   j = 0;
   for (k = ((NN > keyCount) ? NN : keyCount); k; k--)
   {
      rtemp->mt[i] =
         (rtemp->mt[i] ^
            ((rtemp->mt[i - 1] ^ (rtemp->mt[i - 1] >> 62)) * 3935559000370003845ULL))
         + keyList[j] + j; /* non linear */
      i++;
      j++;

      if (i >= NN)
      {
         rtemp->mt[0] = rtemp->mt[NN - 1];
         i            = 1;
      }

      if (j >= keyCount)
      {
         j = 0;
      }
   }

   for (k = NN - 1; k; k--)
   {
      rtemp->mt[i] =
         (rtemp->mt[i] ^
            ((rtemp->mt[i - 1] ^ (rtemp->mt[i - 1] >> 62)) * 2862933555777941757ULL))
         - i; /* non linear */
      i++;
      if (i >= NN)
      {
         rtemp->mt[0] = rtemp->mt[NN - 1];
         i            = 1;
      }
   }

   rtemp->mt[0] = 1ULL << 63; /* MSB is 1; assuring non-zero initial array */

   greturn;
}

/* generates a random number on [0, 2^64-1]-interval */
Gn8 grandomGetN(Grandom * const r)
{
   Gi4          i;
   Gn8          x;
   static Gn8   mag01[2] = {0ULL, grandomMATRIX};
   Grandom     *rtemp;

   genter;

   rtemp = r;
   if (!rtemp)
   {
      rtemp = &_r;
   }

   if (!rtemp->isInit)
   {
      grandomClocContent(rtemp, 5489ULL);
   }

   // generate NN words at one time
   if (rtemp->mti >= NN)
   {
      forCount(i, NN - grandomMM)
      {
         x            = (rtemp->mt[i] & grandomUM) | (rtemp->mt[i + 1] & grandomLM);
         rtemp->mt[i] = rtemp->mt[i + grandomMM] ^ (x >> 1) ^ mag01[(Gi4) (x & 1ULL)];
      }

      for (; i < NN - 1; i++)
      {
         x            = (rtemp->mt[i] & grandomUM) | (rtemp->mt[i + 1] & grandomLM);
         rtemp->mt[i] = rtemp->mt[i + (grandomMM - NN)] ^ (x >> 1) ^ mag01[(Gi4) (x & 1ULL)];
      }

      x                 = (rtemp->mt[NN - 1] & grandomUM) | (rtemp->mt[0] & grandomLM);
      rtemp->mt[NN - 1] = rtemp->mt[grandomMM - 1] ^ (x >> 1) ^ mag01[(Gi4) (x & 1ULL)];

      rtemp->mti = 0;
   }

   x = rtemp->mt[rtemp->mti++];

   x ^= (x >> 29) & 0x5555555555555555ULL;
   x ^= (x << 17) & 0x71D67FFFEDA60000ULL;
   x ^= (x << 37) & 0xFFF7EEE000000000ULL;
   x ^= (x >> 43);

   greturn x;
}

/* generates a random number on [0, 2^63-1]-interval */
long long grandomGetI(Grandom * const r)
{
   long long result;

   genter;

   result = grandomGetN(r) >> 1;

   greturn result;
}

/* generates a random number on [0,1]-real-interval */
double grandomGetR(Grandom * const r)
{
   double result;

   genter;

   result = (grandomGetN(r) >> 11) * (1.0 / 9007199254740991.0);

   greturn result;
}

/* generates a random number on [0,1)-real-interval */
double grandomGetROpen1(Grandom * const r)
{
   double result;

   genter;

   result = (grandomGetN(r) >> 11) * (1.0 / 9007199254740992.0);

   greturn result;
}

/* generates a random number on (0,1)-real-interval */
double grandomGetROpen(Grandom * const r)
{
   double result;

   genter;

   result = ((grandomGetN(r) >> 12) + 0.5) * (1.0 / 4503599627370496.0);

   greturn result;
}
