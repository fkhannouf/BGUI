/*
 * @(#) $Header$
 *
 * BGUI library
 * libfunc.c
 *
 * (C) Copyright 1998 Manuel Lemos.
 * (C) Copyright 1996-1997 Ian J. Einman.
 * (C) Copyright 1993-1996 Jaba Development.
 * (C) Copyright 1993-1996 Jan van den Baard.
 * All Rights Reserved.
 *
 * $Log$
 * Revision 42.0  2000/05/09 22:09:23  mlemos
 * Bumped to revision 42.0 before handing BGUI to AROS team
 *
 * Revision 41.11  2000/05/09 19:54:33  mlemos
 * Merged with the branch Manuel_Lemos_fixes.
 *
 * Revision 41.10.2.11  2000/05/04 04:39:06  mlemos
 * Added the entries to the now built-in supported bar and layout group gadget
 * classes.
 *
 * Revision 41.10.2.10  1999/08/17 19:11:24  mlemos
 * Prevented base class from being replaced by an external library.
 *
 * Revision 41.10.2.9  1999/07/31 01:56:02  mlemos
 * Added code to keep track of created objects.
 *
 * Revision 41.10.2.8  1999/07/29 00:43:47  mlemos
 * Ensured that external library classes can only be freed if they get marked
 * as such.
 *
 * Revision 41.10.2.7  1999/07/28 23:17:11  mlemos
 * Allowed the library to be expunged if there no remainining classes with
 * open subclasses but without any objects to be disposed.
 *
 * Revision 41.10.2.6  1999/07/28 16:38:05  mlemos
 * Added code to detect class object leaks in FreeClasses.
 * Made FreeClasses iterate until the number of classes subclasses that remain
 * to be freed does not change.
 *
 * Revision 41.10.2.5  1999/07/18 02:58:03  mlemos
 * Fixed problem of BGUI_CallHookPkt using the stack frame to store local
 * variables that were pointing to the wrong address after EnsureStack was
 * called.
 *
 * Revision 41.10.2.4  1999/07/03 15:16:54  mlemos
 * Added the function BGUI_CallHookPkt.
 * Replaced the calls to CallHookPkt to BGUI_CallHookPkt.
 *
 * Revision 41.10.2.3  1999/05/31 00:45:03  mlemos
 * Added the TreeView gadget to the list of internally supported gadgets.
 *
 * Revision 41.10.2.2  1998/10/12 01:26:56  mlemos
 * Made the ARexx be initialized internally whenever is needed.
 *
 * Revision 41.10.2.1  1998/03/02 23:51:17  mlemos
 * Switched vector allocation functions calls to BGUI allocation functions.
 *
 * Revision 41.10  1998/02/25 21:12:26  mlemos
 * Bumping to 41.10
 *
 * Revision 1.1  1998/02/25 17:08:50  mlemos
 * Ian sources
 *
 *
 */

#include "include/classdefs.h"

/*
 * Internal lock housekeeping.
 */
typedef struct {
   struct Requester      wl_IDCMPLock;       /* Requester lock.   */
   struct Window        *wl_Locked;       /* Locked window. */
   UWORD           wl_MinWidth, wl_MinHeight;   /* Current sizes. */
   UWORD           wl_MaxWidth, wl_MaxHeight;   /*     "      "         */
}  WINDOWLOCK;


#ifdef DEBUG_BGUI

static ULONG object_serial_number=1;

struct ObjectTracking
{
   struct ObjectTracking *Next;
   Object *Object;
   ULONG SerialNumber;
   STRPTR File;
   ULONG Line;
};

static struct ObjectTracking *tracked_objects=NULL;

makeproto ULONG TrackNewObject(Object *object,struct TagItem *tags)
{
   struct ObjectTracking *track;

   if((track=BGUI_AllocPoolMem(sizeof(*track)))==NULL)
      return(0);
   track->Object=object;
   Forbid();
   track->SerialNumber=object_serial_number++;
   track->Next=tracked_objects;
   tracked_objects=track;
   Permit();
   return(track->SerialNumber);
}

