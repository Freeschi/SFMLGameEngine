// ====================================================================================================
// Lua: Class Wrapper
// ====================================================================================================
#ifndef H_LUA_CLASS_WRAPPERS
#define H_LUA_CLASS_WRAPPERS

namespace LuaClasses
{
	void RegisterClassWrappers();

	void RegisterBase();
	void RegisterGenericSF();
	void RegisterVector2();
	void RegisterSceneNode();
	void RegisterEntity();
	void RegisterEnums();
	void RegisterSceneBuilder();
	void RegisterHuman();
	void RegisterSpriteNode();

	void BuildScene();

	// ====================================================================================================
	// Base
	// ====================================================================================================	
	class base_class_wrapper
	{
	public:
		base_class_wrapper();
		//template <class T>
		void _base_init(std::string classname);

		void Invalidate();
		void CheckValid();
		ACCESSOR_FUNC_BOOL(Valid, m_bValid);
		
		virtual void OnInvalidated()  {};
		virtual luabind::object SetupLuaObject() { return luabind::object(); };
		
		void Push();
		luabind::object LuaBindObject() { return m_oLuaObject; }

	private:
		bool m_bValid;
		luabind::object m_oLuaObject;
		std::string m_sClassName;
	};

	// ====================================================================================================
	// SceneNode
	// ====================================================================================================
	class lua_scenenode_wrapper : public base_class_wrapper, public luabind::wrap_base
	{
	public:
		SceneNode* m_pSceneNode;
		lua_scenenode_wrapper(SceneNode* pSceneNode);
		virtual bool IsValid() { return m_pSceneNode != NULL; }

		void SetPosition(sf::Vector2f pos);
		sf::Vector2f GetPosition();

		void AttachChild(lua_scenenode_wrapper* pSceneNode);
		void DetachChild(lua_scenenode_wrapper* pSceneNode);
		luabind::object GetParent();
		void SetParent(lua_scenenode_wrapper* pSceneNode);
	};

	// ====================================================================================================
	// Entity
	// ====================================================================================================
	class lua_entity_wrapper : public lua_scenenode_wrapper, public luabind::wrap_base
	{
	public:
		Entity* m_pEntity;
		lua_entity_wrapper(Entity* pEntity);
		~lua_entity_wrapper();
		void OnInvalidated();

		luabind::object SetupLuaObject();
		
		void Activate(int iLayer);
		void Activate();
		int Index();
		std::string GetClassName();
	};

	// ====================================================================================================
	// SpriteNode
	// ====================================================================================================
	class lua_spritenode_wrapper : public lua_entity_wrapper, public luabind::wrap_base
	{
	public:
		SpriteNode* m_pSprite;
		lua_spritenode_wrapper(SpriteNode* pSprite);

		luabind::object SetupLuaObject();

		void SetTexture(std::string texture);
	};

	// ====================================================================================================
	// Human
	// ====================================================================================================
	class lua_human_wrapper : public lua_spritenode_wrapper, public luabind::wrap_base
	{
	public:
		BaseHuman* m_pHuman;
		lua_human_wrapper(BaseHuman* pHuman);

		luabind::object SetupLuaObject();
		luabind::object GetSprite();
	};

	// ====================================================================================================
	// Player
	// ====================================================================================================
	class lua_player_wrapper : public lua_human_wrapper, public luabind::wrap_base
	{
	public:
		PlayerEntity* m_pPlayer;
		lua_player_wrapper(PlayerEntity* pHuman);

		luabind::object SetupLuaObject();
	};
};

#endif