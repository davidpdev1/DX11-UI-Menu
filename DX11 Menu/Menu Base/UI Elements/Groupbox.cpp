#include "stdafx.h"
#include "Groupbox.h"
bool Groupbox::m_bIsPartOfGroupbox = false;
Groupbox *Groupbox::m_pCurrentGroupbox = nullptr;


void Groupbox::OnRender() {
	Vector2 position = GetPosition();
	Vector2 size = GetSize();

	// Up left 20px long line
	DrawRect(m_upLineBeginLeft.x, m_upLineBeginLeft.y, 20, m_thickness, m_borderColor);
	// Groupbox name
	DrawText(m_titleBeginPos.x, m_titleBeginPos.y, m_title, WHITE);
	// Right line(after name)
	DrawRect(m_upLineBeginRight.x, m_upLineBeginRight.y, m_upLineRightWidth, m_thickness, m_borderColor);
	// Rest of the full lines
	DrawRectOutline(position.x, position.y, size.x, size.y, m_thickness, m_borderColor, BORDERIGNORE_TOP);
}

Groupbox::Groupbox(Window *parent, Vector2 pos, Vector2 size, const std::string& name) : WindowComponent(parent, pos.x, pos.y, size.x, size.y), m_title(name)
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
