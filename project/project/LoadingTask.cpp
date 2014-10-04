// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"
#include "Lua.h"
#include "lua/ClassWrappers.h"

// ====================================================================================================
// LoadingTask
// ====================================================================================================
LoadingTask::LoadingTask() : mThread(&LoadingTask::RunTask, this)
{
	m_bFinished = false;
	m_flProgress = 0.0f;
}

// ====================================================================================================
// Execute
// ====================================================================================================
void LoadingTask::Execute(LoadingState* pLoadingState)
{
	m_pLoadingState = pLoadingState;
	m_bFinished = false;
	m_cElapsedTime.restart();

	mThread.launch();
}

// ====================================================================================================
// Progress
// ====================================================================================================
bool LoadingTask::IsFinished()
{
	sf::Lock lock(m_mMutex);
	return m_bFinished;
}
float LoadingTask::GetPercentage()
{
	sf::Lock lock(m_mMutex);
	return m_flProgress;
}

// ====================================================================================================
// RunTask
// ====================================================================================================
void LoadingTask::RunTask()
{
	// Call Event
	lua->GetEvent("LoadingScreenResources");
	LuaClasses::lua_loading_screen_data* lsdata = new LuaClasses::lua_loading_screen_data();
	luabind::object lua_lsdata(lua->State(), lsdata);
	lua_lsdata.push(lua->State());
	lua->ProtectedCall(2);

	// Each resource = flResourceStep %
	float flResourceStep = 100.0f / (float)lsdata->m_vResources.size();

	// Loop resources that were requested from Lua
	for (std::vector<LuaClasses::lua_loading_screen_data::ResourceLoadInstruction*>::iterator it = lsdata->m_vResources.begin(); it != lsdata->m_vResources.end(); ++it)
	{
		LuaClasses::lua_loading_screen_data::ResourceLoadInstruction* instruction = *it;
		
		char buf[312];
		sprintf(buf, "Loading %s (%i %%)", instruction->m_sFilename.c_str(), (int) m_flProgress);
		m_pLoadingState->SetStatusText(std::string(buf));

		if (instruction->m_eType == LuaClasses::lua_loading_screen_data::RESOURCE_TEXTURE)
		{
			// Load Texture
			g_pWorld->GetTextureHolder()->Load(instruction->m_sAlias, instruction->m_sFilename);
		} else if (instruction->m_eType == LuaClasses::lua_loading_screen_data::RESOURCE_FONT)
		{
			// Load Font
			g_pWorld->GetFontHolder()->Load(instruction->m_sAlias, instruction->m_sFilename);
		}

		sf::Lock lock(m_mMutex);
		m_flProgress += flResourceStep;
		//Sleep(175);
	}

	sf::Lock lock(m_mMutex);
	m_bFinished = true;
}