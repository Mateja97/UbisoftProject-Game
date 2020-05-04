#pragma once
#include <string>

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

namespace Game
{
    struct WindowData
    {
        std::string m_Title{ "Bird Game" };
        int m_Width{ DEFAULT_WIDTH };
        int m_Height{ DEFAULT_HEIGHT };
    };
}
