// ====================================================================================================
// Includes
// ====================================================================================================
#include "../../Includes.h"
#include "GeneralFunctions.h"
#include "ClassWrappers.h"

// ====================================================================================================
// Base
// ====================================================================================================
namespace LuaClasses
{
	// Valid-Check
	void base_class_wrapper::CheckValid()
	{
		if (!IsValid())
		{
			char buf[350];
			sprintf(buf, "Attempted to use NULL %s!", m_sClassName.c_str());
			lua->PushString(buf);
			throw luabind::error(lua->State());
		}
	}

	/*
	 * Register
	 */
	void RegisterBase()
	{
		// store info
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::base_store_info>("base_store_info")
				.def("GetTable", &LuaClasses::base_store_info::GetTable)
		];

		// class wrapper
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::base_class_wrapper, LuaClasses::base_store_info>("base_class_wrapper")
				.def("IsValid", &LuaClasses::base_class_wrapper::IsValid)
		];
	}

	// ====================================================================================================
	// Register Class Wrappers
	// ====================================================================================================
	void LuaClasses::RegisterClassWrappers()
	{
		RegisterBase();
		RegisterGenericSF();
		RegisterVector2();
		RegisterSceneNode();
		RegisterEntity();
	}
};