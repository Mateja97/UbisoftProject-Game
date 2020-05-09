#pragma once

namespace Engine 
{
	class EntityManager;
	class TextureManager;
}

namespace Game
{
	class ObstacleController
	{
	public:
		bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_);
		void Update(float dt, Engine::EntityManager* entityManager_);

	private:
		float m_ObstacleWidth = 125.f;
		float m_ObstacleHeight = 300.f;
		float m_ColiderHeight = 300.f;
	};
}