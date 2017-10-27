#include "GameObject.h"

GameObject::GameObject()
{
	transform = new Transform();
	sprite = new Sprite();
}

GameObject::~GameObject()
{
	if (transform) { delete transform; }
	if (sprite) { delete sprite; }
}

void GameObject::Update()
{
}
