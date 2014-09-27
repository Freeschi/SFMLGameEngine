// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// World
// ====================================================================================================
World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(window.getDefaultView()), mTextures(), mSceneGraph(), mSceneLayers(), mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f), mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), mScrollSpeed(-50.f), mPlayerAircraft(nullptr)
{
	LoadTextures();
	BuildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

// ====================================================================================================
// Load Textures
// ====================================================================================================
void World::LoadTextures()
{
	mTextures.Load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.Load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.Load(Textures::Desert, "Media/Textures/Desert.png");
}

// ====================================================================================================
// Build Scene
// ====================================================================================================
void World::BuildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.AttachChild(std::move(layer));
	}
	
	sf::Texture& texture = mTextures.Get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->AttachChild(std::move(backgroundSprite));
	
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	//printf("mPlayerAircraft::GetCategory = %i\n", mPlayerAircraft->GetCategory());
	//mPlayerAircraft->SetVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->AttachChild(std::move(leader));

	/*
	typedef std::unique_ptr<SceneNode> t;
	for (t& child : mSceneLayers[Air]->mChildren)
	{
		printf("mSceneLayers[Air] has a child\n");
	}*/
}

// ====================================================================================================
// Draw
// ====================================================================================================
void World::Draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

// ====================================================================================================
// Update
// ====================================================================================================
void World::Update(sf::Time dt, bool focused)
{
	sf::Vector2i windowCenter(mWindow.getSize() / 2u);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	//if (focused) sf::Mouse::setPosition(windowCenter, mWindow);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	mSceneGraph.Update(dt);
}

// ====================================================================================================
// getCommandQueue
// ====================================================================================================
CommandQueue& World::GetCommandQueue()
{
	return mCommandQueue;
}
