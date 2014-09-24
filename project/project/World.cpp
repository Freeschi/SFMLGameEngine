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
	//mPlayerAircraft->SetVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->AttachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->AttachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->AttachChild(std::move(rightEscort));
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
	/*mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->GetVelocity();
	if (position.x <= mWorldBounds.left + 150
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->SetVelocity(velocity);
	}*/

	sf::Vector2i windowCenter(mWindow.getSize() / 2u);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);
	//sf::Vector2i delta = windowCenter – mousePosition;
	if (focused) sf::Mouse::setPosition(windowCenter, mWindow);

	sf::Vector2f movement(0.f, 0.f);
	float playerspeed = 100.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= playerspeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += playerspeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= playerspeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += playerspeed;
	mPlayerAircraft->move(movement * dt.asSeconds());
	mSceneGraph.Update(dt);

	//mWorldView.setCenter(mWorldBounds.left, mWorldBounds.top);
}