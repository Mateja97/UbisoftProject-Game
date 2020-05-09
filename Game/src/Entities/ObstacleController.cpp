#include "precomp.h"
#include "ObstacleController.h"
#include "Entities/GameComponents.h"

namespace Game
{
	bool ObstacleController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entityManager ObstacleController::Init()");
		ASSERT(texture_ != nullptr, "Must pass valid pointer to textuer ObstacleController::Init()");

		for (int i = 1; i < 8; ++i) {
			//UPPER PIPE
			auto obstacle = std::make_unique<Engine::Entity>();

			obstacle->AddComponent<ObstacleComponent>(150.f);
			obstacle->AddComponent<Engine::TransformComponent>(400.f * i, 300.f , m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::CollisionComponent>(m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::MoverComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

			entityManager_->AddEntity(std::move(obstacle));

			//TODO:Colider koji povecava skor igraca kada prodje kroz prepreku
			auto scoreColider = std::make_unique<Engine::Entity>();

			scoreColider->AddComponent<Engine::TransformComponent>(400.f * i + m_ObstacleWidth / 2, 0.f, 50.f, m_ColiderHeight);
			scoreColider->AddComponent<Engine::CollisionComponent>(50.f, m_ColiderHeight);

			entityManager_->AddEntity(std::move(scoreColider));

			//LOWER PIPE
			obstacle = std::make_unique<Engine::Entity>();

			obstacle->AddComponent<ObstacleComponent>(150.f);
			obstacle->AddComponent<Engine::TransformComponent>(400.f * i, -300.f, m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::CollisionComponent>(m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::MoverComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

			entityManager_->AddEntity(std::move(obstacle));
		}
		//TODO: mozda da stavim proveru za obstacle kao return tip
		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entityManager ObstacleController::Update()");

		auto obstaclesToMove = entityManager_->GetAllEntitiesWithComponent<ObstacleComponent>();

		for (auto& obstacle : obstaclesToMove)
		{
			auto move = obstacle->GetComponent<Engine::MoverComponent>();
			auto speed = obstacle->GetComponent<Game::ObstacleComponent>()->m_Speed;

			move->m_TranslationSpeed.x = speed * -1.f;
			
			auto transform = obstacle->GetComponent<Engine::TransformComponent>();
			LOG_INFO("{}", transform->m_Position.x);
			if (transform->m_Position.x < -800.f)
			{
				transform->m_Position.x = 800.f;
			}
		}
	}
}