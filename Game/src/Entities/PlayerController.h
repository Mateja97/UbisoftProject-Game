#pragma once

namespace Engine
{
    class EntityManager;
    class TextureManager;
}

namespace Game
{
    class PlayerController
    {
    public:
        static bool m_running;
        bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_);
        void Update(float dt, Engine::EntityManager* entityManager_);
        static int score;
    };
}