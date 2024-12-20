#pragma once
#include <Supergoon/Primitives/Point.h>
#include <Supergoon/Primitives/Rectangle.hpp>
namespace Supergoon {
struct LocationComponent;

struct CameraComponent {
  RectangleF Box;
  sgPoint Bounds = {0, 0};
  LocationComponent *FollowTarget;
};

} // namespace Supergoon