makeproto BOOL TrackDisposedObject(Object *object)
{
   struct ObjectTracking **track,*found;

   Forbid();
   for(track= &tracked_objects;(found= *track) && (*track)->Object!=object;track= &(*track)->Next);
   if(found)
   {
      *track= found->Next;
      BGUI_FreePoolMem(found);
   }
   else
      bug("*** Could not track disposed object %lX\n",object);
   Permit();
   return((BOOL)(found!=NULL));
   
}

static void DumpTrackedObjects(void)
{
   Forbid();
   while(tracked_objects)
   {
      struct ObjectTracking *track;

      track= tracked_objects;
      tracked_objects=track->Next;
      bug("*** Object %lX leaked! Serial number %lu\n",track->Object,track->SerialNumber);
      BGUI_FreePoolMem(track);
   }
   Permit();
}

#endif

/*
 * Table for class init stuff.
 */
typedef struct {
   Class                *cd_Storage;
   Class              *(*cd_InitFunc)(void);
   UWORD                 cd_ClassID;
   UBYTE                *cd_ClassFile;
   struct BGUIClassBase *cd_ClassBase;
   struct TagItem       *cd_DefTags;
   BOOL                  cd_Leaking;
   BOOL                  cd_LibraryClass;
}  CLASSDEF;

