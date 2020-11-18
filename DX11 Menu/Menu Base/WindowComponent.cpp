#include "stdafx.h"
#include "WindowComponent.h"

void WindowComponent::OnRenderAlt() {
	if (m_windowPreviousPosition != m_pParent->GetWindowPosition())
		SetPosition(Vector2(m_pParent->GetWindowPosition().x + m_position.x, m_pParent->GetWindowPosition().y + m_position.y));
}

WindowComponent::WindowComponent(Window * parent, float x, float y, float width, float height) 
	: MenuComponent(Vector2(parent->GetWindowPosition().x + x, parent->GetWindowPosition().y + y), 
		Vector2(width, height)), 
	m_pParent(parent), 
	m_position(x, y),
	m_windowPreviousPosition(m_pParent->GetWindowPosition()) { }

void WindowComponent::DrawText(float x, float y, const std::string& text, DXColor color, float scale) {
	Vector2 window = m_pParent->GetWindowPosition();
	GetBase()->DrawText(window.x + x, window.y + y, text, color);
}

void WindowComponent::DrawRectOutline(float x, float y, float width, float height, float thickness, DXColor color, unsigned char flag) {
	Vector2 window = m_pParent->GetWindowPosition();
	GetBase()->DrawRectOutline(window.x + x, window.y + y, width, height, thickness, color, flag);
}

void WindowComponent::DrawRect(float x, float y, float width, float height, DXColor color) {
	Vector2 window = m_pParent->GetWindowPosition();
	GetBase()->DrawRect(window.x + x, window.y + y, width, height, color);
}
