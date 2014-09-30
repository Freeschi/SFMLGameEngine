// ====================================================================================================
// Lua: Class Wrapper
// ====================================================================================================
#ifndef H_LUA_CLASS_WRAPPERS
#define H_LUA_CLASS_WRAPPERS

#pragma warning(disable: 4584)

namespace LuaClasses
{
	void RegisterClassWrappers();

	class lua_scenenode_wrapper : public SceneNode, public luabind::wrap_base
	{
	public:
		SceneNode* m_pSceneNode;
		lua_scenenode_wrapper(SceneNode* pSceneNode);

		void SetPosition(sf::Vector2f pos);
	};

	class lua_entity_wrapper : public Entity, public lua_scenenode_wrapper, public luabind::wrap_base
	{
	public:
		Entity* m_pEntity;
		lua_entity_wrapper(Entity* pEntity);
		~lua_entity_wrapper();

		void Invalidate();
		void Validate();
		void Activate();
		std::string GetClassName();
	};
};

#endif