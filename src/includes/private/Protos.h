#pragma once

// Manager Interface
uint32 _manager_Obtain( struct LibraryManagerInterface *Self );
uint32 _manager_Release( struct LibraryManagerInterface *Self );
APTR _manager_Open( struct LibraryManagerInterface *Self, uint32 version );
APTR _manager_Close( struct LibraryManagerInterface *Self );
APTR _manager_Expunge( struct LibraryManagerInterface *Self );
APTR _manager_Init( struct LibBase *libBase, APTR SegList, struct ExecIFace *myIExec );

// --
// Main Interface
uint32 _main_Obtain( struct Test_LibraryIFace *Self );
uint32 _main_Release( struct Test_LibraryIFace *Self );
APTR _main_Clone( struct Test_LibraryIFace *Self );
uint32 _main_Expunge( struct Test_LibraryIFace *Self );
uint32 _main_FuncAdd( struct Test_LibraryIFace *Self, uint32 a, uint32 b );

// --
// Library Resources Functions
int32 Resources_Init( struct LibBase *devBase );
void Resources_Free( struct LibBase *devBase );
int32 myOpenResources( int max_libs );
void myCloseResources( void );
