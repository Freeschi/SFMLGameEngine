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
class World : private sf::NonCopyable
{
public:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt, bool hasfocus);
	void Draw();

	CommandQueue* GetCommandQueue() { return mCommandQueue;  }
	SceneNode* GetSceneLayer(Layer layer) { if (layer >= LayerCount) return NULL; return mSceneLayers[layer]; }
	TextureHolder* GetTextureHolder() { return mTextures;  }

	void LoadTextures();
	void BuildScene();

	std::vector<RegisteredEntityClass*> mRegisteredEntityClasses;
	void RegisterEntityClass(RegisteredEntityClass* ent);
	RegisteredEntityClass* GetEntityClassInfo(std::string classname);
	Entity* CreateEntityByClassName(std::string classname);

private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder* mTextures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	CommandQueue* mCommandQueue;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};

extern World* g_pWorld;

#endif