#include "stdafx.h"
#include "Base.h"
#include "Window.h"

MainWindow *pMainMenu;

struct tmpDrawTxt {
	FXMVECTOR pos;
	FXMVECTOR color;
	std::wstring str;
	Vector2 origin;
	float scale;
};

std::vector<tmpDrawTxt> tmpVec;

void Base::Render() {
	// Draw the temporary background
	m_pSpriteBatch->Begin();
	m_pSpriteBatch->Draw(m_pTexture, XMFLOAT2(0, 0));
	m_pSpriteBatch->End();

	// Restore what sprite batch messed up
	m_pDeviceContext->VSSetShader(m_pVertexShader, 0, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, 0, 0);
	m_pDeviceContext->IASetInputLayout(m_pLayout);

	//// Draw our shapes
	m_vertexBuffer.Begin(m_pDeviceContext);
	m_lsVertexBuffer.Begin(m_pDeviceContext);

	// Rendering in between here.
	if (!pMainMenu) pMainMenu = new MainWindow();
	pMainMenu->Render();
	DrawRect(900, 200, 5, 5, RED);
	m_lsVertexBuffer.Render(m_pDeviceContext);
	m_vertexBuffer.Render(m_pDeviceContext);

	m_pSpriteBatch->Begin();
	for (auto s : tmpVec)
		m_pFont->DrawString(m_pSpriteBatch, s.str.c_str(), s.pos, s.color, 0.f, Vector2(0, 0), s.scale);
	tmpVec.clear();
	m_pSpriteBatch->End();


}

Vector2 Base::GetTextFontSize(std::string str, float scale) {
	Vector2 size = m_pFont->MeasureString(std::wstring(str.begin(), str.end()).c_str());
	return size * scale;
}

void Base::DrawText(float x, float y, std::string text, DXColor color, float scale) {
	std::wstring wstr = std::wstring(text.begin(), text.end());
	Vector2 origin = m_pFont->MeasureString(wstr.c_str()) / 2.f;
	tmpVec.push_back({ (FXMVECTOR)Vector2(x, y), *(FXMVECTOR*)&color, wstr, origin, scale });
	//const wchar_t* str = wstr.c_str();
	//m_pFont->DrawString(m_pSpriteBatch, str, (FXMVECTOR)Vector2(x, y), *(FXMVECTOR*)&color, 0.f, origin, 1.0f, SpriteEffects_None, 0.0f);
}

void Base::DrawCircle(float x, float y, float radius, DXColor color) {

	vertex_list circle;
	const int NUMPOINTS = 50;
	float WedgeAngle = (float)((2 * XM_PI) / NUMPOINTS);
	for (int i = 0; i <= NUMPOINTS; i++)
	{
		float Theta = (float)(i * WedgeAngle);
		float xn = (float)(x + radius * cos(Theta));
		float yn = (float)(y - radius * sin(Theta));
		if (i == 0)
			color = BLUE;
		else if (i == NUMPOINTS - 1)
			color = GREEN;
		else 
			color = RED;
		circle.push_back({ C2DX_X(xn - 0.5f), C2DX_Y(yn - 0.5f), 0, color });
	}


	m_lsVertexBuffer.Push<vertex_list>(circle);
}

// Render sprite instead?
void Base::DrawFilledCircle(float x, float y, float radius, DXColor color) {
	vertex_list circle;
	const int NUMPOINTS = 50;
	float WedgeAngle = (float)((2 * XM_PI) / NUMPOINTS);
	for (int i = 0; i < NUMPOINTS; i++) {
		float Theta = (float)((i+1) * WedgeAngle);
		float xn = (float)(x + radius * cos(Theta));
		float yn = (float)(y - radius * sin(Theta));
		
		m_vertexBuffer.Push<Vertex>({ C2DX_X(x), C2DX_Y(y), 0, color });
		m_vertexBuffer.Push<Vertex>({ C2DX_X(xn - 0.5f), C2DX_Y(yn - 0.5f), 0, color });
		Theta = (float)((i) * WedgeAngle);
		xn = (float)(x + radius * cos(Theta));
		yn = (float)(y - radius * sin(Theta));
		m_vertexBuffer.Push<Vertex>({ C2DX_X(xn - 0.5f), C2DX_Y(yn - 0.5f), 0, color });
	}
}

