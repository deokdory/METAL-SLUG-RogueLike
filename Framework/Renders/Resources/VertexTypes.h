// 버텍스 정보를 저장하기 위한 구조체

#pragma once

// 색상
struct VertexColor {
	VertexColor()
		: position(0, 0, 0), color(0, 0, 0, 0) {}

	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}

	Vector3 position;	// 정점 위치
	Color color;		// 정점 색상

	static D3D11_INPUT_ELEMENT_DESC descs[];	// 정점 데이터 구조 서술
	static const uint count = 2;				// 원소 개수

};

// 텍스쳐
struct VertexTexture {
	VertexTexture()
		: position(0, 0, 0), uv(0, 0) {}

	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}

	Vector3 position;	// 정점 위치
	Vector2 uv;			// 텍스트(?) 좌표

	static D3D11_INPUT_ELEMENT_DESC descs[];	// 정점 데이터 구조 서술
	static const uint count = 2;				// 원소 개수
};