/******************************************************************************
file:       gpinPin
author:     Robbert de Groot
copyright:  2000-2009, Robbert de Groot

description:

What is a plugin?
-----------------
A plugin is generally a dynamically loaded program chunk.  Often it can be
an optional chunk of code.  Meaning, that it may not need to be there.

gpin is a very basic plugin manager.  It keeps track of named interfaces.
Basically a Name->Pin Structure (key->value) relationship.  Each Pin Structure
must have a unique name.  If someone isn't playing nice and using the same name
as something else, gpin doesn't care, it assumes intelligence on the coding front.

What is a pin structure?
------------------------
A pin struct is something like...

typedef struct
{
   int   constMY_VAL_1;
   int   constMY_VAL_2;

   void (*Create)(       void);
   int  (*CreateContent)(Gp *my);

   int  (*Destroy)(      Gp *my);

   int  (*Run)(          Gp *my);
} MyPin;

It holds the constants and the functions for the plugin that are exposed
to the world.

So if you make a plugin and want to use to let others use the innerds of your
plugin, then all you have to provide is a header file with the name and pin
structure of your plugin.  From there the other plugins will be able to access
your stuff.

How do I make a plugin?
-----------------------
You only need to expose one function to gpin in your plugin.

int gpinMain(GpinPin *pin);

When your plugin is loaded, this function is called.  Gpin's pin
structure is provided to you.  This means from there, you can fetch
whatever other plugins that were given to gpin.

How do I expose internals as a plugin?
--------------------------------------
You simply have to set up a pin structure and pass it off to gpin.

How do I send a message to all plugins?
How do I deal with versioning of plugins?
How do I...?
-----------------------------------------
This is where gpin's purview ends.  Like I said, it's a very simple
plugin manager.  From here on out you need to build on top of gpin
to handle other management features.

******************************************************************************/

#if !defined(GPINPINH)
#define      GPINPINH

/******************************************************************************
constant:
******************************************************************************/
#define gpinPIN_NAME L"Gpin"

typedef struct
{
   // Add a plugin to the plugin manager.
   // function struct is a pointer to a static structure with all the functions
   // and constants preset.
   Gb (*Add)(        Gc2 const *name, Gp *functionStruct);

   // Add a plugin DLL.
   // Plugin manager will immediately call int gpinMain(GpinPin *pin) inside that plugin.
   // Returns gbFALSE if something went wrong.  If something went wrong the DLL is not
   // loaded.
   Gb (*AddModule)(  Gc2 const *pinFileName);

   // Get a plugin function structure.
   // Returns the pointer to the function structure.
   Gp *(*Get)(       Gc2 const *name);
} GpinPin;

#endif
