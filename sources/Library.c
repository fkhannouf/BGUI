#include "includes/private/common.h"

static const APTR _manager_Vectors[] =
{
	(APTR) _manager_Obtain,
	(APTR) _manager_Release,
	(APTR) NULL,
	(APTR) NULL,
	(APTR) _manager_Open,
	(APTR) _manager_Close,
	(APTR) _manager_Expunge,
	(APTR) NULL,
	(APTR) -1
};

static const struct TagItem _manager_Tags[] =
{
	{ MIT_Name,			(Tag) "__library"		},
	{ MIT_VectorTable,	(Tag) _manager_Vectors	},
	{ MIT_Version,		(Tag) 1					},
	{ TAG_END,			(Tag) 0					}
};

// -- Main Interface

static const APTR _main_Vectors[] =
{
	(APTR) _main_Obtain,
	(APTR) _main_Release,
	(APTR) _main_Expunge,
	(APTR) _main_Clone,
	(APTR) _main_FuncAdd,
	(APTR) -1
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

static const APTR libInterfaces[] =
{
	(APTR) _manager_Tags,
	(APTR) _main_Tags,
	(APTR) NULL
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
/* rt_MatchTag	*/ (APTR)	( & lib_res + 0 ),
/* rt_EndSkip	*/ (APTR)	( & lib_res + 1 ),
/* rt_Flags		*/			RTF_NATIVE|RTF_COLDSTART|RTF_AUTOINIT,
/* rt_Version	*/			VERSION,
/* rt_Type		*/			NT_LIBRARY,
/* rt_Pri		*/			LIBPRI,
/* rt_Name		*/ (STRPTR)	LIBNAME,
/* rt_IdString	*/ (STRPTR)	VSTRING,
/* rt_Init		*/ (APTR)	_manager_AutoInit
};

// --
// This is the entry point, if someone tries to run us from shell/wb

int32 _start( STRPTR argstring UNUSED, int32 arglen UNUSED, struct ExecBase *sysbase UNUSED )
{
	return( 0 );
}

// --
