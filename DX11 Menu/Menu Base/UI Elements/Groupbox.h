#pragma once
#include "stdafx.h"
class Groupbox : public WindowComponent
{
	static bool m_bIsPartOfGroupbox;
	static Groupbox *m_pCurrentGroupbox;
	Vector2 m_offsetForInsideComponents = Vector2(8, 8);
	DXColor m_borderColor = { 0.5f, 0.5f, 0.5f, 0.05f};
	void OnRender() override {
		Vector2 position = GetPosition();
		Vector2 size = GetSize();
		DrawRect(position.x, position.y, size.x, size.y, m_borderColor);
	}
public:
	Groupbox(Window *parent, Vector2 pos, Vector2 scale);
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

