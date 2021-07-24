#ifndef CLIB_BGUI_PROTOS_H
#define CLIB_BGUI_PROTOS_H
/*
 * @(#) $Header$
 *
 * $VER: clib/bgui_protos.h 41.10 (20.1.97)
 * bgui.library prototypes. For use with 32 bit integers only.
 *
 * (C) Copyright 1998 Manuel Lemos.
 * (C) Copyright 1996-1997 Ian J. Einman.
 * (C) Copyright 1993-1996 Jaba Development.
 * (C) Copyright 1993-1996 Jan van den Baard.
 * All Rights Reserved.
 *
 * $Log$
 * Revision 42.0  2000/05/09 22:23:29  mlemos
 * Bumped to revision 42.0 before handing BGUI to AROS team
 *
 * Revision 41.11  2000/05/09 20:02:02  mlemos
 * Merged with the branch Manuel_Lemos_fixes.
 *
 * Revision 41.10.2.2  1998/02/26 22:06:50  mlemos
 * Corrected bgui.h include path
 *
 * Revision 41.10.2.1  1998/02/26 18:04:48  mlemos
 * Restored the include of bgui.h to libraries/
 *
 * Revision 41.10  1998/02/25 21:14:04  mlemos
 * Bumping to 41.10
 *
 * Revision 1.1  1998/02/25 17:16:12  mlemos
 * Ian sources
 *
 *
 */

#ifndef LIBRARIES_BGUI_H
#include <libraries/bgui.h>
#endif

Class *BGUI_GetClassPtr( ULONG );
Object *BGUI_NewObjectA( ULONG, struct TagItem * );
ULONG BGUI_RequestA( struct Window *, struct bguiRequest *, ULONG * );
BOOL BGUI_Help( struct Window *, UBYTE *, UBYTE *, ULONG );
APTR BGUI_LockWindow( struct Window * );
VOID BGUI_UnlockWindow( APTR );
ULONG BGUI_DoGadgetMethodA( Object *, struct Window *, struct Requester *, Msg );

/* Added in V40.4 */
struct BitMap *BGUI_AllocBitMap( ULONG, ULONG, ULONG, ULONG, struct BitMap * );
VOID BGUI_FreeBitMap( struct BitMap * );
struct RastPort *BGUI_CreateRPortBitMap( struct RastPort *, ULONG, ULONG, ULONG );
VOID BGUI_FreeRPortBitMap( struct RastPort * );

/* Added in V40.8 */
VOID BGUI_InfoTextSize( struct RastPort *, UBYTE *, UWORD *, UWORD * );
VOID BGUI_InfoText( struct RastPort *, UBYTE *, struct IBox *, struct DrawInfo * );

/* Added in V41.3 */
STRPTR BGUI_GetLocaleStr( struct bguiLocale *, ULONG );
STRPTR BGUI_GetCatalogStr( struct bguiLocale *, ULONG, STRPTR );

/* Added in V41.4 */
VOID BGUI_FillRectPattern( struct RastPort *, struct bguiPattern *, LONG, LONG, LONG, LONG );

/* Added in V41.6 */
VOID BGUI_PostRender( Class *, Object *, struct gpRender * );

/* Added in V41.7 */
Class *BGUI_MakeClassA( struct TagItem * );
BOOL BGUI_FreeClass( Class * );

/* Added in V41.8 */
ULONG BGUI_PackStructureTags( APTR pack, ULONG *packTable, struct TagItem *tagList );
ULONG BGUI_UnpackStructureTags( APTR pack, ULONG *packTable, struct TagItem *tagList );

/* varargs */
Object *BGUI_NewObject( ULONG, Tag, ... );
ULONG BGUI_Request( struct Window *, struct bguiRequest *, ... );
ULONG BGUI_DoGadgetMethod( Object *, struct Window *, struct Requester *, ULONG, ... );
Class *BGUI_MakeClass( ULONG, ... );
#endif
