#include "precomp.h"
#include "Window.h"

#include <SDL.h>

namespace Game
{
    bool Window::Init(const WindowData& windowData_)
    {
        std::cout<<"Initializing Window";

        m_WindowData = windowData_;
        if(m_WindowData.m_Width > 0 && m_WindowData.m_Height > 0)
            std::cerr<<"Window size must be greater than zero";

        m_NativeWindowHandle = SDL_CreateWindow(
            m_WindowData.m_Title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_WindowData.m_Width,
            m_WindowData.m_Height,
            0
        );

        if (m_NativeWindowHandle == nullptr)
        {
            std::cerr<<"Unable to create a window. SDL Error:"<< SDL_GetError();
            return false;
        }

        std::cout<<"Window successfully initialized";
        return true;
    }

    bool Window::Shutdown()
    {
        std::cout<<"Shutting down Window";

        if (m_NativeWindowHandle != nullptr)
        {
            SDL_DestroyWindow(m_NativeWindowHandle);
        }

        m_NativeWindowHandle = nullptr;

        return true;
    }

    Window::~Window()
    {
        Shutdown();
    }
}
