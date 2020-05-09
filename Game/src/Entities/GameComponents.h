#pragma once

namespace Game
{
    struct ObstacleComponent : public Engine::Component
    {
        float m_Speed{};
        ObstacleComponent(float speed) : m_Speed(speed) {};
    };

    struct WallComponent : public Engine::Component
    {
        
    };

    struct ScoreComponent : public Engine::Component
    {

    };
}