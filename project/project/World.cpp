// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Definitions
// ====================================================================================================
World* g_pWorld = NULL;

// ====================================================================================================
// World
// ====================================================================================================
World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(window.getDefaultView()), 
										mTextures(new TextureHolder()), mSceneGraph(), mSceneLayers(), 
										mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f), 
										mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f), 
										mScrollSpeed(-50.f), mPlayerAircraft(nullptr),
										mCommandQueue(new CommandQueue())
{
	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

// ====================================================================================================
// Load Textures
// ====================================================================================================
void World::LoadTextures()
{
	mTextures->Load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures->Load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures->Load(Textures::Desert, "Media/Textures/Desert.png");

	printf("World::LoadTextures done\n");
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
	
	sf::Texture& texture = mTextures->Get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->AttachChild(std::move(backgroundSprite));
	
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mSceneLayers[Air]->AttachChild(std::move(leader));

	printf("World::BuildScene\n");
	g_pGame->OnFullyInitialized();
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

	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->SetVelocity(0.f, 0.f);
	sf::Vector2f velocity = mPlayerAircraft->GetVelocity();
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->SetVelocity(velocity / std::sqrt(2.f));
	mPlayerAircraft->Accelerate(0.f, mScrollSpeed);

	while (!mCommandQueue->isEmpty())
		mSceneGraph.onCommand(mCommandQueue->pop(), dt);

	mSceneGraph.Update(dt);

	sf::FloatRect viewBounds(
		mWorldView.getCenter() - mWorldView.getSize() / 2.f,
		mWorldView.getSize());
	const float borderDistance = 40.f;
	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x,
		viewBounds.left + borderDistance);
	position.x = std::min(position.x,
		viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y,
		viewBounds.top + borderDistance);
	position.y = std::min(position.y,
		viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}