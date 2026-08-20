/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Core
*/

#include "AGameCore.hpp"
#include "helpers/time.hpp"

AGameCore::AGameCore(std::shared_ptr<IGraphicWrapper> graphicWrapper)
    : _graphicWrapper(std::move(graphicWrapper))
{
    registerComponents();
    registerSystem();
    registerBuilders();
}

void AGameCore::registerComponents()
{
    _registry.registerComponent<component::Position>();
    _registry.registerComponent<component::Velocity>();
    _registry.registerComponent<component::Health>();
    _registry.registerComponent<component::Projectile>();
    _registry.registerComponent<component::Enemy>();
    _registry.registerComponent<component::Player>();
    _registry.registerComponent<component::Controllable>();
    _registry.registerComponent<component::Collidable>();
    _registry.registerComponent<component::AI>();
    _registry.registerComponent<component::Drawable>();
    _registry.registerComponent<component::Background>();
    _registry.registerComponent<component::Lifespan>();
    _registry.registerComponent<component::Booster>();
}

void AGameCore::registerSystem()
{
    // Player
    _registry.addSystem<component::Velocity, component::Controllable, component::Player>(fsystem::Controlle());
    _registry.addSystem<component::Position, component::Controllable, component::Player>(fsystem::FirePlayer());
    _registry.addSystem<component::Player, component::Position>(fsystem::DeathPlayer());

    // animation
    _registry.addSystem<component::Drawable, component::Controllable, component::Player>(fsystem::UpdatePlayerAnimation());
    _registry.addSystem<component::Drawable>(fsystem::Animation());

    _registry.addSystem<component::Health, component::Position>(fsystem::DeathEnemy());
    _registry.addSystem<component::Position, component::Velocity>(fsystem::Position());
    _registry.addSystem<component::Position,component::Collidable>(fsystem::Collision());
    _registry.addSystem<component::Position, component::Player>(fsystem::CollisionWindow());

    // enemy IA
    _registry.addSystem<component::Velocity, component::Enemy, component::AI>(fsystem::PlatPlatIA());
    _registry.addSystem<component::Position, component::Enemy>(fsystem::FireEnemy());

    //clear
    _registry.addSystem<component::Lifespan>(fsystem::Lifespan());
    _registry.addSystem<component::Position, component::Enemy>(fsystem::ClearEnemy());
    _registry.addSystem<component::Position, component::Projectile>(fsystem::ClearProjectile());
    _registry.addSystem<component::Player>(fsystem::ClearInput());
}

void AGameCore::registerBuilders()
{
    _registry.registerBuilder<entity::Player>();
    _registry.registerBuilder<entity::Projectile>();
    _registry.registerBuilder<entity::Enemy>();
    _registry.registerBuilder<entity::Background>();
    _registry.registerBuilder<entity::AnimationDeath>();
    _registry.registerBuilder<entity::Booster>();
}

void AGameCore::run()
{
    const double timestep_second = 1.0F / _FPS;
    double accumulator_nano = 0.0F;
    int64_t last_time_nano = getTime();
    int64_t current_time_nano = getTime();
    double delta_time_nano;

    initContext();
    while (_running) {
        current_time_nano = getTime();
        delta_time_nano = current_time_nano - last_time_nano;
        last_time_nano = current_time_nano;
        accumulator_nano += delta_time_nano;

        handleEvents();
        if (accumulator_nano >= timestep_second * NANOSECONDS_PER_SECOND) {
            updateContext(accumulator_nano / NANOSECONDS_PER_SECOND);
            update();
            render();
            accumulator_nano = 0.0F;
            _currentTick++;
        }
    }
}

void AGameCore::initContext() {
    Context context;

    context.graphicWrapper = _graphicWrapper;
    context.deltaTimeSeconds = 0.0F;
    _registry.setContext(context);
}

void AGameCore::updateContext(double deltaSeconds) {
    auto &context = _registry.getContext<Context>();

    context.deltaTimeSeconds = deltaSeconds;
}
