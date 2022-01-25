/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2021/02
Update: 2021/02
----------------------------------------------*/
#ifndef __BTXFRAMEWORK_H_
#define __BTXFRAMEWORK_H_

#pragma warning( disable : 4251 )

#include "BTX\Physics\EntityManager.h"

namespace BTX
{
	/*
	USAGE: Releases all BTX Singletons
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseAllSingletons(void)
	{
		EntityManager::ReleaseInstance();
		ModelManager::ReleaseInstance();
		CameraManager::ReleaseInstance();
		MaterialManager::ReleaseInstance();
		TextureManager::ReleaseInstance();
		FolderSingleton::ReleaseInstance();
		ShaderManager::ReleaseInstance();
		SystemSingleton::ReleaseInstance();
		//GLSystem::ReleaseInstance();
		//LightManager::ReleaseInstance();
		//Text::ReleaseInstance();
	};

} //namespace BTX

#endif //__BTXSFRAMEWORK_H_