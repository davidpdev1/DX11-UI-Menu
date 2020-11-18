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

	void OnRender() override;
	void OnMouseEnter() override;
	void OnMouseLeave() override;
	void OnMouseClick() override;

public:
	Checkbox(Window* parent, Vector2 position, std::string text, bool *bSelected);

	static float GetHeight() { return m_boxSize; }
};