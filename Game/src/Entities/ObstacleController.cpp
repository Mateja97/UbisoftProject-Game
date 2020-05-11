#include "precomp.h"
#include "ObstacleController.h"
#include "PlayerController.h"
#include "Entities/GameComponents.h"
#include <random>

namespace Game
{
	static float GetRandomPosition()
	{
		std::random_device rd;
		std::uniform_int_distribution<int> pos(150, 550);

		return pos(rd);
	}

	bool ObstacleController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entityManager ObstacleController::Init()");
		ASSERT(texture_ != nullptr, "Must pass valid pointer to textuer ObstacleController::Init()");

		float randomPosition = 0;

		for (int i = 1; i < m_NumberOfObstacles; ++i) {
			//LOWER PIPE
			auto obstacle = std::make_unique<Engine::Entity>();
			
			randomPosition = GetRandomPosition();

			obstacle->AddComponent<ObstacleComponent>(150.f);
			obstacle->AddComponent<Engine::TransformComponent>(500.f * i, randomPosition , m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::CollisionComponent>(m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::MoverComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

			entityManager_->AddEntity(std::move(obstacle));

			//UPPER PIPE
			obstacle = std::make_unique<Engine::Entity>();

			obstacle->AddComponent<ObstacleComponent>(150.f);
			obstacle->AddComponent<Engine::TransformComponent>(500.f * i, randomPosition - 720.f, m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::CollisionComponent>(m_ObstacleWidth, m_ObstacleHeight);
			obstacle->AddComponent<Engine::MoverComponent>();
			obstacle->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

			entityManager_->AddEntity(std::move(obstacle));
		}

		for (int i = 1; i < m_NumberOfObstacles; ++i) {
			
			auto scoreColider = std::make_unique<Engine::Entity>();

			scoreColider->AddComponent<ScoreColiderComponent>();
			scoreColider->AddComponent<Engine::TransformComponent>(500.f * i + m_ObstacleWidth / 2 + 30.f, 0.f, 5.f, 720.f);
			scoreColider->AddComponent<Engine::CollisionComponent>(5.f, 720.f);
			scoreColider->AddComponent<Engine::MoverComponent>();
			//scoreColider->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

			entityManager_->AddEntity(std::move(scoreColider));
		}
		
		return true;
	}

	void ObstacleController::Update(float dt, Engine::EntityManager* entityManager_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entityManager ObstacleController::Update()");
		
		float randomPosition = 0;
		auto obstaclesToMove = entityManager_->GetAllEntitiesWithComponent<ObstacleComponent>();

		for (auto& obstacle : obstaclesToMove)
		{
			
			
			auto move = obstacle->GetComponent<Engine::MoverComponent>();
			auto speed = obstacle->GetComponent<Game::ObstacleComponent>()->m_Speed;
			if (!Game::PlayerController::m_running) {

				move->m_TranslationSpeed.x = 0;

			}else{
				move->m_TranslationSpeed.x = speed * -1.f;
			}
			
			auto transform = obstacle->GetComponent<Engine::TransformComponent>();

			
			if (transform->m_Position.x < -800.f)
			{
				transform->m_Position.x = 800.f;
				if (obstacle->GetId() % 2 == 1)
				{
					randomPosition = GetRandomPosition();
				}
				else
				{
					randomPosition = randomPosition - 720;;
				}
				transform->m_Position.y = randomPosition;
			}
		}

		obstaclesToMove = entityManager_->GetAllEntitiesWithComponent<Game::ScoreColiderComponent>();

		for (auto& colider : obstaclesToMove)
		{
			auto move = colider->GetComponent<Engine::MoverComponent>();
			auto speed = colider->GetComponent<Game::ScoreColiderComponent>()->m_Speed;
			if (!Game::PlayerController::m_running) {

				move->m_TranslationSpeed.x = 0;

			}
			else {
				move->m_TranslationSpeed.x = speed * -1.f;
			}

			auto transform = colider->GetComponent<Engine::TransformComponent>();


			if (transform->m_Position.x < -800.f)
			{
				transform->m_Position.x = 800.f;
				colider->GetComponent<ScoreColiderComponent>()->m_triggered = false;
			}
		}

	}
}