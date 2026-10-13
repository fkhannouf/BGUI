// --

#ifndef INLINE4_TEST_LIBRARY_H
#define INLINE4_TEST_LIBRARY_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --

#define TESTLIB_FuncAdd(x,y)		ITest_Library->TESTLIB_FuncAdd(x,y)

#define BGUI_InfoText(rp,text,bounds,drawinfo)  ITest_Library->BGUI_InfoText(rp,text,bounds,drawinfo)                                                                   ?
#define BGUI_GetLocaleStr(bl,id)    ITest_Library->BGUI_GetLocaleStr(bl,id)                                                                                             ?
#define BGUI_GetCatalogStr(bl,id,def)   ITest_Library->BGUI_GetCatalogStr(bl,id,def)                                                                                    ?
#define BGUI_FillRectPattern(rport,bpat,x1,y1,x2,y2)    ITest_Library->BGUI_FillRectPattern(rport,bpat,x1,y1,x2,y2)                                                     ?
#define BGUI_PostRender(cl,obj,gpr) ITest_Library->BGUI_PostRender(cl,obj,gpr)                                                                                          ?
#define BGUI_MakeClassA(tags)       ITest_Library->BGUI_MakeClassA(tags)                                                                                                ?
#define BGUI_FreeClass(cl)      ITest_Library->BGUI_FreeClass(cl)                                                                                                       ?
#define BGUI_PackStructureTags(pack,tab,tags)   ITest_Library->BGUI_PackStructureTags(pack,tab,tags)                                                                    ?
#define BGUI_UnpackStructureTags(pack,tab,tags) ITest_Library->BGUI_UnpackStructureTags(pack,tab,tags)

#define BGUI_AllocPoolMem(size)     ITest_Library->BGUI_AllocPoolMem(size)                                                                                              ?
#define BGUI_FreePoolMem(mem)       ITest_Library->BGUI_FreePoolMem(mem)                                                                                                ?
#define BGUI_GetDefaultTags(id)     ITest_Library->BGUI_GetDefaultTags(id)                                                                                              ?
#define BGUI_DefaultPrefs()     ITest_Library->BGUI_DefaultPrefs()                                                                                                      ?
#define BGUI_LoadPrefs(name)        ITest_Library->BGUI_LoadPrefs(name)                                                                                                 ?
#define BGUI_AllocPoolMemDebug(size,file,line)  ITest_Library->BGUI_AllocPoolMemDebug(size,file,line)                                                                   ?
#define BGUI_FreePoolMemDebug(mem,file,line)    ITest_Library->BGUI_FreePoolMemDebug(mem,file,line)
// --

#endif
