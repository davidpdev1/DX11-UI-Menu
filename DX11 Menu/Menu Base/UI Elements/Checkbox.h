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

	void OnRender() override;
	void OnMouseEnter() override;
	void OnMouseLeave() override;
	void OnMouseClick() override;

public:
	Checkbox(Window* parent, Vector2 position, std::string text, bool *bSelected);

	static float GetHeight() { return m_boxSize; }
};