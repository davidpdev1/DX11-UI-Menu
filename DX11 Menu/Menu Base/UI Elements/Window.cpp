#include "stdafx.h"
#include "Window.h"
#include "Checkbox.h"
#include "../WindowComponent.h"

void Window::OnRender() {
	if (GetBase() != nullptr) {
		if (m_isInitFrame) {
			OnBuild();
			m_isInitFrame = false;
		}

		Vector2 pos = GetPosition();
		// Title box
		GetBase()->DrawRect(
			pos.x,
			pos.y, 
			GetSize().x, 
			WINDOW_TITLE_RECT_SIZE, 
			m_titleBoxColor);
		GetBase()->DrawRectOutline(
			pos.x, 
			pos.y, 
			GetSize().x, 
			WINDOW_TITLE_RECT_SIZE, 
			WINDOW_OUTLINE_SIZE, 
			m_borderColor, 
			BORDERIGNORE_BOTTOM);

		// Options box
		GetBase()->DrawRect(
			pos.x, 
			pos.y + WINDOW_TITLE_RECT_SIZE, 
			GetSize().x, 
			GetSize().y - WINDOW_TITLE_RECT_SIZE,
			m_backgroundColor);
		GetBase()->DrawRectOutline(
			pos.x, 
			pos.y + WINDOW_TITLE_RECT_SIZE,
			GetSize().x, 
			GetSize().y - WINDOW_TITLE_RECT_SIZE, 
			WINDOW_OUTLINE_SIZE, 
			m_borderColor, 
			BORDERIGNORE_TOP);

		for (int i = 0; i < m_windowComponents.size(); i++)
			m_windowComponents[i]->Render();
		OnWindowRender();
	}
}

void Window::OnMouseDown() {
	// Handle dragging the window around
	Vector2 currentPos = GetPosition();
	POINT mousePos = GetMouseRelativePosition();
	//Make sure mouse is over title bar before allowing window movement

	if (this->IsMouseOver())
		if (m_dragPointBegin.x == INT_MAX && (mousePos.y < (currentPos.y + WINDOW_TITLE_RECT_SIZE)))
			m_dragPointBegin = mousePos;

	// We don't check for mouse over while moving because mouse speed
	// sometimes makes it so it stops moving.
	if (m_dragPointBegin.x != INT_MAX) {
		POINT offset = { mousePos.x - m_dragPointBegin.x, mousePos.y - m_dragPointBegin.y };
		SetPosition(Vector2(currentPos.x + offset.x, currentPos.y + offset.y));
		m_dragPointBegin = mousePos;
	}
}

void Window::OnMouseUp() {
	m_dragPointBegin = { INT_MAX, INT_MAX };
}

void Window::OnKeyDown(DWORD key) {
	if (key == 'Z') {
		int r, g, b;
		printf("Enter R: ");

	}
}
Window::Window() : MenuComponent(Vector2(50, 50), Vector2(600, 400)) { }

void Window::AddCheckbox(float x, float y, std::string text, bool * toggle) {
	std::unique_ptr<Checkbox> checkbox = std::make_unique<Checkbox>(this, Vector2(x, y + WINDOW_TITLE_RECT_SIZE), text, toggle);
	m_windowComponents.push_back(std::move(checkbox));

}
