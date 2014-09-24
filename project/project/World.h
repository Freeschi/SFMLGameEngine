// ====================================================================================================
// World Class
// ====================================================================================================
#ifndef H_WORLD
#define H_WORLD

class World : private sf::NonCopyable
{
public:
	explicit World(sf::RenderWindow& window);
	void Update(sf::Time dt);
	void Draw();
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
private:
	sf::RenderWindow& mWindow;
	sf::View mWorldView;
	TextureHolder mTextures;
	SceneNode mSceneGraph;
	std::array<SceneNode*, LayerCount> mSceneLayers;

	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosition;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;
};

#endif