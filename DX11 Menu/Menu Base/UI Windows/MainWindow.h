#pragma once
#include "stdafx.h"
class MainWindow : public Window
{
	bool m_checkMeTest;
	float fps;
	float frames;
	DWORD time;
	DWORD GetTime() {
		milliseconds ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			);
		return static_cast<DWORD>(ms.count());
	}
	void OnWindowRender() override {
		GetBase()->DrawFilledCircle(900, 200, 100, D3DCOLOR_RGBA(2, 150, 250, 200));
		frames++;
		if (GetTime() > time) {
			fps = frames;
			frames = 0;
			time = GetTime() + 1000;
		}
		GetBase()->DrawText(50, 50, std::to_string(fps), RED);
	}

	// Add UI elements here. It is executed once on the render thread.
	void OnBuild() override {
		SetTitle("Main Window");
		printf("Built!\n");
		AddCheckbox(5, 5, "Check me!", &m_checkMeTest);
		AddSlider(5, 15 + Checkbox::GetHeight(), 250);
		AddGroupbox(5, 100, 200, 100, "i am a sentence to test stuff", [=]{
			AddCheckbox(0, 0 , "Check me! (gb)", &m_checkMeTest);
		});
	}

public:
	MainWindow();
	~MainWindow();
};

