#ifndef H_UTILITY
#define H_UTILITY

namespace UTIL
{
	void CenterOrigin(sf::Sprite& sprite);
	void CenterOrigin(sf::Text& text);

	void ReplaceString(std::string& str, const std::string& from, const std::string& to);
	void ParseFilePath(std::string& path); // replaces \/ /\ // \\ so they can be compared to other paths
};

#endif