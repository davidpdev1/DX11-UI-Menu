#pragma once
#include "stdafx.h"
#include <iostream>
class Checkbox;
class WindowComponent;

class Window : public MenuComponent {
	const float WINDOW_OUTLINE_SIZE = 1.f;
	const float WINDOW_TITLE_RECT_SIZE = 30;
	DXColor m_titleBoxColor = { 200.f / 255.f, 0, 0, 0.8f };
	DXColor m_backgroundColor = { 30.f / 255.f, 34.f / 255.f, 37.f / 255.f, 0.8f };
	DXColor m_borderColor = { 50.f / 255.f, 54.f / 255.f, 57.f / 255.f, 0.8f };

	POINT m_dragPointBegin = { INT_MAX, INT_MAX };
	bool m_isInitFrame = true;

	std::vector<std::unique_ptr<WindowComponent>> m_windowComponents;

	void OnRender() override;

	void OnMouseDown() override;

	void OnMouseUp() override;

	void OnKeyDown(DWORD key) override;

	

public:
	Window();
	Vector2 GetWindowPosition() {
		return GetPosition();
	}
protected:
	virtual void OnWindowRender() { }
	virtual void OnBuild() { }
	void AddCheckbox(float x, float y, std::string text, bool *toggle);
};
