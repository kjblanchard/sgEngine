#pragma once
#include <SupergoonEngine/flecs/flecs.h>

#include <optional>

namespace Supergoon {

class GameObject {
public:
  GameObject(flecs::entity e);
  GameObject(GameObject *go);
  GameObject();
  // Use this to initialize this using a static gameobject, since the world isn't created at start time most of the time... Just make sure not to use it until you make a real one :)
  GameObject(int dummyGO);
  // Destroy gameobject and all its components
  void FreeGameObject();
  template <typename T, typename... Args>
  void AddComponent(Args &&...args);
  template <typename T>
  T &GetComponent();
  template <typename T>
  bool HasComponent() const;
  template <typename T>
  void RemoveComponent();
  template <typename T>
  static T *FindComponent();
  /**
   * @brief Iterate over all gameobjects with the params passed in with the passed in func.  This version is not cached, and should not be used by systems.
   *
   * @tparam Components Components that should be included in each iteration
   * @tparam Function params, The function (or lambda) to be called on each gameobject with the components
   * @param func The actual function
   */
  template <typename... Components, typename Func>
  static void ForEach(Func func);
  template <typename... Components>
  static std::optional<GameObject> GetGameObjectWithComponents();
  static void ClearGameObjects();
  static int NumberGameObjects();
  // TODO SHould only be used by gameobject query.
  static inline const flecs::world &GetWorld() { return _world; }

private:
  static flecs::world _world;
  flecs::entity _entity;

  template <typename... Components>
  static auto GetGameObjectsWithComponents();
};

template <typename T, typename... Args>
void GameObject::AddComponent(Args &&...args) {
  _entity.emplace<T>(T{std::forward<Args>(args)...});
  assert(_entity.has<T>());
}

template <typename T>
T &GameObject::GetComponent() {
  return *_entity.get_mut<T>();
}

template <typename T>
bool GameObject::HasComponent() const {
  return _entity.has<T>();
}

template <typename T>
void GameObject::RemoveComponent() {
  _entity.remove<T>();
}

template <typename T>
T *GameObject::FindComponent() {
  auto go = GetGameObjectWithComponents<T>();
  if (!go.has_value() || !go->template HasComponent<T>()) {
    return nullptr;
  }
  return &go->template GetComponent<T>();
}

template <typename... Components>
auto GameObject::GetGameObjectsWithComponents() {
  return _world.query<Components...>();
}

template <typename... Components, typename Func>
void GameObject::ForEach(Func func) {
  auto query = GetGameObjectsWithComponents<Components...>();
  query.each([&](flecs::entity entity, Components &...components) {
    GameObject gameObject(entity);
    func(gameObject, components...);
  });
}

// template <typename... Components, typename Func>
// void GameObject::ForEach(Func func, GameObjectQuery query) {
// 	auto query = GetGameObjectsWithComponents<Components...>();
// 	query.each([&](flecs::entity entity, Components&... components) {
// 		GameObject gameObject(entity);
// 		func(gameObject, components...);
// 	});
// }

template <typename... Components>
std::optional<GameObject> GameObject::GetGameObjectWithComponents() {
  auto query = _world.query<Components...>();
  std::optional<GameObject> result = std::nullopt;
  query.each([&](flecs::entity entity, Components &...) {
    if (!result.has_value()) {
      result = GameObject(entity);
    }
  });
  return result;
}

} // namespace Supergoon
