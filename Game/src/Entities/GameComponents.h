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

    struct ScoreColiderComponent : public Engine::Component
    {
        float m_Speed = 150.f;
        bool m_triggered = false;
    };
}