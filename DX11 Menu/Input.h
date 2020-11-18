#pragma once
#include "stdafx.h"

class Input {
	struct KeyState {
		bool pressed;
		short count;
	};

	static Input m_instance;
	std::unordered_map<DWORD, KeyState> m_Keys;
	std::vector<std::function<void(bool, DWORD)>> m_callbacks;

	Input() { }
	~Input() { }
public:
	static Input* Get() { return &m_instance; }

	// void callback(bool keyUpEvent, DWORD vkKeyCode);
	// if keyUpEvent is false then it means it's a key down event.
	void RegisterCallback(std::function<void(bool, DWORD)> callback);

	void ReportKeyUp(DWORD key);

	void ReportKeyDown(DWORD key, short count);

	bool IsKeyDown(DWORD key);
};

