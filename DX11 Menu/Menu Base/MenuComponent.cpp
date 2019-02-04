#include "stdafx.h"
#include "MenuComponent.h"
Base *MenuComponent::m_pBase = nullptr;
HWND MenuComponent::m_hWnd = NULL;

void MenuComponent::MouseEnter() {
	if (!m_isMouseOver)
		OnMouseEnter();
	m_isMouseOver = true;
}

void MenuComponent::MouseLeave() {
	if (m_isMouseOver)
		OnMouseLeave();

	m_isMouseOver = false;
}

void MenuComponent::Render() {
	// Verify if mouse is in the component
	POINT p = GetMouseRelativePosition();
	if (p.x > m_position.x && p.x < (m_position.x + m_size.x))
		if (p.y > m_position.y && p.y < (m_position.y + m_size.y))
			MouseEnter();
		else
			MouseLeave();
	else
		MouseLeave();

	if (Input::Get()->IsKeyDown(VK_LBUTTON))
		OnMouseDown();

	OnRender();
	OnRenderAlt();
}

POINT MenuComponent::GetMouseRelativePosition() {
	POINT p = { -INT_MAX, -INT_MAX };
	if (GetCursorPos(&p))
		if (ScreenToClient(m_hWnd, &p))
			return p;

	return p;
}