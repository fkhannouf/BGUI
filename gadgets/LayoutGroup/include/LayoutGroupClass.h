/*
 * @(#) $Header$
 *
 * BGUI library
 *
 * (C) Copyright 2000 BGUI Developers Team.
 * (C) Copyright 1998 Manuel Lemos.
 * All Rights Reserved.
 *
 * $Log$
 * Revision 42.2  2003/01/18 19:10:18  chodorowski
 * Instead of using the _AROS or __AROS preprocessor symbols, use __AROS__.
 *
 * Revision 42.1  2000/07/07 17:13:31  stegerg
 * in method structures use STACKULONG, STACKUWORD; etc. Should still
 * work on Amiga, because if __AROS__ is NOT defined, then STACKULONG
 * is defined back to ULONG, STACKUWORD to UWORD, etc. ==> like it
 * was initially.
 *
 * Revision 42.0  2000/05/09 22:21:05  mlemos
 * Bumped to revision 42.0 before handing BGUI to AROS team
 *
 * Revision 41.11  2000/05/09 20:34:52  mlemos
 * Bumped to revision 41.11
 *
 * Revision 1.2  2000/05/09 19:59:54  mlemos
 * Merged with the branch Manuel_Lemos_fixes.
 *
 * Revision 1.1.2.1  2000/05/04 05:08:53  mlemos
 * Initial revision.
 *
 *
 */

#include <intuition/classes.h>

#ifndef __AROS__
#undef STACKULONG
#define STACKULONG ULONG
#endif

struct ogpMGet
{
	STACKULONG MethodID;
	struct TagItem *ogpg_AttrList;
};


#define LGA_TB             BGUI_TB+0x20000
#define LGA_LayoutType     LGA_TB+1
#define LGA_FrontPage      LGA_TB+2

/* Layout group types */
#define LGT_HORIZONTAL        0
#define LGT_VERTICAL          1
#define LGT_PAGED             2
#define LGT_TABLE             3

#define LGM_MB                BGUI_MB+0x20000
#define LGM_MGET              LGM_MB+1

#define LGNA_TB               BGUI_TB+0x30000
#define LGNA_Row              LGNA_TB+1
#define LGNA_Column           LGNA_TB+2
#define LGNA_RowSpan          LGNA_TB+3
#define LGNA_ColumnSpan       LGNA_TB+4
#define LGNA_HorizontalWeight LGNA_TB+5
#define LGNA_VerticalWeight   LGNA_TB+6
#define LGNA_LeftWeight       LGNA_TB+7
#define LGNA_TopWeight        LGNA_TB+8
#define LGNA_WidthWeight      LGNA_TB+9
#define LGNA_HeightWeight     LGNA_TB+10
#define LGNA_RightWeight      LGNA_TB+11
#define LGNA_BottomWeight     LGNA_TB+12
#define LGNA_LeftOffset       LGNA_TB+13
#define LGNA_TopOffset        LGNA_TB+14
#define LGNA_RightOffset      LGNA_TB+15
#define LGNA_BottomOffset     LGNA_TB+16
#define LGNA_LeftSpacing      LGNA_TB+17
#define LGNA_TopSpacing       LGNA_TB+18
#define LGNA_RightSpacing     LGNA_TB+19
#define LGNA_BottomSpacing    LGNA_TB+20
