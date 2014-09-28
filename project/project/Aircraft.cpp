// ====================================================================================================
// Includes
// ====================================================================================================
#include "Includes.h"

// ====================================================================================================
// ToTextureID
// ====================================================================================================
Textures::ID toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;
		break;
	case Aircraft::Raptor:
		return Textures::Raptor;
		break;
	}
}

// ====================================================================================================
// Aircraft
// ====================================================================================================
Aircraft::Aircraft(Type type) : mType(type)
{
	printf("%i\n", g_pWorld);
	Sleep(1000);

	TextureHolder* th = g_pWorld->GetTextureHolder();
	printf("th = %i\n", th);
	Sleep(1000);
	mSprite.setTexture(th->Get(toTextureID(type)));
}

// ====================================================================================================
// Aircraft::drawCurrent
// ====================================================================================================
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}