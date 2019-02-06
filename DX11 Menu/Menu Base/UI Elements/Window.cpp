#include "stdafx.h"
#include "Window.h"
#include "Checkbox.h"
#include "WindowComponent.h"
#include "Groupbox.h"

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

		GetBase()->DrawText(pos.x + m_titleLeftOffset, pos.y + m_titleHeightOffset, m_title, WHITE, 1.f);

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

// Updates x & y to be placed at the right place in a groupbox if needed.

void Window::HandleGroupbox(float * x, float * y) {
	if (Groupbox::IsPartOfGroupbox()) {
		Groupbox *gb = Groupbox::GetActiveGroupbox();
		if (gb) {
			Vector2 offset = gb->GetOffset() + gb->GetPosition() - Vector2(0, WINDOW_TITLE_RECT_SIZE);
			*x += offset.x;
			*y += offset.y;
		}
	}
}
Window::Window() : MenuComponent(Vector2(50, 50), Vector2(600, 400)) { }

void Window::AddCheckbox(float x, float y, std::string text, bool * toggle) {
	HandleGroupbox(&x, &y);
	std::shared_ptr<Checkbox> checkbox = std::make_shared<Checkbox>(this, Vector2(x, y + WINDOW_TITLE_RECT_SIZE), text, toggle);
	m_windowComponents.push_back(checkbox);

}

void Window::AddSlider(float x, float y, float width)
{
	HandleGroupbox(&x, &y);
	std::shared_ptr<Slider> sl = std::make_shared<Slider>(this, Vector2(x, y + WINDOW_TITLE_RECT_SIZE), width);
	m_windowComponents.push_back(sl);
}


void Window::AddGroupbox(float x, float y, float width, float height, std::string name, std::function<void()> items)
{
	std::shared_ptr<Groupbox> gb = std::make_shared<Groupbox>(this, Vector2(x, y + WINDOW_TITLE_RECT_SIZE), Vector2(width, height), name);
	m_windowComponents.push_back(gb);
	
	gb->Register(items);
}



void Window::SetTitle(std::string title)
{
	m_title = title;
	m_titleHeightOffset = round(WINDOW_TITLE_RECT_SIZE / 4);
}
