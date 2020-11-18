#include "stdafx.h"
#include "MainWindow.h"


DWORD MainWindow::GetTime() {
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	return static_cast<DWORD>(ms.count());
}

void MainWindow::OnWindowRender() {
	printf("%i\n", a);
	GetBase()->DrawFilledCircle(900, 200, 100, D3DCOLOR_RGBA(r, g, b, a));
	m_frames++;
	if (GetTime() > m_time) {
		m_fps = m_frames;
		m_frames = 0;
		m_time = GetTime() + 1000;
	}
	GetBase()->DrawText(50, 50, std::to_string(m_fps), RED);
}

// Add UI elements here. It is executed once on the render thread.

void MainWindow::OnBuild() {
	SetTitle("Main Window");
	printf("Built!\n");
	AddCheckbox(10, 5, "Check me!", &m_checkMeTest);
	AddSlider(10, 15 + Checkbox::GetHeight(), 255, &r, 255);
	AddSlider(10, 40 + Slider::GetHeight(), 255, &g, 255);
	AddSlider(10, 70 + Slider::GetHeight(), 255, &b, 255);
	AddSlider(10, 100 + Slider::GetHeight(), 255, &a, 255);

	AddGroupbox(10, 150, 200, 100, "i am a sentence to test stuff", [=] {
		AddCheckbox(0, 0, "Check me! (gb)", &m_checkMeTest);
	});
}
