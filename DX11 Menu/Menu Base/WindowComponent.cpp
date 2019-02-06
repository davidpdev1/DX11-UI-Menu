#include "stdafx.h"
#include "WindowComponent.h"

void WindowComponent::DrawText(float x, float y, std::string text, DXColor color, float scale) {
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
