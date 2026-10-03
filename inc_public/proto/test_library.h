
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef PROTO_TEST_LIBRARY_H
#define PROTO_TEST_LIBRARY_H

// --

#include <proto/exec.h>

#include <stdint.h>

// --
// AmigaOS4

#ifdef __amigaos4__

 #include <libraries/test_library.h>
 #include <interfaces/test_library.h>

 #ifdef __USE_INLINE__
 #include <inline4/test_library.h>
 #endif

 #ifndef __NOLIBBASE__
 extern struct Library *Test_LibraryBase;
 #endif

 #ifndef __NOGLOBALIFACE__
 extern struct Test_LibraryIFace *ITest_Library;
 #endif

#else // Other platforms

  #error Only support for AmigaOS4 .. at the moment

#endif

// --

#endif
