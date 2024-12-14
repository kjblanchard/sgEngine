#pragma once

#include <Supergoon/Aseprite/AsepriteAnimation.hpp>
#include <Supergoon/Content/Image.hpp>
#include <Supergoon/Primitives/Point.h>
namespace Supergoon {
struct AnimationComponent {
  std::string AnimationName;
  float AnimationSpeed;
  sgPoint Offset = {0, 0};
  sgPoint OverrideDrawSize = {0, 0};
  bool Playing;
  std::shared_ptr<AsepriteAnimation> Animation;
  std::shared_ptr<Image> AnimationImage;
};
} // namespace Supergoon