STATIC CLASSDEF Classes[] =
{
   { NULL, InitGroupNodeClass,   BGUI_GROUP_NODE,         NULL,                              NULL, FALSE, FALSE },

   { NULL, InitDGMClass,         BGUI_DGM_OBJECT,         NULL,                              NULL, FALSE, FALSE },
   { NULL, InitRootClass,        BGUI_ROOT_OBJECT,        NULL,                              NULL, FALSE, FALSE },

   /*
    * Graphic classes.
    */
   { NULL, InitTextClass,        BGUI_TEXT_GRAPHIC,       NULL,                              NULL, FALSE, FALSE },

   /*
    * Image classes.
    */
   { NULL, InitImageClass,       BGUI_IMAGE_OBJECT,       NULL,                              NULL, FALSE, FALSE },
   { NULL, InitFrameClass,       BGUI_FRAME_IMAGE,        "images/bgui_frame.image",         NULL, FALSE, FALSE },
   { NULL, InitLabelClass,       BGUI_LABEL_IMAGE,        "images/bgui_label.image",         NULL, FALSE, FALSE },
   { NULL, InitVectorClass,      BGUI_VECTOR_IMAGE,       "images/bgui_vector.image",        NULL, FALSE, FALSE },
   { NULL, InitSystemClass,      BGUI_SYSTEM_IMAGE,       "images/bgui_system.image",        NULL, FALSE, FALSE },

   /*
    * Gadget classes.
    */
   { NULL, InitGadgetClass,      BGUI_GADGET_OBJECT,      NULL,                              NULL, FALSE, FALSE },
   { NULL, InitBaseClass,        BGUI_BASE_GADGET,        NULL,                              NULL, FALSE, FALSE },
   { NULL, InitButtonClass,      BGUI_BUTTON_GADGET,      "gadgets/bgui_button.gadget",      NULL, FALSE, FALSE },
   { NULL, InitGroupClass,       BGUI_GROUP_GADGET,       "gadgets/bgui_group.gadget",       NULL, FALSE, FALSE },
   { NULL, InitCycleClass,       BGUI_CYCLE_GADGET,       "gadgets/bgui_cycle.gadget",       NULL, FALSE, FALSE },
   { NULL, InitCheckBoxClass,    BGUI_CHECKBOX_GADGET,    "gadgets/bgui_checkbox.gadget",    NULL, FALSE, FALSE },
   { NULL, InitInfoClass,        BGUI_INFO_GADGET,        "gadgets/bgui_info.gadget",        NULL, FALSE, FALSE },
   { NULL, InitStringClass,      BGUI_STRING_GADGET,      "gadgets/bgui_string.gadget",      NULL, FALSE, FALSE },
   { NULL, InitPropClass,        BGUI_PROP_GADGET,        "gadgets/bgui_prop.gadget",        NULL, FALSE, FALSE },
   { NULL, InitIndicatorClass,   BGUI_INDICATOR_GADGET,   "gadgets/bgui_indicator.gadget",   NULL, FALSE, FALSE },
   { NULL, InitProgressClass,    BGUI_PROGRESS_GADGET,    "gadgets/bgui_progress.gadget",    NULL, FALSE, FALSE },
   { NULL, InitSliderClass,      BGUI_SLIDER_GADGET,      "gadgets/bgui_slider.gadget",      NULL, FALSE, FALSE },
   { NULL, InitPageClass,        BGUI_PAGE_GADGET,        "gadgets/bgui_page.gadget",        NULL, FALSE, FALSE },
   { NULL, InitMxClass,          BGUI_MX_GADGET,          "gadgets/bgui_mx.gadget",          NULL, FALSE, FALSE },
   { NULL, InitListClass,        BGUI_LISTVIEW_GADGET,    "gadgets/bgui_listview.gadget",    NULL, FALSE, FALSE },
   { NULL, InitExtClass,         BGUI_EXTERNAL_GADGET,    "gadgets/bgui_external.gadget",    NULL, FALSE, FALSE },
   { NULL, InitSepClass,         BGUI_SEPARATOR_GADGET,   "gadgets/bgui_separator.gadget",   NULL, FALSE, FALSE },
   { NULL, InitRadioButtonClass, BGUI_RADIOBUTTON_GADGET, "gadgets/bgui_radiobutton.gadget", NULL, FALSE, FALSE },
   { NULL, InitAreaClass,        BGUI_AREA_GADGET,        "gadgets/bgui_area.gadget",        NULL, FALSE, FALSE },
   { NULL, InitViewClass,        BGUI_VIEW_GADGET,        "gadgets/bgui_view.gadget",        NULL, FALSE, FALSE },

   { NULL, NULL,                 BGUI_PALETTE_GADGET,     "gadgets/bgui_palette.gadget",     NULL, FALSE, FALSE },
   { NULL, NULL,                 BGUI_POPBUTTON_GADGET,   "gadgets/bgui_popbutton.gadget",   NULL, FALSE, FALSE },
   { NULL, NULL,                 BGUI_TREEVIEW_GADGET,    "gadgets/bgui_treeview.gadget",    NULL, FALSE, FALSE },
   { NULL, NULL,                 BGUI_BAR_GADGET,         "gadgets/bgui_bar.gadget",         NULL, FALSE, FALSE },
   { NULL, NULL,                 BGUI_LAYOUTGROUP_GADGET, "gadgets/bgui_layoutgroup.gadget", NULL, FALSE, FALSE },

   /*
    * Misc. classes.
    */
   { NULL, InitWindowClass,      BGUI_WINDOW_OBJECT,      "bgui_window.class",               NULL, FALSE, FALSE },
   { NULL, InitCxClass,          BGUI_COMMODITY_OBJECT,   "bgui_commodity.class",            NULL, FALSE, FALSE },
   { NULL, InitAslReqClass,      BGUI_ASLREQ_OBJECT,      "bgui_aslreq.class",               NULL, FALSE, FALSE },
   { NULL, InitFileReqClass,     BGUI_FILEREQ_OBJECT,     "bgui_filereq.class",              NULL, FALSE, FALSE },
   { NULL, InitFontReqClass,     BGUI_FONTREQ_OBJECT,     "bgui_fontreq.class",              NULL, FALSE, FALSE },
   { NULL, InitScreenReqClass,   BGUI_SCREENREQ_OBJECT,   "bgui_screenreq.class",            NULL, FALSE, FALSE },

   { NULL, InitArexxClass,       BGUI_AREXX_OBJECT,       "bgui_arexx.class",                NULL, FALSE, FALSE },

   { NULL, InitSpacingClass,     BGUI_SPACING_OBJECT,     NULL,                              NULL, FALSE, FALSE },

   { NULL, NULL,                 (UWORD)~0,               NULL }
};

