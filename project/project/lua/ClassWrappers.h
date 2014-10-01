// ====================================================================================================
// Lua: Class Wrapper
// ====================================================================================================
#ifndef H_LUA_CLASS_WRAPPERS
#define H_LUA_CLASS_WRAPPERS

#pragma warning(disable: 4584)

namespace LuaClasses
{
	void RegisterClassWrappers();

	class base_store_info
	{
	public:
		base_store_info() : mDataTable(luabind::newtable(lua->State())) {};
		luabind::object GetTable() {
			return mDataTable;
		};

	private:
		luabind::object mDataTable;
	};
	
	class base_class_wrapper : public base_store_info
	{
	public:
		base_class_wrapper() {
			m_bValid = true;
			m_sClassName = "";
		};

		void _base_class_wrapper_name(std::string classname) { m_sClassName = classname; };

		void Invalidate() {
			OnInvalidated();

			SetValid(false);
		}
		void CheckValid();
		ACCESSOR_FUNC_BOOL(Valid, m_bValid);
		virtual void OnInvalidated() {};

	private:
		bool m_bValid;
		std::string m_sClassName;
	};

	class lua_scenenode_wrapper : public base_class_wrapper, public luabind::wrap_base
	{
	public:
		SceneNode* m_pSceneNode;
		lua_scenenode_wrapper(SceneNode* pSceneNode);
		virtual bool IsValid() { return m_pSceneNode != NULL; }

		void SetPosition(sf::Vector2f pos);
		sf::Vector2f GetPosition();

		void lua_AttachChild(lua_scenenode_wrapper* pSceneNode);
		void lua_DetachChild(lua_scenenode_wrapper* pSceneNode);
		lua_scenenode_wrapper* lua_GetParent();
	};

	class lua_entity_wrapper : public lua_scenenode_wrapper, public luabind::wrap_base
	{
	public:
		Entity* m_pEntity;
		lua_entity_wrapper(Entity* pEntity);
		~lua_entity_wrapper();
		void OnInvalidated();
		
		void Activate();
		int Index();
		std::string GetClassName();
	};
};

#endif