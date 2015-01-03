#ifndef LOADERPARAMS_HPP
#define LOADERPARAMS_HPP

#include <string>

class Loaderparams
{
public:

	Loaderparams(int x, int y, int width, int height, std::string   textureID) : m_x(x), m_y(y), m_width(width), m_height(height), m_TextureID(textureID)  {}

	int GetX() const { return m_x; }
	int GetY() const { return m_y; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }
	std::string GetTextureID() const { return m_TextureID; }

private:

	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_TextureID;
};

#endif //LOADERPARAMS - Define