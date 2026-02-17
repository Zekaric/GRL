/********************************************************************

file:       galScope
authour:    Robbert de Groot
copyright:  2005-2009, Robbert de Groot

description:
Scope handling routines.

********************************************************************/

/********************************************************************
include
********************************************************************/
#include "grl_pch.h"

#include <math.h>

/********************************************************************
local
function
********************************************************************/
static void    _Call(            Gal *gal, GalScope *scope, Garray *line);

static int     _FindElse(        GalScope *scope, int instruction);
static int     _FindEndLoop(     GalScope *scope, int instruction);
static int     _FindEndIf(       GalScope *scope, int instruction);

static Garray *_ParseLine(       Gal *gal, GalScope *scope, Gstr *line);
static int     _ParseLineDestroy(Garray *data);
static int     _ProcessOp0Plus(  Gal *gal, GalScope *scope, Gstr *op, Garray *line);
static int     _ProcessOp1(      Gal *gal, GalScope *scope, Gstr *op, Garray *line);
static int     _ProcessOp1Plus(  Gal *gal, GalScope *scope, Gstr *op, Garray *line);
static int     _ProcessOp2Plus(  Gal *gal, GalScope *scope, Gstr *op, Garray *line);

static int     _VariablAdd(      GalScope *scope, Garray *line);

/********************************************************************
global
function
********************************************************************/
/********************************************************************
func: galScopeCreate_

Create a new scope.

param:
instructionList, GRETURNValue, paramList
   Garray *, Gdata *, Garray *
   in, in, in
   The minimum for a new scope.

return:
GalScope *
********************************************************************/
int galScopeCreateContent(GalScope *scope)
{
   GENTER;

   GRETURN_IF(!scope, FALSE);

   gmemClear(scope, sizeof(GalScope));
   scope->variableList     = gnameCreate(21);
   scope->commandIndexList = galCommandIndexListCreate();
   galCommandIndexListPush(scope->commandIndexList);

   GRETURN TRUE;
}

/********************************************************************
func: galScopeDestroy

Clean up.

param:
scope
   GalScope *
   in
   The scope.
********************************************************************/
int galScopeDestroyContent(GalScope *scope) 
{
   GENTER;

   Garray *vlist;

   vlist = ghashCreateKeyArray(scope->variableList);
   garrayForEachCell(vlist, gdataDestroy);
   garrayDestroy(    vlist);

   gnameDestroy(scope->variableList);

   galCommandIndexListDestroy(scope->commandIndexList);

   gmemClear(scope, sizeof(GalScope));

   GRETURN TRUE;
}

/********************************************************************
func: galScopeGetCommandIndex
********************************************************************/
int galScopeGetCommandIndex(GalScope *scope)
{
   GENTER;

   GRETURN galCommandIndexListGet(scope->commandIndexList);
}

/********************************************************************
func: galScopeGetVariable
********************************************************************/
Gdata *galScopeGetVariable(GalScope *scope, Gstr *varName)
{
   GENTER;

   GRETURN (Gdata *) gnameGet(scope->variableList, varName);
}

/********************************************************************
func: galScopePopCommandIndex
********************************************************************/
int galScopePopCommandIndex(GalScope *scope)
{
   GENTER;

   galCommandIndexListPop(scope->commandIndexList);

   GRETURN TRUE;
}

/********************************************************************
func: galScopePushCommandIndex
********************************************************************/
int galScopePushCommandIndex(GalScope *scope)
{
   GENTER;

   galCommandIndexListPush(scope->commandIndexList);

   GRETURN TRUE;
}

