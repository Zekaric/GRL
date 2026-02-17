/********************************************************************

file:       galfunction
authour:    Robbert de Groot
copyright:  2009-2009, Robbert de Groot

description:
Function handling.

********************************************************************/

/********************************************************************
include
********************************************************************/
#include "grl_pch.h"

/********************************************************************
local
variable
********************************************************************/
static Gname      *_function = NULL;
static GnameKey   
                  *_keywordLoop,
                  *_keywordIf,
                  *_keywordIfTest,
                  *_keywordIfThen,
                  *_keywordIfElse,
                  *_keywordBreak,
                  *_keywordContinue,
                  *_keywordVariable,
                  *_keywordType,
                  *_keywordI,
                  *_keywordI1,
                  *_keywordI2,
                  *_keywordI4,
                  *_keywordI8,
                  *_keywordN,
                  *_keywordN1,
                  *_keywordN2,
                  *_keywordN4,
                  *_keywordN8,
                  *_keywordP,
                  *_keywordR,
                  *_keywordR4,
                  *_keywordR8,
                  *_keywordS,
                  *_keywordSA,
                  *_keywordSU,
                  *_keywordV,
                  *_keywordX;

/********************************************************************
prototype: 
********************************************************************/
static int _Compile(             GalCommandList *func, Gstr *script);
static int _CompileConstant(     GalParam *param, GnameKey *nameKey, Gstr *value);
static int _CompileExpression(   GalParam *param, Gstr *script);
static int _CompileFunctionCall( GalCommand *command, Gstr *script);
static int _CompileIf(           GalCommand *command, Gstr *script);
static int _CompileLoop(         GalCommand *command, Gstr *script);
static int _CompileV(            GalParam *param, Gstr *script);
static int _CompileVariable(     GalCommand *command, Gstr *script);
static int _CompileVariableNames(GalCommand *command, Gstr *script);

/********************************************************************
global 
function
********************************************************************/
/********************************************************************
func: galFunctionCreateFunction

Adding a function to gal.
********************************************************************/
GRLFUNC int galFunctionCreateFunction(Gstr *functionName, int (*function)(Gal *, GalScope *, Gdata *returnData, GalParamList *))
{
   GENTER;

   GalFunction *func;

   GRETURN_IF(
         gstrIsEmpty(functionName) ||
         !function,
      FALSE);

   func = (GalFunction *) gmemCreate(sizeof(GalFunction));
   GRETURN_IF(!func, FALSE);

   func->name     = gnameSet(_function, functionName, (void *) func);
   func->type     = galFunctionTypeFUNCTION;
   func->function = function;

   GRETURN TRUE;
}

/********************************************************************
func: galFunctionCreateScript

Adding a GAL script to gal.
********************************************************************/
GRLFUNC int galFunctionCreateScript(Gstr *functionName, Gstr *script)
{
   GENTER;

   GalFunction *func;

   GRETURN_IF(
         gstrIsEmpty(functionName) ||
         gstrIsEmpty(script),
      FALSE);

   func = (GalFunction *) gmemCreate(sizeof(GalFunction));
   GRETURN_IF(!func, FALSE);

   func->name        = gnameSet(_function, functionName, (void *) func);
   func->type        = galFunctionTypeSCRIPT;
   func->commandList = galCommandListCreate();

   if (!_Compile(func->commandList, script))
   {
      galFunctionDestroy(functionName);
      GRETURN FALSE;
   }

   GRETURN TRUE;
}

/********************************************************************
func: galFunctionDestroy 

Clean up.
********************************************************************/
GRLFUNC int galFunctionDestroy(Gstr *functionName) 
{
   GENTER;

   GalFunction *func;

   GRETURN_IF(!functionName, FALSE);

   // Get the funciton.
   func = (GalFunction *) gnameGet(_function, functionName);

   // If 1 then it's a built in function/feature.
   GRETURN_IF(
         !func ||
         func == (void *) 1,
      FALSE);

   // Clean up.
   if (func->type == galFunctionTypeSCRIPT) 
   {
      galCommandListDestroy(func->commandList);
   }

   gmemDestroy(func);

   // Clear the function table.
   gnameSet(_function, functionName, NULL);

   GRETURN FALSE;
}

