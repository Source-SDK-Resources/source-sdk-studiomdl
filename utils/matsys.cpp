//===== Copyright � 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//===========================================================================//

#ifdef _WIN32
#include <windows.h>
#endif
#include "materialsystem/imaterialsystem.h"
#include "materialsystem/materialsystem_config.h"
#include <cmdlib.h>
#include "tier0/dbg.h"
#include "filesystem.h"
#include "cmdlib.h"
#include "tier2/tier2.h"

extern void MdlError( char const *pMsg, ... );

CreateInterfaceFn g_MatSysFactory = NULL;
CreateInterfaceFn g_ShaderAPIFactory = NULL;

static void LoadMaterialSystem( void )
{
	if( g_pMaterialSystem )
		return;
	
	const char *pDllName = "materialsystem" DLL_EXT_STRING;
	CSysModule *materialSystemDLLHInst;
	materialSystemDLLHInst = g_pFullFileSystem->LoadModule( pDllName );
	if( !materialSystemDLLHInst )
	{
		MdlError( "Can't load MaterialSystem" DLL_EXT_STRING "\n" );
	}

	g_MatSysFactory = Sys_GetFactory( materialSystemDLLHInst );
	if ( g_MatSysFactory )
	{
		g_pMaterialSystem = (IMaterialSystem *)g_MatSysFactory( MATERIAL_SYSTEM_INTERFACE_VERSION, NULL );
		if ( !g_pMaterialSystem )
		{
			MdlError( "Could not get the material system interface from materialsystem" DLL_EXT_STRING );
		}
	}
	else
	{
		MdlError( "Could not find factory interface in library MaterialSystem" DLL_EXT_STRING );
	}

	if (!( g_ShaderAPIFactory = g_pMaterialSystem->Init( "shaderapiempty" DLL_EXT_STRING, 0, CmdLib_GetFileSystemFactory() )) )
	{
		MdlError( "Could not start the empty shader (shaderapiempty" DLL_EXT_STRING ")!" );
	}
}

void InitMaterialSystem( const char *materialBaseDirPath )
{
	LoadMaterialSystem();
	MaterialSystem_Config_t config;
	g_pMaterialSystem->OverrideConfig( config, false );
}