#if 0
/********************************************************************
func: galScopeRun

meat an potatoes of the GAL runner.

param:
gal
   Gal *
   in
   The environment.
********************************************************************/
void galScopeRun(Gal *gal) 
{
   GENTER;

   int       instruction,
             loopDone;
   GalScope *scope;
   Garray   *line,
            *loopIndex;
   Gstr     *op;
   Gdata    *data;

   scope = (GalScope *) garrayGet(gal->scopeList, garrayGetCount(gal->scopeList) - 1);

   commandIndex = scope->commandIndex;

   loopDone  = FALSE;
   loopIndex = garrayCreate();
   
   LOOP 
   {
      // Get the parts of the line.
      //line = _ParseLine(gal, scope, (Gstr *) garrayGet(scope->instructionList, instruction));

      // No more instructions.
      BREAK_IF(
         commandIndex >= (int) galCommandListGetCount(
            galFunctionGetCommandList(scope->func)));

      // Comment line.
      if (!line) 
      {
         commandIndex++;
         continue;
      }

      // Get the operation.
      op = (Gstr *) garrayGet(line, 0);

      switch (gstrGetAt(op, 0)) 
      {         
      case '=':
         switch(gstrGetAt(op, 1)) 
         {
         case '=': /* == */
            _ProcessOp2Plus(gal, scope, op, line);
            break;
   
         default: /* = */
            _ProcessOp1(gal, scope, op, line);
         }
         break;
      
      case '+':
      case '-':
         _ProcessOp0Plus(gal, scope, op, line);
         break;
      
      case '*':
      case '/':
      case '^':
      case '%':
         _ProcessOp1Plus(gal, scope, op, line);
         break;
      
      case '|':
         switch(gstrGetAt(op, 1)) 
         {
         case '|': /* || */
            _ProcessOp2Plus(gal, scope, op, line);
            break;
      
         default: /* | */
            _ProcessOp1Plus(gal, scope, op, line);
         }
         break;

      case '&':
         switch(gstrGetAt(op, 1)) 
         {
         case '&': /* && */
            _ProcessOp2Plus(gal, scope, op, line);
            break;
      
         default: /* & */
            _ProcessOp1Plus(gal, scope, op, line);
         }
         break;
      
      case '!':
      case '~':
         _ProcessOp1(gal, scope, op, line);
         break;
      
      case '<':
         switch(gstrGetAt(op, 1)) 
         {
         case '=': /* <= */
            _ProcessOp2Plus(gal, scope, op, line);
            break;
      
         case '<': /* << */
            _ProcessOp1Plus(gal, scope, op, line);
            break;
      
         default: /* < */
            _ProcessOp2Plus(gal, scope, op, line);
         }
         break;
      
      case '>':
         switch(gstrGetAt(op, 1)) 
         {
         case '=': /* >= */
            _ProcessOp2Plus(gal, scope, op, line);
            break;
      
         case '>': /* >> */
            _ProcessOp1Plus(gal, scope, op, line);
            break;
      
         default: /* > */
            _ProcessOp2Plus(gal, scope, op, line);
         }
         break;
      
      case 'b': /* break */
         instruction = _FindEndLoop(scope, instruction);
         garrayDestroyCell(loopIndex, garrayGetCount(loopIndex) - 1);
         break;

      case 'c': 
         switch(gstrGetAt(op, 1)) 
         {
         case 'a': /* call */
            _Call(gal, scope, line);
            break;

         case 'o': /* continue */
            instruction = (int) garrayGetI(loopIndex, (Gn4) (garrayGetCount(loopIndex) - 1));
         }
         break;

      case 'e':
         switch(gstrGetAt(op, 3)) 
         {
         case 'e': /* else */
            instruction = _FindEndIf(scope, instruction);
            break;

         case 'i': /* endif */
            /* Nothing to do.*/
            break;

         case 'l': /* endloop */
            instruction = (int) garrayGetI(loopIndex, (Gn4) garrayGetCount(loopIndex) - 1);
            break;
         }
         break;
      
      case 'i': /* if */
         data = garrayGet(line, 1);
         if (!gdataGetI(data)) 
         {
            instruction = _FindElse(scope, instruction);
         }
         break;

      case 'l': /* loop */
         garraySetI(loopIndex, garrayGetCount(loopIndex), instruction);
         break;

      case 'r': /* GRETURN */
         {
            Gdata *data;

            data = (Gdata *) garrayGet(line, 1);

            if (scope->returnData &&
                data) 
            {
               gdataSet(scope->returnData, data);
            }
         }
         loopDone = TRUE;
         break;

      case 'v': /* var */
         _VariablAdd(scope, line);
         break;
      }

      // Clean up. 
      //_ParseLineDestroy(line);
      //garrayDestroy(line);

      // GRETURNing from the function.
      BREAK_IF(loopDone) 

      commandIndex++;
   }
   GRETURN;
}
#endif

