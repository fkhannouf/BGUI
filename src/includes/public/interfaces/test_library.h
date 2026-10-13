// --

#ifndef INTERFACES_TEST_LIBRARY_H
#define INTERFACES_TEST_LIBRARY_H

// --

#include <proto/exec.h>
#include <proto/intuition.h>

#include <stdint.h>

// --

struct Test_LibraryIFace
{
    struct InterfaceData Data;
    uint32_t                    APICALL (*Obtain)(struct Test_LibraryIFace *Self);
    uint32_t                    APICALL (*Release)(struct Test_LibraryIFace *Self);
    void                        APICALL (*Expunge)(struct Test_LibraryIFace *Self);
    struct Interface *          APICALL (*Clone)(struct Test_LibraryIFace *Self);
    uint32_t                    APICALL (*TESTLIB_FuncAdd)(struct Test_LibraryIFace *Self, uint32_t a, uint32_t b);

    /* Public functions */
    void *                      APICALL (*BGUI_GetClassPtr)(struct Test_LibraryIFace *Self, uint32_t num);
    void *                      APICALL (*BGUI_NewObjectA)(struct Test_LibraryIFace *Self, uint32_t num, void *tags);
    void *                      APICALL (*BGUI_RequestA)(struct Test_LibraryIFace *Self, void *win, void *estruct, void *args);
    uint32_t                    APICALL (*BGUI_Help)(struct Test_LibraryIFace *Self, void *win, void *name, void *node, uint32_t line);
    uint32_t                    APICALL (*BGUI_LockWindow)(struct Test_LibraryIFace *Self, void *win);
    uint32_t                    APICALL (*BGUI_UnlockWindow)(struct Test_LibraryIFace *Self, void *lock);
    uint32_t                    APICALL (*BGUI_DoGadgetMethodA)(struct Test_LibraryIFace *Self, void *object, void *win, void *req, void *msg);
    void *                      APICALL (*BGUI_AllocBitMap)(struct Test_LibraryIFace *Self, uint32_t width, uint32_t height, uint32_t depth, uint32_t flags, void *friend);
    void                        APICALL (*BGUI_FreeBitMap)(struct Test_LibraryIFace *Self, void *bitmap);
    void *                      APICALL (*BGUI_CreateRPortBitMap)(struct Test_LibraryIFace *Self, void *rport, uint32_t width, uint32_t height, uint32_t depth);
    void                        APICALL (*BGUI_FreeRPortBitMap)(struct Test_LibraryIFace *Self, void *rport);
    void                        APICALL (*BGUI_InfoTextSize)(struct Test_LibraryIFace *Self, void *rp, void *text, void *width, void *height);
    void                        APICALL (*BGUI_InfoText)(struct Test_LibraryIFace *Self, void *rp, void *text, void *bounds, void *drawinfo);
    uint32_t                    APICALL (*BGUI_GetLocaleStr)(struct Test_LibraryIFace *Self, void *bl, uint32_t id);
    void *                      APICALL (*BGUI_GetCatalogStr)(struct Test_LibraryIFace *Self, void *bl, uint32_t id, void *def);
    void                        APICALL (*BGUI_FillRectPattern)(struct Test_LibraryIFace *Self, void *rport, void *bpat, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void                        APICALL (*BGUI_PostRender)(struct Test_LibraryIFace *Self, void *cl, void *obj, void *gpr);
    void *                      APICALL (*BGUI_MakeClassA)(struct Test_LibraryIFace *Self, void *tags);
    void                        APICALL (*BGUI_FreeClass)(struct Test_LibraryIFace *Self, void *cl);
    void                        APICALL (*BGUI_PackStructureTags)(struct Test_LibraryIFace *Self, void *pack, void *tab, void *tags);
    void                        APICALL (*BGUI_UnpackStructureTags)(struct Test_LibraryIFace *Self, void *pack, void *tab, void *tags);

    /* Private functions */
    void *                      APICALL (*BGUI_AllocPoolMem)(struct Test_LibraryIFace *Self, uint32_t size);
    void                        APICALL (*BGUI_FreePoolMem)(struct Test_LibraryIFace *Self, void *mem);
    uint32_t                    APICALL (*BGUI_GetDefaultTags)(struct Test_LibraryIFace *Self, uint32_t id);
    uint32_t                    APICALL (*BGUI_DefaultPrefs)(struct Test_LibraryIFace *Self);
    void                        APICALL (*BGUI_LoadPrefs)(struct Test_LibraryIFace *Self, void *name);
    void *                      APICALL (*BGUI_AllocPoolMemDebug)(struct Test_LibraryIFace *Self, uint32_t size, void *file, uint32_t line);
    void                        APICALL (*BGUI_FreePoolMemDebug)(struct Test_LibraryIFace *Self, void *mem, void *file, uint32_t line);
};

// --

#endif