/*
 * Free the classes. Returns FALSE if one of the classes
 * fail to free.
 */
makeproto BOOL FreeClasses(void)
{
   CLASSDEF       *cd;
   BOOL            rc = TRUE;
   ULONG subclasses,last_subclasses=0,opened_classes;

   Forbid();
   do   
   {
      opened_classes=subclasses=0;
      for (cd = Classes; cd->cd_ClassID != (UWORD)~0; cd++)
      {
         if(last_subclasses==0)
            cd->cd_Leaking=FALSE;
         if (cd->cd_Storage)
         {
            if (cd->cd_LibraryClass)
            {
               if(cd->cd_ClassBase)
               {
                  CloseLibrary((struct Library *)cd->cd_ClassBase);
                  cd->cd_ClassBase = NULL;
               }
               opened_classes++;
               rc=FALSE;
            }
            else
            {
               /*
                * Return FALSE if one or more fail to free.
                */
               if (!BGUI_FreeClass(cd->cd_Storage))
               {
                  rc = FALSE;
                  if(cd->cd_Storage->cl_SubclassCount)
                  {
                     subclasses+=cd->cd_Storage->cl_SubclassCount;
                     if(cd->cd_Storage->cl_ObjectCount)
                        opened_classes++;
                  }
                  else
                  {
                     if(!cd->cd_Leaking)
                     {
                        cd->cd_Leaking=TRUE;
                        D(bug("*** Object leak of class %lu: Class %lX, Object count %lu\n",cd->cd_ClassID,cd->cd_Storage,cd->cd_Storage->cl_ObjectCount));
                     }
                  }
               }
               else
                  cd->cd_Storage = NULL;
            };
         }
         else
            cd->cd_LibraryClass=FALSE;
      };
      if(last_subclasses==subclasses)
         break;
      last_subclasses=subclasses;
   }
   while(subclasses);
   if(!rc)
   {
      if(opened_classes==0)
      {
         for (cd = Classes; cd->cd_ClassID != (UWORD)~0; cd++)
            cd->cd_Storage = NULL;
#ifdef DEBUG_BGUI
         DumpTrackedObjects();
#endif
         rc=TRUE;
      }
      else
      {
         D(bug("Opened classes %lu\n",opened_classes));
      }
   }
   Permit();
   return rc;
}

makeproto void MarkFreedClass(Class *cl)
{
   CLASSDEF       *cd;

   Forbid();
   for (cd = Classes; cd->cd_ClassID != (UWORD)~0; cd++)
   {
      if(cl==cd->cd_Storage)
      {
         cd->cd_Storage = NULL;
         break;
      }
   }
   Permit();
}


/*
 * Obtain a class pointer. This routine will only fail if you pass it
 * a non-existing class ID, or the class fails to initialize.
 */
makeproto SAVEDS ASM Class *BGUI_GetClassPtr(REG(d0) ULONG classID)
{
   CLASSDEF     *cd;
   Class        *cl = NULL;


   for (cd = Classes; cd->cd_ClassID != (UWORD)~0; cd++)
   {
      if (classID == (UWORD)cd->cd_ClassID)
      {
         if (!(cl = cd->cd_Storage))
         {
            if (cd->cd_ClassFile)
            {
               if (cd->cd_ClassBase = (struct BGUIClassBase *)OpenLibrary(cd->cd_ClassFile, 0))
               {
                  /*
                   * Get the class pointer.
                   */
                  cl = cd->cd_ClassBase->bcb_Class;
                  cd->cd_LibraryClass=TRUE;
               };
            };
            if (!cl && cd->cd_InitFunc)
            {
               /*
                * Call the initialization routine.
                */
               cl = (cd->cd_InitFunc)();
            };
            cd->cd_Storage = cl;
         };
         break;
      };
   };
   return cl;
}

