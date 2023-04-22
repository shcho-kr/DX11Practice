﻿////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <stdio.h>


GraphicsClass::GraphicsClass()
{
    m_D3D = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
    bool result;


    // Direct3D 객체를 생성합니다.
    m_D3D = new D3DClass;
    if (!m_D3D)
    {
        return false;
    }

    // Direct3D 객체를 초기화합니다.
    result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
    if (!result)
    {
        MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
        return false;
    }

    FILE* fp = nullptr;
    fopen_s(&fp, "video card info.txt", "wt");
    if (fp != nullptr)
    {
        char cardName[255] = {};
        int memory = 0;
        m_D3D->GetVideoCardInfo(cardName, memory);
        fprintf_s(fp, "video card name: %s\n", cardName);
        fprintf_s(fp, "video card memory: %d", memory);
        fclose(fp);
    }

    return true;
}


void GraphicsClass::Shutdown()
{
    // D3D 객체를 반환합니다.
    if (m_D3D)
    {
        m_D3D->Shutdown();
        delete m_D3D;
        m_D3D = 0;
    }

    return;
}


bool GraphicsClass::Frame()
{
    bool result;


    // 그래픽 렌더링을 수행합니다.
    result = Render();
    if (!result)
    {
        return false;
    }

    return true;
}


bool GraphicsClass::Render()
{
    // 씬 그리기를 시작하기 위해 버퍼의 내용을 지웁니다.
    m_D3D->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);


    // 버퍼에 그려진 씬을 화면에 표시합니다.
    m_D3D->EndScene();

    return true;
}