/********************************************************************
func: galScopeSetCommandIndex
********************************************************************/
int galScopeSetCommandIndex(GalScope *scope, int index)
{
   GENTER;

   galCommandIndexListSet(scope->commandIndexList, index);

   GRETURN TRUE;
}

/********************************************************************
local
function
********************************************************************/
/********************************************************************
func: _Call

Make a lib call.

param:
gal, scope, line
   Gal *, GalScope *, Garray *line
   in, in, in
   The environment, scope and the parsed line.

return:

********************************************************************/
void _Call(Gal *gal, GalScope *scope, Garray *line) 
{
   GENTER;

   gal, scope, line;

/*
   Gstr        *str;
   Gdata       *data;
   GalFunction *func;

   // Get the module name.
   data = (Gdata *) garrayGet(line, 2);
   str  = gdataCreateGstr(data);

   // Find the module.
   module = galModuleGet(str);
   gstrDestroy(str);
   if (!module) 
   {
      GRETURN;
   }

   // Call the module.
   galFunctionCall(gal, module, scope, line);
*/
   GRETURN;
}

/********************************************************************
func: _FindElse

Find the else for this if.

param:
scope, instruction
   GalScope *, int
   in, in
   The scope

return:
int
   The index of the else instruction.
********************************************************************/
int _FindElse(GalScope *scope, int instruction) 
{
   GENTER;

   scope, instruction;
/*
   int   a,
         nest;
   Gstr *str;

   nest = 0;

   for (a = instruction + 1; a < (int) garrayGetCount(scope->instructionList); a++) 
   {
      str = (Gstr *) garrayGet(scope->instructionList, a);

      switch (gstrGetAt(str, 0)) 
      {         
      case 'e':
         switch(gstrGetAt(str, 3)) 
         {
         case 'e': // else 
            if (nest == 0) 
            {
               GRETURN a;
            }
            break;

         case 'i': // endif
            if (nest) 
            {
               nest = nest - 1;
            }
            else 
            {
               // No else, found endit instead.
               GRETURN a;
            }
            break;
         }
         break;

      case 'i': // if 
         nest = nest + 1;
         break;
      }
   }
   GRETURN a;
*/
   GRETURN FALSE;
}

/********************************************************************
func: _FindEndLoop

Find the end loop for this loop.

param:
scope, instruction
   GalScope *, int
   in, in
   The scope

return:
int
   The index of the endloop instruction.
********************************************************************/
int _FindEndLoop(GalScope *scope, int instruction) 
{
   GENTER;
   
   scope, instruction;
/*
   int   a,
         nest;
   Gstr *str;

   nest = 0;

   for (a = instruction + 1; a < (int) garrayGetCount(scope->instructionList); a++) 
   {
      str = (Gstr *) garrayGet(scope->instructionList, a);

      switch (gstrGetAt(str, 0)) 
      {         
      case 'e':
         switch(gstrGetAt(str, 3)) 
         {
         case 'l': // endloop
            if (nest == 0) 
            {
               GRETURN a;
            }
            else 
            {
               nest = nest - 1;
            }
            break;
         }
         break;

      case 'l': // loop
         nest = nest + 1;
         break;
      }
   }

   GRETURN a;
*/
   GRETURN FALSE;
}

