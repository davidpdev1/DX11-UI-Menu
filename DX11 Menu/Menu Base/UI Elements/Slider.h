#pragma once
#include "stdafx.h"
class Slider : public WindowComponent
{
	const float LINE_WIDTH = 2.f;
	const float SLIDER_WIDTH = 8.f;
	const float SLIDER_HEIGHT = 20.f;
	POINT m_dragPointBegin = { INT_MAX, INT_MAX };
	float m_sliderPositionOffset = 0;

	int m_value = 50;
	int m_max = 100;
	int m_increment = 1;

	void OnRender() {
		Vector2 position = GetPosition();
		Vector2 size = GetSize();

		int percent = m_value * 100.f / m_max;
		m_sliderPositionOffset = percent * size.x / 100.f;
		DrawRect(position.x, position.y + (size.y / 2.f), size.x, LINE_WIDTH, RED);
		DrawRect(position.x + m_sliderPositionOffset - (SLIDER_WIDTH / 2.f), position.y, SLIDER_WIDTH, SLIDER_HEIGHT, GREEN);
	}

	bool IsMouseOnSlider() {
		POINT mousePos = GetMouseRelativePosition();
		float sliderPosPx = m_sliderPositionOffset + GetParent()->GetWindowPosition().x;
		return
			IsMouseOver() &&
			(mousePos.x > sliderPosPx) &&
			(mousePos.x < (sliderPosPx + SLIDER_WIDTH));
	}
	int count = 1;
	void OnMouseDown() {
		printf("MouseDown\n");
		Vector2 currentPos = GetPosition() + GetParent()->GetWindowPosition();
		POINT mousePos = GetMouseRelativePosition();

		if (IsMouseOnSlider() && m_dragPointBegin.x == INT_MAX)
			m_dragPointBegin = mousePos;

		if (m_dragPointBegin.x != INT_MAX) {
			POINT offset = { mousePos.x - m_dragPointBegin.x, mousePos.y - m_dragPointBegin.y };
			printf("MousePos.x %i - dragPoint.x - %i\n", mousePos.x, m_dragPointBegin.x);
			float dragClipDistance = (100.0f / m_max * GetSize().x / 100.0f);
			printf("%f\nOFF: %i\n", dragClipDistance, offset.x);
			if (round((offset.x / dragClipDistance)) >= count) {
				m_value += m_increment;
				count++;
			}
			else if (round((abs(offset.x) / dragClipDistance)) >= count) {
				m_value -= m_increment;
				count++;
			}
		}
	}

	void OnMouseUp() {
		printf("UP!\n");
		m_dragPointBegin = { INT_MAX, INT_MAX };
		count = 0;
	}

public:
	Slider(Window* parent, Vector2 pos, float width) : WindowComponent(parent, pos.x, pos.y, 0, 0) { SetSize(Vector2(width, SLIDER_HEIGHT)); }
	~Slider() {}
};

