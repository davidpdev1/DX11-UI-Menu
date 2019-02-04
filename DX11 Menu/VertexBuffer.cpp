#include "stdafx.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(D3D11_PRIMITIVE_TOPOLOGY type, int maxVertices) : m_type(type), m_maxVertices(maxVertices) {
	m_vertices.reserve(m_maxVertices);
	m_ms = { 0 };
}

VertexBuffer::~VertexBuffer() {
	m_pVertexBuffer->Release();
}

void VertexBuffer::Initialize(ID3D11Device *pDevice) {
	D3D11_BUFFER_DESC bd = { 0 };
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * m_maxVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	pDevice->CreateBuffer(&bd, NULL, &m_pVertexBuffer);
}


void VertexBuffer::Begin(ID3D11DeviceContext *pContext) {
	pContext->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &m_ms);

}

void VertexBuffer::Render(ID3D11DeviceContext *pContext) {
	if (!m_ms.pData)
		return;
	memcpy((void*)m_ms.pData, m_vertices.data(), sizeof(Vertex)*m_vertices.size());
	pContext->Unmap(m_pVertexBuffer, NULL);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	pContext->IASetPrimitiveTopology(m_type);
	pContext->Draw(static_cast<UINT>(m_vertices.size()), 0);
	m_vertices.clear();
}