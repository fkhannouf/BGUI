
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

/*
** Note:
**  Do not allocate MsgPorts / signals here.
**  We’re running in the Ramdisk/Ramlib/Exec startup context. If you need to
**  allocate any signals, do it in manager_open (the caller’s process context).
*/

PTR _manager_Init( struct LibBase *libBase, PTR SegList, struct ExecIFace *myIExec )
{
struct LibBase *retval;

	retval	= NULL;
	IExec	= (PTR) myIExec;
	SysBase = (PTR) myIExec->Data.LibBase;

	MYDEBUG( "Library : _manager_Init : libBase %p : SegList %p : myIExec %p : SysBase %p :", libBase, SegList, myIExec, SysBase );

	libBase->lib_Base.lib_Node.ln_Type	= NT_LIBRARY;
	libBase->lib_Base.lib_Node.ln_Pri	= LIBPRI;
	libBase->lib_Base.lib_Node.ln_Name	= LIBNAME;
	libBase->lib_Base.lib_Flags			= LIBF_SUMUSED|LIBF_CHANGED;
	libBase->lib_Base.lib_Version		= VERSION;
	libBase->lib_Base.lib_Revision		= REVISION;
	libBase->lib_Base.lib_IdString		= VSTRING;
	libBase->lib_SegList = SegList;

	if ( Resources_Init( libBase ))
	{
		MYDEBUG( "Library : Opening Resources...  Success" );

		/* Set retun value */
		retval = libBase;

		/* Optional: small startup message */
		DebugPrintF( "Library : Rock'n Roll\n" );
	}
	else
	{
		MYERROR( "Library : Opening Resources...  Failed" );

		Resources_Free( libBase );
	}

	return( retval );
}

// --
