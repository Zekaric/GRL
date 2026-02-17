/********************************************************************

file:       gal
authour:    Robbert de Groot
copyright:  2005-2009, Robbert de Groot

description:
This is the entry point for running a gal script.

********************************************************************/

#if !defined(GALH)
#define      GALH

/********************************************************************
constant:
********************************************************************/
typedef enum
{
   galParamTypeNONE,
   galParamTypeDATA,
   galParamTypeEXPRESSION,
   galParamTypeIF_LIST,
   galParamTypePARAMETER_LIST,
   galParamTypeSCRIPT,
   galParamTypeVARIABLE,
   galParamTypeVARIABLE_LIST,
   galParamTypeVARIABLE_NAME_LIST,
} GalParamType;

typedef enum 
{
   galFunctionTypeNONE,
   galFunctionTypeFUNCTION,
   galFunctionTypeSCRIPT
} GalFunctionType;

/********************************************************************
type:
********************************************************************/
typedef Gtarray GalCommandList;
typedef Gtarray GalParamList;
typedef Gtarray GalScopeList;
typedef Garray  GalCommandIndexList;

// Forward references.
typedef struct Gal      Gal;
typedef struct GalScope GalScope;

typedef struct 
{
   GnameKey             *name;
   GalFunctionType       type;
   void                (*function)(Gal *, GalScope *, Gdata *, GalParamList *);
   GalCommandList       *commandList;
} GalFunction;

struct GalScope
{
   GalCommandIndexList  *commandIndexList;
   Gname                *variableList;
};

struct Gal
{
   Gpath                *galRepository;
   GalScopeList         *scopeList;
   Gname                *variableList;
};

typedef union
{
   Gdata                 data;
   GnameKey             *variable;
   GalCommandList       *commandList;
} GalParamData;

typedef struct
{
   GalParamType          type;
   GalParamData          data;
} GalParam;

typedef struct
{
   GnameKey             *functionName;
   GalParamList         *paramList;
} GalCommand;

/********************************************************************
function:
********************************************************************/
// script
GRLFUNC Gal          *galCreate(                Gpath *path);
GRLFUNC Gal          *galCreate_(               Gpath *path);

GRLFUNC void          galDestroy(               Gal *gal);

GRLFUNC int           galIsStarted(             void);

GRLFUNC int           galRun(                   Gal *gal, Gstr *functionName, Gdata *returnData, GalParamList *paramList);

GRLFUNC int           galStart(                 void);
GRLFUNC void          galStop(                  void);

// function
GRLFUNC int           galFunctionCreateFunction(Gstr *functionName, int (*function)(Gal *, GalScope *, Gdata *returnData, GalParamList *));
GRLFUNC int           galFunctionCreateScript(  Gstr *functionName, Gstr *script);

GRLFUNC int           galFunctionDestroy(       Gstr *functionName);

// modules
GRLFUNC void          galMod_Sys(               Gal *gal, GalScope *scope, Garray *line);

/********************************************************************
library: 
function:
********************************************************************/
// Command
        int              galCommandCreateContent(     GalCommand *command);

        int              galCommandDestroyContent(    GalCommand *command);

        GnameKey        *galCommandGetFunctionName(   GalCommand *command);
        GalParamList    *galCommandGetParamList(      GalCommand *command);

        int              galCommandSetFunctionName(   GalCommand *command, GnameKey *functionName);

// CommandIndexList
        GalCommandIndexList 
                        *galCommandIndexListCreate(   void);

        void             galCommandIndexListDestroy(  GalCommandIndexList *commandIndexList);

        Gn4              galCommandIndexListGet(      GalCommandIndexList *commandIndexList);

        int              galCommandIndexListPush(     GalCommandIndexList *commandIndexList);
        int              galCommandIndexListPop(      GalCommandIndexList *commandIndexList);

        int              galCommandIndexListSet(      GalCommandIndexList *commandIndexList, Gn4 value);

// CommandList
        GalCommandList  *galCommandListCreate(        void);

        void             galCommandListDestroy(       GalCommandList *commandList);

        GalCommand      *galCommandListGet(           GalCommandList *commandList, Gn4 index);
        Gn4              galCommandListGetCount(      GalCommandList *commandList);

// Param
        int              galParamCreateContent(       GalParam *param);

        int              galParamDestroyContent(      GalParam *param);

        GalCommandList  *galParamGetCommandList(      GalParam *param);
        Gdata           *galParamGetData(             GalParam *param);
        GalParamType     galParamGetType(             GalParam *param);
        GnameKey        *galParamGetVariableName(     GalParam *param);
        
        int              galParamSetData(             GalParam *param, Gdata *value);
        int              galParamSetType(             GalParam *param, GalParamType value);
        int              galParamSetVariableName(     GalParam *param, Gstr *value);

// ParamList
        GalParamList    *galParamListCreate(          void);

        void             galParamListDestroy(         GalParamList *paramList);

        GalParam        *galParamListGet(             GalParamList *paramList, Gn4 index);
        Gn4              galParamListGetCount(        GalParamList *paramList);

