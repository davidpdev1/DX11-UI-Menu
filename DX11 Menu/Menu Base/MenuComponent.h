#pragma once
#include "stdafx.h"
class MenuComponent {
private:
	static Base *m_pBase;
	static HWND m_hWnd;
	bool m_isMouseOver;
	Vector2 m_position;
	// Width & Height
	Vector2 m_size;
	Vector2 m_offset;
	
	void MouseEnter();
	void MouseLeave();
public:
	static void Initialize(Base *pBase) { m_pBase = pBase; }
	static void SetWindow(HWND hwnd) { m_hWnd = hwnd; }


	MenuComponent(Vector2 position, Vector2 size);
	void Render();

protected:
	virtual void OnRender() { }
	virtual void OnRenderAlt() { }
	virtual void OnMouseEnter() { }
	virtual void OnMouseLeave() { }
	virtual void OnMouseDown() { }
	virtual void OnMouseUp() { }
	virtual void OnMouseClick() { }
	virtual void OnKeyUp(DWORD key) { }
	virtual void OnKeyDown(DWORD key) { }
	virtual Vector2 GetPosition() { return m_position; }

	inline POINT GetMouseRelativePosition();
	inline Base *GetBase() { return m_pBase; }
	inline bool IsMouseOver() { return m_isMouseOver; }
	inline Vector2 GetSize() { return m_size; }
	inline void SetPosition(Vector2 position) { m_position = position; }
	inline void SetSize(Vector2 size) { m_size = size; }
};
