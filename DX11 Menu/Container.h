#pragma once
#include "stdafx.h"
class Container : public MenuComponent
{
	std::vector<std::unique_ptr<WindowComponent>> m_windowComponents;


public:
	Container(float x, float y, float sizeX, float sizeY);
	~Container();
};

