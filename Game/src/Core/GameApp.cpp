#include "precomp.h"

#include "GameApp.h"
#include "Entities/CameraController.h"
#include "Entities/PlayerController.h"
#include "Entities/StadiumController.h"
#include "Entities/StaticImage.h"
#include "Entities/ObstacleController.h"

#include <Engine.h>
#include <Core/EntryPoint.h>


void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Corona Bird";
    gameSpecificWindowData.m_Width = 1280;
    gameSpecificWindowData.m_Height = 720;
    // gameSpecificWindowData.m_Vsync = true;
    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_RenderSystem->SetBackgroundColor(0, 0, 0, 1);

    m_CameraController = std::make_unique<CameraController>();
    m_CameraController->Init(m_EntityManager.get());

    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "virus", "virus.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "background", "background.jpg");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "vaccine", "maska.jpg");

    m_Stadium = std::make_unique<Stadium>();
    m_Stadium->Init(m_EntityManager.get(), m_TextureManager->GetTexture("background"));

   
    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("virus"));

    m_ObstacleController = std::make_unique<ObstacleController>();
    m_ObstacleController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("vaccine"));

   

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EntityManager.get());
    m_CameraController->Update(dt, m_EntityManager.get());
    m_ObstacleController->Update(dt, m_EntityManager.get());

}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
