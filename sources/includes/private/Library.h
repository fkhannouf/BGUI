#pragma once

// Library Base .. is global data shared by all opening the library

struct LibBase
{
	struct Library					lib_Base;
	APTR								lib_SegList;
};

// --
// Library Interface Data .. is only used by the one hold ITest_Library
// and each opener get its own Interface ptr

struct LibData
{
	uint32								LastVal;
};
