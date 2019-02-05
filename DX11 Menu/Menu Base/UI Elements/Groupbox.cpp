#include "stdafx.h"
#include "Groupbox.h"
bool Groupbox::m_bIsPartOfGroupbox = false;
Groupbox *Groupbox::m_pCurrentGroupbox = nullptr;


Groupbox::Groupbox(Window *parent, Vector2 pos, Vector2 size) : WindowComponent(parent, pos.x, pos.y, size.x, size.y)
{
	SetSize(Vector2(size.x, size.y));
}


Groupbox::~Groupbox()
{
}
