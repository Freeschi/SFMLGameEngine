// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// ResourceHolder::Load
// ====================================================================================================
template <typename Resource, typename Identifier>
bool ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		printf("[ResourceManager] Failed to load file %s\n", filename.c_str());
		return false;
	}

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	return inserted.second != NULL;
}

// ====================================================================================================
// ResourceHolder::Load<Parameter>
// ====================================================================================================
template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::Load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
	{
		printf("[ResourceManager] Failed to load file %s\n", filename.c_str());
		return false;
	}

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

// ====================================================================================================
// ResourceHolder::Get
// ====================================================================================================
template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id)
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

// ====================================================================================================
// ResourceHolder::Get (const)
// ====================================================================================================
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::Get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}