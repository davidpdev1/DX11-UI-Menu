#include "stdafx.h"
#include "Container.h"


Container::Container(float x, float y, float sizeX, float sizeY) : MenuComponent(Vector2(x, y), Vector2(sizeX, sizeY))
{
}


Container::~Container()
{
}
