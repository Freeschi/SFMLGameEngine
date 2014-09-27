// ====================================================================================================
// World Class
// ====================================================================================================
#ifndef H_WORLD
#define H_WORLD

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt, bool hasfocus);
	void Draw();
	CommandQueue& GetCommandQueue();

private:
	void LoadTextures();
	void BuildScene();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;
	CommandQueue mCommandQueue;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};

#endif