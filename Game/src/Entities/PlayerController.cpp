#include "precomp.h"
#include "PlayerController.h"
#include "Entities/GameComponents.h"

namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(-400.f, 0.f, 30.f, 100.f);
        //TODO: kolizija kruga
        player->AddComponent<Engine::CollisionComponent>(30.f, 100.0f);
        player->AddComponent<Engine::PlayerComponent>(100.f);
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

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player{}MoveUp", 1));
            LOG_INFO("Input: {}", moveUpInput);
            move->m_TranslationSpeed.y = speed * (moveUpInput ? -150.0f : 1.0f);

            auto collider = entity->GetComponent<Engine::CollisionComponent>();

            for (const auto& entity1 : collider->m_CollidedWith)
            {
                if (entity1->HasComponent<WallComponent>())
                {
                    auto mover = entity->GetComponent<Engine::MoverComponent>();
                    //TODO:Reakcija na sudar
                    mover->m_TranslationSpeed = { mover->m_TranslationSpeed.x, mover->m_TranslationSpeed.y * -1.f };
                }
            }
        }
    }
}