/*
 * Var-args stub for BGUI_NewObjectA().
 */
makeproto Object *BGUI_NewObject(ULONG classID, Tag tag1, ...)
{
   return BGUI_NewObjectA(classID, (struct TagItem *)&tag1);
}

/*
 * Create an object from a class.
 */
makeproto SAVEDS ASM Object *BGUI_NewObjectA(REG(d0) ULONG classID, REG(a0) struct TagItem *attr)
{
   Class       *cl;
   Object      *obj = NULL;

   if (cl = BGUI_GetClassPtr(classID))
      obj = NewObjectA(cl, NULL, attr);

   return obj;
}

/*
 * Allocate a bitmap.
 */
makeproto SAVEDS ASM struct BitMap *BGUI_AllocBitMap(REG(d0) ULONG width, REG(d1) ULONG height, REG(d2) ULONG depth,
   REG(d3) ULONG flags, REG(a0) struct BitMap *fr)
{
   #ifdef ENHANCED
   return AllocBitMap(width, height, depth, flags | BMF_MINPLANES, fr);
   #else
   struct BitMap  *bm = NULL;
   ULONG          *b;
   int             i, rassize;

   /*
    * Use the system routine if
    * we are running OS 3.0 or better.
    */
   if (OS30)
      return AllocBitMap(width, height, depth, flags | BMF_MINPLANES, fr);

   /*
    * Not OS 3.0 or better?
    * Make the bitmap ourselves.
    */
   if (b = (ULONG *)BGUI_AllocPoolMem(sizeof(struct BitMap) + sizeof(ULONG)))
   {
      *b = ID_BGUI;
      bm = (struct BitMap *)(b + 1);
      InitBitMap(bm, depth, width, height);

      flags = flags & BMF_CLEAR ? MEMF_CHIP : MEMF_CHIP | MEMF_CLEAR;
      rassize = RASSIZE(width, height);
      
      /*
       * Allocate planes.
       */
      for (i = 0; i < depth; i++)
      {
         if (!(bm->Planes[i] = AllocVec(rassize, flags)))
         {
            BGUI_FreeBitMap(bm);
            return NULL;
         };
      };
   }
   return bm;
   #endif
}

/*
 * Free a bitmap.
 */
makeproto SAVEDS ASM VOID BGUI_FreeBitMap(REG(a0) struct BitMap *bm)
{
   #ifdef ENHANCED
   WaitBlit();
   FreeBitMap(bm);
   #else

   ULONG    *b = ((ULONG *)bm) - 1;
   int       i;
   UBYTE    *p;
   
   if (bm)
   {
      /*
       * Wait for the blitter.
       */
      WaitBlit();

      /*
       * Under OS 3.0 we call the system routine.
       */
      if (*b == ID_BGUI)
      {
         for (i = bm->Depth - 1; i >= 0; --i)
         {
            /*
             * Free planes.
             */
            if (p = bm->Planes[i]) FreeVec(p);
         };
         /*
          * Free the structure.
          */
         BGUI_FreePoolMem(b);
      }
      else
      {
         FreeBitMap(bm);
      };
   };
   #endif
}

/*
 * Allocate a rastport with bitmap.
 */
