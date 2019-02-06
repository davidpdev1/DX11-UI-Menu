#include "stdafx.h"
#include "Groupbox.h"
bool Groupbox::m_bIsPartOfGroupbox = false;
Groupbox *Groupbox::m_pCurrentGroupbox = nullptr;


Groupbox::Groupbox(Window *parent, Vector2 pos, Vector2 size, std::string name) : WindowComponent(parent, pos.x, pos.y, size.x, size.y), m_title(name)
{
	SetSize(Vector2(size.x, size.y));
	m_pxTitleSize = GetBase()->GetTextFontSize(name, 1.0f);
	m_upLineBeginLeft = Vector2(pos.x - 1, pos.y - 1);
	m_titleBeginPos = Vector2(m_upLineBeginLeft.x + 25, round(m_upLineBeginLeft.y - (m_pxTitleSize.y / 2)));
	m_upLineBeginRight = Vector2(m_titleBeginPos.x + m_pxTitleSize.x + 5, m_upLineBeginLeft.y);
	m_upLineRightWidth = (size.x + 1) - (m_titleBeginPos.x + m_pxTitleSize.x);
}


Groupbox::~Groupbox()
{
}
