// ====================================================================================================
// Resource Holder
// ====================================================================================================
#ifndef H_RESOURCE_HOLDER
#define H_RESOURCE_HOLDER

template <typename Resource>
class ResourceHolder
{
public:
	struct RHResource
	{
		std::string m_sAlias;
		std::string m_sFilename;
		Resource* m_tResource;
	};

	bool Load(std::string alias, std::string filename);
	template <typename Parameter> void Load(std::string alias, const std::string filename, Parameter secondParam);

	Resource& Get(std::string id);
	const Resource& Get(std::string id) const;

private:
	std::vector<RHResource*> mResources;
};


typedef ResourceHolder<sf::Texture> TextureHolder;
typedef ResourceHolder<sf::Font> FontHolder;

#include "ResourceManager.inl"

#endif