makeproto SAVEDS ASM struct RastPort *BGUI_CreateRPortBitMap(REG(a0) struct RastPort *source,
   REG(d0) ULONG width, REG(d1) ULONG height, REG(d2) ULONG depth)
{
   struct RastPort   *rp;
   struct Layer_Info *li;

   /*
    * Allocate a rastport structure.
    */
   if (rp = (struct RastPort *)BGUI_AllocPoolMem(sizeof(struct RastPort)))
   {
      /*
       * If we have a source rastport we
       * copy it. Otherwise we initialize
       * the rastport.
       */
      if (source) *rp = *source;
      else        InitRastPort(rp);

      if (!depth && source) depth = FGetDepth(source);

      /*
       * Add a bitmap.
       */
      if (rp->BitMap = BGUI_AllocBitMap(width, height, depth, BMF_CLEAR, source ? source->BitMap : NULL))
      {
         /*
          * NO LAYER!.
          */
         // rp->Layer = NULL;

         if (li = NewLayerInfo())
         {
            if (rp->Layer = CreateUpfrontLayer(li, rp->BitMap, 0, 0, width - 1, height - 1, 0, NULL))
            {
               /*
                * Mark it as a buffered rastport.
                */
               // rp->RP_User = ID_BFRP;

               return rp;
            };
            /*
             * No layer.
             */
            DisposeLayerInfo(li);
         };
         /*
          * No layerinfo.
          */
         BGUI_FreeBitMap(rp->BitMap);
      }
      /*
       * No bitmap.
       */
      BGUI_FreePoolMem(rp);
   }
   return NULL;
}

/*
 * Free a buffer rastport and bitmap.
 */
makeproto SAVEDS ASM VOID BGUI_FreeRPortBitMap(REG(a0) struct RastPort *rp)
{
   struct Layer      *l  = rp->Layer;
   struct Layer_Info *li = l->LayerInfo;

   /*
    * Free the layer.
    */
   InstallClipRegion(l, NULL);
   DeleteLayer(NULL, l);
   
   /*
    * Free the layerinfo.
    */
   DisposeLayerInfo(li);
   
   /*
    * Free the bitmap.
    */
   BGUI_FreeBitMap(rp->BitMap);

   /*
    * Free the rastport.
    */
   BGUI_FreePoolMem(rp);
}

/*
 * Show AmigaGuide file.
 */
makeproto SAVEDS ASM BOOL BGUI_Help(REG(a0) struct Window *win, REG(a1) UBYTE *file, REG(a2) UBYTE *node, REG(d0) ULONG line)
{
   struct NewAmigaGuide       nag = { NULL };

   /*
    * Initialize structure.
    */
   nag.nag_Name      = ( STRPTR )file;
   nag.nag_Node      = ( STRPTR )node;
   nag.nag_Line      = line;
   nag.nag_Screen    = win ? win->WScreen : NULL;

   /*
    * Show file.
    */
   return( DisplayAGuideInfo( &nag, TAG_END ));
}


/*
 * Set or clear the busy pointer.
 */
STATIC ASM VOID Busy(REG(a0) struct Window *win, REG(d0) BOOL set)
{
   #ifdef ENHANCED

   if (set) SetWindowPointer(win, WA_BusyPointer, TRUE, WA_PointerDelay, TRUE, TAG_END);
   else     SetWindowPointer(win, TAG_END);

   #else

   /*
    * Must be in chip memory (busy pointer on OS 2.04 machines).
    */
   static __chip UWORD BusyPointer[] =
   {
      0x0000, 0x0000, 0x0400, 0x07c0, 0x0000, 0x07c0, 0x0100, 0x0380,
      0x0000, 0x07e0, 0x07c0, 0x1ff8, 0x1FF0, 0x3FEC, 0x3FF8, 0x7FDE,
      0x3FF8, 0x7FBE, 0x7FFC, 0xFF7F, 0x7EFC, 0xFFFF, 0x7FFC, 0xFFFF,
      0x3FF8, 0x7FFE, 0x3FF8, 0x7FFE, 0x1FF0, 0x3FFC, 0x07C0, 0x1FF8,
      0x0000, 0x07E0, 0x0000, 0x0000
   };

   if (OS30)
   {
      if (set) SetWindowPointer(win, WA_BusyPointer, TRUE, WA_PointerDelay, TRUE, TAG_END);
      else     SetWindowPointer(win, TAG_END);
   }
   else
   {
      if (set) SetPointer(win, BusyPointer, 16, 16, -6, 0 );
      else     ClearPointer(win );
   }

   #endif
}

