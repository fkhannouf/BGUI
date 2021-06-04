/*
 * @(#) $Header$
 *
 * BGUI Tree List View class
 *
 * (C) Copyright 1999 Manuel Lemos.
 * (C) Copyright 1996-1999 Nick Christie.
 * All Rights Reserved.
 *
 * $Log$
 * Revision 42.2  2004/06/16 20:16:49  verhaegs
 * Use METHODPROTO, METHOD_END and REGFUNCPROTOn where needed.
 *
 * Revision 42.1  2000/05/15 19:29:08  stegerg
 * replacements for REG macro
 *
 * Revision 42.0  2000/05/09 22:21:51  mlemos
 * Bumped to revision 42.0 before handing BGUI to AROS team
 *
 * Revision 41.11  2000/05/09 20:35:37  mlemos
 * Bumped to revision 41.11
 *
 * Revision 1.2  2000/05/09 20:00:35  mlemos
 * Merged with the branch Manuel_Lemos_fixes.
 *
 * Revision 1.1.2.2  1999/05/31 01:15:50  mlemos
 * Made the method functions take the arguments in the apropriate registers.
 * Commented out debugging code.
 *
 * Revision 1.1.2.1  1999/02/21 04:07:50  mlemos
 * Nick Christie sources.
 *
 *
 *
 */

/************************************************************************
*******************  TREEVIEW CLASS: MISCELLANEOUS  *********************
************************************************************************/

/************************************************************************
******************************  INCLUDES  *******************************
************************************************************************/

#include "TreeViewPrivate.h"
#include "TVUtil.h"

/************************************************************************
**************************  LOCAL DEFINITIONS  **************************
************************************************************************/


/************************************************************************
*************************  EXTERNAL REFERENCES  *************************
************************************************************************/

/*
 * Functions from TVUtil are listed in TVUtil.h
 */

/************************************************************************
*****************************  PROTOTYPES  ******************************
************************************************************************/


/************************************************************************
*****************************  LOCAL DATA  ******************************
************************************************************************/


/************************************************************************
*****************************  TV_CLEAR()  ******************************
************************************************************************/

METHOD(TV_Clear, struct tvCommand *, tvc)
{
TVData	*tv;

tv = INST_DATA(cl,obj);

DoMethod(tv->tv_Listview,LVM_CLEAR,tvc->tvc_GInfo);
TV_FreeTreeNodeList(tv,RootList(tv));
NewList(RootList(tv));
tv->tv_NumEntries = 0;

return(0);
}
METHOD_END

/************************************************************************
******************************  TV_LOCK()  ******************************
************************************************************************/

METHOD(TV_Lock, Msg, msg)
{
TVData	*tv;

tv = INST_DATA(cl,obj);

if (!tv->tv_LockCount)
	DoMethod(tv->tv_Listview,LVM_LOCKLIST,NULL);

tv->tv_LockCount++;

return(0);
}
METHOD_END

/************************************************************************
*****************************  TV_UNLOCK()  *****************************
************************************************************************/

METHOD(TV_Unlock, struct tvCommand *, tvc)
{
TVData	*tv;

tv = INST_DATA(cl,obj);

if (tv->tv_LockCount)
	{
	tv->tv_LockCount--;

	if (!tv->tv_LockCount)
		DoMethod(tv->tv_Listview,LVM_UNLOCKLIST,tvc->tvc_GInfo);
	}

return(0);
}
METHOD_END

/************************************************************************
******************************  TV_SORT()  ******************************
*************************************************************************
* STUB! TV_SORT
*
*************************************************************************/

METHOD(TV_Sort, struct tvCommand *, tvc)
{
return(0);
}
METHOD_END

/************************************************************************
*****************************  TV_REDRAW()  *****************************
*************************************************************************
* STUB! TV_Redraw is using LVM_REFRESH for the moment because of lv bugs.
*
*************************************************************************/

METHOD(TV_Redraw, struct tvCommand *, tvc)
{
TVData	*tv;

tv = INST_DATA(cl,obj);

return(DoMethod(tv->tv_Listview,LVM_REFRESH,tvc->tvc_GInfo));
}
METHOD_END

/************************************************************************
****************************  TV_REFRESH()  *****************************
************************************************************************/

METHOD(TV_Refresh, struct tvCommand *, tvc)
{
TVData	*tv;

tv = INST_DATA(cl,obj);

return(DoMethod(tv->tv_Listview,LVM_REFRESH,tvc->tvc_GInfo));
}
METHOD_END

/************************************************************************
****************************  TV_REBUILD()  *****************************
*************************************************************************
* For debugging use only, clears the listview and reconstructs the
* entries that should be in it from the tree.
*
*************************************************************************/

METHOD(TV_Rebuild, struct tvCommand *, tvc)
{
TVData	*tv;
TNPTR	tn;
BOOL	ok;

tv = INST_DATA(cl,obj);

DoMethod(tv->tv_Listview,LVM_CLEAR,NULL);

tn = FirstChildIn(RootList(tv));
ok = TRUE;

while(tn && ok)
	{
	/* debug
	KPrintF("TVM_REBUILD: Parent:%-16s  Node:%-16s\n",
		tn->tn_Parent ? (STRPTR) tn->tn_Parent->tn_Entry : "Root",
		tn->tn_Entry);
	*/

	ok = (BOOL) DoMethod(tv->tv_Listview,LVM_ADDSINGLE,NULL,tn,LVAP_TAIL,0);
	tn = TV_GetNextTreeNode(tn,TVF_VISIBLE,0,~0);
	}

	/* debug
if (!ok)
	KPrintF("TVM_REBUILD: *** Failed to add to listview! ***\n");
	*/

DoMethod(tv->tv_Listview,LVM_REFRESH,tvc->tvc_GInfo);

return((ULONG) ok);
}
METHOD_END

