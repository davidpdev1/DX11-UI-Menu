#include "stdafx.h"
#include "Input.h"

Input Input::m_instance = Input();

// void callback(bool keyUpEvent, DWORD vkKeyCode);
// if keyUpEvent is false then it means it's a key down event.

void Input::RegisterCallback(std::function<void(bool, DWORD)> callback) {
	m_callbacks.push_back(callback);
}

void Input::ReportKeyUp(DWORD key) {
	for (auto cb : m_callbacks)
		cb(1, key);
	m_Keys[key] = { false, 0 };
}

void Input::ReportKeyDown(DWORD key, short count) {
	for (auto cb : m_callbacks)
		cb(0, key);
	m_Keys[key] = { true, count };
}

bool Input::IsKeyDown(DWORD key) {
	return m_Keys[key].pressed;
}
