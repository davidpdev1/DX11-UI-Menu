#pragma once
#include "stdafx.h"

class Checkbox : public WindowComponent {
	// x == y expected for box size.
	static float m_boxSize;  // 16
	static float m_checkedBoxSize; // 12   check .cpp to edit

	const float m_labelPadding = 4; // # of pixels inbetween the box and the text

	DXColor m_boxColor = D3DCOLOR_RGBA(50, 54, 57, 255);
	
	DXColor m_borderColor = D3DCOLOR_RGBA(90, 94, 97, 255);
	DXColor m_mouseOverBorderColor = D3DCOLOR_RGBA(180, 184, 187, 255);
	DXColor m_selectedColor = D3DCOLOR_RGBA(230, 234, 237, 255);;

	DXColor currentBorderColor = m_borderColor;
	DXColor currentBoxBackground = m_boxColor;
	
	bool *m_pbSelected;
	std::string m_text;
	float m_textScale = 1.0f;

	void OnRender() override {
		Vector2 pos = GetPosition();
		DrawRect(pos.x, pos.y, m_boxSize, m_boxSize, m_boxColor);
		DrawRectOutline(pos.x, pos.y, m_boxSize, m_boxSize, 2, currentBorderColor);
		if (*m_pbSelected) {
			float offsetToCenter = (m_boxSize - m_checkedBoxSize) / 2.f;
			DrawRect(pos.x + offsetToCenter, pos.y + offsetToCenter, m_checkedBoxSize, m_checkedBoxSize, m_selectedColor);
		}
		DrawText(pos.x+m_boxSize + m_labelPadding, pos.y, m_text, WHITE, m_textScale);
	}

	void OnMouseEnter() override {
		currentBorderColor = m_mouseOverBorderColor;
	}

	void OnMouseLeave() override {
		currentBorderColor = m_borderColor;
	}

	void OnMouseClick() override {
		if (IsMouseOver())
			*m_pbSelected = !*m_pbSelected;
	}

public:
	Checkbox(Window* parent, Vector2 position, std::string text, bool *bSelected) : WindowComponent(parent, position.x, position.y, 0, 0), m_text(text), m_pbSelected(bSelected) {
		float width = GetBase()->GetTextFontSize(text, m_textScale).x;
		SetSize(Vector2(m_boxSize+width, m_boxSize));
	}

	static float GetHeight() { return m_boxSize; }
};