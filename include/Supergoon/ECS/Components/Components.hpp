#include <Supergoon/ECS/GameObject.h>
namespace Supergoon {
void RegisterBuiltinComponents();
extern ECS_COMPONENT_DECLARE(AnimationComponent);
extern ECS_COMPONENT_DECLARE(CameraComponent);
extern ECS_COMPONENT_DECLARE(GameState);
extern ECS_COMPONENT_DECLARE(ImageComponent);
extern ECS_COMPONENT_DECLARE(LocationComponent);
extern ECS_COMPONENT_DECLARE(KeepAliveComponent);
extern ECS_COMPONENT_DECLARE(SolidComponent);

}  // namespace Supergoon
