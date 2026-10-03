
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#include "inc_private/All.h"

// --

static const PTR _manager_Vectors[] =
{
	(PTR) _manager_Obtain,
	(PTR) _manager_Release,
	(PTR) NULL,
	(PTR) NULL,
	(PTR) _manager_Open,
	(PTR) _manager_Close,
	(PTR) _manager_Expunge,
	(PTR) NULL,
	(PTR) -1
};

static const struct TagItem _manager_Tags[] =
{
	{ MIT_Name,			(Tag) "__library"		},
	{ MIT_VectorTable,	(Tag) _manager_Vectors	},
	{ MIT_Version,		(Tag) 1					},
	{ TAG_END,			(Tag) 0					}
};

// -- Main Interface

static const PTR _main_Vectors[] =
{
	(PTR) _main_Obtain,
	(PTR) _main_Release,
	(PTR) _main_Expunge,
	(PTR) _main_Clone,
	(PTR) _main_FuncAdd,
	(PTR) -1
};

// Note: if you don't need a unique ITest_Library for
// each opener.. you can comment out the MIT_Flags, then
// all openers get the same ITest_Library interface
// but you loose LibData, and only have LibBase
const struct TagItem _main_Tags[] =
{
	{ MIT_Name,			(Tag) "main"		},
	{ MIT_VectorTable,	(Tag) _main_Vectors	},
	{ MIT_DataSize,		(Tag) sizeof( struct LibData ) },
	{ MIT_Flags,		(Tag) IFLF_PRIVATE	},
	{ MIT_Version,		(Tag) 1				},
	{ TAG_END,			(Tag) 0				}
};

// --

static const PTR libInterfaces[] =
{
	(PTR) _manager_Tags,
	(PTR) _main_Tags,
	(PTR) NULL
};

// --
// if you want you can add a litte extra info for version
// string if you want.. but that is optional
// maybe a copyright line?

static USED char	verstag[] = VERSTAG;
//static USED char	verstag[] = VERSTAG "Coded by awesome me";

// --
// AutoInit informations

static const struct TagItem _manager_AutoInit[] = 
{ 
	{ CLT_DataSize,			(Tag) sizeof( struct LibBase )	},
	{ CLT_InitFunc,			(Tag) _manager_Init				},
	{ CLT_Interfaces,		(Tag) libInterfaces				},
	{ CLT_NoLegacyIFace,	(Tag) TRUE						},
	{ TAG_END,				(Tag) 0							}
};

static USED const struct Resident lib_res =
{
/* rt_MatchWord	*/			RTC_MATCHWORD,
/* rt_MatchTag	*/ (PTR)	( & lib_res + 0 ),
/* rt_EndSkip	*/ (PTR)	( & lib_res + 1 ),
/* rt_Flags		*/			RTF_NATIVE|RTF_COLDSTART|RTF_AUTOINIT,
/* rt_Version	*/			VERSION,
/* rt_Type		*/			NT_LIBRARY,
/* rt_Pri		*/			LIBPRI,
/* rt_Name		*/ (STR)	LIBNAME,
/* rt_IdString	*/ (STR)	VSTRING,
/* rt_Init		*/ (PTR)	_manager_AutoInit
};

// --
// This is the entry point, if someone tries to run us from shell/wb

S32 _start( STR argstring UNUSED, S32 arglen UNUSED, struct ExecBase *sysbase UNUSED )
{
	return( 0 );
}

// --
