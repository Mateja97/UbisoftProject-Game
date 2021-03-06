#pragma once

#include <Core\Application.h>

namespace Game
{
    class CameraController;
    class PlayerController;
    class Stadium;
    class StaticImage;
    class ObstacleController;

    class GameApp final : public Engine::Application
    {
    private:
        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;

        std::unique_ptr<PlayerController> m_PlayerController{};
        std::unique_ptr<CameraController> m_CameraController{};
        std::unique_ptr<Stadium> m_Stadium{};
        std::unique_ptr<StaticImage> m_TestImage{};
        std::unique_ptr<ObstacleController> m_ObstacleController{};
    };

}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
