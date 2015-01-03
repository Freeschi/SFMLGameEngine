#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SDLGameobject.hpp"
#include "Loaderparams.hpp"

class Player : public SDLGameobject
{
public:
	
	Player(const Loaderparams* pParams);

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
};


#endif // PLAYER - Define