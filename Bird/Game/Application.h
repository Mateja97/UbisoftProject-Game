#include "precomp.h"
#include "WindowData.h"
namespace Game {
	class RenderSystem;
	class Application
	{
	public:
		virtual bool Init();
		virtual bool Shutdown();
		int Run();

		virtual ~Application() = default;
	private:
		virtual void Update(float dt);
		bool m_Running{ false };

		std::unique_ptr<RenderSystem> m_RenderSystem;
		WindowData m_WindowData{};
	};
	Application* CreateApplication();

}
