#pragma once
#include "stdafx.h"
class Slider : public WindowComponent
{
	static const float LINE_WIDTH;
	static const float SLIDER_WIDTH;
	static const float SLIDER_HEIGHT;

	DXColor m_mouseOverBox = D3DCOLOR_RGBA(0, 0, 0, 255);
	DXColor m_defaultBoxColor = D3DCOLOR_RGBA(180, 184, 187, 255);
	DXColor m_defaultLineColor = D3DCOLOR_RGBA(100, 104, 107, 255);
	DXColor m_clickedLineColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	float m_sliderPositionOffset = 0;

	int m_value = 0;
	int m_max = 500;

	DXColor m_lineColor = m_defaultLineColor;
	DXColor m_boxColor = m_defaultBoxColor;

	void OnRender();
	bool IsMouseOnSliderBar();
	void OnMouseDown();



public:
	Slider(Window* parent, Vector2 pos, float width, int* value, int max) 
		: WindowComponent(parent, pos.x, pos.y, 0, 0), m_value(value), m_max(max) { SetSize(Vector2(width, SLIDER_HEIGHT)); }
	~Slider() {}

	static float GetHeight() { return SLIDER_HEIGHT; }
};

