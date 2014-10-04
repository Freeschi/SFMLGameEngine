// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// Center
// ====================================================================================================
namespace UTIL
{
	void CenterOrigin(sf::Sprite& sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void CenterOrigin(sf::Text& text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void ReplaceString(std::string& str, const std::string& from, const std::string& to)
	{
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
	void ParseFilePath(std::string& path)
	{
		ReplaceString(path, "\\", "/");
		ReplaceString(path, "/\\", "/");
		ReplaceString(path, "\\/", "/");
		ReplaceString(path, "//", "/");
	}
}