/*
 * Lock a window.
 */
makeproto SAVEDS ASM APTR BGUI_LockWindow( REG(a0) struct Window *win )
{
   WINDOWLOCK        *wl;

   /*
    * Allocate lock structure.
    */
   if ( wl = ( WINDOWLOCK * )BGUI_AllocPoolMem( sizeof( WINDOWLOCK ))) {
      /*
       * Initialize structure.
       */
      wl->wl_Locked   = win;

      /*
       * Copy current min/max sizes.
       */
      *IBOX( &wl->wl_MinWidth ) = *IBOX( &win->MinWidth );

      /*
       * Setup and open requester.
       */
      InitRequester( &wl->wl_IDCMPLock );
      Request( &wl->wl_IDCMPLock, win );

      /*
       * Set busy pointer.
       */
      Busy( win, TRUE );

      /*
       * Disable sizing.
       */
      WindowLimits( win, win->Width, win->Height, win->Width, win->Height );
   }

   return( wl );
}

/*
 * Unlock a window.
 */
makeproto SAVEDS ASM VOID BGUI_UnlockWindow( REG(a0) APTR lock )
{
   WINDOWLOCK        *wl = ( WINDOWLOCK * )lock;

   /*
    * A NULL lock is safe.
    */
   if ( wl ) {
      /*
       * Setup limits.
       */
      WindowLimits( wl->wl_Locked, wl->wl_MinWidth, wl->wl_MinHeight, wl->wl_MaxWidth, wl->wl_MaxHeight );

      /*
       * End request.
       */
      EndRequest( &wl->wl_IDCMPLock, wl->wl_Locked );

      /*
       * Clear busy pointer.
       */
      Busy( wl->wl_Locked, FALSE );

      /*
       * Free lock.
       */
      BGUI_FreePoolMem( wl );
   }
}

makeproto SAVEDS ASM STRPTR BGUI_GetLocaleStr(REG(a0) struct bguiLocale *bl, REG(d0) ULONG id)
{
   STRPTR str = NULL;
   
   struct bguiLocaleStr bls;
   
   if (bl)
   {
      if (bl->bl_LocaleStrHook)
      {
         bls.bls_ID = id;
         str = (STRPTR)BGUI_CallHookPkt(bl->bl_LocaleStrHook, (void *)bl, (void *)&bls);
      }
      else
      {
         if (LocaleBase) str = GetLocaleStr(bl->bl_Locale, id);
      };
   };
   return str;
}

makeproto SAVEDS ASM STRPTR BGUI_GetCatalogStr(REG(a0) struct bguiLocale *bl, REG(d0) ULONG id, REG(a1) STRPTR str)
{
   struct bguiCatalogStr bcs;

   if (bl)
   {
      if (bl->bl_CatalogStrHook)
      {
         bcs.bcs_ID = id;
         bcs.bcs_DefaultString = str;
         str = (STRPTR)BGUI_CallHookPkt(bl->bl_CatalogStrHook, (void *)bl, (void *)&bcs);
      }
      else
      {
         if (LocaleBase) str = GetCatalogStr(bl->bl_Catalog, id, str);
      };
   };
   return str;
}

struct CallHookData
{
   struct Hook *Hook;
   APTR Object;
   APTR Message;
};

static ULONG CallHookWithStack(struct CallHookData *call_hook_data)
{
   register APTR stack;
   register ULONG result;

   stack=EnsureStack();
   result=CallHookPkt(call_hook_data->Hook,call_hook_data->Object,call_hook_data->Message);
   RevertStack(stack);
   return(result);
}

makeproto SAVEDS ASM ULONG BGUI_CallHookPkt(REG(a0) struct Hook *hook,REG(a2) APTR object,REG(a1) APTR message)
{
   struct CallHookData call_hook_data;

   call_hook_data.Hook=hook;
   call_hook_data.Object=object;
   call_hook_data.Message=message;
   return(CallHookWithStack(&call_hook_data));
}
