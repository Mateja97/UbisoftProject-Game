#include "RenderSystem.h"
#include "Renderer.h"
#include "Window.h"

#include <SDL.h>
#include <SDL_Image.h>

namespace Game
{
    bool RenderSystem::Init(const WindowData& windowData_)
    {
        std::cout << "Intialiazing RenderSystem";
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr<<"Unable to initialize SDL. SDL error:"<<SDL_GetError();
            return false;
        }

        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
        {
           std::cerr<<"Unable to initialize SDL_Image";
            return false;
        }

        m_Renderer = std::make_unique<Renderer>();

        if (!m_Renderer->Init(windowData_))
        {
           std::cerr<<"Unable to initialize renderer";
            return false;
        }

        m_Renderer->Init(windowData_);

        std::cout<<"RenderSystem initialized successfully";
        return true;
    }

    bool RenderSystem::Shutdown()
    {
        std::cout<<"Shutting down RenderSystem";

        m_Renderer.reset();
        SDL_Quit();

        return true;
    }

    void RenderSystem::Update(float dt_/*, EntityManager* entityManager*/)
    {
        //std::cout<<"RenderSystem::Update";

        m_Renderer->BeginScene();

        // Find all images to draw

        // Draw every image
        do
        {
            m_Renderer->DrawImage();
        } while (false);

        m_Renderer->EndScene();
    }
}