// function
        GalFunction     *galFunctionGet(              Gstr *functionName);
        GalCommandList  *galFunctionGetCommandList(   GalFunction *func);

        int              galFunctionRun(              Gal *gal, GalScope *scope, GalFunction *f, Gdata *returnData, GalParamList *line);

        int              galFunctionStart(            void);
        void             galFunctionStop(             void);

// scope
        int              galScopeCreateContent(       GalScope *scope);

        int              galScopeDestroyContent(      GalScope *scope);

        int              galScopeGetCommandIndex(     GalScope *scope);
        Gdata           *galScopeGetVariable(         GalScope *scope, Gstr *varName);

        int              galScopePopCommandIndex(     GalScope *scope);
        int              galScopePushCommandIndex(    GalScope *scope);
        
        int              galScopeSetCommandIndex(     GalScope *scope, int index);

// ScopeList
        GalScopeList    *galScopeListCreate(          void);

        void             galScopeListDestroy(         GalScopeList *scopeList);

        GalScope        *galScopeListGet(             GalScopeList *scopeList, int index);
        Gn4              galScopeListGetCount(        GalScopeList *scopeList);

        int              galScopeListPop(             GalScopeList *scopeList);

// Variable names
        GnameKey        *galVariableSet(              Gstr *value);
        GnameKey        *galVariableSetASCII(         const char *value);
        int              galVariableStart(            void);
        void             galVariableStop(             void);


#define galCreate(GPATH)            ((Gal *)       gleakCreate(galCreate_(GPATH)))
#define galScopeCreate(GALFUNC, GDATA_RETURN, GALPARAMLIST)\
                                    ((GalScope *)  gleakCreate(galScopeCreate_(GALFUNC, GDATA_RETURN, GALPARAMLIST)))

#define galCommandIndexListCreate()                            garrayCreate()
#define galCommandIndexListDestroy(COMMANDINDEXLIST)           garrayDestroy( COMMANDINDEXLIST)
#define galCommandIndexListGet(    COMMANDINDEXLIST)           garrayGetLastN(COMMANDINDEXLIST)
#define galCommandIndexListPush(   COMMANDINDEXLIST)           garraySetN(    COMMANDINDEXLIST, garrayGetCount(COMMANDINDEXLIST),     0)
#define galCommandIndexListPop(    COMMANDINDEXLIST)           garraySetCount(COMMANDINDEXLIST, garrayGetCount(COMMANDINDEXLIST) - 1)
#define galCommandIndexListSet(    COMMANDINDEXLIST, VALUE)    garraySetN(    COMMANDINDEXLIST, garrayGetCount(COMMANDINDEXLIST) - 1, VALUE)

#define galCommandListCreate()                     gtarrayCreate(  sizeof(GalCommand), galCommandCreateContent, galCommandDestroyContent);
#define galCommandListDestroy( COMMANDLIST)        gtarrayDestroy( COMMANDLIST)
#define galCommandListGet(     COMMANDLIST, INDEX) (GalCommand *) gtarrayGet(COMMANDLIST, INDEX)
#define galCommandListGetCount(COMMANDLIST)        gtarrayGetCount(COMMANDLIST)
#define galCommandListNew(     COMMANDLIST)        (gtarraySetCount(COMMANDLIST, gtarrayGetCount(COMMANDLIST) + 1), (GalCommand *) gtarrayGetLast(COMMANDLIST))

#define galParamListCreate()                       gtarrayCreate(  sizeof(GalParam), galParamCreateContent, galParamDestroyContent)
#define galParamListDestroy(   PARAMLIST)          gtarrayDestroy( PARAMLIST)
#define galParamListGet(       PARAMLIST, INDEX)   (GalParam *) gtarrayGet(PARAMLIST, INDEX)
#define galParamListGetCount(  PARAMLIST)          gtarrayGetCount(PARAMLIST)
#define galParamListNew(       PARAMLIST)          (gtarraySetCount(PARAMLIST, gtarrayGetCount(PARAMLIST) + 1), (GalParam *) gtarrayGetLast(PARAMLIST))

#define galScopeListCreate()                       gtarrayCreate(  sizeof(GalScope), galScopeCreateContent, galScopeDestroyContent)
#define galScopeListDestroy(   SCOPELIST)          gtarrayDestroy( SCOPELIST)
#define galScopeListGet(       SCOPELIST, INDEX)   (GalScope *) gtarrayGet(SCOPELIST, INDEX)
#define galScopeListGetCount(  SCOPELIST)          gtarrayGetCount(SCOPELIST)
#define galScopeListPop(       SCOPELIST)          gtarraySetCount(SCOPELIST, gtarrayGetCount(SCOPELIST) - 1)
#define galScopeListPush(      SCOPELIST)          galScopeListGet(SCOPELIST, galScopeListGetCount(SCOPELIST))

#endif
