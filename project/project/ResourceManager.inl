// ====================================================================================================
// ResourceHolder::Load
// ====================================================================================================
template <typename Resource>
bool ResourceHolder<Resource>::Load(std::string alias, std::string filename)
{
	// Create and load resource
	RHResource* res = new RHResource();
	res->m_sAlias = alias;
	res->m_sFilename = filename;
	res->m_tResource = new Resource();

	if (!res->m_tResource->loadFromFile(filename))
	{
		printf("[ResourceManager] Failed to load file %s\n", filename.c_str());
		delete res;
		return false;
	}

	mResources.push_back(res);
	return true;
}

// ====================================================================================================
// ResourceHolder::Load<Parameter>
// ====================================================================================================
template <typename Resource>
template <typename Parameter>
void ResourceHolder<Resource>::Load(std::string alias, std::string filename, Parameter secondParam)
{
	// Create and load resource
	RHResource* res = new RHResource();
	res->m_sAlias = alias;
	res->m_sFilename = filename;
	res->m_tResource = new Resource();

	if (!res->m_tResource->loadFromFile(filename, secondParam))
	{
		printf("[ResourceManager] Failed to load file %s\n", filename.c_str());
		delete res;
		return false;
	}

	mResources.push_back(res);
	return true;
}

// ====================================================================================================
// ResourceHolder::Get
// ====================================================================================================
template <typename Resource>
Resource& ResourceHolder<Resource>::Get(std::string id)
{
	for (std::vector<RHResource*>::iterator it = mResources.begin(); it != mResources.end(); ++it)
	{
		RHResource* hResource = *it;
		if (hResource->m_sAlias == id || hResource->m_sFilename == id)
		{
			return *hResource->m_tResource;
		}
	}

	throw std::string("ResourceHolder::Get failed! Unknown resource!");
}

// ====================================================================================================
// ResourceHolder::Get (const)
// ====================================================================================================
template <typename Resource>
const Resource& ResourceHolder<Resource>::Get(std::string id) const
{
	for (std::vector<RHResource*>::iterator it = mResources.begin(); it != mResources.end(); ++it)
	{
		RHResource* hResource = *it;
		if (hResource->m_sAlias == id || hResource->m_sFilename == id)
		{
			return *hResource->m_tResource;
		}
	}

	throw std::string("ResourceHolder::Get failed! Unknown resource!");
}