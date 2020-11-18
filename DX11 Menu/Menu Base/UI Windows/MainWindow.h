#pragma once
#include "stdafx.h"
class MainWindow : public Window
{
	bool m_checkMeTest;
	float m_fps;
	float m_frames;
	DWORD m_time;
	DWORD GetTime();
	int r = 2, g = 150, b = 250, a = 200;
	void OnWindowRender() override;

	// Add UI elements here. It is executed once on the render thread.
	void OnBuild() override;

public:
	MainWindow() : Window() { }
	~MainWindow() { }
};

