// ====================================================================================================
// Resource Holder
// ====================================================================================================
#ifndef H_RESOURCE_HOLDER
#define H_RESOURCE_HOLDER

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	bool Load(Identifier id, const std::string& filename);
	template <typename Parameter> void Load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& Get(Identifier id);
	const Resource& Get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

// ====================================================================================================
// Textures
// ====================================================================================================
namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert
	};
}

//template class ResourceHolder<sf::Texture, Textures::ID>;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#include "ResourceManager.inl"

#endif