#include "precomp.h"
#include "StadiumController.h"

#include "Entities/GameComponents.h"

namespace Game
{
    bool Stadium::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BallController::Init()");

        // Down
        auto wall = std::make_unique<Engine::Entity>();

        wall->AddComponent<WallComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, 355.f, 1300.f, 30.f);
        wall->AddComponent<Engine::CollisionComponent>(1300.f, 30.f);

        entityManager_->AddEntity(std::move(wall));
        auto back = std::make_unique<Engine::Entity>();

        back->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 720.f);
        back->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        entityManager_->AddEntity(std::move(back));
        // Up
        wall = std::make_unique<Engine::Entity>();

        wall->AddComponent<WallComponent>();
        wall->AddComponent<Engine::TransformComponent>(0.f, -355.f, 1300.f, 30.f);
        wall->AddComponent<Engine::CollisionComponent>(1300.f, 30.f);


        entityManager_->AddEntity(std::move(wall));

        return true;
    }
}