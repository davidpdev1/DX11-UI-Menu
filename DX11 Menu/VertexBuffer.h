#include "stdafx.h"
#pragma once
struct DXColor {
	float r;
	float g;
	float b;
	float a;
};
struct Vertex {
	float x, y, z;
	DXColor color;
	Vertex(float x, float y, float z, DXColor color) : x(x), y(y), z(z), color(color) {}
};
class VertexBuffer {
	ID3D11Buffer *m_pVertexBuffer;
	std::vector<Vertex> m_vertices;
	D3D11_MAPPED_SUBRESOURCE m_ms;
	D3D11_PRIMITIVE_TOPOLOGY m_type;
	int m_maxVertices;

public:
	VertexBuffer(D3D11_PRIMITIVE_TOPOLOGY type, int maxVertices) ;

	~VertexBuffer();

	void Initialize(ID3D11Device *pDevice);

	template<class T>
	void Push(T data);

	template<>
	void Push<std::vector<Vertex>>(std::vector<Vertex> data);

	template<>
	void Push<Vertex>(Vertex data);

	void Begin(ID3D11DeviceContext *pContext);

	void Render(ID3D11DeviceContext *pContext);
};
template<class T>
void VertexBuffer::Push(T data) {
	static_assert(false);
}

template<>
void VertexBuffer::Push<std::vector<Vertex>>(std::vector<Vertex> data) {
	if ((m_vertices.size() + data.size()) < m_maxVertices)
		m_vertices.insert(m_vertices.end(), data.begin(), data.end());
	else
		CRITICAL("Reached end of vertex buffer. Increase the MAX_VERTICES macro.");
}

template<>
void VertexBuffer::Push<Vertex>(Vertex data) {
	if ((m_vertices.size() + 1) < m_maxVertices)
		m_vertices.push_back(data);
	else
		CRITICAL("Reached end of vertex buffer. Increase the MAX_VERTICES macro.");
}
