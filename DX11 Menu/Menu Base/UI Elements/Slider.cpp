#include "stdafx.h"
#include "Slider.h"
const float Slider::SLIDER_HEIGHT = 20.f;
const float Slider::LINE_WIDTH = 2.f;
const float Slider::SLIDER_WIDTH = 8.f;

void Slider::OnRender() {
	Vector2 position = GetPosition();
	Vector2 size = GetSize();

	int percent = *m_value * 100.f / m_max;
	m_sliderPositionOffset = percent * size.x / 100.f;
	DrawRect(position.x, position.y + (size.y / 2.f), size.x, LINE_WIDTH, m_lineColor);
	DrawRect(position.x + m_sliderPositionOffset - (SLIDER_WIDTH / 2.f), position.y, SLIDER_WIDTH, SLIDER_HEIGHT, m_boxColor);
}

bool Slider::IsMouseOnSliderBar() {
	POINT mousePos = GetMouseRelativePosition();
	Vector2 position = GetPosition() + GetParent()->GetWindowPosition();
	Vector2 size = GetSize();
	if (mousePos.x > (position.x - SLIDER_WIDTH) && mousePos.x < (position.x + size.x + SLIDER_WIDTH))
		if (mousePos.y > position.y && mousePos.y < (position.y + size.y))
			return true;
	return false;
}

void Slider::OnMouseDown() {
	Vector2 sliderBeginPos = GetPosition() + GetParent()->GetWindowPosition();
	POINT mousePos = GetMouseRelativePosition();
	float sliderEndPos = sliderBeginPos.x + GetSize().x;
	float dragClipDistance = (100.0f / m_max * GetSize().x / 100.0f);
	if (IsMouseOnSliderBar()) {
		int pxOffsetFromStart = mousePos.x - sliderBeginPos.x;
		if (pxOffsetFromStart <= sliderEndPos) {
			int estimatedValue = pxOffsetFromStart / dragClipDistance;
			if (estimatedValue >= 0 && estimatedValue <= m_max)
				*m_value = estimatedValue;
		}

	}
}
