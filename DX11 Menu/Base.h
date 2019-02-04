#pragma once
#include "stdafx.h"
#define BORDERIGNORE_TOP 0x1
#define BORDERIGNORE_LEFT 0x2
#define BORDERIGNORE_BOTTOM 0x4
#define BORDERIGNORE_RIGHT 0x8
class Base {
private:
	// Stuff stolen from the game
	ID3D11Device *m_pDevice;
	IDXGISwapChain *m_pSwapchain;
	ID3D11DeviceContext *m_pDeviceContext;

	// Stuff we need to clean
	ID3D11VertexShader *m_pVertexShader;
	ID3D11PixelShader *m_pPixelShader;
	ID3D11InputLayout *m_pLayout;

	VertexBuffer m_vertexBuffer; // triangle list topology
	VertexBuffer m_lsVertexBuffer; // Line strip topology
	SpriteBatch *m_pSpriteBatch;
	SpriteFont *m_pFont;
	ID3D11ShaderResourceView *m_pTexture;
	//Window mainMenu;

	void EnableAlphaBlending();

	void InitPipeline();
public:
	Vector2 GetTextFontSize(std::string str, float scale);
	void DrawText(float x, float y, std::string text, DXColor color, float scale = 1.f);
	void DrawCircle(float x, float y, float radius, DXColor color);
	/*
	Draws a rectangle...

	@x: X Position (in pixels)
	@y: Y Position (in pixels)
	@width: Width (in pixels)
	@height: Height (in pixels)
	@DXColor: Outline color
	*/
	void DrawRect(float x, float y, float width, float height, DXColor color);
	/*
	Draws an outline of a rectangle.
	It will draw around the rectangle (it will not overlap it, meaning the outline
	will be a little bit bigger than the actual specified size)

	@x: X Position (in pixels)
	@y: Y Position (in pixels)
	@width: Width (in pixels)
	@height: Height (in pixels)
	@thickness: Border thickness (in pixels)
	@DXColor: Outline color
	*/
	void DrawRectOutline(float x, float y, float width, float height, float thickness, DXColor color, unsigned char flag = 0);

	void Render();



	void Initialize(ID3D11Device *pDevice, IDXGISwapChain *pSwapchain, ID3D11DeviceContext *pDeviceContext);
	Base();
	~Base();
};