/********************************************************************
func: _FindEndIf

Find the endif for this if.

param:
scope, instruction
   GalScope *, int
   in, in
   The scope

return:
int
   The index of the endif instruction.
********************************************************************/
int _FindEndIf(GalScope *scope, int instruction) 
{
   GENTER;

   scope, instruction;
/*
   int   a,
         nest;
   Gstr *str;

   nest = 0;

   for (a = instruction + 1; a < (int) garrayGetCount(scope->instructionList); a++) 
   {
      str = (Gstr *) garrayGet(scope->instructionList, a);

      switch (gstrGetAt(str, 0)) 
      {         
      case 'e':
         switch(gstrGetAt(str, 3)) 
         {
         case 'i': // endif
            if (nest == 0) 
            {
               GRETURN a;
            }
            else 
            {
               nest = nest - 1;
            }
            break;
         }
         break;

      case 'i': // if 
         nest = nest + 1;
         break;
      }
   }

   GRETURN a;
*/
   GRETURN FALSE;
}

/********************************************************************
func: _ParseLine

Break the line into tokens.

param:
line
   Gstr *
   in
   The code line

return:
Garray *
********************************************************************/
Garray *_ParseLine(Gal *gal, GalScope *scope, Gstr *line) 
{
   GENTER;

   Gn4      a;
   Gstr    *str;
   Gchar    letter;
   Garray  *pline,
           *final;
   Gdata *data;

   /* Nothing to parse.*/
   if (gcharIsWhiteSpace(gstrGetAt(line, 0))) 
   {
      GRETURN NULL;
   }

   str   = gstrCreate();
   pline = garrayCreate();

   /* Get the pieces.*/
   for (a = 0; a < gstrGetLength(line); a++) 
   {      
      letter = gstrGetAt(line, a);

      if (!gcharIsWhiteSpace(letter)) 
      {
         gstrAppendGchar(str, letter);
      }
      else 
      {
         garraySet(pline, garrayGetCount(pline), str);

         str = gstrCreate();

         /* Skip to the next token.*/
         for (a = a + 1; a < gstrGetLength(line); a++) 
         {
            letter = gstrGetAt(line, a);
            if (!gcharIsWhiteSpace(letter)) 
            {
               gstrAppendGchar(str, letter);

               /* If a quote then the rest of the line is a string.*/
               if (letter == '\"') 
               {
                  for (a = a + 1; a < gstrGetLength(line); a++) 
                  {
                     gstrAppendGchar(str, gstrGetAt(line, a));
                  }
               }
               break;
            }
         }
      }
   }
   /* Toss off the \r\n */
   if (gstrGetAt(str, gstrGetLength(str) - 1) == '\n' ||
       gstrGetAt(str, gstrGetLength(str) - 1) == '\r') 
   {
      if (gstrGetAt(str, gstrGetLength(str) - 2) == '\n' ||
          gstrGetAt(str, gstrGetLength(str) - 2) == '\r')
      {
         gstrDestroySubStr(str, gstrGetLength(str) - 2, gstrGetLength(str));
      }
      else 
      {
         gstrDestroySubStr(str, gstrGetLength(str) - 2, gstrGetLength(str));
      }
   }
   garraySet(pline, garrayGetCount(pline), str);

   final = garrayCreate();
   garraySet(final, 0, garrayGet(pline, 0));

   /* Since we've found all the tokens, convert them to Gdatas. */
   for (a = 1; a < (int) garrayGetCount(pline); a++) 
   {
      str = (Gstr *) garrayGet(pline, a);

      data = NULL;

      letter = gstrGetAt(str, 0);
      gstrDestroySubStr(str, 0, 1);

      switch(letter) 
      {
      case '\"':
         data = gdataCreate(gdataTypeS);
         gdataSetS(data, str);
         gdataSetIsTemp(data, TRUE);
         break;

      case '\'':
         data = gdataCreate(gdataTypeS);
         gdataSetS(data, str);
         gdataSetIsTemp(data, TRUE);
         break;
         
      case 'i':
         data = gdataCreate(gdataTypeI);
         gdataSetI(data, gstrGetI(str));
         gdataSetIsTemp(data, TRUE);
         break;

      case 'n':
         data = gdataCreate(gdataTypeN);
         gdataSetN(data, gstrGetN(str));
         gdataSetIsTemp(data, TRUE);
         break;

      case 'r':
         data = gdataCreate(gdataTypeR);
         gdataSetR(data, gstrGetR(str));
         gdataSetIsTemp(data, TRUE);
         break;

      case 'v':
         data = (Gdata *) gnameGet(scope->variableList, str);
         if (!data) 
         {
            data = (Gdata *) gnameGet(gal->variableList, str);
         }
      }

      gstrDestroy(str);
      if (data) 
      {
         garraySet(final, garrayGetCount(final), (void *) data);
      }
   }

   garrayDestroy(pline);

   GRETURN(final);
}

