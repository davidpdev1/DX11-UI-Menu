#include "stdafx.h"
#include "Checkbox.h"
float Checkbox::m_boxSize = 16;
float Checkbox::m_checkedBoxSize = 12;

void Checkbox::OnRender() {
	Vector2 pos = GetPosition();
	DrawRect(pos.x, pos.y, m_boxSize, m_boxSize, m_boxColor);
	DrawRectOutline(pos.x, pos.y, m_boxSize, m_boxSize, 2, currentBorderColor);
	if (*m_pbSelected) {
		float offsetToCenter = (m_boxSize - m_checkedBoxSize) / 2.f;
		DrawRect(pos.x + offsetToCenter, pos.y + offsetToCenter, m_checkedBoxSize, m_checkedBoxSize, m_selectedColor);
	}
	DrawText(pos.x + m_boxSize + m_labelPadding, pos.y, m_text, WHITE, m_textScale);
}

void Checkbox::OnMouseEnter() {
	currentBorderColor = m_mouseOverBorderColor;
}

void Checkbox::OnMouseLeave() {
	currentBorderColor = m_borderColor;
}

void Checkbox::OnMouseClick() {
	if (IsMouseOver())
		*m_pbSelected = !*m_pbSelected;
}

Checkbox::Checkbox(Window * parent, Vector2 position, std::string text, bool * bSelected) 
	: WindowComponent(parent, position.x, position.y, 0, 0), m_text(text), m_pbSelected(bSelected) {
	float width = GetBase()->GetTextFontSize(text, m_textScale).x;
	SetSize(Vector2(m_boxSize + width, m_boxSize));
}
