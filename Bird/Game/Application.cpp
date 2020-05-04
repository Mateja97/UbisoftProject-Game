#include "precomp.h"
#include "Application.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "Window.h"
#include "WindowData.h"
#include "SDL.h"
namespace Game {

	bool Application::Init() {

		std::cout << "Initializing app";

		m_RenderSystem = std::make_unique<RenderSystem>();
		if (!m_RenderSystem->Init(m_WindowData))
		{
			std::cerr<<"Failed to initialize RenderSystem";
			return false;
		}
		return true;
	}

	bool Application::Shutdown() {

		std::cout << "Shutting down app";
		m_RenderSystem->Shutdown();
		m_RenderSystem.reset();
		return true;
	}

	int Application::Run() {

		while (true) {
			float argForUpdate = 1.0f; //TODO:REMOVE

			Update(argForUpdate);
		}

		m_Running = false;
		return 0;
	}


	void Application::Update(float dt) {
		m_RenderSystem->Update(dt);
	}
	Game::Application* CreateApplication()
	{
		return new Game::Application();
	}


}