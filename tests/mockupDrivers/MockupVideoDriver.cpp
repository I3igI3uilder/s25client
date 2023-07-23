// Copyright (C) 2005 - 2021 Settlers Freaks (sf-team at siedler25.org)
//
// SPDX-License-Identifier: GPL-2.0-or-later

#include "MockupVideoDriver.h"
#include <boost/nowide/iostream.hpp>
#include <iostream>

MockupVideoDriver::MockupVideoDriver(VideoDriverLoaderInterface* CallBack) : VideoDriver(CallBack), tickCount_(1)
{
    modKeyState_.kt = KeyType::Invalid;
    modKeyState_.c = 0;
    modKeyState_.ctrl = false;
    modKeyState_.shift = false;
    modKeyState_.alt = false;
}

MockupVideoDriver::~MockupVideoDriver() = default;

const char* MockupVideoDriver::GetName() const
{
    return "Mockup Video Driver";
}

bool MockupVideoDriver::Initialize()
{
    if(initialized)
        return true;
    initialized = true;
    return true;
}

bool MockupVideoDriver::CreateScreen(const std::string&, const VideoMode& newSize, bool fullscreen)
{
    ResizeScreen(newSize, fullscreen);
    return true;
}

bool MockupVideoDriver::ResizeScreen(const VideoMode& newSize, bool fullscreen)
{
    SetNewSize(newSize, Extent(newSize.width, newSize.height));
    isFullscreen_ = fullscreen;
    return true;
}

bool MockupVideoDriver::MessageLoop()
{
    return true;
}

unsigned long MockupVideoDriver::GetTickCount() const
{
    return tickCount_;
}

static void* dummyLoader(const char*)
{
    return nullptr;
}

OpenGL_Loader_Proc MockupVideoDriver::GetLoaderFunction() const
{
    return dummyLoader;
}

void MockupVideoDriver::ListVideoModes(std::vector<VideoMode>& video_modes) const
{
    video_modes = video_modes_;
}

void MockupVideoDriver::SetMousePos(Position pos)
{
    mouse_xy.pos = pos;
}

void MockupVideoDriver::setGuiScalePercent(unsigned percent)
{
    if(setGuiScaleInternal(percent))
    {
        const auto windowSize = GetWindowSize();
        SetNewSize(windowSize, Extent(windowSize.width, windowSize.height));
    }
}

KeyEvent MockupVideoDriver::GetModKeyState() const
{
    return modKeyState_;
}

void* MockupVideoDriver::GetMapPointer() const
{
    return nullptr;
}

void MockupVideoDriver::ShowErrorMessage(const std::string& title, const std::string& message)
{
    std::cerr << title << ": " << message << std::endl;
}
