#pragma once
#include <SupergoonEngine/flecs/flecs.h>
#ifdef __cplusplus
extern "C" {
#endif

static ecs_world_t* _world;

#define sgGameObjectAddComponent(gameObject, component, ...) \
	ecs_set_ptr(_world, gameObject, component, __VA_ARGS__)

#define sgComponentRegister(component) \
	ECS_COMPONENT(_world, component)

#define sgComponentDeclare(component) \
	ECS_DECLARE(component)

#define sgGameObjectGetComponent(go, component) \
	ecs_get_mut(_world, go, component)

#define sgGameObjectGetGameObjectWithComponents(...)                  \
	({                                                                \
		ecs_query_t* query = ecs_query(_world, #__VA_ARGS__);         \
		ecs_iter_t it = ecs_query_iter(query);                        \
		ecs_entity_t first_entity = 0;                                \
		if (ecs_query_next(&it)) {                                    \
			if (it.count > 0) {                                       \
				first_entity = it.entities[0];                        \
			}                                                         \
		}                                                             \
		ecs_query_fini(query); /* Clean up query if it's temporary */ \
		first_entity;		   /* Return the first entity */          \
	})

typedef ecs_entity_t GameObject;

void sgInitializeECSWorld(void);
void sgFreeGameObject(GameObject gameObject);
GameObject sgGameObjectCreate(void);
void sgClearGameObjects(void);
int sgNumberGameObjects(void);
#ifdef __cplusplus
}
#endif
