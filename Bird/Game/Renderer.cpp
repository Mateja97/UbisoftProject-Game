#include "Renderer.h"
#include "Window.h"
#include "Texture.h"

#include <SDL.h>

namespace Game
{

    bool Renderer::Init(const WindowData& windowData_)
    {
        std::cout<<"Initializing Renderer";


        m_Window = std::make_unique<Window>();

        if (!m_Window->Init(windowData_))
        {
            std::cerr<<"Unable to create a Window.";
        }

        m_NativeRenderer = SDL_CreateRenderer(
            m_Window->GetNativeWindowHandle(),
            -1,
            SDL_RENDERER_ACCELERATED);

        if (m_NativeRenderer == nullptr)
        {
            std::cerr << "Unable to create a renderer. SDL error:"<<SDL_GetError();
            return false;
        }

        SetBackgroundColor(100, 150, 236, SDL_ALPHA_OPAQUE);

        // TODO: Remove after testing
        m_helloWorldTexture.LoadTexture(this, "flappy.jpg");

        return true;
    }

    bool Renderer::Shutdown()
    {
        std::cout << "Shutting down Renderer";

        if (m_NativeRenderer != nullptr)
        {
            SDL_DestroyRenderer(m_NativeRenderer);
        }

        m_NativeRenderer = nullptr;

        m_Window.reset();

        return true;
    }

    void Renderer::DrawImage(/* Some image parameters IDK */)
    {
        // TODO: Remove after testing
        SDL_Rect dst{ 300, 200, 200, 200 };
        SDL_RenderCopy(m_NativeRenderer, m_helloWorldTexture.m_Texture, NULL, &dst);
    }

    void Renderer::SetBackgroundColor(unsigned char bgR_, unsigned char bgG_, unsigned char bgB_, unsigned char bgA_)
    {
        SDL_SetRenderDrawColor(m_NativeRenderer, bgR_, bgG_, bgB_, bgA_);
    }

    void Renderer::BeginScene() const
    {
        SDL_RenderClear(m_NativeRenderer);
    }

    void Renderer::EndScene() const
    {
        SDL_RenderPresent(m_NativeRenderer);
    }

    Renderer::~Renderer()
    {
        Shutdown();
    }

}