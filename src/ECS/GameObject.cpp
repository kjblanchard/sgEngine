#include <Supergoon/ECS/Gameobject.hpp>
using namespace Supergoon;

flecs::world GameObject::_world;

GameObject::GameObject(flecs::entity e) : _entity(e) {}

GameObject::GameObject() : _entity(_world.entity()) {}

void GameObject::FreeGameObject() {
	_entity.destruct();
}

void GameObject::ClearGameObjects() {
	_world.reset();
	// _world.clear();
}

int GameObject::NumberGameObjects() {
	// Count all entities in the world.
	return 1;
	// return _world.count();
}
