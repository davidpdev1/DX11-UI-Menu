#pragma once
#include "stdafx.h"
class MainWindow : public Window
{
	bool m_checkMeTest;

	void OnWindowRender() override {

	}

	// Add UI elements here. It is executed once on the render thread.
	void OnBuild() override {
		SetTitle("Main Window");
		printf("Built!\n");
		AddCheckbox(5, 5, "Check me!", &m_checkMeTest);
		AddCheckbox(5, 5 + 5 + Checkbox::GetHeight(), "Check me!", &m_checkMeTest);
	}

public:
	MainWindow();
	~MainWindow();
};