/********************************************************************
func: galFunctionFind

Find a function.
********************************************************************/
GalFunction *galFunctionGet(Gstr *functionName) 
{
   GENTER;

   GalFunction *func;
#if 0
   Gpath       *path;
   Gstr        *mfile,
               *mpath;
   Gfile       *file;
   Garray      *instructionList;
#endif

   RETURN_IF(!functionName, NULL);

   func = (GalFunction *) gnameGet(_function, functionName);
   GRETURN func;

#if 0
   /* Find the file. */
   path  = gpathCreateFromGstr(name);
   mfile = gpathGet(path, gpathTypeFOLDER);
   gpathPop(path, gpathTypeFOLDER);

   mpath = gpathCreateGstr(path);

   /* Check to see if the module already exists.*/
   mod = gnameGet(_function, mpath);
   gstrDestroy(mpath);
   if (mod) 
   {
      gstrDestroy(mfile);
      gpathDestroy(path);
      GRETURN mod;
   }

   gpathPush(     path, gpathTypeFILE,      mfile);
   gpathPushASCII(path, gpathTypeEXTENSION, "gal");
   gstrDestroy(mfile);
   mpath = gpathCreateGstrSystem(path);
   gpathDestroy(path);

   file = gfileOpen(mpath, gfileOpenREAD);
   gstrDestroy(mpath);
   if (!file) 
   {
      GRETURN NULL;
   }

   /* read in the file. */
   instructionList = garrayCreate();
   gfileGetGstrList(file, gcharTypeUTF8, instructionList);

   gfileClose(file);


   /* Create the module.*/
   mod = galFunctionCreate(name);
   
   galFunctionSetInstructionList(mod, instructionList);

   GRETURN(mod);
#endif
}

/********************************************************************
func: galFunctionGetCommandList
********************************************************************/
GalCommandList *galFunctionGetCommandList(GalFunction *func)
{
   GENTER;

   GRETURN func->commandList;
}

/********************************************************************
func: galFunctionRun

Make the call to the function.
********************************************************************/
int galFunctionRun(Gal *gal, GalScope *scope, GalFunction *func, Gdata *returnData, GalParamList *paramList)
{
   GENTER;

   // Run the script
   if (func->type == galFunctionTypeSCRIPT) 
   {
      //_Run(gal, scope, func, returnData, paramList);
   }
   // Call the function.
   else 
   {
      (func->function)(gal, scope, returnData, paramList);
   }

   GRETURN TRUE;
}

/********************************************************************
func: galFunctionStart

Start the module functions.

return:
int
********************************************************************/
int galFunctionStart(void) 
{
   GENTER;

   if (!_function) 
   {
      _function = gnameCreate(ghashSize100);
   }

   // special key words.
   _keywordLoop     = gnameSetASCII(_function, "loop",      (void *) 1);
   _keywordIf       = gnameSetASCII(_function, "if",        (void *) 1);
   _keywordIfElse   = gnameSetASCII(_function, "else",      (void *) 1);
   _keywordIfTest   = gnameSetASCII(_function, "test",      (void *) 1);
   _keywordIfThen   = gnameSetASCII(_function, "then",      (void *) 1);
   _keywordBreak    = gnameSetASCII(_function, "break",     (void *) 1);
   _keywordContinue = gnameSetASCII(_function, "continue",  (void *) 1);
   _keywordVariable = gnameSetASCII(_function, "var",       (void *) 1);
   _keywordType     = gnameSetASCII(_function, "type",      (void *) 1);

   // param types.
   _keywordI        = gnameSetASCII(_function, "i",         (void *) 1);
   _keywordI1       = gnameSetASCII(_function, "i1",        (void *) 1);
   _keywordI2       = gnameSetASCII(_function, "i2",        (void *) 1);
   _keywordI4       = gnameSetASCII(_function, "i4",        (void *) 1);
   _keywordI8       = gnameSetASCII(_function, "i8",        (void *) 1);
   _keywordN        = gnameSetASCII(_function, "n",         (void *) 1);
   _keywordN1       = gnameSetASCII(_function, "n1",        (void *) 1);
   _keywordN2       = gnameSetASCII(_function, "n2",        (void *) 1);
   _keywordN4       = gnameSetASCII(_function, "n4",        (void *) 1);
   _keywordN8       = gnameSetASCII(_function, "n8",        (void *) 1);
   _keywordP        = gnameSetASCII(_function, "p",         (void *) 1);
   _keywordR        = gnameSetASCII(_function, "r",         (void *) 1);
   _keywordR4       = gnameSetASCII(_function, "r4",        (void *) 1);
   _keywordR8       = gnameSetASCII(_function, "r8",        (void *) 1);
   _keywordS        = gnameSetASCII(_function, "s",         (void *) 1);
   _keywordSA       = gnameSetASCII(_function, "sa",        (void *) 1);
   _keywordSU       = gnameSetASCII(_function, "su",        (void *) 1);
   _keywordV        = gnameSetASCII(_function, "v",         (void *) 1);
   _keywordX        = gnameSetASCII(_function, "x",         (void *) 1);

   GRETURN(TRUE);
}

