#include "Sprite.h"
#include "Transform.h"

#ifndef GameObject_H
#define GameObject_H

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update();

	Transform *transform;
	Sprite *sprite;

private:


};

#endif // !GameObject_H


#pragma once