/********************************************************************
func: _ParseLineDestroy 

Clean up the temporaries.

param:
data
   garray *
   in
   The data.
********************************************************************/
int _ParseLineDestroy(Garray *line) 
{
   GENTER;

   int      a;
   Gdata *data;
   Gstr    *str;

   str = (Gstr *) garrayGet(line, 0);
   gstrDestroy(str);

   for (a = 1; a < (int) garrayGetCount(line); a++) 
   {
      data = (Gdata *) garrayGet(line, a);
      BREAK_IF(!data);

      if (gdataIsTemp(data)) 
      {
         gdataDestroy(data);
      }
   }

   GRETURN TRUE;
}

/********************************************************************
func: _ProcessOp0Plus

Perform a one varaible operation.

param:
gal
   Gal *
   in
   The environment.
********************************************************************/
int _ProcessOp0Plus(Gal *gal, GalScope *scope, Gstr *op, Garray *line) 
{
   GENTER;

   Gdata  *dest;

   dest = (Gdata *) garrayGet(line, 1);

   GRETURN_IF(!dest, FALSE);

   if (garrayGetCount(line) == 2) 
   {
      switch (gstrGetAt(op, 0)) 
      {         
      case '+':
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            if (gdataGetI(dest) < 0) 
            {
               gdataSetI(dest, -gdataGetI(dest));
            }
         }
         else if (gdataTypeIsR(gdataGetType(dest)))
         {
            if (gdataGetR(dest) < 0.) 
            {
               gdataSetR(dest, -gdataGetR(dest));
            }
         }
         break;

      case '-':
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, -gdataGetI(dest));
         }
         else if (gdataTypeIsR(gdataGetType(dest)))
         {
            gdataSetR(dest, -gdataGetR(dest));
         }
         break;
      }

      GRETURN TRUE;
   }

   GRETURN _ProcessOp1Plus(gal, scope, op, line);
}

/********************************************************************
func: _ProcessOp1

Perform a one varaible operation.

param:
gal
   Gal *
   in
   The environment.
********************************************************************/
int _ProcessOp1(Gal *gal, GalScope *scope, Gstr *op, Garray *line) 
{
   GENTER;

   Gdata  *dest,
          *data;

   scope;
   gal;
   dest = (Gdata *) garrayGet(line, 1);
   data = (Gdata *) garrayGet(line, 2);

   RETURN_IF(
         !data || 
         !dest,
      FALSE);

   switch (gstrGetAt(op, 0)) 
   {         
   case '=': /* = */
      gdataSet(dest, data);
      break;
   
   case '!':
      if      (gdataTypeIsI(gdataGetType(dest))) 
      {
         gdataSetI(dest, !gdataGetI(dest));
      }
      else if (gdataTypeIsN(gdataGetType(dest)))
      {
         gdataSetN(dest, !gdataGetN(dest));
      }
      break;

   case '~':
      if      (gdataTypeIsI(gdataGetType(dest))) 
      {
         gdataSetI(dest, ~gdataGetI(dest));
      }
      else if (gdataTypeIsN(gdataGetType(dest)))
      {
         gdataSetN(dest, ~gdataGetN(dest));
      }
      break;
   }

   GRETURN TRUE;
}

