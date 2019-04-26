#pragma once
#include "stdafx.h"
class Slider : public WindowComponent
{
	const float LINE_WIDTH = 2.f;
	const float SLIDER_WIDTH = 8.f;
	const float SLIDER_HEIGHT = 20.f;

	DXColor m_mouseOverBox = D3DCOLOR_RGBA(0, 0, 0, 255);
	DXColor m_defaultBoxColor = D3DCOLOR_RGBA(180, 184, 187, 255);
	DXColor m_defaultLineColor = D3DCOLOR_RGBA(100, 104, 107, 255);
	DXColor m_clickedLineColor = D3DCOLOR_RGBA(0, 0, 0, 255);

	float m_sliderPositionOffset = 0;

	int m_value = 0;
	int m_max = 5;

	DXColor m_lineColor = m_defaultLineColor;
	DXColor m_boxColor = m_defaultBoxColor;

	void OnRender() {
		Vector2 position = GetPosition();
		Vector2 size = GetSize();

		int percent = m_value * 100.f / m_max;
		m_sliderPositionOffset = percent * size.x / 100.f;
		DrawRect(position.x, position.y + (size.y / 2.f), size.x, LINE_WIDTH, m_lineColor);
		DrawRect(position.x + m_sliderPositionOffset - (SLIDER_WIDTH / 2.f), position.y, SLIDER_WIDTH, SLIDER_HEIGHT, m_boxColor);
	}

	bool IsMouseOnSliderBar() {
		POINT mousePos = GetMouseRelativePosition();
		Vector2 position = GetPosition() + GetParent()->GetWindowPosition();
		Vector2 size = GetSize();
		if (mousePos.x > position.x && mousePos.x < (position.x + size.x + SLIDER_WIDTH))
			if (mousePos.y > position.y && mousePos.y < (position.y + size.y))
				return true;
		return false;
	}



	void OnMouseDown() {
		Vector2 sliderBeginPos = GetPosition() + GetParent()->GetWindowPosition();

		POINT mousePos = GetMouseRelativePosition();
		float sliderEndPos = sliderBeginPos.x + GetSize().x;
		float dragClipDistance = (100.0f / m_max * GetSize().x / 100.0f);
		if (IsMouseOnSliderBar()) {
			int pxOffsetFromStart = mousePos.x - sliderBeginPos.x;
			if (pxOffsetFromStart <= sliderEndPos)
				m_value = pxOffsetFromStart / dragClipDistance;
			
		}
	}


public:
	Slider(Window* parent, Vector2 pos, float width) : WindowComponent(parent, pos.x, pos.y, 0, 0) { SetSize(Vector2(width, SLIDER_HEIGHT)); }
	~Slider() {}
};