/********************************************************************
func: galFunctionStop

Clean up.
********************************************************************/
void galFunctionStop(void) 
{
   GENTER;

   Garray *flist;

   flist = ghashCreateKeyArray(_function);
   garrayForEachCell(flist, galFunctionDestroy);
   garrayDestroy(    flist);

   gnameDestroy(_function);
   _function = NULL;

   GRETURN;
}

/********************************************************************
local: 
function:
********************************************************************/
/********************************************************************
func: _Compile
********************************************************************/
int _Compile(GalCommandList *commandList, Gstr *script)
{
   GENTER;

   Gaf          *af;
   Gstr         *name,
                *value;
   GnameKey     *nameKey;
   GalCommand   *command;

   af = gafCreate(gafModeGSTR, script);

   LOOP
   {
      BREAK_IF(!gafGet(af));

      name = gafGetKey(af);

      // Comment or ignorable.
      CONTINUE_IF(gstrIsEmpty(name));

      value = gafGetValue(af);

      nameKey = gnameGetKey(_function, name);
      if (!nameKey)
      {
         nameKey = gnameSet(_function, name, (void *) 1);
      }

      // Create a new command.
      command = galCommandListNew(commandList);

      // Set the function.
      galCommandSetFunctionName(command, nameKey);

      if      (nameKey == _keywordLoop)
      {
         _CompileLoop(command, value);
      }
      else if (nameKey == _keywordIf)
      {
         _CompileIf(command, value);
      }
      else if (nameKey == _keywordVariable)
      {
         _CompileVariable(command, value);
      }
      //else if (nameKey == _keywordType)
      //{
      //   _CompileTypeDefinition(command, value);
      //}
      else 
      {
         _CompileFunctionCall(command, value);
      }
   }

   gafDestroy(af);

   GRETURN TRUE;
}

/********************************************************************
func: _CompileConstant
********************************************************************/
int _CompileConstant(GalParam *param, GnameKey *nameKey, Gstr *value)
{
   GENTER;

   Gdata *data;

   data = galParamGetData(param);

   if (nameKey == _keywordS)
   {
      gdataCreateContent(data, gdataTypeS);
      gdataSetS(         data, value);
      GRETURN TRUE;
   }

   gstrStrip(value, gcharStripWHITE_SPACE_LEADING);

   if      (nameKey == _keywordI)
   {
      // handle b (binary), o (octal), x (hexidecimal) later.
      gdataCreateContent(data, gdataTypeI);
      gdataSetI(         data, gstrGetI(value));
   }
   else if (nameKey == _keywordN)
   {
      gdataCreateContent(data, gdataTypeN);
      gdataSetN(         data, gstrGetN(value));
   }
   else if (nameKey == _keywordR)
   {
      gdataCreateContent(data, gdataTypeR);
      gdataSetR(         data, gstrGetR(value));
   }

   GRETURN TRUE;
}

/********************************************************************
func: _CompileExpression
********************************************************************/
int _CompileExpression(GalParam *param, Gstr *script)
{
   GENTER;

   Gaf            *af;
   Gstr           *name,
                  *value;
   GnameKey       *nameKey;
   GalCommand     *command;
   GalCommandList *commandList;

   af = gafCreate(gafModeGSTR, script);
   RETURN_IF(!af, FALSE);

   // If there isn't an expression then there is a problem.
   if (!gafGet(af))
   {
      gafDestroy(af);
      GRETURN FALSE;
   }

   name = gafGetKey(af);

   // Nothing there?!
   if (gstrIsEmpty(name))
   {
      gafDestroy(af);
      GRETURN FALSE;
   }

   value = gafGetValue(af);

   nameKey = gnameGetKey(_function, name);
   if (!nameKey)
   {
      nameKey = gnameSet(_function, name, (void *) 1);
   }

   // Create a new command.
   commandList = galParamGetCommandList(param);
   command     = galCommandListNew(commandList);

   // Set the function.
   galCommandSetFunctionName(command, nameKey);

   // Can only ever be a function call.
   _CompileFunctionCall(command, value);

   gafDestroy(af);

   GRETURN TRUE;
}

