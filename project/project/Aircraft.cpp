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
Aircraft::Aircraft(Type type) : mType(type), Entity("base_aircraft")
{
	TextureHolder* th = g_pWorld->GetTextureHolder();
	mSprite.setTexture(th->Get(toTextureID(type)));

	printf("Aircraft::Aircraft\n");
}

// ====================================================================================================
// Aircraft::drawCurrent
// ====================================================================================================
void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	printf("Aircraft::Draw\n");
	target.draw(mSprite, states);
}