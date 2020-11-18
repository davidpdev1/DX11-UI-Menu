#pragma once
#include "stdafx.h"
class WindowComponent : public MenuComponent {
	Window *m_pParent;
	Vector2 m_windowPreviousPosition;
	Vector2 m_position;


	void OnRenderAlt() override;

public:
	WindowComponent(Window *parent, float x, float y, float width, float height);
	Vector2 GetPosition() override { return m_position; }
protected:
	
	Window *GetParent() { return m_pParent; }
	void DrawText(float x, float y, const std::string& text, DXColor color, float scale = 1.f);
	void DrawRectOutline(float x, float y, float width, float height, float thickness, DXColor color, unsigned char flag = 0);
	void DrawRect(float x, float y, float width, float height, DXColor color);

};
