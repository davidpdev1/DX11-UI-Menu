#pragma once
#include "stdafx.h"
class Groupbox : public WindowComponent
{
	static bool m_bIsPartOfGroupbox;
	static Groupbox *m_pCurrentGroupbox;
	Vector2 m_offsetForInsideComponents = Vector2(8, 8);
	DXColor m_borderColor = { 0.5f, 0.5f, 0.5f, 0.05f};

	std::string m_title;
	const float m_thickness = 1;
	// These are calculated once
	Vector2 m_pxTitleSize;
	Vector2 m_upLineBeginLeft;
	Vector2 m_upLineBeginRight;
	float m_upLineRightWidth;
	Vector2 m_titleBeginPos;

	void OnRender() override {
		Vector2 position = GetPosition();
		Vector2 size = GetSize();

		// Up left 20px long line
		DrawRect(m_upLineBeginLeft.x, m_upLineBeginLeft.y, 20, m_thickness, m_borderColor);
		// Groupbox name
		DrawText(m_titleBeginPos.x, m_titleBeginPos.y, m_title, WHITE);
		// Right line(after name)
		DrawRect(m_upLineBeginRight.x, m_upLineBeginRight.y, m_upLineRightWidth, m_thickness, m_borderColor);
		// Rest of the full lines
		DrawRectOutline(position.x, position.y, size.x, size.y, m_thickness, m_borderColor, BORDERIGNORE_TOP);
	}
public:
	Groupbox(Window *parent, Vector2 pos, Vector2 scale, std::string name);
	~Groupbox();

	static bool IsPartOfGroupbox() {
		return m_bIsPartOfGroupbox;
	}

	static Groupbox* GetActiveGroupbox() {
		return m_pCurrentGroupbox;
	}

	Vector2 GetOffset() {
		return m_offsetForInsideComponents;
	}

	void Register(std::function<void()> options) {
		m_bIsPartOfGroupbox = true;
		m_pCurrentGroupbox = this;
		options();
		m_bIsPartOfGroupbox = false;
		m_pCurrentGroupbox = nullptr;
	}
};

