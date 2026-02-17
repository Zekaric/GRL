/******************************************************************************
file:       gut.h
author:     Robbert de Groot
copyright:  2010-2010, Robbert de Groot

description:
Macros for one file unit test suite.

The program that
******************************************************************************/

#pragma once

typedef enum
{
   gtestStateTEST_SETUP,
   gtestStateRUN_TEST,
   gtestStateTEST_CLEANUP,

   gtestStateCOUNT
} GtestState;

#define gutTRY_START()                                                        \
   __try                                                                      \
   {
#define gutTRY_CATCH()                                                        \
   }                                                                          \
   __except(EXCEPTION_EXECUTE_HANDLER)                                        \
   {
#define gutTRY_STOP()                                                         \
   }

#define gtestHELP                                                             \
   "gut help:\n"                                                              \
   "=========\n\n"                                                            \
   "[program name] [module] [test]\n\n"                                       \
   "[module] - optional, a specific module name\n"                            \
   "[test]   - optional, requires a [module] setting.  A specific test\n"     \
   "           inside a module specific module.\n\n"

// START and STOP define the main function for the program.
//
#define gtestSTART()                                                          \
   int main(int acount, char **alist)                                         \
   {                                                                          \
      if (acount > 1 &&                                                       \
          strcmp(alist[1], "h") == 0)                                         \
      {                                                                       \
         puts(gtestHELP);                                                     \
         return 0;                                                            \
      }                                                                       \
                                                                              \
      printf("Unit Test: %s\n", alist[0]);                                    \
      printf("===========================================================\n");


#define gtestSTOP()                                                           \
      return 0;                                                               \
   }

// MODULE START and STOP define a test module
#define gtestMODULE_START(NAME)                                               \
   if (acount <= 1                        ||                                  \
       (acount                  >= 2   &&                                     \
        strcmp(alist[1], #NAME) == 0))                                        \
   {                                                                          \
      int iteration,                                                          \
          state,                                                              \
          index,                                                              \
          total;                                                              \
                                                                              \
      puts("Module: " #NAME);                                                 \
                                                                              \
      total = -1;                                                             \
                                                                              \
      for (iteration = 0; ; iteration++)                                      \
      {                                                                       \
         for (state = gtestStateTEST_SETUP;                                   \
              state < gtestStateCOUNT;                                        \
              state++)                                                        \
         {                                                                    \
            index = 0;

#define gtestMODULE_STOP()                                                    \
            if (total < 0)                                                    \
            {                                                                 \
               total = index - 1;                                             \
            }                                                                 \
         }                                                                    \
                                                                              \
         breakIf(iteration == total);                                        \
      }                                                                       \
      printf("===========================================================\n");\
   }

#define gtestPRE_START()                                                      \
            if (state == gtestStateTEST_SETUP)                                \
            {
#define gtestPRE_STOP()                                                       \
            }

#define gtestPOST_START()                                                     \
            if (state == gtestStateTEST_CLEANUP)                              \
            {

#define gtestPOST_STOP()                                                      \
            }

#define gtestTEST_START(NAME)                                                 \
            if (index == iteration                    &&                      \
                (state == gtestStateRUN_TEST       ||                         \
                 (acount                  >= 3  &&                            \
                  strcmp(alist[2], #NAME) == 0)))                             \
            {                                                                 \
               printf("Test  : %s\n", #NAME);


#define gtestTEST_STOP()                                                      \
            }                                                                 \
            index++;

#define gtestERROR_IF(CODE)                                                   \
               gutTRY_START()                                                 \
                  if (CODE)                                                   \
                  {                                                           \
                     printf("   Failure:   line %6d\n", __LINE__);            \
                     puts("   " #CODE);                                       \
                  }                                                           \
               gutTRY_CATCH()                                                 \
                  printf("   Exception: line %6d\n", __LINE__);               \
                  puts("   " #CODE);                                          \
               gutTRY_STOP()
