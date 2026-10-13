// --

#include "includes/private/common.h"

// --

/*
** Note:
**  Do not allocate MsgPorts / signals here.
**  We’re running in the Ramdisk/Ramlib/Exec startup context. If you need to
**  allocate any signals, do it in manager_open (the caller’s process context).
*/

APTR _manager_Init(struct LibBase* libBase, APTR SegList, struct ExecIFace* myIExec) {
	struct LibBase* retval;

	retval = NULL;
	IExec = (APTR)myIExec;
	SysBase = (APTR)myIExec->Data.LibBase;

	MYDEBUG("Library : _manager_Init : libBase %p : SegList %p : myIExec %p : SysBase %p :", libBase, SegList, myIExec,
	        SysBase);

	libBase->lib_Base.lib_Node.ln_Type = NT_LIBRARY;
	libBase->lib_Base.lib_Node.ln_Pri = LIBPRI;
	libBase->lib_Base.lib_Node.ln_Name = LIBNAME;
	libBase->lib_Base.lib_Flags = LIBF_SUMUSED | LIBF_CHANGED;
	libBase->lib_Base.lib_Version = VERSION;
	libBase->lib_Base.lib_Revision = REVISION;
	libBase->lib_Base.lib_IdString = VSTRING;
	libBase->lib_SegList = SegList;

	if (Resources_Init(libBase)) {
		MYDEBUG("Library : Opening Resources...  Success");

		/* Set retun value */
		retval = libBase;

		/* Optional: small startup message */
		DebugPrintF("Library : Rock'n Roll\n");
	}
	else {
		MYERROR("Library : Opening Resources...  Failed");

		Resources_Free(libBase);
	}

	return (retval);
}

// --
// {
//    struct Library       *lib;
//
//    /*
//     * Assign SysBase.
//     */
//    SysBase  = syslib;
//
//    /*
//     * Open up system libraries.
//     */
//    DOSBase        = (struct DosLibrary *)   OpenLibrary("dos.library",       39);
//    IntuitionBase  = (struct IntuitionBase *)OpenLibrary("intuition.library", 39);
//    GfxBase        = (struct GfxBase *)      OpenLibrary("graphics.library",  39);
//
//    GadToolsBase   = OpenLibrary("gadtools.library",      37);
//    UtilityBase    = OpenLibrary("utility.library",       37);
//    LayersBase     = OpenLibrary("layers.library",        37);
//    AslBase        = OpenLibrary("asl.library",           37);
//    CxBase         = OpenLibrary("commodities.library",   37);
//    KeymapBase     = OpenLibrary("keymap.library",        37);
//    IFFParseBase   = OpenLibrary("iffparse.library",      37);
//    WorkbenchBase  = OpenLibrary("workbench.library",     37);
//    LocaleBase     = OpenLibrary("locale.library",        38);
//    DataTypesBase  = OpenLibrary("datatypes.library",     39);
//
//    InitInputStack();
//
//    /*
//     * All libraries open?
//     */
//    if (DOSBase && IntuitionBase && GfxBase && GadToolsBase && UtilityBase && LayersBase && IFFParseBase && WorkbenchBase
//        && AslBase && CxBase && KeymapBase)
//    {
//       /*
//        * Create the library.
//        */
//       if (BGUIBase = lib = MakeLibrary((APTR)Vectors, NULL, NULL, sizeof(struct Library), NULL))
//       {
//          /*
//           * Initialize library structure.
//           */
//          lib->lib_Node.ln_Type = NT_LIBRARY;
//          lib->lib_Node.ln_Name = (UBYTE *)LibName;
//          lib->lib_Flags        = LIBF_CHANGED | LIBF_SUMUSED;
//          lib->lib_Version      = LIBVER;
//          lib->lib_Revision     = LIBREV;
//          lib->lib_IdString     = (APTR)LibID;
//
//          /*
//           * Globally assign the seglist.
//           */
//          SegList = segment;
//
//          /*
//           * Add us to the system.
//           */
//          AddLibrary(lib);
//
//          /*
//           * Initialize the task-list.
//           */
//          InitTaskList();
//
//          return(lib);
//       }
//    }
//    CloseLibs();
//    return NULL;
// }
// }
