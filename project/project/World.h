// ====================================================================================================
// World Class
// ====================================================================================================
#ifndef H_WORLD
#define H_WORLD

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