#include <Supergoon/ECS/Components/AnimationComponent.hpp>
#include <Supergoon/ECS/Components/CameraComponent.hpp>
#include <Supergoon/ECS/Components/Components.hpp>
#include <Supergoon/ECS/Components/GameStateComponent.hpp>
#include <Supergoon/ECS/Components/ImageComponent.hpp>
#include <Supergoon/ECS/Components/KeepAliveComponent.hpp>
#include <Supergoon/ECS/Components/LocationComponent.hpp>
#include <Supergoon/ECS/Components/SolidComponent.hpp>
ECS_COMPONENT_DECLARE(AnimationComponent);
ECS_COMPONENT_DECLARE(CameraComponent);
ECS_COMPONENT_DECLARE(GameState);
ECS_COMPONENT_DECLARE(ImageComponent);
ECS_COMPONENT_DECLARE(LocationComponent);
ECS_COMPONENT_DECLARE(KeepAliveComponent);
ECS_COMPONENT_DECLARE(SolidComponent);
namespace Supergoon {

void RegisterBuiltinComponents() {
	sgComponentRegister(AnimationComponent);
	sgComponentRegister(CameraComponent);
	sgComponentRegister(GameState);
	sgComponentRegister(ImageComponent);
	sgComponentRegister(LocationComponent);
	sgComponentRegister(KeepAliveComponent);
	sgComponentRegister(SolidComponent);
}

}  // namespace Supergoon
