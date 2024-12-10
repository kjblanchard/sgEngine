#include <Supergoon/ECS/GameObject.h>
#include <stdlib.h>
static ecs_world_t* _world = NULL;

void sgInitializeECSWorld(void) {
	_world = ecs_init();
}
void sgFreeGameObject(GameObject gameObject) {
	ecs_delete(_world, gameObject);
}
GameObject sgGameObjectCreate(void) {
	return ecs_new(_world);
}
void sgClearGameObjects(void);
int sgNumberGameObjects(void);

void InitializeBuiltinECS(void) {
}

void sgClearGameObjects(void) {
	if (!_world) {
		return;
	}
	ecs_fini(_world);
}

int sgNumberGameObjects(void) {
	// Count all entities in the world.
	return 1;
}