/********************************************************************
func: _ProcessOp1Plus

Perform a one varaible operation.

param:
gal
   Gal *
   in
   The environment.
********************************************************************/
int _ProcessOp1Plus(Gal *gal, GalScope *scope, Gstr *op, Garray *line) 
{
   GENTER;

   Gdata  *dest,
            *data;

   dest = (Gdata *) garrayGet(line, 1);
   data = (Gdata *) garrayGet(line, 2);

   /* nothing to do. */
   RETURN_IF(
         !dest ||
         !data,
      FALSE);

   if (garrayGetCount(line) == 3) 
   {
      switch (gstrGetAt(op, 0)) 
      {         
      case '+':
         if      (gdataTypeIsR(gdataGetType(dest)) || 
                  gdataTypeIsR(gdataGetType(data))) 
         {
            gdataSetR(dest, gdataGetR(dest) + gdataGetR(data));
         }
         else if (gdataTypeIsI(gdataGetType(dest)) ||
                  gdataTypeIsI(gdataGetType(data))) 
         {
            gdataSetI(dest, gdataGetI(dest) + gdataGetI(data));
         }
         else 
         {
            gdataSetN(dest, gdataGetN(dest) + gdataGetN(data));
         }
         break;
      
      case '-':
         if      (gdataTypeIsR(gdataGetType(dest)) ||
                  gdataTypeIsR(gdataGetType(data))) 
         {
            gdataSetR(dest, gdataGetR(dest) - gdataGetR(data));
         }
         else if (gdataTypeIsI(gdataGetType(dest)) ||
                  gdataTypeIsI(gdataGetType(data))) 
         {
            gdataSetI(dest, gdataGetI(dest) - gdataGetI(data));
         }
         else 
         {
            gdataSetN(dest, gdataGetN(dest) - gdataGetN(data));
         }
         break;
      
      case '*':
         if      (gdataTypeIsR(gdataGetType(dest)) ||
                  gdataTypeIsR(gdataGetType(data))) 
         {
            gdataSetR(dest, gdataGetR(dest) * gdataGetR(data));
         }
         else if (gdataTypeIsI(gdataGetType(dest)) ||
                  gdataTypeIsI(gdataGetType(data))) 
         {
            gdataSetI(dest, gdataGetI(dest) * gdataGetI(data));
         }
         else 
         {
            gdataSetN(dest, gdataGetN(dest) * gdataGetN(data));
         }
         break;
      
      case '/':
         if      (gdataTypeIsR(gdataGetType(dest)) ||
                  gdataTypeIsR(gdataGetType(data))) 
         {
            gdataSetR(dest, gdataGetR(dest) / gdataGetR(data));
         }
         else if (gdataTypeIsI(gdataGetType(dest)) ||
                  gdataTypeIsI(gdataGetType(data))) 
         {
            gdataSetI(dest, gdataGetI(dest) / gdataGetI(data));
         }
         else 
         {
            gdataSetN(dest, gdataGetN(dest) / gdataGetN(data));
         }
         break;
      
      case '%':
         if      (gdataTypeIsR(gdataGetType(dest)) ||
                  gdataTypeIsR(gdataGetType(data))) 
         {
            gdataSetR(dest, fmod(gdataGetR(dest), gdataGetR(data)));
         }
         else if (gdataTypeIsI(gdataGetType(dest)) ||
                  gdataTypeIsI(gdataGetType(data))) 
         {
            gdataSetI(dest, gdataGetI(dest) % gdataGetI(data));
         }
         else 
         {
            gdataSetN(dest, gdataGetN(dest) % gdataGetN(data));
         }
         break;
      
      case '|': /* | */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(dest) | gdataGetI(data));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(dest) | gdataGetN(data));
         }
         break;

      case '&': /* & */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(dest) & gdataGetI(data));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(dest) & gdataGetN(data));
         }
         break;

      case '<': /* << */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(dest) << gdataGetI(data));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(dest) << gdataGetN(data));
         }
         break;
      
      case '>': /* >> */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(dest) >> gdataGetI(data));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(dest) >> gdataGetN(data));
         }
         break;
      }

      GRETURN TRUE;
   }

   GRETURN _ProcessOp2Plus(gal, scope, op, line);
}

