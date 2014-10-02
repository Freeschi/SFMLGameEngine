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
World::World(sf::RenderWindow& window) : mWindow(window), mWorldView(new sf::View(window.getDefaultView()))
{
	mEntityList = (Entity**) malloc(4 * g_pConfig->EntityLimit());
	for (int i = 0; i < g_pConfig->EntityLimit(); i++)
	{
		mEntityList[i] = NULL;
	}

	mCommandQueue = new CommandQueue();
	mFonts = new FontHolder();
	mTextures = new TextureHolder();
	mWorldBounds = sf::FloatRect(0.f, 0.f, mWorldView->getSize().x, 2000.f);
	m_pPhysics = new Physics();
}

// ====================================================================================================
// Load Textures
// ====================================================================================================
void World::LoadTextures()
{
	mTextures->Load("TitleScreen", "Media/Textures/TitleScreen.png");
	mFonts->Load("Main", "Media/Sansation.ttf");
}

// ====================================================================================================
// Build Scene
// ====================================================================================================
void World::BuildScene()
{
	for (std::size_t i = 0; i < g_pWorld->LAYER_COUNT; ++i)
	{
		SceneNode* layer = new SceneNode();
		mSceneLayers[i] = layer;
		mSceneGraph.AttachChild(layer);
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

// ====================================================================================================
// Register / Unregister Entity
// ====================================================================================================
int World::RegisterEntity(Entity* ent)
{
	if (IsEntityRegistered(ent)) return -1;

	// Search free slot
	for (int index = 0; index < g_pConfig->EntityLimit(); index++)
	{
		if (!IsEntityRegistered(index))
		{
			mEntityList[index] = ent;
			return index;
		}
	}

	// oh crap
	// entity list full
	printf("[World] Warning! Entity List is full!\n");
	return -1;
}
void World::UnregisterEntity(Entity* ent)
{
	int iEntityIndex = GetEntityIndex(ent);
	if (iEntityIndex == -1)
	{
		printf("[World] Warning! UnregisterElement called with unregistered entity!\n");
		return;
	}

	ent->RemoveNextUpdate();
	mEntityList[iEntityIndex] = NULL;
}

// ====================================================================================================
// GetEntity
// ====================================================================================================
int World::GetEntityIndex(Entity* ent)
{
	for (int index = 0; index < g_pConfig->EntityLimit(); index++)
	{
		Entity* pRegisteredEntity = mEntityList[index];
		if (pRegisteredEntity != NULL && ent == pRegisteredEntity)
		{
			return index;
		}
	}

	return -1;
}
Entity* World::GetEntityByIndex(int iEntityIndex)
{
	if (iEntityIndex < 0 || iEntityIndex >= g_pConfig->EntityLimit()) {
		throw std::string("Invalid call to World::GetEntityByIndex! iEntityIndex out of bounds!");
		return NULL;
	}

	return mEntityList[iEntityIndex];
}

// ====================================================================================================
// IsEntity
// ====================================================================================================
bool World::IsEntityRegistered(int iEntityIndex)
{
	return GetEntityByIndex(iEntityIndex) != NULL;
}
bool World::IsEntityRegistered(Entity* ent)
{
	return GetEntityIndex(ent) > 0;
}