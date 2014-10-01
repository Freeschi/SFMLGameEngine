#ifndef H_WORLD
#define H_WORLD

// ====================================================================================================
// Registered Entity Classes
// ====================================================================================================
class RegisteredEntityClass
{
private:
	std::string m_sClassName;

public:
	RegisteredEntityClass(std::string classname) { m_sClassName = classname; }
	std::string GetClassName() { return m_sClassName; }
	virtual Entity* Create() { return NULL; };
};
#define REGISTER_ENTITY_CLASS(name, createfunc) \
class RegisteredEntity_##name : public RegisteredEntityClass \
{ \
public: \
	RegisteredEntity_##name() : RegisteredEntityClass(#name) {}; \
	Entity* Create() { return new createfunc; } \
}; g_pWorld->RegisterEntityClass(new RegisteredEntity_##name());

// ====================================================================================================
// World
// ====================================================================================================
#define MAX_ENTITIES 128
class World : private sf::NonCopyable
{
public:
	enum Layer
	{
		LAYER_MAP,
		LAYER_GENERAL,
		LAYER_FOREGROUND,
		LAYER_HUD,
		LAYER_COUNT
	};

	// General
	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt, bool hasfocus);
	void Draw();
	void LoadTextures();
	void BuildScene();

	// Get-Functions
	CommandQueue* GetCommandQueue() { return mCommandQueue;  }
	SceneNode* GetSceneLayer(Layer layer) { if (layer >= LAYER_COUNT) return NULL; return mSceneLayers[layer]; }
	TextureHolder* GetTextureHolder() { return mTextures;  }
	FontHolder* GetFontHolder() { return mFonts; }
	sf::RenderWindow& GetWindow() { return mWindow; }
	sf::View* GetView() { return mWorldView; }

	// Accessor
	ACCESSOR_FUNC(Bounds, sf::FloatRect, mWorldBounds);

	// Registered Entity Classes
	std::vector<RegisteredEntityClass*> mRegisteredEntityClasses;
	void RegisterEntityClass(RegisteredEntityClass* ent);
	RegisteredEntityClass* GetEntityClassInfo(std::string classname);
	Entity* CreateEntityByClassName(std::string classname);

	// Entity List
	// This is used so Entities have their own Index
	int RegisterEntity(Entity* ent);
	void UnregisterEntity(Entity* ent);
	int GetEntityIndex(Entity* ent);
	Entity* GetEntityByIndex(int index);
	bool IsEntityRegistered(Entity* ent);
	bool IsEntityRegistered(int index);


private:
	sf::RenderWindow& mWindow;
	sf::View* mWorldView;
	TextureHolder* mTextures;
	FontHolder* mFonts;
	SceneNode mSceneGraph;
	Entity* mEntityList[MAX_ENTITIES];
	CommandQueue* mCommandQueue;
	std::array<SceneNode*, LAYER_COUNT> mSceneLayers;
	sf::FloatRect mWorldBounds;
};

extern World* g_pWorld;

#endif