/********************************************************************
func: _ProcessOp2Plus

Perform a one varaible operation.

param:
gal
   Gal *
   in
   The environment.
********************************************************************/
int _ProcessOp2Plus(Gal *gal, GalScope *scope, Gstr *op, Garray *line) 
{
   GENTER;

   Gdata *dest,
         *data,
         *datb;

   scope;
   gal;
   dest = (Gdata *) garrayGet(line, 1);
   data = (Gdata *) garrayGet(line, 2);
   datb = (Gdata *) garrayGet(line, 3);

   GRETURN_IF(
         !dest ||
         !data ||
         !datb,
      FALSE);

   switch (gstrGetAt(op, 0)) 
   {      
   case '=': /* == */
      if      (gdataTypeIsR(gdataGetType(data)) ||
               gdataTypeIsR(gdataGetType(datb))) 
      {
         gdataSetI(dest, gdataGetR(data) == gdataGetR(datb));
      }
      else if (gdataTypeIsI(gdataGetType(data)) ||
               gdataTypeIsI(gdataGetType(datb))) 
      {
         gdataSetI(dest, gdataGetI(data) == gdataGetI(datb));
      }
      else 
      {
         gdataSetI(dest, gdataGetN(data) == gdataGetN(datb));
      }
      break;
   
   case '+':
      if      (gdataTypeIsR(gdataGetType(data)) ||
               gdataTypeIsR(gdataGetType(datb))) 
      {
         gdataSetR(dest, gdataGetR(data) + gdataGetR(datb));
      }
      else if (gdataTypeIsI(gdataGetType(data)) ||
               gdataTypeIsI(gdataGetType(datb))) 
      {
         gdataSetI(dest, gdataGetI(data) + gdataGetI(datb));
      }
      else 
      {
         gdataSetN(dest, gdataGetN(data) + gdataGetN(datb));
      }
      break;
   
   case '-':
      if      (gdataTypeIsR(gdataGetType(data)) ||
               gdataTypeIsR(gdataGetType(datb))) 
      {
         gdataSetR(dest, gdataGetR(data) - gdataGetR(datb));
      }
      else if (gdataTypeIsI(gdataGetType(data)) ||
               gdataTypeIsI(gdataGetType(datb))) 
      {
         gdataSetI(dest, gdataGetI(data) - gdataGetI(datb));
      }
      else 
      {
         gdataSetN(dest, gdataGetN(data) - gdataGetN(datb));
      }
      break;
   
   case '*':
      if      (gdataTypeIsR(gdataGetType(data)) ||
               gdataTypeIsR(gdataGetType(datb))) 
      {
         gdataSetR(dest, gdataGetR(data) * gdataGetR(datb));
      }
      else if (gdataTypeIsI(gdataGetType(data)) ||
               gdataTypeIsI(gdataGetType(datb))) 
      {
         gdataSetI(dest, gdataGetI(data) * gdataGetI(datb));
      }
      else 
      {
         gdataSetN(dest, gdataGetN(data) * gdataGetN(datb));
      }
      break;
   
   case '/':
      if      (gdataTypeIsR(gdataGetType(data)) ||
               gdataTypeIsR(gdataGetType(datb))) 
      {
         gdataSetR(dest, gdataGetR(data) / gdataGetR(datb));
      }
      else if (gdataGetType(data) ||
               gdataGetType(datb)) 
      {
         gdataSetI(dest, gdataGetI(data) / gdataGetI(datb));
      }
      else 
      {
         gdataSetN(dest, gdataGetN(data) / gdataGetN(datb));
      }
      break;
   
   case '%':
      if      (gdataTypeIsR(gdataGetType(data))) 
      {
         gdataSetR(dest, fmod(gdataGetR(data), gdataGetR(datb)));
      }
      else if (gdataTypeIsI(gdataGetType(data))) 
      {
         gdataSetI(dest, gdataGetI(data) % gdataGetI(datb));
      }
      else 
      {
         gdataSetN(dest, gdataGetN(data) % gdataGetN(datb));
      }
      break;
   
   case '|':
      switch(gstrGetAt(op, 1)) 
      {
      case '|': /* || */
         gdataSetI(dest, gdataGetI(data) || gdataGetI(datb));
         break;
      
      default: /* | */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(data) | gdataGetI(datb));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(data) | gdataGetN(datb));
         }
      }
      break;

   case '&':
      switch(gstrGetAt(op, 1)) 
      {
      case '&': /* && */
         gdataSetI(dest, gdataGetI(data) && gdataGetI(datb));
         break;
   
      default: /* & */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(data) & gdataGetI(datb));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(data) & gdataGetN(datb));
         }
      }
      break;
   
   case '<':
      switch(gstrGetAt(op, 1)) 
      {
      case '=': /* <= */
         if      (gdataTypeIsR(gdataGetType(data)) ||
                  gdataTypeIsR(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetR(data) <= gdataGetR(datb));
         }
         else if (gdataTypeIsI(gdataGetType(data)) ||
                  gdataTypeIsI(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetI(data) <= gdataGetI(datb));
         }
         else 
         {
            gdataSetI(dest, gdataGetN(data) <= gdataGetN(datb));
         }
         break;
   
      case '<': /* << */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(data) << gdataGetI(datb));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(data) << gdataGetN(datb));
         }
         break;
   
      default: /* < */
         if      (gdataTypeIsR(gdataGetType(data)) ||
                  gdataTypeIsR(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetR(data) < gdataGetR(datb));
         }
         else if (gdataTypeIsI(gdataGetType(data)) ||
                  gdataTypeIsI(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetI(data) < gdataGetI(datb));
         }
         else 
         {
            gdataSetI(dest, gdataGetN(data) < gdataGetN(datb));
         }
      }
      break;
   
   case '>':
      switch(gstrGetAt(op, 1)) 
      {
      case '=': /* >= */
         if      (gdataTypeIsR(gdataGetType(data)) ||
                  gdataTypeIsR(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetR(data) >= gdataGetR(datb));
         }
         else if (gdataTypeIsI(gdataGetType(data)) ||
                  gdataTypeIsI(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetI(data) >= gdataGetI(datb));
         }
         else 
         {
            gdataSetI(dest, gdataGetN(data) >= gdataGetN(datb));
         }
         break;
   
      case '>': /* >> */
         if      (gdataTypeIsI(gdataGetType(dest))) 
         {
            gdataSetI(dest, gdataGetI(data) >> gdataGetI(datb));
         }
         else if (gdataTypeIsN(gdataGetType(dest)))
         {
            gdataSetN(dest, gdataGetN(data) >> gdataGetN(datb));
         }
         break;
   
      default: /* > */
         if      (gdataTypeIsR(gdataGetType(data)) ||
                  gdataTypeIsR(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetR(data) > gdataGetR(datb));
         }
         else if (gdataTypeIsI(gdataGetType(data)) ||
                  gdataTypeIsI(gdataGetType(datb))) 
         {
            gdataSetI(dest, gdataGetI(data) > gdataGetI(datb));
         }
         else 
         {
            gdataSetI(dest, gdataGetN(data) > gdataGetN(datb));
         }
      }
      break;
   }
   
   GRETURN TRUE;
}

/********************************************************************
func: _VariablAdd

Add variables.

param:
scope
   GalScope *
   in
   the scope.

line
   Garray *
   in 
   The code line.
********************************************************************/
int _VariablAdd(GalScope *scope, Garray *line) 
{
   GENTER;

   int        a;
   GdataType *type;
   Gdata     *data;
   Gstr      *str;

   data = (Gdata *) garrayGet(line, 1);
   type = gdataGetType(data);
   GRETURN_IF(type == gdataTypeNONE, FALSE);

   for (a = 2; a < (int) garrayGetCount(line); a++) 
   {
      // Get the name of the variable.
      data = (Gdata *) garrayGet(line, a);
      str  = gdataCreateGstr(data);

      // Test to see if variable already exists.
      data = (Gdata *) gnameGet(scope->variableList, str);
      CONTINUE_IF(data);

      // Add the variable to the dictionary.
      data = gdataCreate(type);
      gnameSet(scope->variableList, str, (void *) data);

      gstrDestroy(str);
   }

   GRETURN TRUE;
}
