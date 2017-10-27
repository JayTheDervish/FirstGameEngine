#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::Initialize(GameObject * parent)
{
	this->Transform = GetOwner()->has(Transform);
}

void Sprite::Update()
{
}
