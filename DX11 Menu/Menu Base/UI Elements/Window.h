#pragma once
#include "stdafx.h"
class Checkbox;
class WindowComponent;
class Groupbox;
class Slider;

class Window : public MenuComponent {
	const float WINDOW_OUTLINE_SIZE = 1.f;
	const float WINDOW_TITLE_RECT_SIZE = 30;
	DXColor m_titleBoxColor = D3DCOLOR_RGBA(200, 0, 0, 204);
	DXColor m_backgroundColor = D3DCOLOR_RGBA(30, 34, 37, 204);
	DXColor m_borderColor = D3DCOLOR_RGBA(50, 54, 57, 204);

	POINT m_dragPointBegin = { INT_MAX, INT_MAX };
	bool m_isInitFrame = true;
	std::string m_title;
	float m_titleHeightOffset;
	float m_titleLeftOffset = 5;

	std::vector<std::shared_ptr<WindowComponent>> m_windowComponents;

	void OnRender() override;

	void OnMouseDown() override;

	void OnMouseUp() override;

	void OnKeyDown(DWORD key) override;

	// Updates x & y to be placed at the right place in a groupbox if needed.
	void HandleGroupbox(float *x, float *y);

public:
	Window();
	Vector2 GetWindowPosition() { return GetPosition(); }
	Vector2 GetWindowSize() { return GetSize(); }
protected:
	virtual void OnWindowRender() { }
	virtual void OnBuild() { }
	void AddCheckbox(float x, float y, const std::string& text, bool *toggle);
	void AddGroupbox(float x, float y, float width, float height, const std::string& name, std::function<void()> items);
	void AddSlider(float x, float y, float width, int* value, int max);
	void SetTitle(std::string title);
};