void Base::DrawRect(float x, float y, float width, float height, DXColor color) {
	
	x = C2DX_X(x);
	y = C2DX_Y(y);
	width = C2DX_W(width);
	height = C2DX_H(height);
	vertex_list vl = {
		{x, y, 0, color}, // top left
		{x + width, y, 0, color }, // top right
		{x, y - height, 0, color}, // bottom left

		{x + width, y - height, 0, color}, // bottom right
		{x, y - height, 0, color}, // bottom left
		{x + width, y, 0, color}, // top right
	};
	m_vertexBuffer.Push<vertex_list>(vl);
}

void Base::DrawRectOutline(float x, float y, float width, float height, float thickness, DXColor color, unsigned char flag) {
	x -= thickness;
	width += thickness;
	y -= thickness;
	height += thickness;

	if (flag & BORDERIGNORE_TOP) {
		y += thickness;
		height -= thickness;
	}
	if (flag & BORDERIGNORE_LEFT) {
		x += thickness;
		width -= thickness;
	}
	if (flag & BORDERIGNORE_BOTTOM) {
		y += thickness;
		height -= thickness;
	}

	if(!(flag & BORDERIGNORE_TOP))
		DrawRect(x, y, width, thickness, color); // top line
	if (!(flag & BORDERIGNORE_LEFT))
		DrawRect(x, y, thickness, height, color); // left line
	if (!(flag & BORDERIGNORE_BOTTOM))
		DrawRect(x, y + height, width + ((flag & BORDERIGNORE_RIGHT) ? 0 : thickness), thickness, color); // bottom line
	if (!(flag & BORDERIGNORE_RIGHT))
		DrawRect(x + width, y, thickness, height, color); // right line

}





void Base::EnableAlphaBlending() {
	D3D11_BLEND_DESC blendDesc = { 0 };

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11BlendState * blendState;
	if (FAILED(m_pDevice->CreateBlendState(&blendDesc, &blendState)))
		fprintf(stderr, "Failed to enable alpha blending...\n");

	m_pDeviceContext->OMSetBlendState(blendState, NULL, 0xffffffff);
}

void Base::InitPipeline() {
	// load and compile the two shaders
	ID3DBlob *VS, *PS;
	D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &VS, 0);
	D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &PS, 0);

	m_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVertexShader);
	m_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPixelShader);

	m_pDeviceContext->VSSetShader(m_pVertexShader, 0, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	m_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &m_pLayout);
	m_pDeviceContext->IASetInputLayout(m_pLayout);

	EnableAlphaBlending();
}



void Base::Initialize(ID3D11Device *pDevice, IDXGISwapChain *pSwapchain, ID3D11DeviceContext *pDeviceContext) {
	m_pDevice = pDevice;
	m_pSwapchain = pSwapchain;
	m_pDeviceContext = pDeviceContext;
	InitPipeline();
	m_vertexBuffer.Initialize(pDevice);
	m_lsVertexBuffer.Initialize(pDevice);

	m_pFont = new SpriteFont(m_pDevice, L"baseFont.spritefont");

	m_pSpriteBatch = new SpriteBatch(m_pDeviceContext);
	ID3D11Resource *res;
	CreateWICTextureFromFile(m_pDevice, L"screen.jpg", &res, &m_pTexture);

	MenuComponent::Initialize(this);

}
Base::Base() : m_vertexBuffer(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, MAX_RECT_VERTICES), m_lsVertexBuffer(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, MAX_LS_VERTICES) { }

Base::~Base() {
	m_pVertexShader->Release();
	m_pPixelShader->Release();
	m_pLayout->Release();
	m_pTexture->Release();
	delete m_pSpriteBatch;
	delete m_pFont;
	if (pMainMenu)
		delete pMainMenu;
	//m_pVertexBuffer->Release();
}