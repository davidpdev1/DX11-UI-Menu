// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement changés
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows
#include <windows.h>

// Fichiers d'en-tête C RunTime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>
#include <map>
#include <unordered_map>
#include <chrono>
#include <functional>

#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

#include <d3d11.h>
#include <memory>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std::chrono;

DWORD getTime() {
	milliseconds ms = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		);
	return static_cast<DWORD>(ms.count());
}

#undef DrawText

#include "Input.h"

// référencer ici les en-têtes supplémentaires nécessaires à votre programme
#define RED {1, 0, 0, 1}
#define BLACK {0, 0, 0, 1}
#define GREEN {0, 1, 0, 1}
#define BLUE { 0, 0, 1, 1}
#define WHITE {1,1,1,1}

#define MAX_VERTICES 100
#define MAX_RECT_VERTICES 1000
#define MAX_LS_VERTICES 1000
#define CRITICAL(error) {fprintf(stderr, "CRITICAL ERROR: %s\n", error); __debugbreak();}
/*
Converts x/y pixel coords for a dx vertex
(-1, 1) - top left
(0, 0) - center
(-1, -1) bottom left
(1, 1) top right
(1, -1) bottom right
*/
#define C2DX_W(val) ((float)val) * 2.f / 1920.f
#define C2DX_H(val) ((float)val) * 2.f / 1080.f
#define C2DX_X(val) (C2DX_W(val) - 1)
#define C2DX_Y(val) (1 - C2DX_H(val))
 
#include "VertexBuffer.h"
#define vertex_list std::vector<Vertex>
#include "Base.h"
#include "MenuComponent.h"
#include "Window.h"
#include "WindowComponent.h"
#include "Checkbox.h"
#include "MainWindow.h"