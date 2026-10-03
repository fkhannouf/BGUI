
/*
** SPDX-License-Identifier: Unlicense
** Written 2025 by Rene W. Olsen
** Target OS: AmigaOS4
*/

// --

#ifndef INC_PRIVATE_ALL_H
#error Include "inc_private/All.h" first
#endif

#ifndef INC_PRIVATE_PROTOS_H
#define INC_PRIVATE_PROTOS_H

// --
// Manager Interface
U32 _manager_Obtain( struct LibraryManagerInterface *Self );
U32 _manager_Release( struct LibraryManagerInterface *Self );
PTR _manager_Open( struct LibraryManagerInterface *Self, U32 version );
PTR _manager_Close( struct LibraryManagerInterface *Self );
PTR _manager_Expunge( struct LibraryManagerInterface *Self );
PTR _manager_Init( struct LibBase *libBase, PTR SegList, struct ExecIFace *myIExec );

// --
// Main Interface
U32 _main_Obtain( struct Test_LibraryIFace *Self );
U32 _main_Release( struct Test_LibraryIFace *Self );
PTR _main_Clone( struct Test_LibraryIFace *Self );
U32 _main_Expunge( struct Test_LibraryIFace *Self );
U32 _main_FuncAdd( struct Test_LibraryIFace *Self, U32 a, U32 b );

// --
// Library Resources Functions
S32 Resources_Init( struct LibBase *devBase );
void Resources_Free( struct LibBase *devBase );
S32 myOpenResources( int max_libs );
void myCloseResources( void );

#endif