/********************************************************************
func: _CompileFunctionCall
********************************************************************/
int _CompileFunctionCall(GalCommand *command, Gstr *script)
{
   GENTER;

   Gaf            *af;
   Gstr           *name,
                  *value;
   GnameKey       *nameKey;
   GalParamList   *paramList;
   GalParam       *param;

   paramList = galCommandGetParamList(command);

   af = gafCreate(gafModeGSTR, script);

   LOOP
   {
      BREAK_IF(!gafGet(af));

      name = gafGetKey(af);

      // Comment or ignorable.
      CONTINUE_IF(gstrIsEmpty(name));

      value = gafGetValue(af);

      nameKey = gnameGetKey(_function, name);
      if (!nameKey)
      {
         nameKey = gnameSet(_function, name, (void *) 1);
      }

      // Variable being used.
      if      (nameKey == _keywordV)
      {
         param = galParamListNew(paramList);

         galParamSetType(param, galParamTypeVARIABLE);

         _CompileV(param, value);
      }
      // Expression being used.
      else if (nameKey == _keywordX)
      {
         // _Compile Expression
         param = galParamListNew(paramList);

         galParamSetType(param, galParamTypeEXPRESSION);

         _CompileExpression(param, value);
      }
      // Constant of some data type used.
      else if (gdataTypeIsDefined(nameKey))
      {
         param = galParamListNew(paramList);

         galParamSetType(param, galParamTypeDATA);

         _CompileConstant(param, nameKey, value);
      }
   }

   gafDestroy(af);

   GRETURN TRUE;
}

/********************************************************************
func: _CompileIf

Compile an if construct.
********************************************************************/
int _CompileIf(GalCommand *command, Gstr *script)
{
   GENTER;

   Gaf            *af;
   Gstr           *name,
                  *value;
   GnameKey       *nameKey;
   GalCommandList *commandList;
   GalCommand     *newCommand;
   GalParamList   *paramList;
   GalParam       *param;
   int             isLookingForTest,
                   isLookingForTestOrElse,
                   isLookingForThen,
                   result;

   result                 = TRUE;
   isLookingForTest       = TRUE;
   isLookingForTestOrElse = FALSE;
   isLookingForThen       = FALSE;
   af = gafCreate(gafModeGSTR, script);


   paramList = galCommandGetParamList(command);
   param     = galParamListNew(paramList);

   galParamSetType(param, galParamTypeIF_LIST);

   commandList = galParamGetCommandList(param);

   LOOP
   {
      BREAK_IF(!gafGet(af));

      name = gafGetKey(af);

      // Comment or ignorable.
      CONTINUE_IF(gstrIsEmpty(name));

      value = gafGetValue(af);

      nameKey = gnameGetKey(_function, name);
      if (!nameKey)
      {
         nameKey = gnameSet(_function, name, (void *) 1);
      }

      if      (nameKey == _keywordIfTest)
      {
         if (!isLookingForTest &&
             !isLookingForTestOrElse)
         {
            result = FALSE;
            break;
         }

         // Create a new command.
         newCommand = galCommandListNew(commandList);

         // Set the function.
         galCommandSetFunctionName(newCommand, nameKey);

         paramList = galCommandGetParamList(newCommand);

         galParamSetType(param, galParamTypeEXPRESSION);

         _CompileExpression(param, value);

         isLookingForThen       = TRUE;
         isLookingForTest       = FALSE;
         isLookingForTestOrElse = FALSE;
      }
      else if (nameKey == _keywordIfThen)
      {
         if (!isLookingForThen)
         {
            result = FALSE;
            break;
         }

         // Create a new command.
         newCommand = galCommandListNew(commandList);

         // Set the function.
         galCommandSetFunctionName(newCommand, nameKey);

         paramList = galCommandGetParamList(newCommand);
         param     = galParamListNew(paramList);

         galParamSetType(param, galParamTypeSCRIPT);
       
         _Compile(galParamGetCommandList(param), value);

         isLookingForThen       = FALSE;
         isLookingForTest       = TRUE;
         isLookingForTestOrElse = TRUE;
      }
      else if (nameKey == _keywordIfElse)
      {
         if (!isLookingForTestOrElse)
         {
            result = FALSE;
            break;
         }

         // Create a new command.
         newCommand = galCommandListNew(commandList);

         // Set the function.
         galCommandSetFunctionName(newCommand, nameKey);

         paramList = galCommandGetParamList(newCommand);
         param     = galParamListNew(paramList);

         galParamSetType(param, galParamTypeSCRIPT);
       
         _Compile(galParamGetCommandList(param), value);

         // If we see an else, there is nothing else we should 
         // do.  Ignore what ever script is left.
         break;
      }
   }

   gafDestroy(af);

   GRETURN TRUE;
}

