// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Loading Screen Data
// ====================================================================================================
namespace LuaClasses
{
	lua_loading_screen_data::~lua_loading_screen_data()
	{
		
	}

	void lua_loading_screen_data::AddTexture(std::string alias, std::string filename)
	{
		ResourceLoadInstruction* rhInstruction = new ResourceLoadInstruction();
		rhInstruction->m_eType = RESOURCE_TEXTURE;
		rhInstruction->m_sAlias = alias;
		rhInstruction->m_sFilename = filename;

		m_vResources.push_back(rhInstruction);
	}

	void lua_loading_screen_data::AddFont(std::string alias, std::string filename)
	{
		ResourceLoadInstruction* rhInstruction = new ResourceLoadInstruction();
		rhInstruction->m_eType = RESOURCE_FONT;
		rhInstruction->m_sAlias = alias;
		rhInstruction->m_sFilename = filename;

		m_vResources.push_back(rhInstruction);
	}

	/*
	 * Register
	 */
	void RegisterLoadingScreenData()
	{
		luabind::module(lua->State()) [
			luabind::class_<lua_loading_screen_data>("LoadingScreenData")
				.def("AddTexture", &lua_loading_screen_data::AddTexture)
				.def("AddFont", &lua_loading_screen_data::AddFont)
		];
	}
}