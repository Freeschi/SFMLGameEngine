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
World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(new sf::View(window.getDefaultView())), 
										mTextures(new TextureHolder()), mSceneGraph(), mSceneLayers(), 
										mWorldBounds(0.f, 0.f, mWorldView->getSize().x, 2000.f), 
										mSpawnPosition(mWorldView->getSize().x / 2.f, mWorldBounds.height - mWorldView->getSize().y / 2.f), 
										mScrollSpeed(-50.f), mPlayerAircraft(nullptr),
										mCommandQueue(new CommandQueue()), mRegisteredEntityClasses(), mFonts(new FontHolder())
{
	// Prepare the view
	mWorldView->setCenter(mSpawnPosition);
}

// ====================================================================================================
// Load Textures
// ====================================================================================================
void World::LoadTextures()
{
	mTextures->Load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures->Load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures->Load(Textures::Desert, "Media/Textures/Desert.png");
	mFonts->Load(Fonts::Main, "Media/Sansation.ttf");
	mTextures->Load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
}

// ====================================================================================================
// Build Scene
// ====================================================================================================
void World::BuildScene()
{
	for (std::size_t i = 0; i < g_pWorld->LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.AttachChild(std::move(layer));
	}
}

// ====================================================================================================
// Draw
// ====================================================================================================
void World::Draw()
{
	mWindow.setView(*mWorldView);
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

	while (!mCommandQueue->isEmpty())
		mSceneGraph.onCommand(mCommandQueue->pop(), dt);

	mSceneGraph.Update(dt);
}

// ====================================================================================================
// RegisterEntityClass
// ====================================================================================================
void World::RegisterEntityClass(RegisteredEntityClass* ent)
{
	printf("[Game] Registered entity class %s (Index %i)\n", ent->GetClassName().c_str(), mRegisteredEntityClasses.size());
	mRegisteredEntityClasses.push_back(ent);
}
RegisteredEntityClass* World::GetEntityClassInfo(std::string classname)
{
	for(std::vector<RegisteredEntityClass*>::iterator it = mRegisteredEntityClasses.begin(); it != mRegisteredEntityClasses.end(); ++it)
	{
		RegisteredEntityClass* pInfo = *it;
		if (pInfo->GetClassName() == classname)
			return pInfo;
	}

	return NULL;
}
Entity* World::CreateEntityByClassName(std::string classname)
{
	RegisteredEntityClass* pInfo = GetEntityClassInfo(classname);
	if (pInfo == NULL)
	{
		printf("[World] Attempted to create entity with unknown classname (%s)\n", classname.c_str());
		return NULL;
	}

	return pInfo->Create();
}