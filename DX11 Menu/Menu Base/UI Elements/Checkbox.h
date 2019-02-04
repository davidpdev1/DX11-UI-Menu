#pragma once
#include "stdafx.h"

class Checkbox : public WindowComponent {
	// x == y expected for box size.
	static float m_boxSize;  // 16
	static float m_checkedBoxSize; // 12   check .cpp to edit

	const float m_labelPadding = 4; // # of pixels inbetween the box and the text

	DXColor m_boxColor = { 50.f / 255.f, 54.f / 255.f, 57.f / 255.f, 1 };
	
	DXColor m_borderColor = { 90.f / 255.f, 94.f / 255.f, 97.f / 255.f, 1 };
	DXColor m_mouseOverBorderColor = { 180.f / 255.f, 184.f / 255.f, 187.f / 255.f, 1 };
	DXColor m_selectedColor = { 230.f / 255.f, 234.f / 255.f, 237.f / 255.f, 1 };

	DXColor currentBorderColor = m_borderColor;
	DXColor currentBoxBackground = m_boxColor;
	
	bool *m_pbSelected;
	std::string m_text;
	float m_textScale = 1.0f;

	void OnRender() override {
		Vector2 myPos = GetPosition();
		DrawRect(m_position.x, m_position.y, m_boxSize, m_boxSize, m_boxColor);
		DrawRectOutline(m_position.x, m_position.y, m_boxSize, m_boxSize, 2, currentBorderColor);
		if (*m_pbSelected) {
			float offsetToCenter = (m_boxSize - m_checkedBoxSize) / 2.f;
			DrawRect(m_position.x + offsetToCenter, m_position.y + offsetToCenter, m_checkedBoxSize, m_checkedBoxSize, m_selectedColor);
		}
		DrawText(m_position.x+m_boxSize + m_labelPadding, m_position.y, m_text, WHITE, m_textScale);
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