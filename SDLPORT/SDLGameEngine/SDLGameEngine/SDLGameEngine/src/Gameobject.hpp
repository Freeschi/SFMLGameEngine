#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <iostream>
#include "Loaderparams.hpp"
#include "SDL.h"

class Gameobject
{
public:

	virtual void Draw() = NULL;
	virtual void Update() = NULL;
	virtual void Clean() = NULL;

protected:

	Gameobject(const Loaderparams* pParams) {}
	virtual ~Gameobject() {  };
};

#endif //Gameobject - Define