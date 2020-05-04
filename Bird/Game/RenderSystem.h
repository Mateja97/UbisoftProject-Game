#include "precomp.h"
#include "WindowData.h"
namespace Game {
	struct WindowData;
	class Renderer;
	class RenderSystem
	{
	public:
		bool Init(const WindowData& windowData_ = WindowData());
		bool Shutdown();
		void Update(float dt_);
	private:
		std::unique_ptr<Renderer> m_Renderer;
	};
}



