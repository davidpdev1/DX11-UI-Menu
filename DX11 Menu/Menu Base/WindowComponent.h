#pragma once
#include "stdafx.h"
class WindowComponent : public MenuComponent {
	Window *m_pParent;
	Vector2 m_windowPreviousPosition;
	Vector2 m_position;


	void OnRenderAlt() override {
		if (m_windowPreviousPosition != m_pParent->GetWindowPosition())
			SetPosition(Vector2(m_pParent->GetWindowPosition().x + m_position.x, m_pParent->GetWindowPosition().y + m_position.y));
	}

public:
	WindowComponent(Window *parent, float x, float y, float width, float height) : MenuComponent(Vector2(parent->GetWindowPosition().x + x, parent->GetWindowPosition().y + y), Vector2(width, height)), m_pParent(parent), m_position(x, y) {
		m_windowPreviousPosition = m_pParent->GetWindowPosition();
	}
	Vector2 GetPosition() override {
		return m_position;
	}
protected:
	
	Window *GetParent() {
		return m_pParent;
	}
	void DrawText(float x, float y, std::string text, DXColor color, float scale = 1.f);
	void DrawRectOutline(float x, float y, float width, float height, float thickness, DXColor color);
	void DrawRect(float x, float y, float width, float height, DXColor color);

};
