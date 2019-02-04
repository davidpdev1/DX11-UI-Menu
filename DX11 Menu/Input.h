#pragma once
#include "stdafx.h"

// TODO: Callback based stuff
class Input {
	struct KeyState {
		bool pressed;
		short count;
	};

	static Input m_instance;
	std::unordered_map<DWORD, KeyState> m_Keys;
	std::vector<std::function<void(bool, DWORD)>> m_callbacks;

	Input();
	~Input();
public:
	static Input* Get() {
		return &m_instance;
	}


	// void callback(bool keyUpEvent, DWORD vkKeyCode);
	// if keyUpEvent is false then it means it's a key down event.
	void RegisterCallback(std::function<void(bool, DWORD)> callback) {
		m_callbacks.push_back(callback);
	}

	void ReportKeyUp(DWORD key) {
		for (auto cb : m_callbacks)
			cb(1, key);
		m_Keys[key] = { false, 0 };
	}

	void ReportKeyDown(DWORD key, short count) {
		for (auto cb : m_callbacks)
			cb(0, key);
		m_Keys[key] = { true, count };
	}

	bool IsKeyDown(DWORD key) {
		return m_Keys[key].pressed;
	}
};

