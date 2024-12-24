#include <Supergoon/ECS/Components/AnimationComponent.hpp>
#include <Supergoon/ECS/Gameobject.hpp>
using namespace Supergoon;

flecs::world GameObject::_world;

GameObject::GameObject(flecs::entity e) : _entity(e) {}

GameObject::GameObject() : _entity(_world.entity()) {}
GameObject::GameObject(int dummyBoi) : _entity(dummyBoi) {}

void GameObject::FreeGameObject() {
  _entity.destruct();
}

void GameObject::ClearGameObjects() {
  _world.reset();
  // _world.clear();
}

int GameObject::NumberGameObjects() {
  // Count all entities in the world.
  // auto query = flecs::query_builder<AnimationComponent>();
  return 1;
  // return _world.count();
}
