#include "precomp.h"
#include "PlayerController.h"
#include "Entities/GameComponents.h"

namespace Game
{
    
    bool PlayerController::m_running = true;
    int PlayerController::score = 0;

    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(-400.f, 0.f, 70.f, 70.f);
        //TODO: kolizija kruga
        player->AddComponent<Engine::CollisionComponent>(60.f, 60.f);
        player->AddComponent<Engine::PlayerComponent>(50.f);
        player->AddComponent<Engine::InputComponent>();
        player->AddComponent<Engine::MoverComponent>();
        player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        auto inputComp = player->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ fmt::format("Player{}MoveUp",1) });
        inputComp->inputActions.push_back({ fmt::format("Player{}MoveDown",1) });

        entityManager_->AddEntity(std::move(player));
        

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_)
    {
        auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent>();
        
        for (auto& entity : entitiesToMove)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto speed = entity->GetComponent<Engine::PlayerComponent>()->m_PanSpeed;
            auto pos = entity->GetComponent<Engine::TransformComponent>();
            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player{}MoveUp", 1));
            
            if (moveUpInput) {
                pos->m_Position.y -= speed;
            }
            move->m_TranslationSpeed.y = speed * (moveUpInput ? -10.0f : 3.0f);
            auto collider = entity->GetComponent<Engine::CollisionComponent>();

            for (const auto& coliderEntity : collider->m_CollidedWith)
            {
                if (coliderEntity->HasComponent<WallComponent>())
                {
                    auto mover = entity->GetComponent<Engine::MoverComponent>();
                    m_running = false;
                    mover->m_TranslationSpeed = {0, 0 };
                }
                if (coliderEntity->HasComponent<ObstacleComponent>())
                {
                    auto mover = entity->GetComponent<Engine::MoverComponent>();
                    m_running = false;
                    mover->m_TranslationSpeed = { 0,0 };
                }
                if (coliderEntity->HasComponent<ScoreColiderComponent>() && !coliderEntity->GetComponent<ScoreColiderComponent>()->m_triggered)
                {
                    coliderEntity->GetComponent<ScoreColiderComponent>()->m_triggered = true;
                    score += 1;
                }
            }
        }
    }
}