/********************************************************************
func: _CompileLoop

Compile the loop contents.
********************************************************************/
int _CompileLoop(GalCommand *command, Gstr *script)
{
   GENTER;

   GalParamList *paramList;
   GalParam     *param;

   paramList = galCommandGetParamList(command);
   param     = galParamListNew(paramList);

   galParamSetType(param, galParamTypeSCRIPT);
 
   GRETURN _Compile(galParamGetCommandList(param), script);
}

/********************************************************************
func: _CompileV

fetch a variable name.
********************************************************************/
int _CompileV(GalParam *param, Gstr *script)
{
   GENTER;

   Gn4           index;
   int           result;
   Gstr         *name;

   result = FALSE;
   name   = gstrCreate();

   // Find the first string.
   // NO COMMENTS ALLOWED HERE!
   for (index = 0; index < gstrGetLength(script); index++)
   {
      if (gcharIsWhiteSpace(gstrGetAt(script, index)))
      {
         BREAK_IF(!gstrIsEmpty(name))
      }
      else
      {
         gstrAppendGchar(name, gstrGetAt(script, index));
      }
   }

   // We found something.
   if (!gstrIsEmpty(name))
   {
      galParamSetVariableName(param, name);
      result = TRUE;
   }

   gstrDestroy(name);

   GRETURN result;
}

/********************************************************************
func: _CompileVariable
********************************************************************/
int _CompileVariable(GalCommand *command, Gstr *script)
{
   GENTER;

   Gaf            *af;
   Gstr           *name,
                  *value;
   GnameKey       *nameKey;
   GalCommand     *newCommand;
   GalCommandList *commandList;
   GalParamList   *paramList;
   GalParam       *param;

   paramList = galCommandGetParamList(command);
   param     = galParamListNew(paramList);

   galParamSetType(param, galParamTypeVARIABLE_LIST);

   commandList = galParamGetCommandList(param);
 
   af = gafCreate(gafModeGSTR, script);

   LOOP
   {
      BREAK_IF(!gafGet(af));

      name = gafGetKey(af);

      value = gafGetValue(af);

      nameKey = gnameGetKey(_function, name);
      if (!nameKey)
      {
         nameKey = gnameSet(_function, name, (void *) 1);
      }

      // Create a new command.
      newCommand = galCommandListNew(commandList);

      // Set the function.
      galCommandSetFunctionName(newCommand, nameKey);

      _CompileVariableNames(newCommand, value);
   }

   gafDestroy(af);

   GRETURN TRUE;
}

/********************************************************************
func: _CompileVariableNames
********************************************************************/
int _CompileVariableNames(GalCommand *command, Gstr *script)
{
   GENTER;

   Gn4             index;
   Gstr           *name;
   GalCommand     *newCommand;
   GalCommandList *commandList;
   GalParamList   *paramList;
   GalParam       *param;

   name      = gstrCreate();
   paramList = galCommandGetParamList(command);
   param     = galParamListNew(paramList);

   galParamSetType(param, galParamTypeVARIABLE_NAME_LIST);

   commandList = galParamGetCommandList(param);

   // fetch all the names in the variable list.
   for (index = 0; index < gstrGetLength(script); index++)
   {
      if (gcharIsWhiteSpace(gstrGetAt(script, index)))
      {
         if (!gstrIsEmpty(name))
         {
            newCommand = galCommandListNew(commandList);
            galCommandSetFunctionName(newCommand, galVariableSet(name));
            gstrSetASCII(name, "");
         }
      }
      else
      {
         gstrAppendGchar(name, gstrGetAt(script, index));
      }
   }

   if (!gstrIsEmpty(name))
   {
      newCommand = galCommandListNew(commandList);
      galCommandSetFunctionName(newCommand, galVariableSet(name));
   }

   gstrDestroy(name);

   GRETURN TRUE;
}
