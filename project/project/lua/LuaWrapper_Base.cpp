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
	// Base Class Wrapper
	base_class_wrapper::base_class_wrapper() {
		m_bValid = true;
		m_sClassName = "";
	};

	// Internal Init
	void base_class_wrapper::_base_init(std::string classname)
	{
		m_sClassName = classname;
		m_oLuaObject = SetupLuaObject();
	}

	// Push
	void base_class_wrapper::Push()
	{
		m_oLuaObject.push(lua->State());
	}

	// Invalidate
	void base_class_wrapper::Invalidate()
	{
		OnInvalidated();
		SetValid(false);
	}

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
		// class wrapper
		luabind::module(lua->State()) [
			luabind::class_<LuaClasses::base_class_wrapper>("base_class_wrapper")
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
		RegisterEnums();
		RegisterSceneBuilder();
		RegisterSpriteNode();
		RegisterHuman